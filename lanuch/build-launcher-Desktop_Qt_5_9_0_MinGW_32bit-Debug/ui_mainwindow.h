/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QLabel *label;
    QLabel *label_2;
    QLineEdit *username;
    QLineEdit *password;
    QPushButton *register_2;
    QPushButton *createroom;
    QPushButton *follow;
    QLineEdit *room_no;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(868, 569);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(60, 70, 61, 121));
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(50, 230, 51, 101));
        username = new QLineEdit(centralWidget);
        username->setObjectName(QStringLiteral("username"));
        username->setGeometry(QRect(180, 100, 381, 51));
        password = new QLineEdit(centralWidget);
        password->setObjectName(QStringLiteral("password"));
        password->setGeometry(QRect(180, 260, 361, 51));
        password->setEchoMode(QLineEdit::Password);
        register_2 = new QPushButton(centralWidget);
        register_2->setObjectName(QStringLiteral("register_2"));
        register_2->setGeometry(QRect(90, 360, 121, 41));
        createroom = new QPushButton(centralWidget);
        createroom->setObjectName(QStringLiteral("createroom"));
        createroom->setGeometry(QRect(420, 360, 121, 41));
        follow = new QPushButton(centralWidget);
        follow->setObjectName(QStringLiteral("follow"));
        follow->setGeometry(QRect(440, 490, 121, 51));
        room_no = new QLineEdit(centralWidget);
        room_no->setObjectName(QStringLiteral("room_no"));
        room_no->setGeometry(QRect(190, 490, 211, 41));
        MainWindow->setCentralWidget(centralWidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", Q_NULLPTR));
        label->setText(QApplication::translate("MainWindow", "\347\224\250\346\210\267\345\220\215", Q_NULLPTR));
        label_2->setText(QApplication::translate("MainWindow", "\345\257\206\347\240\201", Q_NULLPTR));
        register_2->setText(QApplication::translate("MainWindow", "\346\263\250\345\206\214", Q_NULLPTR));
        createroom->setText(QApplication::translate("MainWindow", "\345\273\272\346\210\277", Q_NULLPTR));
        follow->setText(QApplication::translate("MainWindow", "\350\267\237\346\210\277", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
