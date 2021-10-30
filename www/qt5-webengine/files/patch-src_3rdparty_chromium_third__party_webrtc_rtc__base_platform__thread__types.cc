--- src/3rdparty/chromium/third_party/webrtc/rtc_base/platform_thread_types.cc.orig	2019-11-27 21:12:25 UTC
+++ src/3rdparty/chromium/third_party/webrtc/rtc_base/platform_thread_types.cc
@@ -11,7 +11,11 @@
 #include "rtc_base/platform_thread_types.h"
 
 #if defined(WEBRTC_LINUX)
+#if !defined(__FreeBSD__)
 #include <sys/prctl.h>
+#else
+#include <pthread_np.h>
+#endif
 #include <sys/syscall.h>
 #endif
 
@@ -27,6 +31,8 @@ PlatformThreadId CurrentThreadId() {
   return gettid();
 #elif defined(WEBRTC_FUCHSIA)
   return zx_thread_self();
+#elif defined(__FreeBSD__)
+  return pthread_getthreadid_np();
 #elif defined(WEBRTC_LINUX)
   return syscall(__NR_gettid);
 #elif defined(__EMSCRIPTEN__)
@@ -57,6 +63,7 @@ bool IsThreadRefEqual(const PlatformThreadRef& a, cons
 }
 
 void SetCurrentThreadName(const char* name) {
+#if !defined(__FreeBSD__)
 #if defined(WEBRTC_WIN)
   struct {
     DWORD dwType;
@@ -74,6 +81,7 @@ void SetCurrentThreadName(const char* name) {
   prctl(PR_SET_NAME, reinterpret_cast<unsigned long>(name));  // NOLINT
 #elif defined(WEBRTC_MAC) || defined(WEBRTC_IOS)
   pthread_setname_np(name);
+#endif
 #endif
 }
 
