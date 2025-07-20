# Rebel
This is the car

# Example Use-Case Journeys

## 1. Remote "Steer Left" Signal → Car Turns Left

**A. Hardware Layer**  
Physical event: RC receiver gets "steer left" signal (e.g., PWM pulse, GPIO interrupt).

**B. Board-Specific HW Layer**  
Interrupt handler (e.g., EXTI, timer, or DMA) detects the signal.  
Calls a callback or notifies the application via an interface (e.g., `IInputListener::onSteerLeft()`).

**C. Application Layer**  
Receives the event via the interface.  
Decides: "Should I turn left now?" (could check for safety, ignore, or override).  
If yes, calls `steeringMotor.setAngle(-30)` (using the abstract interface).

**D. Board-Specific HW Layer**  
The `steeringMotor` implementation translates the angle to a PWM value, sends it to the PCA9685 over I2C, which drives the L298, which moves the steering motor.

**E. Hardware**  
The car physically turns left.

---

## 2. Remote "Throttle" Signal → Car Moves Forward

**A. Hardware Layer**  
RC receiver gets "throttle" signal.

**B. Board-Specific HW Layer**  
Interrupt or polling detects the signal.  
Notifies application via interface (e.g., `IInputListener::onThrottle(value)`).

**C. Application Layer**  
Decides: "Is it safe to move forward?" (could check for obstacles, battery, etc.)  
If yes, calls `engineMotor.setSpeed(value)`.

**D. Board-Specific HW Layer**  
`engineMotor` implementation sends the command to the motor driver.

**E. Hardware**  
Car moves forward.

---

## 3. No Input Signal (Failsafe or AutoDrive)

**A. Hardware Layer**  
No input detected (e.g., lost RC signal).

**B. Board-Specific HW Layer**  
Notifies application: "No input" or "Signal lost".

**C. Application Layer**  
Decides: "Should I stop, keep going, or enter autonomous mode?"  
Could call `engineMotor.stop()` or start an autonomous routine.

**D. Board-Specific HW Layer**  
Executes the command.

**E. Hardware**  
Car stops or continues as decided.

# Build
Build system requires [Make](http://www.gnu.org/software/make) and [CMake](https://cmake.org). Install them and run:
```shell
make
```