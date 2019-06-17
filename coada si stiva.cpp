#include <iostream>
#include <string>
#pragma warning(disable:4996)
using namespace std;

struct Carte {
	char *titlu;
	int nrPagini;
};

struct nod {
	Carte info;
	nod* next;
};

Carte creareCarte(const char* titlu, int nrPagini) {
	Carte carte;
	carte.titlu = (char*)malloc(sizeof(char)*(strlen(titlu) + 1));
	strcpy(carte.titlu, titlu);
	carte.nrPagini = nrPagini;
	return carte;
}

void afisareCarte(Carte carte) {
	printf("cartea cu titlul %s are %d pagini\r\n", carte.titlu, carte.nrPagini);
}

//in sine stiva si coada se construiesc pe baza unei LSI
void afisareLista(nod* cap) {
	while (cap) {
		afisareCarte(cap->info);
		cap = cap->next;
	}
}

nod* stergereLista(nod* cap) {
	while (cap) {
		free(cap->info.titlu);
		nod*temp = cap;
		cap = cap->next;
		free(temp);
	}

	return cap; //sau null
}

nod* adaugareInceput(Carte c, nod* cap) {
	nod* nou = (nod*)malloc(sizeof(nod));
	nou->next = cap;
	nou->info = creareCarte(c.titlu, c.nrPagini);

	return nou;
}

//varianta 1 - folosind creareNod care e adaugareInceput
nod* adaugareFinal(Carte c, nod*cap) {
	if (cap) {
		nod *t = cap;
		while (t->next)
		{
			t = t->next;
		}
		t->next = adaugareInceput(c, NULL);
		return cap;
	}
	else {
		return adaugareInceput(c, NULL);
	}
}


//implementarea se face la inceput
//ultimul inserat la inceput
//este primul scos
nod* pushStack(Carte c, nod*stiva) {
	stiva = adaugareInceput(c, stiva);
	return stiva;
}

//pentru parcurgere
int isEmptyStack(nod *cap) {
	return cap == NULL;
}
//primim adresa ca sa luam val de acolo
Carte popStack(nod* &cap) {
	if (cap) {
		Carte rezultat = creareCarte(cap->info.titlu, cap->info.nrPagini);
		nod * temp = cap;
		cap = cap->next; //trecem peste urmatorul
		free(temp->info.titlu);
		free(temp);
		return rezultat;
	}
	else {
		return creareCarte(NULL, 0); //un nod gol
	}
}

nod* pushQueue(Carte c, nod* queue) {
	return adaugareFinal(c, queue);
}

Carte popQueue(nod* &cap) {
	if (cap) {
		Carte rezultat = creareCarte(cap->info.titlu, cap->info.nrPagini);
		nod* t = cap;
		cap = cap->next;
		free(t->info.titlu);
		free(t);
		return rezultat;
	}
	else {
		return creareCarte(NULL, 0);
	}
}
//stiva = stack (push si pop)
//coada = queue
int main()
{
    cout << "Hello World!\n"; 
	nod * lista = NULL;

	lista = adaugareInceput(creareCarte("a inceput", 100), lista);
	lista = adaugareInceput(creareCarte("restanta", 999), lista);


	afisareLista(lista);


	printf("elemente stiva\r\n");
	nod* stiva = NULL;
	stiva = pushStack(creareCarte("huck", 200), stiva);
	stiva = pushStack(creareCarte("finn", 233), stiva);

	afisareLista(stiva);


	printf("pop stiva\r\n");

	while (!isEmptyStack(stiva)) {
		Carte c = popStack(stiva);
		afisareCarte(c);
		free(c.titlu);
	}


	//coada implementata prin lsi

	nod* coada =NULL;
	coada = pushQueue(creareCarte("cartea 1", 200), coada);
	coada = pushQueue(creareCarte("cartea 2", 200), coada);
	coada = pushQueue(creareCarte("cartea 3", 100), coada);

	printf("coada este:\r\n");
	afisareLista(coada);
	printf("primul nod iesit\r\n");
	afisareCarte(popQueue(coada));


}
