#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning(disable:4996)


//lsi

struct Fruct {
	char* denumire;
	int pret;
};

struct nod {
	Fruct info;
	nod* next;
};

Fruct initFruct(const char* denumire, int pret) {
	Fruct f;
	f.denumire = (char*)malloc(sizeof(char)*(strlen(denumire) + 1));
	strcpy(f.denumire, denumire);
	f.pret = pret;
	return f;
}

void afisareFruct(Fruct f) {
	printf("fructul %s costa %d", f.denumire, f.pret);
}

nod* creeareNod(Fruct f, nod* urm) {
	nod* nou = (nod*)malloc(sizeof(nod));
	nou->info = initFruct(f.denumire, f.pret);
	nou->next = urm;
	return nou;	 
}

nod* adaugareFinal(Fruct f, nod* cap) {
	if (cap) {
		nod* temp = cap;
		while (temp->next) {
			temp = temp->next;
		}
		temp->next = creeareNod(f, NULL);
		return cap;
	}
	else {
		return creeareNod(f, NULL);
	}
}

nod* stergereLista(nod* cap) {
	while (cap) {
		free(cap->info.denumire);
		nod* temp = cap;
		free(temp);
		cap = cap->next;
	}
	return NULL;
}

void afisareLSI(nod* cap) {
	while (cap) {
		afisareFruct(cap->info);
		printf("\n");
		cap = cap->next;
	}
}



void main() {
	nod* lista = NULL;

	lista = creeareNod(initFruct("banana", 30), lista);
	lista = creeareNod(initFruct("mar", 90), lista);
	lista = creeareNod(initFruct("para", 10), lista);
	afisareLSI(lista);


	printf("\n******************\n");
	nod* lista2 = NULL;
	lista2 = adaugareFinal(initFruct("banana", 30), lista2);
	lista2 = adaugareFinal(initFruct("mar", 10), lista2);
	lista2 = adaugareFinal(initFruct("par", 22), lista2);
	afisareLSI(lista2);


}
