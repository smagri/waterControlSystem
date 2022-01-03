/********************************************************************************
** Form generated from reading UI file 'tanklevel.ui'
**
** Created: Tue Oct 28 21:32:05 2014
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TANKLEVEL_H
#define UI_TANKLEVEL_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QWidget>
#include "qwt_plot.h"
#include "qwt_slider.h"

QT_BEGIN_NAMESPACE

class Ui_TankLevel
{
public:
    QwtPlot *qwtPlot;
    QwtSlider *Slider_2;
    QwtSlider *Slider_3;

    void setupUi(QWidget *TankLevel)
    {
        if (TankLevel->objectName().isEmpty())
            TankLevel->setObjectName(QString::fromUtf8("TankLevel"));
        TankLevel->resize(733, 369);
        qwtPlot = new QwtPlot(TankLevel);
        qwtPlot->setObjectName(QString::fromUtf8("qwtPlot"));
        qwtPlot->setGeometry(QRect(60, 80, 400, 200));
        Slider_2 = new QwtSlider(TankLevel);
        Slider_2->setObjectName(QString::fromUtf8("Slider_2"));
        Slider_2->setGeometry(QRect(580, 80, 61, 171));
        Slider_2->setOrientation(Qt::Vertical);
        Slider_3 = new QwtSlider(TankLevel);
        Slider_3->setObjectName(QString::fromUtf8("Slider_3"));
        Slider_3->setGeometry(QRect(480, 80, 61, 171));
        Slider_3->setOrientation(Qt::Vertical);

        retranslateUi(TankLevel);

        QMetaObject::connectSlotsByName(TankLevel);
    } // setupUi

    void retranslateUi(QWidget *TankLevel)
    {
        TankLevel->setWindowTitle(QApplication::translate("TankLevel", "TankLevel", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class TankLevel: public Ui_TankLevel {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TANKLEVEL_H
