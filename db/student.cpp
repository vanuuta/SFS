#include "student.h"

Student::Student()
    : m_id(-1)
{}

Student::Student(int id, const QString& name, const QString& email, const QString& group)
    : m_id(id), m_name(name), m_email(email), m_groupName(group)
{}

int Student::id() const {
    return m_id;
}

QString Student::name() const {
    return m_name;
}

QString Student::email() const {
    return m_email;
}

QString Student::groupName() const {
    return m_groupName;
}

void Student::setId(int value) {
    m_id = value;
}

void Student::setName(const QString& value) {
    m_name = value;
}

void Student::setEmail(const QString& value) {
    m_email = value;
}

void Student::setGroupName(const QString& value) {
    m_groupName = value;
}
