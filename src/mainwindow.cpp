#include "mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    setFixedSize(500,200);
    setWindowTitle("Students");
    mainWidget=new QWidget;
    setCentralWidget(mainWidget);
    mainWidget->setFixedSize(this->width(),this->height());
    mainLayout=new QVBoxLayout;
    mainWidget->setLayout(mainLayout);
    mydb= new database;
    makeMenus();
    panel=new QStackedLayout;
    mainLayout->addLayout(panel);
    makeInputForm();
    makeSearchForm();
    makeDeleteForm();
    makeDeclarationForm();
    makeStudentDisplayForm();
    AddLessonForm();
    LessonDeleteForm();
    makePerformanceForm();
    makeLessonDisplayForm();
    reloadStudentTable();
    reloadLessonTable();
}

void    MainWindow::makeMenus(){
    StudentMenu= new QMenu("Students");//Create the Students menu
    StudentMenu->addAction("Add student");
    StudentMenu->addAction("Declare lesson");
    StudentMenu->addAction("Search student");
    StudentMenu->addAction("Delete student");
    StudentMenu->addAction("Show students");
    connect(StudentMenu,SIGNAL(triggered(QAction*)),this,SLOT(StudentSlot(QAction*)));

    LessonMenu= new QMenu("Lessons");//Create the Lessons menu
    LessonMenu->addAction("Add lesson");
    LessonMenu->addAction("Delete lesson");
    LessonMenu->addAction("Show grades");
    LessonMenu->addAction("Show lessons");
    connect(LessonMenu,SIGNAL(triggered(QAction*)),this,SLOT(LessonSlot(QAction*)));

    menuBar()->addMenu(StudentMenu);
    menuBar()->addMenu(LessonMenu);
}

void    MainWindow::makeInputForm()//Add students
{
   QWidget *tab1=new QWidget;
   panel->addWidget(tab1);
   tab1->setFixedSize(95*this->size().width()/100,this->size().height());
   QVBoxLayout *tab1layout=new QVBoxLayout;
   tab1->setLayout(tab1layout);
   QHBoxLayout *line1=new QHBoxLayout;
   tab1layout->addLayout(line1);
   QHBoxLayout *line2=new QHBoxLayout;
   tab1layout->addLayout(line2);
   idEdit=new QLineEdit;
   idEdit->setPlaceholderText("ID");
   idEdit->setValidator(new QIntValidator(0,20000));
   line1->addWidget(idEdit);
   nameEdit=new QLineEdit;
   nameEdit->setPlaceholderText("Name");
   line1->addWidget(nameEdit);
   lastnameEdit=new QLineEdit;
   lastnameEdit->setPlaceholderText("Last Name");
   line1->addWidget(lastnameEdit);
   addButton=new QPushButton;
   addButton->setText("Add Student");
   connect(addButton,SIGNAL(clicked(bool)),this,SLOT(addSlot()));

   line2->addWidget(addButton);
   clearButton=new QPushButton;
   clearButton->setText("Clear");
   connect(clearButton,SIGNAL(clicked(bool)),this,SLOT(clearSlot()));
   line2->addWidget(clearButton);
}

void    MainWindow::makeSearchForm()//Search students
{
    QWidget *tab3=new QWidget;
    panel->addWidget(tab3);
    tab3->setFixedSize(95*this->size().width()/100,this->size().height());
    QVBoxLayout *tab3layout=new QVBoxLayout;
    tab3->setLayout(tab3layout);
    QHBoxLayout *line1=new QHBoxLayout;
    tab3layout->addLayout(line1);
    QHBoxLayout *line2=new QHBoxLayout;
    tab3layout->addLayout(line2);
    lastnameStartEdit=new QLineEdit;
    lastnameStartEdit->setPlaceholderText("Last Name starts with");
    line1->addWidget(lastnameStartEdit);
    lastnameContainsEdit=new QLineEdit;
    lastnameContainsEdit->setPlaceholderText("Last Name contains");
    line1->addWidget(lastnameContainsEdit);
    searchButton=new QPushButton;
    searchButton->setText("Search");
    connect(searchButton,SIGNAL(clicked(bool)),this,SLOT(searchSlot()));
    line2->addWidget(searchButton);
    clearSearchButton=new QPushButton;
    clearSearchButton->setText("Clear");
    connect(clearSearchButton,SIGNAL(clicked(bool)),this,SLOT(clearSlot()));
    line2->addWidget(clearSearchButton);
}

void MainWindow::makeDeleteForm()//Delete students
{
    QWidget *tab2=new QWidget;
    panel->addWidget(tab2);
    tab2->setFixedSize(95*this->size().width()/100,this->size().height());
    QVBoxLayout *tab2layout=new QVBoxLayout;
    tab2->setLayout(tab2layout);
    QHBoxLayout *line1=new QHBoxLayout;
    tab2layout->addLayout(line1);
    StudentDeleteID=new QLineEdit;
    StudentDeleteID->setPlaceholderText("Student's ID");
    StudentDeleteID->setValidator(new QIntValidator(0,20000));
    line1->addWidget(StudentDeleteID);
    QHBoxLayout *line2=new QHBoxLayout;
    tab2layout->addLayout(line2);
    deleteButton=new QPushButton;
    deleteButton->setText("Delete");
    connect(deleteButton,SIGNAL(clicked(bool)),this,SLOT(deleteSlot()));
    clearDeleteButton=new QPushButton;
    clearDeleteButton->setText("Clear");
    connect(clearDeleteButton,SIGNAL(clicked(bool)),this,SLOT(clearSlot()));
    line2->addWidget(deleteButton);
    line2->addWidget(clearDeleteButton);
}

void MainWindow::makeDeclarationForm()//Declare lessons
{
    QWidget *tab4=new QWidget;
    panel->addWidget(tab4);
    tab4->setFixedSize(95*this->size().width()/100,this->size().height());
    QVBoxLayout *tab4layout=new QVBoxLayout;
    tab4->setLayout(tab4layout);
    QHBoxLayout *line1=new QHBoxLayout;
    tab4layout->addLayout(line1);
    StudentID=new QLineEdit;
    StudentID->setPlaceholderText("Student's ID");
    StudentID->setValidator(new QIntValidator(0,20000));
    line1->addWidget(StudentID);
    LessonID=new QLineEdit;
    LessonID->setPlaceholderText("Lesson's ID");
    LessonID->setValidator(new QIntValidator(0,10000));
    line1->addWidget(LessonID);
    Grade=new QLineEdit;
    Grade->setPlaceholderText("Grade");
    Grade->setValidator(new QDoubleValidator(0.0,10.0,2,this));
    line1->addWidget(Grade);
    QHBoxLayout *line2=new QHBoxLayout;
    tab4layout->addLayout(line2);
    declarationButton=new QPushButton;
    declarationButton->setText("Add Grade");
    connect(declarationButton,SIGNAL(clicked(bool)),this,SLOT(declarationSlot()));
    clearDeclarationButton=new QPushButton;
    clearDeclarationButton->setText("Clear");
    connect(clearDeclarationButton,SIGNAL(clicked(bool)),this,SLOT(clearSlot()));
    line2->addWidget(declarationButton);
    line2->addWidget(clearDeclarationButton);

}

void    MainWindow::makeStudentDisplayForm()//Show students
{
    QWidget *tab5=new QWidget;
    panel->addWidget(tab5);
    tab5->setFixedSize(95*this->size().width()/100,this->size().height()/1.10);
    QVBoxLayout *tab5layout=new QVBoxLayout;
    tab5->setLayout(tab5layout);
    table=new QTableWidget;
    table->setRowCount(1);
    table->setColumnCount(3);
    QStringList header;
    header<<"Name"<<"Last Name"<<"ID";
    table->setHorizontalHeaderLabels(header);
    tab5layout->addWidget(table);
}

void MainWindow::AddLessonForm()//Add lessons
{
    QWidget *tab4=new QWidget;
    panel->addWidget(tab4);
    tab4->setFixedSize(95*this->size().width()/100,this->size().height());
    QVBoxLayout *tab4layout=new QVBoxLayout;
    tab4->setLayout(tab4layout);
    QHBoxLayout *line1=new QHBoxLayout;
    tab4layout->addLayout(line1);
    QHBoxLayout *line2=new QHBoxLayout;
    tab4layout->addLayout(line2);
    LessonAddName=new QLineEdit;
    LessonAddName->setPlaceholderText("Lesson's Name");
    line1->addWidget(LessonAddName);
    LessonAddId=new QLineEdit;
    LessonAddId->setPlaceholderText("Lesson's ID");
    line1->addWidget(LessonAddId);
    LessonAddId->setValidator(new QIntValidator(0,10000));
    LessonaddButton=new QPushButton;
    LessonaddButton->setText("Add Lesson");
    connect(LessonaddButton,SIGNAL(clicked(bool)),this,SLOT(LessonaddSlot()));
    line2->addWidget(LessonaddButton);
    clearaddLessonButton=new QPushButton;
    clearaddLessonButton->setText("Clear");
    connect(clearaddLessonButton,SIGNAL(clicked(bool)),this,SLOT(clearSlot()));
    line2->addWidget(clearaddLessonButton);
}

void MainWindow::LessonDeleteForm()//Delete lessons
{
    QWidget *tab5=new QWidget;
    panel->addWidget(tab5);
    tab5->setFixedSize(95*this->size().width()/100,this->size().height());
    QVBoxLayout *tab5layout=new QVBoxLayout;
    tab5->setLayout(tab5layout);
    QHBoxLayout *line1=new QHBoxLayout;
    tab5layout->addLayout(line1);
    QHBoxLayout *line2=new QHBoxLayout;
    tab5layout->addLayout(line2);
    LessonDeleteId=new QLineEdit;
    LessonDeleteId->setPlaceholderText("Lesson's ID");
    line1->addWidget(LessonDeleteId);
    LessonDeleteId->setValidator(new QIntValidator(0,10000));
    LessonDeleteButton=new QPushButton;
    LessonDeleteButton->setText("Delete Lesson");
    connect(LessonDeleteButton,SIGNAL(clicked(bool)),this,SLOT(LessondeleteSlot()));
    line2->addWidget(LessonDeleteButton);
    cleardeleteLessonButton=new QPushButton;
    cleardeleteLessonButton->setText("Clear");
    connect(cleardeleteLessonButton,SIGNAL(clicked(bool)),this,SLOT(clearSlot()));
    line2->addWidget(cleardeleteLessonButton);
}

void  MainWindow::makePerformanceForm()//Show grades at lessons
{
    QWidget *tab7=new QWidget;
    panel->addWidget(tab7);
    tab7->setFixedSize(95*this->size().width()/100,this->size().height()/1.10);
    QVBoxLayout *tab7layout=new QVBoxLayout;
    tab7->setLayout(tab7layout);
    QHBoxLayout *line1=new QHBoxLayout;
    tab7layout->addLayout(line1);
    PerformanceBox=new QComboBox;
    line1->addWidget(PerformanceBox);
    viewPerformanceButton=new QPushButton;
    viewPerformanceButton->setText("Show");
    connect(viewPerformanceButton,SIGNAL(clicked(bool)),this,SLOT(viewPerformanceSlot()));
    line1->addWidget(viewPerformanceButton);
    QHBoxLayout *line2=new QHBoxLayout;
    tab7layout->addLayout(line2);
    PerformanceTable=new QTableWidget;
    PerformanceTable->setRowCount(1);
    PerformanceTable->setColumnCount(3);
    QStringList header;
    header<<"Student's ID"<<"Grade"<<"Status";
    PerformanceTable->setHorizontalHeaderLabels(header);
    line2->addWidget(PerformanceTable);
}

void MainWindow::makeLessonDisplayForm()//Show lessons
{
    QWidget *tab8=new QWidget;
    panel->addWidget(tab8);
    tab8->setFixedSize(95*this->size().width()/100,this->size().height()/1.10);
    QVBoxLayout *tab8layout=new QVBoxLayout;
    tab8->setLayout(tab8layout);
    table1=new QTableWidget;
    table1->setRowCount(1);
    table1->setColumnCount(2);
    QStringList header;
    header<<"Name"<<"ID";
    table1->setHorizontalHeaderLabels(header);
    tab8layout->addWidget(table1);
}

void MainWindow::reloadStudentTable()
{
    QVector<Student>S=mydb->student();
    table->clearContents();
    table->setRowCount(S.size());

    for(int i=0;i<S.size();i++)
    {
        Student ss=S[i];
        table->setItem(i,0,new QTableWidgetItem(ss.getName()));
        table->setItem(i,1,new QTableWidgetItem(ss.getLastName()));
        table->setItem(i,2,new QTableWidgetItem(QString::number(ss.getID())));
    }
}
void MainWindow::reloadLessonTable()
{
    QVector<Lesson>L=mydb->lesson();
    table1->clearContents();
    table1->setRowCount(L.size());

    for(int i=0;i<L.size();i++)
    {
        Lesson ll=L[i];
        table1->setItem(i,0,new QTableWidgetItem(ll.getLessonName()));
        table1->setItem(i,1,new QTableWidgetItem(QString::number(ll.getLessonID())));
    }
    QStringList LessonsList=mydb->getLessons();
    PerformanceBox->clear();
    for(int i=0;i<LessonsList.size();i++)
        PerformanceBox->addItem(LessonsList[i]);
}

//Slots

void MainWindow::LessondeleteSlot()
{
    if(LessonDeleteId->text()==""){
       QMessageBox::critical(this,"Error","Empty fields");
    }
    mydb->deleteLesson(LessonDeleteId->text().toInt());
    reloadLessonTable();
}

void MainWindow::LessonaddSlot()
{
    if(LessonAddName->text()==""||LessonAddId->text()=="")
    {
        QMessageBox::critical(this,"Error","Empty fields");
    }
    Lesson L(LessonAddName->text(),LessonAddId->text().toInt());
    mydb->insertLesson(L);
    reloadLessonTable();
}

void MainWindow::declarationSlot()
{
    bool StudentExists=mydb->ExistsStudent(StudentID->text().toInt());
    bool LessonExists=mydb->ExistsLesson(LessonID->text().toInt());
    if(StudentID->text()==""||LessonID->text()==""||Grade->text()=="")
    {
        QMessageBox::critical(this,"Warning","Empty fields");
    }else
    if(StudentExists!=true && LessonExists!=true){
        QMessageBox::critical(this,"Warning","Student and Lesson do not exist on database");
    }else
    if(StudentExists!=true){
        QMessageBox::critical(this,"Warning","Student "+QString::number(StudentID->text().toInt())+" does not exists on database.\nYou have to register this student first.");
    }else
    if(LessonExists!=true){
        QMessageBox::critical(this,"Warning","Lesson "+QString::number(LessonID->text().toInt())+" does not exists on database. \nYou have to register this lesson first.");
        }else
    {
     Enroll E(StudentID->text().toInt(),LessonID->text().toInt(),Grade->text().toDouble());
     mydb->insertEnrolment(E);
     }
}

void MainWindow::addSlot()
{

    if(nameEdit->text()==""||lastnameEdit->text()==""||
            idEdit->text()=="")
    {
        QMessageBox::critical(this,"Error","Empty fields");
    }
    Student S(nameEdit->text(),lastnameEdit->text(),idEdit->text().toInt());
    mydb->insertStudent(S);
    reloadStudentTable();

}
void MainWindow::deleteSlot()
{
    if(StudentDeleteID->text()==""){
       QMessageBox::critical(this,"Error","Empty fields");
    }
        mydb->deleteStudent(StudentDeleteID->text().toInt());
        reloadStudentTable();
}

void MainWindow::viewPerformanceSlot()
{
    PerformanceTable->clearContents();
    QStringList temp1=mydb->getPerformanceName(PerformanceBox->currentText());
    QStringList temp2=mydb->getPerformanceGrade(PerformanceBox->currentText());
    PerformanceTable->setRowCount(temp1.size());
    QPixmap pixmap1=QPixmap(":/success.png");
    QPixmap pixmap2=QPixmap(":/failure.png");
    for(int i=0;i<temp1.size();i++){
        PerformanceTable->setItem(i,0,new QTableWidgetItem(temp1[i]));
        PerformanceTable->setItem(i,1,new QTableWidgetItem(temp2[i]));
        if(temp2[i].toDouble()>=5){
            PerformanceTable->setItem(i,2,new QTableWidgetItem("Pass"));
        }else
        {
            PerformanceTable->setItem(i,2,new QTableWidgetItem("Fail"));
        }
    }
}

void MainWindow::searchSlot()
{
    if(lastnameContainsEdit->text().isEmpty() && lastnameStartEdit->text().isEmpty())
    {
        QMessageBox::critical(this,"Error","Empty fields");
        return ;
    }
    QString htmlText="<h3 align=center>Results</h3><ol>";
    QVector<Student> S=mydb->student();
    for(int i=0;i<S.size();i++)
    {
        if(lastnameContainsEdit->text().isEmpty() && !lastnameStartEdit->text().isEmpty())
        {
            if(S[i].getLastName().startsWith(lastnameStartEdit->text()))
            {
                 htmlText+="<ol>"+S[i].toString()+"</ol>";
            }
        }
        else
        if(!lastnameContainsEdit->text().isEmpty() && lastnameStartEdit->text().isEmpty())
        {
            if(S[i].getLastName().contains(lastnameContainsEdit->text()))
            {
                htmlText+="<ol>"+S[i].toString()+"</ol>";
            }
        }
        else
        {
            if(S[i].getLastName().startsWith(lastnameStartEdit->text()) &&
                    S[i].getLastName().contains(lastnameContainsEdit->text()))
            {
                 htmlText+="<ol>"+S[i].toString()+"</ol>";
            }
        }
    }
    htmlText+="</ol>";
    QMessageBox::information(this,"Results",htmlText);
}

void MainWindow::clearSlot()
{
    nameEdit->setText("");
    lastnameEdit->setText("");
    idEdit->setText("");
    StudentID->setText("");
    LessonID->setText("");
    StudentDeleteID->setText("");
    lastnameStartEdit->setText("");
    lastnameContainsEdit->setText("");
    LessonAddName->setText("");
    LessonAddId->setText("");
    LessonDeleteId->setText("");
    Grade->setText("");
}

//Menu slots

void    MainWindow::StudentSlot(QAction *action)
{
    if(action->text()=="Add student")
    {
        panel->setCurrentIndex(0);
    }
    else
    if(action->text()=="Declare lesson")
    {
        panel->setCurrentIndex(3);
    }
    if(action->text()=="Search student")
    {
        panel->setCurrentIndex(1);
    }
    if(action->text()=="Delete student")
    {
        panel->setCurrentIndex(2);
    }

    if(action->text()=="Show students")
    {
        panel->setCurrentIndex(4);
    }
}

void    MainWindow::LessonSlot(QAction *action)
{
    if(action->text()=="Add lesson")
    {
        panel->setCurrentIndex(5);
    }else
    if(action->text()=="Delete lesson")
    {
        panel->setCurrentIndex(6);
    }
    if(action->text()=="Show grades")
    {
        panel->setCurrentIndex(7);
    }
    if(action->text()=="Show lessons")
    {
        panel->setCurrentIndex(8);
    }
}

