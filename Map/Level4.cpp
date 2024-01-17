#include "Level4.h"
USING_NS_CC;

Level4::Level4()
{};

Level4::~Level4(){};

bool Level4::initWithDifficulty(int difficulty)
{
    if ( !Layer::init() )
    {
        return false;
    }
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("sprite_level4-hd.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("sprite_level4_2-hd.plist");

	setLevel(4);
	this->difficulty = difficulty;
	initMap();

	std::vector<Vec2> points;
	points.push_back(Vec2(700,767));
	points.push_back(Vec2(740,767));
	addWaveProgressBars(points);
	waveFlags.at(0)->restartWaveFlag();
	waveFlags.at(1)->restartWaveFlag();
	SoundManager::playDesertBattle();
	return true;
}

Level4* Level4::createGame(int difficulty)
{  
    auto layer = new Level4();
	if(layer && layer->initWithDifficulty(difficulty)){
		layer->autorelease();
		return layer;
	}
	CC_SAFE_DELETE(layer);

    return NULL;
}

void Level4::addOrnament()
{
	auto ship=Sprite::createWithSpriteFrameName("Stage4_OverShip.png");
	ship->setPosition(Vec2(825,865));
	addChild(ship,99);

	doorSprite=Sprite::createWithSpriteFrameName("Stage4_ShipDoor_0001.png");
	doorSprite->setPosition(Vec2(730,820));
	mapSprite->addChild(doorSprite,0);

		//树下方的植被加入地图
	for(int i=0;i<4;i++)
	{
		treeTerrains[i]=Sprite::createWithSpriteFrameName(cocos2d::StringUtils::format("Stage4_Trees_Terrains_000%d.png",i+1));
		treeTerrains[i]->setPosition(Vec2(985,530));
	}
	for(int i=3;i>=0;i--)
		mapSprite->addChild(treeTerrains[i],0);
	//将树加入地图
	for(int i=0;i<4;i++)
		for(int j=0;j<3;j++)
			TreeSprite[i][j]=NULL;

	TreeSprite[0][0]=Sprite::createWithSpriteFrameName("Stage4_Trees_0001.png");
	TreeSprite[0][0]->setPosition(Vec2(1060,590));
	mapSprite->addChild(TreeSprite[0][0],1);

	TreeSprite[0][1]=Sprite::createWithSpriteFrameName("Stage4_Trees_0001.png");
	TreeSprite[0][1]->setPosition(Vec2(1140,590));
	mapSprite->addChild(TreeSprite[0][1],1);

	TreeSprite[0][2]=Sprite::createWithSpriteFrameName("Stage4_Trees_0001.png");
	TreeSprite[0][2]->setPosition(Vec2(1130,560));
	mapSprite->addChild(TreeSprite[0][2],1);

	TreeSprite[1][0]=Sprite::createWithSpriteFrameName("Stage4_Trees_0001.png");
	TreeSprite[1][0]->setPosition(Vec2(920,620));
	mapSprite->addChild(TreeSprite[1][0],1);

	TreeSprite[1][1]=Sprite::createWithSpriteFrameName("Stage4_Trees_0001.png");
	TreeSprite[1][1]->setPosition(Vec2(990,590));
	mapSprite->addChild(TreeSprite[1][1],1);

	TreeSprite[1][2]=Sprite::createWithSpriteFrameName("Stage4_Trees_0001.png");
	TreeSprite[1][2]->setPosition(Vec2(960,550));
	mapSprite->addChild(TreeSprite[1][2],1);

	TreeSprite[2][0]=Sprite::createWithSpriteFrameName("Stage4_Trees_0001.png");
	TreeSprite[2][0]->setPosition(Vec2(885,580));
	mapSprite->addChild(TreeSprite[2][0],1);

	TreeSprite[3][0]=Sprite::createWithSpriteFrameName("Stage4_Trees_0001.png");
	TreeSprite[3][0]->setPosition(Vec2(860,525));
	mapSprite->addChild(TreeSprite[3][0],1);
}

void Level4::onExit()
{
	SpriteFrameCache::getInstance()->removeSpriteFrameByName("sprite_level4_2-hd.plist");
	SpriteFrameCache::getInstance()->removeSpriteFrameByName("sprite_level4-hd.plist");

	Layer::onExit();
}

void Level4::waveEvent()
{
	if(wave == 0){
		SoundManager::playShipOpen();
		Vector<SpriteFrame*> animFrames;
		SpriteFrame* frame=NULL;
		for (int i = 1; i <= 9; i++)
		{
			frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(cocos2d::StringUtils::format("Stage4_ShipDoor_00%02d.png",i));
			if(frame!=nullptr)
				animFrames.pushBack(frame);
		}
		auto animation=Animation::createWithSpriteFrames(animFrames, 0.1f);
		doorSprite->runAction(Animate::create(animation));
		schedule(CC_SCHEDULE_SELECTOR(Level4::addMonsters), 1.0f, waveVector.at(wave).size(), 1.0f);
	}else{
		schedule(CC_SCHEDULE_SELECTOR(Level4::addMonsters), 1.0f, waveVector.at(wave).size(), 0);
	}
}

void Level4::addTerrains()
{
	auto terrain1 = CustomTerrain::createTerrain(1);
	terrain1->setPosition(Vec2(690,654));
	terrain1->setTag(1);
	addChild(terrain1,4);

	auto terrain5 = CustomTerrain::createTerrain(1);
	terrain5->setPosition(Vec2(471,642));
	terrain5->setTag(5);
	addChild(terrain5,4);

	auto terrain2 = CustomTerrain::createTerrain(1);
	terrain2->setPosition(Vec2(650,574));
	terrain2->setTag(2);
	addChild(terrain2,5);

	auto terrain6 = CustomTerrain::createTerrain(1);
	terrain6->setPosition(Vec2(452,554));
	terrain6->setTag(6);
	addChild(terrain6,5);

	auto terrain13 = CustomTerrain::createTerrain(1);
	terrain13->setPosition(Vec2(225,510));
	terrain13->setTag(13);
	addChild(terrain13,5);

	auto terrain7 = CustomTerrain::createTerrain(1);
	terrain7->setPosition(Vec2(471,475));
	terrain7->setTag(7);
	addChild(terrain7,6);
	
	auto terrain3 = CustomTerrain::createTerrain(1);
	terrain3->setPosition(Vec2(725,456));
	terrain3->setTag(3);
	addChild(terrain3,6);

	auto terrain4 = CustomTerrain::createTerrain(1);
	terrain4->setPosition(Vec2(950,422));
	terrain4->setTag(4);
	addChild(terrain4,6);

	auto terrain14 = CustomTerrain::createTerrain(1);
	terrain14->setPosition(Vec2(250,420));
	terrain14->setTag(14);
	addChild(terrain14,6);

	auto terrain8 = CustomTerrain::createTerrain(1);
	terrain8->setPosition(Vec2(506,405));
	terrain8->setTag(8);
	addChild(terrain8,6);

	auto terrain15 = CustomTerrain::createTerrain(1);
	terrain15->setPosition(Vec2(295,340));
	terrain15->setTag(15);
	addChild(terrain15,7);

	auto terrain16 = CustomTerrain::createTerrain(1);
	terrain16->setPosition(Vec2(162,334));
	terrain16->setTag(16);
	addChild(terrain16,7);

	auto terrain9 = CustomTerrain::createTerrain(1);
	terrain9->setPosition(Vec2(556,330));
	terrain9->setTag(9);
	addChild(terrain9,7);

	auto terrain10 = CustomTerrain::createTerrain(1);
	terrain10->setPosition(Vec2(830,295));
	terrain10->setTag(10);
	addChild(terrain10,8);

	auto terrain11 = CustomTerrain::createTerrain(1);
	terrain11->setPosition(Vec2(615,265));
	terrain11->setTag(11);
	addChild(terrain11,8);

	auto terrain12 = CustomTerrain::createTerrain(1);
	terrain12->setPosition(Vec2(550,210));
	terrain12->setTag(12);
	addChild(terrain12,8);


}