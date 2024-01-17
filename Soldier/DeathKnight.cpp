#include "DeathKnight.h"
#include "Data/GameManager.h"

DeathKnight* DeathKnight::createDeathKnight(Vec2 point)
{
    auto deathKnight = new DeathKnight();
    if (deathKnight && deathKnight->init())
    {

        deathKnight->setLocation(point);
		deathKnight->setMaxHp(250);
		deathKnight->setCurrHp(250); 
		deathKnight->setForce(30);
		deathKnight->setState(SoldierStateNone);
		deathKnight->birth(point);
        deathKnight->autorelease();
        return deathKnight;
    }
	CC_SAFE_DELETE(deathKnight);
    return NULL;
}

void DeathKnight::birth(Vec2 point)
{
	SoundManager::playDKReady();
	setPosition(point);

	baseSprite->runAction(Sequence::create(
		Animate::create(AnimationCache::getInstance()->getAnimation("DK_birth"))
		,CallFuncN::create(CC_CALLBACK_0(DeathKnight::setState, this,SoldierStateWait))
                , NULL));
	schedule(CC_SCHEDULE_SELECTOR(DeathKnight::lookingForMonsters), 1.0f,-1,caculateTime(point));
}

bool DeathKnight::init()
{
	if(!BaseSoldier::init()){
		return false;
	}
	baseSprite = Sprite::createWithSpriteFrameName("NecromancerDeathKnight_0001.png");
	addChild(baseSprite);
	createAndSetHpBar();
	lastState = SoldierStateNone;

	return true;
}

void DeathKnight::attackMonster(float dt)
{
	if(nearestMonster!=NULL && nearestMonster->getCurrHp()>0){
		setState(SoldierStateHit);
		if (!checkDirectionForMonster()){
			nearestMonster->setState(stateAttackLeft);
		}else{
			nearestMonster->setState(stateAttackRight);
		}
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
			unschedule(CC_SCHEDULE_SELECTOR(DeathKnight::attackMonster));
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
				Animate::create(AnimationCache::getInstance()->getAnimation("DK_death"))
				,FadeOut::create(1.0f)
				,NULL));
		}
	}else{
		unschedule(CC_SCHEDULE_SELECTOR(DeathKnight::attackMonster));
		if(this->getCurrHp()>0)
				runToLocation(location);
	}
}

void DeathKnight::update(float dt)
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
			auto action = RepeatForever::create(Animate::create(AnimationCache::getInstance()->getAnimation("DK_run")));
			action->setTag(SoldierStateRun);
			baseSprite->runAction(action);}
			break;
		case(SoldierStateHit):{
			lastState = SoldierStateHit;
			stopSoldierAnimation();
			auto action = RepeatForever::create(Animate::create(AnimationCache::getInstance()->getAnimation("DK_attack")));
			action->setTag(SoldierStateHit);
			baseSprite->runAction(action);}
			break;
		case(SoldierStateWait):{
			lastState = SoldierStateWait;
			stopSoldierAnimation();
			baseSprite->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("NecromancerDeathKnight_0001.png"));}
			break;
		}
	}
}

void DeathKnight::createAndSetHpBar()
{
    hpBgSprite = Sprite::createWithSpriteFrameName("lifebar_bg_small.png");

    hpBgSprite->setPosition(Vec2(baseSprite->getContentSize().width / 2, baseSprite->getContentSize().height));
    baseSprite->addChild(hpBgSprite);
    
	hpBar = ProgressTimer::create(Sprite::createWithSpriteFrameName("lifebar_small.png"));
	hpBar->setType(ProgressTimer::Type::BAR);
	hpBar->setMidpoint(Vec2(0, 0.5f));
	hpBar->setBarChangeRate(Vec2(1, 0));
	hpBar->setPercentage(100);
    hpBar->setPosition(Vec2(hpBgSprite->getContentSize().width / 2, hpBgSprite->getContentSize().height / 2 ));
    hpBgSprite->addChild(hpBar);
}