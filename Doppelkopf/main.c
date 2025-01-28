#include <stdio.h>

typedef enum {
    KREUZ,
    PIK,
    HERZ,
    KARO
} Farbe;

typedef enum {
    NEUN,
    ZEHN,
    BUBE,
    DAME,
    KOENIG,
    ASS
} Bild;

typedef enum {
    RE,
    KONTRA,
} Spieler_Status;

typedef struct {
    Farbe farbe;
    Bild bild;
} Karte;

typedef struct {
    Karte karten[12];
    char gespielt[12];
} Deck;

typedef struct {
    Karte karten[36];
} F_Deck;

typedef struct {
    const char* name;
    int punkte;
    float teamProb;
    float probs1[18];
    float probs2[18];
} Gegner;

Karte readKarte(const char farbe, const char bild) {
    Karte returning;
    
    switch(farbe) {
        case 'K':
            returning.farbe = KREUZ;
            break;
        case 'P':
            returning.farbe = PIK;
            break;
        case 'H':
            returning.farbe = HERZ;
            break;
        case 'A':
            returning.farbe = KARO;
            break;
    }

    switch(bild) {
        case '9':
            returning.bild = NEUN;
            break;
        case '1':
            returning.bild = ZEHN;
            break;
        case 'B':
            returning.bild = BUBE;
            break;
        case 'D':
            returning.bild = DAME;
            break;
        case 'K':
            returning.bild = KOENIG;
            break;
        case 'A':
            returning.bild = ASS;
            break;
    }

    return returning;
}

void printKarte(Karte input) {
    switch(input.farbe) {
        case KREUZ:
            printf("Kreuz-");
            break;
        case PIK:
            printf("Pik-");
            break;
        case HERZ:
            printf("Herz-");
            break;
        case KARO:
            printf("Karo-");
            break;
    }

    switch(input.bild) {
        case NEUN:
            printf("9");
            break;
        case ZEHN:
            printf("10");
            break;
        case BUBE:
            printf("Bube");
            break;
        case DAME:
            printf("Dame");
            break;
        case KOENIG:
            printf("Koenig");
            break;
        case ASS:
            printf("Ass");
            break;
    }
}

Deck readDeck(const char* input) {
    Deck returning;

    for(int i = 0; i < 35; i += 3) {
        returning.karten[i / 3] = readKarte(input[i], input[i + 1]);
        returning.gespielt[i / 3] = 0;
    }

    return returning;
}

void printDeck(Deck input) {
    for(int i = 0; i < 12; i++) {
        printKarte(input.karten[i]);
        printf(" ");
    }

    printf("\n");
}

int contains(Deck deck, Karte karte) {
    for(int i = 0; i < 12; i++) {
        if(deck.gespielt[i])
            continue;

        if(deck.karten[i].farbe == karte.farbe && deck.karten[i].bild == karte.bild)
            return i;
    }
    
    return -1;
}

F_Deck initDeck(Deck ours) {
    F_Deck returning;
    int counter = 0;

    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 6; j++) {
            Karte checking = {.farbe = i, .bild = j};

            int containing = contains(ours, checking);
            if(containing == -1) {
                returning.karten[counter] = checking;
                ++counter;
            }
            else
                ours.karten[containing].farbe = 5;
        }
    }

    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 6; j++) {
            Karte checking = {.farbe = i, .bild = j};

            if(contains(ours, checking) == -1) {
                returning.karten[counter] = checking;
                ++counter;
            }
        }
    }
    
    return returning;
}

Gegner initGegner(const char* name) {
    Gegner returning = {.name = name, .punkte = 0, .teamProb = 1.f/3};

    for(int i = 0; i < 18; i++) {
        returning.probs1[i] = 1.f/3;
        returning.probs2[i] = 11.f/35;
    }

    return returning;
}

int indexOf(F_Deck deck, Karte karte) {
    for(int i = 0; i < 36; i++) {
        if(deck.karten[i].farbe == karte.farbe && deck.karten[i].bild == karte.bild)
            return i;
    }

    return -1;
}

void adjustProb1(Gegner* gegner, int gegnerIndex, int index, float value) {
    const float diff = 1 - gegner[gegnerIndex].probs1[index];
    
    switch(gegnerIndex) {
        case 0:
            gegner[0].probs1[index] = value;
            gegner[1].probs1[index] *= (1 - value) / diff;
            gegner[2].probs1[index] *= (1 - value) / diff;
            break;
        case 1:
            gegner[1].probs1[index] = value;
            gegner[0].probs1[index] *= (1 - value) / diff;
            gegner[2].probs1[index] *= (1 - value) / diff;
            break;
        case 2:
            gegner[2].probs1[index] = value;
            gegner[0].probs1[index] *= (1 - value) / diff;
            gegner[1].probs1[index] *= (1 - value) / diff;
            break;
    }
}

void adjustProb2(Gegner* gegner, int gegnerIndex, int index, float value) {
    const float diff = 1 - gegner[gegnerIndex].probs2[index];
    
    switch(gegnerIndex) {
        case 0:
            gegner[0].probs2[index] = value;
            gegner[1].probs2[index] *= (1 - value) / diff;
            gegner[2].probs2[index] *= (1 - value) / diff;
            break;
        case 1:
            gegner[1].probs2[index] = value;
            gegner[0].probs2[index] *= (1 - value) / diff;
            gegner[2].probs2[index] *= (1 - value) / diff;
            break;
        case 2:
            gegner[2].probs2[index] = value;
            gegner[0].probs2[index] *= (1 - value) / diff;
            gegner[1].probs2[index] *= (1 - value) / diff;
            break;
    }
}

void adjustTeamProb(Gegner* gegner, int gegnerIndex, float value) {
    const float diff = 1 - gegner[gegnerIndex].teamProb;
    
    switch(gegnerIndex) {
        case 0:
            gegner[0].teamProb = value;
            gegner[1].teamProb *= (1 - value) / diff;
            gegner[2].teamProb *= (1 - value) / diff;
            break;
        case 1:
            gegner[1].teamProb = value;
            gegner[0].teamProb *= (1 - value) / diff;
            gegner[2].teamProb *= (1 - value) / diff;
            break;
        case 2:
            gegner[2].teamProb = value;
            gegner[0].teamProb *= (1 - value) / diff;
            gegner[1].teamProb *= (1 - value) / diff;
            break;
    }
}

int adjustReKontra(Gegner* gegner, char input, int checking, int kreuzDame, Spieler_Status wir) {
    int returning = 0;

    switch(input) {
        case 'h':
        case 'H':
            adjustProb1(gegner, checking, kreuzDame, 1);
            adjustProb2(gegner, checking, kreuzDame, 1);
            printf("Hochzeit Modus (1: Geht mit, 2: Erste Fremde)? ");
            scanf("%i", &returning);
            break;
        case 'r':
        case 'R':
            switch(wir) {
                case RE:
                    adjustTeamProb(gegner, checking, 1);
                    break;
                case KONTRA:
                    adjustTeamProb(gegner, checking, 0);
                    break;
            }
            adjustProb1(gegner, checking, kreuzDame, 1);
            printf("Re wurde angesagt\n");
            break;
        case 'k':
        case 'K':
            switch(wir) {
                case RE:
                    adjustTeamProb(gegner, checking, 0);
                    break;
                case KONTRA:
                    adjustTeamProb(gegner, checking, 1);
                    break;
            }
            adjustProb1(gegner, checking, kreuzDame, 0);
            printf("Kontra wurde angesagt\n");
            break;
        default:
            printf("Nichts wurde angesagt\n");
            break;
    }

    if(input != 'h' && input != 'H')
        adjustProb2(gegner, checking, kreuzDame, 0);

    return returning;
}

void printTeamProbs(Gegner* gegner) {
    for(int i = 0; i < 3; i++)
        printf("%s: %f\n", gegner[i].name, gegner[i].teamProb);
}

int main(int argc, char** argv) {
    if(argc != 5) {
        printf("Ein Deck und 3 Gegner werden benoetigt\n");
        return 1;
    }

    const Karte kreuzDame = {.farbe = KREUZ, .bild = DAME};

    Deck deck = readDeck(argv[1]);
    Spieler_Status status = (contains(deck, kreuzDame) != -1) ? RE : KONTRA;
    int punke = 0;

    F_Deck fDeck = initDeck(deck);
    Gegner gegner[3] = {initGegner(argv[2]), initGegner(argv[3]), initGegner(argv[4])};

    int position;
    printf("Wer Kommt Raus (0: %s, 1: %s, 2: %s, 3: Wir)? ", argv[2], argv[3], argv[4]);
    scanf(" %i", &position);

    int hochzeit = 0;

    for(int i = 0; i < 4; i++) {
        const int checking = (position + i) % 4;

        if(checking == 3)
            continue;

        printf("Ansage %s: ", gegner[checking].name);
        char input;
        scanf(" %c", &input);

        if(hochzeit == 0)
            hochzeit = adjustReKontra(gegner, input, checking, indexOf(fDeck, kreuzDame), status);
    }

    for(int i = 0; i < 3; i++) {
        printf("%s: %f, %f\n", gegner[i].name, gegner[i].probs1[indexOf(fDeck, kreuzDame)], 
                gegner[i].probs2[indexOf(fDeck, kreuzDame)]);
    }

    printTeamProbs(gegner);

    return 0;
}
