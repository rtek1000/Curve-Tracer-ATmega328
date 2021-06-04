// Wave period: 12ms
// Interval between waves: 60ms

#include <TimerOne.h>

#define latch_d7 6
#define latch_d6 7
#define latch_d5 13
#define latch_d4 12
#define latch_d3 11
#define latch_d2 10
#define latch_d1 9
#define latch_d0 8

#define latch_clk 5

#define led 3

#define buff_ch 2
volatile int buff_index = 0;
volatile int buff_status[buff_ch] = {0};

int adc0_tmp = 0;
int adc1_tmp = 0;
int adc2_tmp = 0;

int i = 0;
int adc0[65][buff_ch] = {{0}, {0}};
int adc1[65][buff_ch] = {{0}, {0}};
int adc2[65][buff_ch] = {{0}, {0}};

byte flag0 = 0;

// https://www.daycounter.com/Calculators/Sine-Generator-Calculator.phtml
// Number of points: 64
// Max Amplitude: 203

const int wave[] = {
  0x65, 0x6f, 0x79, 0x82, 0x8c, 0x95, 0x9d, 0xa5,
  0xac, 0xb3, 0xb9, 0xbe, 0xc2, 0xc6, 0xc8, 0xca,
  0xca, 0xca, 0xc8, 0xc6, 0xc2, 0xbe, 0xb9, 0xb3,
  0xac, 0xa5, 0x9d, 0x95, 0x8c, 0x82, 0x79, 0x6f,
  0x65, 0x5b, 0x51, 0x48, 0x3e, 0x35, 0x2d, 0x25,
  0x1e, 0x17, 0x11, 0xc, 0x8, 0x4, 0x2, 0x0,
  0x0, 0x0, 0x2, 0x4, 0x8, 0xc, 0x11, 0x17,
  0x1e, 0x25, 0x2d, 0x35, 0x3e, 0x48, 0x51, 0x5b, 0x65
};

const byte offset = 28;

int val_tmp = 0;
byte val_100 = 0;
byte val_10 = 0;
byte val_1 = 0;

int count0 = 0;

float f_adc0_tmp = 0.0;
float f_adc1_tmp = 0.0;
float f_adc2_tmp = 0.0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  pinMode(latch_d0, OUTPUT);
  pinMode(latch_d1, OUTPUT);
  pinMode(latch_d2, OUTPUT);
  pinMode(latch_d3, OUTPUT);
  pinMode(latch_d4, OUTPUT);
  pinMode(latch_d5, OUTPUT);
  pinMode(latch_d6, OUTPUT);
  pinMode(latch_d7, OUTPUT);
  pinMode(latch_clk, OUTPUT);
  pinMode(led, OUTPUT);

  digitalWrite(latch_d0, HIGH);
  digitalWrite(latch_d1, LOW);
  digitalWrite(latch_d2, LOW);
  digitalWrite(latch_d3, LOW);
  digitalWrite(latch_d4, LOW);
  digitalWrite(latch_d5, LOW);
  digitalWrite(latch_d6, LOW);
  digitalWrite(latch_d7, HIGH);

  digitalWrite(latch_clk, LOW);
  delayMicroseconds(100);
  digitalWrite(latch_clk, HIGH);

  digitalWrite(led, HIGH);

  Timer1.initialize(188);
  Timer1.attachInterrupt(tmr1_int);

  // https://www.hackster.io/ArduinoKoen/arduino-very-fast-read-and-very-cheap-scope-d06e23
  ADCSRA = 0;             // clear ADCSRA register
  ADCSRB = 0;             // clear ADCSRB register
  ADMUX |= (0 & 0x07);    // set A0 analog input pin
  ADMUX |= (1 << REFS0);  // set reference voltage

  ADCSRA |= (1 << ADPS2);                     // 16 prescaler for 76.9 KHz

  ADCSRA |= (1 << ADEN);  // enable ADC
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.write(120); // "x": (ASCII Table: 120) http://www.asciitable.com/

  delayMicroseconds(1);

  for (int i = 0; i < 64; i++) {
    f_adc0_tmp = adc0[i][buff_index];

    f_adc0_tmp /= 1.5;

    adc0_tmp = f_adc0_tmp;

    val_tmp = adc0_tmp;

    val_100 = val_tmp / 100;
    val_tmp -= val_100 * 100;

    val_10 = val_tmp / 10;
    val_tmp -= val_10 * 10;

    val_100 += 48;
    val_10 += 48;
    val_1 = val_tmp + 48;

    if (adc0_tmp > 99) {
      Serial.write(val_100);
    }

    if (adc0_tmp > 9) {
      Serial.write(val_10);
    }

    Serial.write(val_1);

    Serial.write(59); // ";": 59
  }

  f_adc0_tmp = adc0[64][buff_index];

  f_adc0_tmp /= 1.5;

  adc0_tmp = f_adc0_tmp;

  val_tmp = adc0_tmp;

  val_100 = val_tmp / 100;
  val_tmp -= val_100 * 100;

  val_10 = val_tmp / 10;
  val_tmp -= val_10 * 10;

  val_100 += 48;
  val_10 += 48;
  val_1 = val_tmp + 48;

  if (adc0_tmp > 99) {
    Serial.write(val_100);
  }

  if (adc0_tmp > 9) {
    Serial.write(val_10);
  }

  Serial.write(val_1);

  Serial.write(121); // "y": 121

  for (int i = 0; i < 64; i++) {
    f_adc1_tmp = adc1[i][buff_index];

    f_adc1_tmp /= 1.5;

    adc1_tmp = f_adc1_tmp;

    val_tmp = adc1_tmp;

    val_100 = val_tmp / 100;
    val_tmp -= val_100 * 100;

    val_10 = val_tmp / 10;
    val_tmp -= val_10 * 10;

    val_100 += 48;
    val_10 += 48;
    val_1 = val_tmp + 48;

    if (adc1_tmp > 99) {
      Serial.write(val_100);
    }

    if (adc1_tmp > 9) {
      Serial.write(val_10);
    }

    Serial.write(val_1);

    Serial.write(59); // ";": 59
  }

  f_adc1_tmp = adc1[64][buff_index];

  f_adc1_tmp /= 1.5;

  adc1_tmp = f_adc1_tmp;

  val_tmp = adc1_tmp;

  val_100 = val_tmp / 100;
  val_tmp -= val_100 * 100;

  val_10 = val_tmp / 10;
  val_tmp -= val_10 * 10;

  val_100 += 48;
  val_10 += 48;
  val_1 = val_tmp + 48;

  if (adc1_tmp > 99) {
    Serial.write(val_100);
  }

  if (adc1_tmp > 9) {
    Serial.write(val_10);
  }

  Serial.write(val_1);

  Serial.write(122); // "z": 122

  for (int i = 0; i < 64; i++) {
    f_adc2_tmp = adc2[i][buff_index];

    f_adc2_tmp /= 1.5;

    adc2_tmp = f_adc2_tmp;

    val_tmp = adc2_tmp;

    val_100 = val_tmp / 100;
    val_tmp -= val_100 * 100;

    val_10 = val_tmp / 10;
    val_tmp -= val_10 * 10;

    val_100 += 48;
    val_10 += 48;
    val_1 = val_tmp + 48;

    if (adc2_tmp > 99) {
      Serial.write(val_100);
    }

    if (adc2_tmp > 9) {
      Serial.write(val_10);
    }

    Serial.write(val_1);

    Serial.write(59); // ";": 59
  }

  f_adc2_tmp = adc2[64][buff_index];

  f_adc2_tmp /= 1.5;

  adc2_tmp = f_adc2_tmp;

  val_tmp = adc2_tmp;

  val_100 = val_tmp / 100;
  val_tmp -= val_100 * 100;

  val_10 = val_tmp / 10;
  val_tmp -= val_10 * 10;

  val_100 += 48;
  val_10 += 48;
  val_1 = val_tmp + 48;

  if (adc2_tmp > 99) {
    Serial.write(val_100);
  }

  if (adc2_tmp > 9) {
    Serial.write(val_10);
  }

  Serial.write(val_1);

  Serial.write(35); // "#": 35

  buff_status[buff_index] = 1;

  if (buff_index == 0) {
    buff_index = 1;

    //https://roboticsbackend.com/arduino-fast-digitalwrite/
    PORTD = PORTD | B00001000; // led HIGH
  } else {
    buff_index = 0;

    PORTD = PORTD & B11110111; // led LOW
  }

  //  delayMicroseconds(2000);
}

void tmr1_int() {
  int val_tmp = 129; // mid_point

  if (i < 65) {
    f_adc0_tmp = analogRead(A0);
    f_adc1_tmp = analogRead(A1);
    f_adc2_tmp = analogRead(A2);

    if (buff_status[0] == 2) {
      adc0[i][0] = f_adc0_tmp + adc0[i][0];
      adc0[i][0] /= 2.0;

      adc1[i][0] = f_adc1_tmp + adc1[i][0];
      adc1[i][0] /= 2.0;

      adc2[i][0] = f_adc2_tmp + adc2[i][0];
      adc2[i][0] /= 2.0;
    } else if (buff_status[1] == 2) {
      adc0[i][1] = f_adc0_tmp + adc0[i][1];
      adc0[i][1] /= 2.0;

      adc1[i][1] = f_adc1_tmp + adc1[i][1];
      adc1[i][1] /= 2.0;

      adc2[i][1] = f_adc2_tmp + adc2[i][1];
      adc2[i][1] /= 2.0;
    }
  } else {
    if (buff_status[1] == 2) {
      buff_status[1] = 3;
    } else if (buff_status[0] == 2) {
      buff_status[0] = 3;
    }
  }

  if (i < 65) {
    val_tmp = wave[i] + offset;
  }

  if (val_tmp & 1) {
    PORTB = PORTB | B00000001;
  } else {
    PORTB = PORTB & B11111110;
  }

  if ((val_tmp >> 1) & 1) {
    PORTB = PORTB | B00000010;
  } else {
    PORTB = PORTB & B11111101;
  }

  if ((val_tmp >> 2) & 1) {
    PORTB = PORTB | B00000100;
  } else {
    PORTB = PORTB & B11111011;
  }

  if ((val_tmp >> 3) & 1) {
    PORTB = PORTB | B00001000;
  } else {
    PORTB = PORTB & B11110111;
  }

  if ((val_tmp >> 4) & 1) {
    PORTB = PORTB | B00010000;
  } else {
    PORTB = PORTB & B11101111;
  }

  if ((val_tmp >> 5) & 1) {
    PORTB = PORTB | B00100000;
  } else {
    PORTB = PORTB & B11011111;
  }

  if ((val_tmp >> 6) & 1) {
    PORTD = PORTD | B10000000;
  } else {
    PORTD = PORTD & B01111111;
  }

  if ((val_tmp >> 7) & 1) {
    PORTD = PORTD | B01000000;
  } else {
    PORTD = PORTD & B10111111;
  }

  PORTD = PORTD & B11011111;

  PORTD = PORTD | B00100000;

  if (i < 390) {
    i++;
  } else {
    i = 0;

    if (buff_status[1] == 1) {
      buff_status[1] = 2;
    } else if (buff_status[0] == 1) {
      buff_status[0] = 2;
    }
  }
}
