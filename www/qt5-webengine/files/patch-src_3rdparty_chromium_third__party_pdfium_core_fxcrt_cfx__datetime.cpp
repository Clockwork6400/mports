--- src/3rdparty/chromium/third_party/pdfium/core/fxcrt/cfx_datetime.cpp.orig	2019-11-27 21:12:25 UTC
+++ src/3rdparty/chromium/third_party/pdfium/core/fxcrt/cfx_datetime.cpp
@@ -9,7 +9,7 @@
 #include "build/build_config.h"
 #include "core/fxcrt/fx_system.h"
 
-#if defined(OS_ANDROID) || defined(OS_LINUX) || defined(OS_MACOSX) || \
+#if defined(OS_ANDROID) || defined(OS_LINUX) || defined(OS_MACOSX) || defined(OS_BSD) || \
     defined(OS_ASMJS) || defined(__wasm__)
 #include <sys/time.h>
 #include <time.h>
