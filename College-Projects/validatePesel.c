#include <stdio.h>
#include <string.h>

int* getPesel(int pesel[11])
{
    for(int i = 0; i<11; i++){
        scanf("%d", &pesel[i]);
        if(pesel[i]<0||pesel[i]>9)
        {
            i = 11;
            return 0;
        }
    }
    return pesel;
}

int checkPesel(int pesel[11])
{
    int x = (1*pesel[0]+3*pesel[1]+7*pesel[2]+9*pesel[3]+1*pesel[4]+3*pesel[5]+7*pesel[6]+9*pesel[7]+1*pesel[8]+3*pesel[9]+1*pesel[10])%10;
    if(x==0){
        return 1;
    }
    else{
        return 0;
    }
}

int checkSex(int pesel[11])
{
    if(pesel[9]%2!=0){return 0;}
    else{return 1;}
}

int main()
{
    int pesel[11];

    printf("Podaj swoj pesel\n");
    if(getPesel(pesel)==0){printf("W PESEL moga byc tylko cyfry od 1-9\n");}
    else{
        if(checkPesel(pesel)==0){
            printf("Twoj pesel jest niepoprawny\n");
            for(int i = 0; i<11; i++)
            {
                printf("%d", pesel[i]);
            }
            printf("\n");
        }
        else{
            printf("Twoj pesel to: \n");
            for(int i = 0; i<11; i++)
            {
                printf("%d", pesel[i]);
            }
            printf("\n");
            if(checkSex(pesel)==0){printf("Jestes mezczyzna \n");}
            else{printf("Jestes kobieta \n");}
        }
    }
    return 0;
}