#include "Level11.h"

USING_NS_CC;

Level11::Level11()
{};

Level11::~Level11(){};

bool Level11::initWithDifficulty(int difficulty)
{
    if ( !Layer::init() )
    {
        return false;
    }
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("sprite_Level11-hd.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("sprite_Level11_2-hd.plist");
	
	setLevel(11);
	this->difficulty = difficulty;
	initMap();
	
	std::vector<Vec2> points;
	points.push_back(Vec2(343,710));
	points.push_back(Vec2(878,820));
	points.push_back(Vec2(1140,750));
	points.push_back(Vec2(1100,480));
	points.push_back(Vec2(700,40));
	addWaveProgressBars(points);
	waveFlags.at(0)->restartWaveFlag();
	waveFlags.at(1)->restartWaveFlag();
	waveFlags.at(2)->restartWaveFlag();
	waveFlags.at(3)->restartWaveFlag();
	waveFlags.at(4)->restartWaveFlag();
	SoundManager::playDesertBattle();
	return true;
}

Level11* Level11::createGame(int difficulty)
{  
    auto layer = new Level11();
	if(layer && layer->initWithDifficulty(difficulty)){
		layer->autorelease();
		return layer;
	}
	CC_SAFE_DELETE(layer);

    return NULL;
}

void Level11::addOrnament()
{

}

void Level11::onExit()
{
	SpriteFrameCache::getInstance()->removeSpriteFrameByName("sprite_Level11-hd.plist");
	SpriteFrameCache::getInstance()->removeSpriteFrameByName("sprite_Level11_2-hd.plist");

	Layer::onExit();
}

void Level11::addTerrains()
{
	auto terrain1 = CustomTerrain::createTerrain(3);
	terrain1->setPosition(Vec2(850,710));
	terrain1->setTag(1);
	addChild(terrain1,3);
	
	auto terrain2 = CustomTerrain::createTerrain(3);
	terrain2->setPosition(Vec2(500,610));
	terrain2->setTag(2);
	addChild(terrain2,4);

	auto terrain3 = CustomTerrain::createTerrain(3);
	terrain3->setPosition(Vec2(220,510));
	terrain3->setTag(3);
	addChild(terrain3,5);

	auto terrain4 = CustomTerrain::createTerrain(3);
	terrain4->setPosition(Vec2(780,540));
	terrain4->setTag(4);
	addChild(terrain4,5);

	auto terrain5 = CustomTerrain::createTerrain(3);
	terrain5->setPosition(Vec2(930,520));
	terrain5->setTag(5);
	addChild(terrain5,5);

	auto terrain6 = CustomTerrain::createTerrain(3);
	terrain6->setPosition(Vec2(450,440));
	terrain6->setTag(6);
	addChild(terrain6,6);

	auto terrain7 = CustomTerrain::createTerrain(3);
	terrain7->setPosition(Vec2(250,380));
	terrain7->setTag(7);
	addChild(terrain7,7);

	auto terrain8 = CustomTerrain::createTerrain(3);
	terrain8->setPosition(Vec2(740,350));
	terrain8->setTag(8);
	addChild(terrain8,7);

	auto terrain9 = CustomTerrain::createTerrain(3);
	terrain9->setPosition(Vec2(940,320));
	terrain9->setTag(9);
	addChild(terrain9,7);

	auto terrain10 = CustomTerrain::createTerrain(3);
	terrain10->setPosition(Vec2(420,250));
	terrain10->setTag(10);
	addChild(terrain10,8);

}
