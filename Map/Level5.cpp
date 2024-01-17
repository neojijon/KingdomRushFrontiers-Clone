#include "Level5.h"
#include "Data/MyAnimation.h"

USING_NS_CC;

Level5::Level5()
{};

Level5::~Level5(){};

bool Level5::initWithDifficulty(int difficulty)
{
    if ( !Layer::init() )
    {
        return false;
    }
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("sprite_level5-hd.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("sprite_level5_2-hd.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("sprite_level5_3-hd.plist");
	MyAnimation::getInstance()->init_BossEfreeti();
	setLevel(5);
	this->difficulty = difficulty;
	initMap();
	//OΪ����1 1Ϊ�ң�2Ϊ����2,3Ϊ��
	std::vector<Vec2> points;
	points.push_back(Vec2(40,637));
	points.push_back(Vec2(1140,490));
	points.push_back(Vec2(40,450));
	addWaveProgressBars(points);
	waveFlags.at(0)->restartWaveFlag();
	waveFlags.at(1)->restartWaveFlag();
	waveFlags.at(2)->restartWaveFlag();
	SoundManager::playDesertBattle();
	return true;
}

void Level5::beforeBoss()
{
	this->runAction(MoveTo::create(0.5f,Vec2(0,Director::getInstance()->getVisibleSize().height-1000)));
}

Level5* Level5::createGame(int difficulty)
{  
    auto layer = new Level5();
	if(layer && layer->initWithDifficulty(difficulty)){
		layer->autorelease();
		return layer;
	}
	CC_SAFE_DELETE(layer);

    return NULL;
}

void Level5::addOrnament()
{
	door = Sprite::createWithSpriteFrameName("Stage5_door_0001.png");
	door->setPosition(Vec2(670,850));
	addChild(door);
}

void Level5::waveEvent()
{
	if(wave == 1){
		beforeBoss();
		Vector<SpriteFrame*> animFrames1;
		SpriteFrame* frame1=NULL;
		for (int i = 1; i <= 36; i++)
		{
			frame1 = SpriteFrameCache::getInstance()->getSpriteFrameByName(cocos2d::StringUtils::format("Stage5_door_00%02d.png",i));
			if(frame1!=nullptr)
				animFrames1.pushBack(frame1);
		}
		auto doorAnimation = Animation::createWithSpriteFrames(animFrames1, 0.04f);
		
		door->runAction(Sequence::create(
			CallFuncN::create(CC_CALLBACK_0(Level5::eyeEffect,this)),
			DelayTime::create(4.0f),
			Animate::create(doorAnimation),
			CallFuncN::create(CC_CALLBACK_0(Level5::stonesEffect,this)),
			NULL));
		schedule(CC_SCHEDULE_SELECTOR(Level5::addMonsters), 1.0f, waveVector.at(wave).size(), 6.0f);
	}else{
		schedule(CC_SCHEDULE_SELECTOR(Level5::addMonsters), 1.0f, waveVector.at(wave).size(), 0.0f);
	}
}

void Level5::eyeEffect()
{
	auto eyeEffect = Sprite::createWithSpriteFrameName("Stage5_door_eyes_effect_0001.png");
	Vector<SpriteFrame*> animFrames;
	SpriteFrame* frame=NULL;
	for (int i = 1; i <= 94; i++){
		frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(cocos2d::StringUtils::format("Stage5_door_eyes_00%02d.png",i));
		if(frame!=nullptr)
		animFrames.pushBack(frame);
	}
	auto eyeAnimation = Animation::createWithSpriteFrames(animFrames, 0.04f);
	eyeEffect->setPosition(Vec2(95,70));
	door->addChild(eyeEffect);
	eyeEffect->runAction(Animate::create(eyeAnimation));
}

void Level5::stonesEffect()
{
	auto stone = Sprite::createWithSpriteFrameName("Stage5_door_stones_0001.png");
	Vector<SpriteFrame*> animFrames;
	SpriteFrame* frame = NULL;
	for (int i = 1; i <= 94; i++){
		frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(cocos2d::StringUtils::format("Stage5_door_stones_00%02d.png",i));
		if(frame!=nullptr)
		animFrames.pushBack(frame);
	}
	auto stoneAnimation = Animation::createWithSpriteFrames(animFrames, 0.04f);
	stone->setPosition(Vec2(670,850));
	addChild(stone);
	stone->runAction(Animate::create(stoneAnimation));
}

void Level5::addTerrains()
{
	auto terrain14 = CustomTerrain::createTerrain(1);
	terrain14->setPosition(Vec2(311,712));
	terrain14->setTag(14);
	addChild(terrain14,3);

	auto terrain3 = CustomTerrain::createTerrain(1);
	terrain3->setPosition(Vec2(687,606));
	terrain3->setTag(3);
	addChild(terrain3,4);

	auto terrain11 = CustomTerrain::createTerrain(1);
	terrain11->setPosition(Vec2(435,550));
	terrain11->setTag(11);
	addChild(terrain11,5);

	auto terrain12 = CustomTerrain::createTerrain(1);
	terrain12->setPosition(Vec2(300,550));
	terrain12->setTag(12);
	addChild(terrain12,5);

	auto terrain13 = CustomTerrain::createTerrain(1);
	terrain13->setPosition(Vec2(170,550));
	terrain13->setTag(13);
	addChild(terrain13,5);


	auto terrain1 = CustomTerrain::createTerrain(1);
	terrain1->setPosition(Vec2(858,466));
	terrain1->setTag(1);
	addChild(terrain1,6);

	auto terrain4 = CustomTerrain::createTerrain(1);
	terrain4->setPosition(Vec2(631,474));
	terrain4->setTag(4);
	addChild(terrain4,6);

	auto terrain8 = CustomTerrain::createTerrain(1);
	terrain8->setPosition(Vec2(558,390));
	terrain8->setTag(8);
	addChild(terrain8,7);

	auto terrain9 = CustomTerrain::createTerrain(1);
	terrain9->setPosition(Vec2(446,373));
	terrain9->setTag(9);
	addChild(terrain9,7);

	auto terrain10 = CustomTerrain::createTerrain(1);
	terrain10->setPosition(Vec2(316,374));
	terrain10->setTag(10);
	addChild(terrain10,7);

	auto terrain5 = CustomTerrain::createTerrain(1);
	terrain5->setPosition(Vec2(668,343));
	terrain5->setTag(5);
	addChild(terrain5,7);

	auto terrain6 = CustomTerrain::createTerrain(1);
	terrain6->setPosition(Vec2(747,305));
	terrain6->setTag(6);
	addChild(terrain6,7);

	auto terrain7 = CustomTerrain::createTerrain(1);
	terrain7->setPosition(Vec2(851,290));
	terrain7->setTag(7);
	addChild(terrain7,8);

}

void Level5::onExit()
{
	SpriteFrameCache::getInstance()->removeSpriteFrameByName("sprite_Level5_3-hd.plist");
	SpriteFrameCache::getInstance()->removeSpriteFrameByName("sprite_Level5_2-hd.plist");
	SpriteFrameCache::getInstance()->removeSpriteFrameByName("sprite_level5-hd.plist");

	Layer::onExit();
}
