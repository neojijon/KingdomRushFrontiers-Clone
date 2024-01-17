#include "BaseArrowTower.h"
#include "Data/GameManager.h"

void BaseArrowTower::initTower(int level)
{
	towerBase = Sprite::createWithSpriteFrameName(cocos2d::StringUtils::format("archer_tower_000%d.png",level));

	shooter_1 = Sprite::createWithSpriteFrameName(cocos2d::StringUtils::format("tower_archer_lvl%d_shooter_0001.png",level));
	shooter_2 = Sprite::createWithSpriteFrameName(cocos2d::StringUtils::format("tower_archer_lvl%d_shooter_0001.png",level));

	shooter_1->setPosition(Vec2(towerBase->getContentSize().width/2-10,towerBase->getContentSize().height/2+18));
	shooter_2->setPosition(Vec2(towerBase->getContentSize().width/2+10,towerBase->getContentSize().height/2+18));

	towerBase->addChild(shooter_1);
	towerBase->addChild(shooter_2);

	addChild(towerBase);

	shootTag = RIGHT_ARCHER_SHOT;
}

void BaseArrowTower::addTerrain()
{
	terrain = Sprite::createWithSpriteFrameName("terrain_archer_0004.png");
	terrain->setAnchorPoint(Vec2(0.5,1));
	addChild(terrain,-1);
}

Bullet* BaseArrowTower::ArrowTowerBullet()
{
    return NULL;
}

void BaseArrowTower::shoot(float dt)
{
    auto instance = GameManager::getInstance();
   // auto bulletVector = instance->bulletVector;
	checkNearestMonster();
	char temp1[20]; 
	sprintf(temp1, "level%d_shoot_down", level); 
	char temp2[20]; 
	sprintf(temp2, "level%d_shoot_top", level); 
	if(nearestMonster!=NULL && nearestMonster->getCurrHp() > 0 )
    {
		auto currBullet = ArrowTowerBullet();
		//instance->bulletVector.pushBack(currBullet);

		Vec2 shootVector = nearestMonster->baseSprite->getPosition() - this->getParent()->getPosition();


		float startAngle = currBullet->getRotation();
		float endAngle = 0;

		auto pVectr = currBullet->getPosition()-shootVector;
        float angleRadians=atan(pVectr.y/pVectr.x);
        float angleDegrees = CC_RADIANS_TO_DEGREES(angleRadians);
		
		if(shootVector.x - currBullet->getPosition().x<=0)//���󹥻�
		{
			startAngle = startAngle + abs(angleDegrees);//��ʼ�����Ƕ�
			endAngle = -90;//�����Ƕ�
			if(shootTag == 1)//�ֵ�1�Ź�����
			{
				currBullet->setPosition(Vec2(0,30));//�ӵ������ڹ���������λ��	
				shooter_1->setFlippedX(true);
				if(shootVector.y - currBullet->getPosition().y<=0)
				{
					//��������
					shooter_1->runAction(Animate::create(AnimationCache::getInstance()->getAnimation(temp1)));
				}else{
					shooter_1->runAction(Animate::create(AnimationCache::getInstance()->getAnimation(temp2)));
				}
				shootTag = 2;
			}
			else//�ֵ�2�Ź�����
			{
				currBullet->setPosition(Vec2(10,30));		
				shooter_2->setFlippedX(true);
				if(shootVector.y - currBullet->getPosition().y<=0)
				{
					shooter_2->runAction(Animate::create(AnimationCache::getInstance()->getAnimation(temp1)));
				}else{
					shooter_2->runAction(Animate::create(AnimationCache::getInstance()->getAnimation(temp2)));
				}
				shootTag = 1;
			}
		}else
		{
			startAngle = startAngle - abs(angleDegrees);
			endAngle = 270;
			if(shootTag == 1)
			{
				currBullet->setPosition(Vec2(0,30));		
				shooter_1->setFlippedX(false);
				if(shootVector.y - currBullet->getPosition().y<=0)
				{
					shooter_1->runAction(Animate::create(AnimationCache::getInstance()->getAnimation(temp1)));
				}else{
					shooter_1->runAction(Animate::create(AnimationCache::getInstance()->getAnimation(temp2)));
				}
				shootTag = 2;
			}
			else
			{
				currBullet->setPosition(Vec2(10,30));		
				shooter_2->setFlippedX(false);
				if(shootVector.y - currBullet->getPosition().y<=0)
				{
					shooter_2->runAction(Animate::create(AnimationCache::getInstance()->getAnimation(temp1)));
				}else{
					shooter_2->runAction(Animate::create(AnimationCache::getInstance()->getAnimation(temp2)));
				}
				shootTag = 1;
			}
		}
		//����
		ccBezierConfig bezier;
		if(shootTag == 1)
			SoundManager::playArrowShoot1();
		else
			SoundManager::playArrowShoot2();
		//�������Ƶ�
		bezier.controlPoint_1 = Vec2(currBullet->getPosition().x,currBullet->getPosition().y+200); 
		bezier.controlPoint_2 = Vec2(shootVector.x,shootVector.y+200);; 
		bezier.endPosition = shootVector;

		auto action = Spawn::create(BezierTo::create(0.5f, bezier),RotateTo::create(0.5f,endAngle),NULL);
		//�������Ը�����
		currBullet->setBulletAction(action);
		currBullet->shoot();
		currBullet = NULL;
	}
}