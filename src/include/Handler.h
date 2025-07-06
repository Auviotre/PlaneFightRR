#pragma once

#include <QFontDatabase>
#include <QMap>

class Handler {
public:
	Handler();
	static void updateScoreRecord();
	static void flushRecord();
	static void updateSettings();
	static QMap<int, bool> keyPressingSet;
	static QMap<int, bool> keyPressSet;
	static QString font;
	static int Difficulty;
	static int ParAmount;
	static bool CoMode;
	static int scoreRecord;
};