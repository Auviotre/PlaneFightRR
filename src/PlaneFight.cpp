#include "PlaneFight.h"

MainWindow::MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent), ui(new Ui_PlaneFight) {
    ui->setupUi(this);
    this->init();
}

MainWindow::~MainWindow() {
}

void MainWindow::init() {
    this->state = BATTLE;
    updateManager();
    this->setFixedSize(SCREEN_WIDTH, SCREEN_HEIGHT);
    this->setWindowTitle(GAME_TITLE);
    this->setWindowIcon(QIcon(GAME_ICON));
    this->timer.setInterval(GAME_RATE);
}

void MainWindow::updateManager() {
    switch (this->state) {
        case BATTLE: manager = new BattleManager;
        case SETTING: manager = new BattleManager;
        default: manager = new BattleManager;
    }
    manager->init();
}

void MainWindow::playGame() {
    this->timer.start();
    connect(&timer, &QTimer::timeout, [=]() {
        update();
        manager->tick();
        ScreenShaker::tick();
        ParticleEngine::tick();
        for (int key : Handler::keyPressSet.keys()) Handler::keyPressSet.insert(key, false);
    });
}

void MainWindow::keyPressEvent(QKeyEvent* event) {
    Handler::keyPressingSet.insert(event->key(), true);
    Handler::keyPressSet.insert(event->key(), true);
}

void MainWindow::keyReleaseEvent(QKeyEvent* event) {
    Handler::keyPressingSet.insert(event->key(), false);
}

void MainWindow::mouseMoveEvent(QMouseEvent* event) {
}


void MainWindow::focusOutEvent(QFocusEvent* event) {
    // player.setPosition(10, 10);
}

void MainWindow::paintEvent(QPaintEvent* event) {
    QPainter painter(this);
    painter.setTransform(QTransform().translate(ScreenShaker::shake.x(), ScreenShaker::shake.y()));
    manager->drawBack(painter);
    ParticleEngine::draw(painter);
    manager->drawFront(painter);
    painter.drawText(GAME_WIDTH + 30, 170, QString("PTC_C: %1").arg(ParticleEngine::particles.count()));
}