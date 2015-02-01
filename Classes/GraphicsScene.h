//
//  GraphicsScene.h
//  SpaceWording
//
//  Created by Chieh-Fu Chen on 11/18/14.
//
//

#ifndef __SpaceWording__GraphicsScene__
#define __SpaceWording__GraphicsScene__

#include <stdio.h>
#include "cocos2d.h"

class GraphicsScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(GraphicsScene);
};

#endif /* defined(__SpaceWording__GraphicsScene__) */



