#ifndef _LEVEL_6_H_
#define _LEVEL_6_H_

#include "Map/BaseMap.h"
#include "cocos2d.h"

USING_NS_CC;

class Level6 : public BaseMap
{
public:
	Level6();
	~Level6();
	static Level6* createGame(int difficulty);
    virtual bool initWithDifficulty(int difficulty);

private:
	//void addMonsters(float dt);
	void addOrnament() override;
	void onExit() override;
	void addTerrains() override;
};

#endif