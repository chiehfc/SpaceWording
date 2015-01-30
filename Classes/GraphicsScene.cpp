//
//  GraphicsScene.cpp
//  ZombieMatrix
//
//  Created by Chieh-Fu Chen on 11/18/14.
//
//

#include "GraphicsScene.h"
USING_NS_CC;

Scene* GraphicsScene::createScene()
{
    auto scene = Scene::create();
    auto layer = GraphicsScene::create();
    scene->addChild(layer);
    
    return scene;
}

bool GraphicsScene::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    auto sprite = Sprite::create("decepticon.png");
    sprite->setPosition(300, 300);
    
    this->addChild(sprite, 0);
    
    return true;
}