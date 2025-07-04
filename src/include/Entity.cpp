#include "Entity.h"

Entity::Entity() : Object() {}

Entity::Entity(QString id, QString location, double size) : Object(id, location, size) {
}

Entity::~Entity() {}

AttributeMap Entity::getAttributes() const {
	return attributeMap;
}

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
	hit_time = hit_time < 0 ? 0 : hit_time - GAME_CLOCK;
	if (getDurability() < 0) setDurability(0);
	if (getDurability() > getMaxDurability()) setDurability(getMaxDurability());
	if (getDurability() <= 0) kill(true);
}

bool Entity::damage(double amount, Entity* attacker) {
	if (attacker == this) return false;
	double left = getDurability() - amount;
	setDurability(left);
	hit_time = 2;
	return true;
}

bool Entity::damage(double amount, Object *bullet, Entity *attacker) {
	return damage(amount, attacker);
}

void Entity::draw(QPainter &painter) const {
	Object::draw(painter);
	int alpha = floor(255 * hit_time) > 255 ? 255 : floor(255 * hit_time);
	alpha = alpha * 4 / 5;
	painter.setPen(QPen(QColor(200, 200, 200, alpha/2), 1));
	painter.setBrush(QBrush(QColor(200, 200, 200, alpha/2)));
	int y = position.y() - size * 2;
    painter.drawRect(QRect(position.x() - 10, y - 1, 20, 2));
	painter.setPen(QPen(QColor(200, 200, 200, alpha), 2));
	painter.setBrush(QBrush(QColor(200, 200, 200, alpha)));
    painter.drawRect(QRect(position.x() - 10, y - 2, ceil(20 * getDurability() / getMaxDurability()), 4));

    painter.drawLine(position.x() - 15, y - 3, position.x() - 15, y + 3);
    painter.drawLine(position.x() + 15, y - 3, position.x() + 15, y + 3);
	if (DEBUG) {
		painter.setPen(QPen(Qt::white, 2));
		painter.setBrush(QBrush(Qt::white));
		QVector2D newPos = position - QVector2D(size, size);
		if (lastHurt != nullptr) {
			painter.drawText(position.x() + 20, position.y() + 00, QString("  %1").arg(lastHurt->descriptId));
			painter.drawText(position.x() + 20, position.y() + 20, QString("  %1").arg(lastHurt->score));
		}
	}
}