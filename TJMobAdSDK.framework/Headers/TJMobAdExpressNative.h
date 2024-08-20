//
//  TJMobAdExpressNative.h
//  TJMobADSDKLib
//
//  信息流广告（模板渲染）
//

#import <UIKit/UIKit.h>
#import <Foundation/Foundation.h>

@class TJMobAdExpressNative;

@protocol TJMobAdExpressNativeDelegate<NSObject>

@optional
/**
 *  广告素材加载成功
 */
- (void)expressNativeAdDidLoad:(TJMobAdExpressNative *)nativeAd;

/**
 *  广告素材加载失败
 */
- (void)expressNativeAdFailToLoaded:(TJMobAdExpressNative *)nativeAd error:(NSError *)error;

/**
 *  广告曝光回调
 */
- (void)expressNativeAdExposured:(TJMobAdExpressNative *)nativeAd;

/**
 *  广告点击回调
 */
- (void)expressNativeAdClicked:(TJMobAdExpressNative *)nativeAd;

@end

@interface TJMobAdExpressNative : NSObject


/**
 *  委托对象
 */
@property (nonatomic, weak) id<TJMobAdExpressNativeDelegate> delegate;


/**
 *  构造方法
 */
- (instancetype)initWithPlacementId:(NSString *)placementId;


/**
 *  拉取广告超时时间，默认为5秒
 */
@property (nonatomic, assign) CGFloat fetchDelay;


/**
 *  nativeAdDidLoad成功后返回的模板view
 */
@property (nonatomic, strong) UIView *templateView;


/**
 *  使用controller present 落地页
 */
@property (nonatomic, weak) UIViewController *presentAdViewController;


/**
 *  发起广告请求
 */
- (void)load;


/**
 返回广告的eCPM，单位：分
 
 @return 成功返回一个大于等于0的值，-1表示无权限或后台出现异常
 */
- (NSInteger)eCPM;


@end
