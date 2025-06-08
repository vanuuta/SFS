#ifndef REQUEST_H
#define REQUEST_H

#include <QString>
#include <QDateTime>

class Request {
public:
    Request();
    Request(int id, int studentId, const QString& type, const QString& status, const QDateTime& createdAt);

    int id() const;
    int studentId() const;
    QString type() const;
    QString status() const;
    QDateTime createdAt() const;

    void setId(int value);
    void setStudentId(int value);
    void setType(const QString& value);
    void setStatus(const QString& value);
    void setCreatedAt(const QDateTime& value);

    bool saveToDb() const;
    static QList<Request> getAllFromDb();

    static bool updateStatus(int id, const QString& newStatus);
    static Request getById(int id);
    static QList<Request> getByStudentId(int studentId);
    static QList<Request> getByStatus(const QString& status);
    static bool removeById(int id);

public:
    QString m_name;
    QString m_type;
private:
    int m_id;
    int m_studentId;
    int m_department_id;
    QString m_status;
    QDateTime m_createdAt;
};

#endif // REQUEST_H
