#pragma once

#include <QVector2D>
#include <QVector>
#include <QColor>
#include <QPainter>
#include "Config.h"

class Particle {
	QVector2D pos;
	QVector2D move;
	QColor baseColor;
	QColor fadeColor;
	bool hasFade;
	double size;
	double lifetime;
	double timer;
	QColor getCurrentColor() const;
public:
	bool discard = false;
	
	Particle(double s, double time);
	~Particle();

	void setColor(QColor color);
	void setFadeColor(QColor color);
	void setPos(QVector2D p);
	void setMove(QVector2D m);
	void tick();
	void draw(QPainter &painter) const;
};

class ParticleEngine {
public:
	static QVector<Particle*> particles;
	
	ParticleEngine();
	~ParticleEngine();

	static void add(Particle* particle);
	static void tick();
	static void draw(QPainter &painter);
	static QVector2D randOffset(double range);
};