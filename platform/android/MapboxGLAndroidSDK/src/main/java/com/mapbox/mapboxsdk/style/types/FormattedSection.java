package com.mapbox.mapboxsdk.style.types;

import android.support.annotation.Keep;
import android.support.annotation.Nullable;

@Keep
public class FormattedSection {
  private String text;
  private double fontScale;
  private String[] fontStack;

  public FormattedSection(String text, double fontScale, String[] fontStack) {
    this.text = text;
    this.fontScale = fontScale;
    this.fontStack = fontStack;
  }

  public String getText() {
    return text;
  }

  public double getFontScale() {
    return fontScale;
  }

  @Nullable
  public String[] getFontStack() {
    return fontStack;
  }
}
