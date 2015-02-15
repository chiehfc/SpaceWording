//
//  Weapon.h
//  SpaceWording
//
//  Created by Chieh-Fu Chen on 2/1/15.
//
//

#ifndef __SpaceWording__Weapon__
#define __SpaceWording__Weapon__

#include <stdio.h>
#include "cocos2d.h"

class Weapon : public cocos2d::Sprite {
public:
    int weaponType = 0;
    
    

};

class FireBall : public Weapon {
public:
    static FireBall* fire(void);
    
};

class IceBall : public Weapon {
public:
    static IceBall* ice(void);
    
};

class ThunderBall : public Weapon {
public:
    static ThunderBall* thunder(void);
};

class DarkBall : public Weapon {
public:
    static DarkBall* dark(void);
};

#endif /* defined(__SpaceWording__Weapon__) */
