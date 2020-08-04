//  Раскомментируйте для программной реализации шины I2C:   //
//  #define pin_SW_SDA 3                                    // Назначение любого вывода Arduino для работы в качестве линии SDA программной шины I2C.
//  #define pin_SW_SCL 9                                    // Назначение любого вывода Arduino для работы в качестве линии SCL программной шины I2C.
//  Раскомментируйте для совместимости с большинством плат: //
//  #include <Wire.h>                                       // Библиотека iarduino_MultiServo будет использовать методы и функции библиотеки Wire.
//  Ссылки для ознакомления:                                //
//  Подробная информация о подключении модуля к шине I2C:   // http://wiki.iarduino.ru/page/i2c_connection/
//  Подробная информация о функциях и методах библиотеки:   // http://wiki.iarduino.ru/page/multi-servo-shield-na-16-servoprivodov/
                                                            //
#include <iarduino_MultiServo.h>                            // Подключаем библиотеку
iarduino_MultiServo MSS;                                    // Объявляем переменную MSS, для работы с библиотекой (объект класса iarduino_MultiServo).
                                                            //
void setup(){                                               //
// MSS.servoSet(10,180,130,470);                            // Ручное позиционирование сервопривода (Подключён к выводу 10. Максимальный угол поворота 180°. ШИМ для 0° = 130. ШИМ для 180° = 470)
// MSS.servoSet(11,180,140,480);                            // Ручное позиционирование сервопривода (Подключён к выводу 11. Максимальный угол поворота 180°. ШИМ для 0° = 140. ШИМ для 180° = 480)
   MSS.servoSet(15, SERVO_SG90);                            // Авто   позиционирование сервопривода (Подключён к выводу 15. Название сервопривода)
                                                            // Функция servoSet() вызывается для каждого сервопривода.
                                                            // Если ко всем выводам подключены одинаковые сервоприводы, то допускается вызвать функцию servoSet() один раз, указав вместо номера вывода: SERVO_ALL
                                                            // - Пример_1: MSS.servoSet(SERVO_ALL, SERVO_SG90); // Ко всем выводам подключены сервоприводы SG90
                                                            // - Пример_2: MSS.servoSet(SERVO_ALL,180,140,480); // Ко всем выводам подключены одинаковые сервоприводы, параметры которых заданы вручную
   MSS.begin();                                             // Инициализация модуля (Адрес по умолчанию = 0x40. Частота по умолчанию = 50Гц)
}                                                           //
                                                            //
void loop(){                                                //
   MSS.servoWrite(15,0);                                    // Повернуть сервопривод, подключённый к 15 выводу, на 0°
   delay(3000);                                             // Ждём 3 сек.
   MSS.servoWrite(15,180);                                  // Повернуть сервопривод, подключённый к 15 выводу, на 180°
   delay(3000);                                             // Ждём 3 сек.
}                                                           //