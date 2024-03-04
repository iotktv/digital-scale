#include <Arduino.h>
#include "soc/timer_group_struct.h"
#include "soc/timer_group_reg.h"
#include <esp_now.h>
#include <WiFi.h>
#include <esp_wifi.h>
#include "EEPROM.h"

#include <BLEDevice.h> 
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>
#include "esp_ota_ops.h"

typedef struct struct_message {
  char stat[5];
  char val[13];
  char unit[3];
} struct_message;

struct_message myData;

#define RXD2 16
#define TXD2 17

#define EEPROM_SIZE 64
#define SERVICE_UUID        "f4eb6c49-afb8-0b2a-10c5-792ac219aa6b"
#define CHARACTERISTIC_UUID "67c75464-2c36-02ce-28ae-f3a4c8eab053"

#define RXD1 22
#define TXD1 23

#define FWB 27

#define BatLS 12
#define BatMS 13
#define BatFS 15


#define BLGS 14
#define WRS 32
#define WGS 33


#define BattSt 34

#define address 50


SemaphoreHandle_t sendSema;
SemaphoreHandle_t checkSema;
TaskHandle_t blStatusTask;

char scaleDataBuff[20];

void setup() {
  // put your setup code here, to run once:
resetwdt();
pinMode(WRS, OUTPUT);
pinMode(WGS, OUTPUT);
pinMode(BLGS, OUTPUT); 
pinMode(BatLS, OUTPUT);
pinMode(BatMS, OUTPUT);
pinMode(BatFS, OUTPUT);
pinMode(FWB,INPUT);
statusStarting();
Serial.begin(9600);
Serial.println("Started");
Serial2.begin(9600, SERIAL_8N1, RXD2, TXD2);
Serial1.begin(9600, SERIAL_8N1, RXD1, TXD1);

sendSema = xSemaphoreCreateBinary();
checkSema = xSemaphoreCreateBinary();
xTaskCreate(startBatStat,"batt",2*1024,NULL,1,NULL);
xTaskCreate(startBlStat,"bleStat",2*1024,NULL,1,&blStatusTask);
xTaskCreate(readConfig,"rc",2*1024,NULL,1,NULL);
initGattServerPlus();
//xTaskCreate(initNowMaster,"inow",4*1024,NULL,3,NULL);
xSemaphoreGive(checkSema);
//xTaskCreate(ScanForSlave,"sken",4*1024,NULL,3,NULL);
xTaskCreate(getFromSerial,"gfs",4*1024,NULL,3,NULL);


//xTaskCreate(getFromSerial,"gfs",2*1024,NULL,3,NULL);

//xTaskCreate(task1,"task1",2*1024,NULL,0,NULL);
//xSemaphoreGive(checkSema);
//xTaskCreate(ScanForSlave,"sken",4*1024,NULL,3,NULL);
//xTaskCreate(initNowMaster,"inow",4*1024,NULL,3,NULL);

//xTaskCreate(startBatStat,"batt",2*1024,NULL,1,NULL);
//xTaskCreate(readConfig,"rc",2*1024,NULL,0,NULL);
//if(!EEPROM.begin(EEPROM_SIZE)){
//  Serial.println("not create EEprom"); delay(5000);
//}
////EEPROM.writeBool(address, false);
////EEPROM.commit();
//Serial.println(EEPROM.readBool(address));
//if(EEPROM.readBool(address) == NULL){
//  Serial.println("null");
//    EEPROM.writeBool(address, false);
//}
//if(EEPROM.readBool(address) == 0){
//  Serial.println("false");
//  sendSema = xSemaphoreCreateBinary();
//  checkSema = xSemaphoreCreateBinary();
//  Serial1.begin(9600, SERIAL_8N1, RXD2, TXD2);
//  Serial2.begin(9600, SERIAL_8N1, RXD1, TXD1);
//  //xTaskCreate(task1,"task1",2*1024,NULL,0,NULL);
//  xTaskCreate(getFromSerial,"gfs",2*1024,NULL,3,NULL);
//  xSemaphoreGive(checkSema);
//  xTaskCreate(ScanForSlave,"sken",4*1024,NULL,3,NULL);
//  xTaskCreate(initNowMaster,"inow",4*1024,NULL,3,NULL);
//  xTaskCreate(startBatStat,"batt",2*1024,NULL,1,NULL);
//  xTaskCreate(readConfig,"rc",2*1024,NULL,0,NULL);
//}
//else if(EEPROM.readBool(address) == 1){
//  Serial.println("true");
//  UpdateFirmware();
//  xTaskCreate(readConfig,"rc",2*1024,NULL,0,NULL);
//}


}

void loop() {
  // put your main code here, to run repeatedly:
vTaskDelete(NULL);
}

//void task1(void *pvParameters){
//  for(;;)
//    {
//    resetwdt();
//    scaleData.stat = "Brow";
//    scaleData.val ="yuyuyuyu";
//    scaleData.unit = "huhuhuhu";
//    xSemaphoreGive(sendSema);
//    Serial.println("Sending");
//    vTaskDelay(3000 / portTICK_PERIOD_MS);
//    }
//  }
