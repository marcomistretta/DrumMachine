//
// Created by Guglielmo Fratticioli on 09/07/19.
//

#include <utility>
#include "DrumKit.h"
#include "Drum.h"
#include "Subject.h"

#include <QMetaType>
#include <QDebug>

//CONSTRUCTORS
DrumKit::DrumKit(QObject *parent) : QAbstractListModel(parent) {
    setDrumStyle(POP);
}

DrumKit::DrumKit(QVector<Drum *> drums, QObject *parent) : QAbstractListModel(parent), drums(std::move(drums)) {}

int DrumKit::rowCount(const QModelIndex &parent) const {
    return parent.isValid() ? 0 : drums.size();
}

QVariant DrumKit::data(const QModelIndex &index, int role) const {
    if (!index.isValid())
        return QVariant();
    if (index.row() >= drums.size() || index.row() < 0)
        return QVariant();
    if (role == Qt::DisplayRole) {
        const auto &drum = drums.at(index.row());
        return QVariant::fromValue(drum);
    }
    return QVariant();
}

bool DrumKit::setData(const QModelIndex &index, const QVariant &value, int role) {
    if (index.isValid() && role == Qt::EditRole) {
        const int row = index.row();
        auto drum = drums.value(row);
        drum = value.value<Drum *>();
        drums.replace(row, drum);
        emit dataChanged(index, index, {Qt::DisplayRole, Qt::EditRole});
        return true;
    }
    return false;
}

bool DrumKit::insertRows(int position, int rows, const QModelIndex &index) {
    Q_UNUSED(index);
    beginInsertRows(QModelIndex(), position, position + rows - 1);

    for (int row = 0; row < rows; ++row)
        drums.insert(position, new Drum());

    endInsertRows();
    return true;
}

bool DrumKit::removeRows(int position, int rows, const QModelIndex &index) {
    Q_UNUSED(index)
    beginRemoveRows(QModelIndex(), position, position + rows - 1);

    for (int row = 0; row < rows; ++row)
        drums.removeAt(position);

    endRemoveRows();
    return true;
}

Qt::ItemFlags DrumKit::flags(const QModelIndex &index) const {
    if (!index.isValid())
        return Qt::ItemIsEnabled;
    return QAbstractListModel::flags(index) | Qt::ItemIsEditable;
}

/*
const QVector<Drum *> &DrumKit::getDrums() const {
    return drums;
}*/

void DrumKit::notify() {
    for (Observer *observer : observers)
        observer->obsUpdate();
    //qDebug() << "DrumKit Observer notified";
}

void DrumKit::addObserver(Observer *o) {
    //qDebug() << "DrumKit Observer added";
    observers.push_back(o);
}

void DrumKit::removeObserver(Observer *o) {
    //qDebug() << "DrumKit Observer removed";
    observers.remove(o);
}

void DrumKit::setDrumStyle(DRUM_STYLE style) {
    drumStyle = style;
    notify();
    //qDebug()<< style;
    for(Drum* drum: drums)
        drum->setDrumStyle(style);
}
DrumKit::~DrumKit() {
    for (auto i : drums)
        delete i;
    drums.clear();
    for (auto i : observers)
        delete i;
    observers.clear();
}
