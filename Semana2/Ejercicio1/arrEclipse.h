#pragma once
#include "eclipse.h"
#include <iostream>
using namespace std;

class arrEclipse {
private:
	eclipse** arreglo_eclipse;
	int numero_eclipses;

public:
	arrEclipse() {
		this->arreglo_eclipse = nullptr;
		this->numero_eclipses = 0;
	};

	~arrEclipse() {
		for (int i = 0; i < numero_eclipses; i++) {
			delete this->arreglo_eclipse[i];
		}
		delete[] arreglo_eclipse;
	};

	void agregarEclipse(eclipse* obj) {
		eclipse** aux = new eclipse* [numero_eclipses + 1];

		for (int i = 0; i < this->numero_eclipses; i++) {
			aux[i] = this->arreglo_eclipse[i];
		}

		aux[this->numero_eclipses] = obj;

		delete[] this->arreglo_eclipse;
		this->arreglo_eclipse = aux;

		++this->numero_eclipses;
	}

	void eliminarPlato(int posicion) {
		eclipse** aux = new eclipse * [this->numero_eclipses - 1];

		int actual = 0;
		for (int i = 0; i < this->numero_eclipses; i++) {
			if (i == posicion) continue;
			aux[actual] = this->arreglo_eclipse[i];
			++actual;
		}

		delete[] this->arreglo_eclipse;
		this->arreglo_eclipse = aux;

		--this->numero_eclipses;
	}

	void reporteEclipsesEuropa() {
		for (int i = 0; i < numero_eclipses; i++) {
			if(arreglo_eclipse[i]->getVisibilidad() == "Europa")
			cout << "\tPosicion: " << i << " -> ";
			this->arreglo_eclipse[i]->toString();
		}
	}

	void reporteEclipsesQueCausaronSismos() {
		for (int i = 0; i < numero_eclipses; i++) {
			if (arreglo_eclipse[i]->getSismos() == true)
				cout << "\tPosicion: " << i << " -> ";
			this->arreglo_eclipse[i]->toString();
		}
	}

	void reporteEclipsesNoche() {
		for (int i = 0; i < numero_eclipses; i++) {
			if (arreglo_eclipse[i]->getSismos() == true)
				cout << "\tPosicion: " << i << " -> ";
			this->arreglo_eclipse[i]->toString();
		}
	}

	eclipse* getEclipses(int posicion) {
		return this->arreglo_eclipse[posicion];
	}

	int getNumeroEclipses() {
		return this->numero_eclipses;
	}
};
