#include "dbmanager.h"
#include <QSqlError>
#include <QDebug>
#include <QSqlQuery>
DBManager::DBManager() {}

DBManager& DBManager::instance()
{
    static DBManager instance;
    // instance.initTables();
    return instance;
}

bool DBManager::connect(const QString& dbPath)
{
    if (QSqlDatabase::contains("qt_sql_default_connection")) {
        m_db = QSqlDatabase::database("qt_sql_default_connection");
    } else {
        m_db = QSqlDatabase::addDatabase("QSQLITE");
        m_db.setDatabaseName(dbPath);
    }

    if (!m_db.open()) {
        qCritical() << "Не удалось открыть базу данных:" << m_db.lastError().text();
        return false;
    }

    qDebug() << "База данных подключена успешно.";
    initTables();
    return true;
}

QSqlDatabase DBManager::database() const
{
    return m_db;
}

void DBManager::initTables() {
    QSqlQuery query;

    // query.exec("DROP TABLE IF EXISTS users");
    query.exec(R"(
        CREATE TABLE IF NOT EXISTS users (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            username TEXT UNIQUE NOT NULL,
            password TEXT NOT NULL,
            role TEXT CHECK(role IN ('student', 'teacher', 'admin')) NOT NULL,
            group_number TEXT
        )
    )");
    // query.exec(R"(ALTER TABLE users RENAME COLUMN group TO group_number;
        // )
    // )");
    query.exec(R"(
        CREATE TABLE IF NOT EXISTS students (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            name TEXT NOT NULL,
            email TEXT,
            group_name TEXT
        )
    )");

    query.exec(R"(
        CREATE TABLE IF NOT EXISTS departments (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            name TEXT NOT NULL,
            description TEXT
        )
    )");

    query.exec(R"(
        CREATE TABLE IF NOT EXISTS appointments (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            student_id INTEGER NOT NULL,
            department_id INTEGER NOT NULL,
            time DATETIME NOT NULL,
            status TEXT CHECK(status IN ('записан', 'отменен', 'завершен')) DEFAULT 'записан',
            FOREIGN KEY(student_id) REFERENCES students(id),
            FOREIGN KEY(department_id) REFERENCES departments(id)
        )
    )");

    query.exec(R"(
        CREATE TABLE IF NOT EXISTS queues (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            department_id INTEGER NOT NULL,
            type TEXT NOT NULL,
            is_active BOOLEAN DEFAULT 1,
            FOREIGN KEY(department_id) REFERENCES departments(id)
        )
    )");

    query.exec(R"(
        CREATE TABLE IF NOT EXISTS requests (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            student_id INTEGER NOT NULL,
            department_id INTEGER NOT NULL,
            message TEXT,
            created_at DATETIME DEFAULT CURRENT_TIMESTAMP,
            status TEXT CHECK(status IN ('новая', 'в работе', 'выполнена', 'отклонена')) DEFAULT 'новая',
            FOREIGN KEY(student_id) REFERENCES students(id),
            FOREIGN KEY(department_id) REFERENCES departments(id)
        )
    )");

    query.exec(R"(
        CREATE TABLE IF NOT EXISTS results (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            request_id INTEGER NOT NULL,
            result TEXT,
            processed_at DATETIME DEFAULT CURRENT_TIMESTAMP,
            FOREIGN KEY(request_id) REFERENCES requests(id)
        )
    )");
    query.exec(R"(
            CREATE TABLE IF NOT EXISTS waiting_queue (
                id INTEGER PRIMARY KEY AUTOINCREMENT,
                name TEXT NOT NULL,
                message TEXT
            )

    )");
    query.exec(R"(
            CREATE TABLE IF NOT EXISTS order_queue (
                id INTEGER PRIMARY KEY AUTOINCREMENT,
                name TEXT,
                message TEXT,
                scheduled_time TEXT
            )

    )");
    query.exec(R"(
            CREATE TABLE IF NOT EXISTS live_queue (
                id INTEGER PRIMARY KEY AUTOINCREMENT,
                name TEXT,
                message TEXT,
                scheduled_time TEXT
            )

    )");
    query.exec(R"(
            CREATE TABLE IF NOT EXISTS self_organizing_queue (
                id INTEGER PRIMARY KEY AUTOINCREMENT,
                name TEXT,
                message TEXT,
                priority INTEGER,
                scheduled_time TEXT
            )

    )");
    query.exec(R"(
            CREATE TABLE IF NOT EXISTS consultation_queue (
                id INTEGER PRIMARY KEY AUTOINCREMENT,
                student_name TEXT NOT NULL,
                teacher_name TEXT NOT NULL,
                subject TEXT NOT NULL,
                date TEXT NOT NULL,
                time TEXT NOT NULL,
                status TEXT DEFAULT 'ожидает'  -- например: ожидает, подтверждено, отклонено
            )
    )");

    query.exec(R"(
            CREATE TABLE IF NOT EXISTS teachers (
                id INTEGER PRIMARY KEY AUTOINCREMENT,
                name TEXT NOT NULL
            )
    )");

    query.exec(R"(
            CREATE TABLE IF NOT EXISTS subjects (
                id INTEGER PRIMARY KEY AUTOINCREMENT,
                name TEXT NOT NULL
            )
    )");
}
void DBManager::clearAllTables()
{
    QSqlQuery query;
    query.exec("DELETE FROM results");
    query.exec("DELETE FROM requests");
    query.exec("DELETE FROM queues");
    query.exec("DELETE FROM appointments");
    query.exec("DELETE FROM departments");
    query.exec("DELETE FROM students");

    // Сброс автоинкремента (если нужно)
    query.exec("DELETE FROM sqlite_sequence");
}
