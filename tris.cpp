#include <iostream>

//costanti
int const NUM_RIGHE = 3;
int const NUM_COLONNE = 3;

char const VUOTO = 0;
char const GIOCATORE1 = 1;
char const GIOCATORE2 = 2;

char const CARATTERE_GIOCATORE1 = 'X';
char const CARATTERE_GIOCATORE2 = 'O';

char const RISULTATO_PARI = 0;
char const RISULTATO_VINCE_GIOCATORE1 = 1;
char const RISULTATO_VINCE_GIOCATORE2 = 2;

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

    //si ripete finchè la partita termina
    do
    {
        if (LeggiCoordinate(giocatore))
        {
            //controlla lo stato del gioco
            //statoGioco = ControllaStatoGioco(giocatore, &finegioco);
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
        printf("\nParità'");
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
    scanf_s("%d", &riga);
    printf("\nColonna: ");
    scanf_s("%d", &colonna);
    //verifica la correttezza dei valori inseriti

    if ((riga < 0) || (riga >= NUM_RIGHE) || (colonna < 0) || (colonna >= NUM_COLONNE))
    {
        printf("\nValori non corretti");
        return false;
    }
    //verifica le la casella è già occupata
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
//verifica se è stato fatto un tris sulle righe
    for (int i = 0; i < NUM_RIGHE; i++)
    {
        if ((TabellaGioco[i][0] == simbolo) && (TabellaGioco[i][1] == simbolo) && (TabellaGioco[i][2]))
        {
            *terminato=true;
            return risultato;
        }
    }
    //verifica se è stato fatto un tris sulle colonne
    for (int i = 0; i < NUM_COLONNE; i++)
    {
        if ((TabellaGioco[0][i] == simbolo) && (TabellaGioco[1][i] == simbolo) && (TabellaGioco[2][i]))
        {
            *terminato = true;
            return risultato;
        }
    }
    //verifica se è stato fatto un tris sulle colonne
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