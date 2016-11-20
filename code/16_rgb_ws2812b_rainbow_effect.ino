/*
 * Rui Santos 
 * Complete Project Details http://randomnerdtutorials.com
 */

#include <FastLED.h>

#define LED_PIN     5
// Change the variable below to the number of RGB LEDs that your strip has
#define NUM_LEDS    14
#define BRIGHTNESS  255
#define LED_TYPE    WS2812
#define COLOR_ORDER GRB
CRGB leds[NUM_LEDS];

#define UPDATES_PER_SECOND 50

CRGBPalette16 currentPalette;
TBlendType    currentBlending;

void setup() {
    delay(3000); // power-up safety delay
    FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
    FastLED.setBrightness(  BRIGHTNESS );
    
    currentPalette = RainbowColors_p;
    currentBlending = LINEARBLEND;
}

void loop(){
    ChangePalettePeriodically();
    
    static uint8_t startIndex = 0;
    startIndex = startIndex + 1;
    
    FillLEDsFromPaletteColors(startIndex);
    
    FastLED.show();
    FastLED.delay(2000 / UPDATES_PER_SECOND);
}

void FillLEDsFromPaletteColors(uint8_t colorIndex){
    uint8_t brightness = 255;
    
    for( int i = 0; i < NUM_LEDS; i++){
        leds[i] = ColorFromPalette( currentPalette, colorIndex, brightness, currentBlending);
        colorIndex += 3;
    }
}

// There are several different palettes of colors demonstrated here.
//
// FastLED provides several 'preset' palettes: RainbowColors_p, RainbowStripeColors_p,
// OceanColors_p, CloudColors_p, LavaColors_p, ForestColors_p, and PartyColors_p.
//
// Additionally, you can manually define your own color palettes, or you can write
// code that creates color palettes on the fly.  All are shown here.

void ChangePalettePeriodically(){
    uint8_t secondHand = (millis() / 1000) % 60;
    static uint8_t lastSecond = 99;
    
    if(lastSecond != secondHand){
        lastSecond = secondHand;
        if(secondHand ==  0){ currentPalette = RainbowColors_p; currentBlending = LINEARBLEND;}
    }
}
