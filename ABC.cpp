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

//structura unui arbore binar (de cautare)
struct nod {
	Avion info;
	nod* stg;
	nod* dr;
};
//pentru fiecare nod informatia este complexa
//trebuie respectata regula ca ce e in stanga sa fie mai mic ca in dreapta
//deci putem pentru structura avion, cheia de comparare sa fie nrLocuri
//radacina 

//cand inseram un nou nod in arbore, obligatoriu el va fi un nod frunza
//min 34

nod* inserareAvionInArbore(nod* rad, Avion a) {
	//verificam daca avem unde sa inseram
	if (rad) {
		//am arbore; deci am informatii in radacina
		//compar pe avion cu cea am in radacina
		if (rad->info.nrLocuri > a.nrLocuri) {
			//cum noi trebuie in stanga sa avem noduri mai mici ca in dreapta
			//si daca a.nrlocuri este 7 si rad.nrlocuri este 8; trebuie sa punem noul avion/nod in stanga radacinei
			//ne folosim de recursivitate 

			//in momentul cand apelam, ne va returna adresa arborelui/ nodului radacine pentru arborele in care a facut inserarea
			//deci sa pun in stanga
			rad->stg = inserareAvionInArbore(rad->stg, a);
		}
		else {
			//e fix situatia in care dupa ce ajungem in 3, 7 este mai mare
			rad->dr = inserareAvionInArbore(rad->dr, a);
			//dupa se duce si compara cu 5 si vrea sa insereze tot in dreapta; dar este un nod null
			//se iese din if=ul mare
		}
		return rad; //ca sa se refaca aceasta legatura pana la acea inserare
	}
	else {
		nod* nou = (nod*)malloc(sizeof(nod)); 
		nou->info = a; //shallow copy
		//deci cand vom insera un nou nod, va fi un nod frunza
		nou->stg = nou->dr = NULL;
		return nou; //daca e sa nu avem arbore, returnam adresa noului nod
	}

}

//preordine - RSD
//inordine - SRD
//postordin - SDR


void afisareArbore(nod* rad) {
	//daca nu avem rad, mue
	//inordine
	if (rad) {
		//mai intai prima oara afisam stanga
		//divide et impera - prima oara afisam stanga, apoi radacina, apoi dreapta
		afisareArbore(rad->stg);
		afisareAvion(rad->info); //afisam radacina
		afisareArbore(rad->dr);
	}
}


void afisareArboreRSD(nod* rad) {
	//daca nu avem rad, mue
	//inordine
	if (rad) {
		//mai intai prima oara afisam stanga
		//divide et impera - prima oara afisam stanga, apoi radacina, apoi dreapta
		afisareAvion(rad->info); //afisam radacina
		afisareArbore(rad->stg);
		afisareArbore(rad->dr);
	}
}

void afisareArboreSDR(nod* rad) {
	//daca nu avem rad, mue
	//inordine
	if (rad) {
		//mai intai prima oara afisam stanga
		//divide et impera - prima oara afisam stanga, apoi radacina, apoi dreapta
		afisareArbore(rad->stg);
		afisareArbore(rad->dr);
		afisareAvion(rad->info); //afisam radacina

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

