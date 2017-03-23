//
//  SGDownloadImp.h
//  SGDownload
//
//  Created by Single on 2017/3/17.
//  Copyright © 2017年 single. All rights reserved.
//

#import <Foundation/Foundation.h>
@class SGDownload;
@class SGDownloadTask;

NS_ASSUME_NONNULL_BEGIN

@protocol SGDownloadDelegate <NSObject>

@optional;
- (void)download:(SGDownload *)download taskStateDidChange:(SGDownloadTask *)task;
- (void)download:(SGDownload *)download taskProgressDidChange:(SGDownloadTask *)task;

@end

extern NSString * const SGDownloadDefaultIdentifier;

@interface SGDownload : NSObject

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

+ (instancetype)download;    // default download manager.
+ (instancetype)downloadWithIdentifier:(NSString *)identifier;
+ (void)handleEventsForBackgroundURLSession:(NSString *)identifier completionHandler:(void (^)())completionHandler;

@property (nonatomic, copy, readonly) NSString * identifier;
@property (nonatomic, strong, readonly) NSURLSessionConfiguration * sessionConfiguration;

@property (nonatomic, weak) id <SGDownloadDelegate> delegate;
@property (nonatomic, assign) NSUInteger maxConcurrentOperationCount;       // defalut is 1.

@property (nonatomic, strong, readonly) NSArray <SGDownloadTask *> * tasks;

- (nullable SGDownloadTask *)taskWithContentURL:(NSURL *)contentURL;    // if return nil, there is no task of the contentURL;

- (void)downloadTask:(SGDownloadTask *)task;
- (void)downloadTasks:(NSArray <SGDownloadTask *> *)tasks;

- (void)resumeAllTasks;
- (void)resumeTask:(SGDownloadTask *)task;
- (void)resumeTasks:(NSArray <SGDownloadTask *> *)tasks;

- (void)suspendAllTasks;
- (void)suspendTask:(SGDownloadTask *)task;
- (void)suspendTasks:(NSArray <SGDownloadTask *> *)tasks;

- (void)cancelAllTasks;
- (void)cancelTask:(SGDownloadTask *)task;
- (void)cancelTasks:(NSArray <SGDownloadTask *> *)tasks;

- (void)startRunning;
- (void)stopRunning;

@end

NS_ASSUME_NONNULL_END
