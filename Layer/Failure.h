#include "cocos2d.h"

USING_NS_CC;

class Failure : public Layer
{

public:

	bool init() override;
	void initMap();
	void starMenu(Ref *pSpender);
	void callBackMenu(Ref *pSpender);
	void getItemMenu(Ref *pSpender);
	CREATE_FUNC(Failure);
	int level;
	int difficulty;
	
private:
	void pauseGame();
	void initOption();
	Sprite* option;
	bool onTouchBegan(Touch* touch, Event* event) override;
	void onTouchEnded(Touch* touch, Event* event) override;
};