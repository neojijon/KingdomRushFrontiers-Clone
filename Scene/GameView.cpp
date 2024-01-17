#include "Scene/GameView.h"
#include "Scene/TransitionGame.h"
#include "WelcomeScene.h"
#include "Sprite/MapFlag.h"
#include "Road/Road.h"
#include "Layer/GameViewMenu.h"
#include "Data/GameManager.h"
#include "Sprite/RespirationSprite.h"
#include "Data/SoundManager.h"

USING_NS_CC;

Scene* GameView::createScene()
{
    auto scene = Scene::create();
    
    auto layer = GameView::create();

	auto menuLayer = GameViewMenu::create();

    scene->addChild(layer);
	scene->addChild(menuLayer);

    return scene;
}

bool GameView::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
	instance = GameManager::getInstance();
		
	//UserDefault::getInstance()->setIntegerForKey(instance->LEVELX_DOWNCOUNT,0);

	winSize = Director::getInstance()->getWinSize();
	bgSprite = Sprite::createWithSpriteFrameName("MapBackground.png");
	bgSprite->setAnchorPoint(Vec2::ZERO);
	bgSprite->setPosition(Vec2::ZERO);

	mapFlagPointVector.push_back(Vec2(375,775));
	mapFlagPointVector.push_back(Vec2(495,735));
	mapFlagPointVector.push_back(Vec2(510,620));
	mapFlagPointVector.push_back(Vec2(370,575));
	mapFlagPointVector.push_back(Vec2(205,505));
	mapFlagPointVector.push_back(Vec2(455,305));
	mapFlagPointVector.push_back(Vec2(690,420));
	mapFlagPointVector.push_back(Vec2(855,254));
	mapFlagPointVector.push_back(Vec2(1020,340));
	mapFlagPointVector.push_back(Vec2(934,490));
	mapFlagPointVector.push_back(Vec2(830,560));
	mapFlagPointVector.push_back(Vec2(795,710));
	mapFlagPointVector.push_back(Vec2(910,770));
	mapFlagPointVector.push_back(Vec2(1015,770));

	addChild(bgSprite);
	//��ӵ�·
	addRoad();
	//�������
	addMapFlag();
	

	this->setPosition(Vec2(0,winSize.height-bgSprite->getContentSize().height));

	int newReady = UserDefault::getInstance()->getIntegerForKey(instance->LEVELX_NEWDOWN,0);

	Vec2 location = Vec2();
	location.x = winSize.width/2 - mapFlagPointVector.at(newReady).x;
	location.y = winSize.height/2 - mapFlagPointVector.at(newReady).y;
	auto bgSpriteCurrSize = bgSprite->getBoundingBox().size;
	location.x = MIN(location.x,0);
    location.x = MAX(location.x, -bgSpriteCurrSize.width + winSize.width);
    location.y = MIN(location.y,0);
    location.y = MAX(location.y, -bgSpriteCurrSize.height + winSize.height);
	this->setPosition(location);

	

	auto listener = EventListenerTouchAllAtOnce::create();
	// 2 �󶨴����¼�
	listener->onTouchesBegan = CC_CALLBACK_2(GameView::onTouchesBegan, this);// ������ʼʱ����
	listener->onTouchesMoved = CC_CALLBACK_2(GameView::onTouchesMoved, this);// �����ƶ�ʱ����
	// 3 ��Ӽ�����
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, bgSprite);

	auto listenerkeyPad = EventListenerKeyboard::create();  
	listenerkeyPad->onKeyReleased = CC_CALLBACK_2(GameView::onKeyReleased, this);  
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listenerkeyPad, this); 
	//SoundManager::playGameTheme1();
    return true;
}

void GameView::onEnterTransitionDidFinish()
{
	int newReady = UserDefault::getInstance()->getIntegerForKey(instance->LEVELX_NEWDOWN,0);
	if(newReady<=12){//���13��
		if(UserDefault::getInstance()->getIntegerForKey(instance->SLOTX_DOWNCOUNT,0)!=newReady){
			UserDefault::getInstance()->setIntegerForKey(instance->SLOTX_DOWNCOUNT,newReady);
			mapFlagVector.at(newReady-1)->changeType(0);
			auto sequence = Sequence::create(
				CallFuncN::create(CC_CALLBACK_0(MapFlag::startSuccessAnimation, mapFlagVector.at(newReady-1)))
				,
				CallFuncN::create(CC_CALLBACK_0(Road::buildRoadAnimation, road,newReady-1))
				,DelayTime::create(1.5f)
				,CallFuncN::create(CC_CALLBACK_0(GameView::addNewMapFlag,this ,newReady))
				,NULL);
			runAction(sequence);
		}
	}
}

void GameView::addNewMapFlag(int num)
{
	auto mapFlag = MapFlag::createWithLevel(num);
	mapFlag->setPosition(mapFlagPointVector.at(num));
	addChild(mapFlag);
	mapFlagVector.pushBack(mapFlag);
	mapFlag->startDropdownAnimation();
}

void GameView::addRoad()
{
	road = Road::create();
	road->setPosition(Vec2(635,500));
	addChild(road);
}

void GameView::onTouchesMoved(const std::vector<Touch*>& touches, Event  *event)
{
	if(touches.size() == 1)        // ��������ƶ�
    {
        // ����ʱ��touches��ֻ��һ��Touch��������ͨ��touches[0]�Ϳ��Եõ���������
        auto touch = touches[0];
        // ���㻬�������еĻ�������
        auto diff = touch->getDelta();       
        // �õ���ǰbgSprite��λ��
        auto currentPos = this->getPosition();
        // �õ�������bgSpriteӦ�����ڵ�λ��
        auto pos = currentPos + diff;
        // �õ��˿�bgSprite�ĳߴ�
        auto bgSpriteCurrSize = bgSprite->getBoundingBox().size;
 
        //�߽���ƣ�Լ��pos��λ��
        pos.x = MIN(pos.x, bgSpriteCurrSize.width * bgSprite->getAnchorPoint().x);
        pos.x = MAX(pos.x, -bgSpriteCurrSize.width + winSize.width + bgSpriteCurrSize.width * bgSprite->getAnchorPoint().x);
        pos.y = MIN(pos.y, bgSpriteCurrSize.height * bgSprite->getAnchorPoint().y);
        pos.y = MAX(pos.y, -bgSpriteCurrSize.height + winSize.height + bgSpriteCurrSize.height * bgSprite->getAnchorPoint().y);

        this->setPosition(pos);
	
    }
}

void GameView::onTouchesBegan(const std::vector<Touch*>& touches, Event  *event)
{

}

void GameView::onKeyReleased(EventKeyboard::KeyCode keycode, Event* event)
{
	if(keycode==EventKeyboard::KeyCode::KEY_BACK)
	{
		auto scene = WelcomeScene::createScene();
		Director::getInstance()->replaceScene(TransitionGame::create(2.0f,scene));
	}
}

void GameView::addMapFlag()
{
	int count = UserDefault::getInstance()->getIntegerForKey(instance->SLOTX_DOWNCOUNT,0);
	for(int i=0;i<= count;i++)
	{
		auto mapFlag = MapFlag::createWithLevel(i);
		mapFlag->setPosition(mapFlagPointVector.at(i));
		mapFlagVector.pushBack(mapFlag);
		if(i == count)
		{
			mapFlag->setStarClose();
		}
		addChild(mapFlag);
	}
	if(UserDefault::getInstance()->getIntegerForKey(instance->LEVELX_NEWDOWN,0)==0){
		auto respirationSprite = RespirationSprite::createRespirationSprite("mapBalloon_starthere.png");
		respirationSprite->setPosition(Vec2(375,855));
		addChild(respirationSprite);
	}
}