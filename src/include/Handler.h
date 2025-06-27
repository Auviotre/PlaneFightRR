#pragma once

#include <QFontDatabase>
#include <QMap>

class Handler {
public:
	Handler();
	static QMap<int, bool> keyPressingSet;
	static QMap<int, bool> keyPressSet;
	static QString font;
};