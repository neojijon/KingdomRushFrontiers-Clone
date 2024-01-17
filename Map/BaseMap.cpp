#include "Map/BaseMap.h"
#include "Data/GameManager.h"
#include "Data/SoundManager.h"
#include "Monster/Desert/Immortal.h"
#include "Monster/Desert/Wolf.h"
#include "Monster/Desert/Fallen.h"
#include "Monster/Desert/Raider.h"
#include "Monster/Desert/WaspHornet.h"
#include "Monster/Desert/Thug.h"
#include "Layer/Victory.h"
#include "Monster/Desert/Scorpion.h"
#include "Monster/Desert/Tremor.h"
#include "Monster/Desert/Munra.h"
#include "Monster/Desert/Executioner.h"
#include "Monster/Desert/WaspQueen.h"
#include "Monster/Jungle/Canibal.h"
#include "Monster/Jungle/Gorilla.h"
#include "Monster/Jungle/Hunter.h"
#include "Monster/Jungle/Priest.h"
#include "Monster/Jungle/Shaman.h"
#include "Monster/Jungle/Shield.h"
#include "Monster/Jungle/WingRider.h"
#include "Monster/Underground/Blazefang.h"
#include "Monster/Underground/Broodguard.h"
#include "Monster/Underground/Elite.h"
#include "Monster/Underground/Myrmidon.h"
#include "Monster/Underground/Nightscale.h"
#include "Monster/Underground/Quetzal.h"
#include "Monster/Boss/Boss_Efreeti.h"
#include "Monster/Boss/Boss_Canibal.h"
#include "Layer/Failure.h"

USING_NS_CC;

void BaseMap::loadPathFromPlist()
{
	winSize = cocos2d::Director::getInstance()->getWinSize();
	auto plistDic = cocos2d::FileUtils::getInstance()->getValueMapFromFile(
		cocos2d::StringUtils::format("level%d_paths.plist", getLevel()));

	auto path_array = plistDic["paths"].asValueVector();

	for (int i = 0; i < path_array.size(); i++) {
		std::vector<std::vector<cocos2d::Vec2>> tempPathVector;
		auto path_array2 = path_array.at(i).asValueVector();

		for (int j = 0; j < path_array2.size(); j++) {
			std::vector<cocos2d::Vec2> tempRandomPathVector;
			auto path_array3 = path_array2.at(j).asValueVector();

			for (int k = 0; k < path_array3.size(); k++) {
				auto tempDic = path_array3.at(k).asValueMap();
				cocos2d::Vec2 tempPath;
				tempPath.x = tempDic["x"].asFloat() * 1.15f;
				tempPath.y = tempDic["y"].asFloat() * 1.20f + 50.0f;
				tempRandomPathVector.push_back(tempPath);
			}

			tempPathVector.push_back(tempRandomPathVector);
		}

		path.push_back(tempPathVector);
	}
}

void BaseMap::showWaveProgressBars(float dt)
{
	for (int i = 0; i < waveFlags.size(); i++)
	{
		waveFlags.at(i)->restartWaveFlag();
	}
}

void BaseMap::addWaveProgressBars(std::vector<Vec2> waveFlagLocations)
{
	for (unsigned int i = 0; i < waveFlagLocations.size(); i++)
	{
		auto waveFlag = WaveFlag::createWaveFlag();
		waveFlag->setPosition(waveFlagLocations.at(i));
		addChild(waveFlag, 20);
		auto waveflag_listener = EventListenerTouchOneByOne::create();
		waveflag_listener->onTouchBegan = [&](Touch* touch, Event* event)
		{
			auto target = static_cast<WaveFlag*>(event->getCurrentTarget());

			Vec2 locationInNode = target->convertTouchToNodeSpace(touch);

			Size size = target->waveProgressTimer->getContentSize();
			Rect rect = Rect(0 - size.width / 2, 0 - size.height / 2, size.width, size.height);
			if (rect.containsPoint(locationInNode) && target->isShown)
			{
				if (target->selected->isVisible())
				{
					for (int i = 0; i < waveFlags.size(); i++)
					{
						waveFlags.at(i)->stopRespiration();
					}
				}
				for (int i = 0; i < waveFlags.size(); i++)
				{
					waveFlags.at(i)->setSelected();
				}
				return true;
			}
			return false;
		};
		waveflag_listener->setSwallowTouches(true);
		_eventDispatcher->addEventListenerWithSceneGraphPriority(waveflag_listener, waveFlag);
		waveFlags.pushBack(waveFlag);
	}
}

void BaseMap::onEnterTransitionDidFinish()
{
	GameManager::getInstance()->MONEY = startGold;
	GameManager::getInstance()->LIFE = maxLife;
	playerState->setGold(startGold);
	playerState->setLife(maxLife);
	playerState->setWave(0, maxWave);
	playerState->startProgressTimers();
	scheduleUpdate();
	schedule(CC_SCHEDULE_SELECTOR(BaseMap::addWaves), 0.5f);
	//schedule([this](float dt) { this->addWaves(dt); }, 0.5f, "addWaves");

}

void BaseMap::loadAndSetLevelData()
{
	// getLevel() 棺 difficulty 窃荐啊 沥狼登绢 乐促绊 啊沥
	auto dataDic = cocos2d::FileUtils::getInstance()->getValueMapFromFile(
		cocos2d::StringUtils::format("level%d_%d_monsters.plist", getLevel(), difficulty));

	auto data_array = dataDic["data"].asValueVector();
	auto data_tempDic = data_array.at(0).asValueMap();
	startGold = data_tempDic["gold"].asInt();
	maxLife = data_tempDic["life"].asInt();
	maxWave = data_tempDic["wave"].asInt();
	
	auto monsters_array = dataDic["monsters"].asValueVector();	

	for (int i = 0; i < monsters_array.size(); i++) {
		auto monster_array = monsters_array.at(i).asValueVector();
		std::vector<cocos2d::Vector<GroupMonster*>> thisTimeMonster;

		for (int j = 0; j < monster_array.size(); j++) {
			auto tempArray = monster_array.at(j).asValueVector();
			cocos2d::Vector<GroupMonster*> monsterVector;

			for (int k = 0; k < tempArray.size(); k++) {
				auto tempDic = tempArray.at(k).asValueMap();
				monsterVector.pushBack(GroupMonster::initGroupEnemy(
					tempDic["type"].asInt(),
					tempDic["road"].asInt(),
					tempDic["path"].asInt()));
			}

			thisTimeMonster.push_back(monsterVector);
			monsterVector.clear();
		}

		waveVector.push_back(thisTimeMonster);
		thisTimeMonster.clear();
	}
}

void BaseMap::setMapPosition()
{
	Vec2 location = Vec2();
	auto mapSize = mapSprite->getBoundingBox().size;
	location.x = winSize.width / 2 - mapSize.width / 2;
	location.y = winSize.height / 2 - mapSize.height / 2;
	location.x = MIN(location.x,0);
	location.x = MAX(location.x, -mapSize.width + winSize.width);
	location.y = MIN(location.y,0);
	location.y = MAX(location.y, -mapSize.height + winSize.height);
	this->setPosition(location);
}

void BaseMap::update(float dt)
{
	updateGoldAndLife();
	if (isStart && isEnd && GameManager::getInstance()->monsterVector.size() == 0)
	{
		isStart = false;
		isEnd = false;
		victory();
	}
}

void BaseMap::updateGoldAndLife()
{
	if (GameManager::getInstance()->LIFE > 0)
	{
		playerState->setGold(GameManager::getInstance()->MONEY);
		playerState->setLife(GameManager::getInstance()->LIFE);
	}
	else if (isStart)
	{
		isStart = false;
		playerState->setLife(0);
		unscheduleAllCallbacks();
		for (int i = 0; i < waveFlags.size(); i++)
		{
			waveFlags.at(i)->stopRespiration();
		}
		auto failure = Failure::create();
		mTouchLayer->removeAllChildren();
		failure->level = getLevel();
		failure->difficulty = difficulty;
		playerState->addChild(failure, 99);
	}
}

void BaseMap::onExitTransitionDidStart()
{
	GameManager::eraseAll();
	this->unscheduleAllCallbacks();
}

void BaseMap::initTouchLayer()
{
	//设置防御塔升级菜单层
	mTouchLayer = TouchLayer::create();
	mTouchLayer->setContentSize(mapSprite->getContentSize());
	mTouchLayer->setAnchorPoint(Vec2(0, 0));
	mTouchLayer->setPosition(Vec2(0, 0));
	addChild(mTouchLayer, 99);
}

void BaseMap::bindPlayerStateMenu(PlayerStateMenu* playerState)
{
	this->playerState = playerState;
	this->playerState->mTouchLayer = this->mTouchLayer;
}

void BaseMap::addWaves(float dt)
{
	bool newWave = false;
	for (int i = 0; i < waveFlags.size(); i++)
	{
		if (waveFlags.at(i)->getWavePercentage() == 100.0f)
		{
			newWave = true;
			break;
		}
	}
	if (newWave && wave < maxWave)
	{
		isStart = true;
		SoundManager::playIncomingWave();
		wave ++;
		for (int i = 0; i < waveFlags.size(); i++)
		{
			waveFlags.at(i)->setWavePercentage(0.0f);
		}
		playerState->setWave(wave + 1, maxWave);
		waveEvent();
	}
}

void BaseMap::waveEvent()
{
	schedule(CC_SCHEDULE_SELECTOR(BaseMap::addMonsters), 1.0f, waveVector.at(wave).size(), 0);
}

void BaseMap::initMap()
{
	isStart = false;
	isEnd = false;
	GameManager::getInstance()->LEVEL = level;
	this->difficulty = difficulty;
	mapSprite = Sprite::createWithSpriteFrameName(cocos2d::StringUtils::format("Stage_%d.png", level + 1));
	mapSprite->setAnchorPoint(Vec2(0, 0));
	mapSprite->setPosition(Vec2(0, 0));
	addChild(mapSprite);

	loadAndSetLevelData();
	loadPathFromPlist();

	addOrnament();

	wave = -1;
	time = 0;

	addTerrains();
	initTouchLayer();
	setMapPosition();
}

void BaseMap::victory()
{
	//停止计时器
	auto instance = GameManager::getInstance();
	auto dataInstance = UserDefault::getInstance();
	unscheduleUpdate();
	unschedule(CC_SCHEDULE_SELECTOR(BaseMap::addWaves));
	unschedule(CC_SCHEDULE_SELECTOR(BaseMap::addMonsters));
	//若此关卡得星数为0，则表示第一次完成
	if (UserDefault::getInstance()->getIntegerForKey(
		cocos2d::StringUtils::format(GameManager::getInstance()->LEVELX_STARNUM, getLevel()).data(), 0) == 0)
	{
		UserDefault::getInstance()->setIntegerForKey(GameManager::getInstance()->LEVELX_NEWDOWN, getLevel() + 1);
	}
	//判断完成等级给星
	int gotStar = 0;
	switch (difficulty)
	{
	case(0):
		if (GameManager::getInstance()->LIFE >= 18)
		{
			gotStar = 3;
		}
		else if (GameManager::getInstance()->LIFE > 10)
		{
			gotStar = 2;
		}
		else
		{
			gotStar = 1;
		}
		break;
	case(1):
		gotStar = 4;
		break;
	case(2):
		gotStar = 5;
		break;
	}
	//若此次得到的星星大于之前记录，更新
	int oldStar = dataInstance->getIntegerForKey(
		cocos2d::StringUtils::format(instance->LEVELX_STARNUM, getLevel()).data(), 0);
	if (gotStar > oldStar)
	{
		//之前星星个数
		int starCount = dataInstance->getIntegerForKey(instance->SLOTX_STAR);
		//加上得到的星星
		dataInstance->setIntegerForKey(instance->SLOTX_STAR, starCount + gotStar - oldStar);
		//更新本关星星
		dataInstance->setIntegerForKey(cocos2d::StringUtils::format(instance->LEVELX_STARNUM, getLevel()).data(),
		                               gotStar);
		//更新剩余星星个数
		dataInstance->setIntegerForKey(instance->SLOTX_STARLEFT,
		                               dataInstance->getIntegerForKey(instance->SLOTX_STARLEFT) + gotStar - oldStar);
	}
	//更新得到的钻石钻石
	int gem = gotStar * 10 * (level + 1) / 2;
	int oldGem = dataInstance->getIntegerForKey(instance->SLOTX_GEM);
	dataInstance->setIntegerForKey(instance->SLOTX_GEM, gem + oldGem);
	//根据难度，星，钻，显示胜利画面
	auto victory = Victory::createVictory(gotStar, gem);
	mTouchLayer->removeAllChildren();
	victory->level = getLevel();
	victory->difficult = difficulty;
	playerState->addChild(victory, 999);
}

void BaseMap::addMonsters(float dt)
{
	//waveVector.size（）为波束
	//waveVector.at()保存该wave怪物，size为怪物个数
	//waveVector.at().at()保存该0.5s内需要创建的怪物,.size为怪物个数
	if (time < waveVector.at(wave).size())
	{
		for (int i = 0; i < waveVector.at(wave).at(time).size(); i++)
		{
			auto monsterData = waveVector.at(wave).at(time).at(i);
			switch (monsterData->getType())
			{
			case(0):
				{
					auto thug = Thug::createMonster(path.at(monsterData->getRoad()).at(monsterData->getPath()));
					addChild(thug);
					GameManager::getInstance()->monsterVector.pushBack(thug);
				}
				break;
			case(1):
				{
					auto raider = Raider::createMonster(path.at(monsterData->getRoad()).at(monsterData->getPath()));
					addChild(raider);
					GameManager::getInstance()->monsterVector.pushBack(raider);
				}
				break;
			case(2):
				{
					auto wolf = Wolf::createMonster(path.at(monsterData->getRoad()).at(monsterData->getPath()));
					GameManager::getInstance()->monsterVector.pushBack(wolf);
					addChild(wolf);
				}
				break;
			case(3):
				{
					auto Immortal = Immortal::createMonster(path.at(monsterData->getRoad()).at(monsterData->getPath()));
					GameManager::getInstance()->monsterVector.pushBack(Immortal);
					addChild(Immortal);
				}
				break;
			case(4):
				{
					auto fallen = Fallen::createMonster(path.at(monsterData->getRoad()).at(monsterData->getPath()));
					GameManager::getInstance()->monsterVector.pushBack(fallen);
					addChild(fallen);
				}
				break;
			case(5):
				{
					auto waspHornet = WaspHornet::createMonster(
						path.at(monsterData->getRoad()).at(monsterData->getPath()));
					GameManager::getInstance()->monsterVector.pushBack(waspHornet);
					addChild(waspHornet);
				}
				break;
			case(6):
				{
					auto waspQueen = WaspQueen::createMonster(
						path.at(monsterData->getRoad()).at(monsterData->getPath()));
					GameManager::getInstance()->monsterVector.pushBack(waspQueen);
					addChild(waspQueen);
				}
				break;
			case(7):
				{
					auto scorpion = Scorpion::createMonster(path.at(monsterData->getRoad()).at(monsterData->getPath()));
					GameManager::getInstance()->monsterVector.pushBack(scorpion);
					addChild(scorpion);
				}
				break;
			case(8):
				{
					auto tremor = Tremor::createMonster(path.at(monsterData->getRoad()).at(monsterData->getPath()));
					GameManager::getInstance()->monsterVector.pushBack(tremor);
					addChild(tremor);
				}
				break;
			case(9):
				{
					auto munra = Munra::createMonster(path.at(monsterData->getRoad()).at(monsterData->getPath()));
					GameManager::getInstance()->monsterVector.pushBack(munra);
					addChild(munra);
				}
				break;
			case(10):
				{
					auto executioner = Executioner::createMonster(
						path.at(monsterData->getRoad()).at(monsterData->getPath()));
					GameManager::getInstance()->monsterVector.pushBack(executioner);
					addChild(executioner);
				}
				break;
			case(11):
				{
					auto canibal = Canibal::createMonster(path.at(monsterData->getRoad()).at(monsterData->getPath()));
					GameManager::getInstance()->monsterVector.pushBack(canibal);
					addChild(canibal);
				}
				break;
			case(12):
				{
					auto gorilla = Gorilla::createMonster(path.at(monsterData->getRoad()).at(monsterData->getPath()));
					GameManager::getInstance()->monsterVector.pushBack(gorilla);
					addChild(gorilla);
				}
				break;
			case(13):
				{
					auto hunter = Hunter::createMonster(path.at(monsterData->getRoad()).at(monsterData->getPath()));
					GameManager::getInstance()->monsterVector.pushBack(hunter);
					addChild(hunter);
				}
				break;
			case(14):
				{
					auto priest = Priest::createMonster(path.at(monsterData->getRoad()).at(monsterData->getPath()));
					GameManager::getInstance()->monsterVector.pushBack(priest);
					addChild(priest);
				}
				break;
			case(15):
				{
					auto shaman = Shaman::createMonster(path.at(monsterData->getRoad()).at(monsterData->getPath()));
					GameManager::getInstance()->monsterVector.pushBack(shaman);
					addChild(shaman);
				}
				break;
			case(16):
				{
					auto shield = Shield::createMonster(path.at(monsterData->getRoad()).at(monsterData->getPath()));
					GameManager::getInstance()->monsterVector.pushBack(shield);
					addChild(shield);
				}
				break;
			case(17):
				{
					auto wingRider = WingRider::createMonster(
						path.at(monsterData->getRoad()).at(monsterData->getPath()));
					GameManager::getInstance()->monsterVector.pushBack(wingRider);
					addChild(wingRider);
				}
				break;
			case(18):
				{
					auto blazefang = Blazefang::createMonster(
						path.at(monsterData->getRoad()).at(monsterData->getPath()));
					GameManager::getInstance()->monsterVector.pushBack(blazefang);
					addChild(blazefang);
				}
				break;
			case(19):
				{
					auto broodguard = Broodguard::createMonster(
						path.at(monsterData->getRoad()).at(monsterData->getPath()));
					GameManager::getInstance()->monsterVector.pushBack(broodguard);
					addChild(broodguard);
				}
				break;
			case(20):
				{
					auto elite = Elite::createMonster(path.at(monsterData->getRoad()).at(monsterData->getPath()));
					GameManager::getInstance()->monsterVector.pushBack(elite);
					addChild(elite);
				}
				break;
			case(21):
				{
					auto myrmidon = Myrmidon::createMonster(path.at(monsterData->getRoad()).at(monsterData->getPath()));
					GameManager::getInstance()->monsterVector.pushBack(myrmidon);
					addChild(myrmidon);
				}
				break;
			case(22):
				{
					auto nightscale = Nightscale::createMonster(
						path.at(monsterData->getRoad()).at(monsterData->getPath()));
					GameManager::getInstance()->monsterVector.pushBack(nightscale);
					addChild(nightscale);
				}
				break;
			case(23):
				{
					auto quetzal = Quetzal::createMonster(path.at(monsterData->getRoad()).at(monsterData->getPath()));
					GameManager::getInstance()->monsterVector.pushBack(quetzal);
					addChild(quetzal);
				}
				break;
			case(100):
				{
					auto Boss_Efreeti = Boss_Efreeti::createMonster(
						path.at(monsterData->getRoad()).at(monsterData->getPath()), path);
					GameManager::getInstance()->monsterVector.pushBack(Boss_Efreeti);
					addChild(Boss_Efreeti);
				}
				break;
			case(101):
				{
					auto Boss_Canibal = Boss_Canibal::createMonster(
						path.at(monsterData->getRoad()).at(monsterData->getPath()), path);
					GameManager::getInstance()->monsterVector.pushBack(Boss_Canibal);
					addChild(Boss_Canibal);
				}
				break;
			default:
				break;
			}
		}
		time ++;
	}
	else
	{
		time = 0;
		if (wave != maxWave - 1)
			//15秒后显示WaveProgressBar
		{
			SoundManager::playNextWaveReady();
			scheduleOnce(CC_SCHEDULE_SELECTOR(BaseMap::showWaveProgressBars), 15.0f);

			/*this->scheduleOnce([this](float dt) {
				this->showWaveProgressBars(dt);
				}, 15.0f, "showWaveProgressBars");*/
			
		}
		else
		{
			isEnd = true;
		}
	}
}
