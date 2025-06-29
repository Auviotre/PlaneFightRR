#pragma once

#include <QVector2D>
#include "Config.h"

class ScreenShaker {
public:
	static QVector2D shake;
	static QVector2D shakeRange;
	static double shakeTimer;
	
	ScreenShaker();
	static void set(double r);
	static void add(double r);
	static void tick();
};