#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning(disable:4996)

struct Masina {
	char* denumire;
	int putere;
};

Masina initMasina(const char* denumire, int putere) {
	Masina m;
	m.denumire = (char*)malloc(sizeof(char)*(strlen(denumire) + 1));
	strcpy(m.denumire, denumire);
	m.putere = putere;

	return m;
}

void afisareMasina(Masina m) {
	printf("masina %s are %d cp", m.denumire, m.putere);
}

struct nodDublu
{
	Masina info;
	nodDublu* next;
	nodDublu* prev;
};

struct LDI {
	nodDublu* first;
	nodDublu* last;
};

nodDublu* creareNodDublu(Masina m, nodDublu* next, nodDublu*prev) {
	nodDublu* nou = (nodDublu*)malloc(sizeof(nodDublu));
	nou->info = initMasina(m.denumire, m.putere);
	nou->next = next;
	nou->prev = prev;
	return nou;
}

LDI inserareInceput(Masina m, LDI lista) {
	nodDublu* nou = creareNodDublu(m, lista.first, NULL);
	if (lista.first) {
		lista.first->prev = nou;
		lista.first = nou;
		return lista;
	}
	else {
		lista.first = nou;
		lista.last = nou;
		return lista;
	}
}

LDI adaugareFinal(Masina m, LDI lista) {
	nodDublu* nou = creareNodDublu(m, NULL, lista.last);
	if (lista.last) {
		lista.last->next = nou;
		lista.last = nou;
		return lista;
	}
	else {
		lista.last = nou;
		lista.first = nou;
		return lista;
	}
}


void afisareListaInceputFinal(LDI lista) {
	nodDublu* temp = lista.first;
	while (temp)
	{
		afisareMasina(temp->info);
		printf("\n");
		temp = temp->next;
	}
}


void stergereLista(LDI *lista) {
	nodDublu * t = lista->first;
	while (t)
	{
		free(t->info.denumire);
		nodDublu * temp = t;
		t = t->next;
		free(temp);
	}
	lista->first = NULL;
	lista->last = NULL;
}

void main() {
	LDI lista;
	//in momentul in care ne am declarat o LDI cei doi pointeri nu sunt initializati
	lista.first = NULL;
	lista.last = NULL;


	Masina masina = initMasina("bmw", 200);
	Masina masina2 = initMasina("audi", 300);
	Masina masina3 = initMasina("mercedes", 100);
	/*lista = inserareInceput(lista, avion);
	lista = inserareInceput(lista, avion2);
	lista = inserareInceput(lista, avion3);*/

	lista = adaugareFinal(masina, lista);
	lista = adaugareFinal(masina2, lista);
	lista = adaugareFinal(masina3, lista);


	afisareListaInceputFinal(lista);
	stergereLista(&lista);
}