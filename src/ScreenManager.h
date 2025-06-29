#pragma once

#include <QApplication>
#include <QPainter>
#include <QList>
#include <QMap>
#include "Config.h"
#include "include/Player.h"
#include "include/AbstructEnemy.h"
#include "include/Bullet.h"
#include "include/Handler.h"
#include "registers/Enemies.h"

class ScreenManager {
public:
	int changeTo = 0;
	ScreenManager() {}
	~ScreenManager() noexcept {}
    virtual void init() = 0;
    virtual void drawBack(QPainter& painter) const = 0;
    virtual void drawFront(QPainter& painter) const = 0;
    virtual void tick() = 0;
    virtual void clear() = 0;
};

class BattleManager : public ScreenManager {
    double timer;
    double summonTime;
	enum BattleState {DEAD, PAUSE, RUNNING};
	BattleState state = RUNNING;
public:
    BattleManager();
	~BattleManager() noexcept;

    virtual void init() override;
    void drawBack(QPainter& painter) const override;
    void drawFront(QPainter& painter) const override;
    void tick() override;
    void clear() override;
};

class MainManager : public ScreenManager {
public:
	MainManager();
	~MainManager() noexcept;

	virtual void init() override;
    void drawBack(QPainter& painter) const override;
    void drawFront(QPainter& painter) const override;
	void tick() override;
    void clear() override;

private:
	QPixmap image;
	QVector2D position = QVector2D(80, 295);
	QVector2D posDisplay = QVector2D(80, SCREEN_HEIGHT + 100);
	int selectedOption; // 当前选中的菜单选项
};