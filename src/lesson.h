#ifndef LESSON_H
#define LESSON_H

#include <QString>

class Lesson
{
private:
    int LessonID;
    QString LessonName;
public:
    Lesson();
    Lesson(QString lname,int lid1);
    int getLessonID();
    QString getLessonName();
    void setLessonID(int lid);
    void setLessonName(QString lname1);

};

#endif // LESSON_H
