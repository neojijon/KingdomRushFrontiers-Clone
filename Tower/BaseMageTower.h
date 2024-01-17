#ifndef _BASE_MAGE_TOWER_H_
#define _BASE_MAGE_TOWER_H_
#include "cocos2d.h"
#include "Tower/BaseTower.h"
#include "Bullet/Bullet.h"
USING_NS_CC;

class BaseMageTower:public BaseTower
{
public:
	virtual void shoot(float dt);
	virtual Bullet* MageTowerBullet();

protected:
	Sprite* shooter;
	Sprite* towerBase;
	Bullet* currBullet;
	void initTower(int level);
	void addTerrain();
};
#endif