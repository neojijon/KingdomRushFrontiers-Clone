#include "Level7.h"

USING_NS_CC;

Level7::Level7()
{};

Level7::~Level7(){};

bool Level7::initWithDifficulty(int difficulty)
{
    if ( !Layer::init() )
    {
        return false;
    }
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("sprite_level7-hd.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("sprite_level7_2-hd.plist");
	setLevel(7);
	this->difficulty = difficulty;
	initMap();

	std::vector<Vec2> points;
	points.push_back(Vec2(1160,340));
	points.push_back(Vec2(1160,680));
	addWaveProgressBars(points);
	waveFlags.at(0)->restartWaveFlag();
	waveFlags.at(1)->restartWaveFlag();

	SoundManager::playJungleBattle();
	return true;
}

Level7* Level7::createGame(int difficulty)
{  
    auto layer = new Level7();
	if(layer && layer->initWithDifficulty(difficulty)){
		layer->autorelease();
		return layer;
	}
	CC_SAFE_DELETE(layer);

    return NULL;
}

void Level7::addOrnament()
{
	auto bridge=Sprite::createWithSpriteFrameName("Stage6_Bridge_0001.png");
	bridge->setPosition(Vec2(760,670));
	addChild(bridge);
}

void Level7::onExit()
{
	SpriteFrameCache::getInstance()->removeSpriteFrameByName("sprite_Level7-hd.plist");
	SpriteFrameCache::getInstance()->removeSpriteFrameByName("sprite_Level7_2-hd.plist");

	Layer::onExit();
}

void Level7::addTerrains()
{
	auto terrain1 = CustomTerrain::createTerrain(2);
	terrain1->setPosition(Vec2(325,770));
	terrain1->setTag(1);
	addChild(terrain1,3);

	auto terrain2 = CustomTerrain::createTerrain(2);
	terrain2->setPosition(Vec2(535,765));
	terrain2->setTag(2);
	addChild(terrain2,3);

	auto terrain3 = CustomTerrain::createTerrain(2);
	terrain3->setPosition(Vec2(410,600));
	terrain3->setTag(3);
	addChild(terrain3,4);

	auto terrain4 = CustomTerrain::createTerrain(2);
	terrain4->setPosition(Vec2(570,600));
	terrain4->setTag(4);
	addChild(terrain4,4);

	auto terrain5 = CustomTerrain::createTerrain(2);
	terrain5->setPosition(Vec2(930,600));
	terrain5->setTag(5);
	addChild(terrain5,4);

	auto terrain6 = CustomTerrain::createTerrain(2);
	terrain6->setPosition(Vec2(290,460));
	terrain6->setTag(6);
	addChild(terrain6,6);

	auto terrain7 =CustomTerrain::createTerrain(2);
	terrain7->setPosition(Vec2(475,355));
	terrain7->setTag(7);
	addChild(terrain7,7);

	auto terrain8 = CustomTerrain::createTerrain(2);
	terrain8->setPosition(Vec2(685,420));
	terrain8->setTag(8);
	addChild(terrain8,6);

	auto terrain9 = CustomTerrain::createTerrain(2);
	terrain9->setPosition(Vec2(920,420));
	terrain9->setTag(9);
	addChild(terrain9,6);

	auto terrain10 = CustomTerrain::createTerrain(2);
	terrain10->setPosition(Vec2(630,220));
	terrain10->setTag(10);
	addChild(terrain10,8);


}
