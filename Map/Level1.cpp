#include "Level1.h"

USING_NS_CC;

Level1::Level1()
{};

Level1::~Level1(){};

bool Level1::initWithDifficulty(int difficulty)
{
    if ( !Layer::init() )
    {
        return false;
    }
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("sprite_level1_2-hd.plist");
	setLevel(1);
	this->difficulty = difficulty;
	initMap();

	std::vector<Vec2> points;
	//road 0��ʾ
	points.push_back(Vec2(980,40));
	//road 1 ��ʾ
	points.push_back(Vec2(40,270));
	addWaveProgressBars(points);
	waveFlags.at(0)->restartWaveFlag();
	waveFlags.at(1)->restartWaveFlag();
	SoundManager::playDesertBattle();
	return true;
}

Level1* Level1::createGame(int difficulty)
{  
   auto layer = new Level1();
	if(layer && layer->initWithDifficulty(difficulty)){
		layer->autorelease();
		return layer;
	}
	CC_SAFE_DELETE(layer);

    return NULL;
}

void Level1::addOrnament()
{

}

void Level1::onExit()
{
	SpriteFrameCache::getInstance()->removeSpriteFrameByName("sprite_level1_2-hd.plist");
	Layer::onExit();
}

void Level1::addTerrains()
{
	auto terrain1 = CustomTerrain::createTerrain(1);
	terrain1->setPosition(Vec2(610,820));//�յ�
	terrain1->setTag(1);
	addChild(terrain1,2);

	auto terrain13 = CustomTerrain::createTerrain(1);
	terrain13->setPosition(Vec2(340,750));//�յ���
	terrain13->setTag(13);
	addChild(terrain13,3);

	auto terrain12 = CustomTerrain::createTerrain(1);
	terrain12->setPosition(Vec2(650,650));//ˮͰ����
	terrain12->setTag(12);
	addChild(terrain12,4);

	auto terrain3 = CustomTerrain::createTerrain(1);
	terrain3->setPosition(Vec2(535,620));//ˮͰ��
	terrain3->setTag(3);
	addChild(terrain3,4);

	auto terrain10 = CustomTerrain::createTerrain(1);
	terrain10->setPosition(Vec2(540,560));//��Բ���Թս��������
	terrain10->setTag(10);
	addChild(terrain10,5);

	auto terrain7 = CustomTerrain::createTerrain(1);
	terrain7->setPosition(Vec2(590,460));//��Բ���Թս����
	terrain7->setTag(7);
	addChild(terrain7,6);

	auto terrain9 = CustomTerrain::createTerrain(1);
	terrain9->setPosition(Vec2(310,440));//���ɽ��2
	terrain9->setTag(9);
	addChild(terrain9,6);

	auto terrain6 = CustomTerrain::createTerrain(1);
	terrain6->setPosition(Vec2(900,440));//��ţ���Թս����
	terrain6->setTag(6);
	addChild(terrain6,6);

	auto terrain2 = CustomTerrain::createTerrain(1);
	terrain2->setPosition(Vec2(380,360));//��ɽ�Ե�һ�ս�
	terrain2->setTag(2);
	addChild(terrain2,7);

	auto terrain8 = CustomTerrain::createTerrain(1);
	terrain8->setPosition(Vec2(250,360));//���ɽ��1
	terrain8->setTag(8);
	addChild(terrain8,7);

	auto terrain4 = CustomTerrain::createTerrain(1);
	terrain4->setPosition(Vec2(590,300));//Բ���Թս�
	terrain4->setTag(4);
	addChild(terrain4,7);

	auto terrain5 = CustomTerrain::createTerrain(1);
	terrain5->setPosition(Vec2(920,260));//ţ���Թս�
	terrain5->setTag(5);
	addChild(terrain5,8);

	auto terrain11 = CustomTerrain::createTerrain(1);
	terrain11->setPosition(Vec2(530,220));//Բ���Թս���
	terrain11->setTag(11);
	addChild(terrain11,8);


}