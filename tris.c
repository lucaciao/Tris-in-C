#include <stdio.h>
#include <stdbool.h>

//costanti
#define NUM_RIGHE 3
#define NUM_COLONNE 3

#define VUOTO 0
#define GIOCATORE1 1
#define GIOCATORE2 2

#define CARATTERE_GIOCATORE1 'X'
#define CARATTERE_GIOCATORE2 'O'

#define RISULTATO_PARI 0
#define RISULTATO_VINCE_GIOCATORE1 1
#define RISULTATO_VINCE_GIOCATORE2 2

//variabili globali
char TabellaGioco[NUM_RIGHE][NUM_COLONNE];

//prototipi delle funzioni
void VisualizzaTabella();
int ControllaStatoGioco(int giocatore, bool* terminato);
bool LeggiCoordinate(int giocatore);


int main()
{
    int giocatore = 0;
    bool finegioco = false;
    int statoGioco = RISULTATO_PARI;
    //inizializzo TabellaGioco
    for (int r = 0; r < NUM_RIGHE; r++)
    {
        for (int c = 0; c < NUM_COLONNE; c++)
            TabellaGioco[r][c] = VUOTO;
    }
    //vis. tabella di gioco
    VisualizzaTabella();

    //si ripete finch� la partita termina
    do
    {
        if (LeggiCoordinate(giocatore))
        {
            //controlla lo stato del gioco
            statoGioco = ControllaStatoGioco(giocatore, &finegioco);
            //vis. tabella
            VisualizzaTabella();
            if (giocatore == 0)
                giocatore = 1;
            else
                giocatore = 0;
        }
    } while (!finegioco);
    //visualizza lo stato del gioco
    switch (statoGioco)
    {
    case RISULTATO_PARI:
        printf("\nParit�'");
        break;
    case RISULTATO_VINCE_GIOCATORE1:
        printf("\nVince giocatore 1");
        break;
    case RISULTATO_VINCE_GIOCATORE2:
        printf("\nVince giocatore 2");
        break;
    }
    printf("\nFine gioco");
}



void VisualizzaTabella()
{
    //vis. contenuto della tabella di gioco
    printf("  0 1 2\n");
    for (int r = 0; r < NUM_RIGHE; r++)
    {
        printf(" -------\n");
        printf("%d",r);

        for (int c = 0; c < NUM_COLONNE; c++)
        {
            char carattere;
            switch (TabellaGioco[r][c])
            {
            case GIOCATORE1:
                carattere = CARATTERE_GIOCATORE1;
                break;
            case GIOCATORE2:
                carattere = CARATTERE_GIOCATORE2;
                break;
            default:
                carattere = ' ';
                break;
            }
            printf("|%c", carattere);
        }
        printf("|\n");
    }
}

bool LeggiCoordinate(int giocatore)
{
    int riga;
    int colonna;
    //legge le coordinate della tastiera
    printf("\n------------ Giocatore %d-------------", (giocatore + 1));
    printf("\nRiga: ");
    scanf("%d", &riga);
    printf("\nColonna: ");
    scanf("%d", &colonna);
    //verifica la correttezza dei valori inseriti

    if ((riga < 0) || (riga >= NUM_RIGHE) || (colonna < 0) || (colonna >= NUM_COLONNE))
    {
        printf("\nValori non corretti");
        return false;
    }
    //verifica le la casella � gi� occupata
    if (TabellaGioco[riga][colonna] != VUOTO)
    { 
        printf("\nCasella occupata");
        return false;
    }
    if (giocatore == 0)
        TabellaGioco[riga][colonna] = GIOCATORE1;
    else
        TabellaGioco[riga][colonna] = GIOCATORE2;
    return true;
}

int ControllaStatoGioco(int giocatore, bool* terminato)
{
    char simbolo;
    int risultato;
    if (giocatore == 0)
    {
        risultato = RISULTATO_VINCE_GIOCATORE1;
        simbolo = GIOCATORE1;
    }
    else
    {
        risultato = RISULTATO_VINCE_GIOCATORE2;
        simbolo = GIOCATORE2;
    }
//verifica se � stato fatto un tris sulle righe
    for (int i = 0; i < NUM_RIGHE; i++)
    {
        if ((TabellaGioco[i][0] == simbolo) && (TabellaGioco[i][1] == simbolo) && (TabellaGioco[i][2]))
        {
            *terminato=true;
            return risultato;
        }
    }
    //verifica se � stato fatto un tris sulle colonne
    for (int i = 0; i < NUM_COLONNE; i++)
    {
        if ((TabellaGioco[0][i] == simbolo) && (TabellaGioco[1][i] == simbolo) && (TabellaGioco[2][i]))
        {
            *terminato = true;
            return risultato;
        }
    }
    //verifica se � stato fatto un tris sulle colonne
    if ((TabellaGioco[0][0] == simbolo) && (TabellaGioco[1][1] == simbolo) && (TabellaGioco[2][2]))
    {
        *terminato = true;
        return risultato;
    }
    if ((TabellaGioco[2][0] == simbolo) && (TabellaGioco[1][1] == simbolo) && (TabellaGioco[0][2]))
    {
        *terminato = true;
        return risultato;
    }
    //verifica se ci sono ancora caselle libere
    *terminato = true;
        for (int r = 0; r < NUM_RIGHE; r++)
            for (int c = 0; c < NUM_COLONNE; c++)
                if (TabellaGioco[r][c] == VUOTO)
                    *terminato = false;
        return RISULTATO_PARI;
}