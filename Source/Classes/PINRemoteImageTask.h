//
//  PINRemoteImageTask.h
//  Pods
//
//  Created by Garrett Moon on 3/9/15.
//
//

#import <Foundation/Foundation.h>

#if !__has_include(<PINOperation/PINOperation.h>)
#import "PINOperation.h"
#else
#import <PINOperation/PINOperation.h>
#endif

#import "PINRemoteImageCallbacks.h"
#import <PINRemoteImage/PINRemoteImageManager.h>
#import <PINRemoteImage/PINRemoteImageMacros.h>
#import "PINRemoteLock.h"
#import "PINResume.h"

@interface PINRemoteImageTask : NSObject

@property (nonatomic, strong, readonly, nonnull) PINRemoteLock *lock;

@property (nonatomic, copy, readonly, nonnull) NSDictionary<NSUUID *, PINRemoteImageCallbacks *> *callbackBlocks;

@property (nonatomic, weak, nullable) PINRemoteImageManager *manager;

@property (nonatomic, strong, nullable) id<PINRequestRetryStrategy> retryStrategy;

@property (nonatomic, copy, nullable) NSString *key;

- (_Nonnull instancetype)init NS_UNAVAILABLE;
- (_Nonnull instancetype)initWithManager:(nonnull PINRemoteImageManager *)manager NS_DESIGNATED_INITIALIZER;

- (void)addCallbacksWithCompletionBlock:(nonnull PINRemoteImageManagerImageCompletion)completionBlock
                     progressImageBlock:(nullable PINRemoteImageManagerImageCompletion)progressImageBlock
                  progressDownloadBlock:(nullable PINRemoteImageManagerProgressDownload)progressDownloadBlock
                               withUUID:(nonnull NSUUID *)UUID;

- (void)removeCallbackWithUUID:(nonnull NSUUID *)UUID;

- (void)callCompletionsWithImage:(nullable PINImage *)image
       alternativeRepresentation:(nullable id)alternativeRepresentation
                          cached:(BOOL)cached
                        response:(nullable NSURLResponse *)response
                           error:(nullable NSError *)error
                          remove:(BOOL)remove;

//returns YES if no more attached completionBlocks
- (BOOL)cancelWithUUID:(nonnull NSUUID *)UUID resume:(PINResume * _Nullable * _Nullable)resume;

- (void)setPriority:(PINRemoteImageManagerPriority)priority;

- (nonnull PINRemoteImageManagerResult *)imageResultWithImage:(nullable PINImage *)image
                                    alternativeRepresentation:(nullable id)alternativeRepresentation
                                                requestLength:(NSTimeInterval)requestLength
                                                   resultType:(PINRemoteImageResultType)resultType
                                                         UUID:(nullable NSUUID *)uuid
                                                     response:(nullable NSURLResponse *)response
                                                        error:(nullable NSError *)error;

@end
