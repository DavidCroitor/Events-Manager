#pragma once
#include <qmainwindow.h>
#include <qlistwidget.h>
#include <qpushbutton.h>
#include <QLabel>
#include <QComboBox>
#include "ADMIN_GUI.h"
#include "USER_GUI.h"

class MainWindow: public QWidget {
private:
    Service& serv;

    QLabel *titleLabel;
    QPushButton* adminSelectButton;
    QPushButton* userSelectButton;
    QToolButton* openFileButton;
public:

    MainWindow(Service& serv);

private:

    void buildGUI();
    void adminButtonHandler();
    void userButtonHandler();

    static  void openHTMLFile();
    static  void openCSVFile();
};

