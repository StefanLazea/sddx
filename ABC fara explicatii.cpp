#include <stdio.h>
#include <malloc.h>
#include <string.h>

#pragma warning(disable:4996)
struct Avion {
	char* model;
	int nrLocuri;
	int nrLocuriOcupate;
	float * preturiBilete; //va avea lungimea de nrlocuriocupate; in ordine
};

Avion initAvion(const char*model, int nrLocuri, int nrLocuriOcupate, float* preturiBilete) {
	Avion avion;
	avion.model = (char*)malloc(sizeof(char)*(strlen(model) + 1));
	strcpy(avion.model, model);
	avion.nrLocuri = nrLocuri;
	avion.nrLocuriOcupate = nrLocuriOcupate;
	avion.preturiBilete = (float*)malloc(sizeof(float)*nrLocuriOcupate);
	for (int i = 0; i < nrLocuriOcupate; i++) {
		avion.preturiBilete[i] = preturiBilete[i];
	}
	return avion;
}
void afisareAvion(Avion a) {
	printf("avion %s are %d locuri, din care %d ocupate:\r\n", a.model, a.nrLocuri, a.nrLocuriOcupate);
	for (int i = 0; i < a.nrLocuriOcupate; i++) {
		printf("locul %d costa %5.2f", i + 1, a.preturiBilete[i]);
		printf("\r\n");
	}
	printf("\r\n");
}

Avion citireAvionDinFisier(FILE* fisier) {
	Avion avion;
	char buffer[20]; //alocat static
	fscanf(fisier, "%s", buffer);
	avion.model = (char*)malloc(sizeof(char)*(strlen(buffer) + 1));
	strcpy(avion.model, buffer);
	fscanf(fisier, "%d", &avion.nrLocuri);
	fscanf(fisier, "%d", &avion.nrLocuriOcupate);
	avion.preturiBilete = (float*)malloc(sizeof(float*)*avion.nrLocuriOcupate);
	for (int i = 0; i < avion.nrLocuriOcupate;i++) {
		fscanf(fisier, "%f", &(avion.preturiBilete[i]));
	}
	return avion;
}

struct nod {
	Avion info;
	nod * stg;
	nod * dr;
};

nod* inserareAvionInArbore(nod* rad, Avion a) {
	if (rad) {
		if (rad->info.nrLocuri > a.nrLocuri) {
			rad->stg = inserareAvionInArbore(rad->stg, a);
		}
		else {
			rad->dr = inserareAvionInArbore(rad->dr, a);
		}
		return rad; //sa se refaca legaturile
	}

	else {
		//frunza 
		nod * nou = (nod*)malloc(sizeof(nod));
		nou->info = a;
		nou->stg = nou->dr = NULL;
		return nou;

	}
}

void afisareArbore(nod *rad) {
	if (rad) {
		afisareArbore(rad->stg);
		afisareAvion(rad->info);
		afisareArbore(rad->dr);
	}
}

//cautarea e usoara; pentru ca arborele ca imparti informatia in bucati (subarbori)
Avion cautareAvionInArboreDupaNumarLocuri(nod* rad, int nrLocuri) {
	if (rad) {
		if (rad->info.nrLocuri == nrLocuri) {
			Avion a = initAvion(rad->info.model, rad->info.nrLocuri, rad->info.nrLocuriOcupate, rad->info.preturiBilete); //deepcopy
			return a; 
		}
		else if (rad->info.nrLocuri > nrLocuri) {
			//nodul radacina ar fi 8 si noi cautam 3, care dupa regula se va afla in stanga
			return cautareAvionInArboreDupaNumarLocuri(rad->stg, nrLocuri);
		}
		else {
			return cautareAvionInArboreDupaNumarLocuri(rad->dr, nrLocuri);
		}
	}
	else {
		return initAvion("", -1, -1, NULL);
	}
}

void main()
{
	/*Avion a = initAvion("airbus a330", 200, 3, new float[3] {10, 20, 30});
	afisareAvion(a);

	FILE *fisier = fopen("fisier.txt", "r");
	int nrAvioane = 0;
	if (fisier) {
		fscanf(fisier, "%d", &nrAvioane);
		for (int i = 0; i < nrAvioane; i++) {
			Avion a = citireAvionDinFisier(fisier);
			afisareAvion(a);
		}
	}
	fclose(fisier);*/

	nod * radacina = NULL; //arborele e identificat prin radacina
	//arborele e gol

	FILE *fisier = fopen("fisier.txt", "r");
	if (fisier) {
		int nrAvioane = 0;
		fscanf(fisier, "%d", &nrAvioane);
		for (int i = 0; i < nrAvioane; i++) {
			//memoria alocata e in functie
			radacina = inserareAvionInArbore(radacina, citireAvionDinFisier(fisier));
		}
	}
	fclose(fisier);

	//afisareArboreRSD(radacina);

	afisareArbore(radacina);

	printf("******************************\n");
	Avion cautat = cautareAvionInArboreDupaNumarLocuri(radacina, 30);
	afisareAvion(cautat);
	free(cautat.model);
	free(cautat.preturiBilete);
	
}

