#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QPainter>
#include <QLabel>

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr); // 构造
    ~MainWindow(); // 析构
    void spawnMonster(); // 出怪点

protected:
    // void paintEvent(QPaintEvent *event) override; // 本来想画背景图的，不用了

private:
    QGraphicsScene *scene;
    void setupScene(); // 设置场景
    QTimer *spawnTimer; // 定时器
    QLabel *goldLabel; // 用于显示金币数
    int goldCount; // 当前金币数
};

#endif
