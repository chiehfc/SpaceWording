//
//  GameLevelScene.cpp
//  SpaceWording
//
//  Created by Chieh-Fu Chen on 1/17/15.
//
//

#include "GameLevelScene.h"
#include "GamePauseScene.h"
#include "GameMenuScene.h"
#include "HelloWorldScene.h"

USING_NS_CC;
#define MAX_MONSTER 3

Scene *GameLevelScene::createScene() {
    auto scene = Scene::create();
    auto layer = GameLevelScene::create();
    
    scene->addChild(layer);
    return scene;
}

bool GameLevelScene::init() {
    
    if (!Layer::init()) {
        return false;
    }
    this->_layer = GameLevelLayer::create();
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

GameLevelScene::~GameLevelScene()
{
    if (_layer)
    {
        _layer->release();
        _layer = NULL;
    }
}

bool GameLevelLayer::init() {
    if ( LayerColor::initWithColor( Color4B(255,255,255,255) ) )
    {
        
        auto winSize = Director::getInstance()->getWinSize();

        Sprite *background = Sprite::create("menu_background.png");
        background->setPosition(Vec2(winSize.width/2, winSize.height/2));
        background->setScale(2.0f, 2.0f);
        this->addChild(background);
        
        this->_monsterNumber = 1;
        
        this->_label = Label::createWithBMFont("double_boxy.fnt", "Select Game Level");
        _label->setScale(2.0f);
        _label->retain();
        _label->setColor(Color3B(255, 255, 255));
        _label->setPosition(Point(winSize.width/2,winSize.height*0.7));
        this->addChild(_label);

        auto leftArrowItem = MenuItemImage::create(
                                                    "leftArrow.png",
                                                    "leftArrow_pressed.png",
                                                    CC_CALLBACK_1(GameLevelLayer::minusMonsterNumberCallback, this));
//        leftArrowItem->setScale(3.0f);
        leftArrowItem->setPosition(Point(winSize.width/2-100,winSize.height*0.6));
        
        // create menu, it's an autorelease object
        auto left = Menu::create(leftArrowItem, NULL);
        left->setPosition(Vec2::ZERO);
        this->addChild(left, 1);
        
        auto rightArrowItem = MenuItemImage::create(
                                                   "rightArrow.png",
                                                   "rightArrow_pressed.png",
                                                   CC_CALLBACK_1(GameLevelLayer::addMonsterNumberCallback, this));
//        rightArrowItem->setScale(3.0f);
        rightArrowItem->setPosition(Point(winSize.width/2+100,winSize.height*0.6));
        
        // create menu, it's an autorelease object
        auto right = Menu::create(rightArrowItem, NULL);
        right->setPosition(Vec2::ZERO);
        this->addChild(right, 1);
        
        auto gameResumeItem = MenuItemImage::create(
                                                    "start.png",
                                                    "start_pressed.png",
                                                    CC_CALLBACK_1(GameLevelLayer::gameLevelCallback, this));
        
        gameResumeItem->setPosition(Point(winSize.width/2,winSize.height*0.6-125));
        gameResumeItem->setScale(2.0f);
        // create menu, it's an autorelease object
        auto menu = Menu::create(gameResumeItem, NULL);
        menu->setPosition(Vec2::ZERO);
        this->addChild(menu, 1);

        return true;
    }
    else return false;
}

void GameLevelLayer::gameLevelCallback(Ref* pSender)
{
    UserDefault::getInstance()->setIntegerForKey("MonsterNumber", _monsterNumber);
    Director::getInstance()->replaceScene(HelloWorld::createScene());
}

void GameLevelLayer::addMonsterNumberCallback(Ref* pSender)
{
    if(_monsterNumber<=MAX_MONSTER-1)
    _monsterNumber++;
    char text[256];
    sprintf(text,"Level: %d", _monsterNumber);
    this->_label->setString(text);
}

void GameLevelLayer::minusMonsterNumberCallback(Ref* pSender)
{
    if(_monsterNumber>1)
        _monsterNumber--;
    char text[256];
    sprintf(text,"Level: %d", _monsterNumber);
    this->_label->setString(text);
}

GameLevelLayer::~GameLevelLayer()
{
    if (_label)
    {
        _label->release();
        _label = NULL;
    }
}