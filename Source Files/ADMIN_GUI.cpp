#include "ADMIN_GUI.h"
#include <qlayout.h>
#include <qlabel.h>
#include "Validator.h"
#include <QMessageBox>
#include "RepositoryException.h"

ADMIN_GUI::ADMIN_GUI(Service &s) : serv(s) {
    this->serv.clearHistory();
    this->buildGUI();
    this->resize(900, 700);

    QWidget::setWindowTitle("Admin");

    QObject::connect(this->addButton, &QPushButton::clicked, this, &ADMIN_GUI::addButtonHandler);
    QObject::connect(this->deleteButton, &QPushButton::clicked, this, &ADMIN_GUI::deleteButtonHandler);
    QObject::connect(this->undoButton, &QPushButton::clicked, this, &ADMIN_GUI::undoButtonHandler);
    QObject::connect(this->redoButton, &QPushButton::clicked, this, &ADMIN_GUI::redoButtonHandler);
    QObject::connect(this->tableView, &QTableView::clicked, this, &ADMIN_GUI::onTableClicked);
}
ADMIN_GUI::~ADMIN_GUI(){
    this->serv.clearHistory();
}


void ADMIN_GUI::buildGUI() {

    QVBoxLayout *mainLayout = new QVBoxLayout{this};

    this->tableView = new QTableView;
    this->model = new EventTableModel(serv);

    this->tableView->setModel(model);

    mainLayout->addWidget(tableView);

    QGridLayout *botLayout = new QGridLayout{};

    QLabel *titleLabel = new QLabel{"Title"};
    this->titleEdit = new QLineEdit{};
    QLabel *descLabel = new QLabel{"Description"};
    this->descEdit = new QLineEdit{};
    QLabel *dateLabel = new QLabel{"Date"};
    this->dateEdit = new QLineEdit{};
    QLabel *peopleLabel = new QLabel{"Number of people"};
    this->peopleEdit = new QLineEdit{};
    QLabel *linkLabel = new QLabel{"Link"};
    this->linkEdit = new QLineEdit{};

    botLayout->addWidget(titleLabel, 0, 1);
    botLayout->addWidget(this->titleEdit, 0, 2);
    botLayout->addWidget(descLabel, 1, 1);
    botLayout->addWidget(this->descEdit, 1, 2);
    botLayout->addWidget(dateLabel, 2, 1);
    botLayout->addWidget(this->dateEdit, 2, 2);
    botLayout->addWidget(peopleLabel, 3, 1);
    botLayout->addWidget(this->peopleEdit, 3, 2);
    botLayout->addWidget(linkLabel, 4, 1);
    botLayout->addWidget(this->linkEdit, 4, 2);

    this->addButton = new QPushButton{"Add"};
    this->deleteButton = new QPushButton{"Delete"};
    this->undoButton = new QPushButton{"Undo"};
    this->redoButton = new QPushButton{"Redo"};



    undoButton->setShortcut(QKeySequence(Qt::CTRL+Qt::Key_Z));
    redoButton->setShortcut(QKeySequence(Qt::CTRL+Qt::Key_Y));


    botLayout->addWidget(this->addButton, 1, 3);
    botLayout->addWidget(this->deleteButton, 2, 3);
    botLayout->addWidget(this->undoButton, 1, 0);
    botLayout->addWidget(this->redoButton, 2, 0);


    mainLayout->addLayout(botLayout);
}


void ADMIN_GUI::addButtonHandler() {
    QString title = this->titleEdit->text();
    QString desc = this->descEdit->text();
    QString date = this->dateEdit->text();
    QString people = this->peopleEdit->text();
    QString link = this->linkEdit->text();
    try {
        this->serv.addEvent(title.toStdString(), desc.toStdString(), date.toStdString(), people.toInt(),
                            link.toStdString());
        this->model->resetModel();
    } catch (ValidatorException &er) {
        QMessageBox::warning(this, "Error", er.what());
    }

}

void ADMIN_GUI::deleteButtonHandler() {
    std::string title = this->titleEdit->text().toStdString();
    try {
        this->serv.removeEvent(title);
        this->titleEdit->clear();
        this->descEdit->clear();
        this->dateEdit->clear();
        this->peopleEdit->clear();
        this->linkEdit->clear();
        this->model->resetModel();
    } catch (RepositoryException &er) {
        QMessageBox::warning(this, "Error", er.what());
    }

}

void ADMIN_GUI::onTableClicked(const QModelIndex index) {
    Event event = model->events[index.row()];

    this->titleEdit->setText(QString::fromStdString(event.getTitle()));
    this->descEdit->setText(QString::fromStdString(event.getDescription()));
    this->dateEdit->setText(QString::fromStdString(event.getDateAndTime()));
    this->peopleEdit->setText(QString::number(event.getNumberOfPeople()));
    this->linkEdit->setText(QString::fromStdString(event.getLink()));


}


void ADMIN_GUI::undoButtonHandler() {
    try {
        this->serv.undo();
        this->model->resetModel();
    }catch(std::runtime_error& er){
        QMessageBox::warning(this, "Error", er.what());
    }
}

void ADMIN_GUI::redoButtonHandler() {
    try {
        this->serv.redo();
        this->model->resetModel();
    }catch(std::runtime_error& er){
        QMessageBox::warning(this, "Error", er.what());
    }
}