//
//  Item.h
//  SpaceWording
//
//  Created by Chieh-Fu Chen on 1/30/15.
//
//

#ifndef __SpaceWording__Item__
#define __SpaceWording__Item__

#include <stdio.h>
#include "cocos2d.h"

class Item : public cocos2d::Sprite {
    
public:
    int curHp;
    int minMoveDuration;
    int maxMoveDuration;
    int destroying; // if destroying=1, should not be detected as monster.
    int locking; // if locking=1, it's locked by IME.
    std::string word;
    cocos2d::FiniteTimeAction *destroyedEffect();
    cocos2d::RepeatForever *repeat;
};

class HealthPack : public Item {
public:
    static HealthPack* healthPack(void);
    
    
};

#endif /* defined(__SpaceWording__Item__) */
