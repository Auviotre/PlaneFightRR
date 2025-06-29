#pragma once

#include "../include/AbstructEnemy.h"

namespace Enemies {
	class Base : public Enemy {
	public:
		Base() : Enemy("base", ENEMY, 10, 10) {
			attributeMap.setValue(Attribute::MAX_DURABILITY, 100);
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
				bullet->setMovement(movement.x(), movement.y() + 150);
				bullet->setDamage(attributeMap.getValue(Attribute::POWER));
				bullet->owner = this;
				Bullet::add(bullet);
			}
		}
	};

	class Strike : public Enemy {
	public:
		Strike() : Enemy("strike", ENEMY, 10, 20) {
			attributeMap.setValue(Attribute::MAX_DURABILITY, 100);
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
			if (fireTimer > 0.32) {
				fireTimer = 0;
				Bullet *bullet = new Bullets::Base;
				bullet->setPosition(getPosition());
				double sp = movement.x() > 0 ? 240 : -240;
				bullet->setMovement(sp, 500);
				bullet->setDamage(attributeMap.getValue(Attribute::POWER));
				bullet->owner = this;
				Bullet::add(bullet);
			}
		}
	};
}