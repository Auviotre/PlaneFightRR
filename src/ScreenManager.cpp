#include "ScreenManager.h"

BattleManager::BattleManager() {
}

BattleManager::~BattleManager() noexcept {
}

void BattleManager::clear() {
    Player::players.remove(0, Player::players.count());
    Bullet::bullets.remove(0, Bullet::bullets.count());
    Enemy::enemies.remove(0, Enemy::enemies.count());
    Item::items.remove(0, Item::items.count());
}

void BattleManager::init() {
	this->timer = 0;
	this->summonTime = 0;
    Player *p1 = new Player(PLAYER_PLANE);
    p1->descriptId = "P1";
    Player::add(p1);
}

void BattleManager::drawBack(QPainter& painter) const {
    // BackGround
    painter.setPen(QPen(Qt::black, 2));
    painter.setBrush(QBrush(Qt::black));
    painter.drawRect(QRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT));
	if (boss != nullptr) boss->drawBack(painter);
}

void BattleManager::drawFront(QPainter& painter) const {
    // Entities
    for (Item *Item : Item::items) Item->draw(painter);
    for (Bullet *bullet : Bullet::bullets) bullet->draw(painter);
    for (Enemy *enemy : Enemy::enemies) enemy->draw(painter);
	if (boss != nullptr) boss->draw(painter);
    for (Player *player : Player::players) player->draw(painter);

    // FrontGround
    painter.setPen(QPen(Qt::black, 1));
    painter.setBrush(QBrush(Qt::black));
    painter.drawRect(QRect(GAME_WIDTH + 20, 0, SCREEN_WIDTH - GAME_WIDTH, SCREEN_HEIGHT));
	if (Handler::Difficulty == 0) painter.setPen(QPen(QColor(128, 128, 255)));
	if (Handler::Difficulty == 1) painter.setPen(QPen(Qt::green, 1));
	if (Handler::Difficulty == 2) painter.setPen(QPen(Qt::red, 1));
    painter.setBrush(QBrush(Qt::black));
    for (int i = 0; i < 44; i++) {
        painter.drawRect(QRect(i * 10, 0, 10, 10));
        painter.drawRect(QRect(i * 10, SCREEN_HEIGHT - 10, 10, 10));
    }
    for (int i = 1; i < 79; i++) {
        painter.drawRect(QRect(0, i * 10, 10, 10));
        painter.drawRect(QRect(GAME_WIDTH + 10, i * 10, 10, 10));
    }
    if (state != RUNNING) {
        painter.setBrush(QBrush(QColor(0, 0, 0, 100)));
        painter.drawRect(QRect(10, 10, GAME_WIDTH, GAME_HEIGHT));
        painter.setPen(QPen(Qt::white, 1));
        QFont font = QFont(Handler::font1);
        font.setPixelSize(20);
        font.setWeight(QFont::Medium);
        painter.setFont(font);
		if (state == PAUSE) painter.drawText(40, 150, QString("PAUSE"));
		if (state == DEAD) painter.drawText(40, 150, QString("You Failed!"));
		if (state == WIN) {
			painter.drawText(40, 150, QString("You Win!"));
			painter.drawText(40, 190, QString("Your Score: %1").arg(Player::getRand()->score));
		}
		painter.drawText(40, 170, QString("Press 'R' to return.").arg(Enemy::enemies.count()));
    }
    // Player Info
	painter.setPen(QPen(Qt::white, 1));
	QFont font = QFont(Handler::font1);
	font.setPixelSize(20);
	font.setWeight(QFont::Medium);
	painter.setFont(font);
	if (DEBUG) {
		painter.drawText(GAME_WIDTH + 30, 430, QString("EMY_C: %1").arg(Enemy::enemies.count()));
		painter.drawText(GAME_WIDTH + 30, 450, QString("BLT_C: %1").arg(Bullet::bullets.count()));
		painter.drawText(GAME_WIDTH + 30, 470, QString("PTC_C: %1").arg(ParticleEngine::particles.count()));
	}
    
	painter.drawText(GAME_WIDTH + 30, 30, QString("TIMER: %1s").arg(timer));
	painter.drawText(GAME_WIDTH + 30, 50, QString("RECORD: %1").arg(Handler::scoreRecord));
    int id = 0;
    for (Player *player : Player::players) player->info(painter, id++);
	if (boss != nullptr) boss->info(painter);
}

Enemy* getRand() {
    int i = rand() % 100;
    if (i < 76) return new Enemies::Base;
    if (i < 84) return new Enemies::Multi;
    if (i < 92) return new Enemies::Boost;
    return new Enemies::Healing;
}

void BattleManager::tick() {
	if (Handler::keyPressSet.value(Qt::Key_Space, false)) {
        if (state == RUNNING) state = PAUSE;
        else if (state == PAUSE) state = RUNNING;
    }
    if (state != RUNNING && Handler::keyPressSet.value(Qt::Key_R, false)) {
        changeTo = 3;
		Handler::scoreRecord = qMax(Handler::scoreRecord, Player::getRand()->score);
		Handler::updateScoreRecord();
    }
    bool allDead = true;
    for (Player *player : Player::players) if (player->getDurability() > 0) allDead = false;
    if (allDead) state = DEAD;
	if (bossSummoned && boss == nullptr) state = WIN;
    if (state == PAUSE || state == WIN) return;
    // Tick
    if (state == RUNNING) timer += 0.001 * GAME_RATE;
    for (Player *player : Player::players) player->tick();
    for (Enemy *enemy : Enemy::enemies) enemy->tick();
    for (Bullet *bullet : Bullet::bullets) bullet->tick();
    for (Item *item : Item::items) item->tick();
	if (boss != nullptr) boss->tick();
	if (timer > 80 && !bossSummoned) {
		bossSummoned = true;
		boss = new Boss;
		boss->setPosition(10 + GAME_WIDTH/2, -15);
	}
    // Enemy Summon
    if (timer - summonTime > 1) {
        summonTime += 1 + bossSummoned * 0.5;
        Enemy *newEnemy;
        newEnemy = getRand();
        newEnemy->setPosition(rand() % (GAME_WIDTH - 10) + 20, -20);
        newEnemy->setMovement(0, 80 + rand() % 80);
        Enemy::add(newEnemy);
        if (rand() % 7 == 0) {
            newEnemy = new Enemies::Strike;
            int r = rand() % 2;
            newEnemy->setPosition(r ? -30 : GAME_WIDTH + 50, rand() % 100);
            newEnemy->setMovement(r ? 320 : -320, 400);
            Enemy::add(newEnemy);
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
	
	if (boss != nullptr) {
        for (Player *player : Player::players) {
            QVector2D delta = boss->getPosition() - player->getPosition();
            if (delta.length() < boss->getSize() + player->getSize()) {
                boss->collisionWith(player);
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
        
		if (boss != nullptr) {
			QVector2D delta = bullet->getPosition() - boss->getPosition();
			if (delta.length() < bullet->getSize() + boss->getSize()) {
				bullet->hitOn(boss);
			}
		}
    }

    for (Item *item : Item::items) {
        for (Player *player : Player::players) {
            QVector2D delta = item->getPosition() - player->getPosition();
            if (abs(delta.x()) < item->getSize() + player->getSize()/1.4 && abs(delta.y()) < item->getSize() + player->getSize()/1.4) {
                if (player->getDurability() > 0) {
					item->addEffect(player);
					item->kill(true);
				}
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
    QList<Item *> Ilist = Item::items.toList();
    for (Item *item : Ilist) if (item->discard) {
        Item::items.removeAll(item);
        delete item;
    }
	if (boss != nullptr) {
		if (boss->discard) {
			delete boss;
			boss = nullptr;
		}
	}
}

MainManager::MainManager() : selectedOption(0) {
	image.load(ARROW);
}

MainManager::~MainManager() noexcept {
}

void MainManager::clear() {
    Player::players.remove(0, Player::players.count());
}

void MainManager::init() {
	// 初始化主菜单
	selectedOption = 0; // 默认选中第一个选项
	changeTo = 0;
}

void MainManager::drawBack(QPainter& painter) const {
	// 绘制主菜单背景
	painter.setPen(QPen(Qt::black, 2));
	painter.setBrush(QBrush(Qt::black));
	painter.drawRect(QRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT));
}

void MainManager::drawFront(QPainter& painter) const {
	// 箭头
	QVector2D imageVec = posDisplay - QVector2D(0.5F * image.width(), 0.5F * image.height());
	painter.setPen(QPen(Qt::white, 1));
	painter.setBrush(QBrush(Qt::transparent));
	painter.drawPixmap(imageVec.toPoint(), image);

	// 绘制主菜单选项
	painter.setPen(QPen(Qt::white, 5));
	painter.drawLine(50, 185, SCREEN_WIDTH - 50, 185);

	painter.setPen(QPen(Qt::white, 2));
	QFont font = QFont(Handler::font1);
	font.setPixelSize(80);
	font.setWeight(QFont::Medium);
	painter.setFont(font);
	painter.drawText(50, 150, "Plane Fight");
	font = QFont(Handler::font2);
	font.setPixelSize(80);
	font.setWeight(QFont::Medium);
	painter.setFont(font);

	font.setPixelSize(30);
	painter.setFont(font);

	QString options[3] = {"开始", "设置", "退出"};
	for (int i = 0; i < 3; i++) {
		if (i == selectedOption && setting != 1 && quiting != 1) {
			painter.setPen(QPen(Qt::yellow, 2)); // 选中的选项用黄色显示
		} else {
			painter.setPen(QPen(Qt::white, 2));
		}
		painter.drawText(100, 300 + i * 80, options[i]);
	}

	if (setting == 1) {
		QString options[3];
		switch (Handler::Difficulty) {
			case 0:
				options[0] = "难度：简单";
				break;
			case 1:
				options[0] = "难度：普通";
				break;
			case 2:
				options[0] = "难度：困难";
				break;
		}
		switch (Handler::ParAmount) {
			case 0:
				options[1] = "粒子量：无";
				break;
			case 1:
				options[1] = "粒子量：少";
				break;
			case 2:
				options[1] = "粒子量：全";
				break;
		}
		if (Handler::CoMode) options[2] = "双人：开 [WIP]";
		else options[2] = "双人：关";
		for (int i = 0; i < 3; i++) {
			if (i == selectedOption) {
				painter.setPen(QPen(Qt::yellow, 2)); // 选中的选项用黄色显示
			} else {
				painter.setPen(QPen(Qt::white, 2));
			}
			painter.drawText(200, 380 + i * 80, options[i]);
		}
	}

	if (quiting == 1) {
		QString options = "确认退出？";
		painter.setPen(QPen(Qt::yellow, 2));
		painter.drawText(250, 620, options);
	}
}

void MainManager::tick() {
	// 主菜单逻辑更新
	// 通常不需要在这里做太多事情，除非有动画效果
    posDisplay = posDisplay + (position - posDisplay) * 10 * GAME_CLOCK;
	if (Handler::keyPressSet.value(Qt::Key_W, false)) {
		selectedOption = (selectedOption - 1 + 3) % 3; // 循环选择
		if (setting) position.setY(369 + selectedOption * 80);
		else if (!quiting) position.setY(289 + selectedOption * 80);
	}
	if (Handler::keyPressSet.value(Qt::Key_S, false)) {
		selectedOption = (selectedOption + 1) % 3; // 循环选择
		if (setting) position.setY(369 + selectedOption * 80);
		else if (!quiting) position.setY(289 + selectedOption * 80);
	}
	if (Handler::keyPressSet.value(Qt::Key_J, false)) {
		Handler::updateSettings();
		if (setting) {
			switch (selectedOption) {
				case 0: // 难度
					Handler::Difficulty = (Handler::Difficulty + 1) % 3;
					break;
				case 1: // 粒子量
					Handler::ParAmount = (Handler::ParAmount + 1) % 3;
					break;
				case 2: // 双人
					if (Handler::CoMode) Handler::CoMode = false;
					else Handler::CoMode = true;
					break;
			}
		} else if (quiting) {
			QApplication::quit();
		} else {
			switch (selectedOption) {
				case 0: // 开始游戏
					changeTo = 1;
					break;
				case 1: // 设置
					position.setX(180);
					selectedOption = 0;
					setting = 1;
					break;
				case 2: // 退出
					position.setX(180);
					position.setY(609);
					quiting = 1;
					break;
			}
		}
	}
	if (Handler::keyPressSet.value(Qt::Key_K, false)) {
		if (setting) {
			setting = 0;
			position.setX(80);
			position.setY(369);
			selectedOption = 1;
		}
		if (quiting) {
			quiting = 0;
			position.setX(80);
			position.setY(449);
			selectedOption = 2;
		}
	}
}