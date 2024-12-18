#include "sceneserializer.h"

bool SceneSerializer::saveScene(QGraphicsScene* scene, const QString& filePath)
{
    QJsonArray itemsArray;

    foreach(QGraphicsItem * item, scene->items())
    {
        if (auto roomEditorObject = dynamic_cast<IRoomEditorObject*>(item))
        {
            itemsArray.append(roomEditorObject->toJson());
        }
    }

    QJsonObject sceneObject;
    sceneObject["items"] = itemsArray;

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

bool SceneSerializer::loadScene(QGraphicsScene* scene, const QString& filePath)
{
    QFile file(filePath);
    if (file.open(QIODevice::ReadOnly))
    {
        QByteArray data = file.readAll();
        file.close();

        QJsonDocument jsonDoc = QJsonDocument::fromJson(data);
        QJsonObject sceneObject = jsonDoc.object();
        QJsonArray itemsArray = sceneObject["items"].toArray();

        scene->clear();

        foreach(const QJsonValue & value, itemsArray)
        {
            QJsonObject itemObject = value.toObject();
            IRoomEditorObject* item = IRoomEditorObject::fromJson(itemObject);
            if (item)
            {
                scene->addItem(dynamic_cast<QGraphicsItem*>(item));
            }
        }
        return true;
    }
    return false;
}
