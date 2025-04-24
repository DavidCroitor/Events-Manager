#pragma once
#include "Service.h"
#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QBoxLayout>
#include <QListWidget>
#include <QDialog>

class USER_GUI: public QWidget {
private:
    Service& serv;

    QListWidget* events;

    QVBoxLayout *mainLayout;
    QGridLayout *allEventsLayout;

    QPushButton* allEventsButton;
    QPushButton* userEventsButton;


public:
    USER_GUI(Service& serv);
    ~USER_GUI();

private:

    void buildGUI();
    void populateList();
    void allEventsButtonHandler();
    void userEventsButtonHandler();

};

class AllEventsDialog: public QDialog {
private:
    Service& serv;

    QListWidget* eventsList;
    QPushButton* nextButton;
    QPushButton* prevButton;
    QPushButton* addButton;

    QPushButton* undoButton;
    QPushButton* redoButton;

    QLabel* titleLabel;
    QLabel* descLabel;
    QLabel* dateLabel;
    QLabel* peopleLabel;
    QLabel* linkLabel;

    int currentIndex;
public:
    AllEventsDialog(Service& serv);
    ~AllEventsDialog();

private slots:
    void nextButtonHandler();
    void prevButtonHandler();
    void addButtonHandler();

    void undoButtonHandler();
    void redoButtonHandler();
};

class UserEventDialog: public QDialog {
    Service& serv;

    QListWidget* eventsList;
    QPushButton* nextButton;
    QPushButton* prevButton;
    QPushButton* removeButton;

    QPushButton* undoButton;
    QPushButton* redoButton;

    QLabel* titleLabel;
    QLabel* descLabel;
    QLabel* dateLabel;
    QLabel* peopleLabel;
    QLabel* linkLabel;

    int currentIndex;

public:
    UserEventDialog(Service& serv);
    ~UserEventDialog();

private slots:
    void populateList();

    void nextButtonHandler();
    void prevButtonHandler();
    void removeButtonHandler();

    void undoButtonHandler();
    void redoButtonHandler();
};
