#include "BaseArtilleryTower.h"
#include "Data/GameManager.h"
#include "Bullet/Bomb.h"

void BaseArtilleryTower::initTower(int level)
{
	setName(cocos2d::StringUtils::format("level%d_Artillery_",level));
	towerBase = Sprite::createWithSpriteFrameName(cocos2d::StringUtils::format("tower_artillery_lvl%d_layer1_0001.png",level));
	leftShooter = Sprite::createWithSpriteFrameName(cocos2d::StringUtils::format("tower_artillery_lvl%d_layer2_0001.png",level));
	rightShooter = Sprite::createWithSpriteFrameName(cocos2d::StringUtils::format("tower_artillery_lvl%d_layer3_0001.png",level));
	barrel = Sprite::createWithSpriteFrameName(cocos2d::StringUtils::format("tower_artillery_lvl%d_layer4_0001.png",level)); 
	smoke = Sprite::createWithSpriteFrameName(cocos2d::StringUtils::format("tower_artillery_lvl%d_layer5_0001.png",level)); 
	c4 = Sprite::createWithSpriteFrameName(cocos2d::StringUtils::format("tower_artillery_lvl%d_layer6_0001.png",level));  

	addChild(towerBase);
	addChild(leftShooter);
	addChild(rightShooter);
	addChild(barrel);
	addChild(smoke);
	addChild(c4);
	addChild(Sprite::createWithSpriteFrameName(cocos2d::StringUtils::format("tower_artillery_lvl%d_layer7_0001.png",level)));

	isReady = true;
}

void BaseArtilleryTower::addTerrain()
{
	terrain = Sprite::createWithSpriteFrameName("terrain_artillery_0004.png");
	terrain->setAnchorPoint(Vec2(0.5,1));
	addChild(terrain,-1);
}

void BaseArtilleryTower::shoot(float dt)
{
	checkNearestMonster();
	if(isReady && nearestMonster!=NULL && nearestMonster->getCurrHp() > 0)
    {
		isReady = false;
		auto firePosition = nearestMonster->baseSprite->getPosition() - this->getParent()->getPosition();
		runAction(Sequence::create(
			CallFuncN::create(CC_CALLBACK_0(BaseArtilleryTower::fireAnimation,this)),
			CallFuncN::create(CC_CALLBACK_0(BaseArtilleryTower::fire,this,firePosition))
			,NULL));
	}
}

void BaseArtilleryTower::filledAnimation()
{
	leftShooter->runAction(Animate::create(AnimationCache::getInstance()->getAnimation(getName()+"leftShooter_throw")));
	c4->runAction(Animate::create(AnimationCache::getInstance()->getAnimation(getName()+"c4")));
	isReady = true;
}

void BaseArtilleryTower::fire(Vec2 firePosition)
{
	auto currBullet = ArtilleryTowerBullet();

	auto shootVector = firePosition;

	Vec2 highPoint = Vec2(shootVector.x,shootVector.y+200);

		
	ccBezierConfig bezier;

		
	bezier.controlPoint_1 = Vec2(currBullet->getPosition().x,currBullet->getPosition().y+200); 
	bezier.controlPoint_2 = Vec2(shootVector.x,shootVector.y+200);; 
	bezier.endPosition = shootVector;
	float endRotate;
	if(shootVector.x>currBullet->getPosition().x)
		endRotate = 180.0f;
	else
		endRotate = -180.0f;
	auto action = Spawn::create(BezierTo::create(1.0f, bezier),RotateTo::create(1.0f,endRotate),NULL);
	currBullet->setBulletAction(action);
	currBullet->shoot();
	runAction(Sequence::create(DelayTime::create(1.0f),
		CallFuncN::create(CC_CALLBACK_0(BaseArtilleryTower::filledAnimation,this)),
		NULL));
	currBullet = NULL;
}

void BaseArtilleryTower::fireAnimation()
{
	leftShooter->runAction(Animate::create(AnimationCache::getInstance()->getAnimation(getName()+"leftShooter_hold")));
	towerBase->runAction(Animate::create(AnimationCache::getInstance()->getAnimation(getName()+"towerBase")));
	barrel->runAction(Animate::create(AnimationCache::getInstance()->getAnimation(getName()+"barrel")));
	rightShooter->runAction(Animate::create(AnimationCache::getInstance()->getAnimation(getName()+"rightShooter")));
	smoke->runAction(Animate::create(AnimationCache::getInstance()->getAnimation(getName()+"smoke")));
}

Bullet* BaseArtilleryTower::ArtilleryTowerBullet()
{	
	auto bullet = Bomb::createBombWithType(getLevel());
	bullet->setPosition(Vec2(0,30));
	this->getParent()->addChild(bullet);
    return bullet;
}

void BaseArtilleryTower::checkNearestMonster()
{
    auto instance = GameManager::getInstance();
    auto monsterVector = instance->monsterVector;
    
	auto currMinDistant = this->scope;
    
	BaseMonster *monsterTemp = NULL;
	for(int i = 0; i < monsterVector.size(); i++)
	{
		auto monster = monsterVector.at(i);
		double distance = this->getParent()->getPosition().getDistance(monster->baseSprite->getPosition());

		if (distance < currMinDistant && monster->getAttackByTower() && monster->getAttackBySoldier()) {
			currMinDistant = distance;
            monsterTemp = monster;
		}
	}
    nearestMonster = monsterTemp;
}