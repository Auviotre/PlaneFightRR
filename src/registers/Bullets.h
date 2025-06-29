#pragma once

#include "../include/Bullet.h"
#include "../ParticleEngine.h"

namespace Bullets {
	class Base : public Bullet {
	public:
		Base() : Bullet("bullet.base", ENEMY_BULLET, 4) {
		}
		~Base() noexcept {}

		void tick() override {
			Bullet::tick();
			particleTimer += GAME_CLOCK;
			if (particleTimer > 0.036) {
				particleTimer = 0;
				Particle* particle = new Particle(3, 0.25);
				particle->setPos(getPosition() + ParticleEngine::randOffset(2));
				particle->setMove(getMovement() * 0.25);
				particle->setColor(QColor(44, 130, 233, 208));
				ParticleEngine::add(particle);
			}
		}

		void kill(bool display) override {
			Bullet::kill(display);
			for (int i = 0; display && i < 12; i++) {
				Particle* particle = new Particle(2.5, 0.3);
				particle->setPos(getPosition());
				particle->setMove(ParticleEngine::randOffset(60) + ParticleEngine::randOffset(10));
				particle->setColor(QColor(44, 130, 233, 208));
				ParticleEngine::add(particle);
			}
		}
	};

	class PlayerBase : public Bullet {
	public:
		PlayerBase() : Bullet("player_bullet.base", PLAYER_BULLET, 4) {
		}
		~PlayerBase() noexcept {}

		void tick() override {
			Bullet::tick();
			particleTimer += GAME_CLOCK;
			if (particleTimer > 0.022) {
				particleTimer = 0;
				Particle* particle = new Particle(3, 0.2);
				particle->setPos(getPosition() + ParticleEngine::randOffset(2));
				particle->setMove(getMovement() * 0.25);
				particle->setColor(QColor(230, 128, 10));
				particle->setFadeColor(QColor(174, 20, 2));
				ParticleEngine::add(particle);
			}
		}

		void kill(bool display) override {
			Bullet::kill(display);
			for (int i = 0; display && i < 12; i++) {
				Particle* particle = new Particle(2.5, 0.3);
				particle->setPos(getPosition());
				particle->setMove(ParticleEngine::randOffset(60) + ParticleEngine::randOffset(10));
				particle->setColor(QColor(230, 128, 10));
				particle->setFadeColor(QColor(174, 20, 2));
				ParticleEngine::add(particle);
			}
		}
	};
}