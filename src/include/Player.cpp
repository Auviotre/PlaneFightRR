#include "Player.h"

QVector<Player *> Player::players;
void Player::add(Player *player) {
    Player::players.append(player);
}

Player* Player::getRand() {
	return Player::players.at(rand() % Player::players.count());
}

Player::Player() : Entity() {}

Player::Player(QString location) : Entity("Player", location, 15) {
	position.setX(SCREEN_WIDTH * 0.5 - image.width() * 0.5);
	position.setY(SCREEN_HEIGHT * 0.8 - image.height());
	attributeMap.setValue(Attribute::MAX_DURABILITY, Handler::Difficulty == 0 ? 150 : Handler::Difficulty == 1 ? 120 : 100);
	attributeMap.setValue(Attribute::POWER, (Handler::Difficulty == 0 ? 18 : Handler::Difficulty == 1 ? 15 : 13));
	attributeMap.setValue(Attribute::DEFENCE, (Handler::Difficulty == 0 ? 6 : Handler::Difficulty == 1 ? 4.5 : 4));
	durability = getMaxDurability();
}

Player::~Player() {}

void Player::setAttribute(Attribute a, double amount) {
	attributeMap.setValue(a, amount);
}

void Player::tick() {
	if (this->getDurability() > 0) Entity::tick();
	displayer = displayer + (getDurability() - displayer) * 5 * GAME_CLOCK;
}

void Player::behaviorTick() {
	multiTimer = qMax(0.0, multiTimer - GAME_CLOCK);
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
			if (multiTimer > 0) {
				double x = 400 * sin(M_PI / 12);
				double y = -400 * cos(M_PI / 12);
				Bullet *bullet = new Bullets::PlayerBase;
				bullet->setPosition(getPosition());
				bullet->setMovement(x, y);
				bullet->setDamage(attributeMap.getValue(Attribute::POWER)*0.8);
				bullet->owner = this;
				Bullet::add(bullet);
				bullet = new Bullets::PlayerBase;
				bullet->setPosition(getPosition());
				bullet->setMovement(-x, y);
				bullet->setDamage(attributeMap.getValue(Attribute::POWER)*0.8);
				bullet->owner = this;
				Bullet::add(bullet);
			}
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
    painter.setPen(QPen(Qt::white));
    QFont font = QFont(Handler::font1);
    font.setPixelSize(18);
    font.setWeight(QFont::Medium);
    painter.setFont(font);
	painter.drawText(GAME_WIDTH + 30, 40 + 50 + id * 300, QString("Player%1").arg(id+1));
	painter.drawText(GAME_WIDTH + 30, 40 + 70 + id * 300, QString("DRTY: %1/%2").arg(getDurability(), 1).arg(getMaxDurability()));
	painter.drawText(GAME_WIDTH + 30, 40 + 110 + id * 300, QString("SCORE: %1").arg(score));
	painter.drawText(GAME_WIDTH + 30, 40 + 130 + id * 300, QString("STORAGE: %1").arg(storage));
	painter.drawText(GAME_WIDTH + 30, 40 + 150 + id * 300, QString("POW: %1").arg(attributeMap.getValue(Attribute::POWER)));
	painter.drawText(GAME_WIDTH + 30, 40 + 170 + id * 300, QString("DEF: %1").arg(attributeMap.getValue(Attribute::DEFENCE)));

    painter.setPen(QPen(Qt::transparent));
    painter.setBrush(QBrush(QColor(255, 255, 255, 72)));
    painter.drawRect(QRect(GAME_WIDTH + 34, 40 + 74 + id * 300, 120, 16));
    painter.setBrush(QBrush(Qt::white));
	double mod = displayer / getMaxDurability() < 0 ? 0 : displayer / getMaxDurability();
    painter.drawRect(QRect(GAME_WIDTH + 34, 40 + 74 + id * 300, 120 * mod, 16));
}