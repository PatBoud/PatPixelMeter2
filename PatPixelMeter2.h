/*
PatPixelMeter2.h - Librairie pour utiliser un NeoPixel Ring comme jauge
Par: PatBoud
Date: 2016-09-21

*/
#ifndef PatPixelMeter2_h
#define PatPixelMeter2_h

#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

#define METER_VJR_STEPS 1
#define METER_BLEU 2
#define METER_VJR_DEGRADE 3
#define METER_RAINBOW 4
#define METER_MAUVE_BLEU 5
#define METER_ROUGE 6
#define METER_COULEUR 7


class PatPixelMeter {
  public:
    PatPixelMeter(Adafruit_NeoPixel *pixels, int _pixelMin, int _pixelMax);
    void affiche(int typeMeter, int pourcent, int R=0, int G=0, int B=0);
    void clear(void);
		void zero(void);
    int pourcentPrec;
  private:
    int _pixelMin;
		int _pixelMax;
    int _tabPixels[32];
    int _nbPixelsPrec;
		int _nbPixelsTotal;
    uint32_t _Wheel(byte WheelPos);
    Adafruit_NeoPixel *_pixels;
};

#endif
