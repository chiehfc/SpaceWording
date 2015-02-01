//
//  Item.cpp
//  SpaceWording
//
//  Created by Chieh-Fu Chen on 1/30/15.
//
//

#include "Item.h"

USING_NS_CC;

HealthPack* HealthPack::healthPack(void)
{
    HealthPack *healthPack = new HealthPack();
    if (healthPack && healthPack->initWithFile("healthPacks.png"))
    {
        healthPack->curHp =1;
        healthPack->minMoveDuration =6;
        healthPack->maxMoveDuration =12;
        healthPack->destroying = 0;
        healthPack->locking = 0;
        healthPack->word = "ninja";
        healthPack->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(healthPack);
    }
    
    return healthPack;
}

FiniteTimeAction* Item::destroyedEffect(){
    int numFrame = 14;
    Vector<SpriteFrame *> frames;
    SpriteFrameCache* frameCache = SpriteFrameCache::getInstance();
    destroying=1;
    
    //    this->stopAllActions();
    char file[100]={0};
    
    for(int i=0;i<numFrame;i++) {
        sprintf(file, "8bit_%02d.png", i+1);
        SpriteFrame *frame = frameCache->getSpriteFrameByName(file);
        frames.pushBack(frame);
    }
    
    Animation *animation = Animation::createWithSpriteFrames(frames, 0.05);
    FiniteTimeAction *action = Animate::create(animation);
    
    return action;
    
}