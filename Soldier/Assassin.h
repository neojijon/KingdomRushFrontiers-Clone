#ifndef _ASSASSIN_H_
#define _ASSASSIN_H_

#include "BaseSoldier.h"

class Assassin : public BaseSoldier
{
public:
	bool initAssassin();
	CREATE_FUNC(Assassin);
	static Assassin* createAssassin(Vec2 location);
	void createAndSetHpBar() override;
	void cheakState();
	void update(float dt) override;
	//void runToMonster();
	void attackMonster(float dt) override;
};

#endif