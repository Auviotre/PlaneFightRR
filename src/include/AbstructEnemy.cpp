#include "AbstructEnemy.h"

QVector<Enemy *> Enemy::enemies;
void Enemy::add(Enemy *enemy) {
    Enemy::enemies.append(enemy);
}

Enemy::Enemy() : Entity() {}

Enemy::Enemy(QString id, QString location, double size, int score) : Entity(id, location, size), score(score) {
}

Enemy::~Enemy() {}

void Enemy::tick() {
	Entity::tick();
	if (position.y() > SCREEN_HEIGHT + 20) {
		kill();
	}
}

void Enemy::behaviorTick() {
	fireTimer += GAME_CLOCK;
	if (fireTimer > 1) {
		fireTimer = 0;
		Bullet *bullet = new Bullets::Base;
		bullet->setPosition(getPosition());
		bullet->setMovement(movement.x(), movement.y() + 100);
		bullet->setDamage(attributeMap.getValue(Attribute::POWER));
		bullet->owner = this;
		Bullet::add(bullet);
	}
}

void Enemy::collisionWith(Player* player) {
	player->damage(this->durability / 10, this);
	kill();
}

bool Enemy::damage(double amount, Entity *attacker) {
	return Entity::damage(amount, attacker);
}

bool Enemy::damage(double amount, Object *bullet, Entity *attacker) {
	if (bullet->descriptId.indexOf("player_bullet") == -1) return false;
	return Entity::damage(amount, bullet, attacker);
}