--- src/basic/parse-util.c.orig	2021-01-06 13:56:51 UTC
+++ src/basic/parse-util.c
@@ -7,7 +7,7 @@
 #include <stdlib.h>
 #include <string.h>
 
-#ifdef __FreeBSD__
+#ifdef __MidnightBSD__
 #include <xlocale.h>
 #endif
 
