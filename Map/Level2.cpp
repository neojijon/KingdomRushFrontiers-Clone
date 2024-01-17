#include "Level2.h"
USING_NS_CC;

Level2::Level2()
{};

Level2::~Level2(){};

bool Level2::initWithDifficulty(int difficulty)
{
    if ( !Layer::init() )
    {
        return false;
    }
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("sprite_level2_2-hd.plist");
	setLevel(2);
	this->difficulty = difficulty;
	initMap();
	//road0Ϊ�ϱߵ�·
	std::vector<Vec2> points;
	points.push_back(Vec2(678,950));
	points.push_back(Vec2(1160,270));
	addWaveProgressBars(points);
	waveFlags.at(0)->restartWaveFlag();
	waveFlags.at(1)->restartWaveFlag();
	SoundManager::playDesertBattle();
	return true;
}

Level2* Level2::createGame(int difficulty)
{  
    auto layer = new Level2();
	if(layer && layer->initWithDifficulty(difficulty)){
		layer->autorelease();
		return layer;
	}
	CC_SAFE_DELETE(layer);

    return NULL;
}

void Level2::addOrnament()
{

}

void Level2::onExit()
{
	SpriteFrameCache::getInstance()->removeSpriteFrameByName("sprite_level2_2-hd.plist");

	Layer::onExit();
}

void Level2::addTerrains()
{
	auto terrain14= CustomTerrain::createTerrain(1);
	terrain14->setPosition(Vec2(700,730));//�����رߵ��ĸ�
	terrain14->setTag(14);
	addChild(terrain14,3);

	auto terrain12= CustomTerrain::createTerrain(1);
	terrain12->setPosition(Vec2(580,660));//�����رߵڶ���
	terrain12->setTag(12);
	addChild(terrain12,4);

	auto terrain13= CustomTerrain::createTerrain(1);
	terrain13->setPosition(Vec2(700,660));//�����رߵ�����
	terrain13->setTag(13);
	addChild(terrain13,4);

	auto terrain11= CustomTerrain::createTerrain(1);
	terrain11->setPosition(Vec2(430,650));//�����رߵ�һ��
	terrain11->setTag(11);
	addChild(terrain11,4);

	auto terrain2 = CustomTerrain::createTerrain(1);
	terrain2->setPosition(Vec2(280,550));//��һ���ұ�
	terrain2->setTag(2);
	addChild(terrain2,5);

	auto terrain1 = CustomTerrain::createTerrain(1);
	terrain1->setPosition(Vec2(160,530));//�����
	terrain1->setTag(1);
	addChild(terrain1,5);

	auto terrain7= CustomTerrain::createTerrain(1);
	terrain7->setPosition(Vec2(620,470));//�м����������
	terrain7->setTag(7);
	addChild(terrain7,6);

	auto terrain8= CustomTerrain::createTerrain(1);
	terrain8->setPosition(Vec2(720,470));//�м�������ĸ�
	terrain8->setTag(8);
	addChild(terrain8,6);

	auto terrain6 = CustomTerrain::createTerrain(1);
	terrain6->setPosition(Vec2(520,460));//�м�����ڶ���
	terrain6->setTag(6);
	addChild(terrain6,6);

	auto terrain5 = CustomTerrain::createTerrain(1);
	terrain5->setPosition(Vec2(440,420));//�м������һ��
	terrain5->setTag(5);
	addChild(terrain5,6);

	auto terrain10= CustomTerrain::createTerrain(1);
	terrain10->setPosition(Vec2(960,380));//�ұ�����ڶ���
	terrain10->setTag(10);
	addChild(terrain10,7);

	auto terrain9= CustomTerrain::createTerrain(1);
	terrain9->setPosition(Vec2(850,370));//�ұ������һ��
	terrain9->setTag(9);
	addChild(terrain9,7);

	auto terrain4 = CustomTerrain::createTerrain(1);
	terrain4->setPosition(Vec2(620,300));//��һ���ϱ�һ��
	terrain4->setTag(4);
	addChild(terrain4,7);


}