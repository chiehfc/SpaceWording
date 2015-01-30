//
//  Monster.cpp
//  ZombieMatrix
//
//  Created by Chieh-Fu Chen on 11/25/14.
//
//

#include "Monster.h"

USING_NS_CC;

WeakAndFastMonster* WeakAndFastMonster::monster(void)
{
    WeakAndFastMonster * monster = new WeakAndFastMonster();
    if (monster && monster->initWithSpriteFrameName("spaceMonster1_1.png"))
    {
        monster->curHp =1;
        monster->minMoveDuration =6;
        monster->maxMoveDuration =12;
        monster->destroying = 0;
        monster->locking = 0;
        monster->word = "ninja";
        monster->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(monster);
    }
    
    return monster;
}

RepeatForever* Monster::movingAnimation() {
    return NULL;
}


RepeatForever* WeakAndFastMonster::movingAnimation() {
    int numFrame =2;
    cocos2d::Vector<cocos2d::SpriteFrame *> frames;
    SpriteFrameCache* frameCache = SpriteFrameCache::getInstance();
    char file[100] = {0};
    
    for (int i = 0; i < numFrame; i++) {
        sprintf(file, "spaceMonster1_%d.png", i+1);
        SpriteFrame *frame = frameCache->getSpriteFrameByName(file);
        frames.pushBack(frame);
    }

    Animation *animation = Animation::createWithSpriteFrames(frames, 0.3);
    Animate *animate = Animate::create(animation);
    
    repeat = RepeatForever::create(animate);

    return repeat;
}

RepeatForever* StrongAndSlowMonster::movingAnimation() {
    int numFrame =2;
    cocos2d::Vector<cocos2d::SpriteFrame *> frames;
    SpriteFrameCache* frameCache = SpriteFrameCache::getInstance();
    char file[100] = {0};
    
    for (int i = 0; i < numFrame; i++) {
        sprintf(file, "spaceMonster2_%d.png", i+1);
        SpriteFrame *frame = frameCache->getSpriteFrameByName(file);
        frames.pushBack(frame);
    }
    
    Animation *animation = Animation::createWithSpriteFrames(frames, 0.3);
    Animate *animate = Animate::create(animation);
    
    repeat = RepeatForever::create(animate);
    return repeat;
    
}

RepeatForever* IvysaurMonster::movingAnimation() {
    int numFrame =2;
    cocos2d::Vector<cocos2d::SpriteFrame *> frames;
    SpriteFrameCache* frameCache = SpriteFrameCache::getInstance();
    char file[100] = {0};
    
    for (int i = 0; i < numFrame; i++) {
        sprintf(file, "spaceMonster3_%d.png", i+1);
        SpriteFrame *frame = frameCache->getSpriteFrameByName(file);
        frames.pushBack(frame);
    }
    
    Animation *animation = Animation::createWithSpriteFrames(frames, 0.3);
    Animate *animate = Animate::create(animation);
    
    repeat = RepeatForever::create(animate);
    return repeat;
}

RepeatForever* CharizardMonster::movingAnimation() {
    int numFrame =2;
    cocos2d::Vector<cocos2d::SpriteFrame *> frames;
    SpriteFrameCache* frameCache = SpriteFrameCache::getInstance();
    char file[100] = {0};
    
    for (int i = 0; i < numFrame; i++) {
        sprintf(file, "spaceMonster1_%d.png", i+1);
        SpriteFrame *frame = frameCache->getSpriteFrameByName(file);
        frames.pushBack(frame);
    }
    
    Animation *animation = Animation::createWithSpriteFrames(frames, 0.3);
    Animate *animate = Animate::create(animation);
    
    repeat = RepeatForever::create(animate);
    return repeat;
}

RepeatForever* dragonMonster::movingAnimation() {
    int numFrame =2;
    cocos2d::Vector<cocos2d::SpriteFrame *> frames;
    SpriteFrameCache* frameCache = SpriteFrameCache::getInstance();
    char file[100] = {0};
    
    for (int i = 0; i < numFrame; i++) {
        sprintf(file, "spaceMonster1_%d.png", i+1);
        SpriteFrame *frame = frameCache->getSpriteFrameByName(file);
        frames.pushBack(frame);
    }
    
    Animation *animation = Animation::createWithSpriteFrames(frames, 0.3);
    Animate *animate = Animate::create(animation);
    
    repeat = RepeatForever::create(animate);
    return repeat;
}

RepeatForever* gengarMonster::movingAnimation() {
    int numFrame =2;
    cocos2d::Vector<cocos2d::SpriteFrame *> frames;
    SpriteFrameCache* frameCache = SpriteFrameCache::getInstance();
    char file[100] = {0};
    
    for (int i = 0; i < numFrame; i++) {
        sprintf(file, "spaceMonster1_%d.png", i+1);
        SpriteFrame *frame = frameCache->getSpriteFrameByName(file);
        frames.pushBack(frame);
    }
    
    Animation *animation = Animation::createWithSpriteFrames(frames, 0.3);
    Animate *animate = Animate::create(animation);
    
    repeat = RepeatForever::create(animate);
    return repeat;
}

RepeatForever* pikachuMonster::movingAnimation() {
    int numFrame =2;
    cocos2d::Vector<cocos2d::SpriteFrame *> frames;
    SpriteFrameCache* frameCache = SpriteFrameCache::getInstance();
    char file[100] = {0};
    
    for (int i = 0; i < numFrame; i++) {
        sprintf(file, "spaceMonster1_%d.png", i+1);
        SpriteFrame *frame = frameCache->getSpriteFrameByName(file);
        frames.pushBack(frame);
    }
    
    Animation *animation = Animation::createWithSpriteFrames(frames, 0.3);
    Animate *animate = Animate::create(animation);
    
    repeat = RepeatForever::create(animate);
    return repeat;
}

RepeatForever* flyingDragonMonster::movingAnimation() {
    int numFrame =2;
    cocos2d::Vector<cocos2d::SpriteFrame *> frames;
    SpriteFrameCache* frameCache = SpriteFrameCache::getInstance();
    char file[100] = {0};
    
    for (int i = 0; i < numFrame; i++) {
        sprintf(file, "spaceMonster1_%d.png", i+1);
        SpriteFrame *frame = frameCache->getSpriteFrameByName(file);
        frames.pushBack(frame);
    }
    
    Animation *animation = Animation::createWithSpriteFrames(frames, 0.3);
    Animate *animate = Animate::create(animation);
    
    repeat = RepeatForever::create(animate);
    return repeat;
}

RepeatForever* turtleMonster::movingAnimation() {
    int numFrame =2;
    cocos2d::Vector<cocos2d::SpriteFrame *> frames;
    SpriteFrameCache* frameCache = SpriteFrameCache::getInstance();
    char file[100] = {0};
    
    for (int i = 0; i < numFrame; i++) {
        sprintf(file, "spaceMonster1_%d.png", i+1);
        SpriteFrame *frame = frameCache->getSpriteFrameByName(file);
        frames.pushBack(frame);
    }
    
    Animation *animation = Animation::createWithSpriteFrames(frames, 0.3);
    Animate *animate = Animate::create(animation);
    
    repeat = RepeatForever::create(animate);
    return repeat;
}


FiniteTimeAction* Monster::destroyedEffect(){
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

StrongAndSlowMonster* StrongAndSlowMonster::monster(void)
{
    StrongAndSlowMonster * monster = new StrongAndSlowMonster();
    if (monster && monster->initWithSpriteFrameName("spaceMonster2_1.png"))
    {
        monster->curHp = 1;
        monster->minMoveDuration = 3;
        monster->maxMoveDuration = 5;
        monster->destroying = 0;
        monster->locking = 0;
        monster->word = "monster";
        monster->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(monster);
    }
    return monster;
}

IvysaurMonster* IvysaurMonster::monster(void)
{
    IvysaurMonster * monster = new IvysaurMonster();
    if (monster && monster->initWithSpriteFrameName("spaceMonster3_1.png"))
    {
        monster->curHp = 1;
        monster->minMoveDuration = 2;
        monster->maxMoveDuration = 4;
        monster->destroying = 0;
        monster->locking = 0;
        monster->word = "ivysaur";
        monster->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(monster);
    }
    return monster;
}

CharizardMonster* CharizardMonster::monster(void)
{
    CharizardMonster * monster = new CharizardMonster();
    if (monster && monster->initWithFile("6-mega-x.png"))
    {
        monster->curHp = 1;
        monster->minMoveDuration = 6;
        monster->maxMoveDuration = 12;
        monster->destroying = 0;
        monster->locking = 0;
        monster->word = "charizard";
        monster->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(monster);
    }
    return monster;
}

flyingDragonMonster* flyingDragonMonster::monster(void)
{
    flyingDragonMonster * monster = new flyingDragonMonster();
    if (monster && monster->initWithFile("flyingDragon.png"))
    {
        monster->curHp = 1;
        monster->minMoveDuration = 6;
        monster->maxMoveDuration = 12;
        monster->destroying = 0;
        monster->locking = 0;
        monster->word = "flyingdragon";
        monster->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(monster);
    }
    return monster;
}

gengarMonster* gengarMonster::monster(void)
{
    gengarMonster * monster = new gengarMonster();
    if (monster && monster->initWithFile("gengar.png"))
    {
        monster->curHp = 1;
        monster->minMoveDuration = 6;
        monster->maxMoveDuration = 12;
        monster->destroying = 0;
        monster->locking = 0;
        monster->word = "gengar";
        monster->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(monster);
    }
    return monster;
}

pikachuMonster* pikachuMonster::monster(void)
{
    pikachuMonster * monster = new pikachuMonster();
    if (monster && monster->initWithFile("pikachu.png"))
    {
        monster->curHp = 1;
        monster->minMoveDuration = 6;
        monster->maxMoveDuration = 12;
        monster->destroying = 0;
        monster->locking = 0;
        monster->word = "pikachu";
        monster->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(monster);
    }
    return monster;
}

dragonMonster* dragonMonster::monster(void)
{
    dragonMonster * monster = new dragonMonster();
    if (monster && monster->initWithFile("dragon.png"))
    {
        monster->curHp = 1;
        monster->minMoveDuration = 6;
        monster->maxMoveDuration = 12;
        monster->destroying = 0;
        monster->locking = 0;
        monster->word = "dragon";
        monster->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(monster);
    }
    return monster;
}

turtleMonster* turtleMonster::monster(void)
{
    turtleMonster * monster = new turtleMonster();
    if (monster && monster->initWithFile("turtle.png"))
    {
        monster->curHp = 1;
        monster->minMoveDuration = 6;
        monster->maxMoveDuration = 12;
        monster->destroying = 0;
        monster->locking = 0;
        monster->word = "turtle";
        monster->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(monster);
    }
    return monster;
}
