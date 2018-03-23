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
	
    initFunc();

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

    initFunc();

}

Executor::~Executor() {
    delete this->eng;
}


QJSValue Executor::exec(QString line) {
    return eng->evaluate(line);
}


QJSValue Executor::getValue(QString name) {
	return eng->globalObject().property(name);
}


void Executor::assign(QString name,QJSValue vl) {
    eng->globalObject().setProperty(name,vl);
}

void Executor::initFunc() {
    eng->evaluate("sin=Math.sin;sinh=Math.sinh;asin=Math.asin;asinh=Math.asinh;");
    eng->evaluate("cos=Math.cos;cosh=Math.cosh;acos=Math.acos;aconh=Math.acosh;");
    eng->evaluate("tan=Math.tan;tanh=Math.tanh;atan=Math.atan;atanh=Math.atanh;");
    eng->evaluate("ln=Math.log;lg=Math.log10;");
    eng->evaluate("function log(a,b) {return Math.log(b)/Math.log(a);}");
    eng->evaluate("pow=Math.pow; function root(a,b) { return Math.pow(a,1/b); }");


    eng->evaluate("function _Calculus(func,low,high,n) { if(typeof(func)!=\"function\") {return \"Need a function as first parameter.\";} if(n==undefined) {n=1000;} sum=0; delt=(high-low)/n; for(var i=low;i<=high;i+=delt) { sum+= func(i)*delt; } return sum;}");
    eng->evaluate("\
function _Derivative(func,x) {\
    if(typeof(func)!=\"function\") {return \"Need a function as first parameter.\";}\
    var delta=0.0001;\
    fx2=func(x+delta);\
    fx1=func(x-delta);\
    return (fx2-fx1)/(2*delta);\
}");
    eng->evaluate("function _Sigma(func,low,high) { if(typeof(func)!=\"function\") {return \"Need a function as first parameter.\";} var sum=0; low=parseInt(low);high=parseInt(high); for(var i=low;i<=high;++i) {sum+=func(i);} return sum;}");
    eng->evaluate("_pi=Math.PI;_e=Math.E;");
}
