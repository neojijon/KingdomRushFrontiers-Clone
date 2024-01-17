#ifndef _CANIBAL_H_
#define _CANIBAL_H_

#include "Monster/BaseMonster.h"
#include "cocos2d.h"
USING_NS_CC;

class Canibal : public BaseMonster
{
public:
	virtual bool init() override;    
	static Canibal* createMonster(std::vector<Vec2> points);
};

#endif