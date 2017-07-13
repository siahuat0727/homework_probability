#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsEllipseItem>
#include <QGraphicsLineItem>
#include <QLabel>
#include <QLineEdit>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <queue>


class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = 0);
private slots:
    void drawTrees();
private:
    QLineEdit *lineEdit1;
    QLineEdit *lineEdit2;
    QPushButton *treeBtn;
    QLabel *str1;
    QLabel *str2;
    QGraphicsScene *scene;
    QGraphicsView * view;
    QWidget *errorWidget;
    QLabel *errorMessage;
};

#endif // WIDGET_H

