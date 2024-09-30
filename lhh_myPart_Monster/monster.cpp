#include "Monster.h"

Monster::Monster(int hp, int speed, int gold, QObject *parent)
    : QObject(parent), HP(hp), speed(speed), gold_getted(gold), x(80), y(0), direction(0), moveStep(0) {
    monster_Image.load(":/res_of_qt/KeAiNie.png"); // 怪的图片

    // 行走计时器
    movement_Timer = new QTimer(this);
    connect(movement_Timer, &QTimer::timeout, this, &Monster::move);
    movement_Timer->start(100); // 0.1秒前进一次
}

Monster::~Monster() {
    delete movement_Timer;
}

// move自定义的，按需求改路径，下面写的都是根据那个地图调试的
void Monster::move() {
    // switch (direction) {
    // case 0:
    //     if (moveStep < 190) {
    //         positionY += speed;
    //         moveStep += speed;
    //     } else {
    //         direction = 1;
    //         moveStep = 0;
    //     }
    //     break;
    // case 1:
    //     if (moveStep < 170) {
    //         positionX += speed;
    //         moveStep += speed;
    //     } else {
    //         direction = 2;
    //         moveStep = 0;
    //     }
    //     break;
    // case 2:
    //     if (moveStep < 50) {
    //         positionY -= speed;
    //         moveStep += speed;
    //     } else {
    //         direction = 0;
    //         moveStep = 0;
    //     }
    //     break;
    // }

    if (moveStep < 150) {
        y += speed;
        moveStep += speed;
        takeDamage(1);
    }
    else if (moveStep >= 150 && moveStep < 313){
        x += speed;
        moveStep += speed;
        takeDamage(0.7);
    }
    else if (moveStep >= 313 && moveStep < 373){
        y -= speed;
        moveStep += speed;
        takeDamage(1);
    }
    else if (moveStep >= 373 && moveStep < 688){
        x +=speed;
        moveStep += speed;
        takeDamage(2);
    }
    else if (moveStep >= 688 && moveStep < 748){
        y += speed;
        moveStep += speed;
    }
    else if (moveStep >= 748){
        x +=speed;
    }
    update();
}

void Monster::takeDamage(double damage) {
    HP -= damage;
    checkDeath();
}

bool Monster::isDead() const {
    return HP <= 0;
}

void Monster::update() {
    setRect(x, y, 50, 70);
}

void Monster::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    Q_UNUSED(option);
    Q_UNUSED(widget);

    // QRect drawRect = rect().toRect(); // 将 QRectF 转换为 QRect
    // QSize size = drawRect.size(); // 获取 QRect 的大小

    // 绘制怪物图像
    if (HP > 0){
        // 设置目标大小 50*70好像挺不错，记得改update
        QSize targetSize(50, 70); // 目标宽度和高度

        // 使用 scaled() 方法调整图像大小
        QPixmap scaledImage = monster_Image.scaled(targetSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);

        // 绘制调整大小后的图像
        QRect targetRect(x, y, scaledImage.width(), scaledImage.height());
        painter->drawPixmap(targetRect, scaledImage);
    }

    //画血条
    if (HP > 40)
        painter->setBrush(Qt::green);
    else
        painter->setBrush(Qt::red);
    painter->drawRect(rect().x(), rect().y() - 2, rect().width() * (HP / 100.0), 5);
}

void Monster::checkDeath() {
    if (isDead()) {
        emit monsterKilled(gold_getted); // 发加金币信号
        delete this;
    }
}
