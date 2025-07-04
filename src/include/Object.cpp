#include "Object.h"


Object::Object() {}

Object::Object(QString id, QString location, double size = 10) : descriptId(id), size(size) {
	image.load(location);
}

Object::~Object() {}

void Object::tick() {
	timer += GAME_CLOCK;
	if (imageRotation > 360) imageRotation -= 360;
	else if (imageRotation < 0) imageRotation += 360;
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
	QPixmap trans = image.transformed(QTransform().rotate(imageRotation), Qt::SmoothTransformation);
	QVector2D pos = position + - QVector2D(0.5*trans.width(), 0.5*trans.height());
	painter.setPen(QPen(Qt::white, 2));
	painter.setBrush(QBrush(Qt::transparent));
	painter.drawPixmap(pos.toPoint(), trans);
	if (DEBUG) {
		QVector2D newPos = position - QVector2D(size, size);
		painter.drawEllipse(newPos.x(), newPos.y(), size * 2, size * 2);
		painter.drawPoint(position.toPoint());
	}
}

void Object::kill(bool display) {
	this->discard = true;
}