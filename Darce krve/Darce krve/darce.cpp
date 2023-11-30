// Jednoducha databaze darcu krve
// Křivánek Filip, Hovořák Jakub

#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <conio.h>
#include "darce.h"


using namespace std;

FILE* darciDB;
FILE* darciDBtemp;

/* Funkce na pridani zaznamu */
void add() {
	system("cls");

	int id;
	char jmeno[21];
	char prijmeni[21];
	char skupina[2];

	darciDB = fopen("darciDB.txt", "a");
	
	printf("------------------\n");
	printf("Zadejte ID darce: ");
	scanf("%d", &id);

	//Zkontroluje, zda se ID = cislu
	if (isdigit(id) != 0) {
		printf("Neplatne ID\nZnovu zadejte ID darce: ");
		scanf("%d", &id);
	}

	printf("Zadejte jmeno darce: ");
	scanf("%s", &jmeno);
	printf("Zadejte prijmeni darce: ");
	scanf("%s", &prijmeni);
	//prida se ID pro darce DODELAT

	//Vepsani do souboru
	fprintf(darciDB, "%d %s %s\n",id, jmeno, prijmeni);

	// Zavre soubor
	fclose(darciDB);
}

/* Funkce na smazani zaznamu */
void del() {
	system("cls");

	int id, id1;
	char jmeno[21], prijmeni[21], skupina[2];

	printf("Zadejte ID darce, ktereho chcete odstranit: ");
	scanf("%d", &id1);

	FILE *darciDB = fopen("darciDB.txt", "r");
	FILE *darciDBtemp = fopen("darciDBtemp.txt", "w");

	while (fscanf(darciDB, "%d %s %s\n", &id, jmeno, prijmeni) != EOF) {
		if (id != id1) {
			fprintf(darciDBtemp, "%d %s %s\n", id, jmeno, prijmeni);
		}
	}
	fclose(darciDB);
	fclose(darciDBtemp);
	remove("darciDB.txt");
	rename("darciDBtemp.txt", "darciDB.txt");
	return;
}

/* Funkce na vypis zaznamu */
void read() {
	system("cls");
	int id;
	char jmeno[21], prijmeni[21], skupina[2];

	//Otevreni souboru v modu "read"
	darciDB = fopen("darciDB.txt", "r");
	
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

	printf("Zadejte ID darce, ktereho chcete upravit: ");
	scanf("%d", &id1);

	FILE* darciDB = fopen("darciDB.txt", "r");
	FILE* darciDBtemp = fopen("darciDBtemp.txt", "w");

	while (fscanf(darciDB, "%d %s %s\n", &id, jmeno, prijmeni) != EOF) {
		if (id = id1) {
			printf("\nCo chcete upravit?");
			printf("\n[1] Jmeno\n[2] Prijmeni");
			scanf("%d", &temp);
			if (temp == 1) {
				printf("Zadejte nove jmeno:");
				scanf("%s", &nove_jmeno);
				fprintf(darciDBtemp, "%d %s %s\n", id, nove_jmeno, prijmeni);
			}
			else if(temp == 2) {
				printf("Zadejte nove prijmeni:");
				scanf("%s", &nove_prijmeni);
				fprintf(darciDBtemp, "%d %s %s\n", id, jmeno, nove_prijmeni);
			}
			else {
				return;
			}
		}
		else {
			fprintf(darciDB, "%d %s %s\n", id, jmeno, prijmeni);
		}
	}

	fclose(darciDB);
	fclose(darciDBtemp);

	remove("darciDB.txt");
	rename("darciDBtemp.txt", "darciDB.txt");
	return;
}

int main()
{
	darciDB = fopen("darciDB.txt", "r");
	char cmd;

	do
	{
		if (darciDB == NULL) {
			printf("Not able to open the file.\nFile created! Try again!");
			darciDB = fopen("darciDB.txt", "a");
			fclose(darciDB);
			return 0;
		}

		system("cls");
		printf("|| Jednoducha databaze darcu krve ||\n");
		printf("------------------\n");
		printf(" [1] Pridat\n [2] Smazat\n [3] Tisk\n [4] Opravit\n [5] Konec\n");
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

	fclose(darciDB);
}
