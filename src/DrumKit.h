//
// Created by Guglielmo Fratticioli on 09/07/19.
//

#ifndef MYTEST_DRUMKIT_H
#define MYTEST_DRUMKIT_H

#include <QAbstractListModel>
#include <QVector>
#include "Subject.h"
#include "Enum.h"

class QString;

class Observer;

class Drum;

class DrumKit : public QAbstractListModel, public Subject {
Q_OBJECT
public:
    //CONSTRUCTORS
    explicit DrumKit(QObject *parent = nullptr);

    explicit DrumKit(QVector<Drum *> drums, QObject *parent = nullptr);

    //DESTRUCTOR
    virtual ~DrumKit();

    //SUBJECT
    void notify() override;

    void addObserver(Observer *o) override;

    void removeObserver(Observer *o) override;

    //DRUMKIT
    int rowCount(const QModelIndex &parent) const override;

    bool insertRows(int position, int rows, const QModelIndex &index = QModelIndex()) override;

    bool removeRows(int position, int rows, const QModelIndex &index = QModelIndex()) override;

    QVariant data(const QModelIndex &index, int role) const override;

    Qt::ItemFlags flags(const QModelIndex &index) const override;

    //GETTER & SETTER
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;
    void setDrumStyle(DRUM_STYLE style);

    //TODO CHECK (even in cpp)
    //const QVector<Drum *> &getDrums() const;
    const QVector<Drum*> & getDrums() const{
        return drums;
    }

    DRUM_STYLE getDrumStyle(){
        return drumStyle;
    };



private:
    QVector<Drum *> drums;
    std::list<Observer *> observers;
    DRUM_STYLE drumStyle;
};

#endif //MYTEST_DRUMKIT_H
