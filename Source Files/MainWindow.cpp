#include "MainWindow.h"
#include <qlayout.h>
#include <qlabel.h>
#include <QMenuBar>
#include <QToolButton>
#include <QApplication>

MainWindow::MainWindow(Service& s):serv(s) {
    this->buildGUI();
    QWidget::setWindowTitle("Events manager");
    this->resize(500, 350);

    QWidget::connect(this->adminSelectButton, &QPushButton:: clicked, this, &MainWindow::adminButtonHandler);
    QWidget::connect(this->userSelectButton, &QPushButton:: clicked, this, &MainWindow::userButtonHandler);
}

void MainWindow::buildGUI() {
    QVBoxLayout *mainLayout = new QVBoxLayout{this};
    QGridLayout *botLayout = new QGridLayout{};

    this->titleLabel = new QLabel{"Events Manager"};
    QFont titleFont = titleLabel->font();
    titleFont.setPointSize(24);
    titleFont.setBold(true);
    this->titleLabel->setFont(titleFont);
    this->titleLabel->setAlignment(Qt::AlignCenter);
    this->titleLabel->setStyleSheet("border: 2px solid black;padding: 10px; background-color:lightgrey; color:black");

    this->adminSelectButton = new QPushButton{"Admin mode"};
    this->userSelectButton = new QPushButton{"User mode"};
    this->openFileButton = new QToolButton{this};
    this->openFileButton->setText("Open file    ");

    QMenu* menu = new QMenu{this->openFileButton};

    QAction *HTMLFileOpen = new QAction("Open HTML file", this);
    QAction *CSVFileOpen = new QAction("Open CSV file", this);

    connect(HTMLFileOpen, &QAction::triggered, this, &MainWindow::openHTMLFile);
    connect(CSVFileOpen, &QAction::triggered, this, &MainWindow::openCSVFile);

    menu->addAction(HTMLFileOpen);
    menu->addAction(CSVFileOpen);

    openFileButton->setMenu(menu);
    openFileButton->setPopupMode(QToolButton::InstantPopup);

    this->adminSelectButton->setStyleSheet("background-color: purple; color: white;");
    this->userSelectButton->setStyleSheet("background-color: purple; color: white;");
    this->openFileButton->setStyleSheet("background-color: purple; color: white;");


    botLayout->addWidget(this->adminSelectButton, 1, 0);
    botLayout->addWidget(this->userSelectButton, 2, 0);
    botLayout->addWidget(this->openFileButton, 3, 0);


    mainLayout->addWidget(this->titleLabel);
    mainLayout->addLayout(botLayout);

}

void MainWindow::adminButtonHandler() {
    ADMIN_GUI *admin_gui = new ADMIN_GUI(serv);
    admin_gui->setAttribute(Qt::WA_DeleteOnClose);
    admin_gui->show();
}

void MainWindow::userButtonHandler() {
    USER_GUI *user_gui = new USER_GUI(serv);
    user_gui->setAttribute(Qt::WA_DeleteOnClose);
    user_gui->show();
}

void MainWindow::openHTMLFile() {
    system("start ../userEvents.html");
}

void MainWindow::openCSVFile() {
    system("start ../userEvents.csv");
}