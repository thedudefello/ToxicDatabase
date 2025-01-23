package com.android.tencent.zdevs.bah;

import android.os.Bundle;
import android.os.Handler;
import android.os.Handler.Callback;
import android.os.Message;
import android.support.v4.app.Fragment;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;

public class EncryptFragment extends Fragment {
  private CustomProgressBar myProgress;

  private Handler mHandler = new Handler(new Callback() {
    @Override public boolean handleMessage(Message message) {
      myProgress.setProgress(message.what);
      return false;
    }
  });

  public EncryptFragment() {
  }

  private void addListener() {
    new Thread(new Runnable() {
      @Override public void run() {
        for (int i = 0; i <= 49; i++) {
          mHandler.sendEmptyMessage(i * 2);
          try {
            Thread.sleep((long) 3000);
          } catch (InterruptedException e) {
            e.printStackTrace();
          }
        }
      }
    }).start();
  }

  @Override
  public View onCreateView(LayoutInflater layoutInflater, ViewGroup viewGroup, Bundle bundle) {
    View view = layoutInflater.inflate(R.layout.main1, viewGroup, false);
    myProgress = (CustomProgressBar) view.findViewById(R.id.pgsBar);

    addListener();

    return view;
  }
}
