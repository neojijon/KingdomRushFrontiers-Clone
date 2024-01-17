#include "BarrackSoldier.h"
#include "Data/GameManager.h"

bool BarrackSoldier::initSoldier(int level)
{
	if (!BaseSoldier::init())
	{
		return false;
	}
	setLevel(level);
	setForce(3*level);
	baseSprite = Sprite::createWithSpriteFrameName(StringUtils::format("soldier_lvl%d_0001.png",level));
	addChild(baseSprite);
	createAndSetHpBar();
	lastState = SoldierStateNone;
	return true;
}

BarrackSoldier* BarrackSoldier::createSoldier(Vec2 point,int level)
{
    auto barrackSoldier = new BarrackSoldier();
    if (barrackSoldier && barrackSoldier->initSoldier(level))
    {

        barrackSoldier->setLocation(point);
		barrackSoldier->setMaxHp(50);
		barrackSoldier->setCurrHp(50);
        barrackSoldier->runToLocation(point);    
        barrackSoldier->autorelease();
        return barrackSoldier;
    }
	CC_SAFE_DELETE(barrackSoldier);
    return NULL;
}

void BarrackSoldier::update(float dt)
{
	//��״̬����
	if(lastState!=getState()){
		//����״̬�ж�
		switch (getState())
		{
		case(SoldierStateRun):{
			lastState = SoldierStateRun;
			//ֹ֮ͣǰ����
			stopSoldierAnimation();
			auto action = RepeatForever::create(Animate::create(AnimationCache::getInstance()->getAnimation(StringUtils::format("level%d_barracksSoilder_run",level))));
			action->setTag(SoldierStateRun);
			baseSprite->runAction(action);}
			break;
		case(SoldierStateHit):{
			lastState = SoldierStateHit;
			stopSoldierAnimation();
			auto action = RepeatForever::create(Animate::create(AnimationCache::getInstance()->getAnimation(StringUtils::format("level%d_barracksSoilder_attack",level))));
			action->setTag(SoldierStateHit);
			baseSprite->runAction(action);}
			break;
		case(SoldierStateWait):{
			lastState = SoldierStateWait;
			stopSoldierAnimation();
			baseSprite->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(StringUtils::format("soldier_lvl%d_0001.png",level)));}
			break;
		case(SoldierStateDeath):{
			lastState = SoldierStateDeath;}
			break;
		}
	}
}

void BarrackSoldier::updateSoldier(int level)
{
	setLevel(level);
	setForce(4*level);
	setMaxHp(40*level);
	stopSoldierAnimation();
	this->setCurrHp(this->getMaxHp());
	this->setHpPercentage(100);
	this->getHpBar()->setPercentage(100);
	baseSprite->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(StringUtils::format("soldier_lvl%d_0001.png",level)));
	lastState = SoldierStateNone;
}

void BarrackSoldier::attackMonster(float dt)
{
	if(nearestMonster!=NULL && nearestMonster->getCurrHp()>0){
		if (!checkDirectionForMonster()){
			nearestMonster->setState(stateAttackLeft);
		}else{
			nearestMonster->setState(stateAttackRight);
		}
		setState(SoldierStateHit);
		auto monsterCurrHp = nearestMonster->getCurrHp();
		auto SoldierHp = this->getCurrHp();

		monsterCurrHp =  monsterCurrHp - this->getForce();
		if(nearestMonster->getState()!=stateFrozen)
			SoldierHp =  SoldierHp - nearestMonster->getForce();

		if(monsterCurrHp <= 0){
			monsterCurrHp = 0;
		}
		if(SoldierHp <= 0){
			SoldierHp = 0;
		}
		nearestMonster->setCurrHp( monsterCurrHp );
		this->setCurrHp(SoldierHp);

		nearestMonster->getHpBar()->setPercentage((monsterCurrHp/nearestMonster->getMaxHp())*100);
		this->getHpBar()->setPercentage((SoldierHp/this->getMaxHp())*100);

		if(monsterCurrHp == 0){
			unschedule(CC_SCHEDULE_SELECTOR(BarrackSoldier::attackMonster));
			//GameManager::getInstance()->monsterVector.eraseObject(nearestMonster);
			nearestMonster->death();
			if(this->getCurrHp()>0)
				runToLocation(location);
		}
		if(SoldierHp == 0){
			lastState = SoldierStateDeath;
			setState(SoldierStateDeath);
			unscheduleAllCallbacks();
			stopAllActions();
			baseSprite->stopAllActions();
			hpBgSprite->setVisible(false);
			if(nearestMonster != NULL && nearestMonster->getCurrHp()>0){
				nearestMonster->restartWalking();
				nearestMonster->setIsAttacking(false);
			}
			baseSprite->runAction(Sequence::create(
				Animate::create(AnimationCache::getInstance()->getAnimation(StringUtils::format("level%d_barracksSoilder_dead",level))),
				FadeOut::create(1.0f)
				,NULL));
		}
	}else{
		unschedule(CC_SCHEDULE_SELECTOR(BarrackSoldier::attackMonster));
		if(this->getCurrHp()>0)
			runToLocation(location);
	}
}