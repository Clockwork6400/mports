From 42dee38ad2ac5c3f23bdf297d824022923270dd9 Mon Sep 17 00:00:00 2001
From: "Sergey G. Brester" <serg.brester@sebres.de>
Date: Mon, 8 Feb 2021 17:25:45 +0100
Subject: [PATCH] amend for `Mapping`

---
 fail2ban/server/actions.py | 5 ++++-
 1 file changed, 4 insertions(+), 1 deletion(-)

diff --git fail2ban/server/actions.py fail2ban/server/actions.py
index b7b95b44..897d907c 100644
--- fail2ban/server/actions.py
+++ fail2ban/server/actions.py
@@ -28,7 +28,10 @@ import logging
 import os
 import sys
 import time
-from collections import Mapping
+try:
+	from collections.abc import Mapping
+except ImportError:
+	from collections import Mapping
 try:
 	from collections import OrderedDict
 except ImportError:
-- 
2.32.0

