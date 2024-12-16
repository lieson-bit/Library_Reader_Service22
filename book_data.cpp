#include "book_data.h"
#include "headers.h"

Book_data::Book_data(QObject *parent)
    : QObject(parent), title(""), writer(""), year(0), type(Jmax_lim) {}

Book_data::Book_data(QString title, QString writer, publisherType type, int year)
    : title(title), writer(writer), year(year), type(type) {}

bool Book_data::check(QString title) {
    MainWindow conn;
    if (!conn.connOpen()) {
        qDebug() << "Failed to open the database when reading for book data";
        return false;
    }

    QSqlQuery qry;
    qry.prepare("SELECT * FROM books_table WHERE title=:title");
    qry.bindValue(":title", title);

    if (qry.exec() && qry.next()) {
        qDebug() << "Book found in the database";

        int totalNumofCopies = qry.value("totalNumofCopies").toInt();
        int numofCopiesAvail = qry.value("NumofCopiesAvail").toInt();

        // Decrease the values by 1
        totalNumofCopies -= 1;
        numofCopiesAvail -= 1;

        // Update the database with the new values
        QSqlQuery updateQry;
        updateQry.prepare("UPDATE books_table SET totalNumofCopies=:totalNumofCopies, NumofCopiesAvail=:NumofCopiesAvail WHERE title=:title");
        updateQry.bindValue(":totalNumofCopies", totalNumofCopies);
        updateQry.bindValue(":NumofCopiesAvail", numofCopiesAvail);
        updateQry.bindValue(":title", title);

        if (updateQry.exec()) {
            qDebug() << "Book copies updated successfully";
            conn.connClose(); // Close the connection
            return true;
        } else {
            qDebug() << "Failed to update book copies: " << updateQry.lastError().text();
            conn.connClose(); // Close the connection
            return false;
        }
    } else {
        qDebug() << "Book not found in the database";
        if (qry.lastError().isValid()) {
            qDebug() << "Error: " << qry.lastError().text();
        }
        conn.connClose(); // Close the connection
        return false;
    }
}



QString Book_data::gettitle() const
{
    return title;
}

QString Book_data::getwriter() const
{
    return  writer;
}

int Book_data::getyear() const
{
    return year;
}

Book_data::publisherType Book_data::getType() const
{
    return type;
}


