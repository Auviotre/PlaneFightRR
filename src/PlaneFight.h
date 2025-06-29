#pragma once

#include <QtWidgets/QMainWindow>
#include <QPaintEvent>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QPainter>
#include <QObject>
#include <QEvent>
#include <QTimer>
#include "ui_PlaneFight.h"
#include "Config.h"
#include "ScreenShaker.h"
#include "ScreenManager.h"
#include "ParticleEngine.h"
#include "include/Handler.h"

class MainWindow : public QMainWindow {
    Q_OBJECT
    enum WindowState {MAIN, BATTLE, SETTING};
public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

    void playGame();

    void keyPressEvent(QKeyEvent* event);
    void keyReleaseEvent(QKeyEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
    void focusOutEvent(QFocusEvent* event);
    void paintEvent(QPaintEvent* event);

private:
    Ui_PlaneFight* ui;
    QTimer timer;
    WindowState state;
    ScreenManager* manager = new MainManager;
    float changeLayer = 0;

    void updateManager();

    void init();
};