#include "Player.h"

QVector<Player *> Player::players;
void Player::add(Player *player) {
    Player::players.append(player);
}

Player::Player() : Entity() {}

Player::Player(QString location) : Entity("Player", location, 15) {
	position.setX(SCREEN_WIDTH * 0.5 - image.width() * 0.5);
	position.setY(SCREEN_HEIGHT * 0.8 - image.height());
	attributeMap.setValue(Attribute::MAX_DURABILITY, 100);
	attributeMap.setValue(Attribute::POWER, 10);
	attributeMap.setValue(Attribute::DEFENCE, 0);
	durability = getMaxDurability();
}

Player::~Player() {}

void Player::tick() {
	Entity::tick();
}

void Player::behaviorTick() {
	double delta = 250.0 * GAME_CLOCK;
	if (Handler::keyPressingSet.value(Qt::Key_W, false)) {
		position.setY(qMax(position.y() - delta, 10.0 + size));
	}
	if (Handler::keyPressingSet.value(Qt::Key_S, false)) {
		position.setY(qMin(position.y() + delta, 10.0 + GAME_HEIGHT - size));
	}
	if (Handler::keyPressingSet.value(Qt::Key_A, false)) {
		position.setX(qMax(position.x() - delta, 10.0 + size));
	}
	if (Handler::keyPressingSet.value(Qt::Key_D, false)) {
		position.setX(qMin(position.x() + delta, 10.0 + GAME_WIDTH - size));
	}

	if (Handler::keyPressingSet.value(Qt::Key_J, false)) {
		if (fireTimer <= 0) {
			fireTimer = 0.16;
			Bullet *bullet = new Bullets::PlayerBase;
			bullet->setPosition(getPosition());
			bullet->setMovement(0, -200);
			bullet->setDamage(attributeMap.getValue(Attribute::POWER));
			bullet->owner = this;
			Bullet::add(bullet);
		} else fireTimer = qMax(0.0, fireTimer - GAME_CLOCK);
	} else fireTimer = qMax(0.0, fireTimer - GAME_CLOCK);
}

bool Player::damage(double amount, Entity *attacker) {
	return Entity::damage(amount, attacker);
}

bool Player::damage(double amount, Object *bullet, Entity *attacker) {
	return Entity::damage(amount, bullet, attacker);
}