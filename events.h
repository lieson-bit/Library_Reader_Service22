#ifndef EVENTS_H
#define EVENTS_H

#include "headers.h"

class Events
{
public:
    Events();
};

class Custom_View: public QGraphicsView
{
    Q_OBJECT
public:
    explicit Custom_View(QWidget *parent = nullptr);
protected:
    void dragEnterEvent(QDragEnterEvent * event);
    void dragLeaverEvent(QDragLeaveEvent * event);
    void dragMoveEvent(QDragMoveEvent * event);
    void dropEvent(QDropEvent *event);

protected:
    QGraphicsScene *scene;
    QString configFilePath;  // Path to the configuration file

    void loadPersistedData();
    void savePersistedData(const QString &filePath);
};

#endif // EVENTS_H
