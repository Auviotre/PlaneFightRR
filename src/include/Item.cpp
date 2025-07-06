#include "Item.h"

QVector<Item *> Item::items;
void Item::add(Item *item) {
    Item::items.append(item);
}

Item::Item() : Object() {}

Item::Item(QString id, QString location, QColor color, QString base) : Object(id, location, 12), color(color) {
	baseImage.load(base);
}

Item::~Item() {}

void Item::tick() {
	Object::tick();
	position += movement * GAME_CLOCK;
	if (position.x() < 10 + image.width()) {
		position.setX(10 + image.width());
		movement.setX(-movement.x());
	}
	if (position.x() > GAME_WIDTH + 10 - image.width()) {
		position.setX(GAME_WIDTH + 10 - image.width());
		movement.setX(-movement.x());
	}
	if (position.y() > SCREEN_HEIGHT + 10) kill(false);
	
	particleTimer += GAME_CLOCK;
	if (particleTimer > 0.03) {
		particleTimer = 0;
		Particle* particle = new Particle(3, 0.5);
		particle->setPos(getPosition() + ParticleEngine::randOffset(size));
		particle->setColor(this->color);
		ParticleEngine::add(particle);
	}
}

void Item::draw(QPainter &painter) const {
	QVector2D pos = position - QVector2D(size, size);
	painter.setPen(QPen(Qt::white));
	painter.setBrush(QBrush(Qt::transparent));
	painter.drawPixmap(pos.toPoint(), baseImage.scaled(2*size, 2*size));
	pos = position - QVector2D(size-1, size-1);
	painter.setPen(QPen(Qt::white));
	painter.setBrush(QBrush(color));
	painter.drawPixmap(pos.toPoint(), image.scaled(2*size - 2, 2*size - 2));
	if (DEBUG) {
		painter.setPen(QPen(Qt::white));
		painter.setBrush(QBrush(Qt::transparent));
		QVector2D newPos = position - QVector2D(size, size);
		painter.drawRect(newPos.x(), newPos.y(), size * 2, size * 2);
		painter.drawPoint(position.toPoint());
	}
}
