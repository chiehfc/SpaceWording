//
//  GraphicsScene.h
//  ZombieMatrix
//
//  Created by Chieh-Fu Chen on 11/18/14.
//
//

#ifndef __ZombieMatrix__GraphicsScene__
#define __ZombieMatrix__GraphicsScene__

#include <stdio.h>
#include "cocos2d.h"

#endif /* defined(__ZombieMatrix__GraphicsScene__) */

class GraphicsScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(GraphicsScene);
};

