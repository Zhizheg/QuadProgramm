//Код для пульта

void setup(){
  Serial.begin(SB);
  pinMode(pitch_pin, INPUT);
  pinMode(roll_pin, INPUT);
  pinMode(yaw_pin, INPUT);
  pinMode(height_pin, INPUT);

  // Настройки кнопок{
  butt1.setType(HIGH_PULL);
  butt2.setType(HIGH_PULL);
  butt3.setType(HIGH_PULL);  //butt1.setDirection(NORM_OPEN); ВОЗМОЖНО НУЖЕН
  butt4.setType(HIGH_PULL);
  butt5.setType(HIGH_PULL);
  // }Настройки кнопок
  
  // Подключение и настройка радиомодуля{
    if (!radio.begin()){ 
    Serial.println(F("Radio hardware is not responding")); 
    while (1) {}
    }
    else{
      Serial.print("Radio connected");
    }
    radio.setPALevel(RF24_PA_LOW); // RF24_PA_MAX is default. 
    radio.setPayloadSize(sizeof(data_joys)); // float datatype occupies 4 bytes  
    // set the TX address of the RX node into the TX pipe  
    radio.stopListening(); // put radio in TX mode
  // }Настройка радиомодуля
  
}

void loop(){
  send_joys = false;
  send_butt = false;
  //Считывание и обновление данных с джойстиков{
  pitch_new = analogRead(pitch_pin);
  if (pitch != pitch_new){
    send_joys = true;
    pitch = pitch_new;
  }
  roll_new = analogRead(roll_pin);
  if (roll != roll_new){
    send_joys = true;
    roll = roll_new;
  }
  yaw_new = analogRead(yaw_pin);
  if (yaw != yaw_new){
    send_joys = true;
    yaw = yaw_new;
  }
  height_new = analogRead(height_pin);
  if (height != height_new){
    send_joys = true;
    height = height_new;
  }
  //}Считывание данных с джойстиков

  //Считывание данных с кнопок и внесения ихменений в массив для отправки{
  butt1.tick();
  butt2.tick();
  butt3.tick();
  butt4.tick();
  butt5.tick();
  if (butt1.isClick()){
    send_butt = true;
    data_butt[0] = 1;
  }
  else{
    data_butt[0] = 0;
  }
  
  if (butt2.isClick()){
    send_butt = true;
    data_butt[1] = 1;
  }
  else{
    data_butt[1] = 0;
  }

  if (butt3.isClick()){
    send_butt = true;
    data_butt[2] = 1;
  }
  else{
    data_butt[2] = 0;
  }

  if (butt4.isClick()){
    send_butt = true;
    data_butt[3] = 1;
  }
  else{
    data_butt[3] = 0;
  }
  if (butt5.isClick()){
    send_butt = true;
    data_butt[4] = 1;
  }
  else{
    data_butt[4] = 0;
  }
  //}Считывание данных с кнопок и внесения ихменений в массив для отправки

  //Внесение считанных данных в массивы для отправки{
  data_joys[0] = pitch / 256;
  data_joys[1] = pitch % 256;
  data_joys[2] = roll / 256;
  data_joys[3] = roll % 256;
  data_joys[4] = yaw / 256;
  data_joys[5] = yaw % 256;
  data_joys[6] = height / 256;
  data_joys[7] = height % 256;
  //}Внесение считанных данных в массивы для отправки
  
  // Отправка данных{
  if (send_joys){
    radio.openWritingPipe(address[0]);
    report = radio.write(&data_joys, sizeof(data_joys)); // transmit & save the report 
    if (report) { 
      Serial.println("+ Joys succesfull transmition, we're good");
      //То, что будет происходить при удачной отправке данных
    } else { 
      Serial.println(F("- Joys transmission failed or timed out, we're f#cked")); // Данные не добрались до приёмника 
    }
  }
  if (send_butt){
    radio.openWritingPipe(address[1]);
    report = radio.write(&data_butt, sizeof(data_butt)); // transmit & save the report 
    if (report) { 
      Serial.println("+ Button succesfull transmition, we're good");
      //То, что будет происходить при удачной отправке данных
    } else { 
      Serial.println(F("- Buttons transmission failed or timed out, we're f#cked")); // Данные не добрались до приёмника 
  }
  
  }
  // }Отправка данных
  
  //delay(1000); // Для теста
}
