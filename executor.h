#ifndef EXECUTOR_H
#define EXECUTOR_H

#include<QMap>
#include<QJSEngine>

// This class is an encapsulation of QJSEngine
// Executor::exec can evaluate a QString expression
// Executor::getValue can get a variable value in the engine
// Executor::assign can assign a value to variable in the engine
// Executor::initFunc initializes all math functions in the engine

class Executor {
public:
    Executor();
    Executor( QMap< QString, QJSValue> &env);
    ~Executor();

    QJSValue exec(QString line);
	
    QJSValue getValue(QString name);

    void assign(QString name,QJSValue vl);
    void initFunc();

private:
    QJSEngine *eng;


};


#endif // EXECUTOR_H
