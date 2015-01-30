//
//  EnemyBase.h
//  ZombieMatrix
//
//  Created by Chieh-Fu Chen on 11/25/14.
//
//

#ifndef __ZombieMatrix__EnemyBase__
#define __ZombieMatrix__EnemyBase__

#include <stdio.h>
#include "cocos2d.h"

class EnemyBase : public cocos2d::Sprite {
public:
    virtual bool init() override;
    CREATE_FUNC(EnemyBase);
    cocos2d::Animation* createAnimation(std::string prefixName, int framesNum, float delay);
    
};

#endif /* defined(__ZombieMatrix__EnemyBase__) */
