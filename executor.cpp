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
    eng->evaluate("sin=Math.sin;asin=Math.asin;");
    eng->evaluate("cos=Math.cos;acos=Math.acos;");
    eng->evaluate("tan=Math.tan;atan=Math.atan;");

    eng->evaluate("ln=Math.log;lg=Math.log10;");
    eng->evaluate("function log(a,b) {return Math.log(b)/Math.log(a);}");
    eng->evaluate("pow=Math.pow; function root(a,b) { return Math.pow(a,1/b); }");

    eng->evaluate("function sinh(x) {return (pow(_e,x)-pow(_e,-x))/2;}");
    eng->evaluate("function cosh(x) {return (pow(_e,x)+pow(_e,-x))/2;}");
    eng->evaluate("function tanh(x) {return sinh(x)/cosh(x);}");
    eng->evaluate("function asinh(x) {return ln(x+root(x*x+1,2));}");
    eng->evaluate("function acosh(x) {return ln(x+root(x*x-1,2));}");
    eng->evaluate("function atanh(x) {return 1.0/2*ln((1+x)/(1-x));}");

    eng->evaluate("function _Calculus(func,low,high,n) { if(typeof(func)!=\"function\") {return \"Need a function as first parameter.\";} if(n==undefined) {n=1000;} sum=0; delt=(high-low)/(n-1); for(var i=low;i<high;i+=delt) { sum+= func(i)*delt; } return sum;}");
    eng->evaluate("\
function _Derivative(func,x) {\
    if(typeof(func)!=\"function\") {return \"Need a function as first parameter.\";}\
    var delta=0.0001;\
    fx2=func(x+delta);\
    fx1=func(x-delta);\
    return (fx2-fx1)/(2*delta);\
}");
    eng->evaluate("\
function BSolve(func,a,b) {\
    if(typeof(func)!=\"function\") {return \"Need a function as first parameter.\";}\
    var delta=0.0001;\
    while(Math.abs(b-a) >= delta) {\
        var c=(a+b)/2;\
        if( func(a)==0 ) return a;\
        if( func(b)==0 ) return b;\
        if(func(a)*func(c)<=0) b=c;\
        else a=c;}\
    if(func(a)*func(b)<=0) return (a+b)/2;\
    else return \"No result!\"\
}\
");
    eng->evaluate("\
function NSolve(func,a,n) {\
    if(typeof(func)!=\"function\") {return \"Need a function as first parameter.\";}\
    if(n==undefined) n=100;\
    x=a;\
    for(i=0;i<n;++i) {\
        k=_Derivative(func,x);\
        x=x-func(x)/k;\
    }\
    if( Math.abs(func(x)) > 0.1) {\
        return \"Can't Solve!\";}\
    return x;\
}");
    eng->evaluate("function _Sigma(func,low,high) { if(typeof(func)!=\"function\") {return \"Need a function as first parameter.\";} var sum=0; low=parseInt(low);high=parseInt(high); for(var i=low;i<=high;++i) {sum+=func(i);} return sum;}");
    eng->evaluate("_pi=Math.PI;_e=Math.E;");
}
