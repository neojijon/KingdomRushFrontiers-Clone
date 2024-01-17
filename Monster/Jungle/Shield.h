#ifndef _SHIELD_H_
#define _SHIELD_H_

#include "Monster/BaseMonster.h"
#include "cocos2d.h"
USING_NS_CC;

class Shield : public BaseMonster
{
public:
	virtual bool init() override;    
	static Shield* createMonster(std::vector<Vec2> points);
};

#endif