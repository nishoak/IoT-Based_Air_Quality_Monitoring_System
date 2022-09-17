int mq135_sensor = A0; //Sensor pin of MQ-135
int mq9_sensor = A1;
float m = -0.33846; //Slope
float b = 1.74331; //Constant
float R0 = 5.23; //Sensor Resistance in fresh air from previous code
float m_a =-0.41586; //Slope
float b_a =0.84616; //Constant
float R0_a=1.01;
float m_CO= -0.44538; //Slope 
float b_CO = 1.2370; //Constant 
float R0_CO =0.45056 ; 
float R0_LPG=0.93 ;
void setup() {
Serial.begin(9600); //Baud rate
pinMode(mq135_sensor, INPUT); //Set gas sensor as input
pinMode(mq9_sensor, INPUT);
}
void loop() {
float ratio_CO;
float ratio_LPG;
float sensor_volt_9; //Define variable for sensor voltage 
float RS_gas_9; //Define variable for sensor resistance  
float sensor_volt_135; //Define variable for sensor voltage
float RS_gas_135; //Define variable for sensor resistance
float ratio; //Define variable for ratio for CO2
float ratio_a; //Define variable for ratio
int sensorValue_135 = analogRead(mq135_sensor); //Read analog values of sensor
int sensorValue_9 = analogRead(mq9_sensor);
sensor_volt_135 = (sensorValue_135)*(5.0/1024.0); //Convert analog values to voltage
sensor_volt_9 = (sensorValue_9)*(5.0/1024.0); //Convert analog values to voltage
RS_gas_135 = (5.0-sensor_volt_135)/sensor_volt_135; //Get value of RS in a gas
ratio = RS_gas_135/R0;//    Get ratio RS_gas/R0
ratio_a = RS_gas_135/R0_a;
RS_gas_9=(5.0-sensor_volt_9)/sensor_volt_9; //Get value of RS in a gas
ratio_CO = RS_gas_9/R0_CO;  // Get ratio RS_gas/RS_air
float ppm_log = (log10(ratio)-b)/m; //Get ppm value in linear scale according to logscale
float ppm = pow(10, ppm_log); //Convert ppm value to log scale
float ppm_log_a = (log10(ratio_a)-b_a)/m_a; //Get ppm value in linear scale according to
float ppm_a = pow(10, ppm_log_a); //Convert ppm value to log scale
double ppm_lpg=RS_gas_9/R0_LPG;
double ppm_CO_log = (log10(ratio_CO)-b_CO)/m_CO; //Get ppm value in linear scale according to the the ratio value  
double PPM_CO_log = pow(10, ppm_CO_log); //Convert ppm value to log scale 
Serial.print("PPM of CarbonDioxide in Air = ");
Serial.println(ppm);
Serial.print("PPM of Ammonia in Air = ");
Serial.println(ppm_a);
Serial.print("PPM of Carbon Monoxide in the Air= ");
Serial.println(PPM_CO_log);
Serial.print("PPM of Flammable Gases in the Air= ");
Serial.println(ppm_lpg);
Serial.print("\n\n");
delay(15000);
}
