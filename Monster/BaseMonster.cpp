#include "Monster/BaseMonster.h"
#include "Data/GameManager.h"
#include "Map/BaseMap.h"

USING_NS_CC;

BaseMonster::BaseMonster()
:baseSprite(NULL),
pointCounter(0),
runSpeed(0)
,maxHp(0)
,currHp(0)
,armor(0)
,hpPercentage(100)
,hpBar(NULL)
,lastState(stateNone)
,attackBySoldier(true)
,attackByTower(true)
,isAttacking(false)
,isSlowed(false)
,money(0)
{}

BaseMonster::~BaseMonster()
{}

bool BaseMonster::init()
{
	if (!Sprite::init())
	{
		return false;
	}
	return true;
}

void BaseMonster::setListener()
{
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(BaseMonster::onTouchBegan, this);
	listener->onTouchEnded = CC_CALLBACK_2(BaseMonster::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener,baseSprite);
}

void BaseMonster::createAndSetHpBar()
{
    hpBgSprite = Sprite::createWithSpriteFrameName("lifebar_bg_small.png");

    hpBgSprite->setPosition(Vec2(baseSprite->getContentSize().width / 2, baseSprite->getContentSize().height ));
    baseSprite->addChild(hpBgSprite);
    
	hpBar = ProgressTimer::create(Sprite::createWithSpriteFrameName("lifebar_small.png"));
	hpBar->setType(ProgressTimer::Type::BAR);
	hpBar->setMidpoint(Vec2(0, 0.5f));
	hpBar->setBarChangeRate(Vec2(1, 0));
	hpBar->setPercentage(hpPercentage);
    hpBar->setPosition(Vec2(hpBgSprite->getContentSize().width / 2, hpBgSprite->getContentSize().height / 2 ));
    hpBgSprite->addChild(hpBar);
}

void BaseMonster::getHurt()
{
	blood->setVisible(true);
	blood->runAction(Sequence::create(Animate::create(AnimationCache::getInstance()->getAnimation("blood_red")),
		CallFuncN::create(CC_CALLBACK_0(Sprite::setVisible,blood, false))
                                       , NULL));
}

Vec2 BaseMonster::currVec2()
{
    return pointsVector.at(pointCounter);
}

Vec2 BaseMonster::getNextVec2()
{
	auto temp = pointCounter + 5;
	auto maxCount = int(pointsVector.size());
	if (temp < maxCount  ){
		auto node =this->pointsVector.at(temp);
        return node;
    }
	return currVec2();
}


Vec2 BaseMonster::nextVec2()
{
    auto maxCount = int(pointsVector.size());
	pointCounter++;
	if (pointCounter < maxCount  ){
		auto node =this->pointsVector.at(pointCounter);
        return node;
    }
	else{
		pointCounter = maxCount - 1 ;
	}
	return currVec2();
}

void BaseMonster::setMonsterZorder(int yOrder)
{
	int hunder = (yOrder/100);
	switch (hunder)
	{
	case(0):
		this->setLocalZOrder(10);
		break;
	case(1):
		this->setLocalZOrder(9);
		break;
	case(2):
		this->setLocalZOrder(8);
		break;
	case(3):
		this->setLocalZOrder(7);
		break;
	case(4):
		this->setLocalZOrder(6);
		break;
	case(5):
		this->setLocalZOrder(5);
		break;
	case(6):
		this->setLocalZOrder(4);
		break;
	case(7):
		this->setLocalZOrder(3);
		break;
	case(8):
		this->setLocalZOrder(2);
		break;
	case(9):
		this->setLocalZOrder(1);
		break;
	case(10):
		this->setLocalZOrder(0);
		break;
	default:

		break;
	}
}

void BaseMonster::runNextVec2()
{
    auto tempCurrPoint = currVec2();

    baseSprite->setPosition(tempCurrPoint);

    tempNextPoint = nextVec2();
	setMonsterZorder(tempNextPoint.y);
	if(fabs(tempNextPoint.y-tempCurrPoint.y)>5 && tempNextPoint.y > tempCurrPoint.y)//����������
	{
		setState(stateWalkUp);
	}else if(fabs(tempNextPoint.y-tempCurrPoint.y)>5 &&tempNextPoint.y <= tempCurrPoint.y)//����������
	{
		setState(stateWalkDown);
	}else if(tempNextPoint.x >= tempCurrPoint.x)//����������
	{
		setState(stateWalkRight);
	}
	else if(tempNextPoint.x < tempCurrPoint.x)//����������
	{
		setState(stateWalkLeft);
	}
	if( tempNextPoint!= tempCurrPoint ){

		auto duration =  tempCurrPoint.getDistance(tempNextPoint) / getRunSpeed() ;

        baseSprite->runAction(Sequence::create(MoveTo::create(duration, tempNextPoint)
                                           , CallFuncN::create(CC_CALLBACK_0(BaseMonster::runNextVec2, this))
                                           , NULL));
    }else{
		//�ߵ��յ�
		GameManager::getInstance()->LIFE --;
		GameManager::getInstance()->monsterVector.eraseObject(this);
		unscheduleAllCallbacks();
		setCurrHp(0);
		removeFromParent();
	}
}

void BaseMonster::update(float dt)
{
	//��״̬����
	if(lastState!=getState()){
		//����״̬�ж�
		switch (getState())
		{
		case(stateWalkRight):{
			lastState = stateWalkRight;
			//ֹ֮ͣǰ����
			stopMonsterAnimation();
			baseSprite->setFlippedX(false);
			auto action = RepeatForever::create(Animate::create(AnimationCache::getInstance()->getAnimation(getName()+"runright")));
			action->setTag(stateWalkRight);
			baseSprite->runAction(action);}
			break;
		case(stateWalkLeft):{
			lastState = stateWalkLeft;
			stopMonsterAnimation();
			baseSprite->setFlippedX(true);
			auto aa = getName();
			auto action = RepeatForever::create(Animate::create(AnimationCache::getInstance()->getAnimation(getName()+"runleft")));
			action->setTag(stateWalkLeft);
			baseSprite->runAction(action);}
			break;
		case(stateWalkUp):{
			lastState = stateWalkUp;
			stopMonsterAnimation();
			baseSprite->setFlippedX(false);
			auto action = RepeatForever::create(Animate::create(AnimationCache::getInstance()->getAnimation(getName()+"runup")));
			action->setTag(stateWalkUp);
			baseSprite->runAction(action);}
			break;
		case(stateWalkDown):{
			lastState = stateWalkDown;
			stopMonsterAnimation();
			baseSprite->setFlippedX(false);
			auto action = RepeatForever::create(Animate::create(AnimationCache::getInstance()->getAnimation(getName()+"rundown")));
			action->setTag(stateWalkDown);
			baseSprite->runAction(action);}
			break;
		case(stateAttackRight):{
			//Ĭ�����ұ߹���
			lastState = stateAttackRight;
			stopMonsterAnimation();
			baseSprite->setFlippedX(false);
			auto action = RepeatForever::create(Animate::create(AnimationCache::getInstance()->getAnimation(getName()+"attack")));
			action->setTag(stateAttackRight);
			baseSprite->runAction(action);}
			break;
		case(stateAttackLeft):{
			lastState = stateAttackLeft;
			stopMonsterAnimation();
			baseSprite->setFlippedX(true);
			auto action = RepeatForever::create(Animate::create(AnimationCache::getInstance()->getAnimation(getName()+"attack")));
			action->setTag(stateAttackLeft);
			baseSprite->runAction(action);}
			break;
		case(stateNone):{
			lastState = stateNone;}
			break;
		case(stateFrozen):{
			lastState = stateFrozen;}
			break;
		case(stateDeath):{
			lastState = stateDeath;}
			break;
		}
	}
}

void BaseMonster::stopMonsterAnimation()
{
	for(int i = 1 ;i <= 5;i++)
	{
		baseSprite->stopActionByTag(i);
	}
}

void BaseMonster::death()
{
	if(GameManager::getInstance()->monsterVector.contains(this))
		GameManager::getInstance()->monsterVector.eraseObject(this);
	if(getState()!=stateDeath){
		setCurrHp(0);
		setState(stateDeath);
		hpBgSprite->setVisible(false);
		baseSprite->stopAllActions();
		unscheduleUpdate();
		auto decal_blood = Sprite::createWithSpriteFrameName("decal_blood_0001.png");
		decal_blood->setPosition(Vec2(baseSprite->getContentSize().width/2,-baseSprite->getContentSize().height/4));
		baseSprite->addChild(decal_blood);
		GameManager::getInstance()->MONEY = GameManager::getInstance()->MONEY + getMoney();
		baseSprite->runAction(Animate::create(AnimationCache::getInstance()->getAnimation(getName()+"death")));
		decal_blood->runAction(Sequence::create(FadeOut::create(1.0f)
			,CallFuncN::create(CC_CALLBACK_0(BaseMonster::setVisible, this,false))
										   , NULL));
	}
}

void BaseMonster::explosion()
{
	if(GameManager::getInstance()->monsterVector.contains(this))
		GameManager::getInstance()->monsterVector.eraseObject(this);
	if(getState()!=stateDeath){

		setCurrHp(0);
		setState(stateDeath);
		hpBgSprite->setVisible(false);
		baseSprite->stopAllActions();
		unscheduleUpdate();
		auto decal_blood = Sprite::createWithSpriteFrameName("decal_blood_0001.png");
		decal_blood->setPosition(Vec2(baseSprite->getContentSize().width/2,-baseSprite->getContentSize().height/4));
		baseSprite->addChild(decal_blood);
		GameManager::getInstance()->MONEY = GameManager::getInstance()->MONEY + getMoney();
		baseSprite->runAction(Animate::create(AnimationCache::getInstance()->getAnimation("explosion_Artillery")));
		decal_blood->runAction(Sequence::create(FadeOut::create(1.0f)
											,CallFuncN::create(CC_CALLBACK_0(BaseMonster::setVisible, this,false))
										   , NULL));
	}
}

void BaseMonster::frozen()
{
	if(getState()!=stateFrozen){
		tempState = lastState;
		setState(stateFrozen);
		baseSprite->stopAllActions();
		ice = Sprite::createWithSpriteFrameName("freeze_creep_0007.png");
		ice->setPosition(Vec2(baseSprite->getContentSize().width/2,baseSprite->getContentSize().height/4));
		baseSprite->addChild(ice);
		ice->runAction(Animate::create(AnimationCache::getInstance()->getAnimation("freeze_creep")));
		scheduleOnce(CC_SCHEDULE_SELECTOR(BaseMonster::refrozen),8.0f);
	}else{
		unschedule(CC_SCHEDULE_SELECTOR(BaseMonster::refrozen));
		scheduleOnce(CC_SCHEDULE_SELECTOR(BaseMonster::refrozen),8.0f);
		ice->stopAllActions();
		ice->removeFromParent();
		ice = Sprite::createWithSpriteFrameName("freeze_creep_0007.png");
		ice->setPosition(Vec2(baseSprite->getContentSize().width/2,baseSprite->getContentSize().height/4));
		baseSprite->addChild(ice);
		ice->runAction(Animate::create(AnimationCache::getInstance()->getAnimation("freeze_creep")));
	}
}

void BaseMonster::refrozen(float dt)
{
	ice->runAction(Sequence::create(Animate::create(AnimationCache::getInstance()->getAnimation("refreeze_creep"))
										,CallFuncN::create(CC_CALLBACK_0(Sprite::removeFromParent, ice))
										,CallFuncN::create(CC_CALLBACK_0(BaseMonster::restartWalking, this))
                                       , NULL));
}

void BaseMonster::stopWalking()
{
	tempState = lastState;
	baseSprite->stopAllActions();
}

void BaseMonster::restartWalking()
{
	lastState = stateNone;
	baseSprite->stopAllActions();
	setState(tempState);

	auto tempCurrPoint = baseSprite->getPosition();
	auto duration =  tempCurrPoint.getDistance(tempNextPoint) / getRunSpeed() ;
	baseSprite->runAction(Sequence::create(MoveTo::create(duration, tempNextPoint)
                                           , CallFuncN::create(CC_CALLBACK_0(BaseMonster::runNextVec2, this))
                                         , NULL));
}

void BaseMonster::slowRunSpeed(float dt,float dis)
{
	if(!isSlowed){
		isSlowed = true;
		auto temp = this->getRunSpeed();
		this->setRunSpeed(temp - dis);
		runAction(Sequence::create(
			DelayTime::create(dt),
			CallFuncN::create(CC_CALLBACK_0(BaseMonster::setRunSpeed, this,temp)),
			CallFuncN::create(CC_CALLBACK_0(BaseMonster::setIsSlowed, this,false)),
			NULL));
	}
}

bool BaseMonster::onTouchBegan(Touch* touch, Event* event)
{
	auto target = static_cast<Sprite*>(event->getCurrentTarget());

	Vec2 locationInNode = target->convertTouchToNodeSpace(touch);

	Size size = target->getContentSize();
	Rect rect = Rect(0, 0, size.width, size.height);
	if (rect.containsPoint(locationInNode) && this->isVisible()){

		return true;
	}
	return false;
}

void BaseMonster::onTouchEnded(Touch* touch, Event* event)
{
	static_cast<BaseMap*>(this->getParent())->playerState->showMonsterInfo(this);
}