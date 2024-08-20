//
//  TJMobAdInterstitial.h
//  TJMobAdSDK
//
//  插屏
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

@class TJMobAdInterstitial;

@protocol TJMobAdInterstitialDelegate<NSObject>

@optional
/**
 *  插屏广告素材加载成功
 */
- (void)interstitialAdDidLoad:(TJMobAdInterstitial *)interstitialAd;

/**
 *  插屏广告素材加载失败
 */
- (void)interstitialAdFailToLoaded:(TJMobAdInterstitial *)interstitialAd error:(NSError *)error;

/**
 *  插屏广告曝光回调
 */
- (void)interstitialAdExposured:(TJMobAdInterstitial *)interstitialAd;

/**
 *  插屏广告点击回调
 */
- (void)interstitialAdClicked:(TJMobAdInterstitial *)interstitialAd;

/**
 *  插屏广告关闭回调
 */
- (void)interstitialAdClosed:(TJMobAdInterstitial *)interstitialAd;

@end

@interface TJMobAdInterstitial : NSObject


/**
 *  委托对象
 */
@property (nonatomic, weak) id<TJMobAdInterstitialDelegate> delegate;


/**
 *  构造方法
 */
- (instancetype)initWithPlacementId:(NSString *)placementId;


/**
 *  拉取广告超时时间，默认为5秒
 */
@property (nonatomic, assign) CGFloat fetchDelay;


/**
 *  广告请求
 */
- (void)load;


/**
 *  展示广告
 */
- (void)showInContainerView:(UIView *)view;


/**
 *  使用controller present 落地页
 */
@property (nonatomic, weak) UIViewController *presentAdViewController;


/**
 返回广告的eCPM，单位：分
 
 @return 成功返回一个大于等于0的值，-1表示无权限或后台出现异常
 */
- (NSInteger)eCPM;


@end
