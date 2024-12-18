#include "sceneserializer.h"
#include <qfileinfo.h>

bool SceneSerializer::saveScene(RoomEditor* roomEditor, const QString& filePath)
{
    QJsonArray itemsArray;

    foreach(QGraphicsItem * item, roomEditor->getScene()->items())
    {
        if (auto roomEditorObject = dynamic_cast<IRoomEditorObject*>(item))
        {
            itemsArray.append(roomEditorObject->toJson());
        }
    }

    QJsonObject sceneObject;
    sceneObject["items"] = itemsArray;

    QJsonObject gridSize;
    gridSize["width"] = roomEditor->getGridWidth();
    gridSize["height"] = roomEditor->getGridHeight();
    sceneObject["gridSize"] = gridSize;

    QFileInfo fileInfo(filePath);
    sceneObject["fileName"] = fileInfo.baseName();

    QJsonDocument jsonDoc(sceneObject);
    QFile file(filePath);
    if (file.open(QIODevice::WriteOnly))
    {
        file.write(jsonDoc.toJson());
        file.close();
        return true;
    }
    return false;
}

RoomEditor* SceneSerializer::loadScene(const QString& filePath, QWidget* parent, MainWindow* mainWindow)
{
    RoomEditor* roomEditor;
    QFile file(filePath);
    if (file.open(QIODevice::ReadOnly))
    {
        QByteArray data = file.readAll();
        file.close();

        QJsonDocument jsonDoc = QJsonDocument::fromJson(data);
        QJsonObject sceneObject = jsonDoc.object();
        QString fileName = "untitled";

        if(sceneObject.contains("fileName"))
        {
           fileName = sceneObject["fileName"].toString();
        }

        if (sceneObject.contains("gridSize"))
        {
            QJsonObject gridSize = sceneObject["gridSize"].toObject();
            int gridWidth = gridSize["width"].toInt();
            int gridHeight = gridSize["height"].toInt();
            roomEditor = new RoomEditor(gridWidth, gridHeight, fileName, parent, mainWindow);
        }

        QJsonArray itemsArray = sceneObject["items"].toArray();
        foreach(const QJsonValue & value, itemsArray)
        {
            QJsonObject itemObject = value.toObject();
            IRoomEditorObject* item = IRoomEditorObject::fromJson(itemObject);
            if (item)
            {
                roomEditor->getScene()->addItem(dynamic_cast<QGraphicsItem*>(item));
            }
        }
        return roomEditor;
    }
    return nullptr;
}
