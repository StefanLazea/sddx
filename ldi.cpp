

struct Avion {
	char * numePilot;
	int numarPasageri;

};

struct nodDublu {
	Avion info; //informatia utila
	nodDublu* next; //ma intereseaza urmatoarea adresa
	nodDublu* prev; //adresa nodul precedent
};

struct LDI {
	nodDublu* first;
	nodDublu* last;
};

Avion creareAvion(const char* numePilot, int nrPasageri) {
	Avion avion;
	avion.numePilot = (char*)malloc(sizeof(char)*((strlen(numePilot) + 1)));
	strcpy(avion.numePilot, numePilot);
	avion.numarPasageri = nrPasageri;
	return avion;
}
//creare nod
nodDublu* creareNod(Avion avion, nodDublu* next, nodDublu *prev) {
	nodDublu* nou = (nodDublu*)malloc(sizeof(nodDublu));

	nou->info = creareAvion(avion.numePilot, avion.numarPasageri);
	nou->next = next;
	nou->prev = prev;

	return nou;
}

LDI inserareInceput(LDI lista, Avion avion) {
	
	nodDublu * nou = creareNod(avion, lista.first, NULL);

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

LDI inserareFinal(LDI lista, Avion avion) {
	nodDublu * nodNou = creareNod(avion, NULL, lista.last);
	if (lista.last) {
		lista.last->next = nodNou;
	}
	else {
		lista.first = nodNou;
	}
	lista.last = nodNou;
	return lista;
}

void afisareAvion(Avion avion) {
	printf("Avionul condus de %s are %d pasageri\r\n", avion.numePilot, avion.numarPasageri);
}


void afisareListaInceputSfarsit(LDI lista) {
	nodDublu* p = lista.first; //pointer la primul element
	while (p) {
		afisareAvion(p->info);
		p = p->next;
	}
		
}

void afisareListaSfarsitInceput(LDI lista){
	nodDublu * p = lista.last;

	while (p) {
		afisareAvion(p->info);
		p = p->prev; //ma deplasez la cel dinainte
	}
}

void stergereLista(LDI *lista) { //pointerii first si last o sa aiba valoare null, deci se modifica, trebui sa avem adresa la lista
	//deci o sa punem pointer la adresa
	nodDublu * p = lista->first; //ca sa nu scriem mult
	while (p) {
		free(p->info.numePilot);
		//imi iau alt nod pentru ca daca as sterge P ul nu as mai avea acces la lista
		nodDublu* temp = p;
		p = p->next; //ma mut pe urmatorul nod
		free(temp); //dar aici nodul urmator, prin care prev pointa la nodul pe care l am sters pointeaza intr o zona goala
		//dar va reintra in while si se va sterge
	}
	//dar first si last raman sa pointeze catre zonele de memorie goale
	//dar adresele celor doi pointeri inca sunt
	lista->first = NULL;
	lista->last = NULL;
}