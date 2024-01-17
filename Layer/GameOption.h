#ifndef _GAME_OPTION_H_
#define _GAME_OPTION_H_

#include "cocos2d.h"
USING_NS_CC;

class GameOption : public Layer
{
public:
	bool init() override;
    CREATE_FUNC(GameOption);
	int difficult;
	int level;
	
private:
	void initOption();
	void initButton();
	void pauseGame();
	Sprite* option;
	bool onTouchBegan(Touch* touch, Event* event) override;
	void onTouchEnded(Touch* touch, Event* event) override;
	void addOff(Sprite* target);
	void onKeyReleased(EventKeyboard::KeyCode keycode, Event* event) override;
};

#endif