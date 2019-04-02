#include "student.h"

Student::Student()
{
}

Student::Student(QString n,QString l,int i)
{
    name=n;
    lastname=l;
    id=i;
}
void Student::setName(QString n1)
{
    name=n1;
}

QString Student::getName()
{
    return name;
}

void Student::setLastName(QString l1)
{
    lastname=l1;
}

QString Student::getLastName()
{
    return lastname;
}

void Student::setID(int i1)
{
    id=i1;
}

int Student::getID()
{
    return id;
}

QString Student::toString()
{
    return name+" "+lastname+" "+QString::number(id);
}

