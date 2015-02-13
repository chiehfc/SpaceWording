//
//  BannerViewController.h
//  SpaceWording
//
//  Created by Chieh-Fu Chen on 2/12/15.
//
//

#ifndef SpaceWording_BannerViewController_h
#define SpaceWording_BannerViewController_h


#import <UIKit/UIKit.h>
#import <GoogleMobileAds/GADBannerViewDelegate.h>

@interface BannerViewController : UIViewController <GADBannerViewDelegate>

- (instancetype)initWithContentViewController:(UIViewController *)contentController;
- (void) hideBanner;
- (void) showBanner;

@end

#endif
