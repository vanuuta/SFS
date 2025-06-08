#ifndef USER_H
#define USER_H
#include <QString>
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
    QString username;
    QString password;
};

#endif // USER_H
