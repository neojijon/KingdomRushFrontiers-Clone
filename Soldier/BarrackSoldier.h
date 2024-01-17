#ifndef _BARRACK_Soldier_H_
#define _BARRACK_Soldier_H_

#include "BaseSoldier.h"

class BarrackSoldier : public BaseSoldier
{
public:
	bool initSoldier(int level);
	CREATE_FUNC(BarrackSoldier);
	static BarrackSoldier* createSoldier(Vec2 point,int level);
	CC_SYNTHESIZE(int, level, Level);
	void update(float dt) override;
	//void runToMonster();
	void attackMonster(float dt) override;
	void updateSoldier(int level) override;
};

#endif