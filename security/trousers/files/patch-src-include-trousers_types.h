--- src/include/trousers_types.h.orig	2010-05-20 02:45:55.000000000 +0900
+++ src/include/trousers_types.h	2010-10-24 21:04:04.829561420 +0900
@@ -11,6 +11,14 @@
 #ifndef _TROUSERS_TYPES_H_
 #define _TROUSERS_TYPES_H_
 
+#ifndef STRUCTURE_PACKING_ATTRIBUTE
+#ifdef __GCC
+#define STRUCTURE_PACKING_ATTRIBUTE   __attribute__((packed))
+#else
+#define STRUCTURE_PACKING_ATTRIBUTE   /* */
+#endif
+#endif
+
 #define TCPA_NONCE_SIZE		sizeof(TCPA_NONCE)
 #define TCPA_DIGEST_SIZE	sizeof(TCPA_DIGEST)
 #define TCPA_ENCAUTH_SIZE	sizeof(TCPA_ENCAUTH)
@@ -100,7 +108,7 @@
 typedef struct tdTSS_KEY12_HDR {
 	TPM_STRUCTURE_TAG tag;
 	UINT16 fill;
-} __attribute__((packed)) TSS_KEY12_HDR;
+} STRUCTURE_PACKING_ATTRIBUTE TSS_KEY12_HDR;
 
 typedef struct tdTSS_KEY {
 	union {
@@ -118,11 +126,10 @@
 	BYTE *encData;
 } TSS_KEY;
 
-#if (defined (__linux) || defined (linux) || defined (SOLARIS) || defined (__GLIBC__))
-#define BSD_CONST
-#elif (defined (__OpenBSD__) || defined (__FreeBSD__))
+#if defined (__FreeBSD__)
 #define BSD_CONST const
-#endif
-
+#else
+#define BSD_CONST /* */
+#endif 
 
 #endif
