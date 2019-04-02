#ifndef STUDENT_H
#define STUDENT_H

#include <QString>

class Student
{
private:
    QString name;
    QString lastname;
    int id;
public:
    Student();
    Student(QString n,QString l,int i);
    QString getName();
    QString getLastName();
    QString toString();
    int getID();
    void setName(QString n1);
    void setLastName(QString l1);
    void setID(int i1);
};

#endif // STUDENT_H
