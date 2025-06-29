#pragma once

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
	ScreenManager() {}
    virtual void init() = 0;
    virtual void drawBack(QPainter& painter) const = 0;
    virtual void drawFront(QPainter& painter) const = 0;
    virtual void tick() = 0;
};

class BattleManager : public ScreenManager {
    double timer;
    double summonTime;
public:
    BattleManager();
	~BattleManager() noexcept;

    virtual void init() override;
    void drawBack(QPainter& painter) const override;
    void drawFront(QPainter& painter) const override;
    void tick() override;
};