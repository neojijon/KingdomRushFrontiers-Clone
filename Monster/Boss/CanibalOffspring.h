#ifndef _CANIBAL_OFF_SPRING_H_
#define _CANIBAL_OFF_SPRING_H_

#include "Monster/BaseMonster.h"
#include "cocos2d.h"
USING_NS_CC;

class CanibalOffspring : public BaseMonster
{
public:
	virtual bool init() override;    
	static CanibalOffspring* createMonster(std::vector<Point> points,int pointCounter);
	void getHurt() override;
	void death() override;
	void explosion() override;
};

#endif