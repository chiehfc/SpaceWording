//
//  Monster.h
//  SpaceWording
//
//  Created by Chieh-Fu Chen on 11/25/14.
//
//

#ifndef __SpaceWording__Monster__
#define __SpaceWording__Monster__

#include <stdio.h>
#include "cocos2d.h"

class Monster : public cocos2d::Sprite {

public:
    int curHp;
    int minMoveDuration;
    int maxMoveDuration;
    int destroying; // if destroying=1, should not be detected as monster.
    int locking; // if locking=1, it's locked by IME.
    int monsterType;
    std::string word;
    cocos2d::FiniteTimeAction *destroyedEffect();
    virtual cocos2d::RepeatForever *movingAnimation();
    cocos2d::RepeatForever *repeat;
};

class WeakAndFastMonster : public Monster
{
    public:
    static WeakAndFastMonster* monster(void);
    cocos2d::RepeatForever *movingAnimation();
};

class StrongAndSlowMonster : public Monster
{
    public:
    static StrongAndSlowMonster* monster(void);
    cocos2d::RepeatForever *movingAnimation();
};

class IvysaurMonster : public Monster
{
    public:
    static IvysaurMonster* monster(void);
    cocos2d::RepeatForever *movingAnimation();
};

class CharizardMonster : public Monster
{
    public:
    static CharizardMonster* monster(void);
//    cocos2d::RepeatForever *movingAnimation();
};

class flyingDragonMonster : public Monster
{
    public:
    static flyingDragonMonster* monster(void);
//    cocos2d::RepeatForever *movingAnimation();
};

class pikachuMonster : public Monster
{
    public:
    static pikachuMonster* monster(void);
//    cocos2d::RepeatForever *movingAnimation();
};

class turtleMonster : public Monster
{
    public:
    static turtleMonster* monster(void);
//    cocos2d::RepeatForever *movingAnimation();
};

class gengarMonster : public Monster
{
    public:
    static gengarMonster* monster(void);
//    cocos2d::RepeatForever *movingAnimation();
};

class dragonMonster : public Monster
{
    public:
    static dragonMonster* monster(void);
//    cocos2d::RepeatForever *movingAnimation();
};

#endif /* defined(__SpaceWording__Monster__) */
