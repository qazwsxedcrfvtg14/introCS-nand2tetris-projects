#pragma GCC optimize ("O3")
#include<bits/stdc++.h>
#pragma GCC optimize ("O3")
using namespace std;
#define f first
#define s second
typedef pair<int,int>par;
typedef pair<int,par>pr;
//0x0000~0x1999 Mem
//0x2000~0x2999 Flag
//0x3000~0x3999 Stack
//0x4000~0x5999 Screen
//0x6000 KBD
const int FlagTop=0x2000;
const int StackTop=0x3000;
void put(string s){puts(s.c_str());}
void while_true(){
    string rng_string;
    for(int i=0;i<8;i++)
        rng_string+=(rand()>>2)%26+'A';
    put("(while_"+rng_string+"_true)");
    put("@while_"+rng_string+"_true");
    put("0;JMP");
    }
template<typename T>
string ToStr(T x){
    stringstream str;
    string s;
    str<<x;
    str>>s;
    return s;
    }
int objcnt=0;
class obj{
    private:
        int id;
    public:
        int star;
        inline int get_id(){return id;}
        obj(){
            id=objcnt++;star=0;
            }
        obj(int _id){
            id=_id;star=0;
            }
        obj(const obj& x){id=x.id;star=x.star;}
        void resetid(int x){
            id=x;
            }
        void run_star()const{
            for(int i=0;i<star;i++)
                put("A=M");
            }
        void operator=(int x){
            if(x>=0){
                put("@"+ToStr(x));
                put("D=A");
                }
            else{
                put("@"+ToStr(-x));
                put("D=-A");
                }
            put("@"+ToStr(id));
            run_star();
            put("M=D");
            }
        void operator=(const obj& x){
            put("@"+ToStr(x.id));
            x.run_star();
            put("D=M");
            put("@"+ToStr(id));
            run_star();
            put("M=D");
            }
        void operator=(string s){
            put("@"+s);
            put("D=A");
            put("@"+ToStr(id));
            run_star();
            put("M=D");
            }
        void operator++(int x){
            put("@"+ToStr(id));
            run_star();
            put("D=M+1");
            put("M=D");
            }
        void operator--(int x){
            put("@"+ToStr(id));
            run_star();
            put("D=M-1");
            put("M=D");
            }
        void operator+=(int x){
            if(x>=0){
                put("@"+ToStr(x));
                put("D=A");
                }
            else{
                put("@"+ToStr(-x));
                put("D=-A");
                }
            put("@"+ToStr(id));
            run_star();
            put("M=M+D");
            }
        void operator-=(int x){
            if(x>=0){
                put("@"+ToStr(x));
                put("D=A");
                }
            else{
                put("@"+ToStr(-x));
                put("D=-A");
                }
            put("@"+ToStr(id));
            run_star();
            put("M=M-D");
            }
        void operator+=(const obj &x){
            put("@"+ToStr(x.id));
            x.run_star();
            put("D=M");
            put("@"+ToStr(id));
            run_star();
            put("M=M+D");
            }
        void operator-=(const obj &x){
            put("@"+ToStr(x.id));
            x.run_star();
            put("D=M");
            put("@"+ToStr(id));
            run_star();
            put("M=M-D");
            }
        void toA(){
            put("@"+ToStr(id));
            put("A=M");
            run_star();
            }
        void toD(){
            put("@"+ToStr(id));
            run_star();
            put("A=M");
            put("D=A");
            }
    };
map<string,obj> glo;
stack<int> esp_ebp;
bool var_id;
class var{
    private:
        int pos;
    public:
        var(){
            pos=esp_ebp.top()++;
            glo["esp"]++;
            }
        var(const var& x){
            pos=x.pos;
            }
        var(const obj& x)=delete;
        var(int x){
            pos=x;
            }
        void operator=(int x){
            pos=esp_ebp.top()++;
            glo["esp"]++;
            (this->to_obj())=x;
            }
        void operator=(const var& x){
            pos=esp_ebp.top()++;
            glo["esp"]++;
            (this->to_obj())=x;
            }
        void operator=(const obj& x){
            pos=esp_ebp.top()++;
            glo["esp"]++;
            (this->to_obj())=x;
            }
        void operator=(string s){
            pos=esp_ebp.top()++;
            glo["esp"]++;
            (this->to_obj())=s;
            }
        /*explicit */operator obj(){
            glo[var_id?"var1":"var2"]=glo["ebp"];
            glo[var_id?"var1":"var2"]+=pos;
            obj ret(glo[var_id?"var1":"var2"]);
            ret.star++;
            var_id=!var_id;
            return ret;
            }
        operator obj()const{
            glo[var_id?"var1":"var2"]=glo["ebp"];
            glo[var_id?"var1":"var2"]+=pos;
            obj ret(glo[var_id?"var1":"var2"]);
            ret.star++;
            var_id=!var_id;
            return ret;
            }
        obj to_obj(){
            glo[var_id?"var1":"var2"]=glo["ebp"];
            glo[var_id?"var1":"var2"]+=pos;
            obj ret(glo[var_id?"var1":"var2"]);
            ret.star++;
            var_id=!var_id;
            return ret;
            }
        void operator++(int x){
            (this->to_obj())++;
            }
        void operator--(int x){
            (this->to_obj())--;
            }
        void operator+=(int x){
            (this->to_obj())+=x;
            }
        void operator-=(int x){
            (this->to_obj())-=x;
            }
        void operator+=(const obj &x){
            (this->to_obj())+=x;
            }
        void operator-=(const obj &x){
            (this->to_obj())-=x;
            }
        void toA(){
            (this->to_obj()).toA();
            }
        void toD(){
            (this->to_obj()).toD();
            }
    };
class memory{
    public:
        obj operator[](int x){
            obj ret(x);
            return ret;
        }
        obj operator[](obj x){
            obj ret(x);
            ret.star++;
            return ret;
        }
    }mem;
void push(){
    mem[glo["esp"]]=glo["ebp"];
    glo["esp"]++;
    glo["ebp"]=glo["esp"];
    }
void pop(){
    glo["ebp"]--;
    glo["esp"]=glo["ebp"];
    glo["ebp"]=mem[glo["ebp"]];
    }
//old data
//return pc 88
//subfunction return value 89
//saved ebp 90
//subfunction arg0 91
//return pc 92
//subfunction return value 93
//saved ebp 94
//subfunction arg0 95
//return pc 96
//subfunction return value 97
//saved ebp 98
//subfunction arg0 99
//return pc 00
//subfunction return value 01
//saved ebp 02
//subfunction arg0 03
//...
map<string,int>func_args;
stack<string>func_stack;
stack<int>block_stack;
void FuncBegin(string fun,int args=0){
    if(func_args.find(fun)!=func_args.end()) throw "error";
    block_stack.push(0);
    func_stack.push(fun);
    func_args[fun]=args;
    put("@Func_"+fun+"_end");
    put("0;JMP");
    put("(Func_"+fun+"_begin)");
    push();
    if(args)
        glo["esp"]+=args;
    esp_ebp.push(args);
    }
template<typename T>
void FuncReturn(T ret){
    string fun=func_stack.top();
    glo["tmp"]=glo["ebp"];
    glo["tmp"]-=2;
    mem[glo["tmp"]]=ret;
    put("@Func_"+fun+"_return");
    put("0;JMP");
    }
void FuncEnd(){
    string fun=func_stack.top();
    func_stack.pop();
    put("(Func_"+fun+"_return)");
    pop();
    glo["esp"]--;
    glo["esp"]--;
    mem[glo["esp"]].toA();
    put("0;JMP");
    put("(Func_"+fun+"_end)");
    esp_ebp.pop();
    }
void FuncCallArgs(){}
template<typename T,typename... Args>
void FuncCallArgs(T arg,Args... args){
    glo["arg"]++;
    mem[glo["arg"]]=arg;
    FuncCallArgs(args...);
    }
template<typename... Args>
var FuncCall(string fun, Args... args){
    string rng_string;
    for(int i=0;i<8;i++)
        rng_string+=(rand()>>2)%26+'A';
    mem[glo["esp"]]=("Func_Call_"+rng_string+"_after");
    glo["esp"]++;
    glo["esp"]++;//return value
    glo["arg"]=glo["esp"];
    FuncCallArgs(args...);
    put("@Func_"+fun+"_begin");
    put("0;JMP");
    put("(Func_Call_"+rng_string+"_after)");
    glo["tmp"]=glo["esp"];
    glo["tmp"]++;
    mem[glo["esp"]]=mem[glo["tmp"]];
    glo["esp"]++;
    var ret(esp_ebp.top()++);
    return ret;
    }
stack<string>if_stack;
template<typename T,typename S>
void IfBegin(T x,string cmp,S y){
    block_stack.push(1);
    string rng_string;
    for(int i=0;i<8;i++)
        rng_string+=(rand()>>2)%26+'A';
    if_stack.push(rng_string);
    glo["cmp"]=x;
    glo["cmp"]-=y;
    glo["cmp"].toD();
    put("@if_"+rng_string+"_end");
    if(cmp=="<")
        put("D;JGE");
    if(cmp=="<=")
        put("D;JGT");
    if(cmp=="==")
        put("D;JNE");
    if(cmp==">")
        put("D;JLE");
    if(cmp==">=")
        put("D;JLT");
    if(cmp=="!=")
        put("D;JEQ");
    }
void IfEnd(){
    string rng_string=if_stack.top();
    if_stack.pop();
    put("(if_"+rng_string+"_end)");
    }
stack<string>loop_stack;
void LoopBegin(){
    block_stack.push(2);
    string rng_string;
    for(int i=0;i<8;i++)
        rng_string+=(rand()>>2)%26+'A';
    loop_stack.push(rng_string);
    put("(loop_"+rng_string+"_begin)");
    }
void LoopBreak(){
    string rng_string=loop_stack.top();
    put("@loop_"+rng_string+"_end");
    put("0;JMP");
    }
void LoopEnd(){
    string rng_string=loop_stack.top();
    loop_stack.pop();
    put("@loop_"+rng_string+"_begin");
    put("0;JMP");
    put("(loop_"+rng_string+"_end)");
    }
void BlockEnd(){
    int top=block_stack.top();
    block_stack.pop();
    if(top==0)FuncEnd();
    else if(top==1)IfEnd();
    else if(top==2)LoopEnd();
    }
void Setup(){
    objcnt=FlagTop;
    glo["ebp"]=StackTop;
    glo["esp"]=glo["ebp"];
    esp_ebp.push(0);
    }
vector<string>ve;
//W=32*16
//H=256
#define Call FuncCall
#define Loop LoopBegin();
#define If(a,b,c) IfBegin((a),(b),(c));
#define Func(a,b) FuncBegin((a),(b));
#define End BlockEnd();
#define Return(a) FuncReturn((a))
#define Break LoopBreak();
int main(){
    Setup();
    var i;
    i=0x4000;
    Loop{
        mem[i]=32767;
        i++;
        If(i,"==",0x4020){
            Break
        }End
    }End
    Func("fib",1){
        var x(0);
        If(x,"==",-1){
            Return(1);
        }End
        If(x,"==",0){
            Return(1);
        }End
        var ret,tmp;
        ret=0;
        tmp=x;
        tmp--;
        ret+=Call("fib",tmp);
        tmp--;
        ret+=Call("fib",tmp);
        Return(ret);
    }End
    var ans;
    ans=Call("fib",mem[0]);
    mem[2]=ans;
    while_true();
    return 0;
    }
