/*
  Peafail teie robootikaprojektile.

  Täida:
    - kasutatavad pinnid
    - globaalsed olekumuutujad
    - setup()
    - loop()
    - abifunktsioonid

  NB! Iga oluline tegevus PEAB olema kommenteeritud eesti keeles.
*/

// === KONFIGURATSIOON / PINID ==================================

// TODO: pane enda projektile õiged pinninumbrid
const int IR_PIN = 7;
const int SERVO_PIN = 6;

const int MOTOR_PWM_PIN = 5;
const int MOTOR_IN1_PIN = 2;
const int MOTOR_IN2_PIN = 3;

// === OLEKUMUUTUJAD ============================================

// kas süsteem on aktiivne (nt vent töötab)
bool systemActive = false;

// servo asend kraadides (0-180)
int servoPosDeg = 90;

// mootori kiirus (0-255 PWM)
int motorPwmValue = 128;

// siia võiks tulla nt IR-remote tulemused
// decode_results results; // kui kasutate IRremote teeki


// === SEADISTUS =================================================

void setup() {
  // TODO: lisa raamatukogude init (IRremote, Servo, Serial, jne)

  pinMode(MOTOR_PWM_PIN, OUTPUT);
  pinMode(MOTOR_IN1_PIN, OUTPUT);
  pinMode(MOTOR_IN2_PIN, OUTPUT);

  // seame vaikimisi pöörlemissuunaks IN1 LOW / IN2 HIGH vms
  digitalWrite(MOTOR_IN1_PIN, LOW);
  digitalWrite(MOTOR_IN2_PIN, HIGH);

  // TODO: servo.attach(SERVO_PIN);

  // TODO: Serial.begin(9600);  // kasulik debugimiseks
}


// === ABI FUNKTSIOONID =========================================

// lülitab süsteemi sisse/välja
void toggleSystemActive() {
  if (systemActive) {
    // LÄLITAME VÄLJA
    motorPwmValue = 0;
    servoPosDeg = 90; // näiteks neutraliseerime asendi
    systemActive = false;
  } else {
    // LÜLITAME SISSE
    motorPwmValue = 128; // keskmine kiirus
    systemActive = true;
  }
}

// muudab servo asendit vasak/parem suunas
void nudgeServo(bool turnRight) {
  if (turnRight) {
    if (servoPosDeg < 180) {
      servoPosDeg++;
    }
  } else {
    if (servoPosDeg > 0) {
      servoPosDeg--;
    }
  }
}

// muudab mootori kiirust üles/alla
void changeMotorSpeed(bool faster) {
  if (faster) {
    if (motorPwmValue < 255) {
      motorPwmValue++;
    }
  } else {
    if (motorPwmValue > 0) {
      motorPwmValue--;
    }
  }
}


// === PEATSÜKKEL ===============================================

void loop() {
  // 1. loe sisendid (IR, nupud, sensorid)
  //    TODO: siia IR-koodi lugemine ja switch/case vajutustele

  // 2. rakenda olekumuutused vastavalt sisenditele
  //    nt:
  //    - toggleSystemActive() kui ON/OFF
  //    - nudgeServo(true/false) vasak/parem
  //    - changeMotorSpeed(true/false) +/-


  // 3. kirjuta väljundid riistvarale
  analogWrite(MOTOR_PWM_PIN, motorPwmValue);

  // TODO: servo.write(servoPosDeg);

  // 4. väike viivitus, et mitte uputada andurit
  delay(100);
}
