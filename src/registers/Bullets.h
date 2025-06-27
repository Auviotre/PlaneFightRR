#pragma once

#include "../include/Bullet.h"

namespace Bullets {
	class Base : public Bullet {
	public:
		Base() : Bullet("bullet.base", ENEMY_BULLET, 4) {
		}
		~Base() noexcept {}
	};

	class PlayerBase : public Bullet {
	public:
		PlayerBase() : Bullet("player_bullet.base", PLAYER_BULLET, 4) {
		}
		~PlayerBase() noexcept {}
	};
}