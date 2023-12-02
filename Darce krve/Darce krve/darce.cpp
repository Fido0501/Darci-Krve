// Jednoducha databaze darcu krve
// Křivánek Filip, Hovořák Jakub

#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <windows.h>
#include <ctime>
#include "darce.h"

#define clear() printf("\033[H\033[J")
#define gotoxy(x,y) printf("\033[%d;%dH", (y), (x))

using namespace std;


FILE* darciDB;
FILE* darciDBtemp;

/* Pomocna Funkce na prepsani temp souboru do hlavni databaze */
void tempf() {
	int id, id1;
	char jmeno[21], prijmeni[21], skupina[2];

	darciDB = fopen("darciDB.txt", "w");
	darciDBtemp = fopen("darciDBtemp.txt", "r");

	while (fscanf(darciDBtemp, "%d %s %s\n", &id, jmeno, prijmeni) != EOF) {
		fprintf(darciDB, "%d %s %s\n", id, jmeno, prijmeni);
	}

	fclose(darciDB);
	fclose(darciDBtemp);
}

/* Funkce na pridani zaznamu */
void add() {
	system("cls");

	int id, id1;
	int temp = 0;
	char jmeno[21];
	char prijmeni[21];
	char skupina[2];
	

	FILE* darciDB = fopen("darciDB.txt", "a+");
	
	printf("  _____      _     _       _   \n");
	printf(" |  __ \\    (_)   | |     | |  \n");
	printf(" | |__) | __ _  __| | __ _| |_ \n");
	printf(" |  ___/ '__| |/ _` |/ _` | __|\n");
	printf(" | |   | |  | | (_| | (_| | |_ \n");
	printf(" |_|   |_|  |_|\\__,_|\\__,_|\\__|\n");

	printf("------------------\n");
	printf("Zadejte ID darce: ");
	scanf("%d", &id);

	//Zkontroluje, zda se ID = cislu a zda ID uz neexistuje
	while (fscanf(darciDB, "%d %s %s\n", &id1, jmeno, prijmeni) != EOF) {
		if (id == id1) {
			MessageBeep(MB_ICONWARNING);
			printf("ID je neplatne nebo jiz existuje\nZnovu zadejte ID darce: ");
			scanf("%d", &id);
			fseek(darciDB, 0, SEEK_SET);
			temp = temp + 2;
		}
	}


	// Zadavani informaci od uzivatele
	printf(
		"\nZadejte jmeno darce:\n"
		"+-----------------+\n"
		"|                 |\n" 
		"+-----------------+\n"
	);
	gotoxy(3,12+temp);
	scanf("%s", &jmeno);

	printf(
		"\nZadejte prijmeni darce:\n"
		"+-----------------+\n"
		"|                 |\n"
		"+-----------------+\n"
	);
	gotoxy(3, 16+temp);
	scanf("%s", &prijmeni);


	// Vepsani do souboru podle id - negunguje

	/*while (fscanf(darciDB, "%d %s %s\n", &id1, jmeno, prijmeni) != EOF) {
		if (id > id1) {
			fprintf(darciDB, "%d %s %s\n", id, jmeno, prijmeni);
			id1 = id1 + 1;
		} else {
			fprintf(darciDB, "%d %s %s\n", id, jmeno, prijmeni);
		}
	}*/

	// Vepsani do souboru
	fprintf(darciDB, "%d %s %s\n", id, jmeno, prijmeni);

	// Zavre soubor
	fclose(darciDB);
	getchar();
}

/* Funkce na smazani zaznamu */
void del() {
	system("cls");

	int id, id1;
	char jmeno[21], prijmeni[21], skupina[2];

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

	while (fscanf(darciDB, "%d %s %s\n", &id1, jmeno, prijmeni) != EOF) {
		if (id != id1) {
			fprintf(darciDBtemp, "%d %s %s\n", id1, jmeno, prijmeni);
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
	int id;
	char jmeno[21], prijmeni[21], skupina[2];

	//Otevreni souboru v modu "read"
	FILE* darciDB = fopen("darciDB.txt", "r");
	
	//Cteni a printeni souboru v tabulce
	printf("\nID\t Jmeno\t\t Prijmeni\t Skupina\t Datum odberu");
	printf("\n______________________________________________________________________");
	while (fscanf(darciDB, "%d %s %s\n", &id, jmeno, prijmeni) != EOF) {
		printf("\n%d\t %s\t\t %s", id, jmeno, prijmeni);
	}
	printf("\n\n[Enter pro potvrzeni]");
	getchar();

	// Zavre soubor
	fclose(darciDB);
}

/* Funkce na upravu zaznamu */
void upd() {
	system("cls");

	int id, id1, temp;
	char jmeno[21], prijmeni[21], skupina[2];
	char nove_jmeno[21], nove_prijmeni[21], nova_skupina[2];

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

	while (fscanf(darciDB, "%d %s %s\n", &id, jmeno, prijmeni) != EOF) {
		if (id == id1) {
			printf("\nCo chcete upravit?");
			printf("\n[1] Jmeno\n[2] Prijmeni\n");
			scanf("%d", &temp);
			if (temp == 1) {
				printf("Zadejte nove jmeno: ");
				scanf("%s", &nove_jmeno);
				fprintf(darciDBtemp, "%d %s %s\n", id, nove_jmeno, prijmeni);
			}
			else if(temp == 2) {
				printf("Zadejte nove prijmeni: ");
				scanf("%s", &nove_prijmeni);
				fprintf(darciDBtemp, "%d %s %s\n", id, jmeno, nove_prijmeni);
			}
			else {
				return;
			}
		}
		else {
			fprintf(darciDBtemp, "%d %s %s\n", id, jmeno, prijmeni);
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
	char cmd;

	if (darciDB == NULL) {
		MessageBeep(MB_ICONWARNING);
		printf("\t\t\t\t\tNepodařilo se otevřít soubor\nSoubor byl vytvořen\n");
		darciDB = fopen("darciDB.txt", "a");
		fclose(darciDB);
		return 0;
	}

	//fclose(darciDB);

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
}
