//
//  GamePauseScene.h
//  ZombieMatrix
//
//  Created by Chieh-Fu Chen on 1/17/15.
//
//

#ifndef __ZombieMatrix__GamePauseScene__
#define __ZombieMatrix__GamePauseScene__

#include <stdio.h>
#include "cocos2d.h"

class GamePauseLayer : public cocos2d::LayerColor {
    
public:
    GamePauseLayer():_label(NULL) {};
    ~GamePauseLayer();
    virtual bool init();
    CREATE_FUNC(GamePauseLayer);
    void gamePauseDone();
    void gameResumeCallback(cocos2d::Ref* pSender);
    void minusMonsterNumberCallback(cocos2d::Ref* pSender);
    void addMonsterNumberCallback(cocos2d::Ref* pSender);
    
    
    cocos2d::Label* getLabel() {return _label;}
private:
    cocos2d::Label* _label;
    std::map<std::string, std::string> _monsterFileName;
    std::vector<std::string> _monsterWords;
    cocos2d::Sprite *_monster;
    int _monsterNumber;
    int _selectedNumber;
};

class GamePauseScene:public cocos2d::Layer {
public:
    GamePauseScene():_layer(NULL) {};
    ~GamePauseScene();
    virtual bool init();
    static cocos2d::Scene *createScene();
    CREATE_FUNC(GamePauseScene);
    
    GamePauseLayer* getLayer() {return _layer;}
private:
    GamePauseLayer* _layer;

};


#endif /* defined(__ZombieMatrix__GamePauseScene__) */
