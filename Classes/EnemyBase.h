//
//  EnemyBase.h
//  SpaceWording
//
//  Created by Chieh-Fu Chen on 11/25/14.
//
//

#ifndef __SpaceWording__EnemyBase__
#define __SpaceWording__EnemyBase__

#include <stdio.h>
#include "cocos2d.h"

class EnemyBase : public cocos2d::Sprite {
public:
    virtual bool init() override;
    CREATE_FUNC(EnemyBase);
    cocos2d::Animation* createAnimation(std::string prefixName, int framesNum, float delay);
    
};

#endif /* defined(__SpaceWording__EnemyBase__) */
