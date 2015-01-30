//
//  CreditScene.cpp
//  ZombieMatrix
//
//  Created by Chieh-Fu Chen on 1/28/15.
//
//

#include "CreditScene.h"
#include "GameMenuScene.h"

USING_NS_CC;

Scene *CreditScene::createScene() {
    auto scene = Scene::create();
    auto layer = CreditScene::create();
    
    scene->addChild(layer);
    return scene;
}

bool CreditScene::init() {
    if (!Layer::init()) {
        return false;
    }

    Size size = Director::getInstance()->getWinSize();
    
    Sprite *background = Sprite::create("menu_background.png");
    background->setPosition(Vec2(size.width/2, size.height/2));
    background->setScale(2.0f, 2.0f);
    this->addChild(background);
    
    auto returnMenuItem = MenuItemImage::create("return.png", "return_pressed.png", CC_CALLBACK_1(CreditScene::returnPressed, this));
    returnMenuItem->setPosition(0, 0-returnMenuItem->getContentSize().height*3);
    returnMenuItem->setScale(1.5f);
    Menu *returnMenu = Menu::create(returnMenuItem, NULL);
    returnMenu->setZOrder(3);
    addChild(returnMenu);
    
    
    return true;
}

void CreditScene::returnPressed(Ref *pSender) {
    Director::getInstance()->replaceScene(GameMenuScene::createScene());
}