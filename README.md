# Arduino-Egg-Drop

## Parts
- Arduino Uno
- [MPU-6050 Accelerometer](https://www.amazon.com/HiLetgo-MPU-6050-Accelerometer-Gyroscope-Converter/dp/B00LP25V1A/ref=asc_df_B00LP25V1A/?tag=hyprod-20&linkCode=df0&hvadid=247487538123&hvpos=&hvnetw=g&hvrand=13980694724921975743&hvpone=&hvptwo=&hvqmt=&hvdev=c&hvdvcmdl=&hvlocint=&hvlocphy=9021760&hvtargid=pla-407209664611&psc=1)
- [MicroSD Breakout Board](https://www.adafruit.com/product/254)

## MicroSD Wiring

- Arduino Pin 13 <-> CLK
- Arduino Pin 12 <-> DO
- Arduino Pin 13 <-> DI
- Arduino Pin 4 <-> CS
- Connect to 5V and GND


## Accelerometer Wiring
- Arduino Pin 5 <-> SCL
- Arduino Pin 4 <-> SDA
- Arduino 3V <-> VCC
- Arduino GND <-> GND


Attempt to create a modern version of the Egg Drop experiment. Originally I planned to use a NodeMCU for a smaller footprint but ran into issues with having both the the accelerometer and MicroSD running at the same time.

Once powered on, the arduino will create a new output.csv (deleting any previous version) and store the X, Y, and Z data. Perform the experiment, remove power, and remove the memory card.

Load the csv into your spreadsheet application for analysis. To convert to G's, divide each by 9.8. To measure magnitude of impact, you can calculate the square root of (X^2+Y^2+Z^2)
