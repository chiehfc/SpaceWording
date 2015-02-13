//
//  HintScene.cpp
//  SpaceWording
//
//  Created by Chieh-Fu Chen on 2/11/15.
//
//

#include "HintScene.h"

USING_NS_CC;

Scene *HintScene::createScene() {
    auto scene = Scene::create();
    auto layer = HintScene::create();
    
    scene->addChild(layer);
    return scene;
}

bool HintScene::init() {
    Size visibleSize = Director::getInstance()->getVisibleSize();
    
    LayerColor *player = LayerColor::create(Color4B(0, 0, 0, 200), visibleSize.width, visibleSize.height);
    addChild(player,100);
    return true;
}

