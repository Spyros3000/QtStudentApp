#include "database.h"

# include <QVariant>
# include <QDebug>

database::database()
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("database.db");
    db.open();
    QSqlQuery q1(db);
    q1.exec(QString("CREATE TABLE student(")+
           QString("NAME VARCHAR(64),"
                   "LASTNAME VARCHAR (64),"
                   "ID integer PRIMARY KEY);"));

    QSqlQuery q2(db);
    q2.exec(QString("CREATE TABLE lesson(")+
           QString("LESSONNAME VARCHAR (64),"
                   "LESSONID integer PRIMARY KEY);"));

    QSqlQuery q3(db);
    q3.exec(QString("CREATE TABLE enroll(")+
           QString("STUDENTID integer,"
                   "LESSONID integer,"
                   "GRADE double,"
                   "FOREIGN KEY(STUDENTID) REFERENCES student(ID),"
                   "FOREIGN KEY(LESSONID) REFERENCES lesson(LESSONID));"));
}

//Students

QVector<Student> database::student()
{
    QVector<Student> S;
    QSqlQuery query(db);
    bool res=query.exec("SELECT name, lastname, id FROM student");
    if(!res)
    {
        qDebug()<<"Wrong query"<<endl;
        return S;
    }

    query.exec("SELECT name, lastname, id FROM student");
    while (query.next())
    {
        Student st(query.value(0).toString(),query.value(1).toString(),query.value(2).toInt());
        S.append(st);
    }
        return S;
}

void database::insertStudent(Student &s)
{
    QSqlQuery query(db);
    query.prepare("INSERT INTO student (name,lastname,id) VALUES (?,?,?)");
    query.addBindValue(s.getName());
    query.addBindValue(s.getLastName());
    query.addBindValue(s.getID());
    query.exec();
    qDebug()<<"studentOK";
}

Student database::getStudent(int id,bool &found)
{
    QSqlQuery query(db);
    query.exec("SELECT name,lastname,id FROM student WHERE id="+QString::number(id));
    if(query.next()==true)
    {
        Student C(query.value(0).toString(),query.value(1).toString(),query.value(2).toInt());
        found=true;
        return C;
    }
    else found=false;
}

bool database::ExistsStudent(int id)
{
    QSqlQuery query(db);
    bool res=query.exec("SELECT count(*) FROM student WHERE student.id="+QString::number(id));
    if(!res)
    {
        qDebug()<<"Wrong query"<<endl;
        return false;
    }
    query.next();
    int v=query.value(0).toInt();
    if(v==0) return false;
    return true;
}

void database::deleteStudent(int id)
{
    QSqlQuery query(db);
    query.exec("DELETE FROM student WHERE ID="+QString::number(id));
    QSqlQuery query1(db);
    query1.exec("DELETE FROM enroll where STUDENTID="+QString::number(id));
}

//Lessons

QVector<Lesson> database::lesson()
{
    QVector<Lesson> L;
    QSqlQuery query(db);
    bool res=query.exec("SELECT LessonName,LessonID FROM lesson");
    if(!res)
    {
        qDebug()<<"Wrong query"<<endl;
        return L;
    }
    query.exec("SELECT LessonName,LessonID FROM lesson");
    while(query.next())
    {
        Lesson less(query.value(0).toString(),query.value(1).toInt());
        L.append(less);
    }
    return L;
}

void database::insertLesson(Lesson &l)
{
    QSqlQuery query(db);
    query.prepare("INSERT INTO lesson (LessonName,LessonID) VALUES (?,?)");
    query.addBindValue(l.getLessonName());
    query.addBindValue(l.getLessonID());
    query.exec();
    qDebug()<<"lessonOK";
}

QStringList database::getLessons()
{
    QStringList result;
    QSqlQuery query(db);
    bool res=query.exec("SELECT LessonName from lesson GROUP BY LessonName ORDER BY LessonName");
    if(!res)
    {
        qDebug()<<"Wrong query"<<endl;
        return result;
    }
    while(query.next())
    {
        result<<query.value(0).toString();
    }
    return result;
}

bool database::ExistsLesson(int id)
{
    QSqlQuery query(db);
    bool res=query.exec("SELECT count(*) FROM lesson WHERE lesson.LessonID="+QString::number(id));
    if(!res)
    {
        qDebug()<<"Wrong query"<<endl;
        return false;
    }
    query.next();
    int v=query.value(0).toInt();
    if(v==0) return false;
    return true;
}

void database::deleteLesson(int id)
{
    QSqlQuery query(db);
    query.exec("DELETE FROM enroll WHERE LessonID="+QString::number(id));
    QSqlQuery query1(db);
    query1.exec("DELETE FROM lesson WHERE LessonID="+QString::number(id));
}

//Enrollments

QVector<Enroll> database::enroll()
{
    QVector<Enroll> E;
    QSqlQuery query(db);
    bool res=query.exec("SELECT StudentID, LessonID, Grade FROM enroll");
    if(!res)
    {
        qDebug()<<"Wrong query"<<endl;
        return E;
    }
    query.exec("SELECT StudentID, LessonID, Grade FROM enroll");
    while(query.next())
    {
        Enroll enr(query.value(0).toInt(),query.value(1).toInt(),query.value(2).toDouble());
        E.append(enr);
    }
    return E;
}

void database::insertEnrolment(Enroll &e)
{
    QSqlQuery query(db);
    query.prepare("INSERT INTO enroll (StudentID, LessonID, Grade) VALUES (?,?,?)");
    query.addBindValue(e.getStudentID());
    query.addBindValue(e.getLessonID());
    query.addBindValue(e.getGrade());
    query.exec();
    qDebug()<<"enrollOK";
}

QStringList database::getPerformanceGrade(QString selectedName)//Returns grade
{
    QStringList GradeResult;
    QSqlQuery query(db);
    bool res=query.exec("SELECT enroll.GRADE FROM enroll, lesson WHERE lesson.LESSONID=enroll.LESSONID AND lesson.LESSONNAME='"+selectedName+"'");
    if(!res)
        qDebug()<<"Wrong query"<<endl;
        while(query.next())
        {
            GradeResult<<query.value(0).toString();
        }
        return GradeResult;
}

QStringList database::getPerformanceName(QString selectedName)//Returns student's ID
{
    QStringList GradeResult;
    QSqlQuery query(db);
    bool res=query.exec("SELECT enroll.STUDENTID FROM enroll,lesson WHERE lesson.LESSONID=enroll.LESSONID AND lesson.LESSONNAME='"+selectedName+"'");
    if(!res)
        qDebug()<<"Wrong query"<<endl;
        while(query.next())
        {
            GradeResult<<query.value(0).toString();

        }
        for(int i=0;i<GradeResult.size();i++){qDebug()<<GradeResult[i]<<endl;}
        return GradeResult;
}

database::~database()
{
    db.close();
}

