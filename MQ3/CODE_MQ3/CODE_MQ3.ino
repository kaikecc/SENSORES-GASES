

#define pin 13

float sensor_volt;
float RS_gas; // Get value of RS in a GAS
float ratio; // Get ratio RS_GAS/RS_air

unsigned long int milli_time;

void setup() {
  Serial.begin(115200);
  pinMode(pin, INPUT);
  Serial.println("CLEARDATA");
  Serial.println("LABEL,Computer Time,Time (Milli Sec.),Volt,Rs_ratio, Rs/R0");
}

void loop() {
  milli_time = millis();

  int sensorValue = analogRead(A0);
  sensor_volt = (float)sensorValue / 4095 * 3.3;
  RS_gas = (3.3 - sensor_volt) / sensor_volt; // omit *RL

  /*-Replace the name "R0" with the value of R0 in the demo of First Test -*/
  ratio = RS_gas / 0.0666667; // ratio = RS/R0
  /*-----------------------------------------------------------------------*/

  Serial.print("DATA,TIME,");
  Serial.print(milli_time);
  Serial.print(",");
  Serial.print(sensor_volt);
  Serial.print(",");
  Serial.print(RS_gas);
  Serial.print(",");
  Serial.println(ratio);

  delay(100);

}
