//bool deviceConnected;
//bool blStat = false;
//TaskHandle_t blStatusTask;
//
//class MyServerCallbacks: public BLEServerCallbacks {
//    void onConnect(BLEServer* pServer) {
//      stopBlStat();
//    };
//
//    void onDisconnect(BLEServer* pServer) {
//      if(blStat == false){
//        xTaskCreate(startBlStat,"bleStat",2*1024,NULL,0,&blStatusTask);
//        blStat = true;
//      }
//    }
//};
//
//
//class MyCallbackHandler: public BLECharacteristicCallbacks {
//  void onRead(BLECharacteristic *pCharacteristic) {
//      pCharacteristic->setValue(scaleDataBuff);
//  }
//};
//
//void initGattServer(){
//  Serial.println("Starting BLE work!");
//  BLEDevice::init("IOT Digital Scale");
//  BLEServer *pServer = BLEDevice::createServer();
//  pServer->setCallbacks(new MyServerCallbacks());
//  BLEService *pService = pServer->createService(SERVICE_UUID);
//  BLECharacteristic *pCharacteristic = pService->createCharacteristic(
//                                         CHARACTERISTIC_UUID,
//                                         BLECharacteristic::PROPERTY_READ
//                                       );
//  pCharacteristic->setCallbacks(new MyCallbackHandler());
//  pCharacteristic->setValue(scaleDataBuff);
//  pService->start();
//  // BLEAdvertising *pAdvertising = pServer->getAdvertising();  // this still is working for backward compatibility
//  BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
//  pAdvertising->addServiceUUID(SERVICE_UUID);
//  pAdvertising->setScanResponse(true);
//  pAdvertising->setMinPreferred(0x06);  // functions that help with iPhone connections issue
//  pAdvertising->setMinPreferred(0x12);
//  BLEDevice::startAdvertising();
//  Serial.println("Characteristic defined! Now you can read it in your phone!");
//}
