// Define pin connections
const int stepPin = 3;    // STEP pin of driver (PUL+)
const int dirPin = 4;     // DIR pin of driver (DIR+)
const int enablePin = 5;  // ENABLE pin of driver (ENA+)

// Motor parameters
const int stepsPerRevolution = 1600;  // 1.8° per step (NEMA 34 standard)
const int microsteps = 4;            // Driver microstepping setting (800 pulses/rev)
const long totalSteps = stepsPerRevolution * microsteps;  // Total steps per revolution considering microstepping

// Speed control
float desiredRPM = 30.0;  // Start at a lower RPM to avoid stalling
float currentRPM = 0.0;   // Current RPM for acceleration
unsigned long stepDelay;  // Delay between steps in microseconds
bool isRunning = true;    // Motor running state
bool isSimulating = false;  // Flag to indicate if simulation is active

void setup() {
  // Initialize pins
  pinMode(stepPin, OUTPUT);  // Set STEP pin as output
  pinMode(dirPin, OUTPUT);   // Set DIR pin as output
  pinMode(enablePin, OUTPUT);  // Set ENABLE pin as output
  
  // Set initial states
  digitalWrite(enablePin, HIGH);  // Disable driver initially (ACTIVE LOW)
  digitalWrite(stepPin, LOW);     // Ensure STEP is LOW initially
  digitalWrite(dirPin, LOW);     // Initial direction: ounter-clockwise
  
  // Start serial communication
  Serial.begin(9600);
  Serial.println("OK2D872 Stepper Motor Control");
  Serial.println("Available Commands:");
  Serial.println("RPM <value> - Set RPM");
  Serial.println("CW - Clockwise direction");
  Serial.println("CCW - Counter-Clockwise direction");
  Serial.println("STOP - Stop motor");
  Serial.println("START - Start motor");
  Serial.println("SIM - Enable simulation mode (no motor control)");

  // Calculate initial step delay
  calculateStepDelayForRPM(desiredRPM);  // Fixed: Use the correct function name
  currentRPM = desiredRPM;  // Start at desired RPM
  digitalWrite(enablePin, LOW);  // Enable driver
}

void loop() {
  static unsigned long lastStepTime = 0;
  static unsigned long lastAccelTime = 0;
  const unsigned long accelInterval = 10;  // Update acceleration every 10ms
  
  // Check for serial input from HMI (Human Machine Interface)
  if (Serial.available() > 0) {
    String command = Serial.readStringUntil('\n');  // Read incoming command
    command.trim();  // Trim any extra spaces or newlines
    
    if (command.startsWith("RPM")) {  // Check if the command starts with "RPM"
      float newRPM = command.substring(4).toFloat();  // Extract the RPM value
      if (newRPM > 0 && newRPM <= 600) {  // Check if RPM is within valid range
        desiredRPM = newRPM;
        Serial.println("Target RPM: " + String(desiredRPM));
      } else {
        Serial.println("RPM out of range (1-600)");
      }
    } else if (command == "CW") {  // If command is "CW", set motor direction to clockwise
      digitalWrite(dirPin, HIGH);
      Serial.println("Direction: Clockwise");
    } else if (command == "CCW") {  // If command is "CCW", set motor direction to counterclockwise
      digitalWrite(dirPin, LOW);
      Serial.println("Direction: Counterclockwise");
    } else if (command == "STOP") {  // If command is "STOP", stop the motor
      isRunning = false;
      digitalWrite(enablePin, HIGH);  // Disable the motor driver
      Serial.println("Motor stopped");
    } else if (command == "START") {  // If command is "START", start the motor
      isRunning = true;
      digitalWrite(enablePin, LOW);  // Enable the motor driver
      Serial.println("Motor started");
    } else if (command == "SIM") {  // If command is "SIM", enable simulation mode
      isSimulating = !isSimulating;
      if (isSimulating) {
        Serial.println("Simulation mode enabled. No motor control.");
      } else {
        Serial.println("Simulation mode disabled.");
      }
    } else {
      Serial.println("Unknown command: " + command);  // Handle unknown commands
    }
  }
  
  // Accelerate/decelerate to desired RPM
  if (isRunning && !isSimulating) {  // Only control motor if running and not in simulation mode
    unsigned long currentTime = micros();
    
    // Update acceleration every accelInterval (10ms)
    if (currentTime - lastAccelTime >= accelInterval * 1000) {
      if (currentRPM < desiredRPM) {
        currentRPM += 0.5;  // Increase RPM by 0.5 per 10ms (adjust for smoothness)
        if (currentRPM > desiredRPM) currentRPM = desiredRPM;
        calculateStepDelayForRPM(currentRPM);
      } else if (currentRPM > desiredRPM) {
        currentRPM -= 0.5;  // Decrease RPM by 0.5 per 10ms
        if (currentRPM < desiredRPM) currentRPM = desiredRPM;
        calculateStepDelayForRPM(currentRPM);
      }
      lastAccelTime = currentTime;
    }
    
    // Step the motor at the calculated delay
    if (currentTime - lastStepTime >= stepDelay) {
      digitalWrite(stepPin, HIGH);
      delayMicroseconds(5);  // 5 µs pulse width for OK2D872
      digitalWrite(stepPin, LOW);
      lastStepTime = currentTime;
    }
  } else if (isSimulating) {  // If simulation mode is active, simulate motor behavior
    simulateMotorBehavior();  // Call the function to simulate motor behavior
  }
}

// Calculate the step delay for the desired RPM
void calculateStepDelayForRPM(float rpm) {
  if (rpm <= 0) rpm = 1;  // Prevent division by zero
  float timePerRevolution = 60000000.0 / rpm;  // µs per revolution
  stepDelay = (unsigned long)(timePerRevolution / totalSteps);  // Calculate step delay in microseconds
  if (stepDelay < 10) stepDelay = 10;  // Minimum 10 µs total period (5 µs HIGH + 5 µs LOW)
  Serial.println("Current RPM: " + String(rpm) + ", Step Delay: " + String(stepDelay) + " µs");
}

// Simulate motor behavior when in simulation mode
void simulateMotorBehavior() {
  Serial.println("Simulating motor behavior...");
  Serial.print("Simulated RPM: ");
  Serial.println(desiredRPM);
  Serial.print("Simulated Direction: ");
  if (digitalRead(dirPin) == HIGH) {
    Serial.println("Clockwise");
  } else {
    Serial.println("Counterclockwise");
  }
  // Simulate the RPM change and direction by printing
  delay(1000);  // Simulate a pause between updates
}
