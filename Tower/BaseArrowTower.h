#ifndef _BASE_ARROW_TOWER_H_
#define _BASE_ARROW_TOWER_H_

#include "cocos2d.h"
#include "Tower/BaseTower.h"
#include "Bullet/Bullet.h"

#define LEFT_ARCHER_SHOT 1
#define RIGHT_ARCHER_SHOT 1

USING_NS_CC;

class BaseArrowTower: public BaseTower
{
public:
	virtual Bullet* ArrowTowerBullet();
	virtual void shoot(float dt);
protected:
	Sprite* shooter_1;
	Sprite* shooter_2;
	Sprite* towerBase;
	int shootTag;
	void initTower(int level);
	void addTerrain();	
	
};


#endif