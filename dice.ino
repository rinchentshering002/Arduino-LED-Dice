// Dynamic Innovator
// Set to 1 if we're debugging
#define DEBUG 1

// 6 consecutive digital pins for the LEDs
int first = 2;
int second = 3;
int third = 4;
int fourth = 5;
int fifth = 6;
int sixth = 7;

// Pin for the button switch
int button = 12;
// Value to check state of button switch
int pressed = 0;

void setup() {
    // Set all LED pins to OUTPUT
    for (int i = first; i <= sixth; i++) {
        pinMode(i, OUTPUT);
    }
    // Set button pin to INPUT with pull-up resistor
    pinMode(button, INPUT_PULLUP);
    
    // Initialize random seed by noise from analog pin 0 (should be unconnected)
    randomSeed(analogRead(0));

    // If we're debugging, connect to serial
    #if DEBUG
        Serial.begin(9600);
    #endif
}

void buildUpTension() {
    // Light LEDs from left to right and back to build up tension
    // Left to right
    for (int i = first; i <= sixth; i++) {
        if (i != first) {
            digitalWrite(i - 1, LOW);
        }
        digitalWrite(i, HIGH);
        delay(100);
    }
    // Right to left
    for (int i = sixth; i >= first; i--) {
        if (i != sixth) {
            digitalWrite(i + 1, LOW);
        }
        digitalWrite(i, HIGH);
        delay(100);
    }
}

void showNumber(int number) {
    digitalWrite(first, HIGH);
    if (number >= 2) digitalWrite(second, HIGH);
    if (number >= 3) digitalWrite(third, HIGH);
    if (number >= 4) digitalWrite(fourth, HIGH);
    if (number >= 5) digitalWrite(fifth, HIGH);
    if (number == 6) digitalWrite(sixth, HIGH);
}

int throwDice() {
    // Get a random number in the range [1,6]
    int randNumber = random(1, 7);
    
    #if DEBUG
        Serial.println(randNumber);
    #endif
    
    return randNumber;
}

void setAllLEDs(int value) {
    for (int i = first; i <= sixth; i++) {
        digitalWrite(i, value);
    }
}

void loop() {
    // If button is pressed - throw the dice
    pressed = digitalRead(button);

    if (pressed == LOW) {  // Button is pressed when LOW
        // Remove previous number
        setAllLEDs(LOW);
        
        buildUpTension();
        int thrownNumber = throwDice();
        showNumber(thrownNumber);
    }
}
