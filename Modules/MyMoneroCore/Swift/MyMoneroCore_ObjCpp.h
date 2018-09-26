//
//  MyMoneroCore_ObjCpp.h
//  MyMonero
//
//  Created by Paul Shapiro on 11/22/17.
//  Copyright (c) 2014-2018, MyMonero.com
//
//  All rights reserved.
//
//  Redistribution and use in source and binary forms, with or without modification, are
//  permitted provided that the following conditions are met:
//
//  1. Redistributions of source code must retain the above copyright notice, this list of
//	conditions and the following disclaimer.
//
//  2. Redistributions in binary form must reproduce the above copyright notice, this list
//	of conditions and the following disclaimer in the documentation and/or other
//	materials provided with the distribution.
//
//  3. Neither the name of the copyright holder nor the names of its contributors may be
//	used to endorse or promote products derived from this software without specific
//	prior written permission.
//
//  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY
//  EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
//  MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL
//  THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
//  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
//  PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
//  INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
//  STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF
//  THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
//
#import <Foundation/Foundation.h>
//
// Types - Arguments - Create Transactions - Accessible from Swift
@interface Monero_Arg_SpendableOutput: NSObject
@property (nonatomic) uint64_t amount;
@property (nonatomic, copy, nonnull) NSString *public_key;
@property (nonatomic, copy, nonnull) NSString *tx_pub_key;
@property (nonatomic, copy, nullable) NSString *rct;
@property (nonatomic) uint64_t global_index;
@property (nonatomic) uint64_t index;
@end
//
@interface Monero_Arg_RandomAmountOut: NSObject
@property (nonatomic, copy, nonnull) NSString *public_key;
@property (nonatomic, copy, nullable) NSString *rct;
@property (nonatomic) uint64_t global_index;
@end
//
@interface Monero_Arg_RandomAmountAndOuts: NSObject
@property (nonatomic) uint64_t amount;
@property (nonatomic, strong, nonnull) NSArray<Monero_Arg_RandomAmountOut *> *outputs;
@end
//
// Types - Return values
@interface Monero_DecodedAddress_RetVals: NSObject
@property (nonatomic, copy, nullable) NSString *errStr_orNil;
// or
@property (nonatomic, copy, nullable) NSString *pub_viewKey_NSString;
@property (nonatomic, copy, nullable) NSString *pub_spendKey_NSString;
@property (nonatomic) BOOL isSubaddress;
@property (nonatomic, copy, nullable) NSString *paymentID_NSString_orNil;
@end
//
@interface Monero_CreatedTransaction: NSObject
@property (nonatomic, copy, nullable) NSString *errStr_orNil;
// or
@property (nonatomic, copy, nullable) NSString *serialized_signed_tx;
@property (nonatomic, copy, nullable) NSString *tx_hash;
@property (nonatomic, copy, nullable) NSString *tx_key;
@end
//
// Constants
extern uint32_t const MyMoneroCore_ObjCpp_SimplePriority_Low;
extern uint32_t const MyMoneroCore_ObjCpp_SimplePriority_MedLow;
extern uint32_t const MyMoneroCore_ObjCpp_SimplePriority_MedHigh;
extern uint32_t const MyMoneroCore_ObjCpp_SimplePriority_High;
//
typedef enum {
	MM_MAINNET,
	MM_TESTNET,
	MM_STAGENET
} NetType;
//
@interface MyMoneroCore_ObjCpp : NSObject
//
// Return value dictionary keys
+ (nonnull NSString *)retValDictKey__ErrStr;
+ (nonnull NSString *)retValDictKey__Value; // used for single value returns… you should force-cast the type… e.g. "as! String" for -mnemonicStringFromSeedHex:…
//
+ (BOOL)areEqualMnemonics:(nonnull NSString *)a b:(nonnull NSString *)b;

+ (BOOL)newlyCreatedWallet:(nonnull NSString *)languageCode
				   nettype:(NetType)nettype
						fn:(void (^_Nonnull)
							(
							 NSString * _Nullable errStr_orNil,
							 // OR
							 NSString * _Nullable seed_NSString,
							 NSString * _Nullable mnemonic_NSString,
							 NSString * _Nullable mnemonicLanguage_NSString,
							 NSString * _Nullable address_NSString,
							 NSString * _Nullable sec_viewKey_NSString,
							 NSString * _Nullable sec_spendKey_NSString,
							 NSString * _Nullable pub_viewKey_NSString,
							 NSString * _Nullable pub_spendKey_NSString
							 )
							)fn;

+ (nonnull NSDictionary *)mnemonicStringFromSeedHex:(nonnull NSString *)seed_NSString
						mnemonicWordsetName:(nonnull NSString *)wordsetName;

+ (BOOL)seedAndKeysFromMnemonic:(nonnull NSString *)mnemonic_NSString
						nettype:(NetType)nettype
							 fn:(void (^_Nonnull)
								 (
								  NSString * _Nullable errStr_orNil,
								  // OR
								  NSString * _Nullable seed_NSString,
								  NSString * _Nullable mnemonic_language_NSString,
								  NSString * _Nullable address_NSString,
								  NSString * _Nullable sec_viewKey_NSString,
								  NSString * _Nullable sec_spendKey_NSString,
								  NSString * _Nullable pub_viewKey_NSString,
								  NSString * _Nullable pub_spendKey_NSString
								  )
								 )fn;

+ (void)verifiedComponentsForOpeningExistingWalletWithAddress:(nonnull NSString *)address_NSString
												  sec_viewKey:(nonnull NSString *)sec_viewKey_NSString
								sec_spendKey_orNilForViewOnly:(nullable NSString *)sec_spendKey_NSString_orNil
											   sec_seed_orNil:(nullable NSString *)sec_seed_NSString_orNil
									 wasANewlyGeneratedWallet:(BOOL)wasANewlyGeneratedWallet
													  nettype:(NetType)nettype
														   fn:(void (^ _Nonnull)
															   (
																NSString * _Nullable errStr_orNil,
																// OR
																NSString * _Nullable seed_NSString_orNil,
																//
																NSString * _Nullable address_NSString,
																NSString * _Nullable sec_viewKey_NSString_orNil,
																NSString * _Nullable sec_spendKey_NSString,
																NSString * _Nullable pub_viewKey_NSString,
																NSString * _Nullable pub_spendKey_NSString,
																BOOL isInViewOnlyMode,
																BOOL isValid
																)
															   )fn;
//
+ (nonnull Monero_DecodedAddress_RetVals *)decodedAddress:(nonnull NSString *)addressString isTestnet:(BOOL)isTestnet;
+ (BOOL)isSubAddress:(nonnull NSString *)addressString isTestnet:(BOOL)isTestnet;
+ (BOOL)isIntegratedAddress:(nonnull NSString *)addressString isTestnet:(BOOL)isTestnet;
//
+ (nullable NSString *)new_integratedAddrFromStdAddr:(nonnull NSString *)std_address_NSString andShortPID:(nonnull NSString *)short_paymentID isTestnet:(BOOL)isTestnet;
+ (nullable NSString *)new_integratedAddrFromStdAddr:(nonnull NSString *)std_address_NSString andShortPID:(nonnull NSString *)short_paymentID; // mainnet
//
+ (nonnull NSString *)new_short_plain_paymentID;
//
+ (nonnull NSString *)new_fakeAddressForRCTTxWithNetType:(NetType)nettype;
//
+ (uint32_t)fixedRingsize; // NOTE: This is not the mixin, which would be fixedRingsize-1
+ (uint32_t)fixedMixinsize; // NOTE: This is not the ringsize, which would be fixedMixin+1
//
+ (uint32_t)default_priority;
+ (uint64_t)estimatedTxNetworkFeeWithFeePerKB:(uint64_t)fee_per_kb
									 priority:(uint32_t)priority;
//
+ (nullable NSString *)new_keyImageFrom_tx_pub_key:(nonnull NSString *)tx_pub_key_NSString
							 sec_spendKey:(nonnull NSString *)sec_spendKey_NSString
							  sec_viewKey:(nonnull NSString *)sec_viewKey_NSString
							 pub_spendKey:(nonnull NSString *)pub_spendKey_NSString
								out_index:(uint64_t)out_index;
//
+ (nonnull Monero_CreatedTransaction *)createTransactionWithNetType:(NetType)objcNetType
										from_address_string:(nonnull NSString *)from_address_string
										 sec_viewKey_string:(nonnull NSString *)sec_viewKey_string
										sec_spendKey_string:(nonnull NSString *)sec_spendKey_string
										  to_address_string:(nonnull NSString *)to_address_string
										  payment_id_string:(nullable NSString *)payment_id_string
											 sending_amount:(uint64_t)sending_amount
												 fee_amount:(uint64_t)fee_amount
											  change_amount:(uint64_t)change_amount
												unlock_time:(uint64_t)unlock_time
															outputs:(NSArray<Monero_Arg_SpendableOutput *> *_Nonnull)args_outputs
														   mix_outs:(NSArray<Monero_Arg_RandomAmountAndOuts *> *_Nonnull)args_mix_outs;
//
@end
