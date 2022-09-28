From 2b6bb2c1bed8f7009631e8f8c306fa3160324a49 Mon Sep 17 00:00:00 2001
From: "Sergey G. Brester" <serg.brester@sebres.de>
Date: Mon, 8 Feb 2021 17:19:24 +0100
Subject: [PATCH] follow bpo-37324: :ref:`collections-abstract-base-classes`
 moved to the :mod:`collections.abc` module

(since 3.10-alpha.5 `MutableMapping` is missing in collections module)
---
 fail2ban/server/action.py | 5 ++++-
 1 file changed, 4 insertions(+), 1 deletion(-)

diff --git fail2ban/server/action.py fail2ban/server/action.py
index 3bc48fe0..f0f1e6f5 100644
--- fail2ban/server/action.py
+++ fail2ban/server/action.py
@@ -30,7 +30,10 @@ import tempfile
 import threading
 import time
 from abc import ABCMeta
-from collections import MutableMapping
+try:
+	from collections.abc import MutableMapping
+except ImportError:
+	from collections import MutableMapping
 
 from .failregex import mapTag2Opt
 from .ipdns import DNSUtils
-- 
2.32.0

