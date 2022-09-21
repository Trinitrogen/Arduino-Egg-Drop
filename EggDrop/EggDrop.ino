//Based heavily on the plotter example in the MPU6050 Library

#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>

Adafruit_MPU6050 mpu;
unsigned long interval=1000;
unsigned long previousMillis=0;
unsigned long samples = 0;

const int MPU_addr = 0x68; // I2C address of the MPU-6050
float AcX, AcY, AcZ;

File outputFile;

void sdcardsetup(void){
 
  //Initialize SD Card
  Serial.print("Initializing SD Card ");
  if (!SD.begin(4)) {
    Serial.println(" failed!");
    while (1) {
      Serial.println(" failed!");
      delay(10);
    }
    //return;
  }
  else {
    Serial.println(" complete");
  }

// Check if old output.csv exists, and delete it:
  if (SD.exists("output.csv")) {
    Serial.println("Deleting Old Output.csv");
     SD.remove("example.txt");
  } 
  else {
    Serial.println("output.csv doesn't exist.");
  }

  //Open output.csv
  Serial.println("Creating output.csv");
  outputFile = SD.open("output.csv", FILE_WRITE);
  outputFile.println("Time,X,Y,Z");
  outputFile.close();
  
}

void setup(void) {
  Serial.begin(115200);

  // Try to Initialize MPU Accelerometer
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


  //Setup SD Card
  //sdcardsetup();
}

void adafruit(bool debug){
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  /* Print out the values */
  Serial.print("AccelX:");
  Serial.print(a.acceleration.x);
  Serial.print(",");
  Serial.print("AccelY:");
  Serial.print(a.acceleration.y);
  Serial.print(",");
  Serial.print("AccelZ:");
  Serial.print(a.acceleration.z);
  Serial.println("");

}

void mpu6050(bool output){

/*
 * Faster way to read the accelerometer, but going to require some work
 * Will come back and use it once I am further along
 * 
 * 
 * * AFS_SEL | Full Scale Range | LSB Sensitivity
* ——–+——————+—————-
* 0 | +/- 2g | 8192 LSB/mg
* 1 | +/- 4g | 4096 LSB/mg
* 2 | +/- 8g | 2048 LSB/mg
* 3 | +/- 16g | 1024 LSB/mg
 */

  int lsb = 2048;
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x3B);  // starting with register 0x3B (ACCEL_XOUT_H)
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_addr, 14, true); // request a total of 14 registers
  AcX = Wire.read() << 8 | Wire.read(); // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)
  AcY = Wire.read() << 8 | Wire.read(); // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
  AcZ = Wire.read() << 8 | Wire.read(); // 0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)

  Serial.print(AcX/lsb);
  Serial.print(","); Serial.print(AcY/lsb); 
  Serial.print(","); Serial.println(AcZ/lsb);
}

void loop() {

  //Used for measuring how many samples happen in a given time
  //To be used to find optimizations
  unsigned long currentMillis = millis();
    if ((unsigned long)(currentMillis - previousMillis) >= interval) {
      Serial.print(samples);
      Serial.println("Samples");
      // save the "current" time
      previousMillis = millis();
      samples = 0;
    }
    
 adafruit(true);

  
 samples++;
}
