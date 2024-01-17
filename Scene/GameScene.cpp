#include "Scene/GameScene.h"
#include "Data/GameManager.h"
#include "Layer/PlayerStateMenu.h"
#include "Map/BaseMap.h"
#include "Map/Level0.h"
#include "Map/Level1.h"
#include "Map/Level2.h"
#include "Map/Level3.h"
#include "Map/Level4.h"
#include "Map/Level5.h"
#include "Map/Level6.h"
#include "Map/Level7.h"
#include "Map/Level8.h"
#include "Map/Level9.h"
#include "Map/Level10.h"
#include "Map/Level11.h"
#include "Map/Level12.h"

Scene* GameScene::playGame(int Level,int Difficulty)
{            
	auto scene = new GameScene();
	if(scene && scene->initGame(Level,Difficulty)){
		scene->autorelease();
		return scene;
	}
	CC_SAFE_DELETE(scene);
	return NULL;
}

bool GameScene::initGame(int Level,int difficulty)
{
	auto playerStateMenu = PlayerStateMenu::create();
	BaseMap* game;
	GameManager::getInstance()->LEVEL = Level;
	switch (Level)
	{
	case(0):{
		game = Level0::createGame(difficulty);}
		break;
	case(1):{
		game = Level1::createGame(difficulty);}
		break;
	case(2):{
		game = Level2::createGame(difficulty);}
		break;
	case(3):{
		game = Level3::createGame(difficulty);}
		break;
	case(4):{
		game = Level4::createGame(difficulty);}
		break;
	case(5):{
		game = Level5::createGame(difficulty);}
		break;
	case(6):{
		game = Level6::createGame(difficulty);}
		break;
	case(7):{
		game = Level7::createGame(difficulty);}
		break;
	case(8):{
		game = Level8::createGame(difficulty);}
		break;
	case(9):{
		game = Level9::createGame(difficulty);}
		break;
	case(10):{
		game = Level10::createGame(difficulty);}
		break;
	case(11):{
		game = Level11::createGame(difficulty);}
		break;
	case(12):{
		game = Level12::createGame(difficulty);}
		break;
	}
	
	game->bindPlayerStateMenu(playerStateMenu);
	playerStateMenu->setLevel(Level);
	playerStateMenu->setDifficult(difficulty);
	playerStateMenu->initGameOption();
	addChild(game);	
	addChild(playerStateMenu);
	return true;
}