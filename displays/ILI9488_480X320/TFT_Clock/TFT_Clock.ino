#include <SPI.h>
#include <TFT_eSPI.h> // Hardware-specific library

#define TFT_GREY 0x5AEB

TFT_eSPI tft = TFT_eSPI(); // Invoke custom library

float sx = 0, sy = 1, mx = 1, my = 0, hx = -1, hy = 0; // Saved H, M, S x & y multipliers
float sdeg = 0, mdeg = 0, hdeg = 0;
uint16_t osx = 240, osy = 160, omx = 240, omy = 160, ohx = 240, ohy = 160; // Saved H, M, S x & y coords
uint16_t x0 = 0, x1 = 0, yy0 = 0, yy1 = 0;
uint32_t targetTime = 0; // for next 1 second timeout

static uint8_t conv2d(const char* p); // Forward declaration needed for IDE 1.6.x
uint8_t hh = conv2d(__TIME__), mm = conv2d(__TIME__ + 3), ss = conv2d(__TIME__ + 6); // Get H, M, S from compile time

bool initial = 1;

void setup(void) {
  tft.init();
  tft.setRotation(1); // Landscape mode
  
  tft.fillScreen(TFT_GREY);
  tft.setTextColor(TFT_WHITE, TFT_GREY); // Adding a background colour erases previous text automatically
  
  // Draw clock face
  tft.fillCircle(240, 160, 150, TFT_CYAN); // Adjusted to center and fill
  tft.fillCircle(240, 160, 140, TFT_BLACK);

  // Draw 12 lines
  for (int i = 0; i < 360; i += 30) {
    sx = cos((i - 90) * 0.0174532925);
    sy = sin((i - 90) * 0.0174532925);
    x0 = sx * 148 + 240; // Adjusted radius
    yy0 = sy * 148 + 160;
    x1 = sx * 120 + 240;
    yy1 = sy * 120 + 160;

    tft.drawLine(x0, yy0, x1, yy1, TFT_CYAN);
  }

  // Draw 60 dots
  for (int i = 0; i < 360; i += 6) {
    sx = cos((i - 90) * 0.0174532925);
    sy = sin((i - 90) * 0.0174532925);
    x0 = sx * 130 + 240;
    yy0 = sy * 130 + 160;
    // Draw minute markers
    tft.drawPixel(x0, yy0, TFT_WHITE);
  }

  tft.fillCircle(240, 160, 4, TFT_WHITE);
  targetTime = millis() + 1000;
}

void loop() {
  if (targetTime < millis()) {
    targetTime += 1000;
    ss++; // Advance second
    if (ss == 60) {
      ss = 0;
      mm++; // Advance minute
      if (mm > 59) {
        mm = 0;
        hh++; // Advance hour
        if (hh > 23) {
          hh = 0;
        }
      }
    }

    // Pre-compute hand degrees, x & y coords for a fast screen update
    sdeg = ss * 6;                // 0-59 -> 0-354
    mdeg = mm * 6 + sdeg * 0.01666667; // 0-59 -> 0-360 - includes seconds
    hdeg = hh * 30 + mdeg * 0.0833333; // 0-11 -> 0-360 - includes minutes and seconds
    hx = cos((hdeg - 90) * 0.0174532925);
    hy = sin((hdeg - 90) * 0.0174532925);
    mx = cos((mdeg - 90) * 0.0174532925);
    my = sin((mdeg - 90) * 0.0174532925);
    sx = cos((sdeg - 90) * 0.0174532925);
    sy = sin((sdeg - 90) * 0.0174532925);

    if (ss == 0 || initial) {
      initial = 0;
      // Erase hour and minute hand positions every minute
      tft.drawLine(ohx, ohy, 240, 160, TFT_BLACK);
      ohx = hx * 80 + 240; // Adjusted radius
      ohy = hy * 80 + 160;
      tft.drawLine(omx, omy, 240, 160, TFT_BLACK);
      omx = mx * 110 + 240;
      omy = my * 110 + 160;
    }

    // Redraw new hand positions
    tft.drawLine(osx, osy, 240, 160, TFT_BLACK);
    osx = sx * 120 + 240;
    osy = sy * 120 + 160;
    tft.drawLine(osx, osy, 240, 160, TFT_RED);
    tft.drawLine(ohx, ohy, 240, 160, TFT_WHITE);
    tft.drawLine(omx, omy, 240, 160, TFT_WHITE);

    tft.fillCircle(240, 160, 4, TFT_RED);
  }
}

static uint8_t conv2d(const char* p) {
  uint8_t v = 0;
  if ('0' <= *p && *p <= '9')
    v = *p - '0';
  return 10 * v + *++p - '0';
}