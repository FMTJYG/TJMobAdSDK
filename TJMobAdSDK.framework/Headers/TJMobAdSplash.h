//
//  TJMobAdSplash.h
//  TJMobAdSDK
//
//  开屏广告
//  

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

@class TJMobAdSplash;

@protocol TJMobAdSplashDelegate<NSObject>

@optional
/**
 *  开屏广告素材加载成功
 */
- (void)splashAdDidLoad:(TJMobAdSplash *)splashAd;

/**
 *  开屏广告素材加载失败
 */
- (void)splashAdFailToLoad:(TJMobAdSplash *)splashAd error:(NSError *)error;

/**
 *  开屏广告曝光回调
 */
- (void)splashAdExposured:(TJMobAdSplash *)splashAd;

/**
 *  开屏广告点击回调
 */
- (void)splashAdClicked:(TJMobAdSplash *)splashAd;

/**
 *  开屏广告关闭回调
 */
- (void)splashAdClosed:(TJMobAdSplash *)splashAd;

@end


@interface TJMobAdSplash : NSObject


/**
 *  委托对象
 */
@property (nonatomic, weak) id<TJMobAdSplashDelegate> delegate;


/**
 *  构造方法
 */
- (instancetype)initWithPlacementId:(NSString *)placementId;


/**
 *  拉取广告超时时间，默认为5秒
 */
@property (nonatomic, assign) CGFloat fetchDelay;


/**
 *  屏幕底部logo图片
 */
@property (nonatomic, strong) UIImage *logoImage;


/**
 *  发起拉取广告请求，只拉取不展示
 *  详解：广告素材及广告图片拉取成功后会回调splashAdDidLoad方法，当拉取失败时会回调splashAdFailToLoad方法
 */
- (void)load;


/**
 *  展示全屏广告
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


/**
 销毁
 */
- (void)destroy;


@end
