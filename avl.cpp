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

		//trebuie tratat cazul in care gradul e diferit de 0, -1 sau 1
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
		//aici daca am facut aceste inserari, exista pericol ca acest arbore
		//daca de exemplu avem nodul 13 apoi 7 apoi 3, dupa ce adaugam 3 si refacem legatura prin rad
		//ar trebui verificat daca mai e echilibrat
		//determinam factorul de balans

		////cand ajungem la 13 de ex, o sa fie 2 
		//if (calculareGradEchilibru(rad) == 2 ) {
		//	//avem dezechilibru de partea stanga -> rotire la dreapta
		//	//vom face o rotire
		//	//sa avem grija sa nu pierdem aceste legaturi


		//	//trebuie avut grija ca sa nu intram in cazul de dubla rotatie
		//	//trebuie calculat si gradul de echilibru al lui y
		//	//daca suntem in cazul de rotire la dreapta, gradul o sa fie 1
		//	//daca e dubla rotire o sa fie -1
		//	if (calculareGradEchilibru(rad->stg) == 1) {
		//		rad = rotireLaDreapta(rad);
		//	}
		//	else {
		//		rad->stg = rotireLaStanga(rad->stg); //se face fix ca in cazul de rotire dreapta dupa apelare
		//		rad = rotireLaDreapta(rad); //direct in x
		//	}

		//}
		//if (calculareGradEchilibru(rad) == -2) {
		//	if (calculareGradEchilibru(rad->dr) == -1) {
		//		rad = rotireLaStanga(rad);
		//	}
		//	else {
		//		rad->dr = rotireLaDreapta(rad->dr);
		//		rad = rotireLaStanga(rad);
		//	}
		//}


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
		//aici inaltime sub arborelui stang si cel drept va fi zero pentru ca e nod frunza -> deci e echilibrat
		nod* nou = (nod*)malloc(sizeof(nod));
		nou->info = a; //shallow copy
		nou->stg = nou->dr = NULL; //nod frunza
		return nou; //daca e sa nu avem arbore, returnam adresa noului nod
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

