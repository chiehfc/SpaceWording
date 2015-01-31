#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "GameOverScene.h"
#include "GamePauseScene.h"
#include "GameLevelScene.h"
#include "Monster.h"
#include <time.h>

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

bool BackgroundLayer::init()
{
    Size winSize = Director::getInstance()->getWinSize();

    this->background1 = Sprite::create("menu_background.png");
    background1->setPosition(Vec2(winSize.width/2, winSize.height/2));
    background1->setScale(2.0f, 2.0f);
    this->addChild(background1);
    
    this->background2 = Sprite::create("menu_background.png");
    background2->setPosition(Vec2(winSize.width/2+background2->getContentSize().width*2, winSize.height/2));
    background2->setScale(2.0f, 2.0f);
    this->addChild(background2);

    this->schedule(schedule_selector(BackgroundLayer::update));
    
    return true;
}

void BackgroundLayer::update(float dt)
{
    
    float deltaA = -2;
    Size winSize = Director::getInstance()->getWinSize();
    
    if(this->background1->getPositionX() <= -background1->getContentSize().width) {
        background1->setPositionX(winSize.width/2+background1->getContentSize().width*2);
    } else if(this->background2->getPositionX() <= -background2->getContentSize().width) {
        background2->setPositionX(winSize.width/2+background2->getContentSize().width*2);
    } else {
        background1->setPositionX(background1->getPositionX()+deltaA);
        background2->setPositionX(background2->getPositionX()+deltaA);
    }
    
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    auto layerr = BackgroundLayer::create();
//    layerr->setZOrder(2);
    this->addChild(layerr);
    
    CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("SpaceGame.caf", true);
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    _elapsedTime = 0;
    _projectilesDestroyed = 0;
    _shooting = 0;
    _reloadTime = 0;
    _bombReloadTime = 0;
    wordBomb = 0;
    
    Size winSize = Director::getInstance()->getWinSize();
    
    
    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    this->_monsterNumber = UserDefault::getInstance()->getIntegerForKey("MonsterNumber");
    CCLOG("%d", this->_monsterNumber);
    
    /////////////////////////////
    // ADD PAUSE BUTTON
    /////////////////////////////
    
    auto gamePauseItem = MenuItemImage::create(
                                           "pause.png",
                                           "pause_pressed.png",
                                           CC_CALLBACK_1(HelloWorld::gamePauseCallback, this));
    
    gamePauseItem->setPosition(Vec2(winSize.width*0.85, winSize.height*0.85));
    gamePauseItem->setScale(1.5f);
    auto gamePause = Menu::create(gamePauseItem, NULL);
    gamePause->setPosition(Vec2::ZERO);
    this->addChild(gamePause, 1);
    
    
    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
    Sprite *player = Sprite::create("spaceShip.png", Rect(0, 0, 64, 64));
    player->setPosition(Vec2(player->getContentSize().width/2, winSize.height/2));
    this->addChild(player,0);
    
    this->scoreLabel = Label::createWithBMFont("double_boxy.fnt", "Score: 0");
    scoreLabel->setScale(2.0f);
    scoreLabel->setPosition(Vec2(150, winSize.height-80));
    this->addChild(scoreLabel);

    this->timeLabel = Label::createWithBMFont("double_boxy.fnt", "Time: 0");
    timeLabel->setScale(2.0f);
    timeLabel->setPosition(Vec2(600, winSize.height-80));
    this->addChild(timeLabel);
    
    this->textField = TextFieldTTF::textFieldWithPlaceHolder("Word Input", Size(200,200), TextHAlignment::CENTER, "fonts/Marker Felt.ttf", 32);
    textField->setPosition(Vec2(150, winSize.height/2));
    this->addChild(textField);
    
    auto listenerText = EventListenerTouchOneByOne::create();
    
    listenerText->onTouchBegan = CC_CALLBACK_2(HelloWorld::textFieldOnTouchBegan,this);
    
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listenerText, textField);
    textField->setDelegate(this);
    
    // put "word" into vector.
    _words.push_back("monster");
    _words.push_back("ninja");
    _words.push_back("ivysaur");
    _words.push_back("charizard");
    _words.push_back("dragon");
    _words.push_back("flyingdragon");
    _words.push_back("gengar");
    _words.push_back("pikachu");
    _words.push_back("turtle");
    
    auto dispatcher = Director::getInstance()->getEventDispatcher();
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan,this);
    listener->onTouchMoved = CC_CALLBACK_2(HelloWorld::onTouchMoved,this);
    listener->onTouchEnded = CC_CALLBACK_2(HelloWorld::onTouchEnded,this);
    listener->setSwallowTouches(true);
    dispatcher->addEventListenerWithSceneGraphPriority(listener,this);
    
    this->schedule(schedule_selector(HelloWorld::gameLogic), 1.0);

    this->schedule(schedule_selector(HelloWorld::update));
    return true;
}

bool HelloWorld::textFieldOnTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event) {
    if(this->textField->getBoundingBox().containsPoint(touch->getLocation())) {
        if (wordBomb==1) {
            this->textField->attachWithIME();   // WORDING_MECHANICS
            wordBomb=0;
        }
    }
    else {
        this->textField->detachWithIME();
    }
    return false;
}

bool HelloWorld::onTextFieldAttachWithIME(cocos2d::TextFieldTTF *sender) {
    sender->setString("");
    this->setPosition(Vec2(0, 100));
    return false;
}

bool HelloWorld::onTextFieldDetachWithIME(cocos2d::TextFieldTTF *sender) {
    cocos2d::Vector<cocos2d::Sprite *> targetsToDelete;
    this->setPosition(Vec2(0, 0));
    
    for(std::string word:_words)
    {
        if(strcmp(sender->getString().c_str(), word.c_str())==0) {
            for(auto target:_targets) {
                Monster *monster = (Monster*)target;
                if(monster->word.compare(word)==0 && monster->locking==0) { // WORDING_MECHANICS
                    targetsToDelete.pushBack(target);
                }
            }
            for(Sprite* target: targetsToDelete) {
                _targets.eraseObject(target);
                Monster *monster = (Monster*)target;
                monster->stopAction(monster->repeat);
                auto seq = Sequence::createWithTwoActions(monster->destroyedEffect(), RemoveSelf::create());
                monster->runAction(seq);

                _projectilesDestroyed++;
                CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("explosion_small.caf");
            }
        }
    }
    
    char textmsg[256];
    sprintf(textmsg,"Score: %d", _projectilesDestroyed);
    this->scoreLabel->setString(textmsg);
    
    return false;
}

bool HelloWorld::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event) {
    cocos2d::Vec2 p = touch->getLocation();
    cocos2d::Rect rect = this->getBoundingBox();
    
    // click on specific monster
    for(auto target: _targets) {
        if(target->getBoundingBox().containsPoint(touch->getLocation())) {

        //    Monster *monster = (Monster*)target;  // WORDING_MECHANICS
        //    monster->locking = 1;                 // WORDING_MECHANICS
        //    this->textField->attachWithIME();     // WORDING_MECHANICS
        }
    }
    
    if(rect.containsPoint(p))
    {
        return true; // to indicate that we have consumed it.
    }
    
    return false; // we did not consume this event, pass thru.
    
}

void HelloWorld::onTouchEnded(Touch *touch, Event *event) {
    
    if(_shooting!=3) {
    _shooting++;
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("laser_ship.caf");
    Vec2 location = touch->getLocation();
    
    Size winSize = Director::getInstance()->getWinSize();
    Sprite *projectile = Sprite::create("Projectile.png", Rect(0, 0, 20, 20));
    projectile->setPosition(Vec2(20, winSize.height/2));
    
    projectile->setTag(2);
    _projectiles.pushBack(projectile);
    
    int offX = location.x - projectile->getPosition().x;
    int offY = location.y - projectile->getPosition().y;
    
    if(offX <= 0) return;
    this->addChild(projectile);
    
    int realX = winSize.width + (projectile->getContentSize().width/2);
    
    float ratio = (float)offY / (float)offX;
    int realY = (realX*ratio) + projectile->getPosition().y;
    Point realDest = Point(realX, realY);
    
    // Determine the length of how far we're shooting
    int offRealX = realX - projectile->getPosition().x;
    int offRealY = realY - projectile->getPosition().y;
    float length = sqrtf((offRealX * offRealX)
                         + (offRealY*offRealY));
    float velocity = 480/1; // 480pixels/1sec
    float realMoveDuration = length/velocity;

    // Move projectile to actual endpoint
    projectile->runAction(
                          Sequence::create(MoveTo::create(realMoveDuration, realDest),
                                             CallFuncN::create(std::bind(&HelloWorld::spriteMoveFinished, this, std::placeholders::_1)),NULL) );
    }
}

void HelloWorld::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif

    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

void HelloWorld::gamePauseCallback(Ref* pSender) {
    Director::getInstance()->pushScene(GamePauseScene::createScene());
}

void HelloWorld::gameLogic(float dt) {
    this->addTarget();
}

void HelloWorld::addTarget() {
    
    Monster *targetCool[9];
    targetCool[0] = WeakAndFastMonster::monster();
    targetCool[1] = StrongAndSlowMonster::monster();
    targetCool[2] = IvysaurMonster::monster();
    targetCool[3] = CharizardMonster::monster();
    targetCool[4] = pikachuMonster::monster();
    targetCool[5] = flyingDragonMonster::monster();
    targetCool[6] = dragonMonster::monster();
    targetCool[7] = gengarMonster::monster();
    targetCool[8] = turtleMonster::monster();
    
    // randomly generate monsters
    Monster *target = NULL;
    int temp = CCRANDOM_0_1()*100;
    temp = temp % _monsterNumber;
    target = targetCool[temp];

    Size winSize = Director::getInstance()->getWinSize();
    
    if(target->movingAnimation()!=NULL)
        target->runAction(target->movingAnimation());
    
    target->setTag(1);
    _targets.pushBack(target);
    
    int minY = target->getContentSize().height/2;
    int maxY = winSize.height - target->getContentSize().height/2;
    
    int rangeY = maxY-minY;
    int actualY = (rand()%rangeY) + minY;
    
    target->setPosition(Point(winSize.width +(target->getContentSize().width/2), actualY));
    this->addChild(target);
    
    int minDuration = target->minMoveDuration;
    int maxDuration = target->maxMoveDuration;
    int rangeDuration = maxDuration - minDuration;
    int actualDuration = (rand()%rangeDuration)+ minDuration;
    
    FiniteTimeAction *actionMove = MoveTo::create((float)actualDuration, Vec2(0-target->getContentSize().width/2, actualY));
    
    FiniteTimeAction *actionMoveDone = CallFuncN::create(std::bind(&HelloWorld::spriteMoveFinished, this, std::placeholders::_1));
    
    target->runAction(Sequence::create(actionMove, actionMoveDone, NULL));
}

void HelloWorld::spriteMoveFinished(Node *sender) {
    Sprite *sprite = (Sprite*)sender;
    
    if(sprite->getTag()==1) {
        _targets.eraseObject(sprite);
        Monster *target = (Monster*)sprite;
        if(target->destroying!=1)
        {
            auto gameOverScene = GameOverScene::create();
            char text[256];
            sprintf(text, "You Lose!!!\nGame Time: %.2f\nGame Level: %d", _elapsedTime, _monsterNumber);
            gameOverScene->getLayer()->getLabel()->setString(text);
            CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
            this->textField->detachWithIME();
            Director::getInstance()->replaceScene(gameOverScene);
            CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("explosion_large.caf");
        }
    }
    else if(sprite->getTag()==2) {
        _projectiles.eraseObject(sprite);
    }
}

void HelloWorld::update(float dt) {
    
    _elapsedTime += dt;
    
    ////  Restricted bullets at most 3.
    ////  WORDING MECHANICS
    if(_shooting > 0 && _reloadTime > 0.5) {
        _reloadTime = 0;
        _shooting--;
    } else if(_shooting > 0 && _reloadTime < 0.5) {
        _reloadTime+=dt;
    }
    
    if(wordBomb==0 && _bombReloadTime<5.0) {
        _bombReloadTime+=dt;
    } else if(wordBomb==0 && _bombReloadTime>5.0) {
        wordBomb=1;
        _bombReloadTime=0;
    }
    
    if(wordBomb==1)
        this->textField->setString("Word Bomb is Ready!");
    
    bool monsterHit = false;
    cocos2d::Vector<cocos2d::Sprite *> projectilesToDelete;
    cocos2d::Vector<cocos2d::Sprite *> targetsToDelete;
    
    //for(auto projectile: this->_projectiles) {
    for(int i=0;i<_projectiles.size();i++) {
        auto projectile = _projectiles.at(i);
        Rect projectileRect = Rect(projectile->getPosition().x - (projectile->getContentSize().width/2),
                                   projectile->getPosition().y - (projectile->getContentSize().height/2),
                                   projectile->getContentSize().width,
                                   projectile->getContentSize().height);
    
        for(int j=0;j<_targets.size();j++) {
            auto target = _targets.at(j);
            Rect targetRect = Rect(target->getPosition().x - (target->getContentSize().width/2),
                                   target->getPosition().y - (target->getContentSize().height/2),
                                   target->getContentSize().width,
                                   target->getContentSize().height);
            if (projectileRect.intersectsRect(targetRect))
            {
                //// SHOOTING MECHANICS
                monsterHit = true;
                Monster *monster = (Monster*)target;

                monster->curHp--;
                if(monster->curHp<=0) {
                    targetsToDelete.pushBack(target);
                }
                projectilesToDelete.pushBack(projectile);
                CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("explosion_small.caf");
                break;
            }
        }
        for(Sprite* target: targetsToDelete) {
            _targets.eraseObject(target);
            Monster *monster = (Monster*)target;

            monster->stopAction(monster->repeat);
            
            auto seq = Sequence::createWithTwoActions(monster->destroyedEffect(), RemoveSelf::create());
            monster->runAction(seq);
            
//            this->removeChild(target, true);
            _projectilesDestroyed++;
            char text[256];
            sprintf(text,"Score: %d", _projectilesDestroyed);
            this->scoreLabel->setString(text);
        }
        if (targetsToDelete.size() > 0)
        {
            if (monsterHit) {
                CCLOG("WOW?");
                
            }
        }
        targetsToDelete.clear();
        for(auto projectile: projectilesToDelete) {
            _projectiles.eraseObject(projectile);
            this->removeChild(projectile, true);
        }
        projectilesToDelete.clear();
    }

    
    char text1[256];
    sprintf(text1,"Time: %.2f", _elapsedTime);
    this->timeLabel->setString(text1);
    
    // Game Win Scene
    if (_projectilesDestroyed >= 50)
    {
        GameOverScene *gameOverScene = GameOverScene::create();
        gameOverScene->getLayer()->getLabel()->setString("You Win!");
        this->textField->detachWithIME();
        CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
        Director::getInstance()->replaceScene(gameOverScene);
    }
}

