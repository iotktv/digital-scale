bool printStart = false;
bool printEnd = false;
String pStat,pDat,dUnit,pType;
String cUnit="kg";
String scaleDatas;
String cNum;
int line = 0;

void getFromSerial(void *pvParameters){
  for(;;){
    resetwdt();
    if(Serial2.available()){
      String datas = Serial2.readStringUntil('\n');
      //Serial.println(datas.length());
      if(datas.length() == 14){
        cUnit = datas.substring(11,13);
        Serial1.println(datas);
        //Serial.println(cUnit);
      }
      else if(datas.length() == 16){
        if(!datas.substring(0,5).equals("-----")){
          cNum = datas.substring(0,4);
          String cDat = datas.substring(4,15);
          //setToPayload(cNum,cDat,cUnit);
          scaleDatas = cNum + "," + cDat + "," + cUnit;
          cNum.toCharArray(myData.stat,5);
          cDat.toCharArray(myData.val,13);
          cUnit.toCharArray(myData.unit,3);
          scaleDatas.toCharArray(scaleDataBuff,scaleDatas.length()+1);
          xSemaphoreGive(sendSema); 
        }
        Serial1.println(datas);
        if(line == 2){
          line = 0;
          Serial1.println("");
          Serial1.println("");
          Serial1.println("");
          Serial1.println("");
          Serial1.println("");
        }
        if(datas.substring(0,5).equals("-----") && !cNum.equals("0001")){
          line = line + 1;
        }
        
      }
      else if(datas.length() == 17){
        String cStat = datas.substring(0,2);
        String cType = datas.substring(3,5);
        String dat   = datas.substring(8,14);
        String cUnit = datas.substring(14,16);
        Serial.println(dat);
        Serial.println(pDat);
        if(!dat.equals(pDat) && datas.substring(0,2).equals("ST")){
           scaleDatas = cStat + cType + "," + dat + "," + cUnit;
           String statt = cStat + cType;
           statt.toCharArray(myData.stat,5);
           dat.toCharArray(myData.val,7);
           cUnit.toCharArray(myData.unit,3);
           scaleDatas.toCharArray(scaleDataBuff,scaleDatas.length()+1);
           xSemaphoreGive(sendSema);
           Serial.println(scaleDataBuff);
           pStat = cStat;
           pType = cType;
           pDat  = dat;
           dUnit = cUnit;
          }
      }
    }
  }
}
