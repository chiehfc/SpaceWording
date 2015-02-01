//
//  GamePauseScene.cpp
//  SpaceWording
//
//  Created by Chieh-Fu Chen on 1/17/15.
//
//

#include "GamePauseScene.h"
#include "GameMenuScene.h"
#include "HelloWorldScene.h"

USING_NS_CC;

Scene *GamePauseScene::createScene() {
    auto scene = Scene::create();
    auto layer = GamePauseScene::create();
    
    scene->addChild(layer);
    return scene;
}

bool GamePauseScene::init() {

    if (!Layer::init()) {
        return false;
    }
    this->_layer = GamePauseLayer::create();
    this->_layer->retain();
    this->addChild(_layer);
    return true;
//
//    Size size = Director::getInstance()->getWinSize();
//    
//    auto sp = LayerColor::create(Color4B(255, 255, 255, 0));
//    addChild(sp);
//    
//    return true;
    
}

GamePauseScene::~GamePauseScene()
{
    if (_layer)
    {
        _layer->release();
        _layer = NULL;
    }
}

bool GamePauseLayer::init() {
    if ( LayerColor::initWithColor( Color4B(0, 0, 0, 0) ) )
    {
        auto winSize = Director::getInstance()->getWinSize();
        
        _monsterNumber = UserDefault::getInstance()->getIntegerForKey("MonsterNumber");
        _selectedNumber = 1;
        
        _monsterFileName["ninja"] = "spaceMonster1_1.png";
        _monsterFileName["monster"] = "spaceMonster2_1.png";
        _monsterFileName["ivysaur"] = "spaceMonster3_1.png";
        _monsterFileName["charizard"] = "6-mega-x.png";
        _monsterFileName["pikachu"] = "pikachu.png";
        _monsterFileName["flyingdragon"] = "flyingDragon.png";
        _monsterFileName["dragon"] = "dragon.png";
        _monsterFileName["gengar"] = "gengar.png";
        _monsterFileName["turtle"] = "turtle.png";
        
        _monsterWords.push_back("ninja");
        _monsterWords.push_back("monster");
        _monsterWords.push_back("ivysaur");
        _monsterWords.push_back("charizard");
        _monsterWords.push_back("pikachu");
        _monsterWords.push_back("flyingdragon");
        _monsterWords.push_back("dragon");
        _monsterWords.push_back("gengar");
        _monsterWords.push_back("turtle");
        
        this->_label = Label::createWithBMFont("double_boxy.fnt", "ninja");
        _label->retain();
        _label->setScale(2.0f);
        _label->setPosition(Point(winSize.width/2,winSize.height*0.6));
        this->addChild(_label);
        
        auto gameResumeItem = MenuItemImage::create(
                                               "return.png",
                                               "return_pressed.png",
                                               CC_CALLBACK_1(GamePauseLayer::gameResumeCallback, this));
        
        gameResumeItem->setPosition(Point(winSize.width/2,winSize.height*0.3));
        
        // create menu, it's an autorelease object
        auto menu = Menu::create(gameResumeItem, NULL);
        menu->setPosition(Vec2::ZERO);
        this->addChild(menu, 1);

        auto leftArrowItem = MenuItemImage::create(
                                                   "leftArrow.png",
                                                   "leftArrow_pressed.png",
                                                   CC_CALLBACK_1(GamePauseLayer::minusMonsterNumberCallback, this));
        leftArrowItem->setPosition(Point(winSize.width/2-150,winSize.height*0.5));
        
        // create menu, it's an autorelease object
        auto left = Menu::create(leftArrowItem, NULL);
        left->setPosition(Vec2::ZERO);
        this->addChild(left, 1);
        
        auto rightArrowItem = MenuItemImage::create(
                                                    "rightArrow.png",
                                                    "rightArrow_pressed.png",
                                                    CC_CALLBACK_1(GamePauseLayer::addMonsterNumberCallback, this));
        rightArrowItem->setPosition(Point(winSize.width/2+150,winSize.height*0.5));
        
        // create menu, it's an autorelease object
        auto right = Menu::create(rightArrowItem, NULL);
        right->setPosition(Vec2::ZERO);
        this->addChild(right, 1);

        _monster = Sprite::create("space_monster_white.png");
        _monster->setPosition(Vec2(winSize.width/2, winSize.height/2));
        _monster->setScale(2.0f, 2.0f);
        this->addChild(_monster);
        
        return true;
    }
    else return false;
}

void GamePauseLayer::minusMonsterNumberCallback(cocos2d::Ref *pSender)
{
    if(_selectedNumber>1 && _selectedNumber<=_monsterNumber) {
        _selectedNumber--;
        _label->setString(_monsterWords.at(_selectedNumber-1).c_str());
        SpriteFrameCache* frameCache = SpriteFrameCache::getInstance();
        SpriteFrame *frame = frameCache
        ->getSpriteFrameByName(_monsterFileName.at(_monsterWords.at(_selectedNumber-1).c_str()));
        
        _monster->setDisplayFrame(frame);
    }
}

void GamePauseLayer::addMonsterNumberCallback(cocos2d::Ref *pSender)
{
    if(_selectedNumber>=1 && _selectedNumber<_monsterNumber) {
        _selectedNumber++;
        _label->setString(_monsterWords.at(_selectedNumber-1).c_str());
        
        SpriteFrameCache* frameCache = SpriteFrameCache::getInstance();
        SpriteFrame *frame = frameCache
        ->getSpriteFrameByName(_monsterFileName.at(_monsterWords.at(_selectedNumber-1).c_str()));
        
        _monster->setDisplayFrame(frame);
    }
}

void GamePauseLayer::gamePauseDone()
{
    Director::getInstance()->popScene();
}

void GamePauseLayer::gameResumeCallback(Ref* pSender)
{
    Director::getInstance()->popScene();
}

GamePauseLayer::~GamePauseLayer()
{
    if (_label)
    {
        _label->release();
        _label = NULL;
    }
}