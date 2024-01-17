#include "WaspQueen.h"

USING_NS_CC;

WaspQueen* WaspQueen::createMonster(std::vector<Vec2> points)
{
    auto monster = new WaspQueen();
    if (monster && monster->init())
    {

        monster->setPointsVector(points);
		monster->setMaxHp(320);
		monster->setCurrHp(320);
		monster->setRunSpeed(30);
		monster->setArmor(10);
		monster->setAttackBySoldier(false);
        monster->runNextVec2();      
		monster->setMoney(50);
        monster->autorelease();
        return monster;
    }
	CC_SAFE_DELETE(monster);
    return NULL;
}

void WaspQueen::frozen()
{
	if(getState()!=stateFrozen){
		tempState = lastState;
		setState(stateFrozen);
		baseSprite->stopAllActions();
		ice = Sprite::createWithSpriteFrameName("freeze_creepFlying_0009.png");
		ice->setPosition(Vec2(baseSprite->getContentSize().width/2,baseSprite->getContentSize().height/4));
		baseSprite->addChild(ice);
		ice->runAction(Animate::create(AnimationCache::getInstance()->getAnimation("freeze_creepFlying")));
		scheduleOnce(CC_SCHEDULE_SELECTOR(WaspQueen::refrozen),8.0f);
	}else{
		unschedule(CC_SCHEDULE_SELECTOR(WaspQueen::refrozen));
		scheduleOnce(CC_SCHEDULE_SELECTOR(WaspQueen::refrozen),8.0f);
		ice->stopAllActions();
		ice->removeFromParent();
		ice = Sprite::createWithSpriteFrameName("freeze_creepFlying_0009.png");
		ice->setPosition(Vec2(baseSprite->getContentSize().width/2,baseSprite->getContentSize().height/4));
		baseSprite->addChild(ice);
		ice->runAction(Animate::create(AnimationCache::getInstance()->getAnimation("freeze_creepFlying")));
	}
}

void WaspQueen::refrozen(float dt)
{
	ice->runAction(Sequence::create(Animate::create(AnimationCache::getInstance()->getAnimation("refreeze_creepFlying"))
										,CallFuncN::create(CC_CALLBACK_0(Sprite::removeFromParent, ice))
										,CallFuncN::create(CC_CALLBACK_0(WaspQueen::restartWalking, this))
                                       , NULL));
}

bool WaspQueen::init()
{
	if (!Sprite::init())
	{
		return false;
	}
	setMonsterType(WASPHORNET);
	setName("WaspQueen_");
	baseSprite = Sprite::createWithSpriteFrameName("wasp_queen_0001.png");
	addChild(baseSprite);
	createAndSetHpBar();
	blood = Sprite::createWithSpriteFrameName("fx_blood_splat_red_0001.png");
	blood->setPosition(Vec2(baseSprite->getContentSize().width/2,baseSprite->getContentSize().height/2));
	baseSprite->addChild(blood);
	blood->setVisible(false);
	lastState = stateNone;
	scheduleUpdate();
	setListener();
	return true;
}