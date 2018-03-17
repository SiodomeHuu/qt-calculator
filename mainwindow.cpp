#include "mainwindow.h"
#include "ui_mainwindow.h"

#include<QMessagebox>


#include<QtDebug>


#pragma execution_character_set("utf-8")






const static QMap<QString,QString> helpNote = {
    {"E", "123E4  equals to 123*pow(10,4)"},
    {"Ans","The answer you just got"},

    {"_A","_A register"},
    {"_B","_B register"},
    {"_C","_C register"},
    {"_D","_D register"},
    {"_E","_E register"},
    {"_F","_F register"},
    {"x","Variable x, use in ¦Ë function"},


    {"sin(","sin(radius)"},
    {"cos(","cos(radius"},
    {"tan(","tan(radius"},
    {"cot(","cot(radius"},
    {"sinh(","sinh(radius)"},
    {"cosh(","cosh(radius"},
    {"tanh(","tanh(radius"},
    {"coth(","coth(radius"},
    {"log(","log(a,b)"},
    {"lg(","lg(b)  equals to log(10,b)"},
    {"ln(", "ln(b)  equals to log(e,b)"},
    {"pow(", "pow(a,b)  a^b"},
    {"root(", "root(a,b)  equals to pow(a,1/b)"},

    {"Assign("," Assign(a,b)  assign a to b, and return value b"},


    {"¡Ò(", "¡Ò(¦Ë(x),low,high,n=1000)"},
    {"¡Æ(", "¡Æ(¦Ë(x),low,high)"},
    {"£ä£¯£ä£ø(","d/dx(¦Ë(x),x0)  the gradient of function ¦Ë at x=x0"},
    {"¦Ë.x->(","¦Ë.x->(x+3)  represents a lambda function"}

};










MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);



    this->m_exec = new Executor();
    this->setFixedSize(this->size());
    this->setWindowFlags(windowFlags()&~Qt::WindowMaximizeButtonHint);




    m_outRight = new QMenu(this);
    m_outTrigger = new QAction("ÇåÆÁ",this);
    m_outRight->addAction(m_outTrigger);

    QObject::connect( m_outTrigger, SIGNAL(triggered()),ui->outputList,SLOT(clear()));

    //Del button
    QObject::connect( ui->pushButton_del, SIGNAL(clicked()), this, SLOT(DelButtonClicked()));


    //Number button,dot and 10e
    QObject::connect( ui->pushButton_0, SIGNAL(clicked()) , this, SLOT(buttonClicked()) );
    QObject::connect( ui->pushButton_1, SIGNAL(clicked()) , this, SLOT(buttonClicked()) );
    QObject::connect( ui->pushButton_2, SIGNAL(clicked()) , this, SLOT(buttonClicked()) );
    QObject::connect( ui->pushButton_3, SIGNAL(clicked()) , this, SLOT(buttonClicked()) );
    QObject::connect( ui->pushButton_4, SIGNAL(clicked()) , this, SLOT(buttonClicked()) );
    QObject::connect( ui->pushButton_5, SIGNAL(clicked()) , this, SLOT(buttonClicked()) );
    QObject::connect( ui->pushButton_6, SIGNAL(clicked()) , this, SLOT(buttonClicked()) );
    QObject::connect( ui->pushButton_7, SIGNAL(clicked()) , this, SLOT(buttonClicked()) );
    QObject::connect( ui->pushButton_8, SIGNAL(clicked()) , this, SLOT(buttonClicked()) );
    QObject::connect( ui->pushButton_9, SIGNAL(clicked()) , this, SLOT(buttonClicked()) );
    QObject::connect( ui->pushButton_dot, SIGNAL(clicked()) , this, SLOT(buttonClicked()) );
    QObject::connect( ui->pushButton_10e, SIGNAL(clicked()) , this, SLOT(buttonClicked()) );


    //Math function
    QObject::connect( ui->pushButton_sin, SIGNAL(clicked()) , this, SLOT(buttonClicked()) );
    QObject::connect( ui->pushButton_sinh, SIGNAL(clicked()) , this, SLOT(buttonClicked()) );
    QObject::connect( ui->pushButton_cos, SIGNAL(clicked()) , this, SLOT(buttonClicked()) );
    QObject::connect( ui->pushButton_cosh, SIGNAL(clicked()) , this, SLOT(buttonClicked()) );
    QObject::connect( ui->pushButton_tan, SIGNAL(clicked()) , this, SLOT(buttonClicked()) );
    QObject::connect( ui->pushButton_tanh, SIGNAL(clicked()) , this, SLOT(buttonClicked()) );

    QObject::connect( ui->pushButton_cot, SIGNAL(clicked()) , this, SLOT(buttonClicked()) );
    QObject::connect( ui->pushButton_coth, SIGNAL(clicked()) , this, SLOT(buttonClicked()) );
    QObject::connect( ui->pushButton_log, SIGNAL(clicked()) , this, SLOT(buttonClicked()) );
    QObject::connect( ui->pushButton_ln, SIGNAL(clicked()) , this, SLOT(buttonClicked()) );
    QObject::connect( ui->pushButton_lg, SIGNAL(clicked()) , this, SLOT(buttonClicked()) );
    QObject::connect( ui->pushButton_pow, SIGNAL(clicked()) , this, SLOT(buttonClicked()) );

    QObject::connect( ui->pushButton_root, SIGNAL(clicked()) , this, SLOT(buttonClicked()) );
    QObject::connect( ui->pushButton_lambda, SIGNAL(clicked()) , this, SLOT(buttonClicked()) );




    //Register
    QObject::connect( ui->pushButton_A, SIGNAL(clicked()) , this, SLOT(buttonClicked()) );
    QObject::connect( ui->pushButton_B, SIGNAL(clicked()) , this, SLOT(buttonClicked()) );
    QObject::connect( ui->pushButton_C, SIGNAL(clicked()) , this, SLOT(buttonClicked()) );
    QObject::connect( ui->pushButton_D, SIGNAL(clicked()) , this, SLOT(buttonClicked()) );
    QObject::connect( ui->pushButton_E, SIGNAL(clicked()) , this, SLOT(buttonClicked()) );
    QObject::connect( ui->pushButton_F, SIGNAL(clicked()) , this, SLOT(buttonClicked()) );
    QObject::connect( ui->pushButton_x, SIGNAL(clicked()) , this, SLOT(buttonClicked()) );



    //Const
    QObject::connect( ui->pushButton_pi, SIGNAL(clicked()) , this, SLOT(buttonClicked()) );
    QObject::connect( ui->pushButton_e, SIGNAL(clicked()) , this, SLOT(buttonClicked()) );

    //Calculus
    QObject::connect( ui->pushButton_calculus, SIGNAL(clicked()) , this, SLOT(buttonClicked()) );
    QObject::connect( ui->pushButton_derivative, SIGNAL(clicked()) , this, SLOT(buttonClicked()) );
    QObject::connect( ui->pushButton_sigma, SIGNAL(clicked()) , this, SLOT(buttonClicked()) );
    QObject::connect( ui->pushButton_assign, SIGNAL(clicked()) , this, SLOT(buttonClicked()) );

    //BinOP & other
    QObject::connect( ui->pushButton_add, SIGNAL(clicked()) , this, SLOT(buttonClicked()) );
    QObject::connect( ui->pushButton_sub, SIGNAL(clicked()) , this, SLOT(buttonClicked()) );
    QObject::connect( ui->pushButton_mult, SIGNAL(clicked()) , this, SLOT(buttonClicked()) );
    QObject::connect( ui->pushButton_div, SIGNAL(clicked()) , this, SLOT(buttonClicked()) );
    QObject::connect( ui->pushButton_mod, SIGNAL(clicked()) , this, SLOT(buttonClicked()) );
    QObject::connect( ui->pushButton_leftparen, SIGNAL(clicked()) , this, SLOT(buttonClicked()) );
    QObject::connect( ui->pushButton_rightparen, SIGNAL(clicked()) , this, SLOT(buttonClicked()) );
    QObject::connect( ui->pushButton_ans, SIGNAL(clicked()) , this, SLOT(buttonClicked()) );
    QObject::connect( ui->pushButton_comma, SIGNAL(clicked()) , this, SLOT(buttonClicked()) );

    //Exec
    QObject::connect( ui->pushButton_eval, SIGNAL(clicked()) , this, SLOT(EvalButtonClicked()) );


    statusBar()->showMessage("Welcome!");
}

MainWindow::~MainWindow()
{
    delete this->m_exec;
    delete ui;
}




void MainWindow::DelButtonClicked() {
    ui->inputLine->backspace();
    ui->inputLine->setFocus();
}

// all buttons should add their text onto the line
// except for del, eval, ac, etc..
void MainWindow::buttonClicked() {
    auto bt = dynamic_cast<QPushButton*> ( QObject::sender() );
    QString text = bt->text();
    ui->inputLine->insert(text);
    ui->inputLine->setFocus();


    auto iter = helpNote.find(text);
    if(iter!=helpNote.end()) {
        statusBar()->showMessage(iter.value());
    }
    else {
        statusBar()->showMessage("");
    }
}


void MainWindow::EvalButtonClicked() {

}









void MainWindow::on_outputList_customContextMenuRequested(const QPoint &pos) {
    m_outRight->move(cursor().pos());
    m_outRight->show();
}

void MainWindow::on_outputList_itemDoubleClicked(QListWidgetItem *item) {
    ui->inputLine->setText( item->text() );
}
