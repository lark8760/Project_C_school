#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <errno.h>

#define LK 10
#define LP 10


void dodaj_klienta();	        //dodanie klienta do bazy danych
void usun_klienta();	        //usunięcie klienta z bazy danych
void mod_klienta();	            //modyfikacja danych klienta
void sort_nazw();	            //wyświetlanie listy klientów posortowanej po nazwisku
void sort_kwota();	            //wyświetlanie listy klientów posortowanej po wysokości pożyczki

void zadluzenie();	            //sprawdzanie ile zadłużony jest dany klient

void splata_teraz();	        //wyświetlanie listy klientów którzy skończą spłacać pożyczkę w tym miesiącu

void menu();		            //funkcja do obsługi interfejsu
void haslo();		            //funkcja odpowiadająca za zabezpieczenie
void delay();                   //upiekszanie

int i,j,k,l;                    //zmienne pomocnicze


typedef struct
{
int ident;                      //identyfikator
char imie[20];
char nazwisko[20];
char pesel[12];
char dowod[10];
char ulica[35];
char nr[5];
char kod[7];
char miasto[20];
int numer1;
int numer2;
int numer3;
int numer4;
int numer5;
}osoba;

typedef struct
{
int numer;                 //numer pożyczki
int kwota;
int rok;
int miesiac;
int dzien;
int na_ile;                //na ile miesiecy
float procent;             //w skali roku

int ile_m_spl;                  //ile miesiecy juz splacono     nie wprowadzana         potrzebne zeby sprawdzic kto konczy splacac w tym miesiacu
float ile_do_splaty;            //do sprawdzania ile zadluzony jest klient

float rata_kap;                 //rata kapitałowa               nie wprowadzana         po co?
float odsetki;                  //                                                      po co?
float rata_lacz;                //rata łączna (w tym miesiacu)  nie wprowadzana         po co?
}bank;

osoba klient[10];
bank poz[50];

//void
void delay(unsigned int mseconds)
{
    clock_t goal = mseconds + clock();
    while (goal > clock());
}

void menu(void)
{
    int choice;
    char choice2;
    do
    {
        printf("\n\nNa razie dziala 1,11");
        printf("\n(1)	Wyswietl baze klientow");
        printf("\n(2)	Modyfikuj dane klienta");
        printf("\n(3)	Dodaj klienta");
        printf("\n(4)	Usun klienta");
        printf("\n(5)	Wyswietl baze pozyczek");
        printf("\n(6)	Wyswietl liste klientow posortowana po nazwisku");
        printf("\n(7)	Wyswietl liste klientow posortowana po wysokosci pozyczki");
        printf("\n(8)	Sprawdz ktorzy sposrod klientow koncza splacac pozyczke w tym miesiacu");
        printf("\n(9)	Sprawdz zadluzenie danego klienta");
        printf("\n(10)	Wybierz dodatkowe opcje:");

        //a)	Wyświetl posortowaną listę klientów od najbardziej zadłużonego
        //b)	Wyświetl posortowaną listę klientów po roku urodzenia
        //c)	Znajdź klientów po nazwisku
        //d)	Znajdź klientów po dacie pożyczki
        //e)	Wyświetl posortowaną listę po ilości pożyczek na klienta (od 5 do 1)
        //f)	Znajdź klienta po identyfikatorze

        printf("\n(11)	Zakoncz");
        fflush(stdin);
        scanf("%d",&choice);

        switch(choice)
        {
        case 1:
            {
                printf("\nCzy chcesz wyswietlic adresy? (Y/N)");
                fflush(stdin);
                scanf("%c",&choice2);
                choice2=toupper(choice2);

                for(i=0;i<LK;++i)
                {
                    printf("\n\n%d",klient[i].ident);
                    printf("  %s",klient[i].imie);
                    printf("  %s",klient[i].nazwisko);
                    printf("  %s",klient[i].pesel);
                    printf("  %s",klient[i].dowod);


                    if(choice2=='Y')
                    {
                        printf("\n   ul. %s",klient[i].ulica);
                        printf("  %s",klient[i].nr);
                        printf("  %s",klient[i].kod);
                        printf("  %s",klient[i].miasto);
                    }
                }
                break;
            }
        case 2:
            {
                break;
            }
        case 3:
            {
                break;
            }
        case 4:
            {
                break;
            }
        case 5:
            {
                break;
            }
        case 6:
            {
                break;
            }
        case 7:
            {
                break;
            }
        case 8:
            {
                break;
            }
        case 9:
            {
                break;
            }
        case 10:
            {
                break;
            }
        }
    }
    while(choice!=11);
}

int main (void)
{
//printf("Loading data");                     //fun
//delay(1000);printf("\n.");delay(1000);printf("\n.");delay(1000);printf("\n.");delay(1000);
//printf("\nInitializing");
//delay(1000);printf("\n.");delay(1000);printf("\n.");delay(1000);printf("\n.");delay(1000);
//system("cls");delay(1000);

FILE *f;
f=fopen("baza.txt","r");     //osoba.txt
FILE *g;
g=fopen("bank.txt","r");     //p.txt

int b_rok,b_miesiac,b_dzien;    //biezaca data          DO ULEPSZENIA
b_rok=2017;
b_miesiac=04;
b_dzien=14;

int pom_m,pom_b;      //pomocniczna liczba miesiecy / ile miesiecy teraz
pom_b=(b_rok*12)+b_miesiac;



for(i=0;i<LK;++i)
{
fscanf(f,"%d",&klient[i].ident);
//printf("\n\nklient[%d].ident=%d",i,klient[i].ident);
fscanf(f,"%s",klient[i].imie);
//printf("\t%s",klient[i].imie);
fscanf(f,"%s",klient[i].nazwisko);
//printf("\t%s",klient[i].nazwisko);
fscanf(f,"%s",klient[i].pesel);
printf("\n%s",klient[i].pesel);
fscanf(f,"%s",klient[i].dowod);
//printf("\n%s",klient[i].dowod);
fscanf(f,"%s",klient[i].ulica);
//printf("\n%s",klient[i].ulica);
fscanf(f,"%s",klient[i].nr);
//printf("\n%s",klient[i].nr);
fscanf(f,"%s",klient[i].kod);
//printf("\n%s",klient[i].kod);
fscanf(f,"%s",klient[i].miasto);
//printf("\n%s",klient[i].miasto);
fscanf(f,"%d",&klient[i].numer1);
//printf("\n%d",klient[i].numer1);
fscanf(f,"%d",&klient[i].numer2);
//printf("\n%d",klient[i].numer2);
fscanf(f,"%d",&klient[i].numer3);
//printf("\n%d",klient[i].numer3);
fscanf(f,"%d",&klient[i].numer4);
//printf("\n%d",klient[i].numer4);
fscanf(f,"%d",&klient[i].numer5);
//printf("\n%d",klient[i].numer5);
}

for (i=0;i<LP;++i)
{
fscanf(g,"%d",&poz[i].numer);
//printf("\n\n%d",poz[i].numer);
fscanf(g,"%d",&poz[i].kwota);
//printf("\n%d",poz[i].kwota);
fscanf(g,"%d",&poz[i].rok);
//printf("\n%d",poz[i].rok);
fscanf(g,"%d",&poz[i].miesiac);
//printf("\n%d",poz[i].miesiac);
fscanf(g,"%d",&poz[i].dzien);
//printf("\n%d",poz[i].dzien);
fscanf(g,"%d",&poz[i].na_ile);
//printf("\n%d",poz[i].na_ile);
fscanf(g,"%f",&poz[i].procent);
//printf("\n%.2f",poz[i].procent);

poz[i].rata_kap=(float)poz[i].kwota/(float)poz[i].na_ile;
//printf("\nrata_kap[%d]=%f",i,poz[i].rata_kap);              //rata kapitalowa

pom_m=(poz[i].rok*12)+poz[i].miesiac;
//printf("\npom_m=%d  pom_b=%d",pom_m,pom_b);


poz[i].ile_m_spl = (poz[i].dzien<b_dzien) ? pom_b-pom_m:pom_b-pom_m-1;
//printf("\npoz[%d].ile_m_spl=%d",i,poz[i].ile_m_spl);        //ile miesiecy juz splacono


poz[i].ile_do_splaty=poz[i].kwota;
for(j=0;j<poz[i].ile_m_spl;++j)
{
    poz[i].odsetki=poz[i].ile_do_splaty*(poz[i].procent/12);
    poz[i].rata_lacz=poz[i].rata_kap+poz[i].odsetki;
    poz[i].ile_do_splaty=poz[i].ile_do_splaty-poz[i].rata_kap;
    //printf("\nodsetki=%f",poz[i].odsetki);                     //test   pozniej do usuniecia tak samo jak i printf w klient
}
//printf("\npoz[%d].ile_do_splaty=%f",i,poz[i].ile_do_splaty);    //ile jest jeszcze zadluzony     mozna dolozyc jeszce if <0  ==>  tzn nie zwraca nadplaty

}


system("cls");
menu();


fclose(f);
fclose(g);
return 0;
}
