#ifndef _ELITE_H_
#define _ELITE_H_

#include "Monster/BaseMonster.h"
#include "cocos2d.h"
USING_NS_CC;

class Elite : public BaseMonster
{
public:
	virtual bool init() override;    
	static Elite* createMonster(std::vector<Vec2> points);
};

#endif