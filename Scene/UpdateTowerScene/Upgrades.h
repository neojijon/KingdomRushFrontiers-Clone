#ifndef __UPGRADES_H__
#define __UPGRADES_H__

#include "cocos2d.h"
#include "Icons.h"

USING_NS_CC;

class Upgrades :public Layer
{
public:
	
	static Scene* createScene();
	bool init() override;
	CREATE_FUNC(Upgrades);
	/*��ʼ��״̬*/
	void initalState();

	//����ԭʼ״̬
	void initalOriginalSta();

	/*������������*/
protected:
	/*��������״̬*/
	Icons::IconsStatus iconSta[5][6];
	/*����ԭʼ״̬*/
	Icons::IconsStatus iconInitSta[5][6];
	/*���涯̬������ͼ��ľ������*/
	Icons* icons[5][6];
	/*��һ�ε����ͼ��*/
	Icons* lastSelectedIcon;
	Icons* selectedIcon;


	/*��������*/
	int startAll;
	/*ʣ������*/
	int startLeft;
	Label* lastStartLabel;
	
	/*������������*/
	Label* upNeedStartLabel;
	

	//��ʾѡ��icon����
	Label* iconNameLabel;
	//��ʾicon������Ϣ
	Label* iconIntroductionLabel;

	/*��ʾ�����ͼ��*/
	Sprite* iconDisplay;

	/*��ʾ����ť*/
	Sprite* buyButten;
	void showStart();
	void showTips();
	void showBuyBut(Icons* iconSelect);
	void done();

	bool onIconTouchBegan(Touch* , Event* );
	void onTouchEnded(Touch* , Event* ) override;

	bool onBuyButTouchBegan(Touch* , Event* );
	void onBuyButTouchEnded(Touch* , Event* );

	//����Ϊԭʼδ����״̬
	bool resetSta(Touch* touch , Event* event);
	void resetStaEnded(Touch* , Event* );
	void onKeyReleased(EventKeyboard::KeyCode keycode, Event* event) override;

	bool onConfirmTouchBegan(Touch* touch,Event* event);
	void onConfirmTouchEnded(Touch* touch,Event* event);
};

#endif