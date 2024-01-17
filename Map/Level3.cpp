#include "Level3.h"
USING_NS_CC;

Level3::Level3()
{};

Level3::~Level3(){};

bool Level3::initWithDifficulty(int difficulty)
{
    if ( !Layer::init() )
    {
        return false;
    }
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("sprite_level3_2-hd.plist");
	setLevel(3);
	this->difficulty = difficulty;
	initMap();
	//ROAD1�ұ�0���
	std::vector<Vec2> points;
	points.push_back(Vec2(40,243));
	points.push_back(Vec2(1139,200));
	addWaveProgressBars(points);
	waveFlags.at(0)->restartWaveFlag();
	waveFlags.at(1)->restartWaveFlag();
	SoundManager::playDesertBattle();
	return true;
}

Level3* Level3::createGame(int difficulty)
{  
    auto layer = new Level3();
	if(layer && layer->initWithDifficulty(difficulty)){
		layer->autorelease();
		return layer;
	}
	CC_SAFE_DELETE(layer);

    return NULL;
}

void Level3::addOrnament()
{

}

void Level3::onExit()
{
	SpriteFrameCache::getInstance()->removeSpriteFrameByName("sprite_level3_2-hd.plist");

	Layer::onExit();
}

void Level3::addTerrains()
{
	auto terrain15 = CustomTerrain::createTerrain(1);
	terrain15->setPosition(Vec2(880,520));
	terrain15->setTag(15);
	addChild(terrain15,5);

	auto terrain5 = CustomTerrain::createTerrain(1);
	terrain5->setPosition(Vec2(865,284));
	terrain5->setTag(5);
	addChild(terrain5,8);

	auto terrain13 = CustomTerrain::createTerrain(1);
	terrain13->setPosition(Vec2(836,450));
	terrain13->setTag(13);
	addChild(terrain13,6);

	auto terrain14 = CustomTerrain::createTerrain(1);
	terrain14->setPosition(Vec2(745,530));
	terrain14->setTag(14);
	addChild(terrain14,5);

	auto terrain12 = CustomTerrain::createTerrain(1);
	terrain12->setPosition(Vec2(710,407));
	terrain12->setTag(12);
	addChild(terrain12,6);

	auto terrain1 = CustomTerrain::createTerrain(1);
	terrain1->setPosition(Vec2(660,818));
	terrain1->setTag(1);
	addChild(terrain1,2);

	auto terrain4 = CustomTerrain::createTerrain(1);
	terrain4->setPosition(Vec2(599,716));
	terrain4->setTag(4);
	addChild(terrain4,3);

	auto terrain11 = CustomTerrain::createTerrain(1);
	terrain11->setPosition(Vec2(597,350));
	terrain11->setTag(11);
	addChild(terrain11,7);

	auto terrain8 = CustomTerrain::createTerrain(1);
	terrain8->setPosition(Vec2(545,520));
	terrain8->setTag(8);
	addChild(terrain8,5);

	auto terrain3 = CustomTerrain::createTerrain(1);
	terrain3->setPosition(Vec2(449,713));
	terrain3->setTag(3);
	addChild(terrain3,3);

	auto terrain10 = CustomTerrain::createTerrain(1);
	terrain10->setPosition(Vec2(460,344));
	terrain10->setTag(10);
	addChild(terrain10,7);

	auto terrain7 = CustomTerrain::createTerrain(1);
	terrain7->setPosition(Vec2(395,518));
	terrain7->setTag(7);
	addChild(terrain7,5);

	auto terrain2 = CustomTerrain::createTerrain(1);
	terrain2->setPosition(Vec2(348,713));
	terrain2->setTag(2);
	addChild(terrain2,3);

	auto terrain9 = CustomTerrain::createTerrain(1);
	terrain9->setPosition(Vec2(324,340));
	terrain9->setTag(9);
	addChild(terrain9,7);

	auto terrain6 = CustomTerrain::createTerrain(1);
	terrain6->setPosition(Vec2(281,517));
	terrain6->setTag(6);
	addChild(terrain6,5);



}