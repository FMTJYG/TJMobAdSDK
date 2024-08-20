//
//  TJMobAdNative.h
//  TJMobAdSDK
//
//  信息流广告（自渲染）
//

#import <UIKit/UIKit.h>
#import <Foundation/Foundation.h>
#import <TJMobAdSDK/TJMobAdNativeRenderModel.h>

@class TJMobAdNative;

@protocol TJMobAdNativeDelegate<NSObject>

@optional
/**
 *  广告素材加载成功
 */
- (void)nativeAdDidLoad:(TJMobAdNative *)nativeAd;

/**
 *  广告素材加载失败
 */
- (void)nativeAdFailToLoaded:(TJMobAdNative *)nativeAd error:(NSError *)error;

/**
 *  广告曝光回调
 */
- (void)nativeAdExposured:(TJMobAdNative *)nativeAd;

/**
 *  广告点击回调
 */
- (void)nativeAdClicked:(TJMobAdNative *)nativeAd;

@end

@interface TJMobAdNative : NSObject


/**
 *  委托对象
 */
@property (nonatomic, weak) id<TJMobAdNativeDelegate> delegate;


/**
 *  构造方法
 */
- (instancetype)initWithPlacementId:(NSString *)placementId;


/**
 *  拉取广告超时时间，默认为5秒
 */
@property (nonatomic, assign) CGFloat fetchDelay;


/**
 *  发起广告请求
 */
- (void)load;


/**
 *  自渲染load成功返回的数据，在renderingAdDidLoad获取素材
 */
@property (nonatomic, strong) TJMobAdNativeRenderModel *renderModel;


/**
 *  自渲染view注册，涉及到曝光点击计费
 */
- (void)registerContainer:(UIView *)containerView;


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
