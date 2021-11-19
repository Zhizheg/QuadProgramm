//Код для сетаов

//Библиотеки{
#include <GyverButton.h>
#include <SPI.h> 
#include "printf.h" 
#include "RF24.h"
//}Библиотеки

//ПИНЫ{
int pitch_pin = A0; //Пин джойстика, отвечающего за тангаж
int roll_pin = A1; //Пин джойстика, отвечающего за крен
int yaw_pin = A2; //Пин джойстика, отвечающего за рысканье
int height_pin = A3; //Пин джойстика, отвечающего за изменение высоты
int CE_pin = 7;
int CSN_pin = 8;
//int buttonPin_1 = ; //*Пины кнопок 1-9
//int buttonPin_2 = ; //*
//int buttonPin_3 = ; //*
//int buttonPin_4 = ; //*
//int buttonPin_5 = ; //*
//int buttonPin_6 = ; //*
//int buttonPin_7 = ; //*
//int buttonPin_8 = ; //*
//}ПИНЫ

// Частота Serial порта{
int SB = 115200;
// }Частота Serial порта

//ОБЪЕКТЫ КЛАССОВ ДЛЯ РАБОТЫ С БИБЛИОТЕКАМИ{
RF24 radio(CE_pin, CSN_pin);
GButton butt1(buttonPin_1);
GButton butt2(buttonPin_2);
GButton butt3(buttonPin_3);
GButton butt4(buttonPin_4);
GButton butt5(buttonPin_5);
//}ОБЪЕКТЫ КЛАССОВ ДЛЯ РАБОТЫ С БИБЛИОТЕКАМИ

//ГЛОБАЛЬНЫЕ ПЕРЕМЕННЫЕ{
uint64_t address[2] = {0xF0F0F0F0D2LL, 0xF0F0F0F0C3LL}; 
bool radioNumber = 1; 
byte data_joys[8]; //Массив для отправляемых данных с джойстика
byte data_butt[8]; //Массив для отправляемых данных с кнопок
//byte new_data_butt[8]; //Массив для новых данных с кнопок
//byte new_data_joys[8]; //Массив для новых данных с джойстиков
int pitch = 0;
int roll = 0;
int yaw = 0;
int height = 0;
bool send_joys, send_butt;
int pitch_new, roll_new, yaw_new, height_new;
bool report;
int pipe;
//}ГЛОБАЛЬНЫЕ ПЕРЕМЕННЫЕ
