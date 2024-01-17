#ifndef _DEATH_KNIGHT_H_
#define _DEATH_KNIGHT_H_

#include "BaseSoldier.h"

class DeathKnight : public BaseSoldier
{
public:
	bool init() override;
	CREATE_FUNC(DeathKnight);
	static DeathKnight* createDeathKnight(Vec2 point);
	void update(float dt) override;
	void attackMonster(float dt) override;
	void birth(Vec2 point);
	void createAndSetHpBar() override;
};

#endif