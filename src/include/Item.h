#pragma once

#include "Object.h"
#include "Player.h"

class Item : public Object {
	QPixmap baseImage;
	QColor color;
	double particleTimer;
public:
    static QVector<Item *> items;
    static void add(Item* item);

	Item();
	Item(QString id, QString location, QColor color, QString base);
	~Item();

	void tick() override;
	void draw(QPainter &painter) const;
	virtual void addEffect(Player *player) = 0;
};