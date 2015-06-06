--- xvpng.c.orig	2007-05-14 00:53:28 UTC
+++ xvpng.c
@@ -31,6 +31,7 @@
 
 #ifdef HAVE_PNG
 
+#include "zlib.h"
 #include "png.h"
 
 /*** Stuff for PNG Dialog box ***/
@@ -41,7 +42,9 @@
 #define COMPRESSION   6     /* default zlib compression level, not max
                                (Z_BEST_COMPRESSION) */
 
-#define HAVE_tRNS  (info_ptr->valid & PNG_INFO_tRNS)
+/* old
+#define HAVE_tRNS  (info_ptr->valid & PNG_INFO_tRNS) */
+#define HAVE_tRNS  png_get_valid(png_ptr,info_ptr,PNG_INFO_tRNS)
 
 #define DWIDE    86
 #define DHIGH    104
@@ -444,6 +447,10 @@ int WritePNG(fp, pic, ptype, w, h, rmap,
   byte       *p, *png_line;
   char        software[256];
   char       *savecmnt;
+  /* for storing values until all are accumulated, so that the image header can be set in full */
+  int         _bit_depth,_color_type,_interlace_type,_compression_type,_filter_type;
+  png_uint_32 _width,_height;
+  png_time    _mod_time;
 
   if ((png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL,
        png_xv_error, png_xv_warning)) == NULL) {
@@ -458,7 +465,7 @@ int WritePNG(fp, pic, ptype, w, h, rmap,
     FatalError(software);
   }
 
-  if (setjmp(png_ptr->jmpbuf)) {
+  if (setjmp(png_jmpbuf(png_ptr))) {
     png_destroy_write_struct(&png_ptr, &info_ptr);
     return -1;
   }
@@ -489,8 +496,8 @@ int WritePNG(fp, pic, ptype, w, h, rmap,
     png_set_filter(png_ptr, 0, filter);
   }
 
-  info_ptr->width = w;
-  info_ptr->height = h;
+  _width = w;
+  _height = h;
   if (w <= 0 || h <= 0) {
     SetISTR(ISTR_WARNING, "%s:  image dimensions out of range (%dx%d)",
       fbasename, w, h);
@@ -498,7 +505,7 @@ int WritePNG(fp, pic, ptype, w, h, rmap,
     return -1;
   }
 
-  info_ptr->interlace_type = interCB.val ? 1 : 0;
+  _interlace_type = interCB.val ? PNG_INTERLACE_ADAM7 : PNG_INTERLACE_NONE;
 
   linesize = 0;   /* quiet a compiler warning */
 
@@ -542,40 +549,44 @@ int WritePNG(fp, pic, ptype, w, h, rmap,
         png_destroy_write_struct(&png_ptr, &info_ptr);
         return -1;
       }
-      info_ptr->color_type = PNG_COLOR_TYPE_RGB;
-      info_ptr->bit_depth = 8;
+      _color_type = PNG_COLOR_TYPE_RGB;
+      _bit_depth = 8;
     } else /* ptype == PIC8 */ {
       linesize = w;
-      info_ptr->color_type = PNG_COLOR_TYPE_PALETTE;
+      _color_type = PNG_COLOR_TYPE_PALETTE;
       if (numuniqcols <= 2)
-        info_ptr->bit_depth = 1;
+        _bit_depth = 1;
       else
       if (numuniqcols <= 4)
-        info_ptr->bit_depth = 2;
+        _bit_depth = 2;
       else
       if (numuniqcols <= 16)
-        info_ptr->bit_depth = 4;
+        _bit_depth = 4;
       else
-        info_ptr->bit_depth = 8;
+        _bit_depth = 8;
 
       for (i = 0; i < numuniqcols; i++) {
         palette[i].red   = r1[i];
         palette[i].green = g1[i];
         palette[i].blue  = b1[i];
       }
-      info_ptr->num_palette = numuniqcols;
-      info_ptr->palette = palette;
+/* cannot find a setter for this, unsure if it is necessary anymore...
       info_ptr->valid |= PNG_INFO_PLTE;
+*/
+      /* set the header just in case it's needed */
+      png_set_IHDR(png_ptr,info_ptr,_width,_height,_bit_depth,_color_type,
+        _interlace_type,PNG_COMPRESSION_TYPE_DEFAULT,PNG_FILTER_TYPE_DEFAULT);
+      png_set_PLTE(png_ptr,info_ptr,palette,numuniqcols);
     }
   }
 
   else if (colorType == F_GREYSCALE || colorType == F_BWDITHER) {
-    info_ptr->color_type = PNG_COLOR_TYPE_GRAY;
+    _color_type = PNG_COLOR_TYPE_GRAY;
     if (colorType == F_BWDITHER) {
       /* shouldn't happen */
       if (ptype == PIC24) FatalError("PIC24 and B/W Stipple in WritePNG()");
 
-      info_ptr->bit_depth = 1;
+      _bit_depth = 1;
       if (MONO(r1[0], g1[0], b1[0]) > MONO(r1[1], g1[1], b1[1])) {
         remap[0] = 1;
         remap[1] = 0;
@@ -595,7 +606,7 @@ int WritePNG(fp, pic, ptype, w, h, rmap,
           png_destroy_write_struct(&png_ptr, &info_ptr);
           return -1;
         }
-        info_ptr->bit_depth = 8;
+        _bit_depth = 8;
       }
       else /* ptype == PIC8 */ {
         int low_precision;
@@ -617,7 +628,7 @@ int WritePNG(fp, pic, ptype, w, h, rmap,
         for (; i < 256; i++)
           remap[i]=0;  /* shouldn't be necessary, but... */
 
-        info_ptr->bit_depth = 8;
+        _bit_depth = 8;
 
         /* Note that this fails most of the time because of gamma */
            /* (and that would be a bug:  GRR FIXME) */
@@ -636,7 +647,7 @@ int WritePNG(fp, pic, ptype, w, h, rmap,
           for (i = 0; i < numuniqcols; i++) {
             remap[i] &= 0xf;
           }
-          info_ptr->bit_depth = 4;
+          _bit_depth = 4;
 
           /* try to adjust to 2-bit precision grayscale */
 
@@ -652,7 +663,7 @@ int WritePNG(fp, pic, ptype, w, h, rmap,
           for (i = 0; i < numuniqcols; i++) {
             remap[i] &= 3;
           }
-          info_ptr->bit_depth = 2;
+          _bit_depth = 2;
 
           /* try to adjust to 1-bit precision grayscale */
 
@@ -668,7 +679,7 @@ int WritePNG(fp, pic, ptype, w, h, rmap,
           for (i = 0; i < numuniqcols; i++) {
             remap[i] &= 1;
           }
-          info_ptr->bit_depth = 1;
+          _bit_depth = 1;
         }
       }
     }
@@ -677,6 +688,9 @@ int WritePNG(fp, pic, ptype, w, h, rmap,
   else
     png_error(png_ptr, "Unknown colorstyle in WritePNG");
 
+  png_set_IHDR(png_ptr,info_ptr,_width,_height,_bit_depth,_color_type,
+    _interlace_type,PNG_COMPRESSION_TYPE_DEFAULT,PNG_FILTER_TYPE_DEFAULT);
+
   if ((text = (png_textp)malloc(sizeof(png_text)))) {
     sprintf(software, "XV %s", REVDATE);
 
@@ -685,20 +699,22 @@ int WritePNG(fp, pic, ptype, w, h, rmap,
     text->text = software;
     text->text_length = strlen(text->text);
 
-    info_ptr->max_text = 1;
-    info_ptr->num_text = 1;
-    info_ptr->text = text;
+/* max_text seems to be internal only now, do not set
+    info_ptr->max_text = 1; */
+    png_set_text(png_ptr,info_ptr,text,1);
   }
 
   Display_Gamma = gDial.val;  /* Save the current gamma for loading */
 
 // GRR FIXME:  add .Xdefaults option to omit writing gamma (size, cumulative errors when editing)--alternatively, modify save box to include "omit" checkbox
-  info_ptr->gamma = 1.0/gDial.val;
-  info_ptr->valid |= PNG_INFO_gAMA;
+  png_set_gAMA(png_ptr,info_ptr,1.0/gDial.val);
+/* doesn't seem to be a way to set valid directly anymore, unnecessary maybe.. 
+  info_ptr->valid |= PNG_INFO_gAMA; */
 
+/* might need to be png_write_info_before_PLTE() ... */
   png_write_info(png_ptr, info_ptr);
 
-  if (info_ptr->bit_depth < 8)
+  if (_bit_depth < 8)
     png_set_packing(png_ptr);
 
   pass=png_set_interlace_handling(png_ptr);
@@ -711,13 +727,13 @@ int WritePNG(fp, pic, ptype, w, h, rmap,
     int j;
     p = pic;
     for (j = 0; j < h; ++j) {
-      if (info_ptr->color_type == PNG_COLOR_TYPE_GRAY) {
+      if (_color_type == PNG_COLOR_TYPE_GRAY) {
         int k;
         for (k = 0; k < w; ++k)
           png_line[k] = ptype==PIC24 ? MONO(p[k*3], p[k*3+1], p[k*3+2]) :
                                        remap[pc2nc[p[k]]];
         png_write_row(png_ptr, png_line);
-      } else if (info_ptr->color_type == PNG_COLOR_TYPE_PALETTE) {
+      } else if (_color_type == PNG_COLOR_TYPE_PALETTE) {
         int k;
         for (k = 0; k < w; ++k)
           png_line[k] = pc2nc[p[k]];
@@ -739,28 +755,31 @@ int WritePNG(fp, pic, ptype, w, h, rmap,
         (savecmnt = (char *)malloc((strlen(picComments) + 1)*sizeof(char)))) {
       png_textp tp;
       char *comment, *key;
+      int nt;
+      int mt;
 
       strcpy(savecmnt, picComments);
       key = savecmnt;
+      png_get_text(png_ptr,info_ptr,&tp,&mt); /* to get 'max_text' */
       tp = text;
-      info_ptr->num_text = 0;
+      nt = 0;      
 
       comment = strchr(key, ':');
 
       do  {
         /* Allocate a larger structure for comments if necessary */
-        if (info_ptr->num_text >= info_ptr->max_text)
+        if (nt >= mt)
         {
           if ((tp =
-              realloc(text, (info_ptr->num_text + 2)*sizeof(png_text))) == NULL)
+              realloc(text, (nt + 2)*sizeof(png_text))) == NULL)
           {
             break;
           }
           else
           {
             text = tp;
-            tp = &text[info_ptr->num_text];
-            info_ptr->max_text += 2;
+            tp = &text[nt];
+            mt += 2;
           }
         }
 
@@ -810,7 +829,7 @@ int WritePNG(fp, pic, ptype, w, h, rmap,
             }
 
             tp->compression = tp->text_length > 640 ? 0 : -1;
-            info_ptr->num_text++;
+            nt++;
             tp++;
           }
         }
@@ -834,27 +853,29 @@ int WritePNG(fp, pic, ptype, w, h, rmap,
           tp->text = key;
           tp->text_length = q - key;
           tp->compression = tp->text_length > 750 ? 0 : -1;
-          info_ptr->num_text++;
+          nt++;
           key = NULL;
         }
       } while (key && *key);
+      png_set_text(png_ptr,info_ptr,text,nt);
     }
     else {
-      info_ptr->num_text = 0;
+      png_set_text(png_ptr,info_ptr,text,0);
     }
   }
-  info_ptr->text = text;
 
-  png_convert_from_time_t(&(info_ptr->mod_time), time(NULL));
-  info_ptr->valid |= PNG_INFO_tIME;
+  png_convert_from_time_t(&_mod_time, time(NULL));
+  png_set_tIME(png_ptr,info_ptr,&_mod_time);
+/* dunno how to set validity
+  info_ptr->valid |= PNG_INFO_tIME; */
 
   png_write_end(png_ptr, info_ptr);
   fflush(fp);   /* just in case we core-dump before finishing... */
 
   if (text) {
     free(text);
-    /* must do this or png_destroy_write_struct() 0.97+ will free text again: */
-    info_ptr->text = (png_textp)NULL;
+    /* must do this or png_destroy_write_struct() 0.97+ will free text again: 
+    info_ptr->text = (png_textp)NULL; */
     if (savecmnt)
     {
       free(savecmnt);
@@ -886,6 +907,14 @@ int LoadPNG(fname, pinfo)
   int pass;
   int gray_to_rgb;
   size_t commentsize;
+  /* temp storage vars for libpng15 migration */
+  int         _bit_depth,_color_type,_interlace_type,_compression_type,_filter_type,_num_text,_num_palette;
+  png_uint_32 _width,_height;
+  png_timep   _mod_time;
+  double      _gamma;
+  png_textp   _text;
+  png_colorp  _palette;
+  png_color_16p _background;
 
   fbasename = BaseName(fname);
 
@@ -921,7 +950,7 @@ int LoadPNG(fname, pinfo)
     FatalError("malloc failure in LoadPNG");
   }
 
-  if (setjmp(png_ptr->jmpbuf)) {
+  if (setjmp(png_jmpbuf(png_ptr))) {
     fclose(fp);
     png_destroy_read_struct(&png_ptr, &info_ptr, (png_infopp)NULL);
     if (!read_anything) {
@@ -945,8 +974,10 @@ int LoadPNG(fname, pinfo)
 #endif
   png_read_info(png_ptr, info_ptr);
 
-  pinfo->w = pinfo->normw = info_ptr->width;
-  pinfo->h = pinfo->normh = info_ptr->height;
+  png_get_IHDR(png_ptr,info_ptr,&_width,&_height,&_bit_depth,&_color_type,&_interlace_type,NULL,NULL);
+
+  pinfo->w = pinfo->normw = _width;
+  pinfo->h = pinfo->normh = _height;
   if (pinfo->w <= 0 || pinfo->h <= 0) {
     SetISTR(ISTR_WARNING, "%s:  image dimensions out of range (%dx%d)",
       fbasename, pinfo->w, pinfo->h);
@@ -957,9 +988,9 @@ int LoadPNG(fname, pinfo)
   pinfo->frmType = F_PNG;
 
   sprintf(pinfo->fullInfo, "PNG, %d bit ",
-          info_ptr->bit_depth * info_ptr->channels);
+          _bit_depth * png_get_channels(png_ptr,info_ptr));
 
-  switch(info_ptr->color_type) {
+  switch(_color_type) {
     case PNG_COLOR_TYPE_PALETTE:
       strcat(pinfo->fullInfo, "palette color");
       break;
@@ -983,15 +1014,17 @@ int LoadPNG(fname, pinfo)
 
   sprintf(pinfo->fullInfo + strlen(pinfo->fullInfo),
 	  ", %sinterlaced. (%d bytes)",
-	  info_ptr->interlace_type ? "" : "non-", filesize);
+	  _interlace_type ? "" : "non-", filesize);
 
-  sprintf(pinfo->shrtInfo, "%lux%lu PNG", info_ptr->width, info_ptr->height);
+  sprintf(pinfo->shrtInfo, "%lux%lu PNG", _width, _height);
 
-  if (info_ptr->bit_depth < 8)
+  if (_bit_depth < 8)
       png_set_packing(png_ptr);
 
-  if (info_ptr->valid & PNG_INFO_gAMA)
-    png_set_gamma(png_ptr, Display_Gamma, info_ptr->gamma);
+  if (png_get_valid(png_ptr,info_ptr,PNG_INFO_gAMA)) {
+    png_get_gAMA(png_ptr,info_ptr,&_gamma);
+    png_set_gamma(png_ptr, Display_Gamma, _gamma);
+  }
 /*
  *else
  *  png_set_gamma(png_ptr, Display_Gamma, 0.45);
@@ -1000,7 +1033,7 @@ int LoadPNG(fname, pinfo)
   gray_to_rgb = 0;   /* quiet a compiler warning */
 
   if (have_imagebg) {
-    if (info_ptr->bit_depth == 16) {
+    if (_bit_depth == 16) {
       my_background.red   = imagebgR;
       my_background.green = imagebgG;
       my_background.blue  = imagebgB;
@@ -1013,8 +1046,8 @@ int LoadPNG(fname, pinfo)
     }
     png_set_background(png_ptr, &my_background, PNG_BACKGROUND_GAMMA_SCREEN,
                        0, Display_Gamma);
-    if ((info_ptr->color_type == PNG_COLOR_TYPE_GRAY_ALPHA ||
-         (info_ptr->color_type == PNG_COLOR_TYPE_GRAY && HAVE_tRNS)) &&
+    if ((_color_type == PNG_COLOR_TYPE_GRAY_ALPHA ||
+         (_color_type == PNG_COLOR_TYPE_GRAY && HAVE_tRNS)) &&
         (imagebgR != imagebgG || imagebgR != imagebgB))  /* i.e., colored bg */
     {
       png_set_gray_to_rgb(png_ptr);
@@ -1022,8 +1055,9 @@ int LoadPNG(fname, pinfo)
       gray_to_rgb = 1;
     }
   } else {
-    if (info_ptr->valid & PNG_INFO_bKGD) {
-      png_set_background(png_ptr, &info_ptr->background,
+    if (png_get_valid(png_ptr,info_ptr,PNG_INFO_bKGD)) {
+      png_get_bKGD(png_ptr,info_ptr,&_background);
+      png_set_background(png_ptr, _background,
                          PNG_BACKGROUND_GAMMA_FILE, 1, 1.0);
     } else {
       my_background.red = my_background.green = my_background.blue =
@@ -1033,13 +1067,13 @@ int LoadPNG(fname, pinfo)
     }
   }
 
-  if (info_ptr->bit_depth == 16)
+  if (_bit_depth == 16)
     png_set_strip_16(png_ptr);
 
-  if (info_ptr->color_type == PNG_COLOR_TYPE_GRAY ||
-      info_ptr->color_type == PNG_COLOR_TYPE_GRAY_ALPHA)
+  if (_color_type == PNG_COLOR_TYPE_GRAY ||
+      _color_type == PNG_COLOR_TYPE_GRAY_ALPHA)
   {
-    if (info_ptr->bit_depth == 1)
+    if (_bit_depth == 1)
       pinfo->colType = F_BWDITHER;
     else
       pinfo->colType = F_GREYSCALE;
@@ -1049,9 +1083,11 @@ int LoadPNG(fname, pinfo)
   pass=png_set_interlace_handling(png_ptr);
 
   png_read_update_info(png_ptr, info_ptr);
+  /* get HIDR again just in case the info_ptr changed */
+  png_get_IHDR(png_ptr,info_ptr,&_width,&_height,&_bit_depth,&_color_type,&_interlace_type,NULL,NULL);
 
-  if (info_ptr->color_type == PNG_COLOR_TYPE_RGB ||
-     info_ptr->color_type == PNG_COLOR_TYPE_RGB_ALPHA || gray_to_rgb)
+  if (_color_type == PNG_COLOR_TYPE_RGB ||
+     _color_type == PNG_COLOR_TYPE_RGB_ALPHA || gray_to_rgb)
   {
     linesize = 3 * pinfo->w;
     if (linesize/3 < pinfo->w) {   /* know pinfo->w > 0 (see above) */
@@ -1065,16 +1101,17 @@ int LoadPNG(fname, pinfo)
   } else {
     linesize = pinfo->w;
     pinfo->type = PIC8;
-    if (info_ptr->color_type == PNG_COLOR_TYPE_GRAY ||
-       info_ptr->color_type == PNG_COLOR_TYPE_GRAY_ALPHA) {
+    if (_color_type == PNG_COLOR_TYPE_GRAY ||
+       _color_type == PNG_COLOR_TYPE_GRAY_ALPHA) {
       for (i = 0; i < 256; i++)
         pinfo->r[i] = pinfo->g[i] = pinfo->b[i] = i;
     } else {
       pinfo->colType = F_FULLCOLOR;
-      for (i = 0; i < info_ptr->num_palette; i++) {
-        pinfo->r[i] = info_ptr->palette[i].red;
-        pinfo->g[i] = info_ptr->palette[i].green;
-        pinfo->b[i] = info_ptr->palette[i].blue;
+      png_get_PLTE(png_ptr,info_ptr,&_palette,&_num_palette);
+      for (i = 0; i < _num_palette; i++) {
+        pinfo->r[i] = _palette[i].red;
+        pinfo->g[i] = _palette[i].green;
+        pinfo->b[i] = _palette[i].blue;
       }
     }
   }
@@ -1092,7 +1129,7 @@ int LoadPNG(fname, pinfo)
     png_error(png_ptr, "can't allocate space for PNG image");
   }
 
-  png_start_read_image(png_ptr);
+  /*png_start_read_image(png_ptr); -- causes a warning and seems to be unnecessary */
 
   for (i = 0; i < pass; i++) {
     byte *p = pinfo->pic;
@@ -1106,22 +1143,23 @@ int LoadPNG(fname, pinfo)
 
   png_read_end(png_ptr, info_ptr);
 
-  if (info_ptr->num_text > 0) {
+  png_get_text(png_ptr,info_ptr,&_text,&_num_text);
+  if (_num_text > 0) {
     commentsize = 1;
 
-    for (i = 0; i < info_ptr->num_text; i++)
-      commentsize += strlen(info_ptr->text[i].key) + 1 +
-                     info_ptr->text[i].text_length + 2;
+    for (i = 0; i < _num_text; i++)
+      commentsize += strlen(_text[i].key) + 1 +
+                     _text[i].text_length + 2;
 
     if ((pinfo->comment = malloc(commentsize)) == NULL) {
       png_warning(png_ptr,"can't allocate comment string");
     }
     else {
       pinfo->comment[0] = '\0';
-      for (i = 0; i < info_ptr->num_text; i++) {
-        strcat(pinfo->comment, info_ptr->text[i].key);
+      for (i = 0; i < _num_text; i++) {
+        strcat(pinfo->comment, _text[i].key);
         strcat(pinfo->comment, "::");
-        strcat(pinfo->comment, info_ptr->text[i].text);
+        strcat(pinfo->comment, _text[i].text);
         strcat(pinfo->comment, "\n");
       }
     }
@@ -1143,7 +1181,7 @@ png_xv_error(png_ptr, message)
 {
   SetISTR(ISTR_WARNING,"%s:  libpng error: %s", fbasename, message);
 
-  longjmp(png_ptr->jmpbuf, 1);
+  longjmp(png_jmpbuf(png_ptr), 1);
 }
 
 
