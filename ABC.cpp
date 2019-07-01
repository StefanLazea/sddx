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

struct nod {
	Avion info;
	nod* stg;
	nod* dr;
};

nod* inserareAvionInArbore(nod* rad, Avion a) {
	if (rad) {
		if (rad->info.nrLocuri > a.nrLocuri) {
			rad->stg = inserareAvionInArbore(rad->stg, a);
		}
		else {
			rad->dr = inserareAvionInArbore(rad->dr, a);
		}
		return rad;
	}
	else {
		nod* nou = (nod*)malloc(sizeof(nod));
		nou->info = initAvion(a.model, a.nrLocuri, a.nrLocuriOcupate, a.preturiBilete);
		nou->stg = nou->dr = NULL;
		return nou;
	}
}

Avion cautareaAvionInArboreDupaNumarLocuri(nod* rad, int nrLocuri) {
	if (rad) {
		if (rad->info.nrLocuri == nrLocuri) {
			Avion a = initAvion(rad->info.model, rad->info.nrLocuri, rad->info.nrLocuriOcupate, rad->info.preturiBilete);
			return a;
		}
		else if(rad->info.nrLocuri > nrLocuri) {
			return cautareaAvionInArboreDupaNumarLocuri(rad->stg, nrLocuri);
		}
		else {
			return cautareaAvionInArboreDupaNumarLocuri(rad->dr, nrLocuri);
		}
	}
	else {
		return initAvion(NULL, -1, -1, NULL);
	}
}
void afisare(nod* rad) {
	if (rad) {
		
		afisare(rad->stg);
		afisareAvion(rad->info);
		afisare(rad->dr);
	}
}
int nrFrunzeClient(nod* rad, const char* denumire, int &nrFrunze) {
	if (rad) {
		nrFrunzeClient(rad->stg, denumire, nrFrunze);
		if (strcmp(rad->info.model, denumire) == 0 && rad->dr == NULL && rad->stg == NULL) {
			nrFrunze++;
			return nrFrunze;
		}
		nrFrunzeClient(rad->dr, denumire, nrFrunze);

	}

}

//float maxPrice(nodArbore* rad, float &max, Car &car) {
//	if (rad) {
//		if (rad->info->price > max) {
//			max = rad->info->price;
//			car = *(rad->info);
//		}
//		return maxPrice(rad->st, max, car) > maxPrice(rad->dr, max, car) ? maxPrice(rad->st, max, car) : maxPrice(rad->dr, max, car);
//	}
//	else {
//		return max;
//	}
//}

void main() {
	nod * radacina = NULL;
	radacina = inserareAvionInArbore(radacina, initAvion("a330", 11, 3, new float[3]{ 10,20,30 }));
	radacina = inserareAvionInArbore(radacina, initAvion("a340", 6, 2, new float[2]{ 20,30 }));
	radacina = inserareAvionInArbore(radacina, initAvion("a350", 8, 2, new float[2]{ 20,30 }));
	radacina = inserareAvionInArbore(radacina, initAvion("a360", 19, 2, new float[2]{ 20,30 }));
	radacina = inserareAvionInArbore(radacina, initAvion("a370", 4, 2, new float[2]{ 20,30 }));
	radacina = inserareAvionInArbore(radacina, initAvion("a380", 10, 2, new float[2]{ 20,30 }));
	radacina = inserareAvionInArbore(radacina, initAvion("a390", 5, 2, new float[2]{ 20,30 }));
	radacina = inserareAvionInArbore(radacina, initAvion("a400", 17, 2, new float[2]{ 20,30 }));
	radacina = inserareAvionInArbore(radacina, initAvion("a410", 43, 2, new float[2]{ 20,30 }));

	afisare(radacina);
	printf("\r\n********************\r\n");
	Avion cautat = cautareaAvionInArboreDupaNumarLocuri(radacina, 6);
	afisareAvion(cautat);

	printf("\r\n********************\r\n");
	const char* nume = "a410";
	int nrFrunze = 0;
	nrFrunzeClient(radacina, nume, nrFrunze);
	printf("%d", nrFrunze);

}