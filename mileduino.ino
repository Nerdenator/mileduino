#include <SD.h>
#include <CanbusMega.h>
//#include <SoftwareSerial.h>
#include <TinyGPS.h>

#define GPSRATE 4800

//SoftwareSerial for lcd
//SoftwareSerial lcd = SoftwareSerial(0, 16);
//pin for the SD card
const int chipSelect = 9;
//buffer for stuff off the CAN bus
char buffer[10];

//for MPG calculation
float massAirFlow = 0.0;
float vehicleSpeed = 0.0;
float MPG = 0.0;
char* mpgBuf;
const float multiplier1 = 41177.346;
const float multiplier2 = 0.621371;
const int multiplier3 = 3600;

//GPS object
TinyGPS gps;

void getData(TinyGPS &gps);

void setup()
{
  Serial.begin(9600);
  Serial2.begin(9600);
  Serial3.begin(GPSRATE);
  LCDinitialize();
  LCDsetContrast(50);
  LCDsetBrightness(8);
  if(!SD.begin(chipSelect))
  {
    return; 
  }

  Canbus.init(CANSPEED_500);   

  LCDclear();
  LCDsetCursor(1,0);
  Serial2.print("   Mileduino");
  delay(3000);

  LCDclear();
  //Removes old CANGPS.TXT file. 
  if(SD.exists("CANGPS.TXT"))
  {
    SD.remove("CANGPS.TXT");
  }
}
void loop()
{
  while(Serial3.available())
  {
    int c= Serial3.read();
    if(gps.encode(c))
    {
      getData(gps);
    }
  }
}

void getData(TinyGPS &gps)
{
  float latitude, longitude;
  
  File outFile = SD.open("CANGPS.TXT", FILE_WRITE);
  gps.f_get_position(&latitude, &longitude);
  if((Canbus.ecu_req(MAF_SENSOR, buffer) == 1))
    {       
      massAirFlow = atof(buffer);
    }
    if((Canbus.ecu_req(VEHICLE_SPEED, buffer) == 1))
    {      
      vehicleSpeed = atof(buffer); 
    }

    MPG = (multiplier1 * (vehicleSpeed * multiplier2))/ (multiplier3 * massAirFlow);
    
    LCDsetCursor(1, 1);
    //lcd.print("MPG: ");
    Serial2.print("MPG: ");
    LCDsetCursor(2, 1);
    //lcd.print(MPG);
    Serial2.print(MPG, 2);
    outFile.print("mpg,");
    outFile.print(MPG, 2);
    outFile.print("\n");
    outFile.print("lat,"); 
    outFile.print(latitude,6);
    outFile.print("\n");
    outFile.print("long,");
    outFile.print(longitude,6);
    outFile.print("\n");
    outFile.close();
}

void LCDinitialize(){
  //lcd.write(0xFE);
  //lcd.write(0x41);
  //lcd.write(0xFE);
  //lcd.write(0x51);
  Serial2.write(0xFE);
  Serial2.write(0x41);
  Serial2.write(0xFE);
  Serial2.write(0x51);
}

void LCDsetContrast(int contrast){
  if(contrast >50){
    return;
  }
  //lcd.write(0xFE);
  //lcd.write(0x52);
  //lcd.write(contrast);
  Serial2.write(0xFE);
  Serial2.write(0x52);
  Serial2.write(contrast);
}

void LCDsetBrightness(int level){
  if(level > 8){
    return;
  }
  //lcd.write(0xFE);
  Serial2.write(0xFE);
  //lcd.write(0x53);
  Serial2.write(0x53);
  //lcd.write(level);
  Serial2.write(level);
}

void LCDsetCursor(int line_num, int x){
  int g_index[4] = { 
    0x00, 0x40, 0x14, 0x54           };
  //lcd.write(0xFE);
  Serial2.write(0xFE);
  //lcd.write(0x45);
  Serial2.write(0x45);
  //lcd.write(g_index[line_num-1] + x - 1);
  Serial2.write(g_index[line_num-1] + x -1);
}

void LCDclear(){
  //lcd.write(0xFE);
  //lcd.write(0x51);
  Serial2.write(0xFE);
  Serial2.write(0x51);
}

