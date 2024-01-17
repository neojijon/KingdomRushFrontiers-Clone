#ifndef _QUETZAL_H_
#define _QUETZAL_H_

#include "Monster/BaseMonster.h"
#include "cocos2d.h"
USING_NS_CC;

class Quetzal : public BaseMonster
{
public:
	virtual bool init() override;    
	static Quetzal* createMonster(std::vector<Vec2> points);
};

#endif