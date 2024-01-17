#include "Level6.h"

USING_NS_CC;

Level6::Level6()
{};

Level6::~Level6(){};

bool Level6::initWithDifficulty(int difficulty)
{
    if ( !Layer::init() )
    {
        return false;
    }

	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("sprite_level6-hd.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("sprite_level6_2-hd.plist");
	setLevel(6);
	this->difficulty = difficulty;
	initMap();
	
	std::vector<Vec2> points;
	points.push_back(Vec2(40,360));
	points.push_back(Vec2(40,610));
	points.push_back(Vec2(756,940));
	points.push_back(Vec2(1145,560));
	addWaveProgressBars(points);
	waveFlags.at(0)->restartWaveFlag();
	waveFlags.at(1)->restartWaveFlag();
	waveFlags.at(2)->restartWaveFlag();
	waveFlags.at(3)->restartWaveFlag();
	SoundManager::playJungleBattle();
	return true;
}

Level6* Level6::createGame(int difficulty)
{  
    auto layer = new Level6();
	if(layer && layer->initWithDifficulty(difficulty)){
		layer->autorelease();
		return layer;
	}
	CC_SAFE_DELETE(layer);

    return NULL;
}

void Level6::addOrnament()
{

}

void Level6::onExit()
{
	SpriteFrameCache::getInstance()->removeSpriteFrameByName("sprite_Level6-hd.plist");
	SpriteFrameCache::getInstance()->removeSpriteFrameByName("sprite_Level6_2-hd.plist");

	Layer::onExit();
}

void Level6::addTerrains()
{
	auto terrain1 = CustomTerrain::createTerrain(2);
	terrain1->setPosition(Vec2(350,690));
	terrain1->setTag(1);
	addChild(terrain1,4);

	auto terrain2 = CustomTerrain::createTerrain(2);
	terrain2->setPosition(Vec2(815,750));
	terrain2->setTag(2);
	addChild(terrain2,3);

	auto terrain3 = CustomTerrain::createTerrain(2);
	terrain3->setPosition(Vec2(275,510));
	terrain3->setTag(3);
	addChild(terrain3,5);

	auto terrain4 = CustomTerrain::createTerrain(2);
	terrain4->setPosition(Vec2(670,520));
	terrain4->setTag(4);
	addChild(terrain4,5);

	auto terrain5 = CustomTerrain::createTerrain(2);
	terrain5->setPosition(Vec2(960,575));
	terrain5->setTag(5);
	addChild(terrain5,5);

	auto terrain6 = CustomTerrain::createTerrain(2);
	terrain6->setPosition(Vec2(750,450));
	terrain6->setTag(6);
	addChild(terrain6,6);

	auto terrain7 = CustomTerrain::createTerrain(2);
	terrain7->setPosition(Vec2(535,350));
	terrain7->setTag(7);
	addChild(terrain7,7);

	auto terrain8 = CustomTerrain::createTerrain(2);
	terrain8->setPosition(Vec2(820,380));
	terrain8->setTag(8);
	addChild(terrain8,7);

	auto terrain9 = CustomTerrain::createTerrain(2);
	terrain9->setPosition(Vec2(1080,370));
	terrain9->setTag(9);
	addChild(terrain9,7);

	auto terrain10 = CustomTerrain::createTerrain(2);
	terrain10->setPosition(Vec2(810,190));
	terrain10->setTag(10);
	addChild(terrain10,9);

}
