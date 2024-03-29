#pragma once
#include "Bullet.h"
#include "Enemy.h"
#include "Bala.h"
#include <vector>

using namespace std;
class Controller {
private:
	vector<Bullet*>bullets;
	vector<Enemy*>enemies;
	vector<Bala*>bala;
	int numberOfEnemies;
public:
	Controller() {
		numberOfEnemies = 1;
	}

	~Controller(){}

	void createEnemies(int width, int height) {
		for (int i = 0; i < numberOfEnemies; i++) {
			Enemy* e = new Enemy(width, height, rand() % 2);
			enemies.push_back(e);
		}
	}

	void createBala(int width, int height) {
		for (int i = 0; i < 1; i++) {
			Bala* e = new Bala(width, height);
			bala.push_back(e);
		}
	}

	void addBullet(Bullet* b) { bullets.push_back(b);}

	void drawEveryThing(Graphics^ g, Bitmap^ bmpEnemy, Bitmap^ bmpBullet, Bitmap^ bmpBala) {
		for (int i = 0; i < enemies.size(); i++) enemies[i]->draw(g, bmpEnemy);
		for (int i = 0; i < bullets.size(); i++) bullets[i]->draw(g,bmpBullet);
		for (int i = 0; i < bala.size(); i++) bala[i]->draw(g, bmpBala);
	}

	void moveEveryThing(Graphics^ g ) {
		for (int i = 0; i < enemies.size(); i++) enemies[i]->move(g);
		for (int i = 0; i < bullets.size(); i++) bullets[i]->move(g);
		for (int i = 0; i < bala.size(); i++) bala[i]->move(g);
	}

	void collision(Graphics^ g) {
		//verificar
		for (int i = 0; i < bullets.size(); i++) {
			if (bullets[i]->getX() <= 0 || bullets[i]->getXWidth() >= g->VisibleClipBounds.Width ||
				bullets[i]->getY() <= 0 || bullets[i]->getYHeight() >= g->VisibleClipBounds.Height) {
				bullets[i]->setVisibility(false);
			}
		}

		// colision bullet vs enemy
		for (int i = 0; i < enemies.size(); i++) {
			for (int j = 0; j < bullets.size(); j++) {
				if (enemies[i]->getRectangle().IntersectsWith(bullets[j]->getRectangle())) {
					enemies[i]->setVisibility(false);
					bullets[j]->setVisibility(false);
				}
			}
		}

		//borrar
		for (int i = 0; i < bullets.size(); i++) {
			//if(Bullets[i]->getVisibility()==false)
			if (!bullets[i]->getVisibility()) bullets.erase(bullets.begin() + i);
		}

		for (int i = 0; i < enemies.size(); i++) {
			if (!enemies[i]->getVisibility()) enemies.erase(enemies.begin() + i);
		}
	}

	void eliminarBala(Graphics^ g) {
		for (int i = 0; i < bala.size(); i++) {
			if (!bala[i]->getVisibility()) bala.erase(bala.begin() + i);
		}
	}
};
