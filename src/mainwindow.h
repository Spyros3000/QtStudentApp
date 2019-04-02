#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <database.h>
#include <QMainWindow>
#include <QWidget>
#include <QVBoxLayout>
#include <QMenu>
#include <QMenuBar>
#include <QComboBox>
#include <QDebug>
#include <QLabel>
#include <QStackedLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QIntValidator>
#include <QDoubleValidator>
#include <QTableWidget>
#include <QMessageBox>
#include <QTableWidgetItem>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
private:
    QWidget *mainWidget;

    QVBoxLayout *mainLayout;
    QMenuBar *menubar;
    QMenu *StudentMenu;
    QMenu *LessonMenu;
    QStackedLayout *panel;
    QLineEdit *nameEdit,*lastnameEdit,*idEdit;
    QLineEdit *lastnameStartEdit,*lastnameContainsEdit;
    QLineEdit *StudentID,*LessonID,*StudentDeleteID,*Grade;
    QLineEdit *LessonAddName,*LessonAddId,*LessonDeleteId;
    QPushButton *addButton,*clearButton,*searchButton,*clearSearchButton;
    QPushButton *deleteButton,*clearDeleteButton;
    QPushButton *declarationButton,*clearDeclarationButton;
    QPushButton *LessonaddButton,*clearaddLessonButton;
    QPushButton *LessonDeleteButton,*cleardeleteLessonButton;
    QPushButton *viewPerformanceButton;
    QTableWidget *table,*table1,*PerformanceTable;
    QComboBox *PerformanceBox;
    database *mydb;
    void    makeMenus();
    void    makeInputForm();
    void    makeSearchForm();
    void    makeDeleteForm();
    void    makeDeclarationForm();
    void    AddLessonForm();
    void    LessonDeleteForm();
    void    makePerformanceForm();
    void    makeStudentDisplayForm();
    void    makeLessonDisplayForm();
    void    reloadStudentTable();
    void    reloadLessonTable();
public slots:
    void    addSlot();
    void    clearSlot();
    void    searchSlot();
    void    deleteSlot();
    void    declarationSlot();
    void    viewPerformanceSlot();
    void    LessonaddSlot();
    void    LessondeleteSlot();
    void    StudentSlot(QAction *action);
    void    LessonSlot(QAction *action);

};

#endif // MAINWINDOW_H
