// this program takes a combination of four different buttons as an input, and outputs the corresponding hex digit as an output.
// the most sensible way to build this would be with a shift register chip. next time, I suppose.

int buttons[4] = {A3,A2,A1,A0};
int light[7] = {3,4,5,6,7,8,9};
int digits[16] = {0x3F, 0x9, 0x5E, 0x5B, 0x69, 0x73, 0x77, 0x19, 0x7F, 0x7B, 0x7D, 0x67, 0x36, 0x4F, 0x76, 0x74};
int state = 0;

void setup() {
  
  for (int i=0;i<4;i++) {
    pinMode(buttons[i], INPUT);
  }
  for (int i=0;i<7;i++) {
    pinMode(light[i], OUTPUT);
  }
}
  
void loop() {
  
  //initialize number to zero
  int number = 0;
  
  //read buttons
  for (int i=0;i<4;i++) {
    state = digitalRead(buttons[i]);
    if (state == HIGH) {
      number += 1<<i;
    }
  }
  
  for (int i=0;i<7;i++) {
    if (digits[number] & 1<<i) {
      digitalWrite(light[i], HIGH);
    }
    else {
      digitalWrite(light[i], LOW);
    }
  }
}
