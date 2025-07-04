#pragma once

#include "../include/AbstructEnemy.h"

namespace Enemies {
	class Base : public Enemy {
	public:
		Base() : Enemy("base", ENEMY, 10, 10) {
			attributeMap.setValue(Attribute::MAX_DURABILITY, 80);
			attributeMap.setValue(Attribute::POWER, 10);
			attributeMap.setValue(Attribute::DEFENCE, 0);
			durability = getMaxDurability();
		}
		~Base() noexcept {}
		void behaviorTick() override {
			fireTimer += GAME_CLOCK;
			if (fireTimer > 1) {
				fireTimer = 0;
				Bullet *bullet = new Bullets::Base;
				bullet->setPosition(getPosition());
				bullet->setMovement(0, movement.y() + 150);
				bullet->setDamage(attributeMap.getValue(Attribute::POWER));
				bullet->owner = this;
				Bullet::add(bullet);
			}
		}
	};

	class Strike : public Enemy {
	public:
		Strike() : Enemy("strike", ENEMY, 10, 20) {
			attributeMap.setValue(Attribute::MAX_DURABILITY, 80);
			attributeMap.setValue(Attribute::POWER, 16);
			attributeMap.setValue(Attribute::DEFENCE, 0);
			durability = getMaxDurability();
			fireTimer = 10;
		}
		~Strike() noexcept {}
		void behaviorTick() override {
			imageRotation = movement.x() > 0 ? -45 : 45;
			fireTimer += GAME_CLOCK;
			movement.setY(movement.y() - 360 * GAME_CLOCK);
			if (fireTimer > 0) {
				fireTimer = -0.32;
				Bullets::Rocket *bullet = new Bullets::Rocket;
				bullet->setPosition(getPosition());
				double sp = movement.x() > 0 ? 240 : -240;
				bullet->setMovement(sp/5, 100);
				bullet->setAcc(sp, 500);
				bullet->setDamage(attributeMap.getValue(Attribute::POWER) * 2);
				bullet->owner = this;
				Bullet::add(bullet);
			}
		}
	};
	
	class Healing : public Enemy {
	public:
		Healing() : Enemy("healing", ENEMY_HEALING, 12, 15) {
			attributeMap.setValue(Attribute::MAX_DURABILITY, 100);
			attributeMap.setValue(Attribute::POWER, 12);
			attributeMap.setValue(Attribute::DEFENCE, 4);
			durability = getMaxDurability();
		}
		~Healing() noexcept {}
		void behaviorTick() override {
			fireTimer += GAME_CLOCK;
			if (fireTimer > 1.1) {
				fireTimer = 0;
				for (int i = -1; i < 2; i++) {
					double x = 200 * sin(i * M_PI / 6);
					double y = 200 * cos(i * M_PI / 6) + movement.y();
					Bullet *bullet = new Bullets::Base;
					bullet->setPosition(getPosition());
					bullet->setMovement(x, y);
					bullet->setDamage(attributeMap.getValue(Attribute::POWER));
					bullet->owner = this;
					Bullet::add(bullet);
				}
			}
		}
	};
	
	class Multi : public Enemy {
	public:
		Multi() : Enemy("multi", ENEMY_MULTI, 12, 15) {
			attributeMap.setValue(Attribute::MAX_DURABILITY, 110);
			attributeMap.setValue(Attribute::POWER, 10);
			attributeMap.setValue(Attribute::DEFENCE, 2);
			durability = getMaxDurability();
		}
		~Multi() noexcept {}
		void behaviorTick() override {
			fireTimer += GAME_CLOCK;
			if (fireTimer > 1.2) {
				fireTimer = 0;
				Bullet *bullet = new Bullets::Base;
				bullet->setPosition(position.x() + size, position.y());
				bullet->setMovement(0, movement.y() + 160);
				bullet->setDamage(attributeMap.getValue(Attribute::POWER));
				bullet->owner = this;
				Bullet::add(bullet);
				bullet = new Bullets::Base;
				bullet->setPosition(position.x() - size, position.y());
				bullet->setMovement(0, movement.y() + 160);
				bullet->setDamage(attributeMap.getValue(Attribute::POWER));
				bullet->owner = this;
				Bullet::add(bullet);
			}
		}
	};

	class Boost : public Enemy {
		int cap = 3;
		int maxCap = 3;
	public:
		Boost() : Enemy("boost", ENEMY_BOOST, 11, 15) {
			attributeMap.setValue(Attribute::MAX_DURABILITY, 105);
			attributeMap.setValue(Attribute::POWER, 9);
			attributeMap.setValue(Attribute::DEFENCE, 3);
			durability = getMaxDurability();
		}
		~Boost() noexcept {}
		void behaviorTick() override {
			fireTimer += GAME_CLOCK;
			if (fireTimer > 1.6) {
				if (cap > 0) {
					fireTimer = 1.35;
					cap--;
				} else {
					fireTimer = 0;
					cap = maxCap;
				}
				Bullet *bullet = new Bullets::Base;
				bullet->setPosition(getPosition());
				bullet->setMovement(0, movement.y() + 140);
				bullet->setDamage(attributeMap.getValue(Attribute::POWER));
				bullet->owner = this;
				Bullet::add(bullet);
			}
		}
	};
}