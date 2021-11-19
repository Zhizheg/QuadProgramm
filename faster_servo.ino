#include <GyverPWM.h> 
#include <Servo.h> 
 
Servo ESC; 
 
void setup() { 
pinMode(9, OUTPUT); 
// запустить ШИМ на D9 с частотой 150'000 Гц, режим FAST_PWM 
PWM_frequency(9, 3000, FAST_PWM); 
Serial.begin(9600); 
ESC.attach(9); //"прикрепляем" контроллер ESC к контакту 9 платы Arduino 
ESC.writeMicroseconds(2300); 
delay(2000); 
ESC.writeMicroseconds(0); 
delay(6000); 
} 
void loop() { 
int throttle = analogRead(A0); //считываем напряжение с выхода потенциометра 
Serial.println(throttle); 
throttle = map(throttle, 0, 1023, 800, 2300); //конвертируем значения из диапазона 0-1023 с выхода АЦП в диапазон 0-180 потому что сервомоторы могут работать только в диапазоне 0-180 
ESC.writeMicroseconds(throttle); //генерируем ШИМ сигнал с необходимым коэффициентом заполнения 
}
