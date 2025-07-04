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

	class Rocket : public Bullet {
		QVector2D acc = QVector2D(0, 0);
	public:
		Rocket() : Bullet("bullet.rocket", ENEMY_ROCKET, 5) {
		}
		~Rocket() noexcept {}

		void setAcc(double x, double y) {
			acc = QVector2D(x, y);
		}

		void tick() override {
			Bullet::tick();
			movement += acc * GAME_CLOCK;
			particleTimer += GAME_CLOCK;
			if (particleTimer > 0.01) {
				particleTimer = 0;
				Particle* particle = new Particle(3, 0.5);
				particle->setPos(getPosition() + ParticleEngine::randOffset(2));
				particle->setMove(getMovement() * 0.5);
				particle->setColor(QColor(51, 122, 255, 200));
				particle->setFadeColor(QColor(25, 60, 120, 100));
				ParticleEngine::add(particle);
			}
		}

		void kill(bool display) override {
			Bullet::kill(display);
			if (display) ScreenShaker::set(2);
			for (int i = 0; display && i < 12; i++) {
				Particle* particle = new Particle(3, 0.3);
				particle->setPos(getPosition());
				particle->setMove(ParticleEngine::randOffset(60) + ParticleEngine::randOffset(10));
				particle->setColor(QColor(51, 122, 255, 200));
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

	class PlayerRocket : public Bullet {
		QVector2D acc = QVector2D(0, 0);
	public:
		PlayerRocket() : Bullet("player_bullet.rocket", PLAYER_ROCKET, 5) {
		}
		~PlayerRocket() noexcept {}

		void setAcc(double x, double y) {
			acc = QVector2D(x, y);
		}

		void tick() override {
			Bullet::tick();
			imageRotation = 270;
			movement += acc * GAME_CLOCK;
			particleTimer += GAME_CLOCK;
			if (particleTimer > 0.01) {
				particleTimer = 0;
				Particle* particle = new Particle(3, 0.5);
				particle->setPos(getPosition() + ParticleEngine::randOffset(2));
				particle->setMove(getMovement() * 0.5);
				particle->setColor(QColor(230, 128, 10));
				particle->setFadeColor(QColor(174, 20, 2));
				ParticleEngine::add(particle);
			}
		}

		void kill(bool display) override {
			Bullet::kill(display);
			if (display) ScreenShaker::set(2);
			for (int i = 0; display && i < 12; i++) {
				Particle* particle = new Particle(3, 0.3);
				particle->setPos(getPosition());
				particle->setMove(ParticleEngine::randOffset(60) + ParticleEngine::randOffset(10));
				particle->setColor(QColor(230, 128, 10));
				particle->setFadeColor(QColor(174, 20, 2));
				ParticleEngine::add(particle);
			}
		}
	};
}