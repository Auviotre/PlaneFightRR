#include "Bullet.h"

QVector<Bullet *> Bullet::bullets;
void Bullet::add(Bullet *bullet) {
    Bullet::bullets.append(bullet);
}

Bullet::Bullet() : Object() {}

Bullet::Bullet(QString id, QString location, double size) : Object(id, location, size) {
}

Bullet::~Bullet() {}

void Bullet::tick() {
	Object::tick();
	position += movement * GAME_CLOCK;
	if (position.y() > SCREEN_HEIGHT + 20 || position.y() < -20) {
		kill();
	}
}

void Bullet::setDamage(double dmg) {
	damage = dmg;
}

void Bullet::hitOn(Entity* target) {
	if (target->damage(damage, this, owner)) kill();
}