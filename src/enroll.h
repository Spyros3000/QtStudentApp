#ifndef ENROLL_H
#define ENROLL_H

class Enroll
{
private:
    int StudentID;
    int LessonID;
    double Grade;
public:
    Enroll();
    Enroll(int sid,int lid,double g);
    int getStudentID();
    int getLessonID();
    double getGrade();
    void setStudentID(int sid1);
    void setLessonID(int lid1);
    void setGrade(double g1);
};

#endif // ENROLL_H
