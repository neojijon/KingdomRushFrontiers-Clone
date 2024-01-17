#include "SimpleArtilleryTowerlvl1.h"
#include "SimpleArtilleryTowerlvl2.h"
#include "Layer/Menu/UpdatePanleLayer.h"
#include "Data/GameManager.h"
#include "Map/BaseMap.h"

bool SimpleArtilleryTowerlvl1::init()
{
	if (!Sprite::init())
	{
		return false;
	}
	setTowerType(ARTILLERY_1);
	setLevel(1);
	addTerrain();
	buildingAnimation();
	
	setScope(160.0f);
	setUpdateMoney(150);
	setBuildMoney(120);
	isUpdateMenuShown = false;
	return true;
}

void SimpleArtilleryTowerlvl1::buildingAnimation()
{
	auto building = Sprite::create();
	auto constructing = Sprite::createWithSpriteFrameName("tower_constructing_0001.png");
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
	scheduleOnce(CC_SCHEDULE_SELECTOR(SimpleArtilleryTowerlvl1::buildingSmokeAnimation),0.5f);

	// scheduleOnce를 사용하여 0.5초 후에 buildingSmokeAnimation 함수 호출
	/*this->scheduleOnce([this](float dt) {
		this->buildingSmokeAnimation(dt);
		}, 0.5f, "buildingSmokeAnimationKey");*/
}

void SimpleArtilleryTowerlvl1::buildingSmokeAnimation(float dt)
{
	auto smoke = Sprite::createWithSpriteFrameName("effect_buildSmoke_0001.png");
	addChild(smoke,99);
	smoke->runAction(Sequence::create(
		Animate::create(AnimationCache::getInstance()->getAnimation("build_smoke")),
		CallFuncN::create(CC_CALLBACK_0(Sprite::removeFromParent, smoke)),NULL));
	SoundManager::playArtilleryReady();
	initTower(1);
	setListener();

	schedule(CC_SCHEDULE_SELECTOR(SimpleArtilleryTowerlvl1::shoot), 3.0f);
	/*this->schedule([this](float dt) {
		this->shoot(dt);
		}, 3.0f, "shoot");*/

}

void SimpleArtilleryTowerlvl1::updateTower()
{
	auto simpleArtilleryTowerlvl2 = SimpleArtilleryTowerlvl2::create();
	simpleArtilleryTowerlvl2->setMyTerrain(myTerrain);
	simpleArtilleryTowerlvl2->setTag(myTerrain->getTag());
	simpleArtilleryTowerlvl2->setPosition(Vec2(0,20));
	myTerrain->addChild(simpleArtilleryTowerlvl2);
	this->removeTower();
}

void SimpleArtilleryTowerlvl1::showUpdateMenu()
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