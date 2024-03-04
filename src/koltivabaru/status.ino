void statusStarting(){
  digitalWrite(WRS,HIGH);
  digitalWrite(BLGS,HIGH);
  digitalWrite(BatLS,HIGH);
}

void startWifiStat(void *pvParameters){
  for(;;){
    resetwdt();
    digitalWrite(WRS,HIGH);
    digitalWrite(WGS,LOW);
    vTaskDelay(300 / portTICK_PERIOD_MS);
    digitalWrite(WRS,LOW);
    digitalWrite(WGS,LOW);
    vTaskDelay(300 / portTICK_PERIOD_MS);
  }
}

void stopWifiStat(){
  digitalWrite(WRS,LOW);
  digitalWrite(WGS,HIGH);
  if(wifiStatusTask != NULL){
    vTaskDelete(wifiStatusTask);
  }
}

void batledmode(int modes){
  if( modes == 1){
    digitalWrite(BatMS,LOW);
    digitalWrite(BatFS,LOW);
    digitalWrite(BatLS,HIGH);
  }
  else if(modes == 2){
    digitalWrite(BatMS,LOW);
    digitalWrite(BatLS,LOW);
    digitalWrite(BatFS,HIGH);
  }
  else if(modes == 3){
    digitalWrite(BatLS,LOW);
    digitalWrite(BatFS,LOW);
    digitalWrite(BatMS,HIGH);
  }
}

    const int numReadings = 10;
    int readings[numReadings];      // the readings from the analog input
    int readIndex = 0;              // the index of the current reading
    int total = 0;                  // the running total
    int average = 0;                // the average

void startBatStat(void *pvParameters){
  for(;;){
    resetwdt();
    
    //int batstat = analogRead(BattSt);

    // subtract the last reading:
    total = total - readings[readIndex];
    // read from the sensor:
    readings[readIndex] = analogRead(BattSt);
    // add the reading to the total:
    total = total + readings[readIndex];
    // advance to the next position in the array:
    readIndex = readIndex + 1;
  
    // if we're at the end of the array...
    if (readIndex >= numReadings) {
      // ...wrap around to the beginning:
      readIndex = 0;
    }
  
    // calculate the average:
    average = total / numReadings;
    // send it to the computer as ASCII digits
    Serial.println(average);

    
    //Serial.println(batstat);
    if(average < 1750){
      batledmode(1);
    }
    else if(average >= 1750 && average < 1950){
      batledmode(2);
    }
    else if(average >= 1950){
      batledmode(3);
    }
    vTaskDelay(100 / portTICK_PERIOD_MS);
  }
}

void startBlStat(void *pvParameters){
  for(;;){
    resetwdt();
    digitalWrite(BLGS,HIGH);
    vTaskDelay(300 / portTICK_PERIOD_MS);
    digitalWrite(BLGS,LOW);
    vTaskDelay(300 / portTICK_PERIOD_MS);
  }
}

void stopBlStat(){
  digitalWrite(BLGS,HIGH);
  if(blStatusTask != NULL){
    vTaskDelete(blStatusTask);
  }
}
