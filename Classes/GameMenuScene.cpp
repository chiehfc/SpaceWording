//
//  GameMenuScene.cpp
//  ZombieMatrix
//
//  Created by Chieh-Fu Chen on 11/24/14.
//
//

#include "GameMenuScene.h"
#include "GameLevelScene.h"
#include "HelloWorldScene.h"
#include "Monster.h"
#include "CreditScene.h"

USING_NS_CC;

Scene *GameMenuScene::createScene() {
    auto scene = Scene::create();
    auto layer = GameMenuScene::create();
    
    scene->addChild(layer);
    return scene;
}


bool GameMenuScene::init() {
    if (!Layer::init()) {
        return false;
    }
    
    Size size = Director::getInstance()->getWinSize();
    
    Sprite *background = Sprite::create("menu_background.png");
    background->setPosition(Vec2(size.width/2, size.height/2));
    background->setScale(2.0f, 2.0f);
    this->addChild(background);
    
    auto sp = LayerColor::create(Color4B(0, 0, 0, 0));
    addChild(sp);
    
    auto titleLabel = Label::createWithBMFont("double_boxy.fnt", "Space");
    titleLabel->setScale(3.5f);
    titleLabel->setPosition(Point(size.width/2,size.height*0.7));
    this->addChild(titleLabel);

    auto anotherLabel = Label::createWithBMFont("double_boxy.fnt", "Wording");
    anotherLabel->setScale(2.5f);
    anotherLabel->setPosition(Point(size.width/2,size.height*0.65));
    this->addChild(anotherLabel);
    
    this->testLabel = Label::createWithBMFont("double_boxy.fnt", "S");
    testLabel->setScale(2.0f);
    testLabel->setOpacity(128);
    testLabel->setPosition(Point(size.width/2, size.height*0.3));
    this->addChild(testLabel);
    
    auto listenerText = EventListenerTouchOneByOne::create();
    
    listenerText->onTouchBegan = CC_CALLBACK_2(GameMenuScene::testLabelOnTouchBegan,this);
    
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listenerText, testLabel);

    
    
    //Sprite *sptop = Sprite::create("holdtailtitletxt.png");
    //sptop->setPosition(Point(size.width*0.5-30, size.height-100));
    //sptop->setZOrder(1);
    //addChild(sptop);
    
//    Sprite *spbutton = Sprite::create("copyright.png");
//    spbutton->setPosition(Point(size.width*0.5, 10));
//    spbutton->setZOrder(1);
//    addChild(spbutton);
    
    auto itemPlay = MenuItemImage::create("start.png", "start_pressed.png", CC_CALLBACK_1(GameMenuScene::playPressed, this));
    itemPlay->setPosition(0,0);
    itemPlay->setScale(2.0f);
    Menu *menu = Menu::create(itemPlay,NULL);
    menu->setZOrder(3);
    addChild(menu);

    auto creditMenuItem = MenuItemImage::create("credit.png", "credit_pressed.png", CC_CALLBACK_1(GameMenuScene::creditPressed, this));
    creditMenuItem->setPosition(0, 0-creditMenuItem->getContentSize().height*3);
    creditMenuItem->setScale(1.5f);
    Menu *creditMenu = Menu::create(creditMenuItem, NULL);
    creditMenu->setZOrder(3);
    addChild(creditMenu);
    
    return true;
}

bool GameMenuScene::testLabelOnTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event) {
    this->testLabel->setString("Cool");
    return true;
}

void GameMenuScene::playPressed(cocos2d::Ref *pSender) {
    Director::getInstance()->replaceScene(GameLevelScene::createScene());
}

void GameMenuScene::creditPressed(cocos2d::Ref *pSender) {
    Director::getInstance()->replaceScene(CreditScene::createScene());
}