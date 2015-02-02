//
//  Weapon.cpp
//  SpaceWording
//
//  Created by Chieh-Fu Chen on 2/1/15.
//
//

#include "Weapon.h"

USING_NS_CC;

FireBall* FireBall::fire(void)
{
    FireBall* fire = new FireBall();
    
    if (fire && fire->initWithFile("fireBall.png"))
    {
        fire->weaponType = 0;
        fire->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(fire);
    }
    
    return fire;
}

IceBall* IceBall::ice(void)
{
    IceBall* ice = new IceBall();
    
    if (ice && ice->initWithFile("iceBall.png"))
    {
        ice->weaponType = 1;
        ice->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(ice);
    }
    
    return ice;
}

ThunderBall* ThunderBall::thunder(void)
{
    ThunderBall* thunder = new ThunderBall();
    
    if (thunder && thunder->initWithFile("thunderBall.png"))
    {
        thunder->weaponType = 2;
        thunder->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(thunder);
    }
    
    return thunder;
}