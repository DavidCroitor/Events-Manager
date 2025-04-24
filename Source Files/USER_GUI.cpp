#include "USER_GUI.h"
#include "RepositoryException.h"
#include <QBoxLayout>
#include <QFrame>
#include <QDialog>
#include <QMessageBox>

USER_GUI::USER_GUI(Service &s) : serv(s) {
    this->serv.clearHistory();
    this->buildGUI();
    this->populateList();
    this->resize(500, 350);

    this->setWindowTitle("User");

    QWidget::connect(this->allEventsButton, &QPushButton::clicked, this, &USER_GUI::allEventsButtonHandler);
    QWidget::connect(this->userEventsButton, &QPushButton::clicked, this, &USER_GUI::userEventsButtonHandler);

}

USER_GUI::~USER_GUI(){
    this->serv.clearHistory();
}

void USER_GUI::buildGUI() {
    this->mainLayout = new QVBoxLayout{this};

    QGridLayout *botLayout = new QGridLayout();

    this->events = new QListWidget{};

    this->allEventsButton = new QPushButton("All events");
    this->userEventsButton = new QPushButton("User events");

    botLayout->addWidget(this->allEventsButton, 1, 0);
    botLayout->addWidget(this->userEventsButton, 1, 1);

    this->mainLayout->addLayout(botLayout);

}

void USER_GUI::allEventsButtonHandler() {
    auto *eventsDialog = new AllEventsDialog{serv};
    eventsDialog->setAttribute(Qt::WA_DeleteOnClose);
    eventsDialog->show();

}

void USER_GUI::userEventsButtonHandler() {
    auto *eventsDialog = new UserEventDialog{serv};
    eventsDialog->setAttribute(Qt::WA_DeleteOnClose);
    eventsDialog->show();
}

void USER_GUI::populateList() {
    this->events->clear();
    for (auto &event: this->serv.getAllEvents()) {
        auto item = QString::fromStdString(event.getTitle());
        events->addItem(item);
    }

}

AllEventsDialog::AllEventsDialog(Service &s) : serv(s) {
    this->serv.clearHistory();
    this->eventsList = new QListWidget{};
    for (auto &event: this->serv.getAllEvents()) {
        auto item = QString::fromStdString(event.getTitle());
        eventsList->addItem(item);
    }
    this->currentIndex = -1;

    this->setWindowTitle("Events");
    this->resize(250, 200);

    auto *layout = new QVBoxLayout{this};

    titleLabel = new QLabel{"Title"};
    descLabel = new QLabel{"Description"};
    dateLabel = new QLabel{"Date"};
    peopleLabel = new QLabel{"People"};
    linkLabel = new QLabel{"Link"};

    auto frame = new QFrame{};
    frame->setFrameStyle(QFrame::Box | QFrame::Plain);
    auto eventLayout = new QGridLayout{frame};
    eventLayout->addWidget(titleLabel, 0, 0);
    eventLayout->addWidget(descLabel, 1, 0);
    eventLayout->addWidget(dateLabel, 2, 0);
    eventLayout->addWidget(peopleLabel, 3, 0);
    eventLayout->addWidget(linkLabel, 4, 0);

    auto frameLayout = new QHBoxLayout{};

    nextButton = new QPushButton{"Next"};
    prevButton = new QPushButton{"Previous"};
    addButton = new QPushButton{"Add"};
    undoButton = new QPushButton{"Undo"};
    redoButton = new QPushButton{"Redo"};

    frameLayout->addWidget(prevButton);
    frameLayout->addWidget(frame);
    frameLayout->addWidget(nextButton);

    auto buttonsLayout = new QHBoxLayout{};

    buttonsLayout->addWidget(redoButton);
    buttonsLayout->addWidget(addButton);
    buttonsLayout->addWidget(undoButton);

    layout->addLayout(frameLayout);
    layout->addLayout(buttonsLayout);

    setLayout(layout);

    connect(nextButton, &QPushButton::clicked, this, &AllEventsDialog::nextButtonHandler);
    connect(prevButton, &QPushButton::clicked, this, &AllEventsDialog::prevButtonHandler);
    connect(addButton, &QPushButton::clicked, this, &AllEventsDialog::addButtonHandler);
    connect(undoButton, &QPushButton::clicked, this, &AllEventsDialog::undoButtonHandler);
    connect(redoButton, &QPushButton::clicked, this, &AllEventsDialog::redoButtonHandler);

}

AllEventsDialog::~AllEventsDialog(){
    this->serv.clearHistory();
}

void AllEventsDialog::nextButtonHandler() {
    if (this->currentIndex == this->eventsList->count() - 1) {
        this->currentIndex = 0;
    } else {
        this->currentIndex++;
    }
    this->eventsList->setCurrentRow(this->currentIndex);

    this->titleLabel->setText(QString::fromStdString(this->serv.getAllEvents()[this->currentIndex].getTitle()));
    this->descLabel->setText(QString::fromStdString(this->serv.getAllEvents()[this->currentIndex].getDescription()));
    this->dateLabel->setText(QString::fromStdString(this->serv.getAllEvents()[this->currentIndex].getDateAndTime()));
    this->peopleLabel->setText(
            QString::fromStdString(std::to_string(this->serv.getAllEvents()[this->currentIndex].getNumberOfPeople())));
    this->linkLabel->setText(QString::fromStdString(this->serv.getAllEvents()[this->currentIndex].getLink()));

}

void AllEventsDialog::prevButtonHandler() {
    if (this->currentIndex <= 0) {
        this->currentIndex = this->eventsList->count() - 1;
    } else {
        this->currentIndex--;
    }
    this->eventsList->setCurrentRow(this->currentIndex);

    this->titleLabel->setText(QString::fromStdString(this->serv.getAllEvents()[this->currentIndex].getTitle()));
    this->descLabel->setText(QString::fromStdString(this->serv.getAllEvents()[this->currentIndex].getDescription()));
    this->dateLabel->setText(QString::fromStdString(this->serv.getAllEvents()[this->currentIndex].getDateAndTime()));
    this->peopleLabel->setText(
            QString::fromStdString(std::to_string(this->serv.getAllEvents()[this->currentIndex].getNumberOfPeople())));
    this->linkLabel->setText(QString::fromStdString(this->serv.getAllEvents()[this->currentIndex].getLink()));
}

void AllEventsDialog::addButtonHandler() {
    try {
        auto title = this->titleLabel->text().toStdString();
        auto event = this->serv.getEvent(title);
        this->serv.addUserEvent(event);
    }
    catch (RepositoryException &er) {
        QMessageBox::warning(this, "Error", "You are already participating to this event!");
    }
}

void AllEventsDialog::undoButtonHandler() {
    try{
        this->serv.undo();
    }
    catch (std::runtime_error& er)  {
        QMessageBox::warning(this, "Error", "No more undos!");
    }
}

void AllEventsDialog::redoButtonHandler() {
    try{
        this->serv.redo();
    }
    catch (std::runtime_error& er){
        QMessageBox::warning(this, "Error", "No more undos!");
    }
}

UserEventDialog::UserEventDialog(Service &s) : serv(s) {
    this->serv.clearHistory();

    this->eventsList = new QListWidget{};
    this->populateList();
    this->currentIndex = -1;

    this->setWindowTitle("User events");
    this->resize(250, 200);

    auto *layout = new QVBoxLayout{this};

    titleLabel = new QLabel{"Title"};
    descLabel = new QLabel{"Description"};
    dateLabel = new QLabel{"Date"};
    peopleLabel = new QLabel{"People"};
    linkLabel = new QLabel{"Link"};

    auto frame = new QFrame{};
    frame->setFrameStyle(QFrame::Box | QFrame::Plain);
    auto eventLayout = new QGridLayout{frame};
    eventLayout->addWidget(titleLabel, 0, 0);
    eventLayout->addWidget(descLabel, 1, 0);
    eventLayout->addWidget(dateLabel, 2, 0);
    eventLayout->addWidget(peopleLabel, 3, 0);
    eventLayout->addWidget(linkLabel, 4, 0);

    auto frameLayout = new QHBoxLayout{};

    nextButton = new QPushButton{"Next"};
    prevButton = new QPushButton{"Previous"};
    removeButton = new QPushButton{"Remove"};
    undoButton = new QPushButton{"Undo"};
    redoButton = new QPushButton{"Redo"};

    undoButton->setShortcut(QKeySequence(Qt::CTRL+Qt::Key_Z));
    redoButton->setShortcut(QKeySequence(Qt::CTRL+Qt::Key_Y));

    frameLayout->addWidget(prevButton);
    frameLayout->addWidget(frame);
    frameLayout->addWidget(nextButton);

    auto buttonsLayout = new QHBoxLayout{};

    buttonsLayout->addWidget(redoButton);
    buttonsLayout->addWidget(removeButton);
    buttonsLayout->addWidget(undoButton);

    layout->addLayout(frameLayout);
    layout->addLayout(buttonsLayout);

    setLayout(layout);

    connect(nextButton, &QPushButton::clicked, this, &UserEventDialog::nextButtonHandler);
    connect(prevButton, &QPushButton::clicked, this, &UserEventDialog::prevButtonHandler);
    connect(removeButton, &QPushButton::clicked, this, &UserEventDialog::removeButtonHandler);
    connect(undoButton, &QPushButton::clicked, this, &UserEventDialog::undoButtonHandler);
    connect(redoButton, &QPushButton::clicked, this, &UserEventDialog::redoButtonHandler);

}

UserEventDialog::~UserEventDialog() {
    this->serv.clearHistory();
}

void UserEventDialog::populateList() {
    this->currentIndex = -1;
    this->eventsList->clear();
    for (auto &event: this->serv.getUserEvents()) {
        auto item = QString::fromStdString(event.getTitle());
        eventsList->addItem(item);
    }
}

void UserEventDialog::nextButtonHandler() {
    if (this->eventsList->count() == 0) {
        this->titleLabel->setText("");
        this->descLabel->setText("");
        this->dateLabel->setText("No events");
        this->peopleLabel->setText("");
        this->linkLabel->setText("");
        return;
    } else {
        if (this->currentIndex == this->eventsList->count() - 1) {
            this->currentIndex = 0;
        } else {
            this->currentIndex++;
        }
        this->eventsList->setCurrentRow(this->currentIndex);


        this->titleLabel->setText(QString::fromStdString(this->serv.getUserEvents()[this->currentIndex].getTitle()));
        this->descLabel->setText(
                QString::fromStdString(this->serv.getUserEvents()[this->currentIndex].getDescription()));
        this->dateLabel->setText(
                QString::fromStdString(this->serv.getUserEvents()[this->currentIndex].getDateAndTime()));
        this->peopleLabel->setText(QString::fromStdString(
                std::to_string(this->serv.getUserEvents()[this->currentIndex].getNumberOfPeople())));
        this->linkLabel->setText(QString::fromStdString(this->serv.getUserEvents()[this->currentIndex].getLink()));
    }
}

void UserEventDialog::prevButtonHandler() {
    if (this->eventsList->count() == 0) {
        this->titleLabel->setText("");
        this->descLabel->setText("");
        this->dateLabel->setText("No events");
        this->peopleLabel->setText("");
        this->linkLabel->setText("");
        return;
    } else {
        if (this->currentIndex <= 0) {
            this->currentIndex = this->eventsList->count() - 1;
        } else {
            this->currentIndex--;

            this->eventsList->setCurrentRow(this->currentIndex);

            this->titleLabel->setText(
                    QString::fromStdString(this->serv.getUserEvents()[this->currentIndex].getTitle()));
            this->descLabel->setText(
                    QString::fromStdString(this->serv.getUserEvents()[this->currentIndex].getDescription()));
            this->dateLabel->setText(
                    QString::fromStdString(this->serv.getUserEvents()[this->currentIndex].getDateAndTime()));
            this->peopleLabel->setText(QString::fromStdString(
                    std::to_string(this->serv.getUserEvents()[this->currentIndex].getNumberOfPeople())));
            this->linkLabel->setText(QString::fromStdString(this->serv.getUserEvents()[this->currentIndex].getLink()));

        }
    }
}

void UserEventDialog::removeButtonHandler() {
    try {
        auto title = this->titleLabel->text().toStdString();
        auto item = this->eventsList->currentItem();
        this->eventsList->removeItemWidget(item);
        this->serv.removeUserEvent(title);
        this->populateList();
    }
    catch (RepositoryException &er) {
        QMessageBox::warning(this, "Error", "Event already removed!");
    }
}

void UserEventDialog::undoButtonHandler() {
    try{
        this->serv.undo();
        this->populateList();
    }
    catch (std::runtime_error& er){
        QMessageBox::warning(this, "Error", "No more undos!");

    }
}

void UserEventDialog::redoButtonHandler() {
    try{
        this->serv.redo();
        this->populateList();
    }
    catch (std::runtime_error& er){
        QMessageBox::warning(this, "Error", "No more redos!");
    }
}