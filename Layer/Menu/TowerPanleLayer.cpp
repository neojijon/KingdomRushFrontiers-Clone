#include "TowerPanleLayer.h"
#include "Data/GameManager.h"
#include "Map/BaseMap.h"
#include "Tower/BaseBarracksTower.h"
#include "Tower/SimpleArrowTowerlvl1.h"
#include "Tower/SimpleArtilleryTowerlvl1.h"
#include "Tower/SimpleMageTowerlvl1.h"

USING_NS_CC;

bool TowerPanleLayer::init()
{
    if ( !Sprite::init() )
    {
        return false;
    }
	circle = Circle::create();
	addChild(circle);
	circle->setVisible(false);

	planesprite = Sprite::createWithSpriteFrameName("gui_ring.png");
	planesprite->setPosition(Vec2(0, 0));
	planesprite->setScale(0.5f);
	addChild(planesprite);

	isBuilt = false;
	return true;
}

void TowerPanleLayer::addTower(int type)
{
	static_cast<BaseMap*>(this->getParent()->getParent())->playerState->removeTowerInfo();
	switch (type)
	{
	case(2):{
		auto barracksTower = BaseBarracksTower::create();
		barracksTower->setPosition(Vec2(0,20));
		barracksTower->setTag(terrain->getTag());
		barracksTower->setMyTerrain(terrain);
		terrain->addChild(barracksTower);
		barracksTower->buildingAnimation();
		GameManager::getInstance()->MONEY = GameManager::getInstance()->MONEY - barracksTower->getBuildMoney();
		}
		break;
	case(1):{
		auto arrowTower = SimpleArrowTowerlvl1::create();
		arrowTower->setPosition(Vec2(0,20));
		arrowTower->setTag(terrain->getTag());
		arrowTower->setMyTerrain(terrain);
		terrain->addChild(arrowTower);
		GameManager::getInstance()->MONEY = GameManager::getInstance()->MONEY - arrowTower->getBuildMoney();
		}
		break;
	case(4):{
		auto artilleryTower = SimpleArtilleryTowerlvl1::create();
		artilleryTower->setPosition(Vec2(0,20));
		artilleryTower->setTag(terrain->getTag());
		artilleryTower->setMyTerrain(terrain);
		terrain->addChild(artilleryTower);
		GameManager::getInstance()->MONEY = GameManager::getInstance()->MONEY - artilleryTower->getBuildMoney();
		}
		break;
	case(3):
		auto mageTower = SimpleMageTowerlvl1::create();
		mageTower->setPosition(Vec2(0,20));
		mageTower->setTag(terrain->getTag());
		mageTower->setMyTerrain(terrain);
		terrain->addChild(mageTower);
		GameManager::getInstance()->MONEY = GameManager::getInstance()->MONEY - mageTower->getBuildMoney();
		break;
	}
	SoundManager::playTowerBuilding();
	isBuilt = true;
	terrain->terrain->setVisible(false);
	this->setVisible(false);
}

void TowerPanleLayer::inAnimation()
{
	SoundManager::playTowerMenu();
	planesprite->runAction(Sequence::create(ScaleTo::create(0.1f,1.0f,1.0f),
		CallFuncN::create(CC_CALLBACK_0(TowerPanleLayer::addIcons,this)),
		NULL));	
}

void TowerPanleLayer::addTempTower(int type)
{
	if(tempTower!=NULL){
		removeChild(tempTower,true);
	}
	circle->setVisible(true);
	switch (type)
	{
	case(1):{
		tempTower = Sprite::createWithSpriteFrameName("tower_preview_archer.png");
		tempTower->setPosition(Vec2(0,25));
		static_cast<BaseMap*>(this->getParent()->getParent())->playerState->showTowerInfo(ARCHER_1);}
		break;
	case(2):{
		tempTower = Sprite::createWithSpriteFrameName("tower_preview_barrack.png");
		tempTower->setPosition(Vec2(0,25));
		static_cast<BaseMap*>(this->getParent()->getParent())->playerState->showTowerInfo(BARAACKS_1);}
		break;
	case(3):{
		tempTower = Sprite::createWithSpriteFrameName("tower_preview_mage.png");
		tempTower->setPosition(Vec2(0,10));
		static_cast<BaseMap*>(this->getParent()->getParent())->playerState->showTowerInfo(MAGE_1);}
		break;
	case(4):{
		tempTower = Sprite::createWithSpriteFrameName("tower_preview_artillery.png");
		tempTower->setPosition(Vec2(0,25));
		static_cast<BaseMap*>(this->getParent()->getParent())->playerState->showTowerInfo(ARTILLERY_1);}
		break;
	}
	addChild(tempTower);
}

void TowerPanleLayer::addIcons()
{	
	archerIcon = BaseBuildIcon::createIcon(1,70);
	archerIcon->setMoney(70);
	archerIcon->setPosition(Vec2(-(planesprite->getContentSize().width/4+20),planesprite->getContentSize().height/4+30));
	addChild(archerIcon);

	artilleryIcon = BaseBuildIcon::createIcon(4,120);
	artilleryIcon->setPosition(Vec2(planesprite->getContentSize().width/4+20,-(planesprite->getContentSize().height/4+30)));
	addChild(artilleryIcon);

	barracksIcon = BaseBuildIcon::createIcon(2,100);
	barracksIcon->setPosition(Vec2(planesprite->getContentSize().width/4+20,planesprite->getContentSize().height/4+30));
	addChild(barracksIcon);

	magicIcon = BaseBuildIcon::createIcon(3,100);
	magicIcon->setPosition(Vec2(-(planesprite->getContentSize().width/4+20),-(planesprite->getContentSize().height/4+30)));
	addChild(magicIcon);

	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->setSwallowTouches(true);
	touchListener->onTouchBegan = CC_CALLBACK_2(TowerPanleLayer::onTouchBegan, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(TowerPanleLayer::onTouchEnded, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, archerIcon);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener->clone(), artilleryIcon);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener->clone(), barracksIcon);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener->clone(), magicIcon);
}

bool TowerPanleLayer::onTouchBegan(Touch *touch, Event *event)
{
	auto target = static_cast<BaseBuildIcon*>(event->getCurrentTarget());
    Vec2 locationInNode = target->convertTouchToNodeSpace(touch);
    Size size = target->baseIcon->getContentSize();
	Rect rect = Rect(0-size.width/2, 0-size.height/2, size.width, size.height);
    if (rect.containsPoint(locationInNode))
    {
		if(target->getIsSelected())//����Ѿ�ѡ�У��ڶ��ΰ��£�
		{
			if(target->getIsAble())//���Ǯ����
			{
				int i = target->getType();
				addTower(target->getType());
			}
		}else{//��һ�ΰ���
			archerIcon->setNotSelected();
			artilleryIcon->setNotSelected();
			barracksIcon->setNotSelected();
			magicIcon->setNotSelected();

			target->setSelected();//����Ϊѡ��״̬
			addTempTower(target->getType());
		}
        return true;
    }
    return false;
}

void TowerPanleLayer::onTouchEnded(Touch* touch, Event* event)
{
	if(isBuilt)
	{
		removeFromParent();
	}
}