// Darce krve.cpp: Definuje vstupní bod pro aplikaci.
//

#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <conio.h>
#include "darce.h"


using namespace std;

FILE* darciDB;
char myString[100];

struct t_darce;
struct t_darce
{
	int ID; // ID darce
	char jmeno[21]; // Jmeno darce
	char prijmeni[21]; // Prijmeni darce
	int datum_odberu; // Datum odberu jednotlivych darcu
} darce;

void add() {
	darciDB = fopen("C:\\Users\\Filda\\Desktop\\Darce krve\\darciDB.txt", "a");

	system("cls");
	printf("------------------\n");
	printf("Zadejte jmeno darce: ");
	scanf("%s", &darce.jmeno);
	printf("Zadejte prijmeni darce: ");
	scanf("%s", &darce.prijmeni);
	printf("[Enter pro potvrzeni]");
	getchar();

	//prida se ID pro darce DODELAT
	darce.ID = darce.ID + 1;


	//pridat(darce.jmeno, darce.prijmeni)
	fprintf(darciDB, "%d %s %s %s\n",darce.ID, darce.jmeno, darce.prijmeni, darce.prijmeni);

	// Zavre soubor
	fclose(darciDB);
}

void del() {

}

void read() {
	system("cls");
	char ch[100];

	//Otevreni souboru v modu "read"
	darciDB = fopen("C:\\Users\\Filda\\Desktop\\Darce krve\\darciDB.txt", "r");




	//Cteni a printeni souboru
	while (fscanf(darciDB, "%*s %s %*s ", ch) == 1)
		printf("%s\n", ch);
	
	printf("[Enter pro potvrzeni]");
	getchar();






	// Zavre soubor
	fclose(darciDB);
}

int main()
{
	darciDB = fopen("C:\\Users\\Filda\\Desktop\\Darce krve\\darciDB.txt", "r");
	char ch;

	/*do {
		ch = fgetc(darciDB);
		if (isdigit(ch)) {

		}
	} while (ch != EOF);*/

	char cmd;

	do
	{
		if (darciDB == NULL) {
			printf("Not able to open the file.");
			return 0;
		}

		system("cls");
		printf("------------------\n");
		printf("[1] Pridat\n[2] Smazat\n[3] Tisk\n[4] Konec\n");
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
		}
	} while (cmd != '4');

	fclose(darciDB);
	return 0;
}
