#include <QApplication>
#include "ADMIN_GUI.h"
#include "MainWindow.h"

class FileTypeDialog : public QDialog {
public:
    FileTypeDialog(QWidget *parent = nullptr) : QDialog(parent) {
        QPushButton *htmlButton = new QPushButton("HTML", this);
        QPushButton *csvButton = new QPushButton("CSV", this);

        connect(htmlButton, &QPushButton::clicked, [this]() { done(1); });
        connect(csvButton, &QPushButton::clicked, [this]() { done(2); });

        QVBoxLayout *layout = new QVBoxLayout(this);
        layout->addWidget(htmlButton);
        layout->addWidget(csvButton);
    }
};


int main(int argc, char **argv) {
    QApplication app(argc, argv);

    FileTypeDialog dialog;
    int type = dialog.exec();
    FileRepository repo{"../events.csv", type};
    Service service{repo};
    MainWindow main{service};
    main.show();

    return app.exec();
}