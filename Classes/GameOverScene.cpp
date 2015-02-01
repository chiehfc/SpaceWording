//
//  GameOverScene.cpp
//  SpaceWording
//
//  Created by Chieh-Fu Chen on 11/20/14.
//
//

#include "GameOverScene.h"
#include "HelloWorldScene.h"
#include "GameMenuScene.h"

USING_NS_CC;

//Scene* GameOverScene::createScene()
//{
//    // 'scene' is an autorelease object
//    auto scene = Scene::create();
//    
//    // 'layer' is an autorelease object
//    auto layer = GameOverScene::create();
//
//    // add layer as a child to scene
//    scene->addChild(layer);
//    
//    // return the scene
//    return scene;
//}

bool GameOverScene::init() {

    if( Scene::init() )
    {
        this->_layer = GameOverLayer::create();
        this->_layer->retain();
        this->addChild(_layer);
        
        return true;
    }
    else
    {
        return false;
    }
    
}

GameOverScene::~GameOverScene()
{
    if (_layer)
    {
        _layer->release();
        _layer = NULL;
    }
}

bool GameOverLayer::init() {
    if ( LayerColor::initWithColor( Color4B(0, 0, 0, 0) ) )
    {
    auto winSize = Director::getInstance()->getWinSize();
    this->_label = Label::createWithBMFont("double_boxy.fnt", "label test");
    _label->setScale(2.0f);
    _label->retain();
    _label->setPosition(Point(winSize.width/2,winSize.height*0.6));
    this->addChild(_label);
    
    this->_bestScoreLabel = Label::createWithBMFont("double_boxy.fnt", "");
    _bestScoreLabel->setScale(2.0f);
    _bestScoreLabel->retain();
    _bestScoreLabel->setPosition(Point(winSize.width/2,winSize.height*0.3));
    this->addChild(_bestScoreLabel);
    
        
    this->runAction(Sequence::create(DelayTime::create(5),
                                     CallFunc::create(std::bind(&GameOverLayer::gameOverDone, this)),
                                     NULL));
    return true;
    }
    else return false;
}

void GameOverLayer::gameOverDone()
{
    Director::getInstance()->replaceScene(GameMenuScene::createScene());
}

GameOverLayer::~GameOverLayer()
{
    if (_label)
    {
        _label->release();
        _label = NULL;
    }
}