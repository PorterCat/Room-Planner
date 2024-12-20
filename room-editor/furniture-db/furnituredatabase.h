#pragma once

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

class FurnitureDatabase
{
public:
    FurnitureDatabase(const QString& dbPath);
    ~FurnitureDatabase();

    bool open();
    void close();

    bool createTables();
    bool addFurniture(const QString& name, const QString& imagePath, int categoryId);
    bool addCategory(const QString& name);
    QList<QPair<QString, QString>> getFurnitureByCategory(int id);
    QList<QString> getCategories();
    int getCategoryIdByName(const QString& name);

    bool categoryExists(const QString& name);
    bool furnitureExists(const QString& name);

private:
    QSqlDatabase m_db;
    QString m_dbPath;
};
