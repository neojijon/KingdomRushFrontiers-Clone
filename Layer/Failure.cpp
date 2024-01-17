#include "Failure.h"
#include "Scene/TransitionGame.h"
#include "Scene/GameView.h"
#include "Scene/GameScene.h"
#include "Data/SoundManager.h"

USING_NS_CC;

void ::Failure::initOption()
{
	option = Sprite::create();
	auto chain_left = Sprite::createWithSpriteFrameName("options_chain.png");
	chain_left->setAnchorPoint(Vec2(1,0));
	chain_left->setPosition(Vec2(-190,200));
	option->addChild(chain_left);

	auto chain_right = Sprite::createWithSpriteFrameName("options_chain.png");
	chain_right->setAnchorPoint(Vec2(0,0));
	chain_right->setPosition(Vec2(190,200));
	option->addChild(chain_right);
	for(int j =-40;j<=40;j++)
	{
		auto mid_center = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()
			->getSpriteFrameByName("options_tileMid_center.png"));
		mid_center->setPosition(Vec2(8.5*j,-56));
		option->addChild(mid_center);
	}
	for(int j =-40;j<=40;j++)
	{
		auto mid_center = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()
			->getSpriteFrameByName("options_tileMid_center.png"));
		mid_center->setPosition(Vec2(8.5*j,+56));
		option->addChild(mid_center);
	}
	for(int j =-7;j<=7;j++)
	{
		auto top_center = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()
			->getSpriteFrameByName("options_tileTop_center.png"));
		top_center->setPosition(Vec2(32*j,+161));
		option->addChild(top_center);
	}

	for(int j =-7;j<=7;j++)
	{
		auto top_center = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()
			->getSpriteFrameByName("options_tileTop_center.png"));
		top_center->setPosition(Vec2(32*j,-161));
		top_center->setFlippedY(true);
		option->addChild(top_center);
	}
	auto mid_left1 = Sprite::createWithSpriteFrameName("options_tileMid_left.png");
	mid_left1->setPosition(Vec2(-369,-56));
	option->addChild(mid_left1);
	auto mid_left2 = Sprite::createWithSpriteFrameName("options_tileMid_left.png");
	mid_left2->setPosition(Vec2(-369,56));
	option->addChild(mid_left2);
	auto mid_right1 = Sprite::createWithSpriteFrameName("options_tileMid_right.png"); 
	mid_right1->setPosition(Vec2(369,-56));
	option->addChild(mid_right1);
	auto mid_right2 = Sprite::createWithSpriteFrameName("options_tileMid_right.png"); 
	mid_right2->setPosition(Vec2(369,56));
	option->addChild(mid_right2);


	auto top_left1 = Sprite::createWithSpriteFrameName("options_tileTop_left.png");
	top_left1->setPosition(Vec2(-347,161));
	option->addChild(top_left1);

	auto top_left2 = Sprite::createWithSpriteFrameName("options_tileTop_left.png");
	top_left2->setFlippedY(true);
	top_left2->setPosition(Vec2(-347,-161));
	option->addChild(top_left2);

	auto top_right1 = Sprite::createWithSpriteFrameName("options_tileTop_left.png");
	top_right1->setPosition(Vec2(347,-161));
	top_right1->setFlippedX(true);
	top_right1->setFlippedY(true);
	option->addChild(top_right1);

	auto top_right2 = Sprite::createWithSpriteFrameName("options_tileTop_left.png");
	top_right2->setPosition(Vec2(347,161));
	top_right2->setFlippedX(true);
	option->addChild(top_right2);

	auto top_left_deco = Sprite::createWithSpriteFrameName("options_tileTop_deco.png");
	top_left_deco->setPosition(Vec2(220,161));
	option->addChild(top_left_deco);

	auto down_left_deco = Sprite::createWithSpriteFrameName("options_tileTop_deco.png");
	down_left_deco->setFlippedY(true);
	down_left_deco->setPosition(Vec2(220,-161));
	option->addChild(down_left_deco);

	auto top_right_deco = Sprite::createWithSpriteFrameName("options_tileTop_deco.png");
	top_right_deco->setFlippedX(true);
	top_right_deco->setPosition(Vec2(-220,161));
	option->addChild(top_right_deco);

	auto down_right_deco = Sprite::createWithSpriteFrameName("options_tileTop_deco.png");
	down_right_deco->setFlippedX(true);
	down_right_deco->setFlippedY(true);
	down_right_deco->setPosition(Vec2(-220,-161));
	option->addChild(down_right_deco);

	auto top_left_cut = Sprite::createWithSpriteFrameName("options_tileTop_cut.png");
	top_left_cut->setPosition(Vec2(-266,161));
	option->addChild(top_left_cut);

	auto down_left_cut = Sprite::createWithSpriteFrameName("options_tileTop_cut.png");
	down_left_cut->setFlippedY(true);
	down_left_cut->setPosition(Vec2(-266,-161));
	option->addChild(down_left_cut);

	auto top_right_cut = Sprite::createWithSpriteFrameName("options_tileTop_cut.png");
	top_right_cut->setFlippedX(true);
	top_right_cut->setPosition(Vec2(266,161));
	option->addChild(top_right_cut);

	auto down_right_cut = Sprite::createWithSpriteFrameName("options_tileTop_cut.png");
	down_right_cut->setFlippedX(true);
	down_right_cut->setFlippedY(true);
	down_right_cut->setPosition(Vec2(266,-161));
	option->addChild(down_right_cut);

	option->setPosition(Vec2(Director::getInstance()->getWinSize().width/2,Director::getInstance()->getWinSize().height/2+20+500));
	addChild(option);
}

bool Failure::init()
{
	if(!Layer::init()){
		return false;
	}
	initOption();
	auto size = Director::getInstance()->getVisibleSize();  
    auto color = LayerColor::create(Color4B(0, 0, 0, 60), size.width, size.height);
    addChild(color);
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = [&](Touch* touch, Event* event){
		return true;
	};
	listener->setSwallowTouches(true);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener,color);
	initOption();
	initMap();
	option->runAction(Sequence::create(
			MoveBy::create(0.2f,Vec2(0,-500))
			,CallFuncN::create(CC_CALLBACK_0(Failure::pauseGame, this))
			,NULL));
	SoundManager::playQuestFailed();
    return true;
  }
void Failure::initMap()
{
	auto size = Director::getInstance()->getVisibleSize();
	auto str ="  USE GEMS TO GET\n  SPECIAL ITEMS TO BLAST\n  YOUR EMENIES!";

	auto defeatLabel = Label::createWithTTF("DEFEAT!", "ObelixPro.ttf", 30);
    defeatLabel->setPosition(Vec2(0, 150));
	defeatLabel->setColor(Color3B(255,255,255));
    option->addChild(defeatLabel,1);

	auto items = Sprite::createWithSpriteFrameName("defeat_items.png");
    items->setPosition(Vec2(140,60));
    option->addChild(items,2);

	auto downLabel = Label::createWithTTF(str, "ObelixPro.ttf", 30);
    downLabel->setPosition(Vec2(-150,60));
	downLabel->setColor(Color3B(255,255,255));
    option->addChild(downLabel,2);


	auto restart = Sprite::createWithSpriteFrameName("options_buttons_0003.png");
	restart->setPosition(Vec2(-145,-100));
	restart->setTag(0);

	auto exit = Sprite::createWithSpriteFrameName("options_buttons_0001.png");
	exit->setPosition(Vec2(145,-100));
	exit->setTag(1);

	option->addChild(restart);
	option->addChild(exit);

	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = CC_CALLBACK_2(Failure::onTouchBegan, this);
	listener->onTouchEnded = CC_CALLBACK_2(Failure::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener,restart);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener->clone(),exit);
}

void Failure::onTouchEnded(Touch* touch, Event* event)
{
	auto target = static_cast<Sprite*>(event->getCurrentTarget());
	target->setScale(1.0f);
	switch (target->getTag())
	{
	case(0):
		Director::getInstance()->resume();
		Director::getInstance()->replaceScene(TransitionGame::create(1.0f, GameScene::playGame(level,difficulty)));
		break;
	case(1):
		Director::getInstance()->resume();
		Director::getInstance()->replaceScene(TransitionGame::create(1.0f, GameView::createScene()));
		break;
	default:
		break;
	}
}

void Failure::pauseGame()
{
	Director::getInstance()->pause();
}

bool Failure::onTouchBegan(Touch* touch, Event* event)
{
	auto target = static_cast<Sprite*>(event->getCurrentTarget());

	Vec2 locationInNode = target->convertTouchToNodeSpace(touch);

	Size size = target->getContentSize();
	Rect rect = Rect(0, 0, size.width, size.height);
	if (rect.containsPoint(locationInNode))
	{  	
		SoundManager::playClickEffect();
		target->setScale(0.9f);
		return true;  
	}  
	return false;
}