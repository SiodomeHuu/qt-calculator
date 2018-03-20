#ifndef EXECUTOR_H
#define EXECUTOR_H

#include<QMap>
#include<QJSEngine>

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
