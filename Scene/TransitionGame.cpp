#include "Scene/TransitionGame.h"

#if USE_AUDIO_ENGINE
#include "audio/include/AudioEngine.h"
using namespace cocos2d::experimental;
#endif

USING_NS_CC;

TransitionGame * TransitionGame::create(float t, Scene *scene)
{
	TransitionGame * pScene = new TransitionGame();
    if (pScene && pScene->initWithDuration(t, scene))
    {
		pScene->autorelease();
        return pScene;
     }
     CC_SAFE_DELETE(pScene);
     return NULL;
}

TransitionGame * TransitionGame::createWithRenderTexture(float t, Scene *scene,RenderTexture *sqr)
{
	TransitionGame * pScene = new TransitionGame();
    if (pScene && pScene->initWithDuration(t, scene))
    {
		pScene->initRenderTexture(sqr);
		pScene->autorelease();
        return pScene;
     }
     CC_SAFE_DELETE(pScene);
     return NULL;
}

void TransitionGame::initRenderTexture(RenderTexture *sqr)
{
	auto _spr = Sprite::createWithTexture(sqr->getSprite()->getTexture());  
    _spr->setPosition(Vec2(Director::getInstance()->getVisibleSize().width/2, Director::getInstance()->getVisibleSize().height/2));   
	addChild(_spr);
}

TransitionGame::TransitionGame()
{
	m_FinishCnt = 0;
}

TransitionGame::~TransitionGame()
{
}

void TransitionGame::onEnter()
{
	
	//Ҫ����ĳ���
	_inScene->setVisible(false);
	TransitionScene::onEnter();
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 stLeftBegin, stLeftEnd, stRightBegin, stRightEnd;

	stLeftBegin.set(0,visibleSize.height / 2.0f);
	stLeftEnd.set(visibleSize.width / 2.0f,visibleSize.height / 2.0f);

	stRightBegin.set(visibleSize.width,visibleSize.height / 2.0f);
    stRightEnd.set(visibleSize.width / 2.0f,visibleSize.height / 2.0f);

	auto pLeft = Sprite::createWithSpriteFrameName("transitionDoor.png");
	pLeft->setScaleX(visibleSize.width/960);
	auto pRight = Sprite::createWithSpriteFrameName("transitionDoor.png");
	pRight->setScaleX(visibleSize.width/960);
	auto pLeft2 = Sprite::createWithSpriteFrameName("transitionLoading_left.png");
	auto pRight2 = Sprite::createWithSpriteFrameName("transitionLoading_right.png");

	pLeft->setAnchorPoint(Vec2(1,0.5));
	pRight->setAnchorPoint(Vec2(0,0.5));

	pLeft2->setAnchorPoint(Vec2(1,0.5));
	pRight2->setAnchorPoint(Vec2(0,0.5));

	pLeft2->setPosition(Vec2(pLeft->getContentSize().width,pLeft->getContentSize().height/2));
	pRight2->setPosition(Vec2(0,pRight->getContentSize().height/2));

	addChild(pLeft,1);
	addChild(pRight,1);

	pRight->setFlippedX(true);
	pLeft->setPosition(stLeftBegin);
	pRight->setPosition(stRightBegin);

	pLeft->addChild(pLeft2);
	pRight->addChild(pRight2);
	auto pActionLeft = MoveTo::create(_duration / 3, stLeftEnd);
    //�ұߵ������ƶ��
    auto pActionRight = MoveTo::create(_duration / 3, stRightEnd);
    //ԭ�ز���
    auto pActionLeft1 = MoveTo::create(_duration / 3, stLeftEnd);
    auto pActionRight1 = MoveTo::create(_duration / 3, stRightEnd);
        
    auto pActionLeft2 = MoveTo::create(_duration / 3, stLeftBegin);
    auto pActionRight2 = MoveTo::create(_duration / 3, stRightBegin);

	if(UserDefault::getInstance()->getIntegerForKey("backeffect",1)==1)
	{
		//SimpleAudioEngine::getInstance()->playEffect("sound/GUITransitionOpen.wav");
	}
	pLeft->runAction(Sequence::create(
		pActionLeft,
		CallFuncN::create(CC_CALLBACK_0(TransitionGame::OnSencondActionFinish, this)),
		DelayTime::create(1.0f),
		pActionLeft2, 
		CallFuncN::create(CC_CALLBACK_0(TransitionGame::LRFinish, this)),
		NULL));
	pRight->runAction(Sequence::create(
		pActionRight,
		DelayTime::create(1.0f),
		pActionRight2, 
		NULL));
}

void TransitionGame::LRFinish(void)
{
	//���ԵĻ��ɺ�Ҫִ�г��е�Finish
	TransitionScene::finish();
}

void TransitionGame::OnSencondActionFinish(void)
{
    if(UserDefault::getInstance()->getIntegerForKey("backeffect",1)==1)
	{
		//SimpleAudioEngine::getInstance()->playEffect("sound/GUITransitionClose.wav");
	}
    _inScene->setVisible(true);
	_outScene->setVisible(false);
}