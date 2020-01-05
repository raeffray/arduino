#include <Adafruit_CircuitPlayground.h>

// Define arrays de 3 posicoes pra acomodar os codigos das cores em RGB (https://www.html.am/html-codes/color/color-scheme.cfm)
int RED[3] = {255, 0, 0};
int YELLOW[3] = {128, 128, 0};
int GREEN[3] = {0, 255, 0};
int MAGENTA[3] = {255, 0, 255};
int D_BLUE[3] = {0, 0, 255};

// notas definidas em hertz
long C = 261.63;
long D = 293.665;
long E = 329.628;
long F = 349.228;
long G = 391.995;
long A = 440;
long B = 466.164;

int LED_POSITION_NOTE[10] = {A, B, C, D, E, F, G, A, B, C};

// quantidade de leds no circuit playground
int LED_QUANTITY = 10;

// posicao do ultimo led
int LAST_LED_POSITION = LED_QUANTITY - 1;

bool leftButtonPressed;
bool rightButtonPressed;

// acumula quando apertamos os botoes laterais
int countPress;

void setup()
{
  CircuitPlayground.begin();
  Serial.begin(9600);
}

void loop()
{
  if (CircuitPlayground.slideSwitch())
  {
    readButtons();
    turnLighOnPress(countPress);
    delay(70);
  }
  else
  {
    CircuitPlayground.clearPixels();
  }
}

void turnOnLed(int ledPos, int colour[3])
{
  // o ultimo LED eh o 10 (posicao 9)/
  // quando mandamos acender o LED 11 (posicao 19), ele nao existe, entao mandamos acender o led posicao 0 (atual led que queremos acender, menos a quantidade total)
  // exemplos:
  // led posicao 10 - vai acender o 0
  // led posicao 11 - vai acender o 1
  // led posicao 12 - vai acender
  if (ledPos > LAST_LED_POSITION)
  {
    ledPos = ledPos - LED_QUANTITY;
  }

  CircuitPlayground.setPixelColor(ledPos, colour[0], colour[1], colour[2]);
}

void playSound(long note)
{
  CircuitPlayground.playTone(note, 100);
}

int readButtons()
{

  int oldCounting = countPress;

  leftButtonPressed = CircuitPlayground.leftButton();
  rightButtonPressed = CircuitPlayground.rightButton();

  if (rightButtonPressed)
  {
    if (countPress == LAST_LED_POSITION)
    {
      countPress = 0;
    }
    else
    {
      countPress++;
    }
  }
  else if (leftButtonPressed)
  {
    if (countPress == 0)
    {
      countPress = LAST_LED_POSITION;
    }
    else
    {
      countPress--;
    }
  }

  if (oldCounting != countPress)
  {
    playSound(LED_POSITION_NOTE[countPress]);
  }

  return countPress;
}

void turnLighOnPress(int value)
{
  CircuitPlayground.clearPixels();

  turnOnLed(value, D_BLUE);
  turnOnLed(value + 1, GREEN);
  turnOnLed(value + 2, RED);
  turnOnLed(value + 3, YELLOW);
  turnOnLed(value + 4, MAGENTA);
}
