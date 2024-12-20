#include "furnituredatabase.h"

FurnitureDatabase::FurnitureDatabase(const QString& dbPath) : m_dbPath(dbPath)
{
    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName(m_dbPath);
}

FurnitureDatabase::~FurnitureDatabase()
{
    if (m_db.isOpen())
    {
        m_db.close();
    }
}

bool FurnitureDatabase::open()
{
    if (!m_db.open())
    {
        qWarning() << "Failed to open database:" << m_db.lastError().text();
        return false;
    }
    qDebug() << "Database opened successfully!";
    return true;
}

void FurnitureDatabase::close()
{
    m_db.close();
}

bool FurnitureDatabase::createTables()
{
    QSqlQuery query;

    // Создаем таблицу Categories
    QString createCategoriesTableQuery = "CREATE TABLE IF NOT EXISTS Categories ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT, "
        "name TEXT NOT NULL UNIQUE"
        ");";

    if (!query.exec(createCategoriesTableQuery))
    {
        qWarning() << "Failed to create Categories table:" << query.lastError().text();
        return false;
    }

    // Создаем таблицу Furniture
    QString createFurnitureTableQuery = "CREATE TABLE IF NOT EXISTS Furniture ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT, "
        "name TEXT NOT NULL, "
        "imagePath TEXT NOT NULL, "
        "category_id INTEGER NOT NULL, "
        "FOREIGN KEY(category_id) REFERENCES Categories(id) ON DELETE CASCADE"
        ");";

    if (!query.exec(createFurnitureTableQuery))
    {
        qWarning() << "Failed to create Furniture table:" << query.lastError().text();
        return false;
    }

    return true;
}

bool FurnitureDatabase::addCategory(const QString& name)
{
    QSqlQuery query;
    query.prepare("INSERT INTO Categories (name) VALUES (:name)");
    query.bindValue(":name", name);

    if (!query.exec())
    {
        qWarning() << "Failed to add category:" << query.lastError().text();
        return false;
    }
    return true;
}

bool FurnitureDatabase::addFurniture(const QString& name, const QString& imagePath, int categoryId)
{
    QSqlQuery query;
    query.prepare("INSERT INTO Furniture (name, imagePath, category_id) VALUES (:name, :imagePath, :categoryId)");
    query.bindValue(":name", name);
    query.bindValue(":imagePath", imagePath);
    query.bindValue(":categoryId", categoryId);

    if (!query.exec())
    {
        qWarning() << "Failed to add furniture:" << query.lastError().text();
        return false;
    }
    return true;
}

int FurnitureDatabase::getCategoryIdByName(const QString& name)
{

    if (!m_db.isOpen())
    {
        qWarning() << "Database is not open!";
        return -1;
    }

    QSqlQuery query;

    query.prepare("SELECT id FROM Categories WHERE name = :name");
    query.bindValue(":name", name);

    if (query.exec() && query.next())
    {
        return query.value("id").toInt();
    }

    qWarning() << "Category not found:" << name;
    return -1; // Возвращаем -1, если категория не найдена
}

QList<QString> FurnitureDatabase::getCategories()
{
    QList<QString> categories;
    QSqlQuery query;
    query.prepare("SELECT name FROM Categories");

    if (query.exec())
    {
        while (query.next())
        {
            QString name = query.value("name").toString();
            categories.append(name);
        }
    }
    else
    {
        qWarning() << "Failed to query categories:" << query.lastError().text();
    }

    return categories;
}

QList<QPair<QString, QString>> FurnitureDatabase::getFurnitureByCategory(int categoryId)
{
    QList<QPair<QString, QString>> furnitureList;
    QSqlQuery query;
    query.prepare("SELECT name, imagePath FROM Furniture WHERE category_id = :categoryId");
    query.bindValue(":categoryId", categoryId);

    if (query.exec())
    {
        while (query.next())
        {
            QString name = query.value("name").toString();
            QString imagePath = query.value("imagePath").toString();
            furnitureList.append(qMakePair(name, imagePath));
        }
    }
    else
    {
        qWarning() << "Failed to query furniture:" << query.lastError().text();
    }

    return furnitureList;
}

bool FurnitureDatabase::categoryExists(const QString& name)
{
    QSqlQuery query;
    query.prepare("SELECT id FROM Categories WHERE name = :name");
    query.bindValue(":name", name);

    if (query.exec() && query.next())
    {
        return true; // Категория существует
    }
    return false; // Категория не существует
}

bool FurnitureDatabase::furnitureExists(const QString& name)
{
    QSqlQuery query;
    query.prepare("SELECT id FROM Furniture WHERE name = :name");
    query.bindValue(":name", name);

    if (query.exec() && query.next())
    {
        return true; // Мебель существует
    }
    return false; // Мебель не существует
}