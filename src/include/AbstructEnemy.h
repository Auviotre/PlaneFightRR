#pragma once

#include "Player.h"
#include "Bullet.h"
#include "../registers/Bullets.h"

class Enemy : public Entity {
public:
    static QVector<Enemy *> enemies;
    static void add(Enemy *enemy);

	int score;
	double fireTimer = 0;

	Enemy();
	Enemy(QString id, QString location, double size, int score);

	~Enemy();
	
	void tick() override;

	void behaviorTick() override;

	void collisionWith(Player* player);
	
	bool damage(double amount, Entity *attacker) override;
	bool damage(double amount, Object *bullet, Entity *attacker) override;
};