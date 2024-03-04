int counter;

void resetwdt(){
  TIMERG0.wdt_wprotect=TIMG_WDT_WKEY_VALUE;
  TIMERG0.wdt_feed=1;
  TIMERG0.wdt_wprotect=0;
}

void readConfig(void *pvParameters){
  for(;;){
    resetwdt();
    if(digitalRead(FWB) == 0){
      counter++;
      Serial.println(counter);
    }
    if(counter > 10){
      bool pst = EEPROM.readBool(address);
      bool cst = EEPROM.writeBool(address, !pst);
      EEPROM.commit();
      vTaskDelay(10 / portTICK_PERIOD_MS);
      ESP.restart();
    }
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
}
