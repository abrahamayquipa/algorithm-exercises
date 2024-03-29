#pragma once
#include "Monigote.h"
#include "Estrella.h"
#include "VectorEstrellas.h"
#include "VectorMeteoros.h"
#include "VectorBasura.h"
#include "VectorAlien.h"

class Controladora {
private:
	int width, height;

	int cantidadEstrellas;
	int cantidadMeteoros;
	int cantidadBasuras;
	int cantidadAliens;

	Monigote* objMonigote;
	VectorEstrellas* objVectorEstrellas;
	VectorMeteoros* objVectorMeteoros;
	VectorBasura* objVectorBasura;
	VectorAlien* objVectorAliens;

	time_t tiempo;
public:
	Controladora(int width, int height, int cantidadEstrellas, int cantidadMeteoros,int cantidadBasuras, int cantidadAliens) {
		this->width = width;
		this->height = height;

		this->cantidadEstrellas = cantidadEstrellas;
		this->cantidadMeteoros = cantidadMeteoros;
		this->cantidadBasuras = cantidadBasuras;
		this->cantidadAliens = cantidadAliens;

		this->objMonigote = new Monigote(width, height);
		this->objVectorEstrellas = new VectorEstrellas(this->cantidadEstrellas, width, height);
		this->objVectorMeteoros = new VectorMeteoros(this->cantidadMeteoros, width, height);
		this->objVectorBasura = new VectorBasura(this->cantidadBasuras, width, height);
		this->objVectorAliens = new VectorAlien(this->cantidadAliens, width, height);

		tiempo = time(0);
	}

	~Controladora() { 
		delete this->objMonigote;
		delete this->objVectorEstrellas;
		delete this->objVectorMeteoros;
		delete this->objVectorBasura;
		delete this->objVectorAliens;
	}

	void gestionTecla(char tecla) {
		this->objMonigote->cambiarDireccion(tecla);
	}

	void gestionMonigote() {
		this->objMonigote->borrar();
		this->objMonigote->mover();
		this->objMonigote->imprimir();
	}

	void gestionColisionesEstrellas() {
		for (Estrella* objEstrellas : this->objVectorEstrellas->getEstrellas()) {
			if (objEstrellas->getRectangle().IntersectsWith(this->objMonigote->getRectangle())) {
				this->objMonigote->agregarEstrellasCapturadas();
				objEstrellas->setActivo(false);
				break;
			}
		}
	}

	void gestionarColisionesMeteoros() {
		for (Meteotoro* objMeteoros : this->objVectorMeteoros->getMeteoros()) {
			if (objMeteoros->getRectangle().IntersectsWith(this->objMonigote->getRectangle())) {
				system("cls");
				system("pause>0");
				exit(0);
			}
		}
	}

	void gestionarColisionesBasura() {
		for (Basura* objBasuras : this->objVectorBasura->getBasura()) {
			if (objBasuras->getRectangle().IntersectsWith(this->objMonigote->getRectangle())) {
				this->objMonigote->agregarBasurasCapturadas();
				objBasuras->setActivo(false);
				break;
			}
		}
	}

	void gestionarColisionesAliens() {
		for (Alien* objAliens : this->objVectorAliens->getBasura()) {
			if (objAliens->getRectangle().IntersectsWith(this->objMonigote->getRectangle())) {
				this->objMonigote->agregarBasurasCapturadas();
				objAliens->setActivo(false);
				exit(0);
			}
		}
	}

	void mostrarLetreroEstrellas() {
		System::Console::ForegroundColor = System::ConsoleColor::White;
		System::Console::SetCursorPosition(0, height - 1);
		cout << "Estrellas: ";
		int i;
		for (i = 0; i < objMonigote->getCantidadEstrellasAtrapados(); i++) {
			cout << char(42) << " ";
		}
		cout << i;
	}

	void mostrarLetreroBasura() {
		System::Console::ForegroundColor = System::ConsoleColor::White;
		System::Console::SetCursorPosition(0, height - 2);
		cout << "Basura: ";
		int i;
		for (i = 0; i < objMonigote->getCantidadBasurasAtrapadas(); i++) {
			cout << "# ";
		}
		cout << i;
	}


	void mostrarLetreroTiempo() {
		System::Console::SetCursorPosition(0, height - 3);
		cout << "tiempo: " << clock() / 1000;
		if (clock() / 1000 == 60) {
			system("cls");
			system("pause>0");
			exit(0);
		} 
	}

	void runGame() {
		this->gestionMonigote();
		this->gestionColisionesEstrellas();
		this->gestionarColisionesMeteoros();
		this->gestionarColisionesBasura();
		this->gestionarColisionesAliens();

		this->objVectorEstrellas->gestionEstrellas(width, height);
		this->objVectorMeteoros->gestionMeteoros(width, height);
		this->objVectorBasura->gestionBasura(width, height);
		this->objVectorAliens->gestionAlien(width, height);

		this->mostrarLetreroEstrellas();
		this->mostrarLetreroTiempo();
		this->mostrarLetreroBasura();
	}

	bool gameOverCase1() {
		return this->objMonigote->getCantidadEstrellasAtrapados() == this->cantidadEstrellas;
	}

	bool gameOverCase2() {
		return this->objMonigote->getCantidadBasurasAtrapadas() == this->cantidadEstrellas;
	}
};
