#ifndef _LEVEL_1_H_
#define _LEVEL_1_H_

#include "Map/BaseMap.h"
#include "cocos2d.h"

USING_NS_CC;

class Level1 : public BaseMap
{
public:
	Level1();
	~Level1();
	static Level1* createGame(int difficulty);
    virtual bool initWithDifficulty(int difficulty);
private:
	//��Ӳ�ͬ�ؿ�������װ����
	void addOrnament() override;
	void onExit() override;
	//void addMonsters(float dt);
	void addTerrains() override;
};

#endif