

#include <Thermistor.h>

Thermistor temp(5);

float sensor_volt = 0.0;
float RS_air = 0.0; //  Get the value of RS via in a clear air
float R0 = 0.0;  // Get the value of R0 via in Alcohol
float sensorValue = 0.0;

void setup()
{
  Serial.begin(19200);


  DDRC |= (1 << PC3);
  DDRC |= (1 << PC2);

  PORTC |= (1 << PC3);
  PORTC &= ~(1 << PC2);
}

void loop()
{



  int temperature = temp.getTemp();
  Serial.print("Temperatura no Sensor eh: ");
  Serial.print(temperature);
  Serial.println("*C");
  Serial.print("\t");



  /*--- Get a average data by testing 100 times ---*/
  for (int x = 0 ; x < 100 ; x++)
  {
    sensorValue = sensorValue + analogRead(A0);
  }
  sensorValue = sensorValue / 100.0;
  Serial.print("VALUE = ");
  Serial.print(sensorValue);
  Serial.print("\t");
  /*-----------------------------------------------*/

  sensor_volt = sensorValue / 1024 * 5.0;
  RS_air = (5.0 - sensor_volt) / sensor_volt; // omit *RL
  R0 = RS_air / 0.9; // The ratio of RS/R0 is 60 in a clear air from Graph (Found using WebPlotDigitizer)

  Serial.print("sensor_volt = ");
  Serial.print(sensor_volt, 3);
  Serial.print("V");
  Serial.print("\t");

  Serial.print("R0 = ");
  Serial.println(R0, 3);
  delay(500);

}
