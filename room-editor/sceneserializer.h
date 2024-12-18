#pragma once

#include <QGraphicsScene>
#include <QString>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QFile>
#include <QDebug>

#include "scene-objects/iroomeditorobject.h"

class SceneSerializer
{
public:
    static bool saveScene(QGraphicsScene* scene, const QString& filePath);

    static bool loadScene(QGraphicsScene* scene, const QString& filePath);

private:
    static QJsonObject serializeItem(QGraphicsItem* item);
    static IRoomEditorObject* deserializeItem(const QJsonObject& json);
};
