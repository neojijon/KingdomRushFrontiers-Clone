#ifndef _CHOOSE_DIFFICULTY_H_
#define _CHOOSE_DIFFICULTY_H_
#include "cocos2d.h"

USING_NS_CC;

class ChooseDifficulty : public Layer
{
public:
    static Scene* createSceneWithLevel(int level);
	bool init() override;
	void menuCallback(Ref* pSpender);  //�رհ�ť������һ����
	void menuCallnext(Ref* pSpender);  //��ʼս����ť������һ����
	void starMenuCallback1(Ref* pSpender);
	void starMenuCallback2(Ref* pSpender);
	void starMenuCallback3(Ref* pSpender);
	int level;
	int difficulty;
	void initWithLevel(int level);
	void setBadges(int star);

protected:
	 void onKeyReleased(EventKeyboard::KeyCode keycode, Event* event) override;
	 MenuItemToggle *toggleItem1; //��ս��ť
	 MenuItemToggle *toggleItem2; //Ӣ��ģʽ��ť
	 MenuItemToggle *toggleItem3; //����ģʽ��ť
	 std::string blueStrTop;
	 Sprite* star1;
	 Sprite* star2;
	 Sprite* star3;
	 Sprite* star4;
	 Sprite* star5;

	 Label *blueLabel; //��ɫ�����ǩ
	 Label *blackLabel;//��ɫ�����ǩ

	 std::string blueStr[3]; //����ɫ��������Ϊһ������
	 std::string blackStr[3]; //����ɫ��������Ϊһ������

	 MenuItemToggle *imgItem1;

	  Size visibleSize;
	  Sprite *modeRulesSprite1;
	  Sprite *modeRulesSprite2;
	  Sprite *modeRulesSprite3;
	  Sprite *modeRulesSprite4;

      CREATE_FUNC(ChooseDifficulty);


};

#endif