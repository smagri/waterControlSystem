/********************************************************************************
** Form generated from reading UI file 'tanklevel.ui'
**
** Created: Sun Nov 2 19:56:22 2014
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
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QWidget>
#include "qwt_plot.h"
#include "qwt_slider.h"
#include "qwt_text_label.h"

QT_BEGIN_NAMESPACE

class Ui_TankLevel
{
public:
    QWidget *widget;
    QGridLayout *gridLayout;
    QwtPlot *qwtPlot;
    QwtSlider *sliderAbsoluteLevel;
    QwtSlider *sliderPercentageLevel;
    QwtTextLabel *labelAbsLevel;
    QwtTextLabel *labelPercentLevel;

    void setupUi(QWidget *TankLevel)
    {
        if (TankLevel->objectName().isEmpty())
            TankLevel->setObjectName(QString::fromUtf8("TankLevel"));
        TankLevel->resize(849, 543);
        widget = new QWidget(TankLevel);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(40, 30, 771, 481));
        gridLayout = new QGridLayout(widget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        qwtPlot = new QwtPlot(widget);
        qwtPlot->setObjectName(QString::fromUtf8("qwtPlot"));

        gridLayout->addWidget(qwtPlot, 0, 0, 2, 1);

        sliderAbsoluteLevel = new QwtSlider(widget);
        sliderAbsoluteLevel->setObjectName(QString::fromUtf8("sliderAbsoluteLevel"));
        sliderAbsoluteLevel->setMinimumSize(QSize(31, 0));
        sliderAbsoluteLevel->setMaximumSize(QSize(100, 16777215));
        sliderAbsoluteLevel->setSizeIncrement(QSize(0, 0));
        sliderAbsoluteLevel->setReadOnly(true);
        sliderAbsoluteLevel->setOrientation(Qt::Vertical);
        sliderAbsoluteLevel->setScalePosition(QwtSlider::RightScale);
        sliderAbsoluteLevel->setHandleSize(QSize(32, 16));

        gridLayout->addWidget(sliderAbsoluteLevel, 0, 1, 1, 1);

        sliderPercentageLevel = new QwtSlider(widget);
        sliderPercentageLevel->setObjectName(QString::fromUtf8("sliderPercentageLevel"));
        sliderPercentageLevel->setMinimumSize(QSize(36, 0));
        sliderPercentageLevel->setMaximumSize(QSize(100, 16777215));
        sliderPercentageLevel->setSizeIncrement(QSize(100, 100));
        sliderPercentageLevel->setReadOnly(true);
        sliderPercentageLevel->setOrientation(Qt::Vertical);
        sliderPercentageLevel->setScalePosition(QwtSlider::RightScale);

        gridLayout->addWidget(sliderPercentageLevel, 0, 2, 1, 1);

        labelAbsLevel = new QwtTextLabel(widget);
        labelAbsLevel->setObjectName(QString::fromUtf8("labelAbsLevel"));
        labelAbsLevel->setMaximumSize(QSize(100, 16777215));
        labelAbsLevel->setFrameShape(QFrame::Box);

        gridLayout->addWidget(labelAbsLevel, 1, 1, 1, 1);

        labelPercentLevel = new QwtTextLabel(widget);
        labelPercentLevel->setObjectName(QString::fromUtf8("labelPercentLevel"));
        labelPercentLevel->setMaximumSize(QSize(100, 16777215));
        labelPercentLevel->setFrameShape(QFrame::Box);

        gridLayout->addWidget(labelPercentLevel, 1, 2, 1, 1);

        qwtPlot->raise();
        sliderPercentageLevel->raise();
        labelAbsLevel->raise();
        labelPercentLevel->raise();
        sliderAbsoluteLevel->raise();

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
