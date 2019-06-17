
struct nod {
	televizor info; //informatia utila
	nod* next; //ma intereseaza urmatoarea adresa
};

//returneaza un nod nou
//vom returna adresa acestui nou nod (in sine)
nod * creareNod(televizor t, nod* urmator) {   
	nod* nodNou;
	nodNou = (nod*)malloc(sizeof(nod)); //aloc spatiu pentru un nod nou
	nodNou->info = t; //shallow copy daca lasam doar nodNou->info = t; practic o copiere de adrese
	//deep-copy ca avem marca de tip char pointer care trebuie alocat
	//pentru primitive nu se face shallow-copy, ci se face direct
	nodNou->info.marca = (char*)malloc(sizeof(char)*((strlen(t.marca) + 1)));
	strcpy(nodNou->info.marca, t.marca);
	nodNou->next = urmator;
	return nodNou;
}

void afisareLista(nod* cap) { //primim adresa primului nod din lista
	while (cap) { //atata timp cat avem noduri in lista; atata timp cand nu este null
		afisareTelevizor(cap->info);
		cap = cap->next;
	}
}

nod* stergereLista(nod* cap) { //primim adresa primului nod din lista
	while (cap) {
		free(cap->info.marca);
		//daca ma mut, nu mai am acces la precedentul
		nod* temp = cap; //au aceeasi adresa
		cap = cap->next;
		free(temp);
	}
	return NULL; //si cap o sa fie tot nul
}

//tot nod*, adresa primului nod din lista
//cazul in care se modifica si primul: cand lista este goala (null), va trebui schimbata cu adresa nodul pe care l inserez 
nod* inserareSfarsit(nod* cap, televizor t) {
	//verificam daca avem sau nu lista
	if (cap) {
		//avem o lista
		//mergem la ultimul nod
		nod* p = cap;
		//p->next pentru ca vreau sa ies inainte de a se termina lista
		while (p->next) {
			//daca urmatorul nod nu exista nu merg
			//deci ma opresc pe ultimul nod "valid"
			p = p->next;
		}
		//ii salvez noua adresa a noudului in p->next
		p->next = creareNod(t, NULL);
		return cap; //ii returnez adresa primului nod
	}
	else {
		//nu avem lista
		return creareNod(t, NULL);
	}
}
