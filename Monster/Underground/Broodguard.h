#ifndef _BROODGUARD_H_
#define _BROODGUARD_H_

#include "Monster/BaseMonster.h"
#include "cocos2d.h"
USING_NS_CC;

class Broodguard : public BaseMonster
{
public:
	virtual bool init() override;    
	static Broodguard* createMonster(std::vector<Vec2> points);
};

#endif