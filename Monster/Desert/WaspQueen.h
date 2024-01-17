#ifndef _WASPQUEEN_H_
#define _WASPQUEEN_H_

#include "Monster/BaseMonster.h"
#include "cocos2d.h"
USING_NS_CC;

class WaspQueen : public BaseMonster
{
public:
	virtual bool init() override;    
	//static WaspQueen* createMonster(std::vector<Vec2> points, int hp ,int value);
	static WaspQueen* createMonster(std::vector<Vec2> points);
	void refrozen(float dt) override;
	void frozen() override;
};

#endif