#pragma once

#include "../include/Item.h"

namespace Items {
	class Storage : public Item {
	public:
		Storage() : Item("item.storage", BONUS_STORAGE, QColor(255, 255, 255), BASE_PLATE1) {
		}
		~Storage() noexcept {}

		void addEffect(Player *player) {
			player->storage += 8;
		}
	};

	class Power : public Item {
	public:
		Power() : Item("item.power", BONUS_POWER, QColor(255, 0, 0), BASE_PLATE1) {
		}
		~Power() noexcept {}

		void addEffect(Player *player) {
			player->setAttribute(Attribute::POWER, player->getAttributes().getValue(Attribute::POWER) + 1);
		}
	};

	class Defence : public Item {
	public:
		Defence() : Item("item.defence", BONUS_DEF, QColor(150, 150, 150), BASE_PLATE1) {
		}
		~Defence() noexcept {}

		void addEffect(Player *player) {
			player->setAttribute(Attribute::DEFENCE, player->getAttributes().getValue(Attribute::DEFENCE) + 0.5);
		}
	};

	class Durability : public Item {
	public:
		Durability() : Item("item.durability", BONUS_DURA, QColor(0, 200, 0), BASE_PLATE1) {
		}
		~Durability() noexcept {}

		void addEffect(Player *player) {
			player->setAttribute(Attribute::MAX_DURABILITY, player->getMaxDurability() + 5);
		}
	};

	class Heal : public Item {
	public:
		Heal() : Item("item.heal", BONUS_HEAL, QColor(0, 240, 0), BASE_PLATE2) {
		}
		~Heal() noexcept {}

		void addEffect(Player *player) {
			player->setDurability(player->getDurability() + player->getMaxDurability() * 0.24);
		}
	};
};