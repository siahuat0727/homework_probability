#include <cstdlib>
#include <cstring>
#include "widget.h"
#include <QValidator>
#include <iostream>
#include <string>
using namespace std;

struct Coordinate{
    int x, y;
};

Widget::Widget(QWidget *parent) : QWidget(parent)
{
    setWindowTitle("Probability and statistic homework 1");
    scene = new QGraphicsScene();
    view = new QGraphicsView();


    str1 = new QLabel("Number of layers:", this);
    str1->setGeometry(80, 30, 170, 30);

    str2 = new QLabel("Number of each node's children:", this);
    str2->setGeometry(80, 70, 170, 30);

    lineEdit1 = new QLineEdit(this);
    lineEdit1->setGeometry(250,30,30,30);  //設定位置大小
    QValidator *validator1 = new QIntValidator(1,100,this);  //設定輸入範圍0到100
    lineEdit1->setValidator(validator1);

    lineEdit2 = new QLineEdit(this);
    lineEdit2->setGeometry(250,70,30,30);  //設定位置大小
    QValidator *validator2 = new QIntValidator(1,100,this);  //設定輸入範圍0到100
    lineEdit2->setValidator(validator2);

    treeBtn = new QPushButton(this); //第二個參數指定父元件，如果沒有就要用布局管理員，否則無法顯現該元件
    treeBtn->setGeometry(80,110,200,30);         //設定位置大小
    treeBtn->setText("Show tree diagram");               //設定內容文字
    connect(treeBtn, SIGNAL(clicked()), this, SLOT(drawTrees()));

    errorMessage = new QLabel(this);
    errorMessage->setGeometry(80, 140, 230, 40);
}

void Widget::drawTrees(){
    errorMessage->clear();
    try{
        scene->clear();
        const int layer = lineEdit1->text().toInt();
        const int children = lineEdit2->text().toInt();

        const double totalLeaf = pow(children, layer-1);
        int radius = 10;
        int height = 50;
        if(totalLeaf <= 10){
            radius = 30;
            height = 6;
        }else if (totalLeaf <= 20){
            radius = 15;
            height = 10;
        }else if(totalLeaf <= 40){
            radius = 10;
            height = 16;
        }else if(totalLeaf <= 200){
            radius = 5;
            height = 40;
        }else if(totalLeaf > 100000){
            errorMessage->setText("There are too many nodes!");
            return;
        }


        if(layer > 1 && children == 0){
            errorMessage->setText("It is impossible to draw a " + lineEdit1->text() + "-layers tree diagram\nwith each non-leaf-node has 0 child!");
            return;
        }

        int y = 0;
        queue<Coordinate> Q;
        for(int i = 1; i <= layer; ++i){
            const int lengthBetweenTwoNodes = 4*radius*pow(children, layer-i);
            const int totalChildren = pow(children, i-1);
            const int totalLengthOfThisLayer = lengthBetweenTwoNodes * (totalChildren-1);
            const int x_start = -totalLengthOfThisLayer/2;
            const int x_end = x_start + totalLengthOfThisLayer;
            Coordinate parent;
            for(int x = x_start, childIndex = 0; x <= x_end; x+=lengthBetweenTwoNodes, ++childIndex){
                const int drawPosX = x - radius;
                const int drawPosY = y - radius;
                QGraphicsEllipseItem *circle = new QGraphicsEllipseItem(drawPosX, drawPosY, radius*2, radius*2);
                scene->addItem(circle);
                if(childIndex == children)
                    childIndex = 0;
                if(i != 1 && childIndex == 0){
                    parent = Q.front();
                    Q.pop();
                }
                if(i != layer){
                    Coordinate co = {x, y};
                    Q.push(co);
                }
                if(i != 1){
                    QGraphicsLineItem *line = new QGraphicsLineItem(parent.x, parent.y+radius, x, y-radius);
                    scene->addItem(line);
                }
            }
            y += height*radius;
        }

        view->close();
        view->setScene(scene);
        view->show();
    }catch (const std::exception& e) {
        std::cout << e.what();
   }
}
