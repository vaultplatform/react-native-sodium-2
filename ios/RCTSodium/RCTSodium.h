//
//  RCTSodium.h
//
//  Created by Lyubomir Ivanov on 9/25/16.
//  Copyright © 2016 Lyubomir Ivanov. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface RCTSodium : NSObject <RCTBridgeModule>

- (void) sodium_version_string:(RCTPromiseResolveBlock)resolve reject:(RCTPromiseRejectBlock)reject;

- (void) randombytes_random:(RCTPromiseResolveBlock)resolve reject:(RCTPromiseRejectBlock)reject;
- (void) randombytes_uniform:(NSUInteger)upper_bound resolve:(RCTPromiseResolveBlock)resolve reject:(RCTPromiseRejectBlock)reject;
- (void) randombytes_buf:(NSUInteger)size resolve:(RCTPromiseResolveBlock)resolve reject:(RCTPromiseRejectBlock)reject;
- (void) randombytes_close:(RCTPromiseResolveBlock)resolve reject:(RCTPromiseRejectBlock)reject;
- (void) randombytes_stir:(RCTPromiseResolveBlock)resolve reject:(RCTPromiseRejectBlock)reject;

- (void) crypto_secretbox_easy:(NSString*)m n:(NSString*)n k:(NSString*)k resolve:(RCTPromiseResolveBlock)resolve reject:(RCTPromiseRejectBlock)reject;
- (void) crypto_secretbox_open_easy:(NSString*)c n:(NSString*)n k:(NSString*)k resolve:(RCTPromiseResolveBlock)resolve reject:(RCTPromiseRejectBlock)reject;
- (void) crypto_auth:(NSString*)in k:(NSString*)k resolve:(RCTPromiseResolveBlock)resolve reject:(RCTPromiseRejectBlock)reject;
- (void) crypto_auth_verify:(NSString*)h in:(NSString*)in k:(NSString*)k resolve:(RCTPromiseResolveBlock)resolve reject:(RCTPromiseRejectBlock)reject;

- (void) crypto_box_keypair:(RCTPromiseResolveBlock)resolve reject:(RCTPromiseRejectBlock)reject;
- (void) crypto_box_beforenm:(NSString*)pk sk:(NSString*)sk resolve:(RCTPromiseResolveBlock)resolve reject:(RCTPromiseRejectBlock)reject;

- (void) crypto_box_easy:(NSString*)m n:(NSString*)n pk:(NSString*)pk sk:(NSString*)sk resolve:(RCTPromiseResolveBlock)resolve reject:(RCTPromiseRejectBlock)reject;
- (void) crypto_box_easy_afternm:(NSString*)m n:(NSString*)n k:(NSString*)k resolve:(RCTPromiseResolveBlock)resolve reject:(RCTPromiseRejectBlock)reject;

- (void) crypto_box_open_easy:(NSString*)c n:(NSString*)n pk:(NSString*)pk sk:(NSString*)sk resolve:(RCTPromiseResolveBlock)resolve reject:(RCTPromiseRejectBlock)reject;
- (void) crypto_box_open_easy_afternm:(NSString*)c n:(NSString*)n k:(NSString*)k resolve:(RCTPromiseResolveBlock)resolve reject:(RCTPromiseRejectBlock)reject;

- (void) crypto_generichash:(NSNumber*)outlen data:(NSString*)data key:(NSString*)key resolve:(RCTPromiseResolveBlock)resolve reject:(RCTPromiseRejectBlock)reject;
- (void) crypto_pwhash:(NSNumber*)keylen password:(NSString*)password salt:(NSString*)salt opslimit:(NSNumber*)opslimit memlimit:(NSNumber*)memlimit algo:(NSNumber*)algo resolve:(RCTPromiseResolveBlock)resolve reject:(RCTPromiseRejectBlock)reject;

- (void) crypto_scalarmult_base:(NSString*)n resolve:(RCTPromiseResolveBlock)resolve reject:(RCTPromiseRejectBlock)reject;

- (void) crypto_sign:(NSString*)m pk:(NSString*)pk resolve:(RCTPromiseResolveBlock)resolve reject:(RCTPromiseRejectBlock)reject;
- (void) crypto_sign_detached:(NSString*)m pk:(NSString*)pk resolve:(RCTPromiseResolveBlock)resolve reject:(RCTPromiseRejectBlock)reject;
- (void) crypto_sign_keypair: resolve: (RCTPromiseResolveBlock)resolve reject:(RCTPromiseRejectBlock)reject;
- (void) crypto_sign_ed25519_sk_to_pk:(NSString*)sk resolve: (RCTPromiseResolveBlock)resolve reject:(RCTPromiseRejectBlock)reject;

- (void) crypto_box_seal:(NSString*)m pk:(NSString*)pk resolve:(RCTPromiseResolveBlock)resolve reject:(RCTPromiseRejectBlock)reject;
- (void) crypto_box_seal_open:(NSString*)c pk:(NSString*)pk sk:(NSString*)sk resolve: (RCTPromiseResolveBlock)resolve reject:(RCTPromiseRejectBlock)reject;

- (void) crypto_aead_xchacha20poly1305_ietf_encrypt:(NSString*)message public_nonce:(NSString*)public_nonce key:(NSString*)key additionalData:(NSString*)additionalData resolve:(RCTPromiseResolveBlock)resolve reject:(RCTPromiseRejectBlock)reject;
- (void) crypto_aead_xchacha20poly1305_ietf_decrypt:(NSString*)cipherText public_nonce:(NSString*)public_nonce key:(NSString*)key additionalData:(NSString*)additionalData resolve:(RCTPromiseResolveBlock)resolve reject:(RCTPromiseRejectBlock)reject;
- (void) crypto_aead_xchacha20poly1305_ietf_keygen:(RCTPromiseResolveBlock)resolve reject:(RCTPromiseRejectBlock)reject;

- (void) to_base64:(NSString*)message variant:(NSNumber*)variant resolve:(RCTPromiseResolveBlock)resolve reject:(RCTPromiseRejectBlock)reject;
- (void) from_base64:(NSString*)cipher variant:(NSNumber*)variant resolve: (RCTPromiseResolveBlock)resolve reject:(RCTPromiseRejectBlock)reject;

- (void) to_hex:(NSString*)message resolve:(RCTPromiseResolveBlock)resolve reject:(RCTPromiseRejectBlock)reject;
- (void) from_hex:(NSString*)cipher resolve: (RCTPromiseResolveBlock)resolve reject:(RCTPromiseRejectBlock)reject;

@end
