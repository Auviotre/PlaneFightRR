#include "PlaneFight.h"

MainWindow::MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent), ui(new Ui_PlaneFight) {
    ui->setupUi(this);
    this->init();
}

MainWindow::~MainWindow() {
}

void MainWindow::init() {
    this->state = MAIN;
    updateManager();
    this->setFixedSize(SCREEN_WIDTH, SCREEN_HEIGHT);
    this->setWindowTitle(GAME_TITLE);
    this->setWindowIcon(QIcon(GAME_ICON));
    this->timer.setInterval(GAME_RATE);
}

void MainWindow::updateManager() {
    manager->clear();
    switch (this->state) {
        case MAIN: manager = new MainManager; break;
        case BATTLE: manager = new BattleManager; break;
        default: manager = new MainManager;
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
        changeLayer = changeLayer + ((manager->changeTo ? 1 : 0) - changeLayer) * 7.5 * GAME_CLOCK;
        if (changeLayer > 0.99) {
            switch (manager->changeTo) {
                case 0: break;
                case 1: this->state = BATTLE; updateManager(); break;
                case 3: this->state = MAIN; updateManager(); break;
            }
        }
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
    painter.setBrush(QBrush(Qt::black));
    painter.setBrush(QBrush(QColor(0, 0, 0, (int) (changeLayer * 255))));
    painter.drawRect(QRect(-10, -10, SCREEN_WIDTH + 20, SCREEN_HEIGHT + 20));
}