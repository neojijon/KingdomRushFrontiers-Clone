#ifndef _NIGHTSCALE_H_
#define _NIGHTSCALE_H_

#include "Monster/BaseMonster.h"
#include "cocos2d.h"
USING_NS_CC;

class Nightscale : public BaseMonster
{
public:
	virtual bool init() override;    
	static Nightscale* createMonster(std::vector<Vec2> points);
};

#endif