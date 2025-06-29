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
	if (movement.x() == 0) imageRotation = movement.y() > 0 ? 90 : 270;
	else imageRotation = qAtan2(movement.y(), movement.x()) / M_PI * 180.0;
	if (position.y() > SCREEN_HEIGHT + 20 || position.y() < -20 || position.x() < -20 || position.x() > GAME_WIDTH + 40) {
		kill(false);
	}
}

void Bullet::setDamage(double dmg) {
	damage = dmg;
}

void Bullet::hitOn(Entity* target) {
	if (target->damage(damage, this, owner)) kill(true);
}