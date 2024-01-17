#ifndef _FALLEN_H_
#define _FALLEN_H_

#include "Monster/BaseMonster.h"
#include "cocos2d.h"

USING_NS_CC;

class Fallen : public BaseMonster
{
public:
   virtual bool init() override;
    
   static Fallen* createMonster(std::vector<Vec2> points);
   static Fallen* createMonster(std::vector<Vec2> points,Vec2 birthLocation,int pointCounter);
   void birth(Vec2 birthLocation,int pointCounter);
};

#endif