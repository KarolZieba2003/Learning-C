#include <stdio.h>

void voltageSelection(int refs1, int refs0){
    switch(refs1-refs0){
        case 0:
            if(refs1==0)printf("Bit REFS1: 0, Bit REFS0: 0 stad wybrane zrodlo napiecia: AREF, Internal Vref turned off\n");
            else printf("Bit REFS1: 1, Bit REFS0: 1 stad wybrane zrodlo napiecia: Internal 2,56V Voltage Reference with external capacitor at AREF pin\n");
        break;
        case -1:
            printf("Bit REFS1: 0, Bit REFS0: 1 stad wybrane zrodlo napiecia: Reserved\n");
        break;
        case 1:
            printf("Bit REFS1: 0, Bit REFS0: 1 stad wybrane zrodlo napiecia: AVCC with external capacitor at AREF pin\n");
        break;
    }   
}

int main()
{
    int admux [8];
    int valid = 1;

    for(int i = 0; i<8; i++){
        scanf("%d", &admux[i]);
        if(admux[i]!=0&&admux[i]!=1){
            printf("Zawartosc rejestru zawiera jedynie wartosci 0 i 1, wartosc ktora wpisales: %d jest nieprawidlowa\n", admux[i]);
            valid = 0;
            break;
        }
    }
    if(!valid){
        printf("Z powodu wprowadzenia nieprawidlowej wartosci koncze dzialanie programu, sprobuj ponownie.\n");
        return 1;
    }else{
        voltageSelection(admux[0], admux[1]);
        if(admux[2]==0){
            printf("Bit ADLAR zostal ustawiony na wartosc: 0 wiec wynik jest rownany do prawej (right justified format)");
        }else{
            printf("Bit ADLAR zostal ustawiony na wartosc: 1 wiec wynik jest rownany do lewej (left justified format)");
        }
    }
    return 0;
}