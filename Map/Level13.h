#ifndef _LEVEL_13_H_
#define _LEVEL_13_H_

#include "Map/BaseMap.h"
#include "cocos2d.h"

USING_NS_CC;

class Level13 : public BaseMap
{
public:
	Level13();
	~Level13();
	static Level13* createGame(int difficulty);
    virtual bool initWithDifficulty(int difficulty);

private:
	void addOrnament() override;
	void onExit() override;
	void addTerrains() override;
};

#endif