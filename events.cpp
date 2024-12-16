#include "events.h"
#include <QSettings>

QString name;
Events::Events()
{

}

Custom_View::Custom_View(QWidget *parent) : QGraphicsView(parent)
{
    setAcceptDrops(true);
    scene = new QGraphicsScene(this);
    setScene(scene);
    viewport()->installEventFilter(this);

    // Set the path to the configuration file
    configFilePath = QApplication::applicationDirPath() + "/config.ini";

    // Load persisted data (image file path) on initialization
    loadPersistedData();
}

void Custom_View::dragEnterEvent(QDragEnterEvent *event)
{
    QDragEnterEvent *DragEnterEvent = static_cast<QDragEnterEvent*>(event);
    if(DragEnterEvent->mimeData()->hasUrls())
    {
        DragEnterEvent->acceptProposedAction();
    }
}

void Custom_View::dragLeaverEvent(QDragLeaveEvent *event)
{
    event->accept();
}

void Custom_View::dragMoveEvent(QDragMoveEvent *event)
{
    event->accept();
    event->acceptProposedAction();
}

void Custom_View::dropEvent(QDropEvent *event)
{
    if (event->source() == this)
        return;

    QDropEvent *dropEvent = static_cast<QDropEvent *>(event);
    if (dropEvent->mimeData()->hasUrls())
    {
        QList<QUrl> urlList = dropEvent->mimeData()->urls();
        foreach (QUrl url, urlList)
        {
            if (url.isLocalFile())
            {
                MainWindow another;
                name =another.returnname();
                QString filePath = url.toLocalFile();
                QPixmap pixmap(filePath);
                if (!pixmap.isNull())
                {
                    // Clear scene when a new image file is dropped
                    if (scene->items().count() > 0)
                        scene->clear();

                    QGraphicsPixmapItem *item = new QGraphicsPixmapItem(pixmap);

                    // Set the scene rect based on the pixmap's rect
                    scene->setSceneRect(pixmap.rect());
                    // Ensure aspect ratio is preserved
                    //fitInView(scene->sceneRect(), Qt::KeepAspectRatio);
                    // Set the fixed width and height
                    setFixedSize(120, 120);

                    scene->addItem(item);

                    // Save the dropped image file path to the configuration file
                    savePersistedData(filePath);

                    dropEvent->acceptProposedAction();
                }
            }
        }
    }
}


void Custom_View::loadPersistedData()
{
    QSettings settings(configFilePath, QSettings::IniFormat);
    QString lastImagePath = settings.value("LastImagePath").toString();

    if (!lastImagePath.isEmpty())
    {
        QPixmap pixmap(lastImagePath);
        if (!pixmap.isNull())
        {
            // Clear scene when loading a persisted image
            if (scene->items().count() > 0)
                scene->clear();

            scene->setSceneRect(pixmap.rect());
            // Ensure aspect ratio is preserved
            //fitInView(scene->sceneRect(), Qt::KeepAspectRatio);
            // Set the pixmap size directly
            QGraphicsPixmapItem *item = new QGraphicsPixmapItem(pixmap.scaled(120, 120, Qt::KeepAspectRatio));

            // Set the fixed size for the QGraphicsView
            setFixedSize(120, 120);

            scene->addItem(item);
        }
    }
}

void Custom_View::savePersistedData(const QString &filePath)
{
    QSettings settings(configFilePath, QSettings::IniFormat);
    settings.setValue("LastImagePath", filePath);
}
