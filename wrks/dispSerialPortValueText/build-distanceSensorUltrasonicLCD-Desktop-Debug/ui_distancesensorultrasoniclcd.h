/********************************************************************************
** Form generated from reading UI file 'distancesensorultrasoniclcd.ui'
**
** Created by: Qt User Interface Compiler version 4.8.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DISTANCESENSORULTRASONICLCD_H
#define UI_DISTANCESENSORULTRASONICLCD_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QStatusBar>
#include <QtGui/QToolBar>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>
#include "qwt_plot.h"
#include "qwt_slider.h"
#include "qwt_text_label.h"

QT_BEGIN_NAMESPACE

class Ui_distanceSensorUltrasonicLCD
{
public:
    QWidget *centralWidget;
    QWidget *verticalLayoutWidget_2;
    QVBoxLayout *verticalLayout_3;
    QwtPlot *qwtPlot;
    QwtTextLabel *PlotTitleTextLabel;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QwtTextLabel *TextLabel;
    QwtTextLabel *QwtTextLabelDistance;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QwtSlider *Slider;
    QMenuBar *menuBar;
    QMenu *menudistanceSensorUltrasonicLCD;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *distanceSensorUltrasonicLCD)
    {
        if (distanceSensorUltrasonicLCD->objectName().isEmpty())
            distanceSensorUltrasonicLCD->setObjectName(QString::fromUtf8("distanceSensorUltrasonicLCD"));
        distanceSensorUltrasonicLCD->resize(1304, 906);
        centralWidget = new QWidget(distanceSensorUltrasonicLCD);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        verticalLayoutWidget_2 = new QWidget(centralWidget);
        verticalLayoutWidget_2->setObjectName(QString::fromUtf8("verticalLayoutWidget_2"));
        verticalLayoutWidget_2->setGeometry(QRect(320, 20, 951, 741));
        verticalLayout_3 = new QVBoxLayout(verticalLayoutWidget_2);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        qwtPlot = new QwtPlot(verticalLayoutWidget_2);
        qwtPlot->setObjectName(QString::fromUtf8("qwtPlot"));
        qwtPlot->setAutoReplot(false);

        verticalLayout_3->addWidget(qwtPlot);

        PlotTitleTextLabel = new QwtTextLabel(verticalLayoutWidget_2);
        PlotTitleTextLabel->setObjectName(QString::fromUtf8("PlotTitleTextLabel"));

        verticalLayout_3->addWidget(PlotTitleTextLabel);

        verticalLayoutWidget = new QWidget(centralWidget);
        verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(20, 20, 291, 121));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        TextLabel = new QwtTextLabel(verticalLayoutWidget);
        TextLabel->setObjectName(QString::fromUtf8("TextLabel"));

        verticalLayout->addWidget(TextLabel);

        QwtTextLabelDistance = new QwtTextLabel(verticalLayoutWidget);
        QwtTextLabelDistance->setObjectName(QString::fromUtf8("QwtTextLabelDistance"));

        verticalLayout->addWidget(QwtTextLabelDistance);

        horizontalLayoutWidget = new QWidget(centralWidget);
        horizontalLayoutWidget->setObjectName(QString::fromUtf8("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(20, 170, 291, 591));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        Slider = new QwtSlider(horizontalLayoutWidget);
        Slider->setObjectName(QString::fromUtf8("Slider"));
        Slider->setUpperBound(400);

        horizontalLayout->addWidget(Slider);

        distanceSensorUltrasonicLCD->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(distanceSensorUltrasonicLCD);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1304, 39));
        menudistanceSensorUltrasonicLCD = new QMenu(menuBar);
        menudistanceSensorUltrasonicLCD->setObjectName(QString::fromUtf8("menudistanceSensorUltrasonicLCD"));
        distanceSensorUltrasonicLCD->setMenuBar(menuBar);
        mainToolBar = new QToolBar(distanceSensorUltrasonicLCD);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        distanceSensorUltrasonicLCD->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(distanceSensorUltrasonicLCD);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        distanceSensorUltrasonicLCD->setStatusBar(statusBar);

        menuBar->addAction(menudistanceSensorUltrasonicLCD->menuAction());

        retranslateUi(distanceSensorUltrasonicLCD);

        QMetaObject::connectSlotsByName(distanceSensorUltrasonicLCD);
    } // setupUi

    void retranslateUi(QMainWindow *distanceSensorUltrasonicLCD)
    {
        distanceSensorUltrasonicLCD->setWindowTitle(QApplication::translate("distanceSensorUltrasonicLCD", "distanceSensorUltrasonicLCD", 0, QApplication::UnicodeUTF8));
        PlotTitleTextLabel->setPlainText(QApplication::translate("distanceSensorUltrasonicLCD", "Ultrasonic HC-SR04 and LCD1602 Distance (2cm - 4m range)", 0, QApplication::UnicodeUTF8));
        TextLabel->setPlainText(QApplication::translate("distanceSensorUltrasonicLCD", "Distance\n"
"(cm)", 0, QApplication::UnicodeUTF8));
        QwtTextLabelDistance->setPlainText(QApplication::translate("distanceSensorUltrasonicLCD", "Value", 0, QApplication::UnicodeUTF8));
        menudistanceSensorUltrasonicLCD->setTitle(QApplication::translate("distanceSensorUltrasonicLCD", "dista&nceSensorUltrasonicLCD", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class distanceSensorUltrasonicLCD: public Ui_distanceSensorUltrasonicLCD {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DISTANCESENSORULTRASONICLCD_H
