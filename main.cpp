#include"MicroBit.h"

// Einfügen Bibliothek

MicroBit uBit;
MicroBitButton buttonA(MICROBIT_PIN_BUTTON_A,MICROBIT_ID_BUTTON_A);
MicroBitButton buttonB(MICROBIT_PIN_BUTTON_B,MICROBIT_ID_BUTTON_B);

// Programm
int main()
{
    // Initialisien des Microbits + Knöpfe
    uBit.init();
    uBit.io.P8.isDigital();
    uBit.io.P8.isInput();
    uBit.io.P12.isDigital();
    uBit.io.P12.isInput();
    uBit.io.P16.isDigital();
    uBit.io.P16.isInput();
    
    // Symbol für Spielstart; ein gefülltes Herz
    const uint8_t full_heart_arr[] {
                          0, 1, 0, 1, 0,
                          1, 1, 1, 1, 1,
                          1, 1, 1, 1, 1,
                          0, 1, 1, 1, 0,
                          0, 0, 1, 0, 0, };

    MicroBitImage full_heart(5,5,full_heart_arr);
    
    // Variablen für Reaktionszeit
    int reaction1 = 0;
    int reaction2 = 0;
    int reaction3 = 0;
    int start_time = 0;
    int current_time = 0;


    // Hauptprogramm
    while(1)
    {
        // Beenden des Programms bei Taster B
        if(buttonB.isPressed()){
            uBit.display.scroll("Ende");
            break;
        }

        // Start des Spieles Knopf A ( Countdown und zufalls Wartezeit (bis 3 sekunden) + Frühstart ausgeschlossen + Systemzeit Start)
        if(buttonA.isPressed()){
            uBit.display.print("321");
            int delay=uBit.random(3000);
            uBit.sleep(delay);
            uBit.display.print(full_heart);
            //Abfrage Systemzeit für die Spieler
            start_time = uBit.systemTime();
        }
        

        // Externer Knopf für Spieler 1 mit Bestätigung zum Sieger (LED + TEXT + Reaktionszeit)
        if(uBit.io.P8.getDigitalValue()==1){
            uBit.io.P0.setDigitalValue(1);
            uBit.display.print("RED");
            reaction1 = uBit.systemTime() - start_time;
            uBit.display.scroll(reaction1);
            uBit.sleep(1000);
            uBit.io.P0.setDigitalValue(0);

}
        // Externer Knopf für Spieler 2 mit Bestätigung zum Sieger (LED + TEXT + Reaktionszeit)
        else if (uBit.io.P12.getDigitalValue()==1){
            (uBit.io.P12.setDigitalValue(1));{
            uBit.io.P2.setAnalogValue(1000);
            uBit.display.print("GREEN");
            reaction2 = uBit.systemTime() - start_time;
            uBit.display.scroll(reaction2);
            uBit.sleep(1000);
            uBit.io.P2.setAnalogValue(0);}

}
        // Externer Knopf für Spieler 3 mit Bestätigung zum Sieger (LED + TEXT + Reaktionszeit)
        else if (uBit.io.P16.getDigitalValue()==1){
            (uBit.io.P16.setDigitalValue(1));{
            uBit.io.P1.setAnalogValue(1000);
            uBit.display.print("BLUE");
            reaction3 = uBit.systemTime() - start_time;
            uBit.display.scroll(reaction3);
            uBit.sleep(1000);
            uBit.io.P1.setAnalogValue(0);}

            // Spiel kann durch erneuten Druck auf ButtonA gestartet werden bei ButtonB wird Programm beendet.
}
}

release_fiber();
}