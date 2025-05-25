#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <QSqlDatabase>
#include <QString>

class DBManager
{
public:
    static DBManager& instance();
    bool connect(const QString& dbPath);
    QSqlDatabase database() const;
    void initTables();
    void clearAllTables();
private:
    DBManager();  // Приватный конструктор для синглтона
    QSqlDatabase m_db;
};

#endif // DBMANAGER_H
