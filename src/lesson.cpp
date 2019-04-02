#include "lesson.h"

Lesson::Lesson()
{
}

Lesson::Lesson(QString lname,int lid1)
{
    LessonName=lname;
    LessonID=lid1;
}
int Lesson::getLessonID()
{
    return LessonID;
}

void Lesson::setLessonID(int lid)
{
    LessonID=lid;
}

QString Lesson::getLessonName()
{
    return LessonName;
}

void Lesson::setLessonName(QString lname1)
{
    LessonName=lname1;
}

