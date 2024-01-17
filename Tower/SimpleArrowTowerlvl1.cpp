#include "SimpleArrowTowerlvl1.h"
#include "SimpleArrowTowerlvl2.h"
#include "Layer/Menu/UpdatePanleLayer.h"
#include "Map/BaseMap.h"
#include "Data/GameManager.h"
#include "Bullet/Arrow.h"

bool SimpleArrowTowerlvl1::init()
{
	if (!Sprite::init())
	{
		return false;
	}
	setTowerType(ARCHER_1);
	setLevel(1);
	addTerrain();
	buildingAnimation();
	
	setForce(8);
	setScope(160.0f);
	setUpdateMoney(100);
	setBuildMoney(70);
	setNextScope(180.0f);

	isUpdateMenuShown = false;
	return true;
}

void SimpleArrowTowerlvl1::buildingAnimation()
{
	auto building = Sprite::create();
	auto constructing = Sprite::createWithSpriteFrameName("tower_constructing_0004.png");
	auto hpBgSprite = Sprite::createWithSpriteFrameName("buildbar_bg.png");
	hpBgSprite->setPosition(Vec2(constructing->getContentSize().width / 2, constructing->getContentSize().height /2+10));
	auto hpBar = ProgressTimer::create(Sprite::createWithSpriteFrameName("buildbar.png"));
	hpBar->setType(ProgressTimer::Type::BAR);
	hpBar->setMidpoint(Vec2(0, 0.5f));
	hpBar->setBarChangeRate(Vec2(1, 0));
	hpBar->setPercentage(0);
    hpBar->setPosition(Vec2(hpBgSprite->getContentSize().width / 2, hpBgSprite->getContentSize().height / 2 ));
    hpBgSprite->addChild(hpBar);
	constructing->addChild(hpBgSprite);
	building->addChild(constructing);
	addChild(building);
	hpBar->runAction(Sequence::create(ProgressTo::create(0.5f, 100)
		, CallFuncN::create(CC_CALLBACK_0(Sprite::removeFromParent, building))
                                           , NULL));
	scheduleOnce(CC_SCHEDULE_SELECTOR(SimpleArrowTowerlvl1::buildingSmokeAnimation),0.5f);
}

void SimpleArrowTowerlvl1::buildingSmokeAnimation(float dt)
{
	auto smoke = Sprite::createWithSpriteFrameName("effect_buildSmoke_0001.png");
	addChild(smoke,99);
	smoke->runAction(Sequence::create(
		Animate::create(AnimationCache::getInstance()->getAnimation("build_smoke")),
		CallFuncN::create(CC_CALLBACK_0(Sprite::removeFromParent, smoke)),
		NULL));
	SoundManager::playArcherReady();
	initTower(1);
	setListener();

	schedule(CC_SCHEDULE_SELECTOR(SimpleArrowTowerlvl1::shoot), 1.0f);
}

void SimpleArrowTowerlvl1::updateTower()
{
	auto simpleArrowTowerlvl2 = SimpleArrowTowerlvl2::create();
	simpleArrowTowerlvl2->setMyTerrain(myTerrain);
	simpleArrowTowerlvl2->setTag(myTerrain->getTag());
	simpleArrowTowerlvl2->setPosition(Vec2(0,20));
	myTerrain->addChild(simpleArrowTowerlvl2);
	this->removeTower();
}

void SimpleArrowTowerlvl1::showUpdateMenu()
{
	auto updatePanleLayer = UpdatePanleLayer::create();
	updatePanleLayer->setTag(myTerrain->getTag()+100);
	updatePanleLayer->setTower(this);
	updatePanleLayer->setPosition(this->getParent()->getPosition());
	static_cast<BaseMap*>(this->getParent()->getParent())->mTouchLayer->addChild(updatePanleLayer);
	if(GameManager::getInstance()->LEVEL ==0){
		updatePanleLayer->couldUpdate = false;
	}
	updatePanleLayer->inAnimation();
	isUpdateMenuShown = true;
}

Bullet* SimpleArrowTowerlvl1::ArrowTowerBullet()
{
	auto bullet = Arrow::create();
	bullet->setRotation(90.0f);
	bullet->setMaxForce(getForce());
	this->getParent()->addChild(bullet);
    return bullet;
}