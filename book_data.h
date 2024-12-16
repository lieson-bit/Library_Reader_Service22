#ifndef BOOK_DATA_H
#define BOOK_DATA_H

#include <QObject>
#include <QString>

class Book_data: public QObject
{
    Q_OBJECT

public:
    enum publisherType{
        Jmax_lim,
        Ted_talks,
        Guap,
        Te_library,
        UNZA
    };
    explicit Book_data(QObject *parent =nullptr);
    Book_data(QString title, QString writer, publisherType type, int year);
    bool check(QString title);
    QString gettitle() const;
    QString getwriter() const;
    int getyear() const;
    publisherType getType() const;

private:
    QString title;
    QString writer;
    int year;
    publisherType type;
};

#endif // BOOK_DATA_H
