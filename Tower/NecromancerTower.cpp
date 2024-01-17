#include "NecromancerTower.h"
#include "Layer/Menu/UpdatePanleLayer.h"
#include "Map/BaseMap.h"
#include "Data/GameManager.h"
#include "Map/BaseMap.h"
#include "Bullet/NecrBolt.h"
#include "Layer/Menu/SimplePanleLayerWithFlag.h"

bool NecromancerTower::init()
{
	if(!Sprite::init())
	{
		return false;
	}
	setTowerType(NEC);
	setLevel(5);
	addTerrain();
	initTower(5);
	setListener();
	setScope(220.0f);
	setBuildMoney(730);
	isUpdateMenuShown = false;
	schedule(CC_SCHEDULE_SELECTOR(NecromancerTower::Attack), 2.0f);
	deathKnight = DeathKnight::createDeathKnight(Vec2(0,-40));
	addChild(deathKnight);
	SoundManager::playNecTowerReady();
	glow = Sprite::createWithSpriteFrameName("NecromancerTowerGlow.png");
	addChild(glow);
	glow->setPosition(Vec2(0,-5));
	glow->setVisible(false);
	auto effect = Sprite::createWithSpriteFrameName("NecromancerTowerEffect_0001.png");
	effect->setPosition(Vec2(0,10));
	addChild(effect);
	effect->runAction(RepeatForever::create(Animate::create(AnimationCache::getInstance()->getAnimation("NecromancerTower_Effect"))));
	schedule(CC_SCHEDULE_SELECTOR(NecromancerTower::cureSoldiers), 10.0f,-1,10.0f);
	return true;
}

Bullet* NecromancerTower::MageTowerBullet()
{
	auto bullet = NecrBolt::create();
	bullet->setPosition(Vec2(10,45));
	bullet->setMaxForce(80);
	this->getParent()->addChild(bullet);
    return bullet;
}

void NecromancerTower::Attack(float dt)
{
	auto instance = GameManager::getInstance();
	checkNearestMonster();
	if(nearestMonster!=NULL && nearestMonster->getCurrHp() > 0 )
    {
		SoundManager::playNecShot();
		auto currBullet = MageTowerBullet();

		Vec2 shootVector = nearestMonster->baseSprite->getPosition() - this->getParent()->getPosition();
		
		auto position=currBullet->getPosition()-shootVector;
		auto rotation=atan2(position.y,position.x);
		float angleDegrees = CC_RADIANS_TO_DEGREES(rotation);
		currBullet->setRotation(180.0f-angleDegrees);

		
		if(shootVector.y>0){
			shooter->runAction(Animate::create(AnimationCache::getInstance()->getAnimation("NecomancerMage_shoot_up")));
		}
		else{
			shooter->runAction(Animate::create(AnimationCache::getInstance()->getAnimation("NecomancerMage_shoot_down")));
		}
		glow->runAction(Sequence::create(
				CallFuncN::create(CC_CALLBACK_0(Sprite::setVisible,glow,true)),
				DelayTime::create(0.5f),
				CallFuncN::create(CC_CALLBACK_0(Sprite::setVisible,glow,false)),
				NULL));
		auto actionMove=MoveTo::create(0.5f,shootVector);
		auto action=Spawn::create(actionMove,NULL);
		currBullet->setBulletAction(action);
		currBullet->shoot();
		currBullet = NULL;
	}
}

void NecromancerTower::showUpdateMenu()
{
	auto simplePanleLayer = SimplePanleLayerWithFlag::create();
	simplePanleLayer->setTag(myTerrain->getTag()+100);
	simplePanleLayer->setTower(this);
	simplePanleLayer->setPosition(this->getParent()->getPosition());
	static_cast<BaseMap*>(this->getParent()->getParent())->mTouchLayer->addChild(simplePanleLayer);
	simplePanleLayer->inAnimation();
	isUpdateMenuShown = true;
}

void NecromancerTower::setRallyVec2(Vec2 point)
{
	auto rally = point - this->getParent()->getPosition();
	SoundManager::playDKTaunt();
	deathKnight->setLocation(rally);

	if(deathKnight->nearestMonster!=NULL && deathKnight->nearestMonster->getState()!=stateDeath)
		deathKnight->nearestMonster->restartWalking();			
	deathKnight->runToLocation(deathKnight->getLocation());
}

void NecromancerTower::cureSoldiers(float dt)
{
	if(deathKnight->getState() == SoldierStateWait){
		deathKnight->setCurrHp(deathKnight->getMaxHp());
		deathKnight->setHpPercentage(100);
		deathKnight->getHpBar()->setPercentage(100);
	}
	else if(deathKnight->getState() == SoldierStateDeath){
		auto point = deathKnight->getLocation();
		deathKnight ->removeFromParent();
		deathKnight = NULL;
		deathKnight = DeathKnight::createDeathKnight(point);
		addChild(deathKnight);
	}
}