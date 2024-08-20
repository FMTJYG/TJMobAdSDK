//
//  TJMobAdNativeRenderModel.h
//  TJMobADSDKLib
//
//  
//

#import <UIKit/UIKit.h>
#import <Foundation/Foundation.h>

typedef NS_ENUM(NSUInteger, TJMobAdNativeRenderType) {
    TJMobAdNativeRenderTypeImage = 1,
    TJMobAdNativeRenderTypeVideo
};

@interface TJMobAdNativeRenderModel : NSObject

/// 广告标题
@property(nonatomic, copy) NSString *title;

/// 广告描述
@property(nonatomic, copy) NSString *text;

/// 图片链接
@property(nonatomic, copy) NSString *imageUrl;

/// 图片高度
@property(nonatomic, assign) double height;

/// 图片宽度
@property(nonatomic, assign) double width;

/// 视频地址
@property(nonatomic, copy) NSString *videoUrl;

/// 视频封面地址
@property(nonatomic, copy) NSString *coverSrc;

/// 视频封面高度
@property(nonatomic, assign) double coverHeight;

/// 视频封面宽度
@property(nonatomic, assign) double coverWidth;

/// 视频播放时长
@property(nonatomic, assign) int playTime;

/// 视频大小
@property(nonatomic, assign) int size;

/// 素材类型
@property(nonatomic, assign) TJMobAdNativeRenderType type;

/// 视频广告view
- (UIView *)configVideoViewWithFrame:(CGRect)frame;

@end
