#pragma once

#include <QGraphicsScene>
#include <QString>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QFile>
#include <QDebug>

#include "scene-objects/iroomeditorobject.h"
#include "actiongraphicsscene.h"
#include "roomeditor.h"

class SceneSerializer
{
public:
    static bool saveScene(RoomEditor* scene, const QString& filePath);
    static RoomEditor* loadScene(const QString& filePath, QWidget* parent = nullptr, MainWindow* mainWindow = nullptr);

private:
    /*static QJsonObject serializeItem(QGraphicsItem* item);
    static IRoomEditorObject* deserializeItem(const QJsonObject& json);*/
};
