//
//  HintScene.h
//  SpaceWording
//
//  Created by Chieh-Fu Chen on 2/11/15.
//
//

#ifndef __SpaceWording__HintScene__
#define __SpaceWording__HintScene__

#include <stdio.h>
#include "cocos2d.h"

class HintScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene *createScene();
    virtual bool init();
    CREATE_FUNC(HintScene);
    
    //    virtual void registerWithTouchDispatcher();
    //    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    //
    //    CCClippingNode* clip;
    //    CCSprite* tip;
    
};

#endif /* defined(__SpaceWording__HintScene__) */
