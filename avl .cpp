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
	for (int i = 0; i < avion.nrLocuriOcupate; i++) {
		fscanf(fisier, "%f", &(avion.preturiBilete[i]));
	}
	return avion;
}


struct nod {
	Avion info;
	nod* stg;
	nod* dr;
};


nod* inserareAvionInArbore(nod* rad, Avion a) {
	//verificam daca avem unde sa inseram
	if (rad) {
		
		if (rad->info.nrLocuri > a.nrLocuri) {
			
			rad->stg = inserareAvionInArbore(rad->stg, a);
		}
		else {
			
			rad->dr = inserareAvionInArbore(rad->dr, a);
			
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

//int maxim;
////varianta 1
//if (inaltimeStanga > inaltimeDreapta) {
//	maxim = inaltimeStanga;
//}
//else {
//	maxim = inaltimeDreapta;
//}
//maxim+=1;
//return maxim; //ptr nivelul curent

int inaltimeArbore(nod* rad) {
	if (rad) {
		int inaltimeStanga = inaltimeArbore(rad->stg);
		int inaltimeDreapta = inaltimeArbore(rad->dr);
		

		return 1 + (inaltimeStanga > inaltimeDreapta ? inaltimeStanga : inaltimeDreapta);
		
	}
	else {
		return 0;
	}
}

nod* rotireLaDreapta(nod*rad) {
	if (rad) {
		nod* aux = rad->stg; // Y-ul
		rad->stg = aux->dr;
		aux->dr = rad;
		return aux;
	}
	else {
		return rad; //adica null
	}
}

nod* rotireLaStanga(nod* rad) {
	if (rad) {
		nod* aux = rad->dr;
		rad->dr = aux->stg;
		aux->stg = rad;
		return rad;
	}
	else {
		return rad;
	}
}


int calculareGradEchilibru(nod* rad) {
	if (rad) {
		int inaltimeStanga = inaltimeArbore(rad->stg);
		int inaltimeDreapta = inaltimeArbore(rad->dr);
		//sau grad de echilibru
		return inaltimeStanga - inaltimeDreapta;
	}
	else {
		return 0;
	}
}
//inserarea intr un ABC echilibrat
nod* inserareAvionInArboreAVL(nod* rad, Avion a) {
	if (rad) {
		
		if (rad->info.nrLocuri > a.nrLocuri) {
		
			rad->stg = inserareAvionInArboreAVL(rad->stg, a);
		}
		else {
			rad->dr = inserareAvionInArboreAVL(rad->dr, a);
		
		}
		
		if (calculareGradEchilibru(rad) == 2) {
			if (calculareGradEchilibru(rad->stg) != 1) {
				rad->stg = rotireLaStanga(rad->stg);
			}
			
			rad = rotireLaDreapta(rad); //direct in x
		}
		if (calculareGradEchilibru(rad) == -2) {
			if (calculareGradEchilibru(rad->dr) != -1) {
				rad->dr = rotireLaDreapta(rad->dr);
			}
			rad = rotireLaStanga(rad);
			
		}
		return rad;
	}
	else {
		nod* nou = (nod*)malloc(sizeof(nod));
		nou->info = a; //shallow copy
		nou->stg = nou->dr = NULL; //nod frunza
		return nou; 
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

	//FILE *fisier = fopen("fisier.txt", "r");
	//if (fisier) {
	//	int nrAvioane = 0;
	//	fscanf(fisier, "%d", &nrAvioane);
	//	for (int i = 0; i < nrAvioane; i++) {
	//		//memoria alocata e in functie
	//		radacina = inserareAvionInArboreAVL(radacina, citireAvionDinFisier(fisier));
	//	}
	//}
	//fclose(fisier);

	//afisareArboreRSD(radacina);
	radacina = inserareAvionInArboreAVL(radacina, initAvion("a330", 30, 3, new float[3]{ 10,20,30 }));
	radacina = inserareAvionInArboreAVL(radacina, initAvion("a340", 40, 2, new float[2]{ 20,30 }));
	radacina = inserareAvionInArboreAVL(radacina, initAvion("b747", 50, 2, new float[2]{ 99,30 }));
	radacina = inserareAvionInArboreAVL(radacina, initAvion("a340", 60, 3, new float[3]{ 88,40,50 }));


	afisareArbore(radacina);

	printf("******************************\n");
	Avion cautat = cautareAvionInArboreDupaNumarLocuri(radacina, 30);
	afisareAvion(cautat);
	free(cautat.model);
	free(cautat.preturiBilete);


	printf("inaltime %d ",inaltimeArbore(radacina));

}

