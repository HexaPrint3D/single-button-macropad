/*
  single button macropad with esp32s3 super mini HW-747 board
  you can also use an other board like xiao esp32s3 or similar. Note that the rgb led probably will not work because it maybe doesn't have a built
  in rg led. 
  I used a keyboard switch for the button

  Have fun with this project! :)

*/
#include "Arduino.h"
#include "USB.h"
#include "USBHIDKeyboard.h"
#include <Adafruit_NeoPixel.h>

//create a keyboard object
USBHIDKeyboard keyboard;

// Define the pin where the RGB LED is connected
#define LED_PIN     48 //you might have to change that nuber if your led is connected to another pin
// Define the number of LEDs
#define NUM_PIXELS   1

const int switchpin = 13;
int buttonState = 0;
// Initialize the NeoPixel strip object
Adafruit_NeoPixel pixel(NUM_PIXELS, LED_PIN, NEO_GRB + NEO_KHZ800);



void openCmd() { // for open command interface on windows. You don't really need it, unless you want it to run some cmd commands
  keyboard.press(KEY_LEFT_GUI);  
  keyboard.press('r');
  delay(20);                    
  keyboard.releaseAll();         
  
  
  delay(800);

  
  keyboard.print("cmd");
  delay(20);

  
  keyboard.press(KEY_RETURN);    
  delay(400);
  keyboard.releaseAll();         
  delay(300);
  
  keyboard.press(KEY_LEFT_GUI);
  keyboard.press(KEY_UP_ARROW);
  delay(50);
  keyboard.releaseAll();
  delay(200);
}


void printGerman(String text) { // I am using a german keyboard layout and the library does not suport other layouts than english so this fixes my problems
// if you use an english layout you need to delete this function and replace some lines. 
  for (int i = 0; i < text.length(); i++) {
    char c = text[i];
    
    if (c == '/') {
      keyboard.press(KEY_LEFT_SHIFT);
      keyboard.press('7');
      delay(10);
      keyboard.releaseAll();
    } 
    else if (c == ':') {
      keyboard.press(KEY_LEFT_SHIFT);
      keyboard.press('.');
      delay(10);
      keyboard.releaseAll();
    } 
    else if (c == '?') {
      keyboard.press(KEY_LEFT_SHIFT);
      keyboard.press('-'); 
      delay(10);
      keyboard.releaseAll();
    } 
    else if (c == '=') {
      keyboard.press(KEY_LEFT_SHIFT);
      keyboard.press('0');
      delay(10);
      keyboard.releaseAll();
    } 
    else if (c == 'z') {
      keyboard.print('y'); 
    } 
    else if (c == 'y') {
      keyboard.print('z');
    } 
    else if (c == 'Z') {
      keyboard.print('Y');
    } 
    else if (c == 'Y') {
      keyboard.print('Z');
    } 
    else {
      keyboard.print(c); 
    }
    delay(10); 
  }
}

void write() { // defines what should happen when the button is pressed
  // ------------------------------ you can replace this code with your own --------------------------------------------------------------------

  pixel.setPixelColor(0, pixel.Color(0, 0, 200)); // this sets the onboard rgb led to blue
  pixel.show();

  printGerman("hello world!"); // replace this line with keyboard.print("your text"); if you use an english layout

  keyboard.press(KEY_LEFT_GUI); // this presses the key combo win + d
  keyboard.press('d');          //
  delay(10);                    // 
  keyboard.releaseAll();        //  
  
  delay(700);
  pixel.clear(); // this turns the rgb led off
  pixel.show();
  //---------------------------------------------------------------------------------------------------------------------------------------------
}

void setup() {
  keyboard.begin();
  USB.begin();
  pixel.begin();
  pixel.clear();
  
  pinMode(switchpin, INPUT_PULLUP);
  delay(5000);
}

void loop() {
  buttonState = digitalRead(switchpin);

  if (buttonState == LOW) {
    write();
    delay(700); 
  }
}
