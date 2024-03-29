#pragma once
#include "Enemy.h"
#include <vector>
using namespace std;

class Controller {
private:
	vector<Enemy*>enemies;
public:
	Controller() {}
	~Controller() {}
	void addEnemy(Enemy* e) {
		enemies.push_back(e);
	}
	void drawEverything(Graphics^ g, Bitmap^ bmpEnemy) {
		for (int i = 0; i < enemies.size(); i++)
		{
			enemies[i]->draw(g, bmpEnemy);
		}
	}
	void moveEveything(Graphics^ g) {
		for (int i = 0; i < enemies.size(); i++)
		{
			enemies[i]->move(g);
		}
	}

	int getEnemies() { return enemies.size(); }
};
