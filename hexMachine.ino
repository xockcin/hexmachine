// This program takes a combination of four different buttons as an input, and returns the corresponding hex digit as an output.
// 
// This program illustrates two signature features of the C programming language: indexed arrays and bit shifting. 
// 
// Let's go over what happens in the program. We begin by declaring three arrays. The first and second are both arrays of pins,
// representing, respectively, the four input pins connected to the four buttons and the seven output pins connected to the pins
// of the seven-segment display. The third array contains sixteen hexadecimal numbers, each of which represents the configuration
// of seven-segment lights needed to light up in order to display the corresponding hexadecimal digit.
//
// The setup function is just a matter of initializing the pins with a couple of for loops.
// 
// The loop function begins by initializing "number" to zero. That is current input number, which the user enters using the four
// buttons.
//
// Then comes the interesting part. First, we take the combination of buttons that the user is pressing and turn it into a number.
// Let's take a closer look at that first for loop. Notice, first, how it echoes the first loop of the setup function. Once again
// we are looping through the input pins. For each number zero through three, if the corresponding pin is high, we increment the
// variable "number" by 1<<i, which is another way of saying 2^i.
// 
// Finally, we actually display the digit by looping once more through the seven output pins. This loop uses a classic bitmask.
// Let's look closer at the conditional: "if (digits[number] & 1<<i)." That is &, single ampersand, which is the bitwise AND
// operator. The array "digits[16]" might be a little confusing at first. It contains 16 numbers, indexed from 0 to 15. Bear in
// mind that a seven-segment display, true to its name, has seven LED's, one for each of its segments. The numbers contained in
// the digits array are numeric representations of the configurations of LEDs that are to be lit to display each of the 16 digits.
// The seven lights of a seven-segment display can be thought of as seven "bits," each of which is either on or off. Therefore,
// each digit can be represented as a seven-bit number, i.e. a number between 0 and 7F. You will notice that the number 0x7F is
// indeed present in our array, representing the number 8.
//
// There are 128 possible seven-segment display configurations. Most of them don't look like anything. 
// 
// So, to return to that conditional. The variable "number" is the number that we are entering using the buttons; "digits[number]"
// is the seven-segment representation of that number. The for loop increments i from zero to seven and, for each i, asks in effect
// if the ith bit of digits[number] is zero or one. If it is one, the ith element in the "light" array, and accordingly the ith
// segment of the display, turns on.
//
// This is a very simple program. In the future, I would like to implement several changes to it. First, I would like to change it
// so that, instead of controlling the bits directly, the buttons manipulate them with bit operators like shift and complement.
// Second, I would like to add a second set of four LEDs and a second seven-segment, so the machine displays a whole byte instead
// of just half of one. I would accomplish this last by connecting the Arduino with the inputs and outputs via three shift register
// chips instead of directly.

int buttons[4] = {A3,A2,A1,A0};
int light[7] = {3,4,5,6,7,8,9};
int digits[16] = {0x3F, 0x09, 0x5E, 0x5B, 0x69, 0x73, 0x77, 0x19, 0x7F, 0x7B, 0x7D, 0x67, 0x36, 0x4F, 0x76, 0x74};

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
   int state = digitalRead(buttons[i]);
    if (state == HIGH) {
      number += 1<<i;
    }
  }
  
  // display digit
  for (int i=0;i<7;i++) {
    if (digits[number] & 1<<i) {
      digitalWrite(light[i], HIGH);
    }
    else {
      digitalWrite(light[i], LOW);
    }
  }
}
