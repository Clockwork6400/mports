--- src/3rdparty/chromium/third_party/blink/renderer/core/inspector/inspector_memory_agent.cc.orig	2019-11-27 21:12:25 UTC
+++ src/3rdparty/chromium/third_party/blink/renderer/core/inspector/inspector_memory_agent.cc
@@ -184,7 +184,7 @@ InspectorMemoryAgent::GetSamplingProfileById(uint32_t 
 
 Vector<String> InspectorMemoryAgent::Symbolize(
     const WebVector<void*>& addresses) {
-#if defined(OS_LINUX)
+#if defined(OS_LINUX) || defined(OS_BSD)
   // TODO(alph): Move symbolization to the client.
   Vector<void*> addresses_to_symbolize;
   for (size_t i = 0; i < addresses.size(); i++) {
