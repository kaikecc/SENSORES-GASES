
#define pin 13

float sensor_volt;
float RS_air; //  Get the value of RS via in a clear air
float R0;  // Get the value of R0 via in Alcohol
float sensorValue;
float RS_gas; // Get value of RS in a GAS
float ratio; // Get ratio RS_GAS/RS_air
unsigned long int milli_time;

void setup()
{
  Serial.begin(19200);
  pinMode(pin, INPUT);
  Serial.println("CLEARDATA");
  Serial.println("LABEL,Computer Time,Time (Milli Sec.),Volt, R0, Rs_gas, ratio");
}

void loop()
{
milli_time = millis();

  /*--- Get a average data by testing 100 times ---*/
  for (int x = 0 ; x < 100 ; x++)
  {
    sensorValue = sensorValue + analogRead(pin);
  }
  sensorValue = sensorValue / 100.0;
  /*-----------------------------------------------*/

  sensor_volt = sensorValue / 4095 * 3.2;
  RS_air = (3.2 - sensor_volt) / sensor_volt; // omit *RL
  R0 = RS_air / 60.0; // The ratio of RS/R0 is 60 in a clear air from Graph (Found using WebPlotDigitizer)

  RS_gas = (3.2 - sensor_volt) / sensor_volt; // omit *RL
  ratio = RS_gas / R0;

  Serial.print("DATA,TIME,");
  Serial.print(milli_time);
  Serial.print(",");
  Serial.print(sensor_volt);
  Serial.print(",");
  Serial.print(R0);
  Serial.print(",");
  Serial.print(RS_gas);
  Serial.print(",");
  Serial.println(ratio);
  delay(500);

}
