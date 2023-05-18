#include <BleKeyboard.h>
BleKeyboard bleKeyboard;
portMUX_TYPE mux = portMUX_INITIALIZER_UNLOCKED;

#define btnPin 23
char button;

void deviceInit();
void press_and_sendSingal();

/*IRAM_ATTR*/ void printEvent()
{
  portENTER_CRITICAL_ISR(&mux);
  button = '1';
  portEXIT_CRITICAL_ISR(&mux);
}

void setup()
{
  deviceInit();  
}

void loop()
{
  noInterrupts();portENTER_CRITICAL_ISR(&mux);
  press_and_sendSingal();
  interrupts();portEXIT_CRITICAL_ISR(&mux);
}

void press_and_sendSingal(){
  switch (button)
  {
  case '1':
    bleKeyboard.write('b'/*KEY_UP_ARROW*/);
    button = '0';
    Serial.printf("2");
    // while(digitalRead(btnPin)==LOW);
  break;

  default:
  break;
  }
}

void deviceInit(){
  bleKeyboard.begin();
  Serial.begin(115200);
  Serial.println("Serial start work");

  pinMode(btnPin, INPUT_PULLUP);
  attachInterrupt(btnPin, printEvent, FALLING);
}

// if(lastNum!=num){
//   Serial.printf("%d\n",num);
//   Serial.println(num);   // 千万不要用println或者print,不论是在中断中还是需要快速响应的程序中
//   lastNum=num;           // print/println函数的重载函数太多了,运行耗时太长了
// }                        // 用在中断中方卡的时间太长了导致长时间不喂狗,程序直接跑飞

// 下面是常用单键的示例
//  bleKeyboard.print("Hello world");
//  bleKeyboard.write(KEY_RETURN);
//  bleKeyboard.write(KEY_MEDIA_PLAY_PAUSE);

// 下面是组合键的示例
// Serial.println("Sending Ctrl+Alt+Delete...");
// bleKeyboard.press(KEY_LEFT_CTRL);
// bleKeyboard.press(KEY_LEFT_ALT);
// bleKeyboard.press(KEY_DELETE);
// delay(100);
// bleKeyboard.releaseAll();
