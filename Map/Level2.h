#ifndef _LEVEL_2_H_
#define _LEVEL_2_H_

#include "Map/BaseMap.h"
#include "cocos2d.h"

USING_NS_CC;

class Level2 : public BaseMap
{
public:
	Level2();
	~Level2();
	static Level2* createGame(int difficulty);
    virtual bool initWithDifficulty(int difficulty);

private:
	//void addMonsters(float dt);
	void addOrnament() override;
	void onExit() override;
	void addTerrains() override;
};

#endif