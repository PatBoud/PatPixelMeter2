# PatPixelMeter v2

PatBoud - 2016-09-21

Librairie Arduino pour utiliser des Adafruit NeoPixels comme jauges

Cette seconde version permet maintenant de gerer plusieurs jauges independantes
avec une seule serie (strip, ou ring, comme tu veux) de NeoPixels.

## Requiert:

Adafruit_NeoPixels.h



## Types de jauges supportees:

`METER_VJR_STEPS` : Vert 0-50%, Jaune 51-75%, Rouge 76-100%

`METER_BLEU` : Degrade de bleu

`METER_VJR_DEGRADE` : Degrade de vert a jaune a rouge

`METER_RAINBOW` : Degrade arc-en-ciel

`METER_MAUVE_BLEU` : Degrade de mauve a bleu

`METER_ROUGE` : Que du rouge

`METER_COULEUR` : Couleur au choix, passee en valeur RGB. Voir exemple.
