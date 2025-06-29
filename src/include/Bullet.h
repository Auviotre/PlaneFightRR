#pragma once

#include "Entity.h"

class Bullet : public Object {
	double damage = 0;
protected:
	double particleTimer = 0;
public:
    static QVector<Bullet *> bullets;
    static void add(Bullet* bullet);
	Entity* owner;

	Bullet();
	Bullet(QString id, QString location, double size);

	~Bullet();

	void setDamage(double dmg);
	
	void tick() override;

	void hitOn(Entity* target);
};