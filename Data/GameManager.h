#ifndef _GAMEMANAGER_H_
#define _GAMEMANAGER_H_

//#include "Bullet/Bullet.h"
#include "cocos2d.h"
#include "Monster/BaseMonster.h"
#include "Tower/BaseTower.h"
#include "Layer/TouchLayer.h"

USING_NS_CC;

class GameManager
{
public:
    //void CreateGameManager(int slot);

    Vector<BaseMonster*> monsterVector;
	static GameManager* getInstance();


	char SLOTX_ISEXIT[20];

	char LEVELX_ISDOWN[20];

	char LEVELX_STARNUM[20];
	char SLOTX_STARLEFT[20];
	char SLOTX_DOWNCOUNT[20];

	char LEVELX_NEWDOWN[20];

	char SLOTX_STAR[20];

	char SLOTX_SHOP[20];

	char SLOTX_GEM[20];
	int SLOTNUM;
	int MONEY;
	int LIFE;
	
	int LEVEL;

	void setInstance(int tag);
	static void eraseAll();
private:
	static GameManager * instance;
};
#endif   
