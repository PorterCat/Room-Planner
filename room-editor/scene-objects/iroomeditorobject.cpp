#include "iroomeditorobject.h"
#include "rewall.h"
#include "refurniture.h"

IRoomEditorObject* IRoomEditorObject::fromJson(const QJsonObject& json)
{
    QString type = json["type"].toString();
    return createFromType(type, json);
}

IRoomEditorObject* IRoomEditorObject::createFromType(const QString& type, const QJsonObject& json)
{
    if (type == "REWall")
    {
        return REWall::fromJson(json);
    }
    else if (type == "REFurniture")
    {
        return REFurniture::fromJson(json);
    }
    return nullptr;
}
