//Based heavily on the plotter example in the MPU6050 Library
/*
 * * AFS_SEL | Full Scale Range | LSB Sensitivity
* ——–+——————+—————-
* 0 | +/- 2g | 8192 LSB/mg
* 1 | +/- 4g | 4096 LSB/mg
* 2 | +/- 8g | 2048 LSB/mg
* 3 | +/- 16g | 1024 LSB/mg
 */


#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

Adafruit_MPU6050 mpu;
unsigned long interval=1000;
unsigned long previousMillis=0;
unsigned long samples = 0;

const int MPU_addr = 0x68; // I2C address of the MPU-6050
//int16_t AcX, AcY, AcZ;
float AcX, AcY, AcZ;

void setup(void) {
  Serial.begin(115200);
  //while (!Serial) {
  //  delay(10); // will pause Zero, Leonardo, etc until serial console opens
  //}

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
  unsigned long currentMillis = millis();
  samples++;

    if ((unsigned long)(currentMillis - previousMillis) >= interval) {
      Serial.print(samples);
      Serial.println("Samples");
      // save the "current" time
      previousMillis = millis();
      samples = 0;
    }

  /* Print out the values */
 /*
  //Serial.print(millis());
  Serial.print("AccelX:");
  Serial.print(a.acceleration.x);
  Serial.print(",");
  Serial.print("AccelY:");
  Serial.print(a.acceleration.y);
  Serial.print(",");
  Serial.print("AccelZ:");
  Serial.print(a.acceleration.z);
  //Serial.print(",");
  //Serial.print("GForce:");
  //Serial.print((sqrt(sq(a.acceleration.x) + sq(a.acceleration.y) + sq(a.acceleration.z)))/9.8);
  Serial.println("");
*/
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x3B);  // starting with register 0x3B (ACCEL_XOUT_H)
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_addr, 14, true); // request a total of 14 registers
  AcX = Wire.read() << 8 | Wire.read(); // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)
  AcY = Wire.read() << 8 | Wire.read(); // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
  AcZ = Wire.read() << 8 | Wire.read(); // 0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)

  Serial.print(AcX/1024);
  Serial.print(","); Serial.print(AcY/1024);
  Serial.print(","); Serial.println(AcZ/1024);

}
