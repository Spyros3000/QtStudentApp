#include "enroll.h"

Enroll::Enroll()
{
}

Enroll::Enroll(int sid,int lid,double g)
{
    StudentID=sid;
    LessonID=lid;
    Grade=g;
}

int Enroll:: getStudentID()
{
    return StudentID;
}

void Enroll::setStudentID(int sid1)
{
    StudentID=sid1;
}

int Enroll:: getLessonID()
{
    return LessonID;
}

void Enroll::setLessonID(int lid1)
{
    LessonID=lid1;
}

double Enroll::getGrade()
{
    return Grade;
}

void Enroll::setGrade(double g1)
{
    Grade=g1;
}
