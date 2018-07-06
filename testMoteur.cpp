#include <Arduino.h>
#include <Servo.h>!

#define CONF_MOTEUR false  //false = board 1     true = board 2
//           A   B   C   D   E   F   G   H
// OFFSET:  -25 10  +37 -22 -23 -8  +78  -13
const int PIN_MOTOR[] = {10, 11, 6, 5};

const int NB_MOTOR = sizeof(PIN_MOTOR)/ sizeof(*PIN_MOTOR);
#if !CONF_MOTEUR
const int ANGLE_MOTOR[NB_MOTOR] = {90, 90, 90, 90};
const int OFFSET_MOTOR[NB_MOTOR] = {-25, 10, 37, -22};
#else
const int ANGLE_MOTOR[NB_MOTOR] = {90, 90, 90, 90};
const int OFFSET_MOTOR[NB_MOTOR] = {-23, -8, 78, -13};
#endif

int currentAlimMotor = 0;

class Motor{
public:
    Servo* servo;
    int pin;
    int number;
    int offset = 0;
    int angle = 0;

    Motor(int number, int PIN_MOTOR):number(number),pin(PIN_MOTOR){
        servo = new Servo();
    }

    Servo * getServo(){
        return servo;
    }

    void motorOff(){
        servo->detach();
        pinMode(pin, INPUT);
    }
    void motorOn(){
        servo->attach(pin);
        update();
    }

    int getAngle(){
        return offset + angle;
    }
    void setOffset(int offset){
        Motor::offset = offset;
        update();
    }
    void saveOffset(){
        saveOffset(getAngle());
    }
    void saveOffset(int angle){
        offset = angle - ANGLE_MOTOR[number];
        Motor::angle = ANGLE_MOTOR[number];
        update();
    }
    void addAngle(int angle){
        setAngle(Motor::angle + angle);
    }
    void setAngle(int angle){
        Motor::angle = angle;
        update();
    }

    void update(){
        if(servo->attached()) {
            servo->write(getAngle());
        }
    }

    void print(){
        Serial.print("Motor ");
        Serial.print(number);
        Serial.print(" :\t offset:");
        Serial.print(offset);
        Serial.print("\t angle:");
        Serial.println(angle);
    }
};
/** Mesure la référence interne à 1.1 volts */
unsigned int analogReadReference(void) {

    /* Elimine toutes charges résiduelles */
#if defined(__AVR_ATmega328P__)
    ADMUX = 0x4F;
#elif defined(__AVR_ATmega2560__)
    ADCSRB &= ~(1 << MUX5);
  ADMUX = 0x5F;
#elif defined(__AVR_ATmega32U4__)
  ADCSRB &= ~(1 << MUX5);
  ADMUX = 0x5F;
#endif
    delayMicroseconds(5);

    /* Sélectionne la référence interne à 1.1 volts comme point de mesure, avec comme limite haute VCC */
#if defined(__AVR_ATmega328P__)
    ADMUX = 0x4E;
#elif defined(__AVR_ATmega2560__)
    ADCSRB &= ~(1 << MUX5);
  ADMUX = 0x5E;
#elif defined(__AVR_ATmega32U4__)
  ADCSRB &= ~(1 << MUX5);
  ADMUX = 0x5E;
#endif
    delayMicroseconds(200);

    /* Active le convertisseur analogique -> numérique */
    ADCSRA |= (1 << ADEN);

    /* Lance une conversion analogique -> numérique */
    ADCSRA |= (1 << ADSC);

    /* Attend la fin de la conversion */
    while(ADCSRA & (1 << ADSC));

    /* Récupère le résultat de la conversion */
    return ADCL | (ADCH << 8);
}
int stoi(String str);

Motor** motors;

void setup(){
    Serial.begin(9600);
    motors = new Motor*[NB_MOTOR];
    Serial.println(NB_MOTOR);
    for(int i = 0; i< NB_MOTOR; i++) {
        motors[i] = new Motor(i,PIN_MOTOR[i]);
        motors[i]->setOffset(OFFSET_MOTOR[i]);
        motors[i]->setAngle(ANGLE_MOTOR[i]);
        motors[i]->motorOn();
    }

    pinMode(13, OUTPUT);
    pinMode(7,OUTPUT);
    digitalWrite(7,HIGH);
};

long alt = 0;

void loop(){
    digitalWrite(13, (((int)millis()) & 0x200) > 0);
    if (Serial.available() > 0) {
        String command = Serial.readString();
        command.substring(0,command.length()-1);
        Serial.print("Commande: ");
        Serial.println(command);
        if(command[0] >= '0' && command[0] < NB_MOTOR + '0' && command[1] == ':'){
            int n = command[0] - '0';
            switch (command[2]){
                case 'p':
                    break;
                case '+':
                    motors[n]->addAngle(stoi(command.substring(3)));
                    break;
                case '-':
                    motors[n]->addAngle(-stoi(command.substring(3)));
                    break;
                case '=':
                    motors[n]->setAngle(stoi(command.substring(3)));
                    break;
                case 'o':
                    motors[n]->setOffset(stoi(command.substring(3)));
                    break;
            }
            motors[n]->print();
        }else if(command.indexOf("print") == 0){
            for(int i = 0; i< NB_MOTOR; i++) {
                motors[i]->print();
            }
        }else if(command.indexOf("saveOffset") == 0){
            for(int i = 0; i< NB_MOTOR; i++) {
                motors[i]->saveOffset();
            }
        }else if(command.indexOf("offset") == 0){
            for(int i = 0; i< NB_MOTOR && command.indexOf(':') != -1; i++) {
                command = command.substring(command.indexOf(':'));
                motors[i]->setOffset(stoi(command));
            }
        }else{
            Serial.print("UNKNOWN COMMANDE : \"");
            Serial.print(command);
            Serial.println("\"");
        }
    }
    float tension_alim = (1023 * 1.1) / analogReadReference();

    if(millis() > alt){
        alt += 1000;
        Serial.println(tension_alim, 3);

        motors[currentAlimMotor]->motorOff();

        if(currentAlimMotor < NB_MOTOR - 1) {
            currentAlimMotor ++;
        }
        else{
            currentAlimMotor = 0;
        }

        motors[currentAlimMotor+1]->motorOn();

    }



}


int stoi(String str) {
   int value = 0;
   bool isNegatif = str[0] == '-';
   int av = isNegatif;

   while(av < str.length() && str[av] >= '0' && str[av] <= '9'){
       value = value * 10 + str[av] - '0';
       av++;
   }

   return isNegatif ? -value : value;
}



