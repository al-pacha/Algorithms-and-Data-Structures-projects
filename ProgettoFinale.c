/*Versione del progetto in cui viene implementato totalmente l'algoritmo greedy*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "abr.h"
#include "tablivelli.h"
#include "abrprogetti.h"
#include "abrint.h"
#include "tabStrStrInt.h"
#include "abrStr.h"
#include "abr_str_abrstr.h"
#include "tabStr.h"
#include "abrStrInt.h"
#include "tabint.h"

#define ROW_LENGTH 256
#define MAXPROGETTI 100
#define MAXIMPIEGATI 100

/*Definizione delle strutture*/

typedef struct _Calendario Calendario;
struct _Calendario
{
    ABRprogetti progetti;
    int inizio;
    int scadenza;

};

/*Strutture per l'algoritmo greedy*/

typedef int * vint;
typedef double * vdouble;
typedef boolean * vboolean;

typedef struct _datiKP datiKP;
struct _datiKP
{
    int n;
    int V;
    vint phi;
    vdouble v;
};

typedef struct _soluzioneKP soluzioneKP;
struct _soluzioneKP
{
    int f;
    vboolean x;
    tab_int ordinamento;
};

/* Legge dalla linea di comando il file che contiene il grafo */
void InterpretaLineaComando(int argc, char *argv[], char *filedatiUno, char *filedatiDue, char *filedatiTre);
/*Questa funzione racchiude tutte le funzioni di lettura da FILE salvataggio su 
    strutture dati e analisi dei dati in ingresso*/
void Analisi(char *fileCompetenze, char *fileProgetti, char *fileImpiegati);
/*Racchiude la lettura dei 3 file in ingresso ed elabora le competenze*/
void ElaboraCompetenze(ABR T);
/*Racchiude la lettura dei 3 file in ingresso ed elabora le competenze*/
void ElaboraCompetenze2(char *fileCompetenze, char *fileProgetti, char *fileImpiegati);
/*Calendario*/
void StampaCalendario (Calendario *Cal);
/*Legge il file sulle competenze*/
ABR LetturaCompetenze (char *filedati);
/*Legge il file sui progetti*/
void LetturaProgetti (char *filedati, ABR T, Calendario *Cal, tabSSI *tabProgetti);
/*Legge il file sugli impiegati*/
int LetturaImpiegati(char *filedati, ABR T, tabSSI *tabImpiegati, ABRStrInt *impiegatiPesati);
/*Stampa la relazione tra un impiegato e i progetti a cui quell'impiegato può partecipare*/
ABRStrABRStr RelazioneIP (tabSSI *tabImpiegati, tabSSI *tabProgetti);
/*Relazione impiegato-impiegato*/
void RelazioneII (ABRStrABRStr T);
/*Trova e stampa il gruppo di livello massimo di impiegati senza competenze sovrapposte*/
void GruppoMigliore (tabSSI *tabImpiegati, int nimpiegati, ABRStrInt impiegatiPesati);

/*Funzioni ausiliarie per l'algoritmo greedy*/

/*Funzioni ausiliarie per l'algoritmo greedy*/
void CaricaDati (datiKP *pI, ABRStrInt impiegatiPesati, int n, ABRStrABRStr T);
/* Crea una soluzione vuota */
void CreaSoluzione (int n, soluzioneKP *pS);



void GreedyPseudoKP (datiKP *pI, soluzioneKP *pS, ABRStrABRStr relazioneImpiegati, tabS *impiegati);

/*controlla se l'indice dell'impiegato massimo ha una relazione con l'impiegato corrente*/
boolean nessunRelazione (int indice, vboolean soluzione,  ABRStrABRStr relazioneImpiegati, tabS *impiegati);

/*Aggiorna l'heap indiretto attraverso Indice sul vettore V di lunghezza n */
void aggiornaheapindiretto (vint Indice, vdouble V, int n, int i);

/*Crea un heap indiretto attraverso Indice sul vettore V di lunghezza n*/
void creaheapindiretto (vint Indice, vdouble V, int n);

void Scambia(int *pa, int *pb);

/* Stampa la soluzione */
void StampaSoluzione (int n, soluzioneKP *pS, tabS *impiegati, vint pesi);

int CercaPosizione (vint heap, int indice, int dim);

/*Crea un heap indiretto attraverso Indice sul vettore V di lunghezza n*/
void creaheapindirettoRapporti (vint Indice, vint indiceRapporti, vdouble V, int n);

/*Aggiorna l'heap indiretto attraverso Indice sul vettore V di lunghezza n */
void aggiornaheapindirettoRapporti (vint Indice, vint indiceRapporti, vdouble V, int n, int i);

void heapSortIndiretto (vint Indice, vdouble V, int n);

/*Parte esecutiva*/


int main(int argc, char *argv[])
{

    /*Fase dichiarativa*/
    char fileCompetenze[ROW_LENGTH];
    char fileProgetti[ROW_LENGTH];
    char fileImpiegati[ROW_LENGTH];

    /* Legge da linea di comando il file che contiene il grafo */
    InterpretaLineaComando(argc, argv, fileCompetenze,fileProgetti,fileImpiegati);

    /*Fase di Lettura e Analisi*/
    Analisi(fileCompetenze, fileProgetti, fileImpiegati);

}

/* Legge dalla linea di comando il file che contiene il grafo */
void InterpretaLineaComando(int argc, char *argv[], char *filedatiUno, char *filedatiDue, char *filedatiTre)
{
    if (argc != 4)
    {
        fprintf(stderr, "Errore nella linea di comando!\n");
        exit(EXIT_FAILURE);
    }

    strcpy(filedatiUno, argv[1]);
    strcpy(filedatiDue, argv[2]);
    strcpy(filedatiTre, argv[3]);
}

/*Questa funzione racchiude tutte le funzioni di lettura da FILE salvataggio su 
    strutture dati e analisi dei dati in ingresso*/
void Analisi(char *fileCompetenze, char *fileProgetti, char *fileImpiegati)
{
    /*Parte dichiarativa*/
    ABR abrCompetenze = creaABR();
    Calendario Cal;
    /*Anche se viene superata la dimensione massima non è un problema perchè l'inserimento nella tabella alloca nuova memoria*/
    tabSSI tabProgetti = creatabSSI(MAXPROGETTI);
    tabSSI tabImpiegati = creatabSSI(MAXIMPIEGATI);
    ABRStrABRStr impiegatiInOrdine = creaABR_str_ABRStr();
    int nimpiegati;
    ABRStrInt impiegatiPesati = creaABRStrInt ();
    
    

    /*Fase 1: Lettura dati e salvataggio degli stessi su strutture dati*/

    /*Lettura del file delle competenze e salvataggio dei dati in un ABRcompetenze*/
    abrCompetenze = LetturaCompetenze(fileCompetenze);

    /*  Lettura del file dei progetti
        Salvataggio dei dati relativi calendario in una struttura Calendario
    */
    LetturaProgetti(fileProgetti, abrCompetenze, &Cal, &tabProgetti);

    /*Lettura del file impiegati e salvataggio dei dati*/
    nimpiegati = LetturaImpiegati(fileImpiegati, abrCompetenze, &tabImpiegati, &impiegatiPesati);

    /*Fase 2: Analisi dei dati*/

    /*Analisi delle competenze e stampa di quanti progetti richiedono un certo livello di competenza
        e di quanti impiegati possiedono lo stesso livello di competenza*/
    ElaboraCompetenze(abrCompetenze);

    /*Calendario*/
    StampaCalendario (&Cal);

    /*Relazione impiegato-progetti*/
    impiegatiInOrdine = RelazioneIP(&tabImpiegati, &tabProgetti);    

    /*Relazione impiegato-impiegato*/
    RelazioneII (impiegatiInOrdine);

    /*Vogliamo trovare il gruppo di livello massimo di impiegati senza competenze sovrapposte*/
    GruppoMigliore (&tabImpiegati, nimpiegati, impiegatiPesati);


    /*distruzione strutture dati create all'inizio del programma*/
    distruggeABR(&abrCompetenze);
    distruggeABRprogetti(&Cal.progetti);
    distruggetabSSI(&tabProgetti);
    distruggetabSSI(&tabImpiegati);
    distruggeABR_str_ABRStr(&impiegatiInOrdine);
    distruggeABRStrInt(&impiegatiPesati);

}

/*Racchiude la lettura dei 3 file in ingresso ed elabora le competenze*/
void ElaboraCompetenze(ABR T)
{
    /*Stampo ABR con competenze e livelli in ordine*/
    stampaABRLivelli(T);
}

/*Legge il file delle competenze*/
ABR LetturaCompetenze(char *filedati)
{
    /*fase dichiarativa*/
    int ncompetenze;
    int i;
    FILE *fp;
    char riga[ROW_LENGTH];
    ABR T = creaABR();  

    /*Apertura FILE*/
    fp = fopen(filedati, "r");
    if (fp == NULL)
    {
        fprintf(stderr, "Errore nell'apertura del file %s!\n", filedati);
        exit(EXIT_FAILURE);
    }

    /*Leggiamo quante competenze dobbiamo leggere*/
    fscanf(fp, "%d", &ncompetenze);

    /*Lettura di ncompetenze*/
    for(i = 0; i < ncompetenze; i++){
        fscanf(fp, "%s ", riga);
        T = insertABR(riga, T);
    }

    /*Chiusura FILE*/
    fclose(fp);

    return T;

}

/*Legge il FILE con le informazioni sui progetti*/
void LetturaProgetti(char *filedati, ABR T, Calendario *Cal, tabSSI *tabProgetti)
{
    /*Fase dichiarativa*/
    /*Numero progetti nel file*/ 
    int             nprogetti;
    int             i,j;
    FILE            *fp;
    ABRprogetti     Tp = creaABRprogetti();

    /*Ausiliari*/
    char riga[ROW_LENGTH];
    int durata;
    int giorno;
    int guadagno;
    int nimpiegati;

    char competenza[ROW_LENGTH];
    int livello;

    /*Apertura FILE*/
    fp = fopen(filedati, "r");
    if (fp == NULL)
    {
        fprintf(stderr, "Errore nell'apertura del file %s!\n", filedati);
        exit(EXIT_FAILURE);
    }

    /*Lettura numero di progetti*/
    fscanf(fp, "%d", &nprogetti);

    /*Creo due abr di interi, una per salvare le scadenze dei progetti 
        e una per salvare gli inizi così da poterne calcolare facilmente
        la massima scadenza e il minimo inizio, si ha una inefficienza 
        nella gestione della memoria, ma una maggiore velocità temporale
        (si ha in effetti un Theta(logn)??? FORSE LOG H CONTROLLA)
        ma un codice più pulito rispetto al 
        calcolo se fatto direttamente sugli ABRprogetti*/
    ABRint Tscadenze = creaABRint();
    ABRint Tinizi = creaABRint();


    /*Leggo per ogni progetto una riga con
    - Nome progetto, durata, giorno di scadenza, guadagno, numero di impiegati richiesti
      E tante righe quanto è grande il numero di impiegati con
    - Nome competenza, livello competenza*/
    for(i = 0; i < nprogetti; i++)
    {
        fscanf(fp, "%s %d %d %d %d", riga, &durata, &giorno, &guadagno, &nimpiegati);

        Tscadenze = insertABRint(giorno, Tscadenze);
        Tinizi = insertABRint(giorno - durata + 1, Tinizi);
        Tp = insertABRprogetti(riga, Tp, giorno, giorno - durata + 1);
        

        for(j = 0; j < nimpiegati; j++){
            fscanf(fp, "%s %d ", competenza, &livello);
            inslivello(competenza, T, livello, FALSE);

            /*inserisco nella tabella il progetto e le relative competenze*/
            instabSSI (tabProgetti, riga, competenza, livello);
        }
    }
    int smax = maxABRint(Tscadenze);
    int imin = minABRint(Tinizi);

    /*Salvataggio su Calendario*/
    Cal->progetti    = Tp;
    Cal->inizio      = imin;
    Cal->scadenza    = smax;

    /*distruzione strutture dati*/
    distruggeABRint(&Tscadenze);
    distruggeABRint(&Tinizi);

    /*Chiusura FILE*/
    fclose(fp);
}

/*Legge il FILE con le informazioni sugli impiegati*/
int LetturaImpiegati(char *filedati, ABR T, tabSSI *tabImpiegati, ABRStrInt *impiegatiPesati)
{
    /*Parte dichiarativa*/
    int         nimpiegati;
    FILE        *fp;

    /*Ausiliarie*/
    int ncompetenze;
    char nome[ROW_LENGTH];
    char competenza[ROW_LENGTH];
    int livello;
    int i,j;
    int sommaLivelli;

    /*Apertura del FILE*/
    fp = fopen(filedati, "r");
    if (fp == NULL)
    {
        fprintf(stderr, "Errore nell'apertura del file %s!\n", filedati);
        exit(EXIT_FAILURE);
    }
    
    /*Lettura numero impiegati*/
    fscanf(fp, "%d", &nimpiegati);

    /*Leggo una riga con
    - Nome dell'impiegato, numero di competenze possedute
      Leggo un blocco di numero di competenze possedute righe con in ciascuna riga
    - Nome competenza, livello competenza*/ 
    for(i = 0; i < nimpiegati; i++){
        fscanf(fp, "%s %d", nome, &ncompetenze);
        sommaLivelli = 0;

        for(j = 0; j < ncompetenze; j++){
            fscanf(fp, "%s %d", competenza, &livello);
            inslivello(competenza, T, livello, TRUE);
            /*Inserisco gli impiegati della tabella impiegati, con le relative 
                competenze possedute e i relativi livelli*/
            instabSSI(tabImpiegati, nome, competenza, livello);
            sommaLivelli += livello;
        }
        *impiegatiPesati = insertABRStrInt (nome, sommaLivelli, *impiegatiPesati);
    }

    /*Chiusura del FILE*/
    fclose(fp);

    return nimpiegati;
}

/*Calendario*/
void StampaCalendario(Calendario *Cal)
{
    /*Fase dichiarativa*/
    int i, j;

    /*Stampo il CALENDARIO*/
    printf("Calendario\n");
    for (i = Cal->inizio; i <= Cal->scadenza; i++)
    {
        /*Stampo il giorno*/
        printf("%d ", i);

        /*Stampo quanti progetti sono attivi nel giorno attuale*/
        printf("%d ", contaProgettiNelGiorno(Cal->progetti, i));

        /*Stampo i nomi dei progetti che iniziano nel giorno attuale*/
        stampaProgettiInizio(Cal->progetti, i);

        /*Stampo i nomi dei progetti che terminano nel giorno attuale*/
        stampaProgettiScadenza(Cal->progetti, i);

        printf("\n");
        
    }
}

/*Stampa la relazione tra un impiegato e i progetti a cui quell'impiegato può partecipare*/
ABRStrABRStr RelazioneIP(tabSSI *tabImpiegati, tabSSI *tabProgetti)
{
    /*Parte dichiarativa*/
    ABRStrABRStr    impiegatiInOrdine                   = creaABR_str_ABRStr();
    char            impiegato[ROW_LENGTH];
    char            competenzaImpiegato[ROW_LENGTH];
    char            competenzaProgetto[ROW_LENGTH];
    char            progetto[ROW_LENGTH];
    int             i,j,h;

    /*Parte esecutiva*/

    /*Prendo l'impiegato i-esimo*/
    for(i = 1; i <= cardtabSSI(tabImpiegati); i++)
    {
        /*inserisco l'impiegato i-esimo in un ABR che ha come nodo
            -una stringa che salva il nome dell'impiegato
            -un puntatore ad ABR che salva i nomi dei progetti*/
        restituisceStrUno(tabImpiegati, i, impiegato);
        impiegatiInOrdine = insertABR_str_ABRStr(impiegato, impiegatiInOrdine);
        // printf("%s\n", impiegato);

        char current[ROW_LENGTH];
        strcpy(current, impiegato);
        /*Accedo alla competenza j-esima dell'impiegato i-esimo*/
        for(j = i; strcmp(current, impiegato) == 0; j++)
        {
            
            restituisceStrDue(tabImpiegati, j, competenzaImpiegato);
            // printf("%s\n", competenza);
            /*Controllo se la competenza j-esima è richiesta da un progetto
                Quindi scorro in tabProgetti la colonna competenze, finchè non 
                trovo una corrispondenza, fra competenza impiegato e competenza progetto*/
            for(h = 1; h <= cardtabSSI(tabProgetti); h++)
            {
                restituisceStrDue(tabProgetti, h, competenzaProgetto);
                /*Se c'è una corrispondeza devo controllare il livello*/
                if(strcmp(competenzaProgetto, competenzaImpiegato) == 0)
                {
                    /*Se il livello di competenza dell'impiegato è maggiore del livello 
                        di competenza richiesto dal progetto, inserisco il progetto
                        nell'ElencoProgetti dell'impiegato considerato*/
                    if(restituisceVal(tabProgetti, h) <= restituisceVal(tabImpiegati, j))
                    {
                        restituisceStrUno(tabProgetti, h, progetto);
                        insInElenco(impiegato, impiegatiInOrdine, progetto);
                    }

                }
            }


            /*restituisce l'impiegato successivo*/
            restituisceStrUno(tabImpiegati, j+1, impiegato);
        }
       i = j - 1;
        
    }

    /*Stampo gli impiegati e i progetti a cui può partecipare ogni impiegato
        in ordine alfabetico*/
    StampaABR_str_ABRStr(impiegatiInOrdine);

    return impiegatiInOrdine;

}

/*Relazione impiegato-impiegato*/
void RelazioneII (ABRStrABRStr T)
{
    /*Parte dichiarativa*/
    int i, j, h, k;
    int nimpiegati = numeroElementi(T);
    tabS impiegati = creatabS(nimpiegati);
    char progetto[ROW_LENGTH];
    char impiegato[ROW_LENGTH];
    char impiegatoDaConfrontare[ROW_LENGTH];
    

    /*Parte esecutiva*/
    printf("Compatibilita'\n");

    /*Inserisco gli impiegati in una tabella*/
    inserisceInTabS(T, &impiegati);
    
    /*Prendo l'i-esimo impiegato*/
    for(i = 1; i <= nimpiegati; i++)
    {
        /*Salvo l'impiegato corrente*/
        restituisceStringa (&impiegati, i, impiegato);
        /*Creo la tabella progetti*/
        tabS progetti = creatabS(20);
        /*Inserisco l'Elenco delle competenze dell'impiegato corrente in una tabella*/
        inserisceElencoInTabS (T, impiegato, &progetti);

        /*Prendo l'h-esimo impiegato, dove h parte da i+1, perchè i precedenti sono già stati controllati */
        for (h = i+1; h <= nimpiegati; h++)
        {
            /*Salvo impiegato da confrontare*/
            restituisceStringa (&impiegati, h, impiegatoDaConfrontare);
            /*Prendo il j-esimo progetto che appartiene all'impiegato corrente*/
            for(j = 1; j <= cardtabS(&progetti); j++)
            {
                /*Salvo il progetto j-esimo*/
                restituisceStringa (&progetti, j, progetto);
                if (appartieneAdElenco(T, impiegatoDaConfrontare, progetto) == TRUE)
                {
                    printf("(%s,%s)\n", impiegato, impiegatoDaConfrontare);
                    break;
                }
            }
        }

        /*Libero la memoria della tabella*/
        distruggetabS (&progetti);
    }


    /*Distruggiamo la tabella degli impiegati*/
    distruggetabS(&impiegati);

}

/*Trova e stampa il gruppo di livello massimo di impiegati senza competenze sovrapposte*/
void GruppoMigliore (tabSSI *tabImpiegati, int nimpiegati, ABRStrInt impiegatiPesati)
{
    /*Parte dichiarativa*/
    ABRStrABRStr impiegatiInOrdine = creaABR_str_ABRStr ();
    tabS impiegati = creatabS(nimpiegati);
    int i, j, h, k;
    char impiegato[ROW_LENGTH];
    char impiegatoDaConfrontare[ROW_LENGTH];
    char competenzaImpiegato[ROW_LENGTH];
    int nodoImpiegato, nodoImpiegatoDaConfrontare;
    int count;
    /*Qui per ogni impiegato viene salvato l'elenco degli impiegati che hanno competenze comune con il soggetto*/
    ABRStrABRStr relazioneImpiegati = creaABR_str_ABRStr ();
    /*Variabili per KP*/
    datiKP I;
    soluzioneKP S;

    /*Parte esecutiva*/

    /*Creo un albero che contiene gli impiegati e l'elenco di competenze per ogni impiegato*/

    /*Per ogni impiegato */
    for(i = 1; i <= cardtabSSI(tabImpiegati); i++)
    {
        restituisceStrUno(tabImpiegati, i, impiegato);

        /*Inserisco l'impiegato corrente nell'albero */
        impiegatiInOrdine = insertABR_str_ABRStr(impiegato, impiegatiInOrdine);

        char current[ROW_LENGTH];
        strcpy(current, impiegato);
        /*Per ogni competenza dell'impiegato corrente*/
        for(j = i; strcmp(current, impiegato) == 0; j++)
        {
            /*La inserisco nell'elenco dell'impiegato corrente*/
            restituisceStrDue(tabImpiegati, j, competenzaImpiegato);

            insInElenco(impiegato, impiegatiInOrdine, competenzaImpiegato);

            /*restituisce l'impiegato successivo*/
            restituisceStrUno(tabImpiegati, j+1, impiegato);
        }
        i = j - 1;
    }

    /*Creo una tabella che contenga i nomi degli impiegati*/
    inserisceInTabS(impiegatiInOrdine, &impiegati);


    /*Se ho due impiegati con la stessa competenza voglio inserire un arco fra i nodi che li rappresentano*/
    
    /*Per ogni impiegato*/
    for(i = 1; i <= nimpiegati; i++)
    {
        /*Salvo l'impiegato corrente*/
        restituisceStringa (&impiegati, i, impiegato);
        /*Salvo l'impiegato corrente in un albero*/
        relazioneImpiegati = insertABR_str_ABRStr(impiegato, relazioneImpiegati);

        /*Creo una tabella competenze, per poter scorrere agevolmente l'elenco di competenze dell'impiegato*/
        tabS competenze = creatabS(20);
        /*Inserisco l'Elenco delle competenze dell'impiegato corrente nella tabella appena costruita*/
        inserisceElencoInTabS (impiegatiInOrdine, impiegato, &competenze);
        /*Prendo l'h-esimo impiegato, dove h parte da i+1, perchè i precedenti sono già stati controllati*/
        for (h = 1; h <= nimpiegati; h++)
        {
            /*Salvo l'impiegato da confrontare*/
            restituisceStringa (&impiegati, h, impiegatoDaConfrontare);
            // count = 0;
            /*Per ogni competenza dell'impiegato corrente*/
            for(j = 1; j <= cardtabS(&competenze); j++)
            {
                /*Salvo la competenza j-esima*/
                restituisceStringa (&competenze, j, competenzaImpiegato);
                /*Se la competenza dell'impiegato corrente appartiene all'elenco delle competenze dell'impiegato da confrontare*/
                if (appartieneAdElenco(impiegatiInOrdine, impiegatoDaConfrontare, competenzaImpiegato) == TRUE)
                {

                    /*Inserisco l'impiegato nell'elenco dell'impiegato corrente*/
                    insInElenco(impiegato, relazioneImpiegati, impiegatoDaConfrontare);
                    break;
                }
            }
        }
        /*Libero la memoria tabella delle competenze*/
        distruggetabS (&competenze);
    }

    /*Determino euristicamente il sottoinsieme di impiegati di peso massimo con competenze totalmente disgiunte*/

    /*Carica Dati*/
    CaricaDati (&I, impiegatiPesati, nimpiegati, relazioneImpiegati);

    /* Crea una soluzione vuota */
    CreaSoluzione(I.n,&S);

    /*Algoritmo greedy Knapsack Problem modificato*/
    GreedyPseudoKP(&I,&S, relazioneImpiegati, &impiegati);

    StampaSoluzione (I.n, &S, &impiegati, I.phi);

    /*Libero la memoria delle strutture dati delle strutture dati*/
    distruggeABR_str_ABRStr(&impiegatiInOrdine);
    distruggetabS(&impiegati);
    distruggeABR_str_ABRStr(&relazioneImpiegati);
    distrugge_tab_int (&S.ordinamento);
 

}

/*Funzioni ausiliarie per l'algoritmo greedy*/
void CaricaDati (datiKP *pI, ABRStrInt impiegatiPesati, int n, ABRStrABRStr T)
{
    /*Parte dichiarativa*/
    int i;
    tab_int auxPhi;
    tab_int auxV;

    crea_tab_int (&auxPhi, n);
    crea_tab_int (&auxV, n);


    insABRStrIntInTabInt (impiegatiPesati, &auxPhi);
    insInTabIntAltezzeABR (T, &auxV);


    /*Salva n, cioè il numero di impiegati*/
    pI->n = n;

    /*Crea il vettore di interi phi, cioè i pesi degli impiegati*/
    pI->phi = (int *)calloc(pI->n + 1, sizeof(int));
    if (pI->phi == NULL)
    {
        fprintf(stderr, "Errore nell'allocazione del vettore dei premi!\n");
        exit(EXIT_FAILURE);
    }

    /*Crea il vettore di interi v, cioè il numero di impiegati in relazione per ogni impiegato*/
    pI->v = (double *)calloc(pI->n + 1, sizeof(double));
    if (pI->v == NULL)
    {
        fprintf(stderr, "Errore nell'allocazione del vettore dei volumi!\n");
        exit(EXIT_FAILURE);
    }

    /*Inserisco i pesi degli impiegati nel vettore phi*/
    for(i = 1; i <= n; i++)
    {
        pI->phi[i] = RestituisceInteroTabInt (&auxPhi, i);
    }

    /*Inserisco il numero di relazioni degli impiegati fra di loro*/
    for(i = 1; i <= n; i++)
    {
        pI->v[i] = RestituisceInteroTabInt (&auxV, i);
    }

    /*distrugge le tabelle ausiliarie*/
    distrugge_tab_int (&auxPhi);
    distrugge_tab_int (&auxV);

}

/* Crea una soluzione vuota */
void CreaSoluzione (int n, soluzioneKP *pS)
{
  pS->f = 0;
  pS->x = (vboolean) calloc(n+1,sizeof(boolean));
  if (pS->x == NULL)
  {
    fprintf(stderr,"Errore nell'allocazione della soluzione!\n");
    exit(EXIT_FAILURE);
  }

  crea_tab_int(&(pS->ordinamento), n);
}

void GreedyPseudoKP (datiKP *pI, soluzioneKP *pS, ABRStrABRStr relazioneImpiegati, tabS *impiegati)
{

    vint Indice;
    vint IndicePeso;
    vdouble phi_v;
    int nEst;
    int i, iMax, iPMAx;
    int v;    

    /*Creazione dell'indice prima allocandone la memoria e poi inserendo i valori da 1 a n*/
    Indice = (vint)calloc(pI->n + 1, sizeof(int));
    if (Indice == NULL)
    {
        fprintf(stderr, "Errore nell'allocazione di Indice!\n");
        exit(EXIT_FAILURE);
    }

    for (i = 1; i <= pI->n; i++)
        Indice[i] = i;

    /*Creazione dell'indice prima allocandone la memoria e poi inserendo i valori da 1 a n*/
    IndicePeso = (vint)calloc(pI->n + 1, sizeof(int));
    if (IndicePeso == NULL)
    {
        fprintf(stderr, "Errore nell'allocazione di Indice!\n");
        exit(EXIT_FAILURE);
    }

    for (i = 1; i <= pI->n; i++)
        IndicePeso[i] = i;


    /*Creiamo il vettore dei rapporti, e gli inseriamo i valori phi/v*/
    phi_v = (vdouble)calloc(pI->n + 1, sizeof(double));

    if (phi_v == NULL)
    {
        fprintf(stderr, "Errore nell'allocazione di phi_v!\n");
        exit(EXIT_FAILURE);
    }

    for (i = 1; i <= pI->n; i++)
        phi_v[i] = (double)pI->phi[i] / pI->v[i];

    nEst = pI->n;

    heapSortIndiretto (IndicePeso, pI->v, nEst);

    creaheapindirettoRapporti (Indice, IndicePeso, phi_v, nEst);

    while (nEst > 0)
    {
        /*Trova l'elemento di valore massimo*/
        iMax = Indice[1];

        /*Se l'impiegato con l'indice massimo non ha relazioni con x*/
        if (nessunRelazione (iMax, pS->x, relazioneImpiegati, impiegati) == TRUE)
        {
            pS->x[iMax] = TRUE;
            ins_tab_int (&(pS->ordinamento), iMax);
            pS->f += pI->phi[iMax];
            v += pI->v[iMax];
        }

        /*Lo toglie dall'elenco*/
        Indice[1] = Indice[nEst];
        nEst--;
        aggiornaheapindirettoRapporti(Indice, IndicePeso, phi_v, nEst, 1);
    }
    
    /*Libero il vettore degli indici e dei rapporti*/
    free(Indice);
    free(phi_v);

}

/*controlla se l'indice dell'impiegato massimo ha una relazione con l'impiegato corrente*/
boolean nessunRelazione (int indice, vboolean soluzione,  ABRStrABRStr relazioneImpiegati, tabS *impiegati)
{
    /*Parte dichiarativa*/
    char impiegatoMax[ROW_LENGTH];
    char impiegato[ROW_LENGTH];
    int i;

    restituisceStringa(impiegati, indice, impiegatoMax);

    /*Per ogni elemento della soluzione*/
    for (i = 1; i <= cardtabS(impiegati); i++)
    {
        /*Prendere l'indice dell'elemento i-esimo con TRUE*/
        if (soluzione[i] == TRUE)
        {

            /*Salvare il nome dell'impiegato dell'elemento i-esimo con TRUE in una stringa*/
            restituisceStringa(impiegati, i, impiegato);

            /*Se impiegatoMax sta dentro ad un elenco dell'impiegato i-esimo, return FALSE*/
            if (appartieneAdElenco(relazioneImpiegati, impiegato, impiegatoMax) == TRUE)
            {
                return FALSE;
            }
        }
    }
    

    return TRUE;
}

void heapSortIndiretto (vint Indice, vdouble V, int n)
{
    int j;

    creaheapindiretto(Indice, V, n);
    for (j = n; j > 1; j--)
    {
        Scambia(&Indice[1], &Indice[j]);
        aggiornaheapindiretto(Indice, V, j - 1, 1);
    }
}


/*Aggiorna l'heap indiretto attraverso Indice sul vettore V di lunghezza n */
void aggiornaheapindiretto (vint Indice, vdouble V, int n, int i)
{
    int s, d;
    int iMax;

    s = 2 * i;
    d = 2 * i + 1;

    iMax = i;
    if ((s <= n) && (V[Indice[s]] > V[Indice[iMax]]))
        iMax = s;
    if ((d <= n) && (V[Indice[d]] > V[Indice[iMax]]))
        iMax = d;

    if (iMax != i)
    {
        Scambia(&Indice[iMax], &Indice[i]);
        aggiornaheapindiretto(Indice, V, n, iMax);
    }

}

/*Crea un heap indiretto attraverso Indice sul vettore V di lunghezza n*/
void creaheapindiretto (vint Indice, vdouble V, int n)
{
    int i;

    for (i = n / 2; i >= 1; i--)
        aggiornaheapindiretto(Indice, V, n, i);
}

/*Aggiorna l'heap indiretto attraverso Indice sul vettore V di lunghezza n */
void aggiornaheapindirettoRapporti (vint Indice, vint IndicePeso, vdouble V, int n, int i)
{
    int s, d;
    int iMax;

    s = 2 * i;
    d = 2 * i + 1;

    iMax = i;
    if ((s <= n) && (V[Indice[s]] == V[Indice[iMax]]))
    {
        
        if(CercaPosizione(IndicePeso, s, n) > CercaPosizione(IndicePeso, iMax, n) ){
            iMax = s;
        }
    }
    if ((s <= n) && (V[Indice[s]] > V[Indice[iMax]]))
        iMax = s;
    if ((d <= n) && (V[Indice[d]] == V[Indice[iMax]]))
    {
        
        if(CercaPosizione(IndicePeso, d, n) > CercaPosizione(IndicePeso, iMax, n) )
        {
            iMax = d;
        }
    }
    if ((d <= n) && (V[Indice[d]] > V[Indice[iMax]]))
        iMax = d;

    if (iMax != i)
    {
        Scambia(&Indice[iMax], &Indice[i]);
        aggiornaheapindirettoRapporti(Indice, IndicePeso, V, n, iMax);
    }
}

/*Crea un heap indiretto attraverso Indice sul vettore V di lunghezza n*/
void creaheapindirettoRapporti (vint Indice,vint indicePeso, vdouble V, int n)
{
    int i;

    for (i = n / 2; i >= 1; i--)
        aggiornaheapindirettoRapporti(Indice, indicePeso, V, n, i);
}

void Scambia(int *pa, int *pb)
{
    int temp;

    temp = *pa;
    *pa = *pb;
    *pb = temp;
}

/* Stampa la soluzione */  
void StampaSoluzione (int n, soluzioneKP *pS, tabS *impiegati, vint pesi)
{
    int i;
    char impiegato[ROW_LENGTH];
    int aux;

    printf("Soluzione %d\n", pS->f);

    for (i = 1; i <= card_tab_int(&(pS->ordinamento) ); i++)
    {
        aux = RestituisceInteroTabInt(&(pS->ordinamento), i);
        restituisceStringa (impiegati, aux, impiegato);
        printf("%s %d\n", impiegato, pesi[aux]);
    }

}


int CercaPosizione (vint heap, int indice, int dim)
{
    int i;

    for (i = 1; i <= dim; i++){
        if(heap[i] == indice)
        return i;
    }

    return -1;

}

