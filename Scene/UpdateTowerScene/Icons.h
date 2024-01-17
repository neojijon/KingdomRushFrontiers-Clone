#ifndef __ICONS_H__
#define __ICONS_H__

#include "cocos2d.h"

USING_NS_CC;
class Icons: public Sprite
{
public :
	enum IconsStatus{eIconOff,eIconOn,eIconOK};
    virtual bool initNewIcons(std::string picture,std::string off_picture,std::string iconName,
		std::string iconIntroduction,int startNum,Icons::IconsStatus iconSta,int row,int column);


	static Icons* createNewIcons(std::string picture,std::string off_picture,std::string iconName,
		std::string iconIntroduction,int startNum,Icons::IconsStatus iconSta,int row,int column);
    CREATE_FUNC(Icons);


	void showIcon(Icons::IconsStatus iconSta);
	int priceTag;
	Sprite* icon;
	Sprite* iconSelected;
	void iconIsSelect(bool select);
	
	std::string iconName;
	std::string iconIntroduction;
	int iconRow;
	int	iconColumn;


	IconsStatus getIconState();
	void setMayUpedate();
	void setUpdated();
protected:
	IconsStatus iconSta;
	Sprite* iconOKBack;
	
	std::string picture;
	std::string off_picture;

};

#endif