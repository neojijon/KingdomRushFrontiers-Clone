#include "Immortal.h"
#include "Fallen.h"
#include "Data/GameManager.h"

USING_NS_CC;

Immortal* Immortal::createMonster(std::vector<Vec2> points)
{
    auto monster = new Immortal();
    if (monster && monster->init())
    {

        monster->setPointsVector(points);
		monster->setMaxHp(290);
		monster->setCurrHp(290);
		monster->setMoney(100);
		monster->setRunSpeed(40);
		monster->setArmor(10);
		monster->setForce(30);
		monster->setAttackBySoldier(true);
        monster->runNextVec2();       
        monster->autorelease();
        return monster;
    }
    CC_SAFE_DELETE(monster);
    return NULL;
}

bool Immortal::init()
{
	if (!Sprite::init())
	{
		return false;
	}
	setMonsterType(IMMORTAL);
	setName("Immortal_");
	baseSprite = Sprite::createWithSpriteFrameName("desertImmortal_0001.png");
	addChild(baseSprite);
	createAndSetHpBar();
	setState(stateNone);
	blood = Sprite::createWithSpriteFrameName("fx_blood_splat_red_0001.png");
	blood->setPosition(Vec2(baseSprite->getContentSize().width/2,baseSprite->getContentSize().height/2));
	baseSprite->addChild(blood);
	blood->setVisible(false);
	lastState = stateNone;
	scheduleUpdate();
	setListener();
	return true;
}

Vec2 Immortal::nextVec2()
{
    auto maxCount = int(pointsVector.size());
	pointCounter++;
	if (pointCounter < maxCount  ){
		auto node =this->pointsVector.at(pointCounter);
		pointsVector.pop_back();
        return node;
    }
	else{
		pointCounter = maxCount - 1 ;
	}
	return currVec2();
}

void Immortal::death()
{
	if(GameManager::getInstance()->monsterVector.contains(this))
		GameManager::getInstance()->monsterVector.eraseObject(this);
	if(getState()!=stateDeath){
		setState(stateDeath);
		hpBgSprite->setVisible(false);
		baseSprite->stopAllActions();
		unscheduleUpdate();
		GameManager::getInstance()->MONEY = GameManager::getInstance()->MONEY + getMoney();
		baseSprite->runAction(Sequence::create(
			Animate::create(AnimationCache::getInstance()->getAnimation(getName()+"death"))
			,CallFuncN::create(CC_CALLBACK_0(Immortal::setVisible, this,false)),NULL));

		auto fallen = Fallen::createMonster(pointsVector,this->getPosition(),pointCounter);
		this->getParent()->addChild(fallen);
		GameManager::getInstance()->monsterVector.pushBack(fallen);

	}
}

void Immortal::explosion()
{
	death();
}