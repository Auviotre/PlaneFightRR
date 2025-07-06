#pragma once

#include "../include/AbstructEnemy.h"

class Boss : public Enemy {
	enum BossState {SUMMON, IDLE, PREPARE, DASH, BACK};
	BossState state = SUMMON;
	BossState next_state = IDLE;
	int dashCount = 0;
	double skill_timer[3] = {0, 0, 20};
	double skill_cooldown[3] = {6.4, 15, 28.8};
	double theta = 0;
	double omega = M_PI/5;
	double displayer = 0;
public:
	Boss() : Enemy("boss", BOSS, 9, 1200) {
		attributeMap.setValue(Attribute::MAX_DURABILITY, 320);
		attributeMap.setValue(Attribute::POWER, 24);
		attributeMap.setValue(Attribute::DEFENCE, 10);
		durability = getMaxDurability();
	}
	~Boss() noexcept {}

	bool isBoost() {
		return getDurability() * 2 < getMaxDurability();
	}

	void tick() override {
		Object::tick();
		behaviorTick();
		hit_time = hit_time < 0 ? 0 : hit_time - GAME_CLOCK;
		if (getDurability() < 0) setDurability(0);
		if (getDurability() > getMaxDurability()) setDurability(getMaxDurability());
		displayer = displayer + (getDurability() - displayer) * 5 * GAME_CLOCK;

		if (state == SUMMON && next_state == IDLE) {
			position.setY(position.y() + (90 - position.y()) * 4 * GAME_CLOCK);
			if (position.y() > 89) state = next_state;
		} else if (state == IDLE && next_state == IDLE) {
			theta += omega * GAME_CLOCK * (5 + rand() % 5) * 0.2;
			position.setX(10 + GAME_WIDTH/2 + (GAME_WIDTH/2 - size*3) * sin(theta));
			position.setY(90 + 20 * sin(theta * 1.16));
		} else if (state == PREPARE) {
			skill_timer[2] = skill_cooldown[2];
			position.setY(position.y() - 200 * GAME_CLOCK);
			dashCount = isBoost() ? 3 : 2;
			if (position.y() < -200) {
				state = DASH;
				position.setX(0 + rand() % (GAME_WIDTH - 10));
			}
		} else if (state == DASH) {
        	position.setY(position.y() + (isBoost() ? 1440 : 1080) * GAME_CLOCK);
			if (position.y() > SCREEN_HEIGHT + 200) {
				position.setY(-260);
				if (--dashCount > 0) {
					position.setX(0 + rand() % (GAME_WIDTH - 10));
				} else {
					state = BACK;
					theta = 0;
					position.setX(10 + GAME_WIDTH/2);
					skill_timer[2] = 0;
				}
			}
			for (Enemy *enemy : Enemy::enemies) {
				QVector2D delta = getPosition() - enemy->getPosition();
				if (delta.length() < getSize() + enemy->getSize()) {
					enemy->damage(10000, this);
					damage(enemy->getDurability()/3, this);
					attributeMap.setValue(Attribute::POWER, attributeMap.getValue(Attribute::POWER) + 3);
				}
			}
		} else if (state == BACK) {
			position.setY(position.y() + (90 - position.y()) * 4 * GAME_CLOCK);
			if (position.y() > 89) state = next_state;
		}
	}
	
	void collisionWith(Player* player) override {
		if (player->damage(player->getMaxDurability()*2, this)) {
			ScreenShaker::set(8);
		}
	}

	void behaviorTick() override {
		if (state == IDLE && next_state == IDLE) {
			fireTimer += GAME_CLOCK;
			if (fireTimer > (isBoost() ? 0.83 : 1.08)) {
				fireTimer = 0;
				Bullets::PinkRocket *bullet = new Bullets::PinkRocket;
				bullet->setPosition(getPosition());
				bullet->setMovement(0, -400);
				bullet->setAcc(0, 800);
				bullet->xApro = 10 + rand() % GAME_WIDTH;
				bullet->setDamage(attributeMap.getValue(Attribute::POWER));
				bullet->owner = this;
				Bullet::add(bullet);
			}
        	skill_timer[0] += GAME_CLOCK;
        	if (skill_timer[0] > skill_cooldown[0]) {
        		skill_timer[0] = 0;
				Player *p = Player::getRand();
				if (p != nullptr) {
					for (int i = 0; i < (isBoost() ? 12 : 8); i++) {
						Bullets::PinkRocket *bullet = new Bullets::PinkRocket;
						bullet->setPosition(getPosition());
						bullet->setMovement(0, -300);
						bullet->setAcc(0, 600 + rand()%200);
						bullet->xApro = p->getPosition().x() + rand() % 150 - 75;
						bullet->setDamage(attributeMap.getValue(Attribute::POWER) * 0.8);
						bullet->owner = this;
						Bullet::add(bullet);
					}
				}
			}

        	skill_timer[1] += GAME_CLOCK;
        	if (skill_timer[1] > skill_cooldown[1]) {
        		skill_timer[1] = isBoost() && (rand() % 5 == 0) ? skill_cooldown[1] - 0.35 : 0;
				int off = rand() % 40;
				int acc = 300 + rand()%300;
				for (int i = -5; i < 16; i++) {
					Bullets::PinkRocket *bullet = new Bullets::PinkRocket;
					bullet->setPosition(getPosition());
					bullet->setMovement(0, -200);
					bullet->setAcc(0, acc);
					bullet->xApro = 60 * i + off;
					bullet->setDamage(attributeMap.getValue(Attribute::POWER) * 0.9);
					bullet->owner = this;
					Bullet::add(bullet);
				}
			}

        	skill_timer[2] += GAME_CLOCK;
        	if (skill_timer[2] > skill_cooldown[2]) {
				state = PREPARE;
			}
		} else if (state == DASH) {
			skill_timer[2] += GAME_CLOCK;
			if (skill_timer[2] > skill_cooldown[2] + (isBoost() ? 0.05 : 0.06)) {
				skill_timer[2] = skill_cooldown[2];
				Bullets::PinkRocket *bullet = new Bullets::PinkRocket;
				bullet->setPosition(getPosition());
				bullet->setMovement(-80, -40);
				bullet->setAcc(400, 200);
				bullet->sideApro = false;
				bullet->setImageRotation(30);
				bullet->setDamage(attributeMap.getValue(Attribute::POWER) * 1.5);
				bullet->owner = this;
				Bullet::add(bullet);

				bullet = new Bullets::PinkRocket;
				bullet->setPosition(getPosition());
				bullet->setMovement(80, -40);
				bullet->setAcc(-400, 200);
				bullet->sideApro = false;
				bullet->setImageRotation(150);
				bullet->setDamage(attributeMap.getValue(Attribute::POWER) * 1.5);
				bullet->owner = this;
				Bullet::add(bullet);
			}
		}
	}

	void drawBack(QPainter &painter) const {
		if (state == DASH) {
			double temp;
			if (position.y() < 0) {
				temp = (double) (position.y() + 200)/200;
			} else if (position.y() > SCREEN_HEIGHT) {
				temp = (double) (SCREEN_HEIGHT + 200 - position.y())/200;
			} else {
				temp = 1;
			}
			temp = temp > 1 ? 1 : (temp < 0 ? 0 : temp);
			painter.setPen(QPen(Qt::transparent));
			painter.setBrush(QBrush(QColor(250, 150, 220, 50)));
			painter.drawRect(QRect(position.x() - 15*temp, 0, 30*temp, SCREEN_HEIGHT));
		}
	}

	void info(QPainter &painter) const {
		painter.setPen(QPen(QColor(250, 150, 220)));
		QFont font = QFont(Handler::font1);
		font.setPixelSize(18);
		font.setWeight(QFont::Medium);
		painter.setFont(font);

		painter.drawText(GAME_WIDTH + 30, 500, QString("Boss"));
		// painter.drawText(GAME_WIDTH + 30, 560, QString("%1").arg(skill_timer[0]));
		// painter.drawText(GAME_WIDTH + 30, 580, QString("%1").arg(skill_timer[1]));
		// painter.drawText(GAME_WIDTH + 30, 600, QString("%1").arg(skill_timer[2]));

		painter.setPen(QPen(Qt::transparent));
		painter.setBrush(QBrush(QColor(255, 255, 255, 72)));
		painter.drawRect(QRect(GAME_WIDTH + 34, 504, 120, 16));
		painter.setBrush(QBrush(QColor(250, 150, 220)));
		double mod = displayer / getMaxDurability() < 0 ? 0 : displayer / getMaxDurability();
		painter.drawRect(QRect(GAME_WIDTH + 34, 504, 120 * mod, 16));
	}
};