#include "TowerScene.h"
#include "Data/SoundManager.h"

USING_NS_CC;

Scene* Tower::createScene(){
    auto scene = Scene::create();
    auto towerInfLayer = Tower::create();
    scene->addChild(towerInfLayer);
    return scene;
}

bool Tower::init(){
    if ( !Layer::init() ){
        return false;
    }
	//���������¼����Ͳ���ִ�к���
	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->setSwallowTouches(true);//�ص�����
	touchListener->onTouchBegan = CC_CALLBACK_2(Tower::onTouchBegan, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(Tower::onTouchEnded, this);
	

    //ȡ����Ļ��С
	visibleSize = Director::getInstance()->getVisibleSize();
	//��ȡ�ֻ�������ԭ�������
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	// �ڶ����ˣ���ʾ�鱾ͼ��-ɾ���ײ㣬ֱ����ʾ��Ƥ
	for(int i = 0;i<4;i++){
		for(int j =0;j<5;j++){
			auto sprite = Sprite::createWithSpriteFrameName("encyclopedia_bgTile.png");
			sprite->setPosition(Vec2(i*310,j*150));
			sprite->setAnchorPoint(Vec2(0,0));
			addChild(sprite);
		}
	}

	// ����-��-�ұ�
    auto sprite1 = Sprite::createWithSpriteFrameName("encyclopedia_book_pg.png");
    sprite1->setPosition(Vec2(visibleSize.width * 3/4 + origin.x, visibleSize.height/2 + origin.y));

	//��-���
    auto sprite2 = Sprite::createWithSpriteFrameName("encyclopedia_book_pg.png");
    sprite2->setPosition(Vec2(visibleSize.width/4 + origin.x, visibleSize.height/2 + origin.y));

	//��ת
	sprite2->setFlippedX(true);
    sprite2->setRotation(360);

	// ���ͼƬ���鵽�����
    this->addChild(sprite1, 1);
	this->addChild(sprite2, 1);

	//�رղ��
	auto sprite3 = Sprite::createWithSpriteFrameName("encyclopedia_tow_creep_close_0001.png");
	//��ӵ��
	spriteCloseButton = MenuItemSprite::create(sprite3,sprite3,sprite3,CC_CALLBACK_1(Tower::closeScene,this));  
    auto closeEnemyScene = Menu::create(spriteCloseButton,NULL);
	closeEnemyScene->setPosition(Vec2(visibleSize.width - sprite3->getContentSize().width * 3 / 2  + origin.x,visibleSize.height + origin.y - sprite3->getContentSize().height / 2));

    this->addChild(closeEnemyScene,2); 
	//�����б�
	//���
	creepFrame = Sprite::createWithSpriteFrameName("encyclopedia_creep_thumbs_frame_0002.png");  

    creepFrame->setPosition(Vec2(visibleSize.width * 0.17, visibleSize.height * 0.75));
	this->addChild(creepFrame,3); 


	//��Ч��Ĵָͼ��
	auto spriteCreepThumbNull = Sprite::createWithSpriteFrameName("encyclopedia_tower_thumbs_0121.png");

	//��ʼ��Ĵָͼ��20��
	//��ʼ��Ĵָͼ��20��
	for(int i = 0; i < 20; i ++)
	{
		auto temp1 = cocos2d::StringUtils::format("encyclopedia_tower_thumbs_01%02d.png",i+1);
		auto temp2 = cocos2d::StringUtils::format("encyclopedia_tower_01%02d.png",i+1);

		towerDesc[i] = TowerDesc::createTowerDesc(temp1);
		towerDesc[i]->setPosition(Vec2(visibleSize.width * (0.17 + (i % 4)*0.085), 
												visibleSize.height * (0.75 - ((i / 4) % 5) *0.15)));
		_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener->clone(), towerDesc[i]);
		towerDesc[i]->towerThumbFileName = temp1;
		towerDesc[i]->towerDescFileName = temp2;
		//��ʼ���α�
		towerDesc[i]->num = i;
		this->addChild(towerDesc[i],2);
		
	}


	//��ʼ��˵����ͼ
	bigSprite = Sprite::createWithSpriteFrameName(towerDesc[0]->towerDescFileName);

	bigSprite->setPosition(Vec2(visibleSize.width * 0.7,visibleSize.height * 0.75));
	this->addChild(bigSprite,2);

	//��-��
    auto labelTitle = Label::createWithTTF("TOWERS", "Marker Felt.ttf", 24);
    labelTitle->setPosition(Vec2(visibleSize.width * 0.3, visibleSize.height * 6 / 7));
	labelTitle->setColor(Color3B(0,0,0));
    this->addChild(labelTitle, 2);

	////////////////////////////////////////////////
	///һ���label-��ʼ
	///////////////////////////////////////////////
	//������
	labelName = Label::createWithTTF("", "Marker Felt.ttf", 24);
    // ����label����Ļ�е���ʾλ��
    labelName->setPosition(Vec2(visibleSize.width * 0.7, visibleSize.height * 0.60));
	labelName->setColor(Color3B(0,0,0));
    // ��label��ӵ������
    this->addChild(labelName, 2);

	labelAttackSpeed = Label::createWithTTF("", "Marker Felt.ttf", 16);
    labelAttackSpeed->setPosition(Vec2(visibleSize.width * 0.65, visibleSize.height * 0.50));
	labelAttackSpeed->setColor(Color3B(0,0,0));
    this->addChild(labelAttackSpeed, 2);

	labelAttackValue = Label::createWithTTF("", "Marker Felt.ttf", 16);
    labelAttackValue->setPosition(Vec2(visibleSize.width * 0.65, visibleSize.height * 0.45));
	labelAttackValue->setColor(Color3B(0,0,0));
    this->addChild(labelAttackValue, 2);

	labelAttackRange = Label::createWithTTF("", "Marker Felt.ttf", 16);
    labelAttackRange->setPosition(Vec2(visibleSize.width * 0.65, visibleSize.height * 0.40));
	labelAttackRange->setColor(Color3B(0,0,0));
    this->addChild(labelAttackRange, 2);
	
	//�����Բ���
    labelNotice = Label::createWithTTF("*", "Marker Felt.ttf", 16);
    labelNotice->setPosition(Vec2(visibleSize.width * 0.7, visibleSize.height * 0.15));
	labelNotice->setColor(Color3B(0,0,0));
	labelNotice->setLineBreakWithoutSpace(true);
	labelNotice->setDimensions(visibleSize.width/3,visibleSize.height * 0.15);
    this->addChild(labelNotice, 2);

	/*****************************
	**��ʾ�������ģ��-��ʼ
	******************************/
	
	//��ȡxml�ĵ�,����ValueVector��
	ValueVector txt_vec = FileUtils::getInstance()->getValueVectorFromFile("tower.xml");
	int i = 0;
	for( auto& e : txt_vec){
		auto txt_map = txt_vec.at(i).asValueMap();//����ֵת����Map��ʽ������txt_map��
		int id_int = txt_map.at("id").asInt();//��ȡid
		if(id_int == i){
			//auto label_str = txt_map.at("info").asString();//��ȡinfo��ֵ
			towerDesc[i]->towerName = txt_map.at("TowerName").asString();
			towerDesc[i]->attackSpeed = txt_map.at("AttackSpeed").asString();
			towerDesc[i]->attackValue = txt_map.at("AttackValue").asString();
			towerDesc[i]->attackRange = txt_map.at("AttackRange").asString();
			towerDesc[i]->note = txt_map.at("Note").asString();
		}else if(id_int == 100){
			labelAttackSpeed->setString(txt_map.at("AttackSpeed").asString());
			labelAttackValue->setString(txt_map.at("AttackValue").asString());
			labelAttackRange->setString(txt_map.at("AttackRange").asString());
		}
		i ++; //��һ������	
	}

	/*****************************
	**��ʾ�������ģ��-����
	*****************************/

	//����������ֵ
	//����Ѫֵ1
	labelAttackSpeed1 = Label::createWithTTF("", "Marker Felt.ttf", 16);
    // ����label����Ļ�е���ʾλ��
    labelAttackSpeed1->setPosition(Vec2(visibleSize.width * 0.75, visibleSize.height * 0.50));
	labelAttackSpeed1->setColor(Color3B(0,0,0));
    // ��label��ӵ������
    this->addChild(labelAttackSpeed1, 2);

	//���﹥����
	labelAttackValue1 = Label::createWithTTF("", "Marker Felt.ttf", 16);
    // ����label����Ļ�е���ʾλ��
    labelAttackValue1->setPosition(Vec2(visibleSize.width * 0.75, visibleSize.height * 0.45));
	labelAttackValue1->setColor(Color3B(0,0,0));
    // ��label��ӵ������
    this->addChild(labelAttackValue1, 2);

	//�������������
	labelAttackRange1 = Label::createWithTTF("", "Marker Felt.ttf", 16);
    // ����label����Ļ�е���ʾλ��
    labelAttackRange1->setPosition(Vec2(visibleSize.width * 0.75, visibleSize.height * 0.40));
	labelAttackRange1->setColor(Color3B(0,0,0));
    // ��label��ӵ������
    this->addChild(labelAttackRange1, 2);

	//////////////////////////////////
	//һ���label-����
	//////////////////////////////////

	bigSprite->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(towerDesc[0]->towerDescFileName));
	labelName->setString(towerDesc[0]->towerName);
	//�ߴ�����
	labelAttackSpeed1->setString(towerDesc[0]->attackSpeed);
	labelAttackValue1->setString(towerDesc[0]->attackValue);
	labelAttackRange1->setString(towerDesc[0]->attackRange);
	labelNotice->setString(towerDesc[0]->note);

	creepFrame->setPosition(towerDesc[0]->getPosition());
	creepFrame->setVisible(true);
	return true;
}

//�������� 
bool Tower::onTouchBegan(Touch* touch, Event* event){

	auto target = static_cast<TowerDesc*>(event->getCurrentTarget());

	Vec2 locationInNode = target->convertTouchToNodeSpace(touch);

	Size size = target->towerDescPic->getContentSize();
	Rect rect = Rect(0-size.width/2, 0-size.height/2, size.width, size.height);

	if (rect.containsPoint(locationInNode) && target->getParent()->isVisible()){
		SoundManager::playClickEffect();
		bigSprite->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(target->towerDescFileName));
		labelName->setString(target->towerName);
		//�ߴ�����
		labelAttackSpeed1->setString(target->attackSpeed);
		labelAttackValue1->setString(target->attackValue);
		labelAttackRange1->setString(target->attackRange);
		labelNotice->setString(target->note);

		moveFrame=MoveTo::create(0.1f,target->getPosition());//����ͼ���λ��ʱ�䣬λ��Ŀ���ַ
		creepFrame->runAction(moveFrame);
		creepFrame->setVisible(true);

		return true;
	}
	return false;
}

void Tower::onTouchEnded(Touch* touch, Event* event){
	return;
}

//�رճ���
void Tower::closeScene(Ref* pSender){
	SoundManager::playClickEffect();
	Director::getInstance()->popScene();
	return;

}