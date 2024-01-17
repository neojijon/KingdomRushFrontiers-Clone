#ifndef _BASE_BASEARTILLERY_TOWER_H_
#define _BASE_BASEARTILLERY_TOWER_H_

#include "cocos2d.h"
#include "Tower/BaseTower.h"
#include "Bullet/Bullet.h"

USING_NS_CC;

class BaseArtilleryTower: public BaseTower
{
public:

protected:
	void initTower(int level);
	void addTerrain();
	virtual Bullet* ArtilleryTowerBullet();//�����ڵ�
	void shoot(float dt);//����
	Sprite* towerBase;//��������
	Sprite* leftShooter;//�������
	Sprite* rightShooter;//�ұ�����
	Sprite* c4;//ը��
	Sprite* barrel;//��Ͳ
	Sprite* smoke;//��
	bool isReady;//�ڵ��Ƿ������ϣ���һ�����Ƿ���꣩
	void filledAnimation();//����ڵ�����
	void fireAnimation();//�����ڵ�����
	void fire(Vec2 firePosition);//�����ڵ�
private:
	void checkNearestMonster() override;
};


#endif