#ifndef DATABASE_H
#define DATABASE_H

#include <student.h>
#include <lesson.h>
#include <enroll.h>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QBuffer>
#include <QMessageBox>
#include <QDebug>
#include <QSqlError>

class database
{
private:
    QSqlDatabase db;
public:
    database();
    QVector <Student> student();
    QVector <Lesson> lesson();
    QVector <Enroll> enroll();
    QStringList getLessons();
    void insertStudent(Student &s);
    void insertEnrolment(Enroll &e);
    void insertLesson(Lesson &c);
    void deleteStudent(int id);
    void deleteLesson(int id);
    bool ExistsStudent(int id);
    bool ExistsLesson(int id);
    QStringList getPerformanceGrade(QString selectedName);
    QStringList getPerformanceName(QString selectedName);
    Student getStudent(int id,bool &found);
    ~database();
};

#endif // DATABASE_H
