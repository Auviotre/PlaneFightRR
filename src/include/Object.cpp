#include "Object.h"


Object::Object() {}

Object::Object(QString id, QString location, double size = 10) : descriptId(id), size(size) {
	image.load(location);
}

Object::~Object() {}

void Object::tick() {
	timer += GAME_CLOCK;
}

void Object::setImageOffset(int x, int y) {
	imageOffset.setX(x);
	imageOffset.setY(y);
}

double Object::getSize() const {
	return size;
}

QVector2D Object::getPosition() const {
	return position;
}

void Object::setPosition(int x, int y) {
	position.setX(x);
	position.setY(y);
}
void Object::setPosition(QVector2D pos) {
	position = pos;
}

QVector2D Object::getMovement() const {
	return movement;
}

void Object::setMovement(int x, int y) {
	movement.setX(x);
	movement.setY(y);
}

void Object::draw(QPainter &painter) const {
	QVector2D imageVec = position - QVector2D(0.5F * image.width(), 0.5F * image.height());
	painter.setPen(QPen(Qt::white, 1));
	painter.setBrush(QBrush(Qt::transparent));
	painter.drawPixmap(imageVec.toPoint(), image);
	if (DEBUG) {
		QVector2D newPos = position + imageOffset;
		newPos -= QVector2D(size, size);
		painter.drawEllipse(newPos.x(), newPos.y(), size * 2, size * 2);
		painter.drawPoint(position.toPoint());
		// painter.drawText(position.toPoint(), QString("  %1").arg(descriptId));
	}
}

void Object::kill() {
	this->discard = true;
}