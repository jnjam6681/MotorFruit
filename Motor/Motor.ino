//pin 6 -> pwm
//pin A1 -> motorF
//pin A2 -> motorB
//pin 2 -> button

// motor
int speed1 = 255;       //แรงตี
const int move = 6;     //pwm
const int motorF = A1;  //direct of motor
const int motorB = A2;

// set pin numbers:
const int buttonPin = 2;    // limit switch

// Variables will change:
int buttonState;             // the current reading from the input pin
int lastButtonState = LOW;   // the previous reading from the input pin

unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
unsigned long debounceDelay = 50;    //ช่วงเวลาจังหวะสัญญาณ

void setup() {
  pinMode(buttonPin, INPUT_PULLUP); //จ่ายสัญญาณตลอด
  pinMode(motorF, OUTPUT);  //กำหนด pin เป็น input หรือ output //pinMode(pin ที่ใช้, input/output)
  pinMode(motorB, OUTPUT);
  // pinMode(sensor, INPUT);
  Serial.begin(9600); // สัญญาณในการส่งข้อมูล
}

void loop() {
  Check_Button(); //ตรวจจับการชนของปุ่ม
}

void Motor_Check()
{
  Serial.println("Start...");
  digitalWrite(motorF, 1); //กำหนดการทำงานของ pin //digitalWrite(pin ที่ใช้, high/low)
  digitalWrite(motorB, 0);
  analogWrite(move, speed1);  //กำหนดการใช้ทำงาน motor //analogWrite(pwm, ความเร็ว) //สั่งการหมุน
  delay(5000); //ตีนานแค่ไหน 1000 = 1 วินาที
  Stop();
}

void Stop()
{
  digitalWrite(motorF, 0);
  digitalWrite(motorB, 0);
}

//เช็คปุ่ม
void Check_Button()
{
  int reading = digitalRead(buttonPin);
  // Serial.println(reading);
  if (reading != lastButtonState) {
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) { //จับสัญญาณปุ่มใช้ช่วงที่กำหนด(50 millis)
    if (reading != buttonState) {   //ค่าตรงข้ามกับที่ตั้งไว้หรือไม่
      buttonState = reading;        //นำค่าที่ได้มากำหนดเป็นสถานะ
      if (buttonState == LOW) {    //ถ้าตรงเงื่อนไข
        Motor_Check();
      }
    }
  }
  lastButtonState = reading;
}
