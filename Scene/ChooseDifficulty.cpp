#include "ChooseDifficulty.h"
#include "ChooseDifficulty.h"
#include "Scene/GameScene.h"
#include "Scene/TransitionGame.h"
#include "Data/GameManager.h"
#include "Data/SoundManager.h"

USING_NS_CC;


Scene* ChooseDifficulty::createSceneWithLevel(int level)
{
    auto scene = Scene::create();
    auto layer = ChooseDifficulty::create();
	layer->initWithLevel(level);
    scene->addChild(layer);
    return scene;
}

bool ChooseDifficulty::init()
{
    if ( !Layer::init() )
    {
        return false;
    }

	visibleSize = Director::getInstance()->getVisibleSize();
	difficulty = 0;

	for(int i = 0;i<4;i++){
		for(int j =0;j<5;j++){
			auto sprite = Sprite::createWithSpriteFrameName("encyclopedia_bgTile.png");
			sprite->setPosition(Vec2(i*320,j*160));
			sprite->setAnchorPoint(Vec2(0,0));
			addChild(sprite);
		}
	}
	auto bgSprite2 = Sprite::createWithSpriteFrameName("LevelSelect_Bg.png");
	bgSprite2->setPosition(Vec2(visibleSize.width*0.5,visibleSize.height*0.5));
	this->addChild(bgSprite2,1);

	auto loupeSprite = Sprite::createWithSpriteFrameName("LevelSelect_loupe.png");
	loupeSprite->setPosition(Vec2(visibleSize.width*0.21,390));
	this->addChild(loupeSprite,2);

	auto closeSprite =MenuItemSprite::create(Sprite::createWithSpriteFrameName("LevelSelect_Back_0001.png"),
	Sprite::createWithSpriteFrameName("LevelSelect_Back_0002.png"),CC_CALLBACK_1(ChooseDifficulty::menuCallback,this));  
    Menu *closeMenu = Menu::create(closeSprite,NULL);    
    closeSprite->setPosition(Vec2(visibleSize.width*0.87,580));  
	closeMenu->setPosition(Vec2::ZERO);
    this->addChild(closeMenu,2);  

	auto startModeSprite =MenuItemSprite::create(Sprite::createWithSpriteFrameName("levelSelect_startMode_0001.png"),
	Sprite::createWithSpriteFrameName("levelSelect_startMode_0002.png"),CC_CALLBACK_1(ChooseDifficulty::menuCallnext,this));  
    Menu *startModeMenu = Menu::create(startModeSprite,NULL);    
    startModeSprite->setPosition(Vec2(visibleSize.width*0.8,100));  
	startModeMenu->setPosition(Vec2::ZERO);
    this->addChild(startModeMenu,2); 

 
	 star1 = Sprite::createWithSpriteFrameName("levelSelect_badges_0002.png");
	 star1->setPosition(Vec2(210,580));
	 star1->setRotation(-30.0f);
	 addChild(star1,9);

	 star2 = Sprite::createWithSpriteFrameName("levelSelect_badges_0002.png");
	 star2->setPosition(Vec2(260,600));
	 star2->setRotation(-15.0f);
	 addChild(star2,9);

	 star3 = Sprite::createWithSpriteFrameName("levelSelect_badges_0002.png");
	 star3->setPosition(Vec2(310,605));
	 addChild(star3,9);
	 star4 = Sprite::createWithSpriteFrameName("levelSelect_badges_0004.png");
	 star4->setPosition(Vec2(360,600));
	 star4->setRotation(15.0f);
	 addChild(star4,9);

	star5 = Sprite::createWithSpriteFrameName("levelSelect_badges_0006.png");
	star5->setPosition(Vec2(410,580));
	star5->setRotation(30.0f);
	addChild(star5,9);


	

	auto imgNormal1 = MenuItemSprite::create(Sprite::createWithSpriteFrameName("levelSelect_butModes_0005.png"),Sprite::createWithSpriteFrameName("levelSelect_butModes_0001.png"));  
    auto imgSelect1 = MenuItemSprite::create(Sprite::createWithSpriteFrameName("levelSelect_butModes_0001.png"),Sprite::createWithSpriteFrameName("levelSelect_butModes_0005.png"));  


	toggleItem1 = MenuItemToggle::createWithCallback(
		                                                 CC_CALLBACK_1(ChooseDifficulty::starMenuCallback1,this), 
		                                                 imgNormal1,
														 imgSelect1,NULL); 
	
	toggleItem1->setTag(1); 
    toggleItem1->setPosition(Vec2(visibleSize.width*0.12,20)); 
    toggleItem1->setSelectedIndex(0);      
    toggleItem1->setEnabled(false);    
    auto imgNormal2 = MenuItemSprite::create(Sprite::createWithSpriteFrameName("levelSelect_butModes_0006.png"),Sprite::createWithSpriteFrameName("levelSelect_butModes_0006.png"));  
    auto imgSelect2 = MenuItemSprite::create(Sprite::createWithSpriteFrameName("levelSelect_butModes_0002.png"),Sprite::createWithSpriteFrameName("levelSelect_butModes_0002.png")); 
	auto imgDisable2 =MenuItemSprite::create(Sprite::createWithSpriteFrameName("levelSelect_butModes_0004.png"),Sprite::createWithSpriteFrameName("levelSelect_butModes_0004.png"));


	toggleItem2 = MenuItemToggle::createWithCallback(
		                                                 CC_CALLBACK_1(ChooseDifficulty::starMenuCallback2,this), 
		                                                 imgNormal2,
														 imgSelect2,
														 imgDisable2,NULL);    	
	toggleItem2->setSelectedIndex(2);
	toggleItem2->setEnabled(false);
	toggleItem2->setPosition(Vec2(visibleSize.width*0.24,20)); 
 
	auto imgNormal3 = MenuItemSprite::create(Sprite::createWithSpriteFrameName("levelSelect_butModes_0007.png"),Sprite::createWithSpriteFrameName("levelSelect_butModes_0007.png"));  
	auto imgSelect3 = MenuItemSprite::create(Sprite::createWithSpriteFrameName("levelSelect_butModes_0003.png"),Sprite::createWithSpriteFrameName("levelSelect_butModes_0003.png"));  
	auto imgDisable3 =MenuItemSprite::create(Sprite::createWithSpriteFrameName("levelSelect_butModes_0004.png"),Sprite::createWithSpriteFrameName("levelSelect_butModes_0004.png"));

	toggleItem3=MenuItemToggle::createWithCallback(
		                                                 CC_CALLBACK_1(ChooseDifficulty::starMenuCallback3,this), 
		                                                 imgNormal3,
														 imgSelect3,
														 imgDisable3,NULL);    	

	toggleItem3->setSelectedIndex(2);
	toggleItem3->setEnabled(false);
    toggleItem3->setPosition(Vec2(visibleSize.width*0.36,20));
     
    auto toggleMenu = Menu::create(toggleItem1,toggleItem2,toggleItem3, NULL);  
    toggleMenu->setPosition(Vec2(0,0));  
    this->addChild(toggleMenu, 2);  
	auto listenerkeyPad = EventListenerKeyboard::create();  
	listenerkeyPad->onKeyReleased = CC_CALLBACK_2(ChooseDifficulty::onKeyReleased, this);  
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listenerkeyPad, this); 

	return true;
}

void ChooseDifficulty::initWithLevel(int level)
{
	ValueVector txt_description = 
		FileUtils::getInstance()->getValueVectorFromFile(cocos2d::StringUtils::format("level%d_description.xml",level));
	int i = 0;
	for( auto& e : txt_description){
		auto txt_map = txt_description.at(i).asValueMap();
		int id_int = txt_map.at("id").asInt();
		if(id_int == i){
			blueStrTop = txt_map.at("blueStrTop").asString();
			blackStr[0] = txt_map.at("blackStr1").asString();
			blackStr[1] = txt_map.at("blackStr2").asString();
			blackStr[2] = txt_map.at("blackStr3").asString();
			blueStr[0] = txt_map.at("blueStr1").asString();
			blueStr[1] = txt_map.at("blueStr2").asString();
			blueStr[2] = txt_map.at("blueStr3").asString();
		}
		i++; 
	}
	auto label1 = Label::createWithTTF(blueStrTop, "Marker Felt.ttf", 40);
    label1->setPosition(Vec2(visibleSize.width*0.5, 620));
	label1->setColor(Color3B(0,0,0));
	label1->setRotation(3.0f);
	label1->setAnchorPoint(Vec2(0,1));
    this->addChild(label1, 1);

	blueLabel = Label::createWithTTF(blueStr[0], "Marker Felt.ttf", 30);
	blueLabel->setPosition(Vec2(visibleSize.width*0.5, 570));
	blueLabel->setRotation(3.0f);
	blueLabel->setColor(Color3B(65,94,241));
	blueLabel->setAnchorPoint(Vec2(0,1));
    this->addChild(blueLabel, 1);




	blackLabel = Label::createWithTTF(blackStr[0], "Marker Felt.ttf", 21);
	blackLabel->setPosition(Vec2(visibleSize.width*0.50, 525));
	blackLabel->setRotation(3.0f);
	blackLabel->setColor(Color3B(0,0,0));
	blackLabel->setAnchorPoint(Vec2(0,1));

    this->addChild(blackLabel, 1);
	this->level = level;
	int star = UserDefault::getInstance()->getIntegerForKey(cocos2d::StringUtils::format(GameManager::getInstance()->LEVELX_STARNUM,level).data(),0);
	toggleItem1->setPosition(toggleItem1->getPosition()+Vec2(0,20));

	setBadges(star);
	auto thumb = Sprite::createWithSpriteFrameName(cocos2d::StringUtils::format("thumb_stage%d.png",level+1));
	thumb->setPosition(Vec2(260,400));
	addChild(thumb,1);
}

void ChooseDifficulty::onKeyReleased(EventKeyboard::KeyCode keycode, Event* event)
{
    switch (keycode)
    {
	case EventKeyboard::KeyCode::KEY_BACK:   
		Director::getInstance()->popScene();
        break;
    case EventKeyboard::KeyCode::KEY_MENU:      
        break;
    case::EventKeyboard::KeyCode::KEY_HOME:
        break;
    default:
        break;
    }
}

void ChooseDifficulty::setBadges(int star)
{
	switch(star)
	{
	case(0):
		toggleItem1->setSelectedIndex(0);       
		toggleItem2->setSelectedIndex(2);      
		toggleItem3->setSelectedIndex(2);  
		toggleItem1->setPosition(toggleItem1->getPosition()+Vec2(0,20));

		toggleItem1->setEnabled(false);
		break;
	case 1:
		toggleItem1->setSelectedIndex(0);       
		toggleItem2->setSelectedIndex(2);      
		toggleItem3->setSelectedIndex(2);      
		star1->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("levelSelect_badges_0001.png"));

		toggleItem1->setEnabled(false);
		break;
	case 2:
		toggleItem1->setSelectedIndex(0);       
		toggleItem2->setSelectedIndex(2);      
		toggleItem3->setSelectedIndex(2);  
		toggleItem1->setEnabled(false);
		star1->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("levelSelect_badges_0001.png"));
		star2->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("levelSelect_badges_0001.png"));
		break;
	case 3:
		toggleItem1->setSelectedIndex(0);     
		toggleItem2->setSelectedIndex(1);      
		toggleItem3->setSelectedIndex(1);  
		toggleItem1->setEnabled(false);
		toggleItem2->setEnabled(true);
		toggleItem3->setEnabled(true);
		star1->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("levelSelect_badges_0001.png"));
		star2->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("levelSelect_badges_0001.png"));
		star3->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("levelSelect_badges_0001.png"));
		break;
	case 4:
		toggleItem1->setSelectedIndex(0);     
		toggleItem2->setSelectedIndex(1);      
		toggleItem3->setSelectedIndex(1);  
		toggleItem1->setEnabled(false);
		toggleItem2->setEnabled(true);
		toggleItem3->setEnabled(true);
		star1->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("levelSelect_badges_0001.png"));
		star2->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("levelSelect_badges_0001.png"));
		star3->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("levelSelect_badges_0001.png"));
		star4->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("levelSelect_badges_0003.png"));
		break;
	case 5:
		toggleItem1->setSelectedIndex(0);     
		toggleItem2->setSelectedIndex(1);      
		toggleItem3->setSelectedIndex(1);  
		toggleItem1->setEnabled(false);
		toggleItem2->setEnabled(true);
		toggleItem3->setEnabled(true);
		star1->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("levelSelect_badges_0001.png"));
		star2->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("levelSelect_badges_0001.png"));
		star3->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("levelSelect_badges_0001.png"));
		star4->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("levelSelect_badges_0003.png"));
		star5->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("levelSelect_badges_0005.png"));
		break;
	default:
		break;
	}

}


void ChooseDifficulty::menuCallback(Ref* pSpender){

	SoundManager::playClickEffect();
	Director::getInstance()->popScene();
}

void ChooseDifficulty::menuCallnext(Ref* pSpender)
{     
	SoundManager::playClickEffect();
	Director::getInstance()->replaceScene(TransitionGame::create(2.0f, GameScene::playGame(level,difficulty)));      
}

void ChooseDifficulty::starMenuCallback1(Ref* pSpender)
{
	SoundManager::playClickEffect();
	difficulty = 0;
	toggleItem1->runAction(MoveBy::create(0.1f,Vec2(0,20)));
	if(toggleItem2->getSelectedIndex() == 0)
		toggleItem2->runAction(MoveBy::create(0.1f,Vec2(0,-20)));
	if(toggleItem3->getSelectedIndex() == 0)
		toggleItem3->runAction(MoveBy::create(0.1f,Vec2(0,-20)));

	toggleItem1->setEnabled(false); 
	toggleItem1->setSelectedIndex(0); 
	toggleItem2->setSelectedIndex(1);       
	toggleItem2->setEnabled(true);
	toggleItem3->setSelectedIndex(1);       
	toggleItem3->setEnabled(true);  

	blueLabel->setString(blueStr[0]);
	blackLabel->setString(blackStr[0]);
}

void ChooseDifficulty::starMenuCallback2(Ref* pSpender)
{
	SoundManager::playClickEffect();
	difficulty = 1;
	toggleItem2->runAction(MoveBy::create(0.1f,Vec2(0,20)));
	if(toggleItem1->getSelectedIndex() == 0)
		toggleItem1->runAction(MoveBy::create(0.1f,Vec2(0,-20)));
	if(toggleItem3->getSelectedIndex() == 0)
		toggleItem3->runAction(MoveBy::create(0.1f,Vec2(0,-20)));
	toggleItem2->setSelectedIndex(0);       
	toggleItem2->setEnabled(false);
	toggleItem1->setSelectedIndex(1);       
	toggleItem1->setEnabled(true);
	toggleItem3->setSelectedIndex(1);       
	toggleItem3->setEnabled(true); 



	blueLabel->setString(blueStr[1]);
	blackLabel->setString(blackStr[1]); 
}

void ChooseDifficulty::starMenuCallback3(Ref* pSpender)
{
	SoundManager::playClickEffect();
	difficulty = 2;
	toggleItem3->runAction(MoveBy::create(0.1f,Vec2(0,20)));
	if(toggleItem2->getSelectedIndex() == 0)
		toggleItem2->runAction(MoveBy::create(0.1f,Vec2(0,-20)));
	if(toggleItem1->getSelectedIndex() == 0)
		toggleItem1->runAction(MoveBy::create(0.1f,Vec2(0,-20)));
	toggleItem3->setSelectedIndex(0);       
	toggleItem3->setEnabled(false); 
	toggleItem1->setSelectedIndex(1);       
	toggleItem1->setEnabled(true);
	toggleItem2->setSelectedIndex(1);       
	toggleItem2->setEnabled(true);  

	blueLabel->setString(blueStr[2]);
	blackLabel->setString(blackStr[2]); 
}