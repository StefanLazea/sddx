#include <stdio.h>
#include <string>
#pragma warning(disable:4996)


struct Masina {
	char * serie;
	int nrKm;
};

Masina initMasina(const char* serie, int nrKm) {
	Masina m;
	m.serie = (char*)malloc(sizeof(char)*(strlen(serie) + 1));
	strcpy(m.serie, serie);
	m.nrKm = nrKm;

	return m;
}

void afisareMasina(Masina m) {
	printf("masina cu seria %s are %d km", m.serie, m.nrKm);
}

struct HashTable {
	Masina* *vector;
	int dim;
};

HashTable initializareHt(int dim) {
	HashTable t;
	t.vector = (Masina**)malloc(sizeof(Masina)*dim);
	for (int i = 0; i < dim; i++) {
		t.vector[i] = NULL;
	}
	t.dim = dim;
	return t;
}

int hashFunction(HashTable h, Masina m) {
	int sum = 0;
	for (int i = 0; i < strlen(m.serie); i++) {
		sum += m.serie[i];
	}
	return sum % h.dim;
}

int inserareMasina(HashTable h, Masina m) {
	if (h.dim > 0){
		int pozitie = hashFunction(h, m);
		if (h.vector[pozitie]) {
			int index = (pozitie + 1) % h.dim;
			while (h.vector[index] != NULL && index != pozitie) {
				index = (index + 1) % h.dim;
			}

			if (index != pozitie) {
				h.vector[index] = (Masina*)malloc(sizeof(Masina));
				*(h.vector[index]) = initMasina(m.serie, m.nrKm);
				return index;
			}
			else {
				return -1;
			}
		}
		else {
			h.vector[pozitie] = (Masina*)malloc(sizeof(Masina));
			*(h.vector[pozitie]) = initMasina(m.serie, m.nrKm);
			return pozitie;
		}
	}
	else {
		return -2; //nu avem
	}
}


int cautareMasina(HashTable h, Masina m) {
	if (h.dim > 0) {
		int pozitie = hashFunction(h, m);
		if (h.vector[pozitie] && strcmp(h.vector[pozitie]->serie, m.serie)==0) {
			return pozitie;
		}
		else {
			int index = (pozitie + 1) % h.dim;
			while (index != pozitie) {
				if (h.vector[index] && strcmp(m.serie, h.vector[index]->serie) == 0) {
					return index;
				}
				index = (index + 1) % h.dim;
			}
		}
	}
	else {
		return -2;
	}
}
int main() {

	HashTable h = initializareHt(4);

	Masina m = initMasina("B35W", 1200);

	inserareMasina(h, m);
	free(m.serie);

	Masina masina = initMasina("A9G6", 1200);
	inserareMasina(h, masina);

	m = initMasina("G5T6", 900);
	inserareMasina(h, m);
	free(m.serie);
	m = initMasina("T2F9", 1600);
	inserareMasina(h, m);
	free(m.serie);
	m = initMasina("Y6J9", 600);
	int index = inserareMasina(h, m);
	printf("index %d", index);
	free(m.serie);
	printf("\r\n");


	int indexCautat = cautareMasina(h, masina);
	printf("indexul cautat %d", indexCautat);
	printf("\r\n");
	afisareMasina(*(h.vector[indexCautat]));


	return 0;
}