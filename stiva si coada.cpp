#include <stdlib.h>
#include <stdio.h>
#include <string>
#pragma warning(disable:4996)


struct Service {
	char*denumire;
	int nrMasini;
};

struct nod {
	Service info;
	nod* next;
};

Service initService(const char*denumire, int nrMasini) {
	Service s;
	s.denumire = (char*)malloc(sizeof(char)*(strlen(denumire) + 1));
	strcpy(s.denumire, denumire);
	s.nrMasini = nrMasini;
	return s;
}

nod* adaugareInceput(nod* cap, Service s) {
	nod* nou = (nod*)malloc(sizeof(nod));
	nou->next = cap;
	nou->info = initService(s.denumire, s.nrMasini);

	return nou;
}

nod* adaugareFinal(nod* cap, Service s) {
	if (cap) {
		nod*t = cap;
		while (t->next) {
			t = t->next;
		}
		t->next = adaugareInceput(NULL, s);
		return cap; //ptr a face legatura
	}
	else {
		return adaugareInceput(cap, s);
	}
}

nod* pushStack(Service s, nod* stiva) {
	stiva = adaugareInceput(stiva, s);
	return stiva;
}

Service popStack(nod* &cap) {
	if(cap){
		Service rezultat = initService(cap->info.denumire, cap->info.nrMasini);
		free(cap->info.denumire);
		nod*t = cap;
		cap = cap->next;
		free(t);
		return rezultat;
	}
	else {
		return initService(NULL, -1);
	}

}

nod* pushQueue(Service s, nod* queue) {
	queue = adaugareFinal(queue, s);
	return queue;
}

Service popQueue(nod* &cap){
	if (cap) {
		Service rezultat = initService(cap->info.denumire, cap->info.nrMasini);
		free(cap->info.denumire);
		nod* temp = cap;
		cap = cap->next;
		free(temp);

		return rezultat;
	}
	else {
		return initService(NULL, -1);
	}
}

void afisareService(Service s) {
	printf("service ul %s are %d masini", s.denumire, s.nrMasini);
}

void afisare(nod* lista) {
	while (lista) {
		afisareService(lista->info);
		lista = lista->next;
		printf("\n");
	}
}

void main() {
	//stiva
	nod* stiva = NULL;
	stiva = pushStack(initService("sco", 4), stiva);
	stiva = pushStack(initService("meg", 10), stiva);
	afisare(stiva);
	printf("\n************ \n");
	Service s = popStack(stiva);
	afisareService(s);
	printf("\n************ \n");
	afisare(stiva);

	printf("\n******COADA****** \n");
	nod* coada = NULL;

	coada = pushQueue(initService("prim", 10), coada);
	coada = pushQueue(initService("aloha", 90), coada);
	coada = pushQueue(initService("servcoi", 4), coada);
	coada = pushQueue(initService("bahoi", 2), coada);


	afisare(coada);
	printf("\n************ \n");

	Service p = popQueue(coada);
	afisareService(p);


}