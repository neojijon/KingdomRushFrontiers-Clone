#ifndef __WELCOME_SCENE_H__
#define __WELCOME_SCENE_H__

#include "cocos2d.h"
USING_NS_CC;

class WelcomeScene : public Layer
{
public:
    static cocos2d::Scene* createScene();

	bool init() override;

    CREATE_FUNC(WelcomeScene);
	void initBackGround();
	void initLogo();
	void initButton_start();
	void initLogoAnimation();
	void initButton_startAnimation();
	void initMenu_save();
	void savemenuCloseCallback(cocos2d::Ref* pSender);
	void setSaveMenuInVisible();
	void setSaveMenuVisible();
	void init_creditBtn();
	void initSoundButton();
	void init_creditBtn_startAnimation();
	void onKeyReleased(EventKeyboard::KeyCode keycode, Event* event) override;
private:
	Size visibleSize;
	Vec2 point_Logo;
	Sprite *sprite_Logo;
	Sprite *button_Start;
	Sprite *button_credit;
	Sprite *menu_Save;
	Vec2 point_Menu_Save;
	MenuItemSprite *button_Menu_Save_Close;
	Vec2 point_Button_Menu_Save_Close;
	void onEnterTransitionDidFinish() override;
};

#endif