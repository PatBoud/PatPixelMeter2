/*
PatPixelMeter2.cpp - Librairie pour utiliser un NeoPixel Ring comme jauge
Par: PatBoud
Date: 2016-09-21

*/
#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include <PatPixelMeter2.h>

int _maxBrightness;
int _nbPixelsPrec;
int _nbPixelsTotal;
int _tabPixels[32]; //Tableau de correspondance POSITION DANS LE METER : PIXEL SUR LA STRIP

PatPixelMeter::PatPixelMeter(Adafruit_NeoPixel *pixels, int _pixelMin, int _pixelMax)
  {
  // Private
  int _i;
  int _iPixel = 0;

	_pixels = pixels;

	if (_pixelMax > _pixelMin) {
		_nbPixelsTotal = _pixelMax - _pixelMin + 1;

    for (_i=0; _i<32;_i++) {
      if ((_i >= _pixelMin) && (_i <= _pixelMax)) {
        _tabPixels[_iPixel] = _i;
        _iPixel ++;
      }
    }
	}
	else {
		_nbPixelsTotal = _pixelMin - _pixelMax + 1;

    for (_i=31; _i>=0;_i--) {
      if ((_i <= _pixelMin) && (_i >= _pixelMax)) {
        _tabPixels[_iPixel] = _i;
        _iPixel ++;
      }
    }
	}

  _nbPixelsPrec = 0;

  // Public
  int pourcentPrec = 0;

}

// Vide soudainement le meter, sans animation
void PatPixelMeter::clear(void) {
  int i;
  for (i=0;i<_nbPixelsTotal;i++) {
    _pixels->setPixelColor(_tabPixels[i-1], 0, 0, 0); //OFF
  }
  _pixels->show();

  //Reinitialisation des variables
  _nbPixelsPrec = 0;
  pourcentPrec = 0;
}


// Remet le meter à zero en faisant l'animation habituelle
void PatPixelMeter::zero(void) {
	int i;
	for (i=_nbPixelsPrec; i>0; i--) {
		_pixels->setPixelColor(_tabPixels[i-1], 0, 0, 0);
		_pixels->show();
		delay(50);

		//Reinitialisation des variables
		_nbPixelsPrec = 0;
		pourcentPrec = 0;
	}
}

void PatPixelMeter::affiche(int typeMeter, int pourcent, int R, int G, int B) {
  int variation;
  int i;

  int _nbPixels = map(pourcent, 0, 100, 0, _nbPixelsTotal);

  if (_nbPixelsPrec < _nbPixels) {
    variation = 1;
  }
  else {
    variation = -1;
  }

  Serial.print("Pourcent: ");
  Serial.println(pourcent);

  Serial.print("Pixels: ");
  Serial.println (_nbPixels);

  switch (typeMeter) {

    case METER_VJR_STEPS:
      // 50% pixels verts, 25% pixels jaunes, 25% pixels rouges

      float pourcentSteps;
      //On allume les pixels en montant
      if (variation == 1) {
        for (i=_nbPixelsPrec+1; i<=_nbPixels;i++) {
            pourcentSteps = (float)(i-1) / (float)_nbPixelsTotal;

            if (pourcentSteps >= 0.75) {
              _pixels->setPixelColor(_tabPixels[i-1], 255, 0, 0); //Rouge
            }
            else {
              if (pourcentSteps >= 0.5) {
                _pixels->setPixelColor(_tabPixels[i-1], 255, 255, 0); //Jaune
              }
              else {
                _pixels->setPixelColor(_tabPixels[i-1], 0, 255, 0); //Vert
              }
            }

          _pixels->show();
          delay(50);
        }
      }
      else {
        //On eteint les pixels en descendant
        for (i=_nbPixelsPrec; i>_nbPixels; i--) {
          _pixels->setPixelColor(_tabPixels[i-1], 0, 0, 0);
          _pixels->show();
          delay(50);
        }
      }
      break;


    case METER_BLEU:
      // Teintes de bleu

      //On allume les pixels en montant
      if (variation == 1) {
        for (i=_nbPixelsPrec+1; i<=_nbPixels;i++) {
          //_pixels->setPixelColor(_tabPixels[i-1], 0, 0, i * _nbPixelsTotal - 1);
					_pixels->setPixelColor(_tabPixels[i-1], 0, 0, map(i, 0, _nbPixelsTotal, 25, 255));
          _pixels->show();
          delay(50);
        }
      }
      else {
        //On eteint les pixels en descendant
        for (i=_nbPixelsPrec; i>_nbPixels; i--) {
          _pixels->setPixelColor(_tabPixels[i-1], 0, 0, 0);
          _pixels->show();
          delay(50);
        }
      }
      break;


    case METER_VJR_DEGRADE:
      // Degrade de vert a jaune a rouge

      //On allume les pixels en montant
      if (variation == 1) {
        for (i=_nbPixelsPrec+1; i<=_nbPixels;i++) {
          _pixels->setPixelColor(_tabPixels[i-1], _Wheel(map(_nbPixelsTotal - i, 0, _nbPixelsTotal, 0, 80)));
          _pixels->show();
          delay(50);
        }
      }
      else {
        //On eteint les pixels en descendant
        for (i=_nbPixelsPrec; i>_nbPixels; i--) {
          _pixels->setPixelColor(_tabPixels[i-1], 0, 0, 0);
          _pixels->show();
          delay(50);
        }
      }
      break;


    case METER_RAINBOW:
      // Degrade arc-en-ciel

      //On allume les pixels en montant
      if (variation == 1) {
        for (i=_nbPixelsPrec+1; i<=_nbPixels;i++) {
          _pixels->setPixelColor(_tabPixels[i-1], _Wheel(map(_nbPixelsTotal - i, 0, _nbPixelsTotal, 0, 255)));
          _pixels->show();
          delay(50);
        }
      }
      else {
        //On eteint les pixels en descendant
        for (i=_nbPixelsPrec; i>_nbPixels; i--) {
          _pixels->setPixelColor(_tabPixels[i-1], 0, 0, 0);
          _pixels->show();
          delay(50);
        }
      }
      break;



	case METER_MAUVE_BLEU:
      // Degrade mauve-bleu

      //On allume les pixels en montant
      if (variation == 1) {
        for (i=_nbPixelsPrec+1; i<=_nbPixels;i++) {
          _pixels->setPixelColor(_tabPixels[i-1], _Wheel(map(_nbPixelsTotal - i, 0, _nbPixelsTotal, 100, 200)));
          _pixels->show();
          delay(50);
        }
      }
      else {
        //On eteint les pixels en descendant
        for (i=_nbPixelsPrec; i>_nbPixels; i--) {
          _pixels->setPixelColor(_tabPixels[i-1], 0, 0, 0);
          _pixels->show();
          delay(50);
        }
      }
      break;


	case METER_ROUGE:
      // Que du rouge

      //On allume les pixels en montant
      if (variation == 1) {
        for (i=_nbPixelsPrec+1; i<=_nbPixels;i++) {
          _pixels->setPixelColor(_tabPixels[i-1], 255, 0, 0);
          _pixels->show();
          delay(50);
        }
      }
      else {
        //On eteint les pixels en descendant
        for (i=_nbPixelsPrec; i>_nbPixels; i--) {
          _pixels->setPixelColor(_tabPixels[i-1], 0, 0, 0);
          _pixels->show();
          delay(50);
        }
      }
      break;


			case METER_COULEUR:
					// Couleur definie par l'utilisateur

					//On allume les pixels en montant
					if (variation == 1) {
						for (i=_nbPixelsPrec+1; i<=_nbPixels;i++) {
							_pixels->setPixelColor(_tabPixels[i-1], R, G, B);
							_pixels->show();
							delay(50);
						}
					}
					else {
						//On eteint les pixels en descendant
						for (i=_nbPixelsPrec; i>_nbPixels; i--) {
							_pixels->setPixelColor(_tabPixels[i-1], 0, 0, 0);
							_pixels->show();
							delay(50);
						}
					}
					break;
			}

  _nbPixelsPrec = _nbPixels;
  pourcentPrec = pourcent;
}



// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t PatPixelMeter::_Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return _pixels->Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    return _pixels->Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return _pixels->Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}
