# TJMobAdSDK 接入文档   
      
## 接入提示
1.首先需要在平台注册应用信息，注册通过后下载并集成SDK到您的APP内。   
2.广告产品接入需要先初始化SDK，并填写平台注册生成的应用appId。然后根据您的需求接入不同的广告产品，并按照规范渲染各类广告产品。  
3.每一种类型广告的接入都需要placementId（广告位id）。   
4.信息流自渲染广告需要特殊注意调用register方法注册曝光给到SDK，否则无法计费。   

## SDK集成
### CocoaPods集成

SDK支持pod方式接入，只需配置pod环境，在podfile文件中加入以下代码即可接入成功。开发者可按照以下方式进行接入
#### Podfile

为了您能集成TJMobAdSDK到Xcode工程中，请在Podfile文件中指定它
   
```
target 'Your APP Xcode Project' do
  pod 'TJMobAdSDK', :git => "https://github.com/FMTJYG/TJMobAdSDK.git", :tag => '1.0.0'
end
```

然后执行
```
pod install
```

## 注意事项
### IDFA 适配说明
建议媒体向用户申请IDFA权限授权，在用户授权之前 IDFA 将不可用。如果用户拒绝此请求，应用获取到的 IDFA 将自动清零，可能会导致您的广告收入的降低。

## 初始化SDK
SDK 拉取广告之前，必须要进行初始化操作，传入在平台注册得到的 appId 和 appName

```
#import <TJMobAdSDK/TJMobAdConfig.h>

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {
    [TJMobAdConfig initWithAppId:@"appId" appName:@"appName"];
    return YES;
}
```

## 开屏广告

### 基本信息
开屏广告在 App 启动时展现。用户可以点击广告跳转到广告落地页;或者点击右上角的“跳过”按钮，跳转到 app 内容首页

### 适用场景
开屏广告会在您的应用开启时加载，展示完毕后自动关闭并进入您的应用主界面。展示时间和跳过广告样式，可以通过后台配置并配合前端自定义修改

### 分类
开屏广告分为半屏和全屏，其中半屏开屏广告支持开发者控制广告容器，设置开屏底部的界面，用以展示媒体LOGO

### 主要API
TJMobAdSplashDelegate   

```
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
```   
TJMobAdSplash   
```
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
```

### 接入代码示例
#### 加载并显示开屏广告   
1.在头文件中导入头文件并声明实例
```
#import <TJMobAdSDK/TJMobAdSplash.h>

@interface ViewController () <TJMobAdSplashDelegate>
 
@property (nonatomic, strong) TJMobAdSplash *splash;

@end
```   
2.加载广告数据，开屏广告目前支持全屏开屏和半屏开屏广告两种形式，其中半屏开屏广告支持开发者自定义设置开屏底部的界面，用以展示应用Logo等
```
self.splash = [[TJMobAdSplash alloc] initWithPlacementId:@"PlacementId"];
self.splash.logoImage = [UIImage imageNamed:@"adLogo"];
self.splash.delegate = self;
self.splash.presentAdViewController = self;
[self.splash load];
```
3.将PlacementId替换成你自己的PlacementId   
**说明：logoImage的尺寸高度不能超过屏幕高度的 15%；目前开屏广告只针对iPhone设备在垂直方向上展示**   
4.回调并展示开屏
```
- (void)splashAdDidLoad:(TJMobAdSplash *)splashAd {
    /// 展示
    [self.splash showInContainerView:self.view];
}

- (void)splashAdFailToLoad:(TJMobAdSplash *)splashAd error:(NSError *)error {
    [self.splash destroy];
}

- (void)splashAdExposured:(TJMobAdSplash *)splashAd {
    
}

- (void)splashAdClicked:(TJMobAdSplash *)splashAd {
    
}

- (void)splashAdClosed:(TJMobAdSplash *)splashAd {
    [self.splash destroy];
}
```

## 信息流自渲染广告

### 基本信息
自渲染是对原有类型的优化和升级，使用自渲染的API，您可以为您的应用打造定制式体验

### 适用场景
您可自行定义广告布局样式和展示场景

### 包含内容
使用自渲染 API拉取到的广告数据主要包含如下字段：   
1.广告标题   
2.广告描述   
3.图片媒体信息   
4.视频媒体信息

### 主要API
TJMobAdNativeDelegate

```
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
```
TJMobAdNative
```
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
```
### 接入代码示例
#### 加载并显示信息流广告   
1.在头文件中导入头文件并声明实例
```
#import <TJMobAdSDK/TJMobAdNative.h>

@interface ViewController () <TJMobAdNativeDelegate>
 
@property (nonatomic, strong) TJMobAdNative *nativeAd;

@end
```
2.加载广告数据
```
self.nativeAd = [[TJMobAdNative alloc] initWithPlacementId:@"PlacementId"];
self.nativeAd.delegate = self;
self.nativeAd.presentAdViewController = self;
[self.nativeAd load];
```
3.回调并展示
```
- (void)nativeAdDidLoad:(TJMobAdNative *)nativeAd {
    TJMobAdNativeRenderModel *model = nativeAd.renderModel;
    
    UIView *renderView = [[UIView alloc] initWithFrame:CGRect(....)];
    
    /// add subview
    /// add subview
    /// add subview
    
    /// 如果是视频素材
    UIView *videoView = [model configVideoViewWithFrame:CGRect(....)];
    /// add subview
    
    [nativeAd registerContainer:renderView];
}

- (void)nativeAdFailToLoaded:(TJMobAdNative *)nativeAd error:(NSError *)error {
    
}

- (void)nativeAdExposured:(TJMobAdNative *)nativeAd {
    
}
 
- (void)nativeAdClicked:(TJMobAdNative *)nativeAd {
    
}
```

## 信息流模板广告

### 基本信息
信息流模板是由SDK提供渲染完成的view组件，有多款覆盖主流场景的模板样式，媒体可以通过后台的模板自定义平台，可视化地改变view组件内部元素的大小、位置、字体、颜色等信息

### 适用场景
为您提供了多种的广告模板样式，在新建广告位时支持只出图文广告或只出视频广告，也支持图文和视频广告混出。为保证广告位填充率，建议尽量选择图文和视频广告混出

### 主要API
TJMobAdExpressNativeDelegate
```
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
```
TJMobAdExpressNative
```
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

```
### 接入代码示例
#### 加载并显示模板广告   
1.在头文件中导入头文件并声明实例
```
#import <TJMobAdSDK/TJMobAdExpressNative.h>

@interface ViewController () <TJMobAdExpressNativeDelegate>
 
@property (nonatomic, strong) TJMobAdExpressNative *expressAd;

@end
```
2.加载广告数据
```
self.expressAd = [[TJMobAdExpressNative alloc] initWithPlacementId:@"PlacementId"];
self.expressAd.delegate = self;
self.expressAd.presentAdViewController = self;
[self.expressAd load];
```
3.回调并展示
```
- (void)expressNativeAdDidLoad:(TJMobAdExpressNative *)nativeAd {
    [self.view addSubview:nativeAd.templateView];
}

- (void)expressNativeAdFailToLoaded:(TJMobAdExpressNative *)nativeAd error:(NSError *)error {
    
}

- (void)expressNativeAdExposured:(TJMobAdExpressNative *)nativeAd {
    
}
 
- (void)expressNativeAdClicked:(TJMobAdExpressNative *)nativeAd {
    
}
```

## 插屏广告

### 基本信息
插屏全屏广告是移动广告的一种常见形式，在应用流程中弹出，当应用展示插页式广告时，用户可以选择点按广告，访问其目标网址，也可以将其关闭，返回应用。

### 适用场景
在应用执行流程的自然停顿点，适合投放这类广告   
### 主要API
TJMobAdInterstitialDelegate
```
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
```
TJMobAdInterstitial
```
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
```
### 接入代码示例
#### 加载并显示插屏广告   
1.在头文件中导入头文件并声明实例
```
#import <TJMobAdSDK/TJMobAdInterstitial.h>

@interface ViewController () <TJMobAdInterstitialDelegate>
 
@property (nonatomic, strong) TJMobAdInterstitial *interstitialAd;

@end
```
2.加载广告数据
```
self.interstitialAd = [[TJMobAdInterstitial alloc] initWithPlacementId:@"PlacementId"];
self.interstitialAd.delegate = self;
self.interstitialAd.presentAdViewController = self;
[self.interstitialAd load];
```
3.回调并展示
```
- (void)interstitialAdDidLoad:(TJMobAdInterstitial *)interstitialAd {
    [interstitialAd showInContainerView:self.view];
}

- (void)interstitialAdFailToLoaded:(TJMobAdInterstitial *)interstitialAd error:(NSError *)error {
    
}

- (void)interstitialAdExposured:(TJMobAdInterstitial *)interstitialAd {
    
}
 
- (void)interstitialAdClicked:(TJMobAdInterstitial *)interstitialAd {
    
}

- (void)interstitialAdClosed:(TJMobAdInterstitial *)interstitialAd {
    
}
```
