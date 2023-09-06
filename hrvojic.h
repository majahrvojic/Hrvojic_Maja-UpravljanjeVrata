#include "mbed.h"


class UpravljanjeVrata{
public:

UpravljanjeVrata(PinName crvena_led, PinName zelena_led, PinName motor_otvori, PinName motor_zatvori);

~UpravljanjeVrata();

  void inicijalizacija();
    
  void Otvaranje();

  void Zatvaranje();

private:
	DigitalOut *crvena_led;
	DigitalOut *zuta_led;
	DigitalOut *zelena_led;
    DigitalOut *motor_otvori;
    DigitalOut *motor_zatvori;
};