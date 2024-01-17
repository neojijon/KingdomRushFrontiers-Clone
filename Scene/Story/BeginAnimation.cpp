#include "Scene/Story/BeginAnimation.h"
#include "Map/BaseMap.h"

USING_NS_CC;

Scene* BeginAnimation::createScene()
{
    auto scene = Scene::create();
    auto layer = BeginAnimation::create();
    scene->addChild(layer);
    return scene;
}

bool BeginAnimation::init()
{
   
    if ( !Layer::init() )
    {
        return false;
    }
	Size visibleSize = Director::getInstance() -> getVisibleSize();
	auto color = LayerColor::create(Color4B::BLACK, visibleSize.width, visibleSize.height);
    addChild(color);
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = [&](Touch* touch, Event* event){
		return true;
	};
	listener->setSwallowTouches(true);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener,color);
	startAnimation1();
     return true;
}


void BeginAnimation::startAnimation1() 
 {     
	
	 Size size = Director::getInstance()->getVisibleSize();  

     sp1 = Sprite::createWithSpriteFrameName("1_1.png");
     sp1->setPosition(Vec2(0,size.height*0.5));
     addChild(sp1,1);
     sp1->runAction(MoveTo::create(0.5f,Vec2(size.width*0.16,size.height*0.5)));
 
	 sp2 = Sprite::createWithSpriteFrameName("1_2.png");
     sp2->setPosition(Vec2(size.width*1,size.height*0.5));
     addChild(sp2,1);

	 sp2->runAction(Sequence::create(
		 Hide::create(),
		 DelayTime::create(1.0f),
		 Show::create(),
		 MoveTo::create(0.5f,Vec2(size.width*0.60,size.height*0.5)),NULL));
	 sp3 = Sprite::createWithSpriteFrameName("1_3.png");
     sp3->setPosition(Vec2(size.width*0.75,size.height*0.0));
     addChild(sp3,1);

	 sp3->runAction(Sequence::create(
		 Hide::create(),
		 DelayTime::create(1.5f),Show::create(),
		 JumpTo ::create(0.5f, Vec2(size.width*0.75,size.height*0.45), 50, 1 ),NULL));
	continue_btn = Sprite::createWithSpriteFrameName("comicContinue.png");

	continue_btn->setPosition(Vec2(-200,size.height*0.13));
	addChild(continue_btn,1);
	
	continue_btn->runAction(Sequence::create(
		 DelayTime::create(2),
		 JumpTo ::create(0.005f, Vec2(size.width*0.75,size.height*0.13), 1, 1 ),NULL));

	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = [&](Touch* touch, Event* event){
		
		auto target = static_cast<Sprite*>(event->getCurrentTarget());

		Vec2 locationInNode = target->convertTouchToNodeSpace(touch);

		Size size = target->getContentSize();
		Rect rect = Rect(0, 0, size.width, size.height);
		if (rect.containsPoint(locationInNode)&&target->isVisible())
		{  
			 sp1->removeFromParent();
			 sp2->removeFromParent();
			 sp3->removeFromParent();	
			 startAnimation2();
			return true;  
		}  
		return false;  
	};
	listener->onTouchEnded = [&](Touch* touch, Event* event){
		_eventDispatcher->removeEventListener(listener);
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener,continue_btn);
 }

void BeginAnimation::startAnimation2() 
 {     
	 continue_btn->removeFromParent();
	 Size size = Director::getInstance()->getVisibleSize();  
     auto sp11 = Sprite::createWithSpriteFrameName("1_4.png");
     sp11->setPosition(Vec2(size.width*0.33,size.height*1.0));
     addChild(sp11,2);

     sp11->runAction(MoveTo::create(0.5f,Vec2(size.width*0.33,size.height*0.5)));

	 auto sp22 = Sprite::createWithSpriteFrameName("1_5.png");
     sp22->setPosition(Vec2(size.width*1,size.height*0.5));
     addChild(sp22,2);
	 
	 sp22->runAction(Sequence::create(
		 Hide::create(),
		 DelayTime::create(1.0f),
		 Show::create(),
		 MoveTo::create(0.5f,Vec2(size.width*0.75,size.height*0.5)),NULL));
	 
    auto sp4 = Sprite::createWithSpriteFrameName("comicContinue.png");
	sp4->setPosition(Vec2(size.width*0.80,-300));
	this->addChild(sp4,2);
	 
	sp4->runAction(Sequence::create(
		DelayTime::create(1.5),
		JumpTo ::create(0.005f, Vec2(size.width*0.80,size.height*0.15), 1, 1 ),NULL));

	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = [&](Touch* touch, Event* event){
		
		auto target = static_cast<Sprite*>(event->getCurrentTarget());

		Vec2 locationInNode = target->convertTouchToNodeSpace(touch);

		Size size = target->getContentSize();
		Rect rect = Rect(0, 0, size.width, size.height);
		if (rect.containsPoint(locationInNode))
		{  
			backToGame();
			return true;  
		}  
		return false;  
	};
	listener->onTouchEnded = [&](Touch* touch, Event* event){
		_eventDispatcher->removeEventListener(listener);
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener,sp4);
  }

void BeginAnimation::backToGame() 
{
	game->startAfterStory();
	this->removeFromParent();
}