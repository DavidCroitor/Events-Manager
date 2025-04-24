#pragma once
#include <qwidget.h>
#include "Service.h"
#include <qlistwidget.h>
#include <qlineedit.h>
#include <qpushbutton.h>
#include "EventTableModel.h"
#include <QTableView>

class ADMIN_GUI: public QWidget{
    friend class EventTableModel;
//    Q_OBJECT
private:
    Service& serv;

    QTableView* tableView;
    EventTableModel* model;

    QLineEdit* titleEdit;
    QLineEdit* descEdit;
    QLineEdit* dateEdit;
    QLineEdit* peopleEdit;
    QLineEdit* linkEdit;

    QPushButton* undoButton;
    QPushButton* redoButton;

    QPushButton* addButton;
    QPushButton* deleteButton;

public:

    ADMIN_GUI(Service& serv);
    ~ADMIN_GUI();

private:

    void buildGUI();

    void addButtonHandler();
    void deleteButtonHandler();

    void undoButtonHandler();
    void redoButtonHandler();

private slots:

    void onTableClicked( const QModelIndex index);

};

