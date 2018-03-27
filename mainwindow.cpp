#include "mainwindow.h"
#include "ui_mainwindow.h"

#include<QMessagebox>
#include<QHeaderView>

#include<QScrollBar>

#include<QtDebug>


#pragma execution_character_set("utf-8")





// Explaination of some buttons
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
    {"cos(","cos(radius)"},
    {"tan(","tan(radius)"},
    {"asin(","asin(float)"},
    {"acos(","acos(float)"},
    {"atan(","atan(float)"},

    {"sinh(","sinh(radius)"},
    {"cosh(","cosh(radius)"},
    {"tanh(","tanh(radius)"},
    {"asinh(","asinh(float)"},
    {"acosh(","acosh(float)"},
    {"atanh(","atanh(float)"},

    {"log(","log(a,b)"},
    {"lg(","lg(b)  equals to log(10,b)"},
    {"ln(", "ln(b)  equals to log(e,b)"},
    {"pow(", "pow(a,b)  a^b"},
    {"root(", "root(a,b)  equals to pow(a,1/b)"},
    {"BSolve(","BSolve(¦Ë(x){},a,b) Search result for ¦Ë(x)=0 between a and b Binary."},
    {"NSolve(","NSolve(¦Ë(x){},a,n=100) Search result for ¦Ë(x)=0 around x=a with Newton Methods, iterate n times."},

    {"<-"," _A<-100  assign 100 to _A, and return value 100"},


    {"¡Ò(", "¡Ò(¦Ë(x),low,high,n=1000)"},
    {"¡Æ(", "¡Æ(¦Ë(x),low,high)"},
    {"£ä£¯£ä£ø(","d/dx(¦Ë(x),x0)  the gradient of function ¦Ë at x=x0"},
    {"¦Ë(x){}","¦Ë(x){3*x;}  a function."},
    {"Advance","Enter Advance Mode"}
};










MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);



    this->m_exec = new Executor();
    this->setFixedSize(this->size());
    this->setWindowFlags(windowFlags()&~Qt::WindowMaximizeButtonHint);

	
	// RightContext Menu
    ui->outputList->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->outputList->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->outputList->verticalHeader()->setVisible(false);
    ui->outputList->setColumnWidth(0,500);
    ui->outputList->setColumnWidth(1,100);
    ui->outputList->setSelectionBehavior(QAbstractItemView::SelectRows);


    m_outRight = new QMenu(this);
    m_outTrigger = new QAction("ÇåÆÁ",this);
    m_outErase = new QAction("É¾³ý",this);
    m_outRight->addAction(m_outTrigger);
    m_outRight->addAction(m_outErase);

	
	/*
	 Connect All buttons:
	*/
	
    QObject::connect( m_outTrigger, SIGNAL(triggered()),this, SLOT(clearResult())  );
    QObject::connect( m_outErase, SIGNAL(triggered()),this,SLOT(deleteResult())  );

    QObject::connect( ui->inputLine, SIGNAL(returnPressed()),this,SLOT(EvalButtonClicked()));

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
    QObject::connect( ui->pushButton_asin, SIGNAL(clicked()) , this, SLOT(buttonClicked()) );
    QObject::connect( ui->pushButton_sinh, SIGNAL(clicked()) , this, SLOT(buttonClicked()) );
    QObject::connect( ui->pushButton_asinh, SIGNAL(clicked()) , this, SLOT(buttonClicked()) );
    QObject::connect( ui->pushButton_cos, SIGNAL(clicked()) , this, SLOT(buttonClicked()) );
    QObject::connect( ui->pushButton_acos, SIGNAL(clicked()) , this, SLOT(buttonClicked()) );
    QObject::connect( ui->pushButton_cosh, SIGNAL(clicked()) , this, SLOT(buttonClicked()) );
    QObject::connect( ui->pushButton_acosh, SIGNAL(clicked()) , this, SLOT(buttonClicked()) );
    QObject::connect( ui->pushButton_tan, SIGNAL(clicked()) , this, SLOT(buttonClicked()) );
    QObject::connect( ui->pushButton_atan, SIGNAL(clicked()) , this, SLOT(buttonClicked()) );
    QObject::connect( ui->pushButton_tanh, SIGNAL(clicked()) , this, SLOT(buttonClicked()) );
    QObject::connect( ui->pushButton_atanh, SIGNAL(clicked()) , this, SLOT(buttonClicked()) );


    QObject::connect( ui->pushButton_log, SIGNAL(clicked()) , this, SLOT(buttonClicked()) );
    QObject::connect( ui->pushButton_ln, SIGNAL(clicked()) , this, SLOT(buttonClicked()) );
    QObject::connect( ui->pushButton_lg, SIGNAL(clicked()) , this, SLOT(buttonClicked()) );
    QObject::connect( ui->pushButton_pow, SIGNAL(clicked()) , this, SLOT(buttonClicked()) );

    QObject::connect( ui->pushButton_root, SIGNAL(clicked()) , this, SLOT(buttonClicked()) );
    QObject::connect( ui->pushButton_lambda, SIGNAL(clicked()) , this, SLOT(buttonClicked()) );

    QObject::connect( ui->pushButton_nsolve,SIGNAL(clicked()),this, SLOT(buttonClicked()));
    QObject::connect( ui->pushButton_bsolve,SIGNAL(clicked()),this, SLOT(buttonClicked()));


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
    QString evalLine = ui->inputLine->text();
    evalLine = evalLine.trimmed();
    if(evalLine=="") return;
	// Parse special symbol first
    evalLine.replace("¡Ò","_Calculus");
    evalLine.replace("£ä£¯£ä£ø","_Derivative");
    evalLine.replace("¡Æ","_Sigma");
    evalLine.replace("¦Ë","function");
    evalLine.replace("{","{return ");
    evalLine.replace("¦Ð","_pi");
    evalLine.replace("£å","_e");
    evalLine.replace("<-","=");
    auto temp=m_exec->exec(evalLine);
    QString printAns;
    if( temp.isError() ) {
        printAns="Error!";
    }
    else {
        if(temp.isString()) {
            printAns=temp.toString();
        }
        else {
            printAns.setNum(temp.toNumber(),'g');
            m_exec->assign("Ans",temp);
        }
    }
    int nowRowCount = ui->outputList->rowCount();

    ui->outputList->setRowCount(++nowRowCount);

    ui->outputList->setItem(nowRowCount-1,0,new QTableWidgetItem(ui->inputLine->text()));
    ui->outputList->setItem(nowRowCount-1,1,new QTableWidgetItem(printAns));

    ui->outputList->setCurrentCell(nowRowCount-1,0);

    m_exec->initFunc();
    ui->inputLine->selectAll();
}








// RightContext Menu of the TableWidget
void MainWindow::on_outputList_customContextMenuRequested(const QPoint &pos) {
    m_outRight->move(cursor().pos());
    m_outRight->show();
}

// After double click on the cell of TableWidget,
// automatically copy the cell to the inputLine.
void MainWindow::on_outputList_itemDoubleClicked(QTableWidgetItem *item)
{
    if(item->text()=="Error!") return;
    ui->inputLine->setText( item->text() );
}

// Clear All result
void MainWindow::clearResult() {
    ui->outputList->setRowCount(0);
    ui->outputList->clearContents();
}
// Delete one result which is now choosen
void MainWindow::deleteResult() {
    auto temp=ui->outputList->currentRow();
    if(temp!=-1) {
        ui->outputList->removeRow(temp);
    }
}
