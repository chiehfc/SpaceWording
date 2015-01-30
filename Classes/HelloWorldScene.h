#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

class BackgroundLayer : public cocos2d::Layer
{
    public:
    virtual bool init();
    void update(float dt);
    CREATE_FUNC(BackgroundLayer);
private:
    cocos2d::Sprite *background1;
    cocos2d::Sprite *background2;
};

class HelloWorld : public cocos2d::Layer, public cocos2d::TextFieldDelegate
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    void gamePauseCallback(cocos2d::Ref* pSender);
    
    void addTarget();
    void spriteMoveFinished(Node *sender);
    void gameLogic(float dt);
    
    bool textFieldOnTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event);
    bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event);
    void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event);
    bool onTextFieldAttachWithIME(cocos2d::TextFieldTTF *sender);
    bool onTextFieldDetachWithIME(cocos2d::TextFieldTTF *sender);
    void update(float dt);
    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
    
    
protected:
    cocos2d::Vector<cocos2d::Sprite *> _targets;
    cocos2d::Vector<cocos2d::Sprite *> _projectiles;
    std::vector<std::string> _words;
    int _monsterNumber;
    int _projectilesDestroyed;
    cocos2d::Label *scoreLabel;
    cocos2d::Label *wordLabel;
    cocos2d::Label *timeLabel;
    float _elapsedTime;
    cocos2d::TextFieldTTF *textField;
    int _shooting;
    float _reloadTime;
    int wordBomb;
    
    BackgroundLayer* _layer;
};



#endif // __HELLOWORLD_SCENE_H__
