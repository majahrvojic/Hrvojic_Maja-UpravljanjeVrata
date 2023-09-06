#include "mbed.h"
#include "hrvojic.h"


UpravljanjeVrata *UpravljanjeVrata(new class UpravljanjeVrata(/*Crvena LED*/ARDUINO_UNO_A5, /*Zelena LED*/ARDUINO_UNO_A3, /*motor_otvori*/ARDUINO_UNO_D10, /*motor_zatvori*/ARDUINO_UNO_D11));
DigitalOut crvena_led(ARDUINO_UNO_A5);
DigitalIn Dipswitch1 (ARDUINO_UNO_A0, PullUp);
DigitalOut zuta_led(ARDUINO_UNO_A4);
DigitalOut zelena_led(ARDUINO_UNO_A3);
InterruptIn gljiva(ARDUINO_UNO_A1, PullUp);
Timer debounce_gljiva;
Ticker upozorenje;
Ticker alarm;
Timer debounce;
PwmOut piezo(ARDUINO_UNO_D9);
float freq[2] = {600, 450};
void pritisni_gljivu(void){
	if(debounce_gljiva.read_ms()>500)
    {
	debounce_gljiva.reset();
    bool crvena_status=crvena_led.read();
	bool zelena_status=zelena_led.read();
	bool zuta_status=zuta_led.read();
	bool Kriticno_zaustavljanje=true;
	bool treptaj=true;
    debounce_gljiva.start();
	while(Kriticno_zaustavljanje==true){
		crvena_led=treptaj;
		zelena_led=treptaj;
		zuta_led=treptaj;
		treptaj=!treptaj;
		if(gljiva==0 && debounce_gljiva.read_ms()>500){
			Kriticno_zaustavljanje=false;
		}
        wait_us(500000);
	}
    debounce_gljiva.reset();
    crvena_led=crvena_status;
    zuta_led=zuta_status;
    zelena_led=zelena_status;


}
}
void zvuk(){
        for(int i=0; i<=1; ++i){
                piezo.period(float (1/(freq[i])));
                piezo.write(0.5);
                wait_us(500000);
                alarm.attach(&zvuk, 1000010us);
        }
        piezo=0;
}
void Upozorenje(){
zuta_led=1;
upozorenje.detach();
}

int main(){
debounce.start();
debounce_gljiva.start();
UpravljanjeVrata->inicijalizacija();
    while (1) {

        gljiva.rise(&pritisni_gljivu);
        if(Dipswitch1==0 && debounce.read_ms()>500 && crvena_led==1){
            UpravljanjeVrata->Otvaranje();
            upozorenje.attach(&Upozorenje, 5000000us);
            alarm.attach(&zvuk, 10000000us);
            debounce.reset(); 
        }
        debounce.start();
        if(Dipswitch1==1 && debounce.read_ms()>500 && zelena_led==1){
            upozorenje.detach();
            alarm.detach();
            zuta_led=0;
            UpravljanjeVrata->Zatvaranje();
            debounce.reset();
        }
        
    }
}
  

