#pragma once

#include <QVector2D>
#include <QPainter>
#include <QPixmap>
#include <QRect>
#include <QMap>
#include "../ScreenShaker.h"
#include "../Config.h"

class Object {
protected:
	QPixmap image;
	double imageRotation = 0;
	double size;
	QVector2D position = QVector2D(0, 0);
	QVector2D movement = QVector2D(0, 0);
public:
	QString descriptId;
    double timer = 0;
	bool discard = false;

	Object();

	Object(QString id, QString location, double size);

	~Object();

	virtual void tick();

	double getSize() const;
	QVector2D getPosition() const;

	void setPosition(int x, int y);
	void setPosition(QVector2D pos);

	QVector2D getMovement() const;

	void setMovement(int x, int y);

	void draw(QPainter &painter) const;
	
	virtual void kill(bool display);
};