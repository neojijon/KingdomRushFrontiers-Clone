#ifndef _GORILLA_H_
#define _GORILLA_H_

#include "Monster/BaseMonster.h"
#include "cocos2d.h"
USING_NS_CC;

class Gorilla : public BaseMonster
{
public:
	virtual bool init() override;    
	static Gorilla* createMonster(std::vector<Vec2> points);
};

#endif