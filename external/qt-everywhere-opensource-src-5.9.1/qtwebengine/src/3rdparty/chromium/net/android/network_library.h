// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef NET_ANDROID_NETWORK_LIBRARY_H_
#define NET_ANDROID_NETWORK_LIBRARY_H_

#include <jni.h>
#include <stddef.h>
#include <stdint.h>

#include <string>
#include <vector>

#include "net/android/cert_verify_result_android.h"
#include "net/base/mime_util.h"
#include "net/base/net_export.h"

namespace net {
namespace android {

// |cert_chain| is DER encoded chain of certificates, with the server's own
// certificate listed first.
// |auth_type| is as per the Java X509Certificate.checkServerTrusted method.
void VerifyX509CertChain(const std::vector<std::string>& cert_chain,
                         const std::string& auth_type,
                         const std::string& host,
                         CertVerifyStatusAndroid* status,
                         bool* is_issued_by_known_root,
                         std::vector<std::string>* verified_chain);

// Adds a certificate as a root trust certificate to the trust manager.
// |cert| is DER encoded certificate, |len| is its length in bytes.
void AddTestRootCertificate(const uint8_t* cert, size_t len);

// Removes all root certificates added by |AddTestRootCertificate| calls.
void ClearTestRootCertificates();

// Helper for the <keygen> handler. Passes the DER-encoded key pair via JNI to
// the Credentials store. The public key should be a DER-encoded
// SubjectPublicKeyInfo (X.509) and the private key a DER-encode PrivateKeyInfo
// (PKCS#8).
bool StoreKeyPair(const uint8_t* public_key,
                  size_t public_len,
                  const uint8_t* private_key,
                  size_t private_len);

// Returns true if it can determine that only loopback addresses are configured.
// i.e. if only 127.0.0.1 and ::1 are routable.
// Also returns false if it cannot determine this.
bool HaveOnlyLoopbackAddresses();

// Get the mime type (if any) that is associated with the file extension.
// Returns true if a corresponding mime type exists.
bool GetMimeTypeFromExtension(const std::string& extension,
                              std::string* result);

// Returns the ISO country code equivalent of the current MCC (mobile country
// code).
NET_EXPORT std::string GetTelephonyNetworkCountryIso();

// Returns MCC+MNC (mobile country code + mobile network code) as
// the numeric name of the current registered operator.
NET_EXPORT std::string GetTelephonyNetworkOperator();

// Returns MCC+MNC (mobile country code + mobile network code) as
// the numeric name of the current SIM operator.
NET_EXPORT std::string GetTelephonySimOperator();

// Returns true if the device is roaming on the currently active network. When
// true, it suggests that use of data may incur extra costs.
NET_EXPORT bool GetIsRoaming();

// Gets the SSID of the currently associated WiFi access point if there is one.
// Otherwise, returns empty string.
NET_EXPORT_PRIVATE std::string GetWifiSSID();

}  // namespace android
}  // namespace net

#endif  // NET_ANDROID_NETWORK_LIBRARY_H_
