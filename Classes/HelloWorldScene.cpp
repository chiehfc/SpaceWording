#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "GameOverScene.h"
#include "GamePauseScene.h"
#include "GameLevelScene.h"
#include "Monster.h"
#include "Item.h"
#include "Weapon.h"
#include <time.h>

USING_NS_CC;
#define BULLET_LIMIT 5

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
    
    CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("Background.mp3", true);
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    _elapsedTime = 0;
    _projectilesDestroyed = 0;
    _shooting = 0;
    _reloadTime = 0;
    _bombReloadTime = 0;
    
    _weaponType = 0;

    swipeBegin = false;
    wordBomb = 0;
    
    int gameLevel = UserDefault::getInstance()->getIntegerForKey("GameLevel");
    float gameSecond = (float)1/(float)gameLevel;
    CCLOG("%f", gameSecond);
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
    
    player = Sprite::create("spaceShip.png", Rect(0, 0, 64, 64));
    player->setPosition(Vec2(player->getContentSize().width/2, winSize.height/2));
    this->addChild(player,3);
    
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
    
    this->weaponLabel = Label::createWithBMFont("double_boxy.fnt", "Weapon: ");
    weaponLabel->setScale(2.0f);
    weaponLabel->setPosition(Vec2(150, winSize.height-160));
    this->addChild(weaponLabel);
    
    image = Sprite::create("fireBall.png", Rect(0,0,32,32));
    image->setPosition(Vec2(300, winSize.height-140));
    this->addChild(image);
    
    //// Set TextField touch listener
    auto listenerText = EventListenerTouchOneByOne::create();
    listenerText->onTouchBegan = CC_CALLBACK_2(HelloWorld::textFieldOnTouchBegan,this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listenerText, textField);
    textField->setDelegate(this);
    
    //// Set Changing weapon touch listener
    auto swipeListener = EventListenerTouchOneByOne::create();
    swipeListener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onSwipeBegan, this);
    swipeListener->onTouchEnded = CC_CALLBACK_2(HelloWorld::onSwipeEnded, this);
    
//    swipeListener->setSwallowTouches(true);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(swipeListener, player);
    
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
    
    //// Set Shooting touch listener
    auto dispatcher = Director::getInstance()->getEventDispatcher();
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan,this);
    listener->onTouchMoved = CC_CALLBACK_2(HelloWorld::onTouchMoved,this);
    listener->onTouchEnded = CC_CALLBACK_2(HelloWorld::onTouchEnded,this);
    listener->setSwallowTouches(true);
    dispatcher->addEventListenerWithSceneGraphPriority(listener,this);
    
    this->schedule(schedule_selector(HelloWorld::gameLogic), gameSecond);

    this->schedule(schedule_selector(HelloWorld::itemLogic), 10.0);
    
    this->schedule(schedule_selector(HelloWorld::update));
    return true;
}

bool HelloWorld::onSwipeBegan(cocos2d::Touch *touch, cocos2d::Event *event) {
    
    Rect rect = Rect(this->player->getPosition().x - this->player->getContentSize().width/2,
                     this->player->getPosition().y - this->player->getContentSize().height/2 - 64,
                     128, 192);
    
    if(rect.containsPoint(touch->getLocation())) {
        if(!swipeBegin) {
            startSwipe = touch->getLocation();
            swipeBegin = true;
            CCLOG("%f, %f", this->player->getContentSize().width, this->player->getContentSize().height);
        }
    }
    return true;
}

void HelloWorld::onSwipeEnded(cocos2d::Touch *touch, cocos2d::Event *event) {
    if(swipeBegin) {
        endSwipe = touch->getLocation();
        Point delta = startSwipe - endSwipe;
        if(abs(delta.x) > abs(delta.y))
        {
            if(delta.x > 15)
            {
                CCLOG("SWIPE LEFT");
            }
            else if (delta.x < -15)
            {
                CCLOG("SWIPE RIGHT");
            }
        }
        else
        {
            if(delta.y > 15)
            {
                CCLOG("SWIPE DOWN");
                if(_weaponType<2) {
                    _weaponType++;
                }
            }
            else if (delta.y < -15)
            {
                CCLOG("SWIPE UP");
                if(_weaponType>0) {
                    _weaponType--;
                }
            }
        }
        swipeBegin = false;
    }
}

bool HelloWorld::textFieldOnTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event) {
    if(this->textField->getBoundingBox().containsPoint(touch->getLocation())) {
//        if (wordBomb==1) {
//            this->textField->attachWithIME();   // WORDING_MECHANICS
//            wordBomb=0;
//        }
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

    if(strcmp(sender->getString().c_str(), "fire")==0)
        this->_weaponType = 0;
    else if(strcmp(sender->getString().c_str(), "ice")==0)
        this->_weaponType = 1;
    else if(strcmp(sender->getString().c_str(), "thunder")==0)
        this->_weaponType = 2;
    else this->_weaponType = 0;
    
//    for(std::string word:_words)
//    {
//        if(strcmp(sender->getString().c_str(), word.c_str())==0) {
//            for(auto target:_targets) {
//                Monster *monster = (Monster*)target;
//                if(monster->word.compare(word)==0 && monster->locking==0) { // WORDING_MECHANICS
//                    targetsToDelete.pushBack(target);
//                }
//            }
//            for(Sprite* target: targetsToDelete) {
//                _targets.eraseObject(target);
//                Monster *monster = (Monster*)target;
//                monster->stopAction(monster->repeat);
//                auto seq = Sequence::createWithTwoActions(monster->destroyedEffect(), RemoveSelf::create());
//                monster->runAction(seq);
//
//                _projectilesDestroyed++;
//                CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("explosion_small.caf");
//            }
//        }
//    }
    
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
    
    if(_shooting != BULLET_LIMIT) {
    _shooting++;
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("laser_ship.caf");
    Vec2 location = touch->getLocation();
    
    Size winSize = Director::getInstance()->getWinSize();


    if (_weaponType==0)
        projectile = FireBall::fire();
    else if (_weaponType==1)
        projectile = IceBall::ice();
    else if (_weaponType==2)
        projectile = ThunderBall::thunder();

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
    UserDefault::getInstance()->setIntegerForKey("MonsterNumber", _monsterNumber);
    Director::getInstance()->pushScene(GamePauseScene::createScene());
}

void HelloWorld::gameLogic(float dt) {
    this->addTarget();
}

void HelloWorld::itemLogic(float dt) {
    Item *item;
    item = HealthPack::healthPack();
    
    item->setTag(3);
    _items.pushBack(item);
    
    Size winSize = Director::getInstance()->getWinSize();
    
    int minY = item->getContentSize().height/2;
    int maxY = winSize.height - item->getContentSize().height/2;
    
    int rangeY = maxY-minY;
    int actualY = (rand()%rangeY) + minY;
    
    item->setPosition(Point(winSize.width +(item->getContentSize().width/2), actualY));
    this->addChild(item);
    
    int minDuration = item->minMoveDuration;
    int maxDuration = item->maxMoveDuration;
    int rangeDuration = maxDuration - minDuration;
    int actualDuration = (rand()%rangeDuration)+ minDuration;
    
    FiniteTimeAction *actionMove = MoveTo::create((float)actualDuration, Vec2(0-item->getContentSize().width/2, actualY));
    
    FiniteTimeAction *actionMoveDone = CallFuncN::create(std::bind(&HelloWorld::spriteMoveFinished, this, std::placeholders::_1));
    
    item->runAction(Sequence::create(actionMove, actionMoveDone, NULL));
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
            int gameLevel = UserDefault::getInstance()->getIntegerForKey("GameLevel");
            auto gameOverScene = GameOverScene::create();
            char text[256];
            sprintf(text, "You Lose!!!\nGame Time: %.2f\nGame Level: %d", _elapsedTime, gameLevel);
            gameOverScene->getLayer()->getLabel()->setString(text);

            float bestScore;
            if(gameLevel==1)
                bestScore = UserDefault::getInstance()->getFloatForKey("BestScore-1");
            else if(gameLevel==2)
                bestScore = UserDefault::getInstance()->getFloatForKey("BestScore-2");
            else if(gameLevel==3)
                bestScore = UserDefault::getInstance()->getFloatForKey("BestScore-3");
            
            if(bestScore<_elapsedTime) {
                if(gameLevel==1)
                    UserDefault::getInstance()->setFloatForKey("BestScore-1", _elapsedTime);
                else if(gameLevel==2)
                    UserDefault::getInstance()->setFloatForKey("BestScore-2", _elapsedTime);
                else if(gameLevel==3)
                    UserDefault::getInstance()->setFloatForKey("BestScore-3", _elapsedTime);
                
                sprintf(text, "Best Score: %.2f", _elapsedTime);
            } else
                sprintf(text, "Best Score: %.2f", bestScore);
            
            gameOverScene->getLayer()->getBestScoreLabel()->setString(text);
            
            CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
            this->textField->detachWithIME();
            Director::getInstance()->replaceScene(gameOverScene);
            CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("explosion_large.caf");
        }
    }
    else if(sprite->getTag()==2) {
        _projectiles.eraseObject((Weapon *)sprite);
    }
    else if(sprite->getTag()==3) {
        _items.eraseObject(sprite);
    }
}

void HelloWorld::update(float dt) {
    
    _elapsedTime += dt;
    
    ////  Restricted bullets at most 3.
    ////  WORDING MECHANICS
    if(_shooting > 0 && _reloadTime > 0.5) {
        _reloadTime = 0;
        _shooting=0;
    } else if(_shooting > 0 && _reloadTime < 0.5) {
        _reloadTime+=dt;
    }
    _bombReloadTime+=dt;
    if(_bombReloadTime>10 && _monsterNumber<3)
    {
        _bombReloadTime=0;
        CCLOG("%d", _monsterNumber);
        _monsterNumber++;
    }
    
    if(_weaponType==0)
        image->setTexture(Director::getInstance()->getTextureCache()->addImage("fireBall.png"));
    else if(_weaponType==1)
        image->setTexture(Director::getInstance()->getTextureCache()->addImage("iceBall.png"));
    else if(_weaponType==2)
        image->setTexture(Director::getInstance()->getTextureCache()->addImage("thunderBall.png"));
    
//    if(wordBomb==0 && _bombReloadTime<5.0) {
//        _bombReloadTime+=dt;
//    } else if(wordBomb==0 && _bombReloadTime>5.0) {
//        wordBomb=1;
//        _bombReloadTime=0;
//    }
    
//    if(wordBomb==1)
//        this->textField->setString("Word Bomb is Ready!");
    
    bool monsterHit = false;
    cocos2d::Vector<Weapon *> projectilesToDelete;
    cocos2d::Vector<cocos2d::Sprite *> targetsToDelete;
    cocos2d::Vector<cocos2d::Sprite *> itemsToDelete;
    
    //for(auto projectile: this->_projectiles) {
    for(int i=0;i<_projectiles.size();i++) {
        auto projectile = _projectiles.at(i);
        Rect projectileRect = Rect(projectile->getPosition().x - (projectile->getContentSize().width/2),
                                   projectile->getPosition().y - (projectile->getContentSize().height/2),
                                   projectile->getContentSize().width,
                                   projectile->getContentSize().height);
        //// Monster Part
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
                if(monster->monsterType==projectile->weaponType)
                {
                    monster->curHp--;
                    if(monster->curHp<=0) {
                        targetsToDelete.pushBack(target);
                    }
                    projectilesToDelete.pushBack(projectile);
                    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("8bitExplosion.aiff");
                    break;
                }
            }
        }
        //// Item Part
        for(int j=0;j<_items.size();j++) {
            auto item = _items.at(j);
            Rect itemRect = Rect(item->getPosition().x - (item->getContentSize().width/2),
                                 item->getPosition().y - (item->getContentSize().height/2),
                                 item->getContentSize().width,
                                 item->getContentSize().height);
            if (projectileRect.intersectsRect(itemRect))
            {
                Item *healthPack = (Item*)item;
                healthPack->curHp--;
                if(healthPack->curHp<=0) {
                    wordBomb=1;
                    itemsToDelete.pushBack(item);
                }
                projectilesToDelete.pushBack(projectile);
                CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("8bitExplosion.aiff");
            }
        }
        
        for(auto item:itemsToDelete) {
            _items.eraseObject(item);
            Item *healthPack = (Item*)item;
            auto seq = Sequence::createWithTwoActions(healthPack->destroyedEffect(), RemoveSelf::create());
            healthPack->runAction(seq);
        }
        itemsToDelete.clear();
        
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
//    if (_projectilesDestroyed >= 50)
//    {
//        GameOverScene *gameOverScene = GameOverScene::create();
//        gameOverScene->getLayer()->getLabel()->setString("You Win!");
//        this->textField->detachWithIME();
//        CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
//        Director::getInstance()->replaceScene(gameOverScene);
//    }
}

