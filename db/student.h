#ifndef STUDENT_H
#define STUDENT_H

#include <QString>

class Student {
public:
    Student();
    Student(int id, const QString& name, const QString& email, const QString& group);

    int id() const;
    QString name() const;
    QString email() const;
    QString groupName() const;

    void setId(int value);
    void setName(const QString& value);
    void setEmail(const QString& value);
    void setGroupName(const QString& value);

private:
    int m_id;
    QString m_name;
    QString m_email;
    QString m_groupName;
};

#endif // STUDENT_H
