#ifndef _GROUP_MONSTER_H_
#define _GROUP_MONSTER_H_

#include "cocos2d.h"

USING_NS_CC;

class GroupMonster: public Node
{
public:     
   // virtual bool init();
    static GroupMonster* initGroupEnemy(int type, int road, int path);
    CREATE_FUNC(GroupMonster);  
	//�����������
	CC_SYNTHESIZE(int, type, Type);
	//��ͬ����
	CC_SYNTHESIZE(int, road, Road);
	//��ͬ·��
	CC_SYNTHESIZE(int, path, Path);
};

#endif