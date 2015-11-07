--- pylib/gyp/generator/make.py.orig	2015-04-16 13:28:24.117918307 +0900
+++ pylib/gyp/generator/make.py	2015-04-16 13:28:50.421923951 +0900
@@ -342,7 +342,7 @@
 # We remove slashes and replace spaces with new lines;
 # remove blank lines;
 # delete the first line and append a colon to the remaining lines.
-sed -e 's|\\||' -e 'y| |\n|' $(depfile).raw |\
+env NL=`printf "\n"` sed -e 's|\\||' -e 'y| |\n|' $(depfile).raw |\
   grep -v '^$$'                             |\
   sed -e 1d -e 's|$$|:|'                     \
     >> $(depfile)
