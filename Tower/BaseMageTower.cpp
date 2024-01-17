#include "BaseMageTower.h"
#include "Layer/Menu/UpdatePanleLayer.h"
#include "Map/BaseMap.h"
#include "Data/GameManager.h"
#include "math.h"

void BaseMageTower::initTower(int level)
{
	if(level<4)
	{
		towerBase=Sprite::createWithSpriteFrameName(cocos2d::StringUtils::format("mage_lvl%d_0001.png",level));
		shooter=Sprite::createWithSpriteFrameName(cocos2d::StringUtils::format("mage_shooter_0001.png"));
		shooter->setPosition(Vec2(towerBase->getContentSize().width/2+3,towerBase->getContentSize().height/2+34));
	}
	if(4==level){
		towerBase=Sprite::createWithSpriteFrameName("ArchMageTower.png" );
		shooter=Sprite::createWithSpriteFrameName("ArchMageGuy_0001.png");
		shooter->setPosition(Vec2(towerBase->getContentSize().width/2+3,towerBase->getContentSize().height/2+34));
	}
	if(5==level){
		towerBase=Sprite::createWithSpriteFrameName("NecromancerTower.png");
		shooter=Sprite::createWithSpriteFrameName("NecomancerMage_0001.png");
		shooter->setPosition(Vec2(towerBase->getContentSize().width/2+3,towerBase->getContentSize().height/2+34));
	}
	towerBase->setPosition(Vec2(0,-10));
	towerBase->addChild(shooter);
	addChild(towerBase);
	
	currBullet=NULL;
}

void BaseMageTower::addTerrain()
{
	terrain = Sprite::createWithSpriteFrameName("terrain_mage_0004.png");
	terrain->setAnchorPoint(Vec2(0.5,1));
	addChild(terrain,-1);
}

Bullet* BaseMageTower::MageTowerBullet()
{
	 return NULL;
}

void BaseMageTower::shoot(float dt)
{
	auto instance = GameManager::getInstance();
	checkNearestMonster();
	if(nearestMonster!=NULL && nearestMonster->getCurrHp() > 0)
    {
		auto currBullet = MageTowerBullet();
		SoundManager::playMageTowerShot();
		Vec2 shootVector = nearestMonster->baseSprite->getPosition() - this->getParent()->getPosition();
		
		auto position=currBullet->getPosition()-shootVector;
		auto rotation=atan2(position.y,position.x);
		float angleDegrees = CC_RADIANS_TO_DEGREES(rotation);
		currBullet->setRotation(180.0f-angleDegrees);

		towerBase->runAction(Animate::create(AnimationCache::getInstance()->getAnimation(cocos2d::StringUtils::format("level%d_mage_shine",level))));


		if(shootVector.y>0){
			shooter->runAction(Animate::create(AnimationCache::getInstance()->getAnimation("mage_shoot_up")));
		}else{
			shooter->runAction(Animate::create(AnimationCache::getInstance()->getAnimation("mage_shoot_down")));
		}

		auto actionMove=MoveTo::create(0.25f,shootVector);
		auto action=Spawn::create(actionMove,NULL);

		currBullet->setBulletAction(action);
		currBullet->shoot();
		currBullet = NULL;
	}
}