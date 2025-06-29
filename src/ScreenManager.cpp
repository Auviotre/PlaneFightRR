#include "ScreenManager.h"

BattleManager::BattleManager() {
}

BattleManager::~BattleManager() noexcept {
}

void BattleManager::init() {
	this->timer = 0;
	this->summonTime = 0;
    Player::add(new Player(PLAYER_PLANE));
}

void BattleManager::drawBack(QPainter& painter) const {
    // BackGround
    painter.setPen(QPen(Qt::black, 2));
    painter.setBrush(QBrush(Qt::black));
    painter.drawRect(QRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT));
}

void BattleManager::drawFront(QPainter& painter) const {
    // Entities
    for (Bullet *bullet : Bullet::bullets) bullet->draw(painter);
    for (Enemy *enemy : Enemy::enemies) enemy->draw(painter);
    for (Player *player : Player::players) player->draw(painter);

    // FrontGround
    painter.setPen(QPen(Qt::black, 1));
    painter.setBrush(QBrush(Qt::black));
    painter.drawRect(QRect(GAME_WIDTH + 20, 0, SCREEN_WIDTH - GAME_WIDTH, SCREEN_HEIGHT));
    painter.setPen(QPen(Qt::green, 1));
    painter.setBrush(QBrush(Qt::black));
    for (int i = 0; i < 44; i++) {
        painter.drawRect(QRect(i * 10, 0, 10, 10));
        painter.drawRect(QRect(i * 10, SCREEN_HEIGHT - 10, 10, 10));
    }
    for (int i = 1; i < 79; i++) {
        painter.drawRect(QRect(0, i * 10, 10, 10));
        painter.drawRect(QRect(GAME_WIDTH + 10, i * 10, 10, 10));
    }
    // Player Info
    painter.setPen(QPen(Qt::white, 1));
    
    QFont font = QFont(Handler::font);
    font.setPixelSize(20);
    font.setWeight(QFont::Medium);
    painter.setFont(font);
    painter.drawText(GAME_WIDTH + 30, 130, QString("EMY_C: %1").arg(Enemy::enemies.count()));
    painter.drawText(GAME_WIDTH + 30, 150, QString("BLT_C: %1").arg(Bullet::bullets.count()));
    painter.drawText(GAME_WIDTH + 30, 30, QString("TIMER: %1s").arg(timer));
    
    int id = 0;
    for (Player *player : Player::players) {
        painter.drawText(GAME_WIDTH + 30, 50 + id * 20, QString("DRTY: %1/%2").arg(player->getDurability()).arg(player->getMaxDurability()));
        id++;
    }
}

void BattleManager::tick() {
    timer += 0.001 * GAME_RATE;
    // Tick
    for (Player *player : Player::players) player->tick();
    for (Enemy *enemy : Enemy::enemies) enemy->tick();
    for (Bullet *bullet : Bullet::bullets) bullet->tick();
    // Enemy Summon
    if (timer - summonTime > 1) {
        summonTime += 1;
        if (rand() % 2 > 0) {
            Enemy *newEnemy;
            newEnemy = new Enemies::Base;
            newEnemy->setPosition(rand() % (GAME_WIDTH - 10) + 20, -20);
            newEnemy->setMovement(0, 80 + rand() % 80);
            Enemy::add(newEnemy);
        } else {
            // newEnemy = new Enemies::Strike;
            // int r = rand() % 2;
            // newEnemy->setPosition(r ? -30 : GAME_WIDTH + 50, rand() % 100);
            // newEnemy->setMovement(r ? 320 : -320, 400);
        }
    }
    // Collision
    for (Enemy *enemy : Enemy::enemies) {
        for (Player *player : Player::players) {
            QVector2D delta = enemy->getPosition() - player->getPosition();
            if (delta.length() < enemy->getSize() + player->getSize()) {
                enemy->collisionWith(player);
            }
        }
    }

    for (Bullet *bullet : Bullet::bullets) {
        for (Player *player : Player::players) {
            QVector2D delta = bullet->getPosition() - player->getPosition();
            if (delta.length() < bullet->getSize() + player->getSize()) {
                bullet->hitOn(player);
            }
        }
        
        for (Enemy *enemy : Enemy::enemies) {
            QVector2D delta = bullet->getPosition() - enemy->getPosition();
            if (delta.length() < bullet->getSize() + enemy->getSize()) {
                bullet->hitOn(enemy);
            }
        }
    }
    // Discard
    QList<Enemy *> Elist = Enemy::enemies.toList();
    for (Enemy *enemy : Elist) if (enemy->discard) {
        Enemy::enemies.removeAll(enemy);
        delete enemy;
    }
    QList<Bullet *> Blist = Bullet::bullets.toList();
    for (Bullet *bullet : Blist) if (bullet->discard) {
        Bullet::bullets.removeAll(bullet);
        delete bullet;
    }
}

MainManager::MainManager() : selectedOption(0) {
	image.load(ARROW);
}

MainManager::~MainManager() noexcept {
}

void MainManager::init() {
	// 初始化主菜单
	selectedOption = 0; // 默认选中第一个选项
	nxt = 0;
}

void MainManager::draw(QPainter& painter) const {
	// 绘制主菜单背景
	painter.setPen(QPen(Qt::black, 2));
	painter.setBrush(QBrush(Qt::black));
	painter.drawRect(QRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT));

	// 箭头
	QVector2D imageVec = position - QVector2D(0.5F * image.width(), 0.5F * image.height());
	painter.setPen(QPen(Qt::white, 1));
	painter.setBrush(QBrush(Qt::transparent));
	painter.drawPixmap(imageVec.toPoint(), image);

	// 绘制主菜单选项
	painter.setPen(QPen(Qt::white, 5));
	painter.drawLine(50, 185, SCREEN_WIDTH - 50, 185);

	painter.setPen(QPen(Qt::white, 2));
	QFont font = QFont(Handler::font);
	font.setPixelSize(80);
	font.setWeight(QFont::Medium);
	painter.setFont(font);
	painter.drawText(50, 150, "Plane Fight");

	font.setPixelSize(30);
	painter.setFont(font);

	QString options[3] = {"Start", "Settings", "Exit"};
	for (int i = 0; i < 3; i++) {
		if (i == selectedOption) {
			painter.setPen(QPen(Qt::yellow, 2)); // 选中的选项用黄色显示
		} else {
			painter.setPen(QPen(Qt::white, 2));
		}
		painter.drawText(250, 300 + i * 40, options[i]);
	}
}

void MainManager::tick() {
	// 主菜单逻辑更新
	// 通常不需要在这里做太多事情，除非有动画效果
	if (Handler::keyPressSet.value(Qt::Key_W, false)) {
		selectedOption = (selectedOption - 1 + 3) % 3; // 循环选择
		position.setY(290 + selectedOption * 40);
	}
	if (Handler::keyPressSet.value(Qt::Key_S, false)) {
		selectedOption = (selectedOption + 1) % 3; // 循环选择
		position.setY(290 + selectedOption * 40);
	}
	if (Handler::keyPressSet.value(Qt::Key_J, false)) {
		switch (selectedOption) {
			case 0: // 开始游戏
				// 切换到 BattleManager
				nxt = 1;
				break;
			case 1: // 设置
				// 切换到 SettingManager
				nxt = 2;
				break;
			case 2: // 退出
				QApplication::quit();
				break;
		}
	}
}