package com.tencent;

import android.util.Log;

import java.io.BufferedInputStream;
import java.io.BufferedOutputStream;
import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.io.UnsupportedEncodingException;
import java.util.Enumeration;
import java.util.zip.ZipEntry;
import java.util.zip.ZipFile;

/**
 * Created by icezheng on 4/12/15.
 */
public class ZipUtils {

    private static final String TAG = "Skin-Utils";

    private static final int BUFF_SIZE = 1024 * 10; // 10KB

    /**
     * 解压缩功能.
     * 将zipFile文件解压到folderPath目录下.
     *
     * @throws Exception
     */
    public static int unZipFile(File zipFile, String folderPath) throws IOException, SecurityException {
        ZipFile zfile = null;
        try {
            File dest = new File(folderPath);
            if (dest.exists()) {
                dest.delete();
            } else {
                dest.mkdirs();
            }

            zfile = new ZipFile(zipFile);
            Enumeration zList = zfile.entries();
            ZipEntry ze = null;
            byte[] buf = new byte[BUFF_SIZE];
            while (zList.hasMoreElements()) {
                ze = (ZipEntry) zList.nextElement();
                if (ze.getName().contains("../")) {
                    Log.e(TAG, "usecurity zipFile! filename is :" + ze.getName());
                    throw new SecurityException("unsecurity zipfile!");
                }
                if (ze.isDirectory()) {
                    String dirstr = folderPath + ze.getName();
                    //dirstr.trim();
                    dirstr = new String(dirstr.getBytes("8859_1"), "GB2312");
                    File file = new File(dirstr);
                    file.mkdir();
                    continue;
                }
                OutputStream os = null;
                InputStream is = null;
                try {
                    os = new BufferedOutputStream(new FileOutputStream(getRealFileName(folderPath, ze.getName())));
                    is = new BufferedInputStream(zfile.getInputStream(ze));
                    int readLen = 0;
                    while ((readLen = is.read(buf, 0, BUFF_SIZE)) != -1) {
                        os.write(buf, 0, readLen);
                    }
                } catch (IOException e) {
                    throw e;
                } finally {
                    if (is != null) {
                        is.close();
                    }
                    if (os != null) {
                        os.close();
                    }
                }
            }
        } catch (IOException e) {
            Log.e(TAG, e.getMessage());
            throw e;
        } finally {
            if (zfile != null) {
                zfile.close();
            }
        }
        return 0;
    }

    /**
     * 给定根目录，返回一个相对路径所对应的实际文件名.
     *
     * @param baseDir     指定根目录
     * @param absFileName 相对路径名，来自于ZipEntry中的name
     *
     * @return java.io.File 实际的文件
     */
    public static File getRealFileName(String baseDir, String absFileName) {
        String[] dirs = absFileName.split("/");
        File ret = new File(baseDir);
        String substr = null;
        if (dirs.length >= 1) {
            for (int i = 0; i < dirs.length - 1; i++) {
                substr = dirs[i];
                try {
                    //substr.trim();
                    substr = new String(substr.getBytes("8859_1"), "GB2312");

                } catch (UnsupportedEncodingException e) {
                    // TODO Auto-generated catch block
                    e.printStackTrace();
                }
                ret = new File(ret, substr);

            }
            if (!ret.exists()) {
                ret.mkdirs();
            }
            substr = dirs[dirs.length - 1];
            try {
                //substr.trim();
                substr = new String(substr.getBytes("8859_1"), "GB2312");
            } catch (UnsupportedEncodingException e) {
                // TODO Auto-generated catch block
                e.printStackTrace();
            }

            ret = new File(ret, substr);
            return ret;
        }
        return ret;
    }

}
