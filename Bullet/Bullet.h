#ifndef _BULLET_H_
#define _BULLET_H_

#include "Data/SoundManager.h"
#include "cocos2d.h"
#include "Data/GameManager.h"

USING_NS_CC;

class Bullet : public Sprite
{
public:
	 Bullet();
    ~Bullet();
	bool init() override;
    CREATE_FUNC(Bullet);

protected:
	CC_SYNTHESIZE(int, maxForce, MaxForce);
	CC_SYNTHESIZE(int, bulletScope, BulletScope);//�����ӵ�������Χ
	CC_SYNTHESIZE(int, bulletType, BulletType);
	CC_SYNTHESIZE(Spawn*, bulletAction, BulletAction);
	Sprite* sprite;
	virtual void shoot(){};
	virtual void removeBullet(){};
};

#endif