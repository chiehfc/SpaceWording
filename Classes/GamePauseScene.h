//
//  GamePauseScene.h
//  SpaceWording
//
//  Created by Chieh-Fu Chen on 1/17/15.
//
//

#ifndef __SpaceWording__GamePauseScene__
#define __SpaceWording__GamePauseScene__

#include <stdio.h>
#include "cocos2d.h"
#include "Monster.h"

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
    //std::vector<Monster *> & getPointer() {return _monsterType;}
    
    cocos2d::Label* getLabel() {return _label;}
private:
    cocos2d::Label* _label;
    std::map<std::string, std::string> _monsterFileName;
    std::vector<std::string> _monsterWords;
    cocos2d::Sprite *_monster;
    int _monsterNumber;
    int _selectedNumber;
    Monster* monster1;
    Monster* monster2;
    Monster* monster3;
    std::vector<Monster *> _monsterType;
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


#endif /* defined(__SpaceWording__GamePauseScene__) */
