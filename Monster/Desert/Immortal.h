#ifndef _IMMORTAL_H_
#define _IMMORTAL_H_

#include "Monster/BaseMonster.h"
#include "cocos2d.h"

USING_NS_CC;

class Immortal : public BaseMonster
{
public:
   virtual bool init() override;
    
   static Immortal* createMonster(std::vector<Vec2> points);
   void death() override;
   void explosion() override;
   Vec2 nextVec2();
};

#endif