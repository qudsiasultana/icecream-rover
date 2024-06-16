// ===== Initialized variables here =====
// integer variable for on and off state of the rover, we initially want it off
// [code here]
int onOff = 0;

// interger for the on and off state of the button, we initially want it off
// [code here]
int buttonState = 0;

// The rover is sending out a signal, create a more complex integer "duration" for the time it takes for the sound to return to Echo    
// [code here]
long duration;

// The rover is detecting an object, create a more complex integer "distance" for the distance of that object
// [code here]
long distance;


// ===== Variables for connecting the Arduino to the sensors (Ulstrasonic sensor + 2 DC motors) =====
// integer for pin position for Trig (Trigger), the pin that's transmitting a sonar pulse to the environment  
// [code here]
int trigPin = 9;

// integer for the pin position of Echo, the pin that's reading the returning pulse that bounced off an object   
// [code here]
int echoPin = 10;

// integer for the motor on the right
// [code here]
int motorPinR = 5;

// integer for the motor on the left
// [code here]
int motorPinL = 6;

// integer for the pushbutton
int buttonPin = 2;


//=======================================================================
void setup() {
  // ===== Put your setup code here. This code runs once =====
  // Set pinMode() as OUTPUT for your Trig variable to emit a sound
  // [code here]
  pinMode(trigPin, OUTPUT);
  
  // Set pinMode() as INPUT for Echo to receive reflected sound
  // [code here]
  pinMode(echoPin, INPUT);

  // Set pinMode() as OUTPUT for motor on the right
  // [code here]
  pinMode(motorPinR, OUTPUT);

  // Set pinMode() as OUTPUT for motor on the left
  // [code here]
  pinMode(motorPinL, OUTPUT);

  // Set pinMode() as INPUT for the button pin
  // [code here]
  pinMode(buttonPin, INPUT);

  // Start serial communication at 9600 bps 
  // [code here]
  Serial.begin(9600); // Starts the serial communication

}


//=======================================================================
void loop() {
  // ===== put your main code here, to run repeatedly =====
  // variable used for the on and off state of the button = read the button pin 
  // [code here] - Reads the current state of the button
  buttonState = digitalRead (buttonPin); 

  // if (button state is pressed == HIGH)
  // [code here] 
  if (buttonState == HIGH) 
  {
    // the rover state is 1 - indicates it's pressed
    onOff = 1; 
    delay(1000) ; // one second delay
  }

  
  // while (button state is == one)
  // [code here]
  while (onOff == 1)
  {
    // turn on left motor, set to full speed of 225
    // [code here]
    analogWrite(motorPinL, 255); 
    
    // turn on right motor, set to full speed of 225
    // [code here]
    analogWrite(motorPinR, 255); 


    // clear the Trig output to allow for a new sound to emit 
    // [code here]
    digitalWrite(trigPin, LOW); 
    // set a delay of 2 microseconds for good measure
    // [code here]
    delayMicroseconds (2);
    // Output sound from Trig + small delay
    // [code here]
    digitalWrite(trigPin, HIGH);
    // [code here]
    delayMicroseconds (10);
    // clear Trig again to stop sound 
    // [code here]
    digitalWrite(trigPin, LOW);

    // read a pulse and store the Echo value inside of duration
    // [code here]
    duration = pulseIn(echoPin, HIGH);

    // calculate distance of the object
    // [code here] //Distance in cm
    distance = duration * 0.034 / 2; 

    // ==== turn the car if an obstacle is detected ====
    // if (distance is less than 60cm)
    if (distance < 60) 
    { 
      // stop both motors
      // [code here for left motor]
      // [code here for right motor]
      analogWrite(motorPinL, 0); //Turn off left motor
      analogWrite(motorPinR, 0); //Turn off right motor

      // ===== turn the rover =====
      // short delay
      // [code here]
      delay(500);
      // turn on the right motor, set to full speed 
      // [code here]
      analogWrite (motorPinR, 255);
      //short delay
      // [code here]
      delay(700); 
      // turn off the right motor
      // [code here]
      analogWrite(motorPinR, 0); 
      //short delay
      // [code here]
      delay(500) ; 
    }

    // read the current state of the button again to wait again for the user to press the button   
    // [code here] 
    buttonState = digitalRead (buttonPin); 

    // if (button state is pressed == HIGH)
    // [code here]
    if (buttonState == HIGH) 
    {
      // stop both motors
      // [code here for left motor]
      // [code here for right motor]
      analogWrite (motorPinR, 0); 
      analogWrite (motorPinL, 0); 

      // rover state is off
      // [code here]
      onOff = 0; 
      delay (1000) ; // One second delay
    }
  
  // print distance values in our serial monitor 
  // [code here]
  // [code here]
  Serial.print("Distance: ");
  Serial.println(distance);
  
  delay(50);  // wait milliseconds

  }
}
