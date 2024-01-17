#include "Level10.h"
#include "Data/MyAnimation.h"

USING_NS_CC;

Level10::Level10()
{};

Level10::~Level10(){};

bool Level10::initWithDifficulty(int difficulty)
{
    if ( !Layer::init() )
    {
        return false;
    }
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("sprite_level10-hd.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("sprite_level10_2-hd.plist");
	setLevel(10);
	this->difficulty = difficulty;
	initMap();
	MyAnimation::getInstance()->init_BossCanibal();
	std::vector<Vec2> points;
	points.push_back(Vec2(610,710));
	points.push_back(Vec2(650,710));
	addWaveProgressBars(points);
	waveFlags.at(0)->restartWaveFlag();
	waveFlags.at(1)->restartWaveFlag();
	Vector<SpriteFrame*> animFrames1;
	SpriteFrame* frame1=NULL;
	for (int i = 1; i <= 31; i++)
	{
		frame1 = SpriteFrameCache::getInstance()->getSpriteFrameByName(cocos2d::StringUtils::format("Stage10_Tower_00%02d.png",i));
		if(frame1!=nullptr)
			animFrames1.pushBack(frame1);
	}
	AnimationCache::getInstance()->addAnimation(Animation::createWithSpriteFrames(animFrames1, 0.04f),"level_stage");
	SoundManager::playJungleBattle();
	return true;
}

Level10* Level10::createGame(int difficulty)
{  
    auto layer = new Level10();
	if(layer && layer->initWithDifficulty(difficulty)){
		layer->autorelease();
		return layer;
	}
	CC_SAFE_DELETE(layer);

    return NULL;
}

void Level10::addOrnament()
{
	auto door=Sprite::createWithSpriteFrameName("Stage10_Dark.png");
	door->setPosition(Vec2(635,880));
	addChild(door,100);

	stageTower = Sprite::createWithSpriteFrameName("Stage10_Tower_0001.png");
	stageTower->setPosition(Vec2(635,510));
	addChild(stageTower,100);


}

void Level10::waveEvent()
{
	if(wave == 0)	{
		/*Vector<SpriteFrame*> animFrames1;
		SpriteFrame* frame1=NULL;
		for (int i = 1; i <= 31; i++)
		{
			frame1 = SpriteFrameCache::getInstance()->getSpriteFrameByName(cocos2d::StringUtils::format("Stage10_Tower_00%02d.png",i));
			if(frame1!=nullptr)
				animFrames1.pushBack(frame1);
		}*/
		stageTower->runAction(Animate::create(AnimationCache::getInstance()->getAnimation("level_stage")));
	}
	schedule(CC_SCHEDULE_SELECTOR(Level10::addMonsters), 1.0f, waveVector.at(wave).size(), 0.0f);
}

void Level10::onExit()
{
	SpriteFrameCache::getInstance()->removeSpriteFrameByName("sprite_Level10-hd.plist");
	SpriteFrameCache::getInstance()->removeSpriteFrameByName("sprite_Level10_2-hd.plist");

	Layer::onExit();
}

void Level10::addTerrains()
{
	auto terrain1 = CustomTerrain::createTerrain(2);
	terrain1->setPosition(Vec2(184,330));
	terrain1->setTag(1);
	addChild(terrain1,4);

	auto terrain2 = CustomTerrain::createTerrain(2);
	terrain2->setPosition(Vec2(251,410));
	terrain2->setTag(2);
	addChild(terrain2,4);

	auto terrain3 = CustomTerrain::createTerrain(2);
	terrain3->setPosition(Vec2(247,566));
	terrain3->setTag(3);
	addChild(terrain3,6);

	auto terrain4 = CustomTerrain::createTerrain(2);
	terrain4->setPosition(Vec2(345,630));
	terrain4->setTag(4);
	addChild(terrain4,7);

	auto terrain5 = CustomTerrain::createTerrain(2);
	terrain5->setPosition(Vec2(381,540));
	terrain5->setTag(5);
	addChild(terrain5,6);

	auto terrain6 = CustomTerrain::createTerrain(2);
	terrain6->setPosition(Vec2(450,450));
	terrain6->setTag(6);
	addChild(terrain6,5);

	auto terrain7 =CustomTerrain::createTerrain(2);
	terrain7->setPosition(Vec2(414,320));
	terrain7->setTag(7);
	addChild(terrain7,4);

	auto terrain8 = CustomTerrain::createTerrain(2);
	terrain8->setPosition(Vec2(1014,560));
	terrain8->setTag(8);
	addChild(terrain8,6);

	auto terrain9 = CustomTerrain::createTerrain(2);
	terrain9->setPosition(Vec2(890,550));
	terrain9->setTag(9);
	addChild(terrain9,6);

	auto terrain10 = CustomTerrain::createTerrain(2);
	terrain10->setPosition(Vec2(816,450));
	terrain10->setTag(10);
	addChild(terrain10,5);

	auto terrain11 = CustomTerrain::createTerrain(2);
	terrain11->setPosition(Vec2(820,380));
	terrain11->setTag(11);
	addChild(terrain11,4);

	auto terrain12 = CustomTerrain::createTerrain(2);
	terrain12->setPosition(Vec2(916,280));
	terrain12->setTag(12);
	addChild(terrain12,3);

	auto terrain13 = CustomTerrain::createTerrain(2);
	terrain13->setPosition(Vec2(740,280));
	terrain13->setTag(13);
	addChild(terrain13,3);

	auto terrain14 = CustomTerrain::createTerrain(2);
	terrain14->setPosition(Vec2(1016,410));
	terrain14->setTag(14);
	addChild(terrain14,5);
}
