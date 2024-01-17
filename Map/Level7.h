#ifndef _LEVEL_7_H_
#define _LEVEL_7_H_

#include "Map/BaseMap.h"
#include "cocos2d.h"

USING_NS_CC;

class Level7 : public BaseMap
{
public:
	Level7();
	~Level7();
	static Level7* createGame(int difficulty);
    virtual bool initWithDifficulty(int difficulty);

private:
	//void addMonsters(float dt);
	void addOrnament() override;
	void onExit() override;
	void addTerrains() override;
};

#endif