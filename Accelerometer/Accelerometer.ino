#include <ADXL345.h>

ADXL345 accelerometer;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  Serial.println("Initializing the accelerometer...");

  if(!accelerometer.begin()) {
    Serial.println("Could not find a valid ADXL345 sensor, check wiring!");
    return;
  }

   // Set tap detection on Z-Axis
  accelerometer.setTapDetectionX(0);       // Don't check tap on X-Axis
  accelerometer.setTapDetectionY(0);       // Don't check tap on Y-Axis
  accelerometer.setTapDetectionZ(1);       // Check tap on Z-Axis
  // or
  // accelerometer.setTapDetectionXYZ(1);  // Check tap on X,Y,Z-Axis

  accelerometer.setTapThreshold(2.5);      // Recommended 2.5 g
  accelerometer.setTapDuration(0.02);      // Recommended 0.02 s
  accelerometer.setDoubleTapLatency(0.10); // Recommended 0.10 s
  accelerometer.setDoubleTapWindow(0.30);  // Recommended 0.30 s

  accelerometer.setActivityThreshold(2.0);    // Recommended 2 g
  accelerometer.setInactivityThreshold(2.0);  // Recommended 2 g
  accelerometer.setTimeInactivity(5);         // Recommended 5 s

  // Set activity detection only on X,Y,Z-Axis
  accelerometer.setActivityXYZ(1);         // Check activity on X,Y,Z-Axis

  // Set inactivity detection only on X,Y,Z-Axis
  accelerometer.setInactivityXYZ(1);       // Check inactivity on X,Y,Z-Axis

  // Select INT 1 for get activities
  accelerometer.useInterrupt(ADXL345_INT1);

  // Check settings
  checkSetup();
}

void checkSetup()
{
  Serial.print("Activity Threshold = "); Serial.println(accelerometer.getActivityThreshold());
  Serial.print("Inactivity Threshold = "); Serial.println(accelerometer.getInactivityThreshold());
  Serial.print("Time Inactivity = "); Serial.println(accelerometer.getTimeInactivity());

  Serial.print("Look activity on axis = "); 
  if (accelerometer.getActivityX()) { Serial.print(" X "); }
  if (accelerometer.getActivityY()) { Serial.print(" Y "); }
  if (accelerometer.getActivityZ()) { Serial.print(" Z "); }
  Serial.println();

  Serial.print("Look inactivity on axis = "); 
  if (accelerometer.getInactivityX()) { Serial.print(" X "); }
  if (accelerometer.getInactivityY()) { Serial.print(" Y "); }
  if (accelerometer.getInactivityZ()) { Serial.print(" Z "); }
  Serial.println();  
  
  Serial.print("Look tap on axis = "); 
  if (accelerometer.getTapDetectionX()) { Serial.print(" X "); }
  if (accelerometer.getTapDetectionY()) { Serial.print(" Y "); }
  if (accelerometer.getTapDetectionZ()) { Serial.print(" Z "); }
  Serial.println();

  Serial.print("Tap Threshold = "); Serial.println(accelerometer.getTapThreshold());
  Serial.print("Tap Duration = "); Serial.println(accelerometer.getTapDuration());
  Serial.print("Double Tap Latency = "); Serial.println(accelerometer.getDoubleTapLatency());
  Serial.print("Double Tap Window = "); Serial.println(accelerometer.getDoubleTapWindow());
  Serial.println();
  Serial.println("------------------------");
  Serial.println();
}

void loop() {
  // put your main code here, to run repeatedly:
  Vector norm = accelerometer.readNormalize();

  // Output normalized m/s^2
  Serial.println(" Xnorm = ");
  Serial.println(norm.XAxis);
  Serial.println(" Ynorm = ");
  Serial.println(norm.YAxis);
  Serial.println(" Znorm = ");
  Serial.println(norm.ZAxis);

  delay(4000);

  // Read activities
  Activites activities = accelerometer.readActivites();

//  if (activities.isActivity)
//  {
//    Serial.println("Activity Detected");
//  }
//
//  if (activities.isInactivity)
//  {
//    Serial.println("Inactivity Detected");
//  }
  
  if (activities.isDoubleTap)
  {
    Serial.println("Double Tap Detected");
  } else
  if (activities.isTap)
  {
    Serial.println("Tap Detected");
  }
}
