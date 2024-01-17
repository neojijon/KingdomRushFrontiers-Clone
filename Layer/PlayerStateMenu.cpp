#include "PlayerStateMenu.h"
#include "GameOption.h"
#include "Data/GameManager.h"
#include "Data/SoundManager.h"
#include "Sprite/TowerInfoLayer.h"
#include "Sprite/MonsterInfoLayer.h"

bool PlayerStateMenu::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
	isFrozen = false;
	instance = GameManager::getInstance();
	stateSprite = Sprite::createWithSpriteFrameName("hud_background.png");
	stateSprite->setAnchorPoint(Vec2(0,1));
	stateSprite->setPosition(Vec2(20,Director::getInstance()->getWinSize().height - 20 + 100));
	addChild(stateSprite);
	
	lifeLabel = Label::createWithTTF("0","arial.ttf",20);
	lifeLabel->setPosition(Vec2(stateSprite->getContentSize().width/4,stateSprite->getContentSize().height/4*3));
	stateSprite->addChild(lifeLabel);

	goldLabel = Label::createWithTTF("0","arial.ttf",20);
	goldLabel->setPosition(Vec2(stateSprite->getContentSize().width/4*3,stateSprite->getContentSize().height/4*3));
	stateSprite->addChild(goldLabel);

	waveLabel = Label::createWithTTF("","arial.ttf",20);
	waveLabel->setPosition(Vec2(stateSprite->getContentSize().width/2,stateSprite->getContentSize().height/4));
	stateSprite->addChild(waveLabel);

	pause = Sprite::createWithSpriteFrameName("hud_buttons_0001.png");
	pause->setAnchorPoint(Vec2(1,1));
	pause->setPosition(Vec2(Director::getInstance()->getWinSize().width - 20,Director::getInstance()->getWinSize().height - 20 + 100));
	addChild(pause);

	thunderStoneSprite = Sprite::createWithSpriteFrameName("power_portrait_fireball_0001.png");
	thunderStoneSprite->setAnchorPoint(Vec2(0,0));
	thunderStoneSprite->setPosition(Vec2(10,-20));
	thunderStoneSprite->setName("inactive");
	completeThunder = false;
	addChild(thunderStoneSprite,1);

	paratrooperSprite = Sprite::createWithSpriteFrameName("power_portrait_reinforcement_0001.png");
	paratrooperSprite->setAnchorPoint(Vec2(0,0));
	paratrooperSprite->setPosition(Vec2(120,-20));
	paratrooperSprite->setName("inactive");
	completeParatrooper = false;
	addChild(paratrooperSprite,1);

	packSprite = Sprite::createWithSpriteFrameName("power_portrait_backpack_0001.png");
	packSprite->setAnchorPoint(Vec2(1,0));
	packSprite->setPosition(Vec2(Director::getInstance()->getWinSize().width - 10,-20));
	packSprite->setName("inactive");
	addChild(packSprite,1);
	backPackSprite = Sprite::createWithSpriteFrameName("backPack_hover.png");
	backPackSprite->setAnchorPoint(Vec2(1,0));
	backPackSprite->setPosition(Vec2(Director::getInstance()->getWinSize().width - 60,30));
	backPackSprite->setVisible(false);
	addChild(backPackSprite,-1);
	auto backPackSpritelistener = EventListenerTouchOneByOne::create();

	backPackSpritelistener->onTouchBegan = [&](Touch* touch, Event* event){
		auto target = static_cast<Sprite*>(event->getCurrentTarget());

		Vec2 locationInNode = target->convertTouchToNodeSpace(touch);

		Size size = target->getContentSize();
		Rect rect = Rect(0, 0, size.width, size.height);
		if (rect.containsPoint(locationInNode) && backPackSprite->isVisible() )
		{  
			
			return true;  
		}  
		return false;  
	};
	backPackSpritelistener->setSwallowTouches(true);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(backPackSpritelistener,backPackSprite);
	for(int i = 0; i < 6 ; i ++){
		int num = UserDefault::getInstance()->getIntegerForKey(cocos2d::StringUtils::format(instance->SLOTX_SHOP,i).data());
		if(num > 0){
			stringForSkillFileName = cocos2d::StringUtils::format("backPack_icons_000%d.png",i+1);
		}else{
			stringForSkillFileName = cocos2d::StringUtils::format("backPack_icons_off_000%d.png",i+1);
		}
		backPack_icons_Sprite[i] = Sprite::createWithSpriteFrameName(stringForSkillFileName);
		backPack_icons_Sprite[i]->setAnchorPoint(Vec2(1,0));
		backPack_icons_Sprite[i]->setPosition(Vec2(540 - 85 * i,-20));

		backPack_icons_Sprite[i]->setTag(i);
		backPack_icons_Sprite[i]->setName(cocos2d::StringUtils::format(instance->SLOTX_SHOP,i));
		backPackSprite->addChild(backPack_icons_Sprite[i],0);

		auto numLeft = Label::createWithTTF(cocos2d::StringUtils::format("%d",num),"arial.ttf",20);
		numLeft->setPosition(Vec2(backPack_icons_Sprite[i]->getContentSize().width/4*3,backPack_icons_Sprite[i]->getContentSize().height/4));
		numLeft->setTag(101);
		backPack_icons_Sprite[i]->addChild(numLeft);
	}

	stoneTimer = ProgressTimer::create(Sprite::createWithSpriteFrameName("power_loading.png"));
	stoneTimer->setAnchorPoint(Vec2(0,0));
	stoneTimer->setReverseDirection(true);
	stoneTimer->setPosition(Vec2(10,-20));
	stoneTimer->setPercentage(100);
	this->addChild(stoneTimer,1,100);
	

	paratrooperTimer = ProgressTimer::create(Sprite::createWithSpriteFrameName("power_loading.png"));
	paratrooperTimer->setReverseDirection(true);
	paratrooperTimer->setAnchorPoint(Vec2(0,0));
	paratrooperTimer->setPosition(Vec2(120,-20));
	paratrooperTimer->setPercentage(100);
	this->addChild(paratrooperTimer,1,200);

	auto pause_listener = EventListenerTouchOneByOne::create();
	pause_listener->onTouchBegan = [&](Touch* touch, Event* event){
		
		auto target = static_cast<Sprite*>(event->getCurrentTarget());

		Vec2 locationInNode = target->convertTouchToNodeSpace(touch);

		Size size = target->getContentSize();
		Rect rect = Rect(0, 0, size.width, size.height);
		if (rect.containsPoint(locationInNode))
		{  
			SoundManager::playClickEffect();
			return true;  
		}  
		return false;  
	};
	pause_listener->onTouchEnded = [&](Touch* touch, Event* event){
		if(packSprite->getName() == "active"){
			packSprite->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("power_portrait_backpack_0001.png"));
			packSprite->setName("inactive");
			backPackSprite->setVisible(false);
		}
		removeTowerInfo();
		removeMonsterInfo();
		addGameOption();
	};
	pause_listener->setSwallowTouches(true);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(pause_listener,pause);

	auto stoneListener = EventListenerTouchOneByOne::create();
	stoneListener->onTouchBegan = [&](Touch* touch, Event* event){
		
		auto target = static_cast<Sprite*>(event->getCurrentTarget());
		Vec2 locationInNode = target->convertTouchToNodeSpace(touch);
		Size size = target->getContentSize();
		Rect rect = Rect(0, 0, size.width, size.height);
		if(rect.containsPoint(locationInNode)){
			if(completeThunder == true){
				mTouchLayer->removeAllListener();
				if(thunderStoneSprite->getName() == "inactive"){
					thunderStoneSprite->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("power_portrait_fireball_0002.png"));
					thunderStoneSprite->setName("active");
					paratrooperSprite->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("power_portrait_reinforcement_0001.png"));
					paratrooperSprite->setName("inactive");
					packSprite->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("power_portrait_backpack_0001.png"));
					packSprite->setName("inactive");
					backPackSprite->setVisible(false);
					mTouchLayer->setFireBallTouchShield();
				}else{
					thunderStoneSprite->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("power_portrait_fireball_0001.png"));
					thunderStoneSprite->setName("inactive");
				}
			}
			return true;
		}
		return false;  
	};

	stoneListener->onTouchEnded = [&](Touch* touch, Event* event){
	};
	stoneListener->setSwallowTouches(true);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(stoneListener,thunderStoneSprite);
	auto paratrooperListener = EventListenerTouchOneByOne::create();
	paratrooperListener->onTouchBegan = [&](Touch* touch, Event* event){

		auto target = static_cast<Sprite*>(event->getCurrentTarget());
		Vec2 locationInNode = target->convertTouchToNodeSpace(touch);
		Size size = target->getContentSize();
		Rect rect = Rect(0, 0, size.width, size.height);
		
		if(rect.containsPoint(locationInNode)){
			if(completeParatrooper == true){
				mTouchLayer->removeAllListener();
				if(paratrooperSprite->getName() == "inactive"){
					paratrooperSprite->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("power_portrait_reinforcement_0002.png"));
					paratrooperSprite->setName("active");
					thunderStoneSprite->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("power_portrait_fireball_0001.png"));
					thunderStoneSprite->setName("inactive");
					packSprite->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("power_portrait_backpack_0001.png"));
					packSprite->setName("inactive");
					backPackSprite->setVisible(false);
					mTouchLayer->setSoldierTouchShield();
				}else{
					paratrooperSprite->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("power_portrait_reinforcement_0001.png"));
					paratrooperSprite->setName("inactive");
				}
			}
			return true;
		}
		return false;
	};
	paratrooperListener->onTouchEnded = [&](Touch* touch, Event* event){

	};
	paratrooperListener->setSwallowTouches(true);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(paratrooperListener,paratrooperSprite);
	auto packListener = EventListenerTouchOneByOne::create();
	packListener->onTouchBegan = [&](Touch* touch, Event* event){

		auto target = static_cast<Sprite*>(event->getCurrentTarget());
		Vec2 locationInNode = target->convertTouchToNodeSpace(touch);
		Size size = target->getContentSize();
		Rect rect = Rect(0, 0, size.width, size.height);
		if (rect.containsPoint(locationInNode) && packSprite->getName() == "inactive"){  
			removeTowerInfo();
			removeMonsterInfo();
			mTouchLayer->removeAllListener();
			packSprite->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("power_portrait_backpack_0002.png"));
			packSprite->setName("active");
			backPackSprite->setVisible(true);
			if(thunderStoneSprite->getName() == "active" || paratrooperSprite->getName() == "active"){
				thunderStoneSprite->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("power_portrait_fireball_0001.png"));
				thunderStoneSprite->setName("inactive");
				paratrooperSprite->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("power_portrait_reinforcement_0001.png"));
				paratrooperSprite->setName("inactive");
			}
			return true;  
		}
		if(rect.containsPoint(locationInNode) && packSprite->getName() == "active"){
			packSprite->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("power_portrait_backpack_0001.png"));
			packSprite->setName("inactive");
			backPackSprite->setVisible(false);
		}
		return false;  
	};
	packListener->setSwallowTouches(true);
	paratrooperListener->onTouchEnded = [&](Touch* touch, Event* event){
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(packListener,packSprite);

	auto skillListener = EventListenerTouchOneByOne::create();
	skillListener->onTouchBegan = [&](Touch* touch, Event* event){
		
		auto target = static_cast<Sprite*>(event->getCurrentTarget());
		Vec2 locationInNode = target->convertTouchToNodeSpace(touch);
		Size size = target->getContentSize();
		Rect rect = Rect(0, 0, size.width, size.height);
		if (rect.containsPoint(locationInNode) && backPackSprite->isVisible()){  
			
			int num = UserDefault::getInstance()->getIntegerForKey(target->getName().c_str());
			if(num <= 0){
				UserDefault::getInstance()->setIntegerForKey(target->getName().c_str(),0);
				target->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(cocos2d::StringUtils::format( "backPack_icons_off_00%02d.png",target->getTag()+1)));
				static_cast<Label*>(target->getChildByTag(101))->setString("0");
				packSprite->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("power_portrait_backpack_0001.png"));
				packSprite->setName("inactive");
				backPackSprite->setVisible(false);
			}else{
				num--;
				static_cast<Label*>(target->getChildByTag(101))->setString(cocos2d::StringUtils::format("%d",num));
				UserDefault::getInstance()->setIntegerForKey(target->getName().c_str(),num);
				shopSkill(target->getTag());

				if(num<=0){
					target->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName((cocos2d::StringUtils::format( "backPack_icons_off_00%02d.png",target->getTag()+1))));
					target->setAnchorPoint(Vec2(1,0));
					static_cast<Label*>(target->getChildByTag(101))->setString("0");
				}
				packSprite->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("power_portrait_backpack_0001.png"));
				packSprite->setName("inactive");
				backPackSprite->setVisible(false);
			}
			return true;  
		}
		return false;  
	};

	skillListener->onTouchEnded = [&](Touch* touch, Event* event){
	};
	
	skillListener->setSwallowTouches(true);
	
	for(int i = 0; i < 6; i++){
		_eventDispatcher->addEventListenerWithSceneGraphPriority(skillListener->clone(),backPack_icons_Sprite[i]);
	}	
	
	return true;
}

void PlayerStateMenu::initGameOption()
{
	gameOption = GameOption::create();
	gameOption->level = getLevel();
	gameOption->difficult = getDifficult();
	gameOption->setPosition(Vec2(0,
		Director::getInstance() -> getVisibleSize().height));
	addChild(gameOption,99);
}

void PlayerStateMenu::addGameOption()
{
	auto color = LayerColor::create(Color4B(0, 0, 0, 60), Director::getInstance() -> getVisibleSize().width, Director::getInstance() -> getVisibleSize().height);
	color->setTag(501);
	addChild(color);
	auto gameOptionListener = EventListenerTouchOneByOne::create();
	gameOptionListener->onTouchBegan = [&](Touch* touch, Event* event){
		return true;
	};
	gameOptionListener->setSwallowTouches(true);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(gameOptionListener,color);
	gameOption->runAction(
		Sequence::create(MoveBy::create(0.2f,Vec2(0,-Director::getInstance() -> getVisibleSize().height)),
		CallFuncN::create(CC_CALLBACK_0(PlayerStateMenu::pauseGame, this)),NULL));
}

void PlayerStateMenu::removeGameOption()
{
	Director::getInstance()->resume();
	gameOption->runAction(MoveBy::create(0.2f,Vec2(0,Director::getInstance() -> getVisibleSize().height)));
	removeChildByTag(501);
}

void PlayerStateMenu::pauseGame()
{
	Director::getInstance()->pause();
}

void PlayerStateMenu::startProgressTimers()
{
	this->schedule(CC_SCHEDULE_SELECTOR(PlayerStateMenu::updateStoneProgress));
	this->schedule(CC_SCHEDULE_SELECTOR(PlayerStateMenu::updateParatrooperProgress));
}

void PlayerStateMenu::startStone()
{
	completeThunder = false;
	thunderStoneSprite->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("power_portrait_fireball_0001.png"));
	thunderStoneSprite->setName("inactive");
	stoneTimer->setPercentage(100.0f);
	this->unschedule(CC_SCHEDULE_SELECTOR(PlayerStateMenu::updateStoneProgress));
	this->schedule(CC_SCHEDULE_SELECTOR(PlayerStateMenu::updateStoneProgress));
}

void PlayerStateMenu::showTowerInfo(TowerType towerType)
{
	removeChildByTag(MONSTER_INFO);
	removeChildByTag(TOWER_INFO);
	packSprite->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("power_portrait_backpack_0001.png"));
	packSprite->setName("inactive");
	backPackSprite->setVisible(false);
	auto towerInfoLayer = TowerInfoLayer::createTowerInfoLayer(towerType);
	towerInfoLayer->setTag(TOWER_INFO);
	addChild(towerInfoLayer);
	towerInfoLayer->setAnchorPoint(Vec2(0,0));
	towerInfoLayer->setPosition(Vec2(620,-50));
	towerInfoLayer->runAction(MoveBy::create(0.2f,Vec2(0,100)));
}

void PlayerStateMenu::removeTowerInfo()
{
	removeChildByTag(TOWER_INFO);
}

void PlayerStateMenu::showMonsterInfo(BaseMonster* monster)
{
	removeChildByTag(TOWER_INFO);
	removeChildByTag(MONSTER_INFO);
	packSprite->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("power_portrait_backpack_0001.png"));
	packSprite->setName("inactive");
	backPackSprite->setVisible(false);
	auto monsterInfoLayer = MonsterInfoLayer::createMonsterInfoLayer(monster);
	monsterInfoLayer->setTag(MONSTER_INFO);
	addChild(monsterInfoLayer);
	monsterInfoLayer->setAnchorPoint(Vec2(0,0));
	monsterInfoLayer->setPosition(Vec2(620,-50));
	monsterInfoLayer->runAction(MoveBy::create(0.2f,Vec2(0,100)));
}

void PlayerStateMenu::removeMonsterInfo()
{
	removeChildByTag(MONSTER_INFO);
}

void PlayerStateMenu::startParatrooper()
{
	completeParatrooper = false;
	paratrooperSprite->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("power_portrait_reinforcement_0001.png"));
	paratrooperSprite->setName("inactive");
	paratrooperTimer->setPercentage(100.0f);
	this->unschedule(CC_SCHEDULE_SELECTOR(PlayerStateMenu::updateParatrooperProgress));
	this->schedule(CC_SCHEDULE_SELECTOR(PlayerStateMenu::updateParatrooperProgress));
}

void PlayerStateMenu::setLife(int life)
{
	lifeLabel->setString(cocos2d::StringUtils::format("%d",life));
}

void PlayerStateMenu::setGold(int gold)
{
	goldLabel->setString(cocos2d::StringUtils::format("%d",gold));
}

void PlayerStateMenu::setWave(int thisWave,int totalWave)
{
	waveLabel->setString(cocos2d::StringUtils::format("WAVE %d/%d",thisWave,totalWave));
}

void PlayerStateMenu::onEnterTransitionDidFinish()
{
	stateSprite->runAction(MoveBy::create(0.2f,Vec2(0,-100)));
	pause->runAction(MoveBy::create(0.2f,Vec2(0,-100)));

}

void PlayerStateMenu::updateStoneProgress(float Dt){  
	stoneTimer->setPercentage(stoneTimer->getPercentage() - Dt*2);
	if (stoneTimer->getPercentage()==0) {
		this->unschedule(CC_SCHEDULE_SELECTOR(PlayerStateMenu::updateStoneProgress));
		completeThunder = true;
	}
	return;
}
void PlayerStateMenu::updateParatrooperProgress(float Dt){ 
	paratrooperTimer->setPercentage(paratrooperTimer->getPercentage() - Dt*5);
	if (paratrooperTimer->getPercentage()==0) {
		this->unschedule(CC_SCHEDULE_SELECTOR(PlayerStateMenu::updateParatrooperProgress));
		completeParatrooper = true;
	}
	return;
}

void PlayerStateMenu::clearMonsters()
{
	auto monstersVector = GameManager::getInstance()->monsterVector;

	for(int i = 0;i<monstersVector.size();i++){
		auto monster = monstersVector.at(i);
		if(monster!=NULL){
			monster->explosion();
		}
	}
}

void PlayerStateMenu::shopSkill(int type)
{
	switch(type){
	case(0):{
		auto atomicBomb_plane = Sprite::createWithSpriteFrameName("atomicBomb_plane.png");
		atomicBomb_plane->setPosition(Vec2(0,Director::getInstance()->getWinSize().height/3*2));
		addChild(atomicBomb_plane);
		atomicBomb_plane->runAction(Sequence::create(
			MoveBy::create(2.0f,Vec2(Director::getInstance()->getWinSize().width,0)),
			CallFuncN::create(CC_CALLBACK_0(Sprite::removeFromParent, atomicBomb_plane))
			,NULL));
		auto atomicBomb_bomb = Sprite::createWithSpriteFrameName("atomicBomb_bomb.png");
		atomicBomb_bomb->setPosition(Vec2(Director::getInstance()->getWinSize().width/2,Director::getInstance()->getWinSize().height/3*2-30));
		addChild(atomicBomb_bomb);
		atomicBomb_bomb->setVisible(false);
		atomicBomb_bomb->runAction(Sequence::create(
			DelayTime::create(1.0f),
			CallFuncN::create(CC_CALLBACK_0(Sprite::setVisible, atomicBomb_bomb,true)),
			MoveBy::create(0.5f,Vec2(0,-300)),
			CallFuncN::create(CC_CALLBACK_0(Sprite::removeFromParent, atomicBomb_bomb)),
			CallFuncN::create(CC_CALLBACK_0(PlayerStateMenu::clearMonsters, this)),NULL));
		}
		break;
	case(1):
		frozenMonsters();	
		break;
	case(2):
		mTouchLayer->removeAllListener();
		mTouchLayer->setDynamiteTouchShield();
		break;
	case(3):
		mTouchLayer->removeAllListener();
		mTouchLayer->setFreezeTouchShield();
		break;
	case(4):
		SoundManager::playCash();
		GameManager::getInstance()->LIFE = GameManager::getInstance()->LIFE + 5;
		break;
	case(5):
		SoundManager::playHearts();
		GameManager::getInstance()->MONEY = GameManager::getInstance()->MONEY + 500;
		break;
	}
}

void PlayerStateMenu::reFrozenMonsters(float dt)
{
	removeChildByTag(301);
	removeChildByTag(302);
	removeChildByTag(303);
	removeChildByTag(304);
	isFrozen = false;
}

void PlayerStateMenu::frozenMonsters()
{
	if(!isFrozen){
		auto winSize = Director::getInstance()->getWinSize();
		auto ice_corner_1 = Sprite::createWithSpriteFrameName("freeze_gfx_corner.png");
		ice_corner_1->setAnchorPoint(Vec2(1,1));
		ice_corner_1->setPosition(Vec2(winSize.width,winSize.height));
		auto ice_corner_2 = Sprite::createWithSpriteFrameName("freeze_gfx_corner.png");
		ice_corner_2->setFlippedY(true);
		ice_corner_2->setAnchorPoint(Vec2(1,0));
		ice_corner_2->setPosition(Vec2(winSize.width,0));
		auto ice_corner_3 = Sprite::createWithSpriteFrameName("freeze_gfx_corner.png");
		ice_corner_3->setFlippedX(true);
		ice_corner_3->setFlippedY(true);
		ice_corner_3->setAnchorPoint(Vec2(0,0));
		ice_corner_3->setPosition(Vec2(0,0));
		auto ice_corner_4 = Sprite::createWithSpriteFrameName("freeze_gfx_corner.png");
		ice_corner_4->setFlippedX(true);
		ice_corner_4->setAnchorPoint(Vec2(0,1));
		ice_corner_4->setPosition(Vec2(0,winSize.height));

		ice_corner_1->setTag(301);
		ice_corner_2->setTag(302);
		ice_corner_3->setTag(303);
		ice_corner_4->setTag(304);
		addChild(ice_corner_1);
		addChild(ice_corner_2);
		addChild(ice_corner_3);
		addChild(ice_corner_4);
		isFrozen = true;
		auto monstersVector = GameManager::getInstance()->monsterVector;

		for(int i = 0;i<monstersVector.size();i++){
			auto monster = monstersVector.at(i);
			if(monster!=NULL)
				monster->frozen();
		}
		scheduleOnce(CC_SCHEDULE_SELECTOR(PlayerStateMenu::reFrozenMonsters),8.0f);
	}else{
		unschedule(CC_SCHEDULE_SELECTOR(PlayerStateMenu::reFrozenMonsters));
		removeChildByTag(301);
		removeChildByTag(302);
		removeChildByTag(303);
		removeChildByTag(304);
		isFrozen = false;
		frozenMonsters();
	}
}