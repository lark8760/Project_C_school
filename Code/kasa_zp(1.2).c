#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <errno.h>

#define LP 50

void dodaj_klienta();	        //dodanie klienta do bazy danych
void usun_klienta();	        //usuniêcie klienta z bazy danych
void mod_klienta();	            //modyfikacja danych klienta
void sort_nazw();	            //wyœwietlanie listy klientów posortowanej po nazwisku
void sort_kwota();	            //wyœwietlanie listy klientów posortowanej po wysokoœci po¿yczki

void zadluzenie();	            //sprawdzanie ile zad³u¿ony jest dany klient

void splata_teraz();	        //wyœwietlanie listy klientów którzy skoñcz¹ sp³acaæ po¿yczkê w tym miesi¹cu

void menu();		            //funkcja do obs³ugi interfejsu
void haslo();		            //funkcja odpowiadaj¹ca za zabezpieczenie
void delay();                   //upiekszanie

int i,j,k,l;                    //zmienne pomocnicze
int LK;                         //liczba klientow



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
int numer;                 //numer po¿yczki
int kwota;
int rok;
int miesiac;
int dzien;
int na_ile;                //na ile miesiecy
float procent;             //w skali roku

int ile_m_spl;                  //ile miesiecy juz splacono     nie wprowadzana         potrzebne zeby sprawdzic kto konczy splacac w tym miesiacu
float ile_do_splaty;            //do sprawdzania ile zadluzony jest klient

float rata_kap;                 //rata kapita³owa               nie wprowadzana         po co?
float odsetki;                  //                                                      po co?
float rata_lacz;                //rata ³¹czna (w tym miesiacu)  nie wprowadzana         po co?
}bank;

osoba klient[2000];
bank poz[10000];

//void
void delay(unsigned int mseconds)
{
    clock_t goal = mseconds + clock();
    while (goal > clock());
}

void zapisz (void)
{
    FILE *z;
    z=fopen("baza.txt","w");
    fprintf(z,"%d",LK);

    for(i=0;i<LK;++i)
        {
            fprintf(z,"\n%d",klient[i].ident);
            fprintf(z,"\t%s",klient[i].imie);
            fprintf(z,"\t%s",klient[i].nazwisko);
            fprintf(z,"\t%s",klient[i].pesel);
            fprintf(z,"\t%s",klient[i].dowod);
            fprintf(z,"\t%s",klient[i].ulica);
            fprintf(z,"\t%s",klient[i].nr);
            fprintf(z,"\t%s",klient[i].kod);
            fprintf(z,"\t%s",klient[i].miasto);
            fprintf(z,"\t%d",klient[i].numer1);
            fprintf(z,"\t%d",klient[i].numer2);
            fprintf(z,"\t%d",klient[i].numer3);
            fprintf(z,"\t%d",klient[i].numer4);
            fprintf(z,"\t%d",klient[i].numer5);
        }
    fclose(z);
}



void menu(void)
{
    int choice;                 //menu
    char choice2;               //case 1

    int klient_out;        //case 4

    do
    {
        printf("\n\nNa razie dziala 1,4,11,12,13,14");
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

        //a)	Wyœwietl posortowan¹ listê klientów od najbardziej zad³u¿onego
        //b)	Wyœwietl posortowan¹ listê klientów po roku urodzenia
        //c)	ZnajdŸ klientów po nazwisku
        //d)	ZnajdŸ klientów po dacie po¿yczki
        //e)	Wyœwietl posortowan¹ listê po iloœci po¿yczek na klienta (od 5 do 1)
        //f)	ZnajdŸ klienta po identyfikatorze

        printf("\n(11)	Zapisz");
        printf("\n(12)	Zakoncz");
        printf("\n(13)	Zakoncz i zapisz");
        printf("\n(14)	Test\n");
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
                printf("\n");
//                system("pause");                  /*jesli ma czyscic ekran po wyswietleniu bazy klientow, ale to moze byc przydatne jesli chcesz zmienic dane*/
//                system("cls");
//                break;
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
                printf("\nPodaj numer klienta: ");
                fflush(stdin);
                scanf("%d",&klient_out);
                --klient_out;

                if(klient_out<LK)
                {

                //fscanf(f,"%d",&klient[klient_out].ident);
                printf("\n\nklient[%d].ident=%d",klient_out,klient[klient_out].ident);
                //fscanf(f,"%s",klient[klient_out].imie);
                printf("\t%s",klient[klient_out].imie);
                //fscanf(f,"%s",klient[klient_out].nazwisko);
                printf("\t%s",klient[klient_out].nazwisko);
                //fscanf(f,"%s",klient[klient_out].pesel);
                printf("\n%s",klient[klient_out].pesel);
                //fscanf(f,"%s",klient[klient_out].dowod);
                printf("\n%s",klient[klient_out].dowod);
                //fscanf(f,"%s",klient[klient_out].ulica);
                printf("\n%s",klient[klient_out].ulica);
                //fscanf(f,"%s",klient[klient_out].nr);
                printf("\n%s",klient[klient_out].nr);
                //fscanf(f,"%s",klient[klient_out].kod);
                printf("\n%s",klient[klient_out].kod);
                //fscanf(f,"%s",klient[klient_out].miasto);
                printf("\n%s",klient[klient_out].miasto);
                //fscanf(f,"%d",&klient[klient_out].numer1);
                printf("\n%d",klient[klient_out].numer1);
                //fscanf(f,"%d",&klient[klient_out].numer2);
                printf("\n%d",klient[klient_out].numer2);
                //fscanf(f,"%d",&klient[klient_out].numer3);
                printf("\n%d",klient[klient_out].numer3);
               //fscanf(f,"%d",&klient[klient_out].numer4);
                printf("\n%d",klient[klient_out].numer4);
                //fscanf(f,"%d",&klient[klient_out].numer5);
                printf("\n%d",klient[klient_out].numer5);



                printf("\nCzy chcesz usunac? (Y/N)");
                fflush(stdin);
                scanf("%c",&choice2);
                choice2=toupper(choice2);
                if(choice2=='Y')
                    {
                        for(l=klient_out;l<LK;++l)
                        {
                            klient[klient_out]=klient[klient_out+1];
                            klient[klient_out].ident=klient[klient_out].ident-1;
                            ++klient_out;

                            if(l==LK-1)
                            {
                               --LK;
                               printf("\n\nLK=%d\n\n",LK);
                            }
                        }

                    }

                }
                else
                {
                    printf("\nNie ma klienta o takim numerze");
                }


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
        case 11:
            {
                zapisz();
                break;
            }
        case 13:
            {
                zapisz();
                choice=12;
                break;
            }
        case 14:
            {
                FILE *t;
                t=fopen("baza_test.txt","w");

                fprintf(t,"%d\n",LK);
                fprintf(t,"%d",LK);

                fclose(t);
                break;
            }
        }
    }
    while(choice!=12);
}

void wielka_litera (char *x)                      // porpawia pierwsza litere na wielka reszta male
    {
        int j;
        x[0]=toupper(x[0]);
        j=1;
        while(isalpha(x[j]))
        {
            x[j]=tolower(x[j]);
            j++;
        }
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

fscanf(f,"%d",&LK);

for(i=0;i<LK;++i)
{
fscanf(f,"%d",&klient[i].ident);
//printf("\n\nklient[%d].ident=%d",i,klient[i].ident);
fscanf(f,"%s",klient[i].imie);
//printf("\t%s",klient[i].imie);
fscanf(f,"%s",klient[i].nazwisko);
//printf("\t%s",klient[iFILE *f;
fscanf(f,"%s",klient[i].pesel);
//printf("\n%s",klient[i].pesel);
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
{                                       //jesli gdzies w srodku 0 znaczy blad wczytywania
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
