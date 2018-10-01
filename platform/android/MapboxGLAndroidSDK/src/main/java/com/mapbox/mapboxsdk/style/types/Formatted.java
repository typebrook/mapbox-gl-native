package com.mapbox.mapboxsdk.style.types;

import android.support.annotation.Keep;

@Keep
public class Formatted {
  private final FormattedSection[] formattedSections;

  public Formatted(FormattedSection[] formattedSections) {
    this.formattedSections = formattedSections;
  }

  public FormattedSection[] getFormattedSections() {
    return formattedSections;
  }
}
