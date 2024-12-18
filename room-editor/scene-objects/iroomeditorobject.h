#ifndef ROOMEDITOROBJECT_H
#define ROOMEDITOROBJECT_H

#include <QJsonObject>
#include <QPen>
#include <qgraphicsitem.h>

class IRoomEditorObject
{
  public:
      enum ObjectType 
      {
          RoomEditorObjectBase = QGraphicsItem::UserType + 1,
          REWallType,
          REDoorType
      };
	
      virtual ~IRoomEditorObject() = default;

      virtual int type() const = 0;
      virtual QString typeName() const = 0;
      virtual QJsonObject toJson() const = 0;

      static IRoomEditorObject* fromJson(const QJsonObject& json);
      static IRoomEditorObject* createFromType(const QString& type, const QJsonObject& json);
};

#endif // ROOMEDITOROBJECT_H
