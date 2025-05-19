#include <iostream>
#include <random>


using namespace std;

// 0 - puste pole; 1 - statek; 2 - zatopiony; 3 - pudlo;
int plansza_gracza[10][10] = {0}, plansza_komputera[10][10] = {0}, ukryta_plansza_komputera[10][10] = {0};

int devmode = 1;


int isValid(int sprWiersz, int sprKolumna, int wybrana_plansza[10][10]){
    for(int wiersz = -1; wiersz<2; wiersz++){
        int kolumna = -1;
        for (kolumna = -1; kolumna<2; kolumna++){
            if(wybrana_plansza[sprWiersz+wiersz][sprKolumna+kolumna] == 1){
                if(wiersz<0||wiersz>9||kolumna<0||kolumna>9) continue;
                else if(wiersz==0&&kolumna==0) continue;
                else return 0;
            }
        }
    }
    return 1;            
}


void display(int wybrana_plansza[10][10]){
    if(wybrana_plansza == plansza_gracza) cout<<"Plansza gracza\n";
    else cout<<"Plansza komputera\n";
    for (int i = 0; i < 10; i++){
        for (int j = 0; j < 10; j++)
        {
            cout << wybrana_plansza[i][j] << " ";
        }
        cout << '\n';
    }
    cout << "--------------------\n";
}

void display(){
    display(plansza_gracza);
    display(ukryta_plansza_komputera);
    if(devmode) display(plansza_komputera);
}

void pause(){
    cout << "Nacisnij Enter aby kontynuowac...\n";
    cin.ignore(); 
    cin.get();
    cout << "\033[2J\033[1;1H"; // czyszczenie terminala    
}

int gameOver(int wybrana_plansza[10][10]){
    for(int i = 0; i<10; i++){
        for(int j = 0; j<10; j++){
            if (wybrana_plansza[i][j] == 1) return 0;
        }
    }
    return 1;
}

int main()
{
    for (int i = 0; i < 4; i++){ //Petla do rozmieszczenia statkow gracza TODO: nadal mozna wybierac miejsca spoza planszy 10x10 np wiersz 75 kolumnna 2173
    
        int wiersz, kolumna;
        while (true)
        {   
            cout << i + 1 << " statek - wprowadz wiersz na planszy (od 1 do 10): \n";
            cin >> wiersz;
            wiersz -=1;
            cout << "\033[2J\033[1;1H"; // czyszczenie terminala
            cout << i + 1 << " statek - wprowadz kolumne na planszy (od 1 do 10): \n";
            cin >> kolumna;
            kolumna -=1;
            if(wiersz<0||wiersz>9||kolumna<0||kolumna>9){
                cout << "Wiersze oraz kolumny musza byc w zakresie od 1 do 10!!\n";
                wiersz = 0, kolumna = 0;
                cout << "\033[2J\033[1;1H"; // czyszczenie terminala
            }
            else{
                if(isValid(wiersz,kolumna,plansza_gracza)){
                        plansza_gracza[wiersz][kolumna] = 1;
                        cout << "\033[2J\033[1;1H"; // czyszczenie terminala
                        break;
                }
            }
            
        }
    }
    
    random_device rd;  
    mt19937 gen(rd()); 
    uniform_int_distribution<> dist(0, 9);

    for (int j = 0; j<4; j++){ //Petla do rozmieszczenia statkow komputera
        while(true){
            int wiersz_k = dist(gen), kolumna_k = dist(gen);
            if(isValid(wiersz_k, kolumna_k, plansza_komputera)){
                plansza_komputera[wiersz_k][kolumna_k] = 1;
                break;
            }
        }
    }

    while(gameOver(plansza_gracza)==0&&gameOver(plansza_komputera)==0){
        int strzal_w, strzal_k;

        cout<<"Wprowadz wiersz na planszy w ktory chcesz strzelic (od 1 do 10): \n";
        cin >> strzal_w;
        strzal_w -=1;
        cout<<"Wprowadz kolumne na planszy w ktora chcesz strzelic (od 1 do 10): \n";
        cin >> strzal_k;
        strzal_k -=1;

        switch(plansza_komputera[strzal_w][strzal_k])
        {
            case 0:
                cout<<"Pudlo! Na polu: ["<<strzal_w+1<<", "<<strzal_k+1<<"] nie ma zadnego statku. \n";
                ukryta_plansza_komputera[strzal_w][strzal_k] = 3, plansza_komputera[strzal_w][strzal_k] = 3;
                pause();
                display();
            break;

            case 1:
                cout<<"Trafiony zatopiony! Na polu: ["<<strzal_w+1<<", "<<strzal_k+1<<"] byl statek komputera. \n";
                ukryta_plansza_komputera[strzal_w][strzal_k] = 2, plansza_komputera[strzal_w][strzal_k] = 2;
                pause();
                display();
            break;

            default:
                cout<<"Juz strzelales w pole: ["<<strzal_w+1<<", "<<strzal_k+1<<"] Tracisz ruch. \n";
                pause();
                display();
            break;
    
        }
        if (gameOver(plansza_komputera)){
            cout << "\033[2J\033[1;1H"; // czyszczenie terminala
            cout<<"Wygrales z komputerem\n";
            break;
        }

        while(true){ //petla zapobiega zeby komputer strzelal w miejsca gdzie juz strzelil
            strzal_w = dist(gen), strzal_k = dist(gen);
            if(plansza_gracza[strzal_w][strzal_k]==0||plansza_gracza[strzal_w][strzal_k]==1) break; 
        }
        
        switch(plansza_gracza[strzal_w][strzal_k]){    
            case 0:
                cout<<"Pudlo! Komputer strzelil w pole: ["<<strzal_w+1<<", "<<strzal_k+1<<"] nie ma tam zadnego statku. \n";
                plansza_gracza[strzal_w][strzal_k] = 3;
                pause();
                display();
            break;

            case 1:
                cout<<"Trafiony zatopiony! Na polu: ["<<strzal_w+1<<", "<<strzal_k+1<<"] byl statek gracza. \n";
                plansza_gracza[strzal_w][strzal_k] = 2;
                pause();
                display();
            break;

            default:
                cout<<"Blad programu\n";
                pause();
                display();
            break;    
        }    
        if (gameOver(plansza_gracza)){
            cout << "\033[2J\033[1;1H"; // czyszczenie terminala
            cout<<"Przegrales z komputerem\n";
            break;
        }
    }
}
