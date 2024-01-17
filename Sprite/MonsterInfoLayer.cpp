#include "MonsterInfoLayer.h"

MonsterInfoLayer* MonsterInfoLayer::createMonsterInfoLayer(BaseMonster* monster)
{
	auto monsterInfoLayer = new MonsterInfoLayer();
	if(monsterInfoLayer && monsterInfoLayer->init(monster)){
		monsterInfoLayer->autorelease();
		return monsterInfoLayer;
	}
	CC_SAFE_DELETE(monsterInfoLayer);
	return NULL;
}

bool MonsterInfoLayer::init(BaseMonster* monster)
{
	if(!Sprite::init()){
		return false;
	}
	info_bg = Sprite::createWithSpriteFrameName("menu_bottom_bg.png");
	mBaseMonster = monster;
	setMonsterInfo();
	addChild(info_bg);
	schedule(CC_SCHEDULE_SELECTOR(MonsterInfoLayer::updateMonsterHp),0.1f);
	return true;
}

void MonsterInfoLayer::updateMonsterHp(float dt)
{
	if(mBaseMonster->getCurrHp()<=0){
		unschedule(CC_SCHEDULE_SELECTOR(MonsterInfoLayer::updateMonsterHp));
		this->removeFromParent();
	}
	else
		hpLabel->setString(cocos2d::StringUtils::format("%d/%d",(int)mBaseMonster->getCurrHp(),(int)mBaseMonster->getMaxHp()));
}

void MonsterInfoLayer::setMonsterInfo()
{
	auto protraits = Sprite::createWithSpriteFrameName("portraits_sc.png");
	protraits->setPosition(Vec2(20,25));
	info_bg->addChild(protraits);

	auto monsterName = Label::createWithTTF("","Comic_Book.ttf",20);
	monsterName->setPosition((Vec2(60,25)));
	monsterName->setAnchorPoint(Vec2(0,0.5));
	info_bg->addChild(monsterName);

	auto hpSprite = Sprite::createWithSpriteFrameName("icon_0006.png");
	hpSprite->setPosition(Vec2(280,25));
	info_bg->addChild(hpSprite);

	hpLabel = Label::createWithTTF("0/0","Comic_Book.ttf",18);
	hpLabel->setAnchorPoint(Vec2(0,0.5));
	hpLabel->setPosition(Vec2(305,25));

	info_bg->addChild(hpLabel);

	auto forceSprite = Sprite::createWithSpriteFrameName("icon_0007.png");
	forceSprite->setPosition(Vec2(440,25));
	info_bg->addChild(forceSprite);

	auto forceLabel = Label::createWithTTF("NONE","Comic_Book.ttf",18);
	forceLabel->setAnchorPoint(Vec2(0,0.5));
	forceLabel->setPosition(Vec2(475,25));

	info_bg->addChild(forceLabel);

	//��ʾ����
	auto armorSprite = Sprite::createWithSpriteFrameName("icon_0004.png");
	armorSprite->setPosition(Vec2(570,25));
	info_bg->addChild(armorSprite);

	auto armorLabel = Label::createWithTTF("NONE","Comic_Book.ttf",18);
	armorLabel->setAnchorPoint(Vec2(0,0.5));
	armorLabel->setPosition(Vec2(605,25));
	info_bg->addChild(armorLabel);
	Sprite* portraits_sc;

	hpLabel->setString(cocos2d::StringUtils::format("%d/%d",(int)mBaseMonster->getMaxHp(),(int)mBaseMonster->getMaxHp()));
	forceLabel->setString(cocos2d::StringUtils::format("%d",(int)mBaseMonster->getForce()));
	armorLabel->setString(cocos2d::StringUtils::format("%d",(int)mBaseMonster->getArmor()));

	switch(mBaseMonster->getMonsterType()){

	case(THUG):
		portraits_sc = Sprite::createWithSpriteFrameName("portraits_sc_0027.png");
		monsterName->setString("Thug");
		break;
	case(RADIER):
		portraits_sc = Sprite::createWithSpriteFrameName("portraits_sc_0028.png");
		monsterName->setString("Raider");
		break;
	case(IMMORTAL):
		portraits_sc = Sprite::createWithSpriteFrameName("portraits_sc_0028.png");
		monsterName->setString("Immortal");
		break;
	case(EXECUTIONER):
		portraits_sc = Sprite::createWithSpriteFrameName("portraits_sc_0031.png");
		monsterName->setString("Executioner");
		break;
	case(MUNRA):
		portraits_sc = Sprite::createWithSpriteFrameName("portraits_sc_0032.png");
		monsterName->setString("Munra");
		break;
	case(WOLF):
		portraits_sc = Sprite::createWithSpriteFrameName("portraits_sc_0034.png");
		monsterName->setString("Wolf");
		break;
	case(TREMOR):
		portraits_sc = Sprite::createWithSpriteFrameName("portraits_sc_0035.png");
		monsterName->setString("Tremor");
		break;
	case(SCORPION):
		portraits_sc = Sprite::createWithSpriteFrameName("portraits_sc_0036.png");
		monsterName->setString("Tremor");
		break;
	case(WASPHORNET):
		portraits_sc = Sprite::createWithSpriteFrameName("portraits_sc_0037.png");
		monsterName->setString("WaspHornet");
		break;
	case(WASPQUEEN):
		portraits_sc = Sprite::createWithSpriteFrameName("portraits_sc_0038.png");
		monsterName->setString("WaspQueen");
		break;
	case(BOSS_EFREETI):
		portraits_sc = Sprite::createWithSpriteFrameName("portraits_sc_0040.png");
		monsterName->setString("Boss_Efreeti");
		break;
	case(EFREETI):
		portraits_sc = Sprite::createWithSpriteFrameName("portraits_sc_0039.png");
		monsterName->setString("Efreeti");
		break;
	case(FALLEN):
		portraits_sc = Sprite::createWithSpriteFrameName("portraits_sc_0055.png");
		monsterName->setString("Fallen");
		break;
	case(BOSS_CANIBAL):
		portraits_sc = Sprite::createWithSpriteFrameName("portraits_sc_0068.png");
		monsterName->setString("Sun Wukong"); 
		break;
	case(CANIBAL_OFFSPRING):
		portraits_sc = Sprite::createWithSpriteFrameName("portraits_sc_0067.png");
		monsterName->setString("Offspring");
		break;
	case(CANIBAL):
		portraits_sc = Sprite::createWithSpriteFrameName("portraits_sc_0044.png");
		monsterName->setString("Cabibal");
		break;
	case(GORILLA):
		portraits_sc = Sprite::createWithSpriteFrameName("portraits_sc_0050.png");
		monsterName->setString("Gorilla");
		break;
	case(HUNTER):
		portraits_sc = Sprite::createWithSpriteFrameName("portraits_sc_0045.png");
		monsterName->setString("Hunter");
		break;
	case(PRIEST):
		portraits_sc = Sprite::createWithSpriteFrameName("portraits_sc_0046.png");
		monsterName->setString("Priest");
		break;
	case(SHAMAN):
		portraits_sc = Sprite::createWithSpriteFrameName("portraits_sc_0048.png");
		monsterName->setString("Magic");
		break;
	case(SHIELD):
		portraits_sc = Sprite::createWithSpriteFrameName("portraits_sc_0049.png");
		monsterName->setString("Shield");
		break;
	case(WINGRIDER):
		portraits_sc = Sprite::createWithSpriteFrameName("portraits_sc_0052.png");
		monsterName->setString("WingRider");
		break;
	default:
		portraits_sc = Sprite::createWithSpriteFrameName("portraits_sc_0029.png");
		break;
	}
	portraits_sc->setPosition(Vec2(protraits->getContentSize().width/2,protraits->getContentSize().height/2));
	protraits->addChild(portraits_sc);
}