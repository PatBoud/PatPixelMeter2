#include <Adafruit_NeoPixel.h>
#include <PatPixelMeter2.h>

#define PIN 4
#define NUMPIXELS 16
#define BRIGHTNESS 20

// Bande ou anneau de NeoPixels
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

// Creation de differents meters
// Plusieurs meters peuvent se partager la meme bande de NeoPixels
// PatPixelMeter [Nom] = PatPixelMeter(&[NeoPixels], [pixelMinimum], [pixelMaximum]);

PatPixelMeter meterMoitieG = PatPixelMeter(&pixels, 15, 8); // Cote gauche d'un anneau
PatPixelMeter meterMoitieD = PatPixelMeter(&pixels, 7, 0);  // Cote droit d'un anneau

// On peut aussi reutiliser des pixels utilises dans d'autres meters
// Evidemment, on ne peut pas les utiliser en meme temps

PatPixelMeter meterComplet = PatPixelMeter(&pixels, 15, 0); // Anneau en entier

void setup() {
  // Initialisation de la ligne serial pour voir les messages d'information
  Serial.begin(115200);
  
  // Initialisation obligatoire des NeoPixels
  pixels.begin();
  pixels.setBrightness(BRIGHTNESS);
  pixels.show();

  // A partir de maintenant on peut afficher des valeurs avec les meters
  // en utilisant la methode [nom].affiche([Mode_de_couleur], [Pourcentage]);
}

void loop() {
  // Serie d'affichages pour demontrer les differents modes de couleur
  // disponibles dans la librairie

  // EN UTILISANT LE METER COMPLET
  meterComplet.affiche(METER_VJR_STEPS, 100);
  delay(2000);
  meterComplet.affiche(METER_VJR_STEPS, 0);
  delay(1000);

  meterComplet.affiche(METER_VJR_DEGRADE, 100);
  delay(2000);
  meterComplet.affiche(METER_VJR_DEGRADE, 0);
  delay(1000);

  meterComplet.affiche(METER_RAINBOW, 100);
  delay(2000);
  meterComplet.affiche(METER_RAINBOW, 0);
  delay(1000);

  meterComplet.affiche(METER_BLEU, 100);
  delay(2000);
  meterComplet.affiche(METER_BLEU, 0);
  delay(1000);

  meterComplet.affiche(METER_MAUVE_BLEU, 100);
  delay(2000);
  meterComplet.affiche(METER_MAUVE_BLEU, 0);
  delay(1000);

  meterComplet.affiche(METER_ROUGE, 100);
  delay(2000);
  meterComplet.clear(); // Efface tous les pixels de ce meter sans les animer
  delay(1000);

  // EN SEPARANT LES NEOPIXELS EN 2 MOITIES

  meterMoitieG.affiche(METER_VJR_STEPS, 100);
  meterMoitieD.affiche(METER_ROUGE, 100);
  delay(2000);
  meterMoitieG.affiche(METER_VJR_STEPS, 0);
  meterMoitieD.affiche(METER_ROUGE, 0);
  delay(1000);

  meterMoitieG.affiche(METER_BLEU, 100);
  meterMoitieD.affiche(METER_RAINBOW, 100);
  delay(2000);
  meterMoitieG.affiche(METER_BLEU, 0);
  meterMoitieD.affiche(METER_RAINBOW, 0);
  delay(1000);
}
