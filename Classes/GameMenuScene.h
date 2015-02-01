//
//  GameMenuScene.h
//  SpaceWording
//
//  Created by Chieh-Fu Chen on 11/24/14.
//
//

#ifndef __SpaceWording__GameMenuScene__
#define __SpaceWording__GameMenuScene__

#include <stdio.h>
#include "cocos2d.h"

class GameMenuScene:public cocos2d::Layer {
public:
    virtual bool init();
    static cocos2d::Scene *createScene();
    CREATE_FUNC(GameMenuScene);
    bool testLabelOnTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event);
    
    
private:
    void playPressed(cocos2d::Ref *pSender);
    void creditPressed(cocos2d::Ref *pSender);
    cocos2d::Label *testLabel;
};


#endif /* defined(__SpaceWording__GameMenuScene__) */
