#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenu>
#include<QTableWidget>
#include<QMap>

#include"executor.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT


public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();








public slots:
    void buttonClicked();
    void DelButtonClicked();
    void EvalButtonClicked();

    void clearResult();
    void deleteResult();

private slots:
    void on_outputList_customContextMenuRequested(const QPoint &pos);


    void on_outputList_itemDoubleClicked(QTableWidgetItem *item);

private:
    Ui::MainWindow *ui;

    Executor *m_exec;

    QMenu *m_outRight;
    QAction *m_outTrigger;
    QAction *m_outErase;

    QRegExp lambdaReg;
};

#endif // MAINWINDOW_H
