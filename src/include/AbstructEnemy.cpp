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
	if (position.y() > SCREEN_HEIGHT + 50 || position.y() < -50 || position.x() < -50 || position.x() > GAME_WIDTH + 70) {
		kill(false);
	}
}

void Enemy::kill(bool display) {
	Entity::kill(display);
	for (int i = 0; display && i < 16; i++) {
		Particle* particle = new Particle(4, 0.5);
		particle->setPos(getPosition());
		particle->setMove(ParticleEngine::randOffset(60) + ParticleEngine::randOffset(20));
		particle->setColor(QColor(160, 160, 160, 208));
		ParticleEngine::add(particle);
	}
}

void Enemy::collisionWith(Player* player) {
	ScreenShaker::set(6);
	player->damage(this->durability / 10, this);
	kill(true);
}

bool Enemy::damage(double amount, Entity *attacker) {
	return Entity::damage(amount, attacker);
}

bool Enemy::damage(double amount, Object *bullet, Entity *attacker) {
	if (bullet->descriptId.indexOf("player_bullet") == -1) return false;
	return Entity::damage(amount, bullet, attacker);
}