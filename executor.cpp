#include"executor.h"
#include<QMapIterator>
#include<QVector>

Executor::Executor() {
    eng = new QJSEngine();
	
	QString regs[]={
        "_A","_B","_C","_D","_E","_F"
	};
	
	for(auto &a : regs) {
		eng->globalObject().setProperty(a,0);
	}
	

}

Executor::Executor( QMap<QString,QJSValue> &env) {
    auto iter=env.begin();
    eng = new QJSEngine();

    for(;iter!=env.end();++iter) {
        eng->globalObject().setProperty(iter.key(),iter.value());
    }
	
    QString regs[]={
        "_A","_B","_C","_D","_E","_F"
    };

    for(auto &a : regs) {
        eng->globalObject().setProperty(a,0);
    }

}

Executor::~Executor() {
    delete this->eng;
}


QJSValue Executor::exec(QString &line) {
    return eng->evaluate(line);
}


QJSValue Executor::getValue(QString &name) {
	return eng->globalObject().property(name);
}


void Executor::assign(QString &name,QJSValue vl) {
    eng->globalObject().setProperty(name,vl);
}
