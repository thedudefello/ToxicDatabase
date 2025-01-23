package com.android.tencent.zdevs.bah;

import android.app.Activity;
import android.content.Context;
import android.graphics.Canvas;
import android.graphics.Paint;
import android.graphics.Rect;
import android.support.v4.internal.view.SupportMenu;
import android.util.AttributeSet;
import android.util.DisplayMetrics;
import android.widget.ProgressBar;

public class CustomProgressBar extends ProgressBar {
  Paint mPaint;
  String text;

  public CustomProgressBar(Context context) {
    super(context);
    initText();
  }

  public CustomProgressBar(Context context, AttributeSet attributeSet) {
    super(context, attributeSet);
    initText();
  }

  public CustomProgressBar(Context context, AttributeSet attributeSet, int i) {
    super(context, attributeSet, i);
    initText();
  }

  public static int getScreenHeight(Activity activity) {
    DisplayMetrics displayMetrics = new DisplayMetrics();
    activity.getWindowManager().getDefaultDisplay().getMetrics(displayMetrics);
    return displayMetrics.heightPixels;
  }

  public static int getScreenWidth(Activity activity) {
    DisplayMetrics displayMetrics = new DisplayMetrics();
    activity.getWindowManager().getDefaultDisplay().getMetrics(displayMetrics);
    return displayMetrics.widthPixels;
  }

  private void initText() {
    this.mPaint = new Paint();
    this.mPaint.setColor(SupportMenu.CATEGORY_MASK);
    if (getResources().getDisplayMetrics().widthPixels > 480) {
      this.mPaint.setTextSize((float) 36);
    } else {
      this.mPaint.setTextSize((float) 18);
    }
  }

  private void setText() {
    setText(getProgress());
  }

  private void setText(int i) {
    this.text =
        new StringBuffer().append(String.valueOf((i * 100) / getMax())).append("%").toString();
  }

  @Override protected void onDraw(Canvas canvas) {
    synchronized (this) {
      super.onDraw(canvas);
      Rect rect = new Rect();
      this.mPaint.getTextBounds(this.text, 0, this.text.length(), rect);
      canvas.drawText(this.text, (float) ((getWidth() / 2) - rect.centerX()),
          (float) ((getHeight() / 2) - rect.centerY()), this.mPaint);
    }
  }

  @Override public void setProgress(int i) {
    synchronized (this) {
      setText(i);
      super.setProgress(i);
    }
  }
}
