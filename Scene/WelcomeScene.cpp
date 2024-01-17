#include "WelcomeScene.h"
#include "Scene/GameView.h"
#include "Scene/TransitionGame.h"
#include "Data/SoundManager.h"
#include "Introduction/Information.h"
#include "Sprite/SlotMenu.h"

#if USE_AUDIO_ENGINE
#include "audio/include/AudioEngine.h"
using namespace cocos2d::experimental;
#endif

Scene* WelcomeScene::createScene()
{
    auto scene = Scene::create();
    
    auto layer = WelcomeScene::create();

    scene->addChild(layer);

    return scene;
}

bool WelcomeScene::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
	visibleSize = Director::getInstance()->getVisibleSize();

	initBackGround();
	initLogo();
	initMenu_save();
	initButton_start();
	init_creditBtn();
	initSoundButton();

	auto listenerkeyPad = EventListenerKeyboard::create();  
	listenerkeyPad->onKeyReleased = CC_CALLBACK_2(WelcomeScene::onKeyReleased, this);  
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listenerkeyPad, this); 

    return true;
}

void WelcomeScene::onEnterTransitionDidFinish()
{
	auto Sequence=Sequence::create(ScaleTo::create(0.5f,1.5f,1.5f),
		ScaleTo::create(0.2f,1.0f,1.0f),
		CallFuncN::create(CC_CALLBACK_0(WelcomeScene::initLogoAnimation, this)),
		CallFuncN::create(CC_CALLBACK_0(WelcomeScene::initButton_startAnimation, this)),
		CallFuncN::create(CC_CALLBACK_0(WelcomeScene::init_creditBtn_startAnimation, this)),
		NULL);
	sprite_Logo->runAction(Sequence);
}

void WelcomeScene::initBackGround()
{
	auto sprite_background = Sprite::createWithSpriteFrameName("mainmenu_bg.png");
	sprite_background->setPosition(Vec2(visibleSize.width/2,visibleSize.height/2));
	addChild(sprite_background,-1);
}

void WelcomeScene::initLogo()
{
	sprite_Logo = Sprite::createWithSpriteFrameName("logo.png");
	sprite_Logo->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	point_Logo.x = visibleSize.width/2;
	point_Logo.y = visibleSize.height-(sprite_Logo->getContentSize().height/2);
	sprite_Logo->setScale(0.2f);
	sprite_Logo->setPosition(point_Logo);
	addChild(sprite_Logo,9);
}

void WelcomeScene::initButton_start()
{
	button_Start = Sprite::createWithSpriteFrameName("menu_startchain_0001.png");
	button_Start->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	button_Start->setVisible(false);
	button_Start->setPosition(point_Logo.x,point_Logo.y);
	addChild(button_Start,1);

	auto button_Start_listener = EventListenerTouchOneByOne::create();
	button_Start_listener->onTouchBegan = [&](Touch* touch, Event* event){
		
		auto target = static_cast<Sprite*>(event->getCurrentTarget());

		Vec2 locationInNode = target->convertTouchToNodeSpace(touch);

		Size size = target->getContentSize();
		Rect rect = Rect(0+40, 0+30, size.width-80, size.height/3 +15);
		if (rect.containsPoint(locationInNode)&&target->isVisible())
		{  
			//SoundManager::playClickEffect();
			target->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("menu_startchain_0002.png"));			
			return true;  
		}  
		return false;  
	};
	button_Start_listener->onTouchEnded = [&](Touch* touch, Event* event){
		auto target = static_cast<Sprite*>(event->getCurrentTarget());
		static_cast<Sprite*>(event->getCurrentTarget())->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("menu_startchain_0001.png"));
		button_credit->setVisible(false);
		button_credit->runAction(MoveTo::create(0.3f, Vec2(point_Logo.x,point_Logo.y - 180)));	
		button_Start->runAction(Sequence::create(
			DelayTime::create(0.3f),
			MoveTo::create(0.3f, Vec2(point_Logo.x,point_Logo.y)),NULL));
		button_Start->setVisible(false);
		setSaveMenuVisible();
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(button_Start_listener,button_Start);
}

void WelcomeScene::initLogoAnimation()
{
	auto sprite = Sprite::createWithSpriteFrameName("logo_brillo_0001.png");
	sprite->setPosition(point_Logo);
	SpriteFrame* frame = NULL;
	Vector<SpriteFrame*> aFrames(20);

	for (int len = 1;len <= 21; len++)
	{
		frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(cocos2d::StringUtils::format("logo_brillo_00%02d.png",len));
		if(frame!=nullptr)
			aFrames.pushBack(frame);
	}
	addChild(sprite,10);
	auto animation = Animation::createWithSpriteFrames(aFrames,0.1f);
	sprite->runAction(RepeatForever::create(Animate::create(animation)));
}

void WelcomeScene::initButton_startAnimation()
{
	button_Start->setVisible(true);
	button_Start->runAction(MoveTo::create(0.3f, Vec2(point_Logo.x,point_Logo.y-180)));	
}

void WelcomeScene::init_creditBtn()
{
	button_credit = Sprite::createWithSpriteFrameName("menu_creditschain_0001.png");
	button_credit->setVisible(false);
	button_credit->setPosition(point_Logo.x,point_Logo.y - 180);
	addChild(button_credit,0);

	auto button_credit_listener = EventListenerTouchOneByOne::create();
	button_credit_listener->onTouchBegan = [&](Touch* touch, Event* event){
		
		auto target = static_cast<Sprite*>(event->getCurrentTarget());

		Vec2 locationInNode = target->convertTouchToNodeSpace(touch);

		Size size = target->getContentSize();
		Rect rect = Rect(0+40, 0+30, size.width-80, size.height/3 +15);
		if (rect.containsPoint(locationInNode)&&target->isVisible())
		{  
			//SoundManager::playClickEffect();
			target->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("menu_creditschain_0002.png"));			
			return true;  
		}  
		return false;  
	};
	button_credit_listener->onTouchEnded = [&](Touch* touch, Event* event){
		static_cast<Sprite*>(event->getCurrentTarget())->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("menu_creditschain_0001.png"));
		Director::getInstance()->replaceScene(Information::createScene());
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(button_credit_listener,button_credit);
}

void WelcomeScene::init_creditBtn_startAnimation()
{
	button_credit->runAction(Sequence::create(
		DelayTime::create(0.3f),
		CallFuncN::create(CC_CALLBACK_0(Sprite::setVisible, button_credit,true)),
		MoveTo::create(0.3f, Vec2(point_Logo.x,point_Logo.y - 360)),NULL));	
}

void WelcomeScene::initMenu_save()
{
	menu_Save = Sprite::createWithSpriteFrameName("mainmenu_saveslot_bg.png");
	point_Menu_Save.x = point_Logo.x;
	point_Menu_Save.y = point_Logo.y - sprite_Logo->getContentSize().height*1.4/2;
	menu_Save->setPosition(Vec2(point_Menu_Save.x,point_Menu_Save.y-500));
	auto slot_0 = SlotMenu::createMenu(2);
	slot_0->setPosition(Vec2(menu_Save->getContentSize().width/2,menu_Save->getContentSize().height/2));
	menu_Save->addChild(slot_0);

	auto slot_1 = SlotMenu::createMenu(1);
	slot_1->setPosition(Vec2(menu_Save->getContentSize().width/4 -30,menu_Save->getContentSize().height/2));
	menu_Save->addChild(slot_1);

	auto slot_2 = SlotMenu::createMenu(3);
	slot_2->setPosition(Vec2(menu_Save->getContentSize().width/4*3 +30,menu_Save->getContentSize().height/2));
	menu_Save->addChild(slot_2);
	
	addChild(menu_Save,0);
	button_Menu_Save_Close = MenuItemSprite::create(Sprite::createWithSpriteFrameName("mainmenu_saveslot_close_0001.png"),
		Sprite::createWithSpriteFrameName("mainmenu_saveslot_close_0002.png"),
		CC_CALLBACK_1(WelcomeScene::savemenuCloseCallback, this));
	point_Button_Menu_Save_Close.x = point_Logo.x;
	point_Button_Menu_Save_Close.y = point_Menu_Save.y - menu_Save->getContentSize().height/2 + button_Menu_Save_Close->getContentSize().height+2;
	button_Menu_Save_Close->setPosition(Vec2(point_Button_Menu_Save_Close.x,point_Button_Menu_Save_Close.y-500));
	auto menu = Menu::create(button_Menu_Save_Close,NULL);
	menu->setPosition(Vec2::ZERO);
	addChild(menu,0);
}

void WelcomeScene::savemenuCloseCallback(cocos2d::Ref* pSender)
{
	//SoundManager::playClickEffect();
	setSaveMenuInVisible();	
	initButton_startAnimation();
	init_creditBtn_startAnimation();
}

void WelcomeScene::setSaveMenuInVisible()
{
	menu_Save->runAction(MoveBy::create(0.3f,Vec2(0,-500)));
	button_Menu_Save_Close->runAction(MoveBy::create(0.3f,Vec2(0,-500)));
}

void WelcomeScene::setSaveMenuVisible()
{
	menu_Save->runAction(MoveTo::create(0.3f,point_Menu_Save));
	button_Menu_Save_Close->runAction(MoveTo::create(0.3f,point_Button_Menu_Save_Close));
}

void WelcomeScene::onKeyReleased(EventKeyboard::KeyCode keycode, Event* event)
{
    switch (keycode)
    {
	case EventKeyboard::KeyCode::KEY_BACK:   
		if(button_Start->isVisible()){
			//SimpleAudioEngine::getInstance()->end();
			Director::getInstance()->end();
			#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS || CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID )
				exit(0);
			#endif
		}else
		{
			setSaveMenuInVisible();
			initButton_startAnimation();
		}
        break;
    case EventKeyboard::KeyCode::KEY_MENU:      
        break;
    case::EventKeyboard::KeyCode::KEY_HOME:
        break;
    default:
        break;
    }
}

void WelcomeScene::initSoundButton()
{
	auto winSize = Director::getInstance()->getWinSize();
	Sprite* backMusic;
	//SoundManager::playWelcomeBackMusic();
	if(UserDefault::getInstance()->getIntegerForKey("backmusic",1)==1){
		backMusic = Sprite::createWithSpriteFrameName("options_overlay_buttons_0001.png");		
	}else{
		backMusic = Sprite::createWithSpriteFrameName("options_overlay_buttons_0002.png");				
	}
	backMusic->setPosition(Vec2(0 + backMusic->getContentSize().width/2 + 10 ,winSize.height - backMusic->getContentSize().height/2 - 10));
	addChild(backMusic);
	auto button_backMusic_listener = EventListenerTouchOneByOne::create();
	button_backMusic_listener->onTouchBegan = [&](Touch* touch, Event* event){
		
		auto target = static_cast<Sprite*>(event->getCurrentTarget());

		Vec2 locationInNode = target->convertTouchToNodeSpace(touch);

		Size size = target->getContentSize();
		Rect rect = Rect(0, 0, size.width, size.height);
		if (rect.containsPoint(locationInNode))
		{  
			if(UserDefault::getInstance()->getIntegerForKey("backmusic",1)==1){
				UserDefault::getInstance()->setIntegerForKey("backmusic",0);
			}else{
				UserDefault::getInstance()->setIntegerForKey("backmusic",1);
			}
			target->setScale(1.1f);			
			return true;  
		}  
		return false;  
	};
	button_backMusic_listener->onTouchEnded = [&](Touch* touch, Event* event){
		auto target = static_cast<Sprite*>(event->getCurrentTarget());
		target->setScale(1.0f);
		if(UserDefault::getInstance()->getIntegerForKey("backmusic",1)==1){
			//SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
			target->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("options_overlay_buttons_0001.png"));	
		}else{
			//SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
			target->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("options_overlay_buttons_0002.png"));	
		}	
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(button_backMusic_listener,backMusic);

	Sprite* backEffect;
	if(UserDefault::getInstance()->getIntegerForKey("backeffect",1)==1){
		backEffect = Sprite::createWithSpriteFrameName("options_overlay_buttons_0003.png");		
	}else{
		backEffect = Sprite::createWithSpriteFrameName("options_overlay_buttons_0004.png");				
	}
	backEffect->setPosition(Vec2(backMusic->getPosition().x + backMusic->getContentSize().width ,winSize.height - backEffect->getContentSize().height/2 - 10));
	addChild(backEffect);
	auto button_backEffect_listener = EventListenerTouchOneByOne::create();
	button_backEffect_listener->onTouchBegan = [&](Touch* touch, Event* event){
		
		auto target = static_cast<Sprite*>(event->getCurrentTarget());

		Vec2 locationInNode = target->convertTouchToNodeSpace(touch);

		Size size = target->getContentSize();
		Rect rect = Rect(0, 0, size.width, size.height);
		if (rect.containsPoint(locationInNode))
		{  
			if(UserDefault::getInstance()->getIntegerForKey("backeffect",1)==1){
				UserDefault::getInstance()->setIntegerForKey("backeffect",0);
			}else{
				UserDefault::getInstance()->setIntegerForKey("backeffect",1);
			}
			target->setScale(1.1f);			
			return true;  
		}  
		return false;  
	};
	button_backEffect_listener->onTouchEnded = [&](Touch* touch, Event* event){
		auto target = static_cast<Sprite*>(event->getCurrentTarget());
		target->setScale(1.0f);
		if(UserDefault::getInstance()->getIntegerForKey("backeffect",1)==1){
			target->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("options_overlay_buttons_0003.png"));	
		}else{
			target->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("options_overlay_buttons_0004.png"));	
		}	
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(button_backEffect_listener,backEffect);
}