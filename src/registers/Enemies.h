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
	};
}