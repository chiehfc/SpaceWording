//
//  GameLevelScene.h
//  SpaceWording
//
//  Created by Chieh-Fu Chen on 1/17/15.
//
//

#ifndef __SpaceWording__GameLevelScene__
#define __SpaceWording__GameLevelScene__

#include <stdio.h>
#include "cocos2d.h"

class GameLevelLayer : public cocos2d::LayerColor {
    
public:
    GameLevelLayer():_label(NULL) {};
    ~GameLevelLayer();
    virtual bool init();
    CREATE_FUNC(GameLevelLayer);
    void gameLevelCallback(cocos2d::Ref* pSender);
    void addMonsterNumberCallback(cocos2d::Ref* pSender);
    void minusMonsterNumberCallback(cocos2d::Ref* pSender);
    
    cocos2d::Label* getLabel() {return _label;}
    int getMonsterNumber() {return _monsterNumber;}
private:
    cocos2d::Label* _label;
    int _monsterNumber;
};

class GameLevelScene:public cocos2d::Layer {
public:
    GameLevelScene():_layer(NULL) {};
    ~GameLevelScene();
    virtual bool init();
    static cocos2d::Scene *createScene();
    CREATE_FUNC(GameLevelScene);
    
    GameLevelLayer* getLayer() {return _layer;}
private:
    GameLevelLayer* _layer;
};



#endif /* defined(__SpaceWording__GameLevelScene__) */
