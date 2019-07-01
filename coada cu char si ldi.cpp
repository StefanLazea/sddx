#include <stdlib.h>
#include <stdio.h>
#pragma warning(disable:4996)
#include <string.h>


struct Comanda
{
	int cod;
	char* nume;
	int numarProduse;
	char** produse;
	float suma;
};

struct nod {
	Comanda info;
	nod* next;
};

Comanda initComanda(int cod, const char* nume, int numarProduse, char** produse, float suma) {
	Comanda c;
	c.cod = cod;
	c.nume = (char*)malloc(sizeof(char)*(strlen(nume) + 1));
	strcpy(c.nume, nume);
	c.numarProduse = numarProduse;
	c.produse = (char**)malloc(sizeof(char*)*numarProduse);

	for (int i = 0; i < numarProduse; i++){
		c.produse[i] = (char*)malloc(sizeof(char)*(strlen(produse[i]) + 1));
	}

	for (int i = 0; i < numarProduse; i++) {
		strcpy(c.produse[i], produse[i]);
	}

	c.suma = suma;
	return c;
}

nod* adaugareInceput(nod* cap, Comanda c) {
	nod* nou = (nod*)malloc(sizeof(nod));
	nou->next = cap;
	nou->info = initComanda(c.cod, c.nume, c.numarProduse, c.produse, c.suma);
	return nou; //se realizeaza legatura prin apel 
}

nod* adaugareFinal(nod*cap, Comanda c) {
	if (cap) {
		nod* t = cap;
		while (t->next) {
			t = t->next;
		}
		t->next = adaugareInceput(NULL, c); //ptr ca trebuie ca next sa duca la null
		return cap; //returnez lista
	}
	else {
		return adaugareInceput(NULL, c);
	}
}

nod* pushStack(nod* stack, Comanda c) {
	stack = adaugareInceput(stack, c);
	return stack;
}
nod* pushQueue(nod* queue, Comanda c) {
	queue = adaugareFinal(queue, c);
	return queue;
}

Comanda popQueue(nod* &cap) {
	if (cap) {
		Comanda rez = initComanda(cap->info.cod, cap->info.nume, cap->info.numarProduse, cap->info.produse, cap->info.suma);
		nod*temp = cap;
		cap = cap->next;
		free(temp->info.nume);
		for (int i = 0; i < temp->info.numarProduse; i++) {
			free(temp->info.produse[i]);
		}
		free(temp->info.produse);

		free(temp);
		return rez;
	}
	else {
		return initComanda(-1, NULL, -1, NULL, -1);
	}
}


Comanda popStack(nod* &cap) {
	if (cap) {
		Comanda rez = initComanda(cap->info.cod, cap->info.nume, cap->info.numarProduse, cap->info.produse, cap->info.suma);
		nod* temp = cap;
		cap = cap->next;
		free(temp->info.nume);
		for (int i = 0; i < temp->info.numarProduse; i++) {
			free(temp->info.produse[i]);
		}
		free(temp->info.produse);

		free(temp);
		return rez;
	}
	else {
		return initComanda(-1, NULL, -1, NULL, -1);
	}
}

void afisareComanda(Comanda c) {
	printf("comanda cu codul %d si denumirea %s, are %d produse:\n", c.cod, c.nume, c.numarProduse);
	for (int i = 0; i < c.numarProduse; i++) {
		printf("produsul %d: %s \n", i + 1, c.produse[i]);
	}
}

void afisareLista(nod* cap) {
	while (cap) {
		afisareComanda(cap->info);
		cap = cap->next;
	}
}


struct nodDublu {
	Comanda info;
	nodDublu* prev;
	nodDublu* next;
};
struct LDI {
	nodDublu* first;
	nodDublu* last;
};

nodDublu* creareNod(Comanda c, nodDublu* next, nodDublu* prev) {
	nodDublu* nou = (nodDublu*)malloc(sizeof(nodDublu));

	nou->info = initComanda(c.cod, c.nume, c.numarProduse, c.produse, c.suma);
	nou->next = next;
	nou->prev = prev;
	return nou;
}


LDI adaugareInceputLDI(LDI lista, Comanda c) {
	nodDublu * nou = creareNod(c, lista.first, NULL);

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

void afisareListaInceputSfarsit(LDI lista) {
	nodDublu * p = lista.first;
	while (p) {
		afisareComanda(p->info);
		printf("\n");
		p = p->next;
	}
}
int isEmptyStack(nod *cap) {
	return cap == NULL;
}
void main() {
	const char *produse[3] = { "aragaz","frigider","cuptor" };
	Comanda c = initComanda(100, "celmaimisto", 3, (char**)produse, 2000);

	const char *produse2[3] = { "aragaz","frigider","cuptor" };
	Comanda c2 = initComanda(100, "celmaimisto", 3, (char**)produse2, 190); 
	const char *produse3[3] = { "aragaz","frigider","cuptor" };
	Comanda c3 = initComanda(100, "celmaimisto", 3, (char**)produse3, 311);
	afisareComanda(c);


	nod* coada = NULL;
	coada = pushQueue(coada, c);
	coada = pushQueue(coada, c2);
	coada = pushQueue(coada, c3);

	printf("\n***************\n");
	LDI listaMaiMari;
	listaMaiMari.first = NULL;
	listaMaiMari.last = NULL;

	LDI listaMici;
	listaMici.first = NULL;
	listaMici.last = NULL;

	afisareLista(coada);


	//nu merge
	while (!isEmptyStack(coada)) {
		if (coada->info.suma > 300) {
			Comanda c = popQueue(coada);
			listaMaiMari = adaugareInceputLDI(listaMaiMari, c);
		}
		else {
			listaMici = adaugareInceputLDI(listaMici, c);
		}
 		coada = coada->next;
	}

	printf("\n***************\n");
	afisareListaInceputSfarsit(listaMaiMari);



}