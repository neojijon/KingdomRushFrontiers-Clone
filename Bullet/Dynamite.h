#ifndef _DYNAMITE_H_
#define _DYNAMITE_H_

#include "cocos2d.h"
#include "Bullet/Bullet.h"

USING_NS_CC;

class Dynamite : public Bullet
{
public:
	bool init() override;
    CREATE_FUNC(Dynamite);
	void shoot(Vec2 point);
	void removeBullet() override;
private:
	
};

#endif