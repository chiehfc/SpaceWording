//
//  Item.h
//  ZombieMatrix
//
//  Created by Chieh-Fu Chen on 1/30/15.
//
//

#ifndef __ZombieMatrix__Item__
#define __ZombieMatrix__Item__

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
    virtual cocos2d::RepeatForever *movingAnimation();
    cocos2d::RepeatForever *repeat;
};

#endif /* defined(__ZombieMatrix__Item__) */
