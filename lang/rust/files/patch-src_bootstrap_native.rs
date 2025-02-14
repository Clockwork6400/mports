--- src/bootstrap/native.rs.orig	2021-09-06 14:42:35.000000000 -0400
+++ src/bootstrap/native.rs	2021-12-31 03:24:28.230834000 -0500
@@ -380,6 +380,8 @@
             cfg.define("CMAKE_SYSTEM_NAME", "NetBSD");
         } else if target.contains("freebsd") {
             cfg.define("CMAKE_SYSTEM_NAME", "FreeBSD");
+        } else if target.contains("midnightbsd") {
+            cfg.define("CMAKE_SYSTEM_NAME", "FreeBSD");
         } else if target.contains("windows") {
             cfg.define("CMAKE_SYSTEM_NAME", "Windows");
         } else if target.contains("haiku") {
@@ -561,26 +563,9 @@
         let mut cfg = cmake::Config::new(builder.src.join("src/llvm-project/lld"));
         configure_cmake(builder, target, &mut cfg, true);
 
-        // This is an awful, awful hack. Discovered when we migrated to using
-        // clang-cl to compile LLVM/LLD it turns out that LLD, when built out of
-        // tree, will execute `llvm-config --cmakedir` and then tell CMake about
-        // that directory for later processing. Unfortunately if this path has
-        // forward slashes in it (which it basically always does on Windows)
-        // then CMake will hit a syntax error later on as... something isn't
-        // escaped it seems?
-        //
-        // Instead of attempting to fix this problem in upstream CMake and/or
-        // LLVM/LLD we just hack around it here. This thin wrapper will take the
-        // output from llvm-config and replace all instances of `\` with `/` to
-        // ensure we don't hit the same bugs with escaping. It means that you
-        // can't build on a system where your paths require `\` on Windows, but
-        // there's probably a lot of reasons you can't do that other than this.
-        let llvm_config_shim = env::current_exe().unwrap().with_file_name("llvm-config-wrapper");
-
         cfg.out_dir(&out_dir)
             .profile("Release")
-            .env("LLVM_CONFIG_REAL", &llvm_config)
-            .define("LLVM_CONFIG_PATH", llvm_config_shim)
+            .define("LLVM_CONFIG_PATH", &llvm_config)
             .define("LLVM_INCLUDE_TESTS", "OFF");
 
         // While we're using this horrible workaround to shim the execution of
@@ -812,6 +797,7 @@
         "x86_64-apple-darwin" => darwin_libs("osx", &["asan", "lsan", "tsan"]),
         "x86_64-fuchsia" => common_libs("fuchsia", "x86_64", &["asan"]),
         "x86_64-unknown-freebsd" => common_libs("freebsd", "x86_64", &["asan", "msan", "tsan"]),
+        "x86_64-unknown-midnightbsd" => common_libs("freebsd", "x86_64", &["asan", "msan", "tsan"]),
         "x86_64-unknown-linux-gnu" => {
             common_libs("linux", "x86_64", &["asan", "lsan", "msan", "tsan"])
         }
