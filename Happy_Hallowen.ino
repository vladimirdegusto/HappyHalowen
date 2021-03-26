#include <TimerOne.h>

int OutPin1 = 6;                // Выход управляющий шунтирующим датчик ключом 1
int OutPin2 = 7;                // Выход управляющий шунтирующим датчик ключом 2
int InPin1 = 2;                 // Подключенный паралельно датчику мячей вход 1
int InPin2 = 3;                 // Подключенный паралельно датчику мячей вход 2
volatile int count1 = 0;        // переменная для хранения значения колличества сработок 1
volatile int count2 = 0;        // переменная для хранения значения колличества сработок 2
const int criticalcount = 5;    // Максимальное значение сработок датчика за период "timecr"
const int timecr = 10;          // период блокировки выраженный в количестве циклов проверки сработок
volatile int timecr1 = 0;       //оставшееся время блокировки 1
volatile int timecr2 = 0;       //оставшееся время блокировки 2


void setup() {
  

    Timer1.initialize(2000000); //период проверки 2 сек.
   // настроить вывод блокировки 1 на выход:
   pinMode(OutPin1, OUTPUT);
   // настроить вывод датчика 1 на вход:
   pinMode(InPin1, INPUT);
   // прикрепить прерывание к пину 2(вектор 0)
   attachInterrupt(0, pin_ISR1, RISING);
    
   // настроить вывод блокировки 2 на выход:
   pinMode(OutPin2, OUTPUT);
   // настроить вывод датчика 2 на вход:
   pinMode(InPin2, INPUT);
   // прикрепить прерывание к пину 3(вектор 1)
   attachInterrupt(1, pin_ISR2, RISING);
   
   Timer1.attachInterrupt(Timer1_action);
   
}

void loop() {
 }

void pin_ISR1() // обработка прерывания входа датчика 1
{

  count1 ++;
  }

void pin_ISR2() // обработка прерывания входа датчика 2
{

  count2 ++;
  }

void Timer1_action()
{
Serial.println(timecr1);
                  // Обработка 1 ого канала

  if (timecr1 == 0)
{
  // В этом блоке список команд, выполняющихся, если время блокировки прошло или ее небыло
  if (count1 > criticalcount) //если превышен лимит то блокируем
  {
  timecr1 = timecr; 
  digitalWrite(OutPin1,HIGH); 
  digitalWrite(LED_BUILTIN, HIGH); // Зажигаем встроеный светодиод
  }
}
else
{
// В этом блоке список команд, выполняющихся, если в действии блокировка  
 timecr1 --; // уменьшаем счетчик блокировки
 if (timecr1 == 1)  // Снимаем блок если остался 1 тайминг блокировки.
 {
  digitalWrite(OutPin1,LOW);
  digitalWrite(LED_BUILTIN, LOW);
 }

}
count1 = 0; // обнуляем счетчик 


                  // Обработка 2 ого канала


  if (timecr2 == 0)
{
//  В этом блоке список команд, выполняющихся, если время блокировки прошло или ее небыло
  if (count2 > criticalcount) //если превышен лимит то блокируем
  {
  timecr2 = timecr; 
  digitalWrite(OutPin2,HIGH); 
  digitalWrite(LED_BUILTIN, HIGH); // Зажигаем встроеный светодиод, для индикации сработки блокировки.
  }
}
else
{
//   В этом блоке список команд, выполняющихся, если в действии блокировка  
  timecr2 --; // уменьшаем счетчик блокировки
  if (timecr2 == 1)  // Снимаем блок если остался 1 тайминг блокировки.
  {
  digitalWrite(OutPin2,LOW);
  digitalWrite(LED_BUILTIN, LOW); // гасим встроеный светодиод, для индикации сработки блокировки.
  }

}
count2 = 0; // обнуляем счетчик 


}
