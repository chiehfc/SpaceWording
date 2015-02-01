//
//  CreditScene.h
//  SpaceWording
//
//  Created by Chieh-Fu Chen on 1/28/15.
//
//

#ifndef __SpaceWording__CreditScene__
#define __SpaceWording__CreditScene__

#include <stdio.h>
#include "cocos2d.h"

class CreditScene:public cocos2d::Layer {
public:
    virtual bool init();
    static cocos2d::Scene *createScene();
    CREATE_FUNC(CreditScene);
    bool testLabelOnTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event);
    
private:
    void returnPressed(cocos2d::Ref *pSender);
    cocos2d::Label *testLabel;
};

#endif /* defined(__SpaceWording__CreditScene__) */
