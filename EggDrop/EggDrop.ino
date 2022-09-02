//Based heavily on the plotter example in the MPU6050 Library



#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

Adafruit_MPU6050 mpu;
//unsigned long time;

void setup(void) {
  Serial.begin(115200);
  while (!Serial) {
    delay(10); // will pause Zero, Leonardo, etc until serial console opens
  }

  // Try to initialize!
  if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip");
    while (1) {
      delay(10);
    }
  }

  mpu.setAccelerometerRange(MPU6050_RANGE_16_G);
  mpu.setGyroRange(MPU6050_RANGE_250_DEG);
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);
  Serial.println("Time,X,Y,Z");
  delay(100);
}

void loop() {

  /* Get new sensor events with the readings */
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);
  //time = millis();

  /* Print out the values */
  //Serial.print(millis());
  //Serial.print("AccelX:");
  //Serial.print(a.acceleration.x);
  //Serial.print(",");
  //Serial.print("AccelY:");
  //Serial.print(a.acceleration.y);
  //Serial.print(",");
  //Serial.print("AccelZ:");
  //Serial.print(a.acceleration.z);
  //Serial.print(",");
  Serial.print("GForce:");
  Serial.print((sqrt(sq(a.acceleration.x) + sq(a.acceleration.y) + sq(a.acceleration.z)))/9.8);
  Serial.println("");

  delay(10);
}
