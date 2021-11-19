#include <MPU9250.h>
#include <Wire.h>
// По умолчанию адрес устройства на шине I2C - 0x68
MPU9250 accelgyro;
int16_t ax, ay, az;
int16_t gx, gy, gz;
float StartValA[3];
float StartValG[3];
float Axyz[3];
float Gxyz[3];
void setup()
{
    //подключаемся к шине I2C (I2Cdev не может сделать это самостоятельно)
    Wire.begin();
    // инициализация подключения в Мониторе порта
    // ( 38400бод выбрано потому, что стабильная работа наблюдается и при 8MHz и при 16Mhz, поэтому
    // в дальнейшем выставляйте скорость согласно ваших требований)
    Serial.begin(38400);
    // Инициализация устройства
    Serial.println("Initializing I2C devices...");
    accelgyro.initialize();
    // Подтверждение подключения
    Serial.println("Testing device connections...");
    delay(1000);
    Serial.println("     ");
    accelgyro.getMotion9(&ax, &ay, &az, &gx, &gy, &gz, &mx, &my, &mz);
    StartValA[0] = (long double) ax / 16384 * 10;
    StartValA[1] = (long double) ay / 16384 * 10;
    StartValA[2] = (long double) az / 16384 * 10;
    accelgyro.getMotion9(&ax, &ay, &az, &gx, &gy, &gz, &mx, &my, &mz);
    StartValG[0] = (double) gx * 250 / 32768;
    StartValG[1] = (double) gy * 250 / 32768;
    StartValG[2] = (double) gz * 250 / 32768;
    }
void loop()
{
    getAccel_Data();             // Получение значений Акселерометра
    getGyro_Data();              // Получение значений Гироскопа
      Serial.print(Axyz[0]-StartValA[0]);
      Serial.print(' ');
      Serial.print(Axyz[1]-StartValA[1]);
      Serial.print(' ');
      Serial.println(Axyz[2]-StartValA[2]);
      Serial.print(Gxyz[0]-StartValG[0]);
      Serial.print(' ');
      Serial.print(Gxyz[1]-StartValG[1]);
      Serial.print(' ');
      Serial.println(Gxyz[2]-StartValG[2]);
    delay(1000);
}
void getAccel_Data(void)
{
    accelgyro.getMotion9(&ax, &ay, &az, &gx, &gy, &gz, &mx, &my, &mz);
    Axyz[0] = (long double) ax / 16384 * 10;
    Axyz[1] = (long double) ay / 16384 * 10;
    Axyz[2] = (long double) az / 16384 * 10;
}
void getGyro_Data(void)
{
    accelgyro.getMotion9(&ax, &ay, &az, &gx, &gy, &gz, &mx, &my, &mz);
    Gxyz[0] = (double) gx * 250 / 32768;
    Gxyz[1] = (double) gy * 250 / 32768;
    Gxyz[2] = (double) gz * 250 / 32768;
}
