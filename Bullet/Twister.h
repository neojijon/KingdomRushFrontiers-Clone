#ifndef _TWISTER_H_
#define _TWISTER_H_

#include "cocos2d.h"
#include "Bullet/Bullet.h"
#include "Monster/BaseMonster.h"

class Twister:public Bullet
{
public:
	bool init() override;
	CREATE_FUNC(Twister);
	void round();
	void attackMon();
	void hitMon(float dt);
	void move(float dt);
	void removeTwister();
	void removeTwisterAction(float dt);
	void checkNearestMonster();
	BaseMonster* nearestMonster;
};
#endif