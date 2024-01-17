#include "EncyclopediaScene.h"
#include "EncyclopaediaTips.h"
#include "EnemyScene.h"
#include "TowerScene.h"
#include "Data/SoundManager.h"

USING_NS_CC;


//��������
Scene* EncyclopediaScene::createScene()
{
    auto scene = Scene::create();
    auto layer = EncyclopediaScene::create();
    scene->addChild(layer);
    return scene;
}

// // ������ʼ������
bool EncyclopediaScene::init()
{
    //////////////////////////////
    // 1.���Ƚ��и����ʼ��
    if ( !Layer::init() )
    {
		 //�����ʼ������ʧ�ܷ���false
        return false;
    }

	 Size visibleSize = Director::getInstance()->getVisibleSize();
		//����plist


/*****************************************************************************************************************/
	//��һ��ͼƬ��� ������ͼƬ
   //// addImage ��������ͼƬ  ��ʵ��ͼƬ�ķŴ�
// ֧��ͼƬ��ʽ: .png, .bmp, .tiff, .jpeg, .pvr
	for(int i = 0;i<4;i++){
		for(int j =0;j<5;j++){
			auto sprite = Sprite::createWithSpriteFrameName("encyclopedia_bgTile.png");
			sprite->setPosition(Vec2(i*310,j*150));
			sprite->setAnchorPoint(Vec2(0,0));
			addChild(sprite);
		}
	}

//�ڶ���ͼƬ=====��ͼƬ���л�=================================================================================================
	//������

    auto sprite11 = Sprite::createWithSpriteFrameName("encyclopedia_button_towers_0001.png");
	sprite11->setScale(0.95f);

	auto sprite1 = MenuItemSprite::create(Sprite::createWithSpriteFrameName("encyclopedia_button_towers_0001.png"),sprite11,
		CC_CALLBACK_1(EncyclopediaScene::menuNextCallback2,this));  
    auto ccmenuu1 = Menu::create(sprite1,NULL);  //ʵ������֮���˳���л�  
    sprite1->setPosition(Vec2(visibleSize.width*0.23,visibleSize.height*0.65));  
	ccmenuu1->setPosition(Vec2::ZERO);
    this->addChild(ccmenuu1,2); 

	//�ٿ� ����
	//��ͼ
	auto sprite21 = Sprite::createWithSpriteFrameName("encyclopedia_button_enemies_0001.png");
	sprite21->setScale(0.95f);

	auto sprite2 = MenuItemSprite::create(Sprite::createWithSpriteFrameName("encyclopedia_button_enemies_0001.png"),
	sprite21,CC_CALLBACK_1(EncyclopediaScene::menuNextCallback3,this));  
    auto ccmenuu2 = Menu::create(sprite2,NULL);  //ʵ���л�  
    sprite2->setPosition(Vec2(visibleSize.width*0.57,visibleSize.height*0.5));  
	ccmenuu2->setPosition(Vec2::ZERO);
    this->addChild(ccmenuu2,2); 

	//�ٿ� ��ʾ
	//ԭͼ
	auto sprite31 = Sprite::createWithSpriteFrameName("encyclopedia_button_tips_0001.png");
	sprite31->setScale(0.8f);
   //��ͼ
	auto sprite32 = Sprite::createWithSpriteFrameName("encyclopedia_button_tips_0001.png");
	sprite32->setScale(0.75f);
	
	auto sprite3 =MenuItemSprite::create(sprite31,sprite32,CC_CALLBACK_1(EncyclopediaScene::menuNextCallback1,this));  
    auto ccmenuu3 = Menu::create(sprite3,NULL);  //ʵ���л�  
    sprite3->setPosition(Vec2(visibleSize.width*0.86,visibleSize.height*0.3));  
	ccmenuu3->setPosition(Vec2::ZERO);
    this->addChild(ccmenuu3,2); 

	
	//�ٿ� ս������
	auto sprite4 =Sprite::createWithSpriteFrameName("encyclopedia_button_strategyGuide_0001.png");
    sprite4->setPosition(Vec2(visibleSize.width*0.22,visibleSize.height*0.2));  
	sprite4->setScale(0.9f);
    this->addChild(sprite4,1); 

	//�ٿ� �رհ�ť
	//auto sprite51 = Sprite::createWithSpriteFrameName("encyclopedia_little_button_close_0001.png");
	auto sprite5 = MenuItemSprite::create(Sprite::createWithSpriteFrameName("encyclopedia_button_close_0001.png"), Sprite::createWithSpriteFrameName("encyclopedia_button_close_0001.png"),
		CC_CALLBACK_1(EncyclopediaScene::menuNextCallback4,this));  

    auto ccmenuu5 = Menu::create(sprite5,NULL);  //ʵ���л�  
    sprite5->setPosition(Vec2(visibleSize.width*0.87,visibleSize.height*0.83));  
	ccmenuu5->setPosition(Vec2::ZERO);
    this->addChild(ccmenuu5,2); 

	return true;
   
}

//============================================================================================================================//

////����ٿ���ʾ��ť�������л�
void EncyclopediaScene::menuNextCallback1(Ref *pSender ){
	SoundManager::playClickEffect();
    Director::getInstance()->pushScene(EncyclopaediaTips::createScene());
  }

//����ٿƷ�������ť�������л�
void EncyclopediaScene::menuNextCallback2(Ref *pSender ){
	SoundManager::playClickEffect();
	Director::getInstance()->pushScene(Tower::createScene());
 }

//����ٿƵ��˰�ť�������л�
void EncyclopediaScene::menuNextCallback3(Ref *pSender ){
	SoundManager::playClickEffect();
	Director::getInstance()->pushScene(Enemy::createScene());
 }

//����ٿƹرհ�ť�������л�
void EncyclopediaScene::menuNextCallback4(Ref *pSender ){
	SoundManager::playClickEffect();
	Director::getInstance()->popScene();
 }