#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

typedef struct {
    char nom[50];
    char prenom[50];
    char telephone[15];
    int age;
    int statut;
    int reference;
    char date[11];
} Reservation;

Reservation RDV[100] = {
    {"kamal", "mohamed", "0655983456", 30, 1, 1, "2024-10-01"},
    {"alami", "khadija", "0752345489", 25, 3, 2, "2024-10-02"},
    {"monadi", "hassan", "0698742589", 45, 1, 3, "2024-10-03"},
    {"nadif", "marwa", "0662147954", 60, 4, 4, "2024-10-04"},
    {"jawhari", "Mouad", "0662181890", 22, 1, 5, "2024-10-05"},
    {"meftah", "aya", "0615479632", 16, 2, 6, "2024-10-06"},
    {"moutaraji", "Omar", "0613467920", 27, 3, 7, "2024-10-07"},
    {"falouh", "oussama", "0601987461", 37, 4, 8, "2024-10-08"},
    {"sadik", "Youssef", "061564845", 41, 2, 9, "2024-10-09"},
    {"hadioui", "hiba", "0749325549", 17, 3, 10, "2024-10-10"},
};

int compteur = 10;

bool validertelephone(char telephone[15]) {
    return strlen(telephone) == 10 && strspn(telephone, "0123456789") == 10;
}

bool Datevalide(char date[11]) {
    int annee, mois, jour ;
    sscanf(date ,"%d-%d-%d", &annee, &mois, &jour);

    if (mois < 1 || mois > 12 || jour < 1 || jour > 31) return false;

    int joursParMois[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if ((annee % 4 == 0 && annee % 100 != 0) || (annee % 400 == 0)) {
        joursParMois[2] = 29;
    }

    return jour <= joursParMois[mois];
}

void ajouter() {
    if (compteur >= 100) {
        printf("La memoire est pleine, impossible d'ajouter une nouvelle reservation.\n");
        return;
    }

    Reservation r;
    printf("Nom : ");
    scanf("%s", r.nom);
    printf("Prenom : ");
    scanf("%s", r.prenom);

    do {
        printf("Telephone (10 chiffres) : ");
        scanf("%s", r.telephone);
        if (!validerTelephone(r.telephone)) {
            printf("Numero de telephone invalide, veuillez reessayer.\n");
        }
    } while (!validerTelephone(r.telephone));

    printf("Age : ");
    scanf("%d", &r.age);
    printf("Statut (1-valide, 2-reporte, 3-annule, 4-traite) : ");
    scanf("%d", &r.statut);
    r.reference = compteur + 1;

    do {
        printf("Date de reservation (YYYY-MM-DD) : ");
        scanf("%s", r.date);
        if (!estDateValide(r.date)) {
            printf("Date invalide, veuillez reessayer.\n");
        }
    } while (!estDateValide(r.date));

    RDV[compteur] = r;
    compteur++;
    printf("Reservation ajoutee avec succes.\n");
}

void modifier() {
    int ref;
    printf("Entrez la reference de la reservation a modifier : ");
    scanf("%d", &ref);
    bool exist = false;

    for (int i = 0; i < compteur; i++) {
        if (RDV[i].reference == ref) {
            exist = true;
            printf("Modifier le Nom (%s) : ", RDV[i].nom);
            scanf("%s", RDV[i].nom);
            printf("Modifier le Prenom (%s) : ", RDV[i].prenom);
            scanf("%s", RDV[i].prenom);

            do {
                printf("Modifier le Telephone (%s) : ", RDV[i].telephone);
                scanf("%s", RDV[i].telephone);
                if (!validerTelephone(RDV[i].telephone)) {
                    printf("Numero de telephone invalide, veuillez reessayer.\n");
                }
            } while (!validerTelephone(RDV[i].telephone));

            printf("Modifier l'Age (%d) : ", RDV[i].age);
            scanf("%d", &RDV[i].age);
            printf("Modifier le Statut (%d) : ", RDV[i].statut);
            scanf("%d", &RDV[i].statut);

            do {
                printf("Modifier la Date (%s) : ", RDV[i].date);
                scanf("%s", RDV[i].date);
                if (!estDateValide(RDV[i].date)) {
                    printf("Date invalide, veuillez reessayer.\n");
                }
            } while (!estDateValide(RDV[i].date));

            printf("Reservation modifiee avec succes.\n");
            break;
        }
    }
    if (!exist) {
        printf("Reservation non trouvee.\n");
    }
}

void supprimer() {
    int ref;
    printf("Entrez la reference de la reservation a supprimer : ");
    scanf("%d", &ref);
    bool exist = false;

    for (int i = 0; i < compteur; i++) {
        if (RDV[i].reference == ref) {
            exist = true;
            for (int j = i; j < compteur - 1; j++) {
                RDV[j] = RDV[j + 1];
            }
            compteur--;
            printf("Reservation supprimee avec succes.\n");
            break;
        }
    }
    if (!exist) {
        printf("Reservation non trouvee.\n");
    }
}

void afficher() {
    printf("\n             Liste des Reservations                \n\n");
    printf("| %-10s | %-15s | %-15s | %-5s | %-10s | %-13s | %-10s |\n",
           "Reference", "Nom", "Prenom", "Age", "Statut", "Telephone", "Date");
    printf("+------------+-----------------+-----------------+-------+------------+---------------+------------+\n");

    for (int i = 0; i < compteur; i++) {
        printf("| %-10d | %-15s | %-15s | %-5d | %-10d | %-13s | %-10s |\n",
               RDV[i].reference, RDV[i].nom, RDV[i].prenom, RDV[i].age, RDV[i].statut, RDV[i].telephone,
               RDV[i].date);
    }
    printf("+------------+-----------------+-----------------+-------+------------+---------------+------------+\n");
}

void trier() {
    int choixTri;
    printf("Choisissez le critère de tri:\n");
    printf("1 - Trier par nom\n");
    printf("2 - Trier par statut\n");
    printf("Taper votre choix : ");
    scanf("%d", &choixTri);

    if (choixTri == 1) {
        for (int i = 0; i < compteur - 1; i++) {
            for (int j = 0; j < compteur - 1 - i; j++) {
                if (strcmp(RDV[j].nom, RDV[j + 1].nom) > 0) {
                    Reservation temp = RDV[j];
                    RDV[j] = RDV[j + 1];
                    RDV[j + 1] = temp;
                }
            }
        }
        printf("Reservations triees par nom.\n");
    } else if (choixTri == 2) {
        for (int i = 0; i < compteur - 1; i++) {
            for (int j = 0; j < compteur - 1 - i; j++) {
                if (RDV[j].statut > RDV[j + 1].statut) {
                    Reservation temp = RDV[j];
                    RDV[j] = RDV[j + 1];
                    RDV[j + 1] = temp;
                }
            }
        }
        printf("Reservations triees par statut.\n");
    } else {
        printf("Choix invalide !\n");
    }
}

void rechercher() {
    int choixRecherche;
    printf("Choisissez le critère de recherche:\n");
    printf("1 - Recherche par référence\n");
    printf("2 - Recherche par nom\n");
    printf("3 - Recherche par date\n");
    printf("Taper votre choix : ");
    scanf("%d", &choixRecherche);

    switch (choixRecherche) {
        case 1: {
            int ref;
            printf("Entrez la référence à rechercher : ");
            scanf("%d", &ref);
            bool found = false;
            for (int i = 0; i < compteur; i++) {
                if (RDV[i].reference == ref) {
                    printf("Reservation trouvée : Nom: %s, Prenom: %s, Telephone: %s, Age: %d, Statut: %d, Date: %s\n",
                           RDV[i].nom, RDV[i].prenom, RDV[i].telephone, RDV[i].age, RDV[i].statut, RDV[i].date);
                    found = true;
                    break;
                }
            }
            if (!found) {
                printf("Reservation non trouvée.\n");
            }
            break;
        }
        case 2: {
            char nom[50];
            printf("Entrez le nom à rechercher : ");
            scanf("%s", nom);
            bool found = false;
            for (int i = 0; i < compteur; i++) {
                if (strcmp(RDV[i].nom, nom) == 0) {
                    printf("Reservation trouvée : Nom: %s, Prenom: %s, Telephone: %s, Age: %d, Statut: %d, Date: %s\n",
                           RDV[i].nom, RDV[i].prenom, RDV[i].telephone, RDV[i].age, RDV[i].statut, RDV[i].date);
                    found = true;
                }
            }
            if (!found) {
                printf("Reservation non trouvée.\n");
            }
            break;
        }
        case 3: {
            char date[11];
            printf("Entrez la date à rechercher (YYYY-MM-DD) : ");
            scanf("%s", date);
            bool found = false;
            for (int i = 0; i < compteur; i++) {
                if (strcmp(RDV[i].date, date) == 0) {
                    printf("Reservation trouvée : Nom: %s, Prenom: %s, Telephone: %s, Age: %d, Statut: %d, Date: %s\n",
                           RDV[i].nom, RDV[i].prenom, RDV[i].telephone, RDV[i].age, RDV[i].statut, RDV[i].date);
                    found = true;
                }
            }
            if (!found) {
                printf("Reservation non trouvée.\n");
            }
            break;
        }
        default:
            printf("Choix invalide.\n");
            break;
    }
}

int main() {
    int choix;
    do {
        printf("\n      Menu Principal:\n");
        printf("1. Ajouter une reservation\n");
        printf("2. Modifier une reservation\n");
        printf("3. Supprimer une reservation\n");
        printf("4. Afficher les reservations\n");
        printf("5. Trier les reservations\n");
        printf("6. Rechercher une reservation\n");
        printf("7. Quitter\n");
        printf("Taper votre choix : ");
        scanf("%d", &choix);

        switch (choix) {
            case 1:
                ajouter();
                break;
            case 2:
                modifier();
                break;
            case 3:
                supprimer();
                break;
            case 4:
                afficher();
                break;
            case 5:
                trier();
                break;
            case 6:
                rechercher();
                break;
            case 7:
                printf("Au revoir !\n");
                break;
            default:
                printf("Choix invalide !\n");
                break;
        }
    } while (choix != 8);

    return 0;
}
