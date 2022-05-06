#include <Arduino.h>

typedef struct {
  uint8_t pin;
  uint8_t mode;
} pins;

// 
// For ESP32
// 

// const pins anodePins[] {
//   {15, LOW},
//   {2, LOW},
//   {0, LOW},
// };

// const pins cathodPins[] {
//   {4, LOW},
//   {16, LOW},
//   {17, LOW},
//   {5, LOW},
//   {18, LOW},
//   {19, LOW},
//   {21, LOW},
//   {22, LOW},
//   {23, LOW},
// };


//
// For Arduino
//

const pins anodePins[] {
  {2, LOW},
  {3, LOW},
  {4, LOW},
};

const pins cathodPins[] {
  {5, LOW},
  {6, LOW},
  {7, LOW},
  {8, LOW},
  {9, LOW},
  {10, LOW},
  {11, LOW},
  {12, LOW},
  {13, LOW},
};

void allAnodes(int);
void allCathods(int);
void columnAll(int, int);
void clear();
void xRowAll(int, int);
void yRowAll(int, int);
void forwardSnake(int);
void reverseSnake(int);
void blink();
void elevator();
void pusher();
void snake();

void setup() {

  Serial.begin(9600);

  for (int i = 0; i < 3; i++) {
    pinMode(anodePins[i].pin, OUTPUT);
    digitalWrite(anodePins[i].pin, HIGH);
  }
  for (int i = 0; i < 9; i++) {
    pinMode(cathodPins[i].pin, OUTPUT);
    digitalWrite(cathodPins[i].pin, LOW);
  }

  allCathods(HIGH);
  allAnodes(LOW);
}

bool flag = true;

void loop() {
  snake();
}

void forwardSnake(int column) {
  int i = column;
  int array[] = {6, 7, 8, 3, 4, 5, 2, 1, 0};
  for (int j = 0; j < 9; j++) {
    digitalWrite(anodePins[i].pin, HIGH);
    digitalWrite(cathodPins[array[j]].pin, LOW);
    delay(120);
    digitalWrite(anodePins[i].pin, LOW);
    digitalWrite(cathodPins[array[j]].pin, HIGH);
  }
}

void reverseSnake(int column) {
  int i = column;
  int array[] = {0, 1, 2, 5, 4, 3, 8, 7, 6};
  for (int j = 0; j < 9; j++) {
    digitalWrite(anodePins[i].pin, HIGH);
    digitalWrite(cathodPins[array[j]].pin, LOW);
    delay(120);
    digitalWrite(anodePins[i].pin, LOW);
    digitalWrite(cathodPins[array[j]].pin, HIGH);
  }
}

void allAnodes(int level) {
  for (int i = 0; i < 3; i++) {
    digitalWrite(anodePins[i].pin, level);
  }
}

void allCathods(int level) {
  for (int i = 0; i < 9; i++) {
    digitalWrite(cathodPins[i].pin, level);
  }
}

void columnAll(int index, int level) {
  digitalWrite(anodePins[index].pin, level);
}

void xRowAll(int index, int level) {
  int offset = index;
  for (int i = 0 + offset * 3; i < 3 * (offset + 1); i++) {
    digitalWrite(cathodPins[i].pin, level);
  }
  allAnodes(HIGH);
}

void yRowAll(int index, int level) {
  int offset = index;
  for (int i = 0 + offset; i < 7 + offset * 3; i += 3) {
    digitalWrite(cathodPins[i].pin, level);
  }
  allAnodes(HIGH);
}

void clear() {
  for (int i = 0; i < 3; i++) {
    pinMode(anodePins[i].pin, OUTPUT);
    digitalWrite(anodePins[i].pin, HIGH);
  }
  for (int i = 0; i < 9; i++) {
    pinMode(cathodPins[i].pin, OUTPUT);
    digitalWrite(cathodPins[i].pin, HIGH);
  }
}

// Animations

void blink() {
  allCathods(LOW);
  allAnodes(HIGH);
  delay(300);
  allCathods(HIGH);
  allAnodes(LOW);
  delay(300);
}

void elevator() {
  allCathods(LOW);
  for(int i = 0; i < 3; i++) {
    columnAll(i, HIGH);
    delay(75);
    allAnodes(LOW);
  }
  columnAll(2, HIGH);
  delay(125);
  allAnodes(LOW);
  for(int i = 2; i > -1; i--) {
    columnAll(i, HIGH);
    delay(75);
    allAnodes(LOW);
  }
  columnAll(0, HIGH);
  delay(125);
  allAnodes(LOW);
}

void pusher() {
  for (int i = 0; i < 3; ++i) {
    allCathods(HIGH);
    allAnodes(HIGH);
    xRowAll(i, LOW);
    delay(200);
    Serial.print("forward xRow: ");
    Serial.print(String(i) + "\n");
  }
  for (int i = 0; i < 3; ++i) {
    allCathods(HIGH);
    allAnodes(HIGH);
    yRowAll(i, LOW);
    delay(200);
    Serial.print("forward yRow: ");
    Serial.print(String(i) + "\n");
  }
  for (int i = 2; i > -1; --i) {
    allCathods(HIGH);
    allAnodes(HIGH);
    xRowAll(i, LOW);
    delay(200);
    Serial.print("forward xRow: ");
    Serial.print(String(i) + "\n");
  }
  for (int i = 2; i > -1; --i) {
    allCathods(HIGH);
    allAnodes(HIGH);
    yRowAll(i, LOW);
    delay(200);
    Serial.print("forward yRow: ");
    Serial.print(String(i) + "\n");
  }
}

void snake() {
  allCathods(HIGH);
  allAnodes(LOW);
  reverseSnake(2);

  allCathods(HIGH);
  allAnodes(LOW);
  forwardSnake(1);

  allCathods(HIGH);
  allAnodes(LOW);
  reverseSnake(0);

  allCathods(HIGH);
  allAnodes(LOW);
  forwardSnake(1);
}
