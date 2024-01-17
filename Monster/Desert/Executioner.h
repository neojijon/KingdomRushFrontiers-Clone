#ifndef _EXECUTIONER_H_
#define _EXECUTIONER_H_

#include "Monster/BaseMonster.h"
#include "cocos2d.h"

USING_NS_CC;

class Executioner : public BaseMonster
{
public:
   virtual bool init() override;
    
   static Executioner* createMonster(std::vector<Vec2> points);
};

#endif