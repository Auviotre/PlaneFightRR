#pragma once

#include "Entity.h"
#include "Handler.h"
#include "../registers/Bullets.h"

class Player : public Entity {
	double fireTimer = 0;
public:
	int storage = 10;
    static QVector<Player *> players;
    static void add(Player* player);

	Player();
	Player(QString location);

	~Player();

	void tick() override;

	void behaviorTick() override;

	bool damage(double amount, Entity *attacker) override;
	bool damage(double amount, Object *bullet, Entity *attacker) override;

	void draw(QPainter &painter) const;
	void info(QPainter &painter, int id) const;
};