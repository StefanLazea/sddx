#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning(disable:4996)

struct Mesaj {
	char*text;
	int prioritate;
};

Mesaj initMesaj(const char* text, int prioritate) {
	Mesaj m;
	m.text = (char*)malloc(sizeof(char)*(strlen(text) + 1));
	strcpy(m.text, text);
	m.prioritate = prioritate;
	return m;
}

void afisareMesaj(Mesaj m) {
	printf("mesajul %s \n are o prioritate de %d\n", m.text, m.prioritate);
}

struct Heap {
	Mesaj *vector;
	int dim;
};

void afisareHeap(Heap heap) {
	for (int i = 0; i < heap.dim; i++) {
		afisareMesaj(heap.vector[i]);
	}
}

void filtrare(Heap heap, int pozitie) {
	int fiuS = 2 * pozitie + 1;
	int fiuD = 2 * pozitie + 2;

	int max = pozitie;
	if (fiuS < heap.dim && heap.vector[max].prioritate < heap.vector[fiuS].prioritate) {
		max = fiuS;
	}
	if (fiuD < heap.dim && heap.vector[max].prioritate < heap.vector[fiuD].prioritate) {
		max = fiuD;
	}

	if (max != pozitie) {
		Mesaj aux = heap.vector[max];
		heap.vector[max] = heap.vector[pozitie];
		heap.vector[pozitie] = aux;

		if (2 * max + 1 < heap.dim) {
			filtrare(heap, max);
		}
	}
}

void insereareHeap(Heap &heap, Mesaj m) {
	if (heap.dim>=0) {
		Mesaj* temp = (Mesaj*)malloc(sizeof(Mesaj)*(heap.dim + 1));
		for (int i = 0; i < heap.dim; i++) {
			temp[i] = heap.vector[i];
		}
		temp[heap.dim] = m;
		free(heap.vector);
		heap.vector = temp;
		heap.dim++;

		for (int i = (heap.dim-2)/2; i >= 0; i--) {
			filtrare(heap, i);
		}
	}
}

Mesaj extragereHeap(Heap &heap) {
	if (heap.dim > 0) {
		Mesaj rezultat = heap.vector[0];
		Mesaj* temp = (Mesaj*)malloc(sizeof(Mesaj)*(heap.dim - 1));
		for (int i = 1; i < heap.dim; i++) {
			temp[i - 1] = heap.vector[i];
		}
		free(heap.vector);
		heap.vector = temp;
		heap.dim--;

		for (int i = (heap.dim - 2) / 2; i >= 0; i--) {
			filtrare(heap, i);
		}
		return rezultat;
	}
	else {
		return initMesaj(NULL, -1);
	}
}

void main() {
	Heap h;
	h.dim = 6;
	h.vector = (Mesaj*)malloc(sizeof(Mesaj)*h.dim);
	h.vector[0] = initMesaj("macarena", 1);
	h.vector[1] = initMesaj("ura", 2);
	h.vector[2] = initMesaj("messi", 3);
	h.vector[3] = initMesaj("mue", 4);
	h.vector[4] = initMesaj("po", 5);
	h.vector[5] = initMesaj("ma", 6);

	afisareHeap(h);
	printf("\r\n");
	for (int i = (h.dim - 2) / 2; i >= 0; i--) {
		filtrare(h, i);
	}
	afisareHeap(h);


}
