#include "Entity.h"

Entity::Entity() : Object() {}

Entity::Entity(QString id, QString location, double size) : Object(id, location, size) {
}

Entity::~Entity() {}

void Entity::setDurability(double dura) {
	durability = dura;
}

double Entity::getDurability() const {
	return durability;
}

double Entity::getMaxDurability() const {
	return attributeMap.getValue(Attribute::MAX_DURABILITY);
}

void Entity::tick() {
	Object::tick();
	behaviorTick();
	position += movement * GAME_CLOCK;
}

bool Entity::damage(double amount, Entity* attacker) {
	if (attacker == this) return false;
	double left = getDurability() - amount;
	if (left <= 0) kill();
	setDurability(left);
	return true;
}

bool Entity::damage(double amount, Object *bullet, Entity *attacker) {
	return damage(amount, attacker);
}
