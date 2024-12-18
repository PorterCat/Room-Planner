#include "iroomeditorobject.h"
#include "rewall.h"

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
    return nullptr;
}
