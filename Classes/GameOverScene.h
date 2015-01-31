//
//  GameOverScene.h
//  ZombieMatrix
//
//  Created by Chieh-Fu Chen on 11/20/14.
//
//

#ifndef __ZombieMatrix__GameOverScene__
#define __ZombieMatrix__GameOverScene__

#include <stdio.h>
#include "cocos2d.h"

class GameOverLayer : public cocos2d::LayerColor {

public:
    GameOverLayer():_label(NULL) {};
    ~GameOverLayer();
    virtual bool init();
    CREATE_FUNC(GameOverLayer);
    void gameOverDone();

    cocos2d::Label* getLabel() {return _label;}
    cocos2d::Label* getBestScoreLabel() {return _bestScoreLabel;}
private:
    cocos2d::Label* _label;
    cocos2d::Label* _bestScoreLabel;
};

class GameOverScene : public cocos2d::Scene {
public:
    GameOverScene():_layer(NULL) {};
    ~GameOverScene();
//    static cocos2d::Scene *createScene();
    virtual bool init();
    CREATE_FUNC(GameOverScene);
    
    GameOverLayer* getLayer() {return _layer;}
private:
    GameOverLayer* _layer;
};

#endif /* defined(__ZombieMatrix__GameOverScene__) */

