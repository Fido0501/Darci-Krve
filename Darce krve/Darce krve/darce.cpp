﻿// Jednoducha databaze darcu krve
// Křivánek Filip, Hovořák Jakub

#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <windows.h>
#include <time.h>
#include "darce.h"

#define clear() printf("\033[H\033[J")
#define gotoxy(x,y) printf("\033[%d;%dH", (y), (x))

using namespace std;


FILE* darciDB;
FILE* darciDBtemp;

/* Funkce na upozorneni, kteri darci uz muzou darovat znovu (funguje z nejakeho duvodu jen pri spusteni, po pouziti treba vypisu a vraceni se z5 to menu funkce zmizí) */
void ag() {
	time_t t = time(NULL);
	struct tm date = *localtime(&t);

	int id, id1, temp, day = 0, mon = 0, year = 0;
	char jmeno[21], prijmeni[21], skupina[3], datum[10];

	printf("Tito darci z databaze mohou znovu darovat:");
	printf("\nID\t JMENO\t\t PRIJMENI");
	while (fscanf(darciDB, "%d %s %s %s %d-%d-%d\n", &id, jmeno, prijmeni, skupina, &day, &mon, &year) != EOF) {
		temp = (date.tm_mon + 1) - mon;
		if (temp >= 1) {
			printf("\n%d\t %s\t\t %s", id, jmeno, prijmeni);
		}
	}
}

/* Pomocna Funkce na prepsani temp souboru do hlavni databaze */
void tempf() {
	int id, id1, day = 0, mon = 0, year = 0;
	char jmeno[21], prijmeni[21], skupina[3], datum[10];

	darciDB = fopen("darciDB.txt", "w");
	darciDBtemp = fopen("darciDBtemp.txt", "r");

	while (fscanf(darciDBtemp, "%d %s %s %s %d-%d-%d\n", &id, jmeno, prijmeni, skupina, &day, &mon, &year) != EOF) {
		fprintf(darciDB, "%d %s %s %s %d-%d-%d\n", id, jmeno, prijmeni, skupina, datum, day, mon, year);
	}

	fclose(darciDB);
	fclose(darciDBtemp);
}

/* Funkce na pridani zaznamu */
void add() {
	system("cls");

	int id = 1, id1 = 0, temp = 0, day = 0, mon = 0, year = 0;
	char jmeno[21], prijmeni[21], skupina[3], datum[10];

	FILE* darciDB = fopen("darciDB.txt", "a+");

	printf("  _____      _     _       _   \n");
	printf(" |  __ \\    (_)   | |     | |  \n");
	printf(" | |__) | __ _  __| | __ _| |_ \n");
	printf(" |  ___/ '__| |/ _` |/ _` | __|\n");
	printf(" | |   | |  | | (_| | (_| | |_ \n");
	printf(" |_|   |_|  |_|\\__,_|\\__,_|\\__|\n");

	printf("------------------\n");
	while (fscanf(darciDB, "%d %s %s %s %d-%d-%d\n", &id1, jmeno, prijmeni, skupina, &day, &mon, &year) != EOF) {
		id = id + 1;
	}
	printf("Prirazene id darce: %d\n", id);

	// Zadavani informaci od uzivatele
	printf(
		"\nZadejte jmeno darce:\n"
		"+-----------------+\n"
		"|                 |\n"
		"+-----------------+\n"
	);
	gotoxy(3, 12 + temp);
	scanf("%s", &jmeno);

	printf(
		"\nZadejte prijmeni darce:\n"
		"+-----------------+\n"
		"|                 |\n"
		"+-----------------+\n"
	);
	gotoxy(3, 16 + temp);
	scanf("%s", &prijmeni);

	printf(
		"\nZadejte Krevni skupinu darce: [A/B/AB/0]\n"
		"+-----------------+\n"
		"|                 |\n"
		"+-----------------+\n"
	);
	gotoxy(3, 20 + temp);
	scanf("%s", &skupina);
	
	printf(
		"\nZadejte datum posledniho odberu [dd-mm-yyyy]:\n"
		"+-----------------+\n"
		"|                 |\n"
		"+-----------------+\n"
	);
	gotoxy(3, 24 + temp);
	scanf("%d-%d-%d", &day, &mon, &year);

	// Vepsani do souboru bez sortu
	fprintf(darciDB, "%d %s %s %s %d-%d-%d\n", id, jmeno, prijmeni, skupina, day, mon, year);

	// Zavre soubor
	fclose(darciDB);
	getchar();
}


/* Funkce na smazani zaznamu */
void del() {
	system("cls");

	int id, id1, day = 0, mon = 0, year = 0;
	char jmeno[21], prijmeni[21], skupina[3], datum[10];

	printf("   _____                          _   \n");
	printf("  / ____|                        | |  \n");
	printf(" | (___  _ __ ___   __ _ ______ _| |_ \n");
	printf("  \\___ \\| '_ ` _ \\ / _` |_  / _` | __|\n");
	printf("  ____) | | | | | | (_| |/ / (_| | |_ \n");
	printf(" |_____/|_| |_| |_|\\__,_/___\\__,_|\\__|\n");

	printf("------------------\n");
	printf("Zadejte ID darce, ktereho chcete odstranit: ");
	scanf("%d", &id);

	FILE* darciDB = fopen("darciDB.txt", "r");
	FILE* darciDBtemp = fopen("darciDBtemp.txt", "w");

	while (fscanf(darciDB, "%d %s %s %s %d-%d-%d\n", &id1, jmeno, prijmeni, skupina, &day, &mon, &year) != EOF) {
		if (id != id1) {
			fprintf(darciDBtemp, "%d %s %s %s %d-%d-%d\n", id1, jmeno, prijmeni, skupina, day, mon, year);
		}
	}

	fclose(darciDB);
	fclose(darciDBtemp);

	tempf();
	getchar();
	return;
}

/* Funkce na vypis zaznamu */
void read() {
	system("cls");

	int id, day = 0, mon = 0, year = 0;
	char jmeno[21], prijmeni[21], skupina[3], datum[10];

	//Otevreni souboru v modu "read"
	FILE* darciDB = fopen("darciDB.txt", "r");
	
	//Cteni a printeni souboru v tabulce
	printf("\nID\t Jmeno\t\t Prijmeni\t Skupina\t Datum odberu");
	printf("\n______________________________________________________________________");
	while (fscanf(darciDB, "%d %s %s %s %d-%d-%d\n", &id, jmeno, prijmeni, skupina, &day, &mon, &year) != EOF) {
		printf("\n%d\t %s\t\t %s\t\t %s\t\t %d-%d-%d", id, jmeno, prijmeni, skupina, day, mon, year);
	}
	printf("\n\n[Enter pro potvrzeni]");
	getchar();

	// Zavre soubor
	fclose(darciDB);
}

/* Funkce na upravu zaznamu */
void upd() {
	system("cls");

	int id, id1, temp, day = 0, mon = 0, year = 0;
	char jmeno[21], prijmeni[21], skupina[3], datum[10];

	int new_day = 0, new_mon = 0, new_year = 0;
	char nove_jmeno[21], nove_prijmeni[21], nova_skupina[3], nove_datum[10];

	printf("  _    _                       _ _   \n");
	printf(" | |  | |                     (_) |  \n");
	printf(" | |  | |_ __  _ __ __ ___   ___| |_ \n");
	printf(" | |  | | '_ \\| '__/ _` \\ \\ / / | __|\n");
	printf(" | |__| | |_) | | | (_| |\\ V /| | |_ \n");
	printf("  \\____/| .__/|_|  \\__,_| \\_/ |_|\\__|\n");
	printf("        |_|                          \n");

	printf("------------------\n");
	printf("Zadejte ID darce, ktereho chcete upravit: ");
	scanf("%d", &id1);

	FILE* darciDB = fopen("darciDB.txt", "r");
	FILE* darciDBtemp = fopen("darciDBtemp.txt", "w");

	while (fscanf(darciDB, "%d %s %s %s %d-%d-%d\n", &id, jmeno, prijmeni, skupina, &day, &mon, &year) != EOF) {
		if (id == id1) {
			printf("\nCo chcete upravit?");
			printf("\n[1] Jmeno\n[2] Prijmeni\n[3] Skupina\n[4] Datum\n");
			scanf("%d", &temp);
			if (temp == 1) {
				printf("Zadejte nove jmeno: ");
				scanf("%s", &nove_jmeno);
				fprintf(darciDBtemp, "%d %s %s %s %d-%d-%d\n", id, nove_jmeno, prijmeni, skupina, day, mon, year);
			}
			else if(temp == 2) {
				printf("Zadejte nove prijmeni: ");
				scanf("%s", &nove_prijmeni);
				fprintf(darciDBtemp, "%d %s %s %s %d-%d-%d\n", id, jmeno, nove_prijmeni, skupina, day, mon, year);
			}
			else if (temp == 3) {
				printf("Zadejte novou skupinu: [A/B/AB/B0] ");
				scanf("%s", &nova_skupina);
				fprintf(darciDBtemp, "%d %s %s %s %d-%d-%d\n", id, jmeno, prijmeni, nova_skupina, day, mon, year);
			}
			else if (temp == 4) {
				printf("Zadejte nove datum: [dd-mm-yyyy]");
				scanf("%d-%d-%d", &new_day, &new_mon, &new_year);
				fprintf(darciDBtemp, "%d %s %s %s %d-%d-%d\n", id, jmeno, prijmeni, skupina, new_day, new_mon, new_year);
			}
			else {
				return;
			}
		}
		else {
			fprintf(darciDBtemp, "%d %s %s %s %d-%d-%d\n", id, jmeno, prijmeni, skupina, day, mon, year);
		}
	}

	fclose(darciDB);
	fclose(darciDBtemp);

	tempf();
	getchar();
	return;
}

/* Funkce Main */
int main()
{
	darciDB = fopen("darciDB.txt", "r");

	int id, id1, temp, day = 0, mon = 0, year = 0;
	char cmd, jmeno[21], prijmeni[21], skupina[3], datum[10];

	time_t t = time(NULL);
	struct tm date = *localtime(&t);

	if (darciDB == NULL) {
		MessageBeep(MB_ICONWARNING);
		printf("Nepodarilo se otevrít soubor\nSoubor byl vytvoren\n");
		darciDB = fopen("darciDB.txt", "a");
		fclose(darciDB);
		return 0;
	}

	do
	{
		system("cls");

		printf("  _____        _        _                         _                        _                   \n");
		printf(" |  __ \\      | |      | |                       | |                      | |                  \n");
		printf(" | |  | | __ _| |_ __ _| |__   __ _ _______    __| | __ _ _ __ ___ _   _  | | ___ ____   _____ \n");
		printf(" | |  | |/ _` | __/ _` | '_ \\ / _` |_  / _ \\  / _` |/ _` | '__/ __| | | | | |/ / '__\\ \\ / / _ \\ \n");
		printf(" | |__| | (_| | || (_| | |_) | (_| |/ /  __/ | (_| | (_| | | | (__| |_| | |   <| |   \\ V /  __/\n");
		printf(" |_____/ \\__,_|\\__\\__,_|_.__/ \\__,_/___\\___|  \\__,_|\\__,_|_|  \\___|\\__,_| |_|\\_\\_|    \\_/ \\___|\n");

		printf("------------------\n");
		printf("[1] Pridat\n[2] Smazat\n[3] Tisk\n[4] Upravit\n[5] Konec\n");
		printf("------------------\n");
		
		printf("\n\n\n------------------\n");
		printf("Dnesni datum: %02d-%02d-%d\n\n", date.tm_mday, date.tm_mon + 1, date.tm_year + 1900);

		// Ti co mohou znovu darovat
		ag();
		printf("\n------------------\n");
		gotoxy(3, 15);

		cmd = tolower(getchar());
		while (getchar() != '\n');

		switch (cmd) {
		case '1':
			add();
			break;
		case '2':
			del();
			break;
		case '3':
			read();
			break;
		case '4':
			upd();
			break;
		}
	} while (cmd != '5');
	gotoxy(1, 25);
	fclose(darciDB);
}
