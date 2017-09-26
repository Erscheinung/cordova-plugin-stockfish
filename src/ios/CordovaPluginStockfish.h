#import <Cordova/CDVPlugin.h>
#import "CordovaPluginStockfishc.h"

@interface CordovaPluginStockfish : CDVPlugin

- (void)pluginInitialize;

- (void)init:(CDVInvokedUrlCommand*)command;

- (void)cmd:(CDVInvokedUrlCommand*)command;

- (void)output:(CDVInvokedUrlCommand*)command;

- (void)exit:(CDVInvokedUrlCommand*)command;

- (void)sendOutput:(NSString *)output;

- (void)onAppTerminate;

@end
