#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <errno.h>




void dodaj_klienta();	        //dodanie klienta do bazy danych
void usun_klienta();	        //usunięcie klienta z bazy danych
void mod_klienta();	            //modyfikacja danych klienta
void sort_nazw();	            //wyświetlanie listy klientów posortowanej po nazwisku
void sort_kwota();	            //wyświetlanie listy klientów posortowanej po wysokości pożyczki

void zadluzenie();	            //sprawdzanie ile zadłużony jest dany klient

void splata_teraz();	        //wyświetlanie listy klientów którzy skończą spłacać pożyczkę w tym miesiącu

void menu();		            //funkcja do obsługi interfejsu
void haslo();		            //funkcja odpowiadająca za zabezpieczenie


int i,j,k,l;                    //zmienne pomocnicze


typedef struct
{
int ident;                      //identyfikator
char imie[20];
char nazwisko[20];
char pesel[11];
char dowod[9];
char ulica[35];
char nr[5];
char kod[6];
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

int main (void)
{

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



for(i=0;i<10;++i)
{
fscanf(f,"%d",&klient[i].ident);
printf("\n\nklient[%d].ident=%d",i,klient[i].ident);
fscanf(f,"%s",klient[i].imie);
printf("\t%s",klient[i].imie);
fscanf(f,"%s",klient[i].nazwisko);
printf("\t%s",klient[i].nazwisko);
fscanf(f,"%s",klient[i].pesel);
printf("\t%s",klient[i].pesel);
fscanf(f,"%s",klient[i].dowod);
printf("\n%s",klient[i].dowod);
fscanf(f,"%s",klient[i].ulica);
printf("\n%s",klient[i].ulica);
fscanf(f,"%s",klient[i].nr);
printf("\n%s",klient[i].nr);
fscanf(f,"%s",klient[i].kod);
printf("\n%s",klient[i].kod);
fscanf(f,"%s",klient[i].miasto);
printf("\n%s",klient[i].miasto);
fscanf(f,"%d",&klient[i].numer1);
printf("\n%d",klient[i].numer1);
fscanf(f,"%d",&klient[i].numer2);
printf("\n%d",klient[i].numer2);
fscanf(f,"%d",&klient[i].numer3);
printf("\n%d",klient[i].numer3);
fscanf(f,"%d",&klient[i].numer4);
printf("\n%d",klient[i].numer4);
fscanf(f,"%d",&klient[i].numer5);
printf("\n%d",klient[i].numer5);
}

for (i=0;i<10;++i)
{
fscanf(g,"%d",&poz[i].numer);
printf("\n\n%d",poz[i].numer);
fscanf(g,"%d",&poz[i].kwota);
printf("\n%d",poz[i].kwota);
fscanf(g,"%d",&poz[i].rok);
printf("\n%d",poz[i].rok);
fscanf(g,"%d",&poz[i].miesiac);
printf("\n%d",poz[i].miesiac);
fscanf(g,"%d",&poz[i].dzien);
printf("\n%d",poz[i].dzien);
fscanf(g,"%d",&poz[i].na_ile);
printf("\n%d",poz[i].na_ile);
fscanf(g,"%f",&poz[i].procent);
printf("\n%.2f",poz[i].procent);

poz[i].rata_kap=(float)poz[i].kwota/(float)poz[i].na_ile;
printf("\nrata_kap[%d]=%f",i,poz[i].rata_kap);              //rata kapitalowa

pom_m=(poz[i].rok*12)+poz[i].miesiac;
printf("\npom_m=%d  pom_b=%d",pom_m,pom_b);


poz[i].ile_m_spl = (poz[i].dzien<b_dzien) ? pom_b-pom_m:pom_b-pom_m-1;
printf("\npoz[%d].ile_m_spl=%d",i,poz[i].ile_m_spl);        //ile miesiecy juz splacono


poz[i].ile_do_splaty=poz[i].kwota;
for(j=0;j<poz[i].ile_m_spl;++j)
{
    poz[i].odsetki=poz[i].ile_do_splaty*(poz[i].procent/12);
    poz[i].rata_lacz=poz[i].rata_kap+poz[i].odsetki;
    poz[i].ile_do_splaty=poz[i].ile_do_splaty-poz[i].rata_kap;
    //printf("\nodsetki=%f",poz[i].odsetki);                     //test   pozniej do usuniecia tak samo jak i printf w klient
}
printf("\npoz[%d].ile_do_splaty=%f",i,poz[i].ile_do_splaty);    //ile jest jeszcze zadluzony     mozna dolozyc jeszce if <0  ==>  tzn nie zwraca nadplaty


}


fclose(f);
return 0;
}
