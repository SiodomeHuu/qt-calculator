#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenu>
#include<QListWidget>
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

private slots:
    void on_outputList_customContextMenuRequested(const QPoint &pos);

    void on_outputList_itemDoubleClicked(QListWidgetItem *item);

private:
    Ui::MainWindow *ui;

    Executor *m_exec;

    QMenu *m_outRight;
    QAction *m_outTrigger;

   // QMap< QString,QString >
};

#endif // MAINWINDOW_H
