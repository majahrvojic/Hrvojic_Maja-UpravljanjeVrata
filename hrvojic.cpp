#include "mbed.h"
#include "hrvojic.h"


UpravljanjeVrata::UpravljanjeVrata(PinName crvena_led, PinName zelena_led, PinName motor_otvori, PinName motor_zatvori)
    : crvena_led(new DigitalOut(crvena_led)),
      zelena_led(new DigitalOut(zelena_led)),
        motor_otvori(new DigitalOut(motor_otvori)),
      motor_zatvori(new DigitalOut(motor_zatvori))
{
  inicijalizacija();
}

Timer timer1;
bool Blinker=false;


void UpravljanjeVrata::inicijalizacija(){
    crvena_led->write(1);
    zelena_led->write(0);
    motor_otvori->write(0);
    motor_zatvori->write(0);
}

void UpravljanjeVrata::Otvaranje(){
                crvena_led->write(0);
                timer1.start();
                motor_otvori->write(1);
                while(timer1.read_us()<5000000)
                {
                  Blinker=!Blinker;
                  zelena_led->write(Blinker);
                  wait_us(500000);
                }
            motor_otvori->write(0);
            timer1.stop();
            timer1.reset();
            zelena_led->write(1);            
}

void UpravljanjeVrata::Zatvaranje(){
            zelena_led->write(0);
            timer1.start();
            motor_zatvori->write(1);
                while(timer1.read_us()<5000000)
                {
                    Blinker=!Blinker;
                    crvena_led->write(Blinker);
                    wait_us(500000);
                }
            motor_zatvori->write(0);
            crvena_led->write(1);            
            timer1.stop();
            timer1.reset();
            }
