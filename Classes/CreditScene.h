//
//  CreditScene.h
//  ZombieMatrix
//
//  Created by Chieh-Fu Chen on 1/28/15.
//
//

#ifndef __ZombieMatrix__CreditScene__
#define __ZombieMatrix__CreditScene__

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

#endif /* defined(__ZombieMatrix__CreditScene__) */
