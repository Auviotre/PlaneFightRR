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
	int nxt = 0;
	ScreenManager() {}
    virtual void init() = 0;
    virtual void draw(QPainter& painter) const = 0;
    virtual void tick() = 0;
};

class BattleManager : public ScreenManager {
    double timer;
    double summonTime;
public:
    BattleManager();
	~BattleManager() noexcept;

    virtual void init() override;
    void draw(QPainter& painter) const override;
    void tick() override;
};

class MainManager : public ScreenManager {
public:
	MainManager();
	~MainManager() noexcept;

	virtual void init() override;
	void draw(QPainter& painter) const override;
	void tick() override;

private:
	QPixmap image;
	QVector2D position = QVector2D(230, 295);
	int selectedOption; // 当前选中的菜单选项
};