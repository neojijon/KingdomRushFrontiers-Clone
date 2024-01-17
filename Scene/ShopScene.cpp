#include "ShopScene.h"
#include "Data/GameManager.h"
#
USING_NS_CC;

Scene* ShopScene::createScene()
{
    auto scene = Scene::create();   
    auto layer = ShopScene::create();
    scene->addChild(layer);
    return scene;
}

bool ShopScene::init()
{
    if ( !Layer::init() )
    {
        return false;
    }

	size = Director::getInstance()->getVisibleSize();  
  
    str_introduction[0] = "THE BIG BAD BOY OF\n BOMBS! YOU ONLY NEED\n ONE OF THESE TO CLEAR THE\n BATTLEFIELD AND CLAIM THE\n SPOILS OF WAR! JUST TELL\n US WHERE TO DROP IT!";
	str_introduction[1] = "FREEZE THE WORLE!\n\n THE MAGIC IN THIS ROD WILL\n FREZE ALL BADDIES AND\n PREVENT NEW ONES FROM\n APPROACHING ";
	str_introduction[2] = "BLAST YOUR ENEMIES TO\n PLECES WITH THESE\n SPECIALLY DESIGNED\n GNOME EXPLOSIVES.\n\n DESTRUCTION GUARANTEED.";
	str_introduction[3] = "THIS SPECIAL CONCOCTION\n WILL FREEZE YOUR ENEMIES\n HELPLESS IN PLACE FOR A\n WHILE";
	str_introduction[4] = "MAGICAL HEARTS TRAPPED\n IN A BOX.\n\n BREAK GLASS IN AN\n EMERGENCY TO GAIN 5\n EXTRA LIVES.";
	str_introduction[5] = "LEAVE NOTHING TO CHANCE.\n BRING EXTRA GOLD TO THE\n BATTLEFIELD!\n\n EACH BIG WORTH 500\n GOLD PIECES.";

	str_name[0] = "BOY";
	str_name[1] = "ICE";
	str_name[2] = "BOMB";
	str_name[3] = "WATER";
	str_name[4] = "HEARTBOX";
	str_name[5] = "MONEY";

	str_gem[0] = 999;
	str_gem[1] = 250;
	str_gem[2] = 50;
	str_gem[3] = 50;
	str_gem[4] = 50;
	str_gem[5] = 500;
	label = Label::createWithTTF("", "SohoGothicProMedium.ttf", 24);
    label->setPosition(Vec2(680, 560));
    addChild(label,1);
	label2 = Label::createWithTTF(" ", "SohoGothicProMedium.ttf", 24);
	label2->setPosition(Vec2(900, 545));
	addChild(label2,1);
	label3 = Label::createWithTTF("", "SohoGothicProMedium.ttf", 12);
    label3->setPosition(Vec2(900, 440));
    addChild(label3,1);

	gem = UserDefault::getInstance()->getIntegerForKey(GameManager::getInstance()->SLOTX_GEM,0);
	for(int i=0;i<6;i++)
	{
		count[i]=UserDefault::getInstance()->getIntegerForKey(cocos2d::StringUtils::format(GameManager::getInstance()->SLOTX_SHOP,i).data());		
	}

	initBackpackIcon();
	


	gemLabel = Label::createWithTTF(cocos2d::StringUtils::format("%d",gem), "SohoGothicProMedium.ttf", 30);
	gemLabel->setColor(Color3B::WHITE);
	gemLabel->setPosition(Vec2(size.width*0.35, size.height*0.92));
    addChild(gemLabel,1);


	initPicture();
	auto listenerkeyPad = EventListenerKeyboard::create();  
	listenerkeyPad->onKeyReleased = CC_CALLBACK_2(ShopScene::onKeyReleased, this);  
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listenerkeyPad, this); 
	return true;
}

void ShopScene::onKeyReleased(EventKeyboard::KeyCode keycode, Event* event)
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

void ShopScene::initBackpackIcon()
{
	float a[6] = {0.0f,0.13f,0.236f,0.346f,0.46f,0.56f};
	for(int i=0;i<6;i++){
		auto backPackIcon = Sprite::createWithSpriteFrameName(cocos2d::StringUtils::format("inaps_backPackIcons_000%d.png",i+1));
		backPackIcon->setPosition(156,size.height*(0.72f-a[i]));
		addChild(backPackIcon,3);
		if(count[i] == 0)
			backPackIcon->setVisible(false);
		auto countLabel =  Label::createWithTTF(cocos2d::StringUtils::format("%d",count[i]), "SohoGothicProMedium.ttf", 24); 
		countLabel->setPosition(Vec2(137, size.height*(0.70f-a[i])));
		addChild(countLabel,3);
		backpackIcons.pushBack(backPackIcon);
		countLabels.pushBack(countLabel);
	}
}

void ShopScene::initPicture()
{
	auto size = Director::getInstance()->getVisibleSize();  
    auto bgSprite = Sprite::createWithSpriteFrameName("inaps_BG.png");
    bgSprite->setPosition(Vec2(size.width*0.5,size.height*0.5));
    addChild(bgSprite,0);
	borad = Sprite::create();
	borad->setPosition(Vec2(655,440));
	addChild(borad);

	auto shopIcon2 = ShopIcon::createIcon(2);
	shopIcon2->setPosition(Vec2(830,250));
	addChild(shopIcon2);

	auto shopIcon5 = ShopIcon::createIcon(5);
	shopIcon5->setPosition(Vec2(280,155));
	addChild(shopIcon5);

	auto shopIcon1 = ShopIcon::createIcon(1);
	shopIcon1->setPosition(Vec2(640,170));
	addChild(shopIcon1);

	auto shopIcon4 = ShopIcon::createIcon(4);
	shopIcon4->setPosition(Vec2(385,145));
	addChild(shopIcon4);

	auto shopIcon6 = ShopIcon::createIcon(6);
	shopIcon6->setPosition(Vec2(800,170));
	addChild(shopIcon6);

	auto shopIcon3 = ShopIcon::createIcon(3);
	shopIcon3->setPosition(Vec2(485,130));
	addChild(shopIcon3);

	shopIcons.pushBack(shopIcon1);
	shopIcons.pushBack(shopIcon2);
	shopIcons.pushBack(shopIcon3);
	shopIcons.pushBack(shopIcon4);
	shopIcons.pushBack(shopIcon5);
	shopIcons.pushBack(shopIcon6);

	shopIcon3->setGlowing();
	setBorad(3);

	auto buttonListener = EventListenerTouchOneByOne::create();
	buttonListener->onTouchBegan = [&](Touch* touch, Event* event){
		
		auto target = static_cast<ShopIcon*>(event->getCurrentTarget());
		
		Vec2 locationInNode = target->convertToNodeSpace(touch->getLocation());

		Size size = target->icon->getContentSize();
		Rect rect;
		if(target->type == 1)
			rect = Rect(0-size.width/4, 0-size.height/2, size.width/2, size.height);
		else
			rect = Rect(0-size.width/4, 0-size.height/2, size.width/2, size.height/2);
		if (rect.containsPoint(locationInNode))
		{  
			setBorad(target->type);
			target->setScale(0.9f);
			return true;  
		}  
		return false;  
	};
	buttonListener->onTouchEnded = [&](Touch* touch, Event* event){
		auto target = static_cast<ShopIcon*>(event->getCurrentTarget());
		target->setScale(1.0f);
		for(int i = 0;i<6;i++){
			shopIcons.at(i)->setNotGlowing();
		}
		target->setGlowing();
	};
	buttonListener->setSwallowTouches(true);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(buttonListener,shopIcon1);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(buttonListener->clone(),shopIcon3);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(buttonListener->clone(),shopIcon4);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(buttonListener->clone(),shopIcon5);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(buttonListener->clone(),shopIcon6);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(buttonListener->clone(),shopIcon2);
	  auto confirmButton = MenuItemSprite::create(Sprite::createWithSpriteFrameName("upgrades_buttons_0003.png"),
		  Sprite::createWithSpriteFrameName("upgrades_buttons_0004.png")); 
	  confirmButton->setPosition(Vec2(size.width*0.90,size.height*0.10));
	  confirmButton->setCallback([&](Ref *pSender){
		UserDefault::getInstance()->setIntegerForKey(GameManager::getInstance()->SLOTX_GEM,gem);
		for(int i=0;i<6;i++)
		{
			UserDefault::getInstance()->setIntegerForKey(cocos2d::StringUtils::format(GameManager::getInstance()->SLOTX_SHOP,i).data(),count[i]);		
		}
		Director::getInstance()->popScene();
	  });
	  auto buyButton = MenuItemSprite::create(Sprite::createWithSpriteFrameName("inaps_buyButton_0001.png"),
		  Sprite::createWithSpriteFrameName("inaps_buyButton_0002.png")); 
	  buyButton->setPosition(Vec2(780,320));
	  buyButton->setCallback([&](Ref *pSender){
		  for(int i=0;i<6;i++){
			  if(shopIcons.at(i)->glow->isVisible()){
				  buySth(i);
				  break;
			  }
		  }
		
	  });
      auto menu = Menu::create(confirmButton,buyButton,NULL);    
	  menu->setPosition(Vec2::ZERO);
      addChild(menu,1);
	
 }

 void ShopScene::buySth(int i)
 {
	 if(gem < str_gem[i]){
		auto bubbleNeedMore = Sprite::createWithSpriteFrameName("inaps_bubble_needMore.png");
		bubbleNeedMore->setVisible(true);
		bubbleNeedMore->setPosition(650,430);
		addChild(bubbleNeedMore,5);
		bubbleNeedMore->runAction(Sequence::create(
			FadeOut::create(3.0f),
			CallFuncN::create(CC_CALLBACK_0(Sprite::removeFromParent, bubbleNeedMore)),NULL));
	 }else{
		gem = gem - str_gem[i];
		setBackpackIcon(i);
		gemLabel->setString(cocos2d::StringUtils::format("%d",gem));
		auto bubbleSprite = Sprite::createWithSpriteFrameName("inaps_bubble.png");
		bubbleSprite->setPosition(650,430);
		addChild(bubbleSprite,5); 
		bubbleSprite->runAction(Sequence::create(
			FadeOut::create(3.0f),
			CallFuncN::create(CC_CALLBACK_0(Sprite::removeFromParent, bubbleSprite)),NULL));
	 }
 }

 void ShopScene::setBackpackIcon(int i)
 {
	 count[i] ++;
	 countLabels.at(i)->setString(cocos2d::StringUtils::format("%d",count[i]));
	 if(count[i]>0)
		 backpackIcons.at(i)->setVisible(true);
 }

 void ShopScene::setBorad(int type)
 {
	 borad->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(
		 cocos2d::StringUtils::format("inaps_boardDrawings_000%d.png",type)));
	 label3->setString(str_introduction[type-1]);
	 label2->setString(cocos2d::StringUtils::format("%d",str_gem[type-1]));
	 label->setString(str_name[type-1]);
 }