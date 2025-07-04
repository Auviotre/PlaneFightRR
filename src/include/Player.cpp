#include "Player.h"

QVector<Player *> Player::players;
void Player::add(Player *player) {
    Player::players.append(player);
}

Player::Player() : Entity() {}

Player::Player(QString location) : Entity("Player", location, 15) {
	position.setX(SCREEN_WIDTH * 0.5 - image.width() * 0.5);
	position.setY(SCREEN_HEIGHT * 0.8 - image.height());
	attributeMap.setValue(Attribute::MAX_DURABILITY, 120);
	attributeMap.setValue(Attribute::POWER, 12);
	attributeMap.setValue(Attribute::DEFENCE, 4);
	durability = getMaxDurability();
}

Player::~Player() {}

void Player::tick() {
	if (this->getDurability() > 0) Entity::tick();
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
			bullet->setMovement(0, -400);
			bullet->setDamage(attributeMap.getValue(Attribute::POWER));
			bullet->owner = this;
			Bullet::add(bullet);
		} else fireTimer = qMax(0.0, fireTimer - GAME_CLOCK);
	} else fireTimer = qMax(0.0, fireTimer - GAME_CLOCK);

	if (Handler::keyPressSet.value(Qt::Key_K, false) && storage > 0) {
		storage--;
		Bullets::PlayerRocket *bullet = new Bullets::PlayerRocket;
		bullet->setPosition(getPosition());
		bullet->setMovement(0, 400);
		bullet->setAcc(0, -800);
		bullet->setDamage(attributeMap.getValue(Attribute::POWER) * 5);
		bullet->owner = this;
		Bullet::add(bullet);
	}
}

bool Player::damage(double amount, Entity *attacker) {
	return this->getDurability() > 0 && Entity::damage(amount, attacker);
}

bool Player::damage(double amount, Object *bullet, Entity *attacker) {
	return this->getDurability() > 0 && Entity::damage(amount, bullet, attacker);
}

void Player::draw(QPainter &painter) const {
	if (this->getDurability() > 0) Object::draw(painter);
}

void Player::info(QPainter &painter, int id) const {
    painter.setPen(QPen(Qt::white, 1));
    QFont font = QFont(Handler::font);
    font.setPixelSize(16);
    font.setWeight(QFont::Medium);
    painter.setFont(font);
	painter.drawText(GAME_WIDTH + 30, 40 + 50 + id * 200, QString("Player%1").arg(id+1));
	painter.drawText(GAME_WIDTH + 30, 40 + 70 + id * 200, QString("DRTY: %1/%2").arg(getDurability()).arg(getMaxDurability()));
	painter.drawText(GAME_WIDTH + 30, 40 + 90 + id * 200, QString("SCORE: %1").arg(score));
	painter.drawText(GAME_WIDTH + 30, 40 + 110 + id * 200, QString("STORAGE: %1").arg(storage));
	painter.drawText(GAME_WIDTH + 30, 40 + 130 + id * 200, QString("POW: %1").arg(attributeMap.getValue(Attribute::POWER)));
	painter.drawText(GAME_WIDTH + 30, 40 + 150 + id * 200, QString("DEF: %1").arg(attributeMap.getValue(Attribute::DEFENCE)));
}