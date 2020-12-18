#include <Bounce.h>

#define ROW1_PIN 15
#define ROW2_PIN 16
#define ROW3_PIN 17

#define COL1_PIN 18
#define COL2_PIN 19
#define COL3_PIN 20
#define COL4_PIN 21

//#define TOTAL_ROWS 2
//#define TOTAL_COLUMNS 1

#define TOTAL_ROWS 3
#define TOTAL_COLUMNS 4

#define TOTAL_KEYS TOTAL_COLUMNS * TOTAL_ROWS

#define DEBOUNCE_DELAY 10

const uint8_t rowPins[3] = {ROW1_PIN ,ROW2_PIN, ROW3_PIN};
const uint8_t columnPins[4] = {COL1_PIN ,COL2_PIN, COL3_PIN, COL4_PIN};

const int keyMap[TOTAL_ROWS][TOTAL_COLUMNS] = {{KEY_Q, KEY_B, KEY_C, KEY_D},{KEY_E, KEY_F, KEY_G, KEY_H},{KEY_I, KEY_J, KEY_K, KEY_L}};

bool switchLastState[TOTAL_ROWS][TOTAL_COLUMNS] = {{0}};
elapsedMillis lastStateChange[TOTAL_ROWS][TOTAL_COLUMNS] = {{0}};

void setup() {
  initialisePins();
}

void loop() {
  scanForKeyPresses();
}
  
void initialisePins() {
  for (int i = 0; i < TOTAL_ROWS; ++i) {
    pinMode(rowPins[i], OUTPUT);
    digitalWrite(rowPins[i], LOW);
  }

  for (int i = 0; i < TOTAL_COLUMNS; ++i) {
    pinMode(columnPins[i], INPUT_PULLDOWN);
  }
}

void scanForKeyPresses()
{
  for (int i = 0; i < TOTAL_ROWS; ++i) {
    delay(1);
    digitalWrite(rowPins[i], HIGH);
    for (int j = 0; j < TOTAL_COLUMNS; ++j) {
      if(lastStateChange[i][j] > DEBOUNCE_DELAY)
      {
        bool keyPressed = digitalRead(columnPins[j]);
        if(switchLastState[i][j] != keyPressed)
        {
          switchLastState[i][j] = keyPressed;
          lastStateChange[i][j] = 0;

          //Press On Rising edge
          if(keyPressed)
          {
            pressKey(i,j);
          }
        }
      }
    }
    
    digitalWrite(rowPins[i], LOW);
  }
}

void pressKey(int row, int column) {
    Keyboard.set_modifier(MODIFIERKEY_CTRL | MODIFIERKEY_ALT);
    Keyboard.set_key1(keyMap[row][column]);
    Keyboard.send_now();

    Keyboard.set_modifier(0);
    Keyboard.set_key1(0);
    Keyboard.send_now();  
}  
