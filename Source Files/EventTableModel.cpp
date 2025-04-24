#include "EventTableModel.h"

#include <utility>

int EventTableModel::rowCount(const QModelIndex &parent) const {
    return events.size();
}

int EventTableModel::columnCount(const QModelIndex &parent) const {
    return 5; // Assuming Event has 5 attributes
}

QVariant EventTableModel::data(const QModelIndex &index, int role) const {
    if (!index.isValid() || role != Qt::DisplayRole)
        return QVariant();

    const Event &event = events[index.row()];
    switch (index.column()) {
        case 0:
            return QString::fromStdString(event.getTitle());
        case 1:
            return QString::fromStdString(event.getDescription());
        case 2:
            return QString::fromStdString(event.getDateAndTime());
        case 3:
            return event.getNumberOfPeople();
        case 4:
            return QString::fromStdString(event.getLink());
        default:
            return QVariant();
    }
}

QVariant EventTableModel::headerData(int section, Qt::Orientation orientation, int role) const {
    if (role != Qt::DisplayRole || orientation != Qt::Horizontal)
        return QVariant();

    switch (section) {
        case 0:
            return QString("Title");
        case 1:
            return QString("Description");
        case 2:
            return QString("Date");
        case 3:
            return QString("Number of People");
        case 4:
            return QString("Link");
        default:
            return QVariant();
    }
}

void EventTableModel::resetModel() {
    beginResetModel();
    events = serv.getAllEvents();
    endResetModel();

}

EventTableModel::EventTableModel(Service& service, QObject *parent)
        : QAbstractTableModel(parent), serv(service) {
    this->events=serv.getAllEvents();

}

