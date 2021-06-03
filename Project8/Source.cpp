#include<iostream>

using namespace std;

struct Mesaj {
	int id;
	char* destinatar;
	int prioritate;
};

Mesaj creareMesaj(int id, const char* destinatar, int prioritate) {
	Mesaj m;
	m.id = id;
	m.destinatar = (char*)malloc(sizeof(char*) * (strlen(destinatar) + 1));
	strcpy(m.destinatar, destinatar);
	m.prioritate = prioritate;
	return m;
}

void afisareMesaj(Mesaj m) {
	printf("\nMesajul cu i-ul %d pentru destinatarul %s are prioritatea %d.", m.id, m.destinatar, m.prioritate);
}

struct Heap {
	Mesaj* vector;
	int dim;
};

Heap creareHeap(int dim) {
	Heap h;
	h.dim = dim;
	h.vector = (Mesaj*)malloc(sizeof(Mesaj) * dim);
	return h;
}

void filtrare(Heap h, int poz) {
	if (h.vector) {
		if (poz <= (h.dim - 1) / 2) {
			int fiuS = 2 * poz + 1;
			int fiuD = 2 * poz + 2;
			int pozMax = poz;
			if (fiuS<h.dim && h.vector[fiuS].prioritate>h.vector[pozMax].prioritate) {
				pozMax = fiuS;
			}
			if (fiuD<h.dim && h.vector[fiuD].prioritate>h.vector[pozMax].prioritate) {
				pozMax = fiuD;
			}

			if (pozMax != poz) {
				Mesaj aux = h.vector[poz];
				h.vector[poz] = h.vector[pozMax];
				h.vector[pozMax] = aux;
				if (pozMax <= (h.dim - 1) / 2) {
					filtrare(h, pozMax);
				}
			}
		}
	}
}

void afisareHeap(Heap h) {
	if (h.vector) {
		for (int i = 0; i < h.dim; i++) {
			afisareMesaj(h.vector[i]);
		}
	}
}
Heap inserareheap(Heap h, Mesaj m) {
	int dimensiune = h.dim + 1;
	Mesaj * copie= (Mesaj*)malloc(sizeof(Mesaj) * dimensiune);
	for (int i = 0;i < h.dim;i++) {
		copie[i] = h.vector[i];

	}
	copie[dimensiune - 1] = m;

	h.dim = dimensiune;
	free(h.vector);
	h.vector= (Mesaj*)malloc(sizeof(Mesaj) * dimensiune);
	for (int i = 0;i < h.dim;i++) {
		h.vector[i] = copie[i];
	}
	for (int i = (h.dim - 1) / 2;i >= 0;i--) {
		filtrare(h, i);
	}
	return h;
}
Mesaj extragereheap(Heap* h) {
	Mesaj rezultat = h->vector[0];
	int dimensiune = h->dim - 1;
	Mesaj* copie = (Mesaj*)malloc(sizeof(Mesaj) * dimensiune);
	for (int i = 0;i < dimensiune;i++) {
		copie[i] = h->vector[i + 1];
	}
	h->dim = dimensiune;
	free(h->vector);
	h->vector = (Mesaj*)malloc(sizeof(Mesaj) * dimensiune);
	for (int i = 0;i < h->dim;i++) {
		h->vector[i] = copie[i];
	}
	for (int i = (h->dim - 1) / 2;i >= 0;i--) {
		filtrare(*h, i);
	}
	return rezultat;
}
void main() {
	Heap h = creareHeap(7);

	h.vector[0] = creareMesaj(1, "dajhd", 5);
	h.vector[1] = creareMesaj(2, "dajhd", 10);
	h.vector[2] = creareMesaj(3, "dajhd", 20);
	h.vector[3] = creareMesaj(4, "dajhd", 2);
	h.vector[4] = creareMesaj(5, "dajhd", 6);
	h.vector[5] = creareMesaj(6, "dajhd", 15);
	h.vector[6] = creareMesaj(7, "dajhd", 14);

	printf("\nAfisare heap inainte de filtrare");
	afisareHeap(h);

	for (int i = (h.dim - 1) / 2;i >= 0;i--) {
		filtrare(h, i);
	}
	printf("\nAfisare heap dupa filtrare");
	afisareHeap(h);

	printf("\nAfisare heap dupa inserare: ");
	h = inserareheap(h, creareMesaj(100, "sjdhsda", 30));
	afisareHeap(h);

	printf("\nMesaj extras: ");
	afisareMesaj(extragereheap(&h));

	printf("\nAfisare heap dupa extragere: ");
	afisareHeap(h);
}