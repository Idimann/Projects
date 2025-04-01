#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define FARB_NUMBER 4
enum Farbe {
    KREUZ,
    PIK,
    HERZ,
    KARO
};

#define BILD_NUMBER 6
enum Bild {
    NEUN,
    ZEHN,
    BUBE,
    DAME,
    KOENIG,
    ASS
};

enum Spieler_Status {
    RE,
    KONTRA,
    UNKNOWN,
};

struct Karte {
    enum Farbe farbe;
    enum Bild bild;
};

int equals(const struct Karte *first, const struct Karte *second) {
    return first->farbe == second->farbe && first->bild == second->bild;
}

void print_card(struct Karte *card) {
    switch(card->farbe) {
        case KREUZ:
            printf("Kr");
            break;
        case PIK:
            printf("Pi");
            break;
        case HERZ:
            printf("He");
            break;
        case KARO:
            printf("Ka");
            break;
    }

    switch(card->bild) {
        case NEUN:
            printf("9");
            break;
        case ZEHN:
            printf("1");
            break;
        case BUBE:
            printf("B");
            break;
        case DAME:
            printf("D");
            break;
        case KOENIG:
            printf("K");
            break;
        case ASS:
            printf("A");
            break;
    }
}

struct Karte get_card(const char *input) {
    assert(strlen(input) >= 3 && "Invalid card input\n");

    struct Karte returning;

    switch(input[0]) {
        case 'K':
            switch(input[1]) {
                case 'r':
                    returning.farbe = KREUZ;
                    break;
                case 'a':
                    returning.farbe = KARO;
                    break;
            }
            break;
        case 'P':
            returning.farbe = PIK;
            break;
        case 'H':
            returning.farbe = HERZ;
            break;
        default:
            assert(false && "Invalid Color inputting card");
            break;
    }

    switch(input[2]) {
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
        default:
            assert(false && "Invalid Image inputting card");
            break;
    }

    return returning;
}

enum Karten_Status {
    HAND,
    OUR,
    PLAYED,
};

struct Karte_Status {
    struct Karte karte;
    enum Karten_Status status1, status2;
};

struct Spieler {
    enum Spieler_Status status;
    unsigned char punkte;
};

#define CARD_NUMBER (FARB_NUMBER * BILD_NUMBER)
#define PLAYER_NUMBER 4

struct Spiel {
    struct Karte_Status karten[CARD_NUMBER];
    struct Spieler spieler[PLAYER_NUMBER];
};

void print_spiel(struct Spiel *spiel) {
    for(size_t i = 0; i < PLAYER_NUMBER; i++) {
        switch(spiel->spieler[i].status) {
            case RE:
                printf("Re");
                break;
            case KONTRA:
                printf("Kontra");
                break;
            case UNKNOWN:
                printf("Unknown");
                break;
        }

        printf(" %d\n", spiel->spieler[i].punkte);
    }

    for(size_t i = 0; i < CARD_NUMBER; i++) {
        print_card(&spiel->karten[i].karte);
        printf(" ");

        switch(spiel->karten[i].status1) {
            case HAND:
                printf("Unknown - ");
                break;
            case OUR:
                printf("Our - ");
                break;
            case PLAYED:
                printf("Played - ");
                break;
        }

        switch(spiel->karten[i].status2) {
            case HAND:
                printf("Unknown\n");
                break;
            case OUR:
                printf("Our\n");
                break;
            case PLAYED:
                printf("Played\n");
                break;
        }
    }
}

struct Karte* ALL_CARDS;

const struct Karte Kreuz_Dame = (struct Karte) {
    .farbe = KREUZ,
    .bild = DAME,
};

void init_all_cards() {
    ALL_CARDS = malloc(sizeof(struct Karte) * CARD_NUMBER);

    for(size_t i = 0; i < FARB_NUMBER; i++) {
        for(size_t j = 0; j < FARB_NUMBER; j++) {
            ALL_CARDS[i * FARB_NUMBER + j] = (struct Karte) {
                .farbe = i,
                .bild = j,
            };
        }
    }
}

struct Spiel *standard_spiel(struct Karte *karten) {
    struct Spiel* returning = malloc(sizeof(struct Spiel));

    bool re = false;
    for(size_t i = 0; i < CARD_NUMBER; i++) {

        if(equals(&ALL_CARDS[i], &Kreuz_Dame))
            re = true;

        unsigned char num = 0;
        for(size_t j = 0; j < CARD_NUMBER / 2; j++) {
            if(equals(&ALL_CARDS[i], &karten[j]))
                ++num;

            if(num > 1)
                break;
        }

        returning->karten[i] = (struct Karte_Status) {
            .karte = ALL_CARDS[i],
            .status1 = (num > 0) ? OUR : HAND,
            .status2 = (num > 1) ? OUR : HAND,
        };
    }

    returning->spieler[0] = (struct Spieler) {
        .status = re ? RE : KONTRA,
        .punkte = 0,
    };

    for(size_t i = 1; i < PLAYER_NUMBER; i++) {
        returning->spieler[i] = (struct Spieler) {
            .status = UNKNOWN,
            .punkte = 0,
        };
    }

    return returning;
}

int main(int argc, char** argv) {
    assert(argc == CARD_NUMBER / 2 + 1 && "Wrong number of args");

    init_all_cards();

    struct Karte karten[CARD_NUMBER / 2];

    for(size_t i = 0; i < CARD_NUMBER / 2; i++) {
        karten[i] = get_card(argv[1 + i]);
    }

    struct Spiel *spiel = standard_spiel(karten);

    print_spiel(spiel);

    return 0;
}
