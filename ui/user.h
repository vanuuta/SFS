#ifndef USER_H
#define USER_H
#include <QString>
#include <optional>
#include "../themetogglebutton.h"
class User
{
public:
    User();
    User(QString _name, QString _username, QString _passwored):
        name(_name),
        username(_username),
        password(_passwored){};
public:
    QString name;
    QString role;
    QString username;
    QString password;
    std::optional<QString> group;
};

#endif // USER_H
