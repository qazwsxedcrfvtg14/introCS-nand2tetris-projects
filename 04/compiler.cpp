#pragma GCC optimize ("O3")
#include<bits/stdc++.h>
#pragma GCC optimize ("O3")
using namespace std;
#define f first
#define s second
typedef pair<int,int>par;
typedef pair<int,par>pr;
//0x0000~0x2EFF Mem
//0x3D00~0x3DFF Flag
//0x3E00~0x3FFF Stack
//0x4000~0x5FFF Screen
//0x6000 KBD
const int FlagTop=0x3D00;
const int StackTop=0x3E00;
vector<string>cmd;
void put(string s){
    cmd.push_back(s);
    return;
    }
void optimize(int o=0){
    if(o<=0){
        for(string &s:cmd)
            puts(s.c_str());
        return;
        }
    int sz=cmd.size();
    vector<string>result,optres;
    string preA="-1";
    for(int i=0;i<sz;i++){
        string s=cmd[i];
        string preCmd=result.size()>=1?result.back():"~~";
        string preCmd2=result.size()>=2?result[result.size()-2]:"~~";
        if(s.length()>1&&s[0]=='@'){
            string nowA=s.substr(1);
            if(preA==nowA)continue;
            preA=nowA;
            }
        if(s.length()>1&&s[0]=='(')
            preA="-1";
        if(s.length()>1&&s[0]=='A')
            preA="-1";
        if(s.length()>2&&s[0]=='A')
            preA="-1";
        if(preCmd=="M=D"&&(s=="M=D"||s=="D=M"))continue;
        if(preCmd=="D=M"&&(s=="M=D"||s=="D=M"))continue;
        if(preCmd2=="M=D"&&preCmd=="A=M"&&s=="D=A")continue;
        if(preCmd=="M=M+1"&&s=="M=M-1"){result.pop_back();continue;}
        if(preCmd=="M=M-1"&&s=="M=M+1"){result.pop_back();continue;}
        if(preCmd=="D=D+1"&&s=="D=D-1"){result.pop_back();continue;}
        if(preCmd=="D=D-1"&&s=="D=D+1"){result.pop_back();continue;}
        if(preCmd.length()>2&&s.length()>2&&preCmd=="M="&&s=="M="){result.pop_back();result.push_back(s);continue;}
        if(preCmd.length()>2&&s.length()>2&&preCmd=="D="&&s=="D="){result.pop_back();result.push_back(s);continue;}
        if(preCmd=="M=D"&&s=="M=M+1"){result.pop_back();result.push_back("M=D+1");continue;}
        if(preCmd=="M=D"&&s=="M=M-1"){result.pop_back();result.push_back("M=D-1");continue;}
        if(preCmd=="M=D"&&s=="M=-M"){result.pop_back();result.push_back("M=-D");continue;}
        result.push_back(s);
        }
    if(o<=1){
        for(string &s:result)
            puts(s.c_str());
        return;
        }
    sz=result.size();
    for(int i=0;i<sz;i++){
        string s=result[i];
        string preCmd=optres.size()>=1?optres.back():"~~";
        string preCmd2=optres.size()>=2?optres[optres.size()-2]:"~~";
        if(preCmd.length()>2&&preCmd.substr(0,2)=="M="&&s=="D=M"){optres.pop_back();optres.push_back("MD="+preCmd.substr(2));continue;}
        if(preCmd.length()>2&&preCmd.substr(0,2)=="M="&&s=="A=M"){optres.pop_back();optres.push_back("AM="+preCmd.substr(2));continue;}
        if(preCmd.length()>2&&preCmd.substr(0,2)=="A="&&s=="D=A"){optres.pop_back();optres.push_back("AD="+preCmd.substr(2));continue;}
        if(preCmd.length()>2&&preCmd.substr(0,2)=="D="&&s=="M=D"){optres.pop_back();optres.push_back("MD="+preCmd.substr(2));continue;}
        if(preCmd.length()>2&&preCmd.substr(0,2)=="D="&&s=="A=D"){optres.pop_back();optres.push_back("AD="+preCmd.substr(2));continue;}
        optres.push_back(s);
        }
    for(string &s:optres)
        puts(s.c_str());
    }
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
            if(x==0){
                put("@"+ToStr(id));
                run_star();
                put("M=0");
                }
            else if(x==1){
                put("@"+ToStr(id));
                run_star();
                put("M=1");
                }
            else if(x==-1){
                put("@"+ToStr(id));
                run_star();
                put("M=-1");
                }
            else if(x==-32768){
                put("@"+ToStr(32767));
                put("D=-A");
                put("@"+ToStr(id));
                run_star();
                put("M=D-1");
                }
            else if(x>0){
                put("@"+ToStr(x));
                put("D=A");
                put("@"+ToStr(id));
                run_star();
                put("M=D");
                }
            else{
                put("@"+ToStr(-x));
                put("D=-A");
                put("@"+ToStr(id));
                run_star();
                put("M=D");
                }
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
            put("M=M+1");
            }
        void operator--(int x){
            put("@"+ToStr(id));
            run_star();
            put("M=M-1");
            }
        void operator+=(int x){
            if(x==0)
                return;
            else if(x==1){
                put("@"+ToStr(id));
                run_star();
                put("M=M+1");
                }
            else if(x==-1){
                put("@"+ToStr(id));
                run_star();
                put("M=M-1");
                }
            else if(x==2){
                put("@"+ToStr(id));
                run_star();
                put("M=M+1");
                put("M=M+1");
                }
            else if(x==-2){
                put("@"+ToStr(id));
                run_star();
                put("M=M-1");
                put("M=M-1");
                }
            else if(x>=0){
                put("@"+ToStr(x));
                put("D=A");
                put("@"+ToStr(id));
                run_star();
                put("M=M+D");
                }
            else if(x==-32768){
                put("@"+ToStr(32767));
                put("D=-A");
                put("D=D-1");
                put("@"+ToStr(id));
                run_star();
                put("M=M+D");
                }
            else{
                put("@"+ToStr(-x));
                put("D=-A");
                put("@"+ToStr(id));
                run_star();
                put("M=M+D");
                }
            }
        void operator&=(int x){
            if(x==0){
                put("@"+ToStr(id));
                run_star();
                put("M=0");
                }
            else if(x>0){
                put("@"+ToStr(x));
                put("D=A");
                put("@"+ToStr(id));
                run_star();
                put("M=M&D");
                }
            else{
                put("@"+ToStr(-x));
                put("D=-A");
                put("@"+ToStr(id));
                run_star();
                put("M=M&D");
                }
            }
        void operator|=(int x){
            if(x==0){
                return;
                }
            else if(x>0){
                put("@"+ToStr(x));
                put("D=A");
                put("@"+ToStr(id));
                run_star();
                put("M=M|D");
                }
            else{
                put("@"+ToStr(-x));
                put("D=-A");
                put("@"+ToStr(id));
                run_star();
                put("M=M|D");
                }
            }
        void operator-=(int x){
            if(x==0)
                return;
            else if(x==1){
                put("@"+ToStr(id));
                run_star();
                put("M=M-1");
                }
            else if(x==-1){
                put("@"+ToStr(id));
                run_star();
                put("M=M+1");
                }
            else if(x==2){
                put("@"+ToStr(id));
                run_star();
                put("M=M-1");
                put("M=M-1");
                }
            else if(x==-2){
                put("@"+ToStr(id));
                run_star();
                put("M=M+1");
                put("M=M+1");
                }
            else if(x>=0){
                put("@"+ToStr(x));
                put("D=A");
                put("@"+ToStr(id));
                run_star();
                put("M=M-D");
                }
            else if(x==-32768){
                put("@"+ToStr(32767));
                put("D=-A");
                put("D=D-1");
                put("@"+ToStr(id));
                run_star();
                put("M=M-D");
                }
            else{
                put("@"+ToStr(-x));
                put("D=-A");
                put("@"+ToStr(id));
                run_star();
                put("M=M-D");
                }
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
        void operator&=(const obj &x){
            put("@"+ToStr(x.id));
            x.run_star();
            put("D=M");
            put("@"+ToStr(id));
            run_star();
            put("M=M&D");
            }
        void operator|=(const obj &x){
            put("@"+ToStr(x.id));
            x.run_star();
            put("D=M");
            put("@"+ToStr(id));
            run_star();
            put("M=M|D");
            }
        void operator*=(int x){
            if(x==1)
                return;
            else if(x==-1){
                put("@"+ToStr(id));
                run_star();
                put("M=-M");
                }
            else if(x==0){
                put("@"+ToStr(id));
                run_star();
                put("M=0");
                }
            else{
                throw "error: *= only support -1,0,1";
                }
            }
        void nt(){
            put("@"+ToStr(id));
            run_star();
            put("M=!M");
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
        int level;
    public:
        int get_pos(){return pos;}
        var(){
            pos=esp_ebp.top()++;
            glo["esp"]++;
            level=esp_ebp.size();
            }
        var(const var& x){
            pos=x.pos;
            level=x.level;
            }
        var(const obj& x)=delete;
        var(int x){
            pos=x;
            level=esp_ebp.size();
            }
        void operator=(int x){
            (this->to_obj())=x;
            }
        void operator=(const var& x){
            (this->to_obj())=x.to_obj();
            }
        void operator=(const obj& x){
            (this->to_obj())=x;
            }
        void operator=(string s){
            (this->to_obj())=s;
            }
        /*explicit */operator obj(){
            if(level!=esp_ebp.size())throw "error: outer var can't use in function";
            glo[var_id?"var1":"var2"]=glo["ebp"];
            glo[var_id?"var1":"var2"]+=pos;
            obj ret(glo[var_id?"var1":"var2"]);
            ret.star++;
            var_id=!var_id;
            return ret;
            }
        operator obj()const{
            if(level!=esp_ebp.size())throw "error: outer var can't use in function";
            glo[var_id?"var1":"var2"]=glo["ebp"];
            glo[var_id?"var1":"var2"]+=pos;
            obj ret(glo[var_id?"var1":"var2"]);
            ret.star++;
            var_id=!var_id;
            return ret;
            }
        obj to_obj()const{
            if(level!=esp_ebp.size())throw "error: outer var can't use in function";
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
        void operator&=(int x){
            (this->to_obj())&=x;
            }
        void operator|=(int x){
            (this->to_obj())|=x;
            }
        void operator*=(int x){
            (this->to_obj())*=x;
            }
        void operator+=(const obj &x){
            (this->to_obj())+=x;
            }
        void operator-=(const obj &x){
            (this->to_obj())-=x;
            }
        void operator&=(const obj &x){
            (this->to_obj())&=x;
            }
        void operator|=(const obj &x){
            (this->to_obj())|=x;
            }
        void nt(){
            (this->to_obj()).nt();
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
stack<int>block_stack,loop_esp_stack,if_esp_stack;
set<string>defined_func;
void FuncBegin(string fun,int args=0){
    if(func_args.find(fun)!=func_args.end()) throw "error: multi define function";
    defined_func.insert(fun);
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
    if(func_stack.empty()) throw "error: return without function";
    string fun=func_stack.top();
    glo["tmp"]=glo["ebp"];
    glo["tmp"]-=2;
    mem[glo["tmp"]]=ret;
    put("@Func_"+fun+"_return");
    put("0;JMP");
    }
void FuncEnd(){
    if(func_stack.empty()) throw "error: end without function";
    string fun=func_stack.top();
    func_stack.pop();
    put("(Func_"+fun+"_return)");
    pop();
    glo["esp"]-=2;
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
set<string>called_func;
template<typename... Args>
var FuncCall(string fun, Args... args){
    called_func.insert(fun);
    string rng_string;
    for(int i=0;i<8;i++)
        rng_string+=(rand()>>2)%26+'A';
    mem[glo["esp"]]=("Func_Call_"+rng_string+"_after");
    glo["esp"]+=2;//return value
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
    if_esp_stack.push(esp_ebp.top());
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
    if(if_stack.empty()) throw "error: end without if";
    int d=esp_ebp.top()-if_esp_stack.top();
    if_esp_stack.pop();
    if(d)glo["esp"]-=d;
    esp_ebp.top()-=d;
    string rng_string=if_stack.top();
    put("(if_"+rng_string+"_end)");
    if_stack.pop();
    }
stack<string>loop_stack;
void LoopBegin(){
    block_stack.push(2);
    loop_esp_stack.push(esp_ebp.top());
    string rng_string;
    for(int i=0;i<8;i++)
        rng_string+=(rand()>>2)%26+'A';
    loop_stack.push(rng_string);
    put("(loop_"+rng_string+"_begin)");
    }
void LoopBreak(){
    if(loop_stack.empty()) throw "error: break without loop";
    string rng_string=loop_stack.top();
    int d=esp_ebp.top()-loop_esp_stack.top();
    if(d)glo["esp"]-=d;
    put("@loop_"+rng_string+"_end");
    put("0;JMP");
    }
void LoopEnd(){
    string rng_string=loop_stack.top();
    loop_stack.pop();
    int d=esp_ebp.top()-loop_esp_stack.top();
    loop_esp_stack.pop();
    if(d)glo["esp"]-=d;
    esp_ebp.top()-=d;
    put("@loop_"+rng_string+"_begin");
    put("0;JMP");
    put("(loop_"+rng_string+"_end)");
    }
void BlockEnd(){
    if(block_stack.empty()) throw "error: end without block";
    int top=block_stack.top();
    block_stack.pop();
    if(top==0)FuncEnd();
    else if(top==1)IfEnd();
    else if(top==2)LoopEnd();
    }
bool Setuped=false;
void Setup(){
    if(Setuped)throw "error: multi setup";
    Setuped=true;
    objcnt=FlagTop;
    glo["ebp"]=StackTop;
    glo["esp"]=glo["ebp"];
    esp_ebp.push(0);
    }
void StackCheck(){
    for(string s:called_func)
        if(defined_func.find(s)==defined_func.end())
            throw ("error: call undefined function '"+s+"'").c_str();
    if(!block_stack.empty()) throw "error: exit without empty stack";
    }
vector<string>ve;
//W=32*16
//H=256
#define Begin int main(){try{Setup();

#define CallFunction FuncCall
#define Call0(a) FuncCall(#a)
#define Call1(a,b) FuncCall(#a,b)
#define Call2(a,b,c) FuncCall(#a,b,c)
#define Call3(a,b,c,d) FuncCall(#a,b,c,d)
#define Call4(a,b,c,d,e) FuncCall(#a,b,c,d,e)
#define Call5(a,b,c,d,e,f) FuncCall(#a,b,c,d,e,f)
#define Call6(a,b,c,d,e,f,g) FuncCall(#a,b,c,d,e,f,g)
#define GET_MACRO2(_1,_2,_3,_4,_5,_6,_7,NAME,...) NAME
#define Call(...) GET_MACRO2(__VA_ARGS__, Call6, Call5, Call4, Call3, Call2, Call1, Call0)(__VA_ARGS__)
#define Loop LoopBegin();{
#define If(a,b,c) IfBegin((a),#b,(c));{
#define Function(a,b) FuncBegin((a),(b));{
#define Func0(a) FuncBegin(#a,0);{
#define Func1(a,b) FuncBegin(#a,1);{var b(0);
#define Func2(a,b,c) FuncBegin(#a,2);{var b(0),c(1);
#define Func3(a,b,c,d) FuncBegin(#a,3);{var b(0),c(1),d(2);
#define Func4(a,b,c,d,e) FuncBegin(#a,4);{var b(0),c(1),d(2),e(3);
#define Func5(a,b,c,d,e,f) FuncBegin(#a,5);{var b(0),c(1),d(2),e(3),f(4);
#define Func6(a,b,c,d,e,f,g) FuncBegin(#a,6);{var b(0),c(1),d(2),e(3),f(4),g(5);
#define GET_MACRO(_1,_2,_3,_4,_5,_6,_7,NAME,...) NAME
#define Func(...) GET_MACRO(__VA_ARGS__, Func6, Func5, Func4, Func3, Func2, Func1, Func0)(__VA_ARGS__)
#define Stop while_true();
#define End }BlockEnd();
#define Return(a) FuncReturn((a))
#define Break LoopBreak();
#define Finish while_true();StackCheck();}catch(char const* error){puts(error);return 0;}optimize(2);return 0;}
#define Var var
#define Mem mem
#define Global glo

const int ScreenBuffer=0x0F00;
const int KBD=0x6000;
Begin
    Func(clean)
        Var j;
        j=ScreenBuffer;
        Loop
            mem[j]=0;
            j++;
            If(j,==,ScreenBuffer+0x2000)
                Break;
            End
        End
    End
    Func(set_screen)
        Var i,j;
        i=0x4000;
        j=ScreenBuffer;
        Loop
            mem[i]=mem[j];
            i++;
            j++;
            If(i,==,0x6000)
                Break;
            End
        End
    End
    for(int i=0;i<16;i++)
        Mem[i]=-(1<<i);
    Mem[16]=-1;
    for(int i=0;i<15;i++)
        Mem[i+16]=(1<<i+1)-1;
    Mem[31]=-1;
    for(int i=0;i<32;i++)
        Mem[(i<<4)+32]=i;
    Func(draw_rect,x1,x2,y1,y2,col)
        If(x1,>,x2)
            Return(0);
        End
        If(y1,>,y2)
            Return(0);
        End
        Var x1_high,x1_low,x2_high,x2_low;
        x1_low=x1;
        x1_low&=15;
        x1_low=Mem[x1_low];
        x1_high=x1;
        x1_high&=-16;
        x1_high+=32;
        x1_high=Mem[x1_high];
        x2_low=x2;
        x2_low&=15;
        x2_low+=16;
        x2_low=Mem[x2_low];
        x2_high=x2;
        x2_high&=-16;
        x2_high+=32;
        x2_high=Mem[x2_high];
        If(x1_high,==,x2_high)
            x1_low&=x2_low;
            x2_low=x1_low;
        End
        If(col,==,0)
            x1_low.nt();
            x2_low.nt();
        End
        Var line_begin,y32;
        line_begin=ScreenBuffer;
        y32=y1;
        y32+=y32;//2
        y32+=y32;//4
        y32+=y32;//8
        y32+=y32;//16
        y32+=y32;//32
        line_begin+=y32;
        Loop
            Var pos,i;
            If(col,!=,0)
                pos=line_begin;
                pos+=x2_high;
                mem[pos]|=x2_low;
                pos=line_begin;
                pos+=x1_high;
                mem[pos]|=x1_low;
                i=x1_high;
                Loop
                    pos++;
                    i++;
                    If(i,>=,x2_high)
                        Break
                    End
                    mem[pos]|=-1;
                End
            End
            If(col,==,0)
                pos=line_begin;
                pos+=x2_high;
                mem[pos]&=x2_low;
                pos=line_begin;
                pos+=x1_high;
                mem[pos]&=x1_low;
                i=x1_high;
                Loop
                    pos++;
                    i++;
                    If(i,>=,x2_high)
                        Break
                    End
                    mem[pos]=0;
                End
            End
            line_begin+=32;
            y1++;
            If(y1,>,y2)
                Break
            End
        End
    End
    Func(draw_line,x,y1,y2)
        Call(draw_rect,x,x,y1,y2,0);
    End
    Func(WaitEnter)
        Loop
            If(mem[KBD],==,128)
                Break
            End
        End
    End
    Func(draw_num,n,x,y)
        Var pos;
        pos=0x0600;
        pos+=n;
        pos=mem[pos];
        Loop
            Var a,b,c;
            a=mem[pos];
            If(a,==,-1)
                Break;
            End
            pos++;
            b=mem[pos];
            pos++;
            c=mem[pos];
            pos++;
            a+=x;
            b+=y;
            c+=y;
            Call(draw_line,a,b,c);
        End
    End
    Func(GameOver,score)
        Call(set_gameover_pic);
        Call(clean);
        Call(draw_rect,0,511,0,255,1);
        Var pos;
        pos=0x2F00;
        Loop
            Var a,b,c;
            a=mem[pos];
            If(a,==,-1)
                Break;
            End
            pos++;
            b=mem[pos];
            pos++;
            c=mem[pos];
            pos++;
            Call(draw_line,a,b,c);
        End
        Var s0,s1,s2;
        s0=0;
        s1=0;
        s2=0;
        Loop
            If(score,==,0)
                Break
            End
            score--;
            s0++;
            If(s0,==,10)
                s0=0;
                s1++;
                If(s1,==,100)
                    s1=0;
                    s2++;
                End
            End
        End
        Var x;
        x=223;
        Call(draw_num,s2,x,200);
        x+=22;
        Call(draw_num,s1,x,200);
        x+=22;
        Call(draw_num,s0,x,200);
        Call(set_screen);
        Call(WaitEnter);
    End
    Func(Title)
        Call(set_title_pic);
        Call(clean);
        Call(draw_rect,0,511,0,255,1);
        Var pos;
        pos=0x2F00;
        Loop
            Var a,b,c;
            a=mem[pos];
            If(a,==,-1)
                Break;
            End
            pos++;
            b=mem[pos];
            pos++;
            c=mem[pos];
            pos++;
            Call(draw_line,a,b,c);
        End
        Call(set_screen);
        Call(WaitEnter);
    End

    Call(set_num_pic);
    Call(Title);

    Loop
        Global["score"]=0;
        Global["rand3"]=mem[KBD];
        Global["rand3"]-=130;
        Global["rand3"]+=Global["rand3"];
        Global["rand3"]+=Global["rand3"];
        Global["rand3"]+=Global["rand3"];
        Global["rand3"]+=Global["rand3"];
        Global["rand3"]+=Global["rand3"];
        Global["rand1"]+=Global["rand3"];
        Global["rand1"]+=7122;
        Global["rand2"]+=Global["rand3"];
        Global["rand2"]+=7777;
        Var vx,vy,len;
        Var mx,my;
        mx=16*7;
        my=16*7;
        const int ar=0x0400,snake_len=5;
        vx=16;
        vy=0;
        len=snake_len;
        for(int i=0;i<snake_len;i++){
            mem[ar+i*2]=16*(snake_len-i-1);
            mem[ar+i*2+1]=0;
            }
        Loop
            Call(clean);
            If(Mem[KBD],==,130)
                Var tmp;
                tmp=mem[ar];
                tmp-=mem[ar+2];
                If(tmp,!=,16)
                    vx=-16;
                    vy=0;
                End
            End
            If(Mem[KBD],==,131)
                Var tmp;
                tmp=mem[ar+1];
                tmp-=mem[ar+3];
                If(tmp,!=,16)
                    vx=0;
                    vy=-16;
                End
            End
            If(Mem[KBD],==,132)
                Var tmp;
                tmp=mem[ar];
                tmp-=mem[ar+2];
                If(tmp,!=,-16)
                    vx=16;
                    vy=0;
                End
            End
            If(Mem[KBD],==,133)
                Var tmp;
                tmp=mem[ar+1];
                tmp-=mem[ar+3];
                If(tmp,!=,-16)
                    vx=0;
                    vy=16;
                End
            End
            Var i,j;
            i=ar;
            i+=len;
            i+=len;
            j=i;
            j-=2;
            Loop
                i--;j--;
                mem[i]=mem[j];
                i--;j--;
                mem[i]=mem[j];
                If(i,==,ar+2)
                    Break
                End
            End
            mem[ar]+=vx;
            mem[ar+1]+=vy;
            If(mem[ar],<,0)
                Break
            End
            If(mem[ar+1],<,0)
                Break
            End
            If(mem[ar],>=,512)
                Break
            End
            If(mem[ar+1],>=,256)
                Break
            End
            i=ar;
            i+=len;
            i+=len;
            Var gameover;
            gameover=0;
            Loop
                Var x,y,xx,yy;
                i--;
                y=mem[i];
                yy=y;
                yy+=15;
                i--;
                x=mem[i];
                xx=x;
                xx+=15;
                Call(draw_rect,x,xx,y,yy,1);
                If(i,==,ar)
                    Break
                End
                If(mem[ar],==,x)
                    If(mem[ar+1],==,y)
                        gameover=1;
                        Break
                    End
                End
            End
            If(gameover,==,1)
                Break
            End
            Var x,y,xx,yy;
            y=my;
            yy=y;
            yy+=11;
            y+=4;
            x=mx;
            xx=x;
            xx+=11;
            x+=4;
            If(mx,==,mem[ar])
                If(my,==,mem[ar+1])
                    len++;
                    Global["score"]++;
                    Loop
                        mx+=21525;
                        mx+=Global["rand1"];
                        my+=6732;
                        my+=Global["rand2"];
                        mx&=511^15;
                        my&=255^15;
                        Var ok;
                        ok=1;
                        i=ar;
                        i+=len;
                        i+=len;
                        j=i;
                        j--;
                        Var k;
                        Loop
                            i--;j--;
                            If(mem[i],==,my)
                                If(mem[j],==,mx)
                                    ok=0;
                                    Break
                                End
                            End
                            i--;j--;
                            If(i,==,ar+2)
                                Break
                            End
                        End
                        If(ok,==,1)
                            Break
                        End
                    End
                End
            End
            Call(draw_rect,x,xx,y,yy,1);
            Call(set_screen);
        End
        Call(GameOver,Global["score"]);
    End
    Func(set_title_pic)
        mem[12032]=175;mem[12033]=75;mem[12034]=76;
        mem[12035]=176;mem[12036]=74;mem[12037]=76;
        mem[12038]=176;mem[12039]=150;mem[12040]=154;
        mem[12041]=177;mem[12042]=74;mem[12043]=76;
        mem[12044]=177;mem[12045]=148;mem[12046]=154;
        mem[12047]=178;mem[12048]=73;mem[12049]=76;
        mem[12050]=178;mem[12051]=148;mem[12052]=150;
        mem[12053]=178;mem[12054]=152;mem[12055]=152;
        mem[12056]=179;mem[12057]=72;mem[12058]=75;
        mem[12059]=179;mem[12060]=148;mem[12061]=148;
        mem[12062]=179;mem[12063]=152;mem[12064]=152;
        mem[12065]=180;mem[12066]=71;mem[12067]=74;
        mem[12068]=180;mem[12069]=148;mem[12070]=148;
        mem[12071]=180;mem[12072]=150;mem[12073]=152;
        mem[12074]=181;mem[12075]=70;mem[12076]=74;
        mem[12077]=181;mem[12078]=148;mem[12079]=151;
        mem[12080]=182;mem[12081]=70;mem[12082]=73;
        mem[12083]=182;mem[12084]=149;mem[12085]=150;
        mem[12086]=183;mem[12087]=69;mem[12088]=72;
        mem[12089]=183;mem[12090]=76;mem[12091]=77;
        mem[12092]=183;mem[12093]=97;mem[12094]=97;
        mem[12095]=183;mem[12096]=102;mem[12097]=103;
        mem[12098]=183;mem[12099]=152;mem[12100]=153;
        mem[12101]=184;mem[12102]=68;mem[12103]=71;
        mem[12104]=184;mem[12105]=76;mem[12106]=77;
        mem[12107]=184;mem[12108]=81;mem[12109]=98;
        mem[12110]=184;mem[12111]=101;mem[12112]=103;
        mem[12113]=184;mem[12114]=148;mem[12115]=153;
        mem[12116]=185;mem[12117]=67;mem[12118]=70;
        mem[12119]=185;mem[12120]=75;mem[12121]=77;
        mem[12122]=185;mem[12123]=81;mem[12124]=98;
        mem[12125]=185;mem[12126]=100;mem[12127]=103;
        mem[12128]=185;mem[12129]=148;mem[12130]=151;
        mem[12131]=186;mem[12132]=66;mem[12133]=69;
        mem[12134]=186;mem[12135]=75;mem[12136]=77;
        mem[12137]=186;mem[12138]=81;mem[12139]=103;
        mem[12140]=186;mem[12141]=149;mem[12142]=150;
        mem[12143]=187;mem[12144]=65;mem[12145]=71;
        mem[12146]=187;mem[12147]=75;mem[12148]=77;
        mem[12149]=187;mem[12150]=81;mem[12151]=102;
        mem[12152]=187;mem[12153]=148;mem[12154]=149;
        mem[12155]=188;mem[12156]=64;mem[12157]=68;
        mem[12158]=188;mem[12159]=70;mem[12160]=71;
        mem[12161]=188;mem[12162]=75;mem[12163]=76;
        mem[12164]=188;mem[12165]=81;mem[12166]=82;
        mem[12167]=188;mem[12168]=97;mem[12169]=101;
        mem[12170]=188;mem[12171]=148;mem[12172]=149;
        mem[12173]=189;mem[12174]=63;mem[12175]=67;
        mem[12176]=189;mem[12177]=69;mem[12178]=71;
        mem[12179]=189;mem[12180]=74;mem[12181]=76;
        mem[12182]=189;mem[12183]=81;mem[12184]=82;
        mem[12185]=189;mem[12186]=86;mem[12187]=87;
        mem[12188]=189;mem[12189]=91;mem[12190]=92;
        mem[12191]=189;mem[12192]=96;mem[12193]=100;
        mem[12194]=189;mem[12195]=149;mem[12196]=149;
        mem[12197]=190;mem[12198]=61;mem[12199]=66;
        mem[12200]=190;mem[12201]=69;mem[12202]=71;
        mem[12203]=190;mem[12204]=74;mem[12205]=76;
        mem[12206]=190;mem[12207]=81;mem[12208]=82;
        mem[12209]=190;mem[12210]=86;mem[12211]=87;
        mem[12212]=190;mem[12213]=91;mem[12214]=92;
        mem[12215]=190;mem[12216]=96;mem[12217]=99;
        mem[12218]=190;mem[12219]=149;mem[12220]=153;
        mem[12221]=191;mem[12222]=60;mem[12223]=65;
        mem[12224]=191;mem[12225]=69;mem[12226]=71;
        mem[12227]=191;mem[12228]=74;mem[12229]=76;
        mem[12230]=191;mem[12231]=81;mem[12232]=82;
        mem[12233]=191;mem[12234]=86;mem[12235]=87;
        mem[12236]=191;mem[12237]=91;mem[12238]=92;
        mem[12239]=191;mem[12240]=96;mem[12241]=98;
        mem[12242]=191;mem[12243]=148;mem[12244]=153;
        mem[12245]=192;mem[12246]=60;mem[12247]=64;
        mem[12248]=192;mem[12249]=68;mem[12250]=70;
        mem[12251]=192;mem[12252]=74;mem[12253]=75;
        mem[12254]=192;mem[12255]=80;mem[12256]=82;
        mem[12257]=192;mem[12258]=85;mem[12259]=87;
        mem[12260]=192;mem[12261]=90;mem[12262]=92;
        mem[12263]=192;mem[12264]=96;mem[12265]=97;
        mem[12266]=192;mem[12267]=148;mem[12268]=148;
        mem[12269]=192;mem[12270]=150;mem[12271]=151;
        mem[12272]=192;mem[12273]=153;mem[12274]=153;
        mem[12275]=193;mem[12276]=60;mem[12277]=64;
        mem[12278]=193;mem[12279]=68;mem[12280]=70;
        mem[12281]=193;mem[12282]=73;mem[12283]=75;
        mem[12284]=193;mem[12285]=80;mem[12286]=82;
        mem[12287]=193;mem[12288]=85;mem[12289]=87;
        mem[12290]=193;mem[12291]=90;mem[12292]=92;
        mem[12293]=193;mem[12294]=96;mem[12295]=97;
        mem[12296]=193;mem[12297]=148;mem[12298]=148;
        mem[12299]=193;mem[12300]=150;mem[12301]=151;
        mem[12302]=193;mem[12303]=153;mem[12304]=153;
        mem[12305]=194;mem[12306]=61;mem[12307]=64;
        mem[12308]=194;mem[12309]=68;mem[12310]=70;
        mem[12311]=194;mem[12312]=73;mem[12313]=75;
        mem[12314]=194;mem[12315]=80;mem[12316]=81;
        mem[12317]=194;mem[12318]=85;mem[12319]=87;
        mem[12320]=194;mem[12321]=90;mem[12322]=92;
        mem[12323]=194;mem[12324]=96;mem[12325]=97;
        mem[12326]=194;mem[12327]=148;mem[12328]=150;
        mem[12329]=194;mem[12330]=152;mem[12331]=153;
        mem[12332]=195;mem[12333]=62;mem[12334]=64;
        mem[12335]=195;mem[12336]=67;mem[12337]=69;
        mem[12338]=195;mem[12339]=73;mem[12340]=74;
        mem[12341]=195;mem[12342]=79;mem[12343]=81;
        mem[12344]=195;mem[12345]=85;mem[12346]=87;
        mem[12347]=195;mem[12348]=90;mem[12349]=91;
        mem[12350]=195;mem[12351]=95;mem[12352]=97;
        mem[12353]=195;mem[12354]=148;mem[12355]=149;
        mem[12356]=195;mem[12357]=152;mem[12358]=153;
        mem[12359]=196;mem[12360]=63;mem[12361]=65;
        mem[12362]=196;mem[12363]=67;mem[12364]=69;
        mem[12365]=196;mem[12366]=73;mem[12367]=74;
        mem[12368]=196;mem[12369]=78;mem[12370]=81;
        mem[12371]=196;mem[12372]=85;mem[12373]=86;
        mem[12374]=196;mem[12375]=89;mem[12376]=91;
        mem[12377]=196;mem[12378]=95;mem[12379]=97;
        mem[12380]=196;mem[12381]=152;mem[12382]=152;
        mem[12383]=197;mem[12384]=63;mem[12385]=65;
        mem[12386]=197;mem[12387]=67;mem[12388]=69;
        mem[12389]=197;mem[12390]=72;mem[12391]=74;
        mem[12392]=197;mem[12393]=76;mem[12394]=81;
        mem[12395]=197;mem[12396]=85;mem[12397]=86;
        mem[12398]=197;mem[12399]=89;mem[12400]=91;
        mem[12401]=197;mem[12402]=95;mem[12403]=97;
        mem[12404]=197;mem[12405]=150;mem[12406]=150;
        mem[12407]=198;mem[12408]=64;mem[12409]=66;
        mem[12410]=198;mem[12411]=68;mem[12412]=69;
        mem[12413]=198;mem[12414]=72;mem[12415]=81;
        mem[12416]=198;mem[12417]=85;mem[12418]=86;
        mem[12419]=198;mem[12420]=89;mem[12421]=91;
        mem[12422]=198;mem[12423]=95;mem[12424]=96;
        mem[12425]=198;mem[12426]=99;mem[12427]=100;
        mem[12428]=198;mem[12429]=149;mem[12430]=150;
        mem[12431]=198;mem[12432]=153;mem[12433]=153;
        mem[12434]=199;mem[12435]=64;mem[12436]=66;
        mem[12437]=199;mem[12438]=72;mem[12439]=80;
        mem[12440]=199;mem[12441]=90;mem[12442]=91;
        mem[12443]=199;mem[12444]=95;mem[12445]=96;
        mem[12446]=199;mem[12447]=99;mem[12448]=100;
        mem[12449]=199;mem[12450]=148;mem[12451]=151;
        mem[12452]=199;mem[12453]=153;mem[12454]=153;
        mem[12455]=200;mem[12456]=64;mem[12457]=66;
        mem[12458]=200;mem[12459]=72;mem[12460]=77;
        mem[12461]=200;mem[12462]=79;mem[12463]=81;
        mem[12464]=200;mem[12465]=95;mem[12466]=97;
        mem[12467]=200;mem[12468]=99;mem[12469]=101;
        mem[12470]=200;mem[12471]=148;mem[12472]=148;
        mem[12473]=200;mem[12474]=150;mem[12475]=153;
        mem[12476]=201;mem[12477]=65;mem[12478]=67;
        mem[12479]=201;mem[12480]=71;mem[12481]=76;
        mem[12482]=201;mem[12483]=79;mem[12484]=101;
        mem[12485]=201;mem[12486]=148;mem[12487]=148;
        mem[12488]=201;mem[12489]=151;mem[12490]=153;
        mem[12491]=202;mem[12492]=65;mem[12493]=67;
        mem[12494]=202;mem[12495]=71;mem[12496]=75;
        mem[12497]=202;mem[12498]=79;mem[12499]=102;
        mem[12500]=202;mem[12501]=148;mem[12502]=148;
        mem[12503]=202;mem[12504]=151;mem[12505]=152;
        mem[12506]=203;mem[12507]=65;mem[12508]=67;
        mem[12509]=203;mem[12510]=72;mem[12511]=74;
        mem[12512]=203;mem[12513]=79;mem[12514]=102;
        mem[12515]=204;mem[12516]=66;mem[12517]=68;
        mem[12518]=204;mem[12519]=72;mem[12520]=73;
        mem[12521]=204;mem[12522]=80;mem[12523]=98;
        mem[12524]=204;mem[12525]=100;mem[12526]=103;
        mem[12527]=204;mem[12528]=150;mem[12529]=150;
        mem[12530]=205;mem[12531]=66;mem[12532]=68;
        mem[12533]=205;mem[12534]=98;mem[12535]=98;
        mem[12536]=205;mem[12537]=101;mem[12538]=103;
        mem[12539]=205;mem[12540]=149;mem[12541]=150;
        mem[12542]=205;mem[12543]=153;mem[12544]=153;
        mem[12545]=206;mem[12546]=66;mem[12547]=68;
        mem[12548]=206;mem[12549]=101;mem[12550]=103;
        mem[12551]=206;mem[12552]=148;mem[12553]=151;
        mem[12554]=206;mem[12555]=153;mem[12556]=153;
        mem[12557]=207;mem[12558]=67;mem[12559]=69;
        mem[12560]=207;mem[12561]=103;mem[12562]=103;
        mem[12563]=207;mem[12564]=148;mem[12565]=148;
        mem[12566]=207;mem[12567]=150;mem[12568]=153;
        mem[12569]=208;mem[12570]=67;mem[12571]=69;
        mem[12572]=208;mem[12573]=148;mem[12574]=148;
        mem[12575]=208;mem[12576]=151;mem[12577]=153;
        mem[12578]=209;mem[12579]=67;mem[12580]=70;
        mem[12581]=209;mem[12582]=148;mem[12583]=148;
        mem[12584]=209;mem[12585]=151;mem[12586]=152;
        mem[12587]=210;mem[12588]=68;mem[12589]=70;
        mem[12590]=211;mem[12591]=68;mem[12592]=70;
        mem[12593]=212;mem[12594]=68;mem[12595]=70;
        mem[12596]=218;mem[12597]=149;mem[12598]=153;
        mem[12599]=219;mem[12600]=148;mem[12601]=153;
        mem[12602]=220;mem[12603]=148;mem[12604]=148;
        mem[12605]=220;mem[12606]=150;mem[12607]=151;
        mem[12608]=220;mem[12609]=153;mem[12610]=153;
        mem[12611]=221;mem[12612]=81;mem[12613]=83;
        mem[12614]=221;mem[12615]=148;mem[12616]=148;
        mem[12617]=221;mem[12618]=150;mem[12619]=151;
        mem[12620]=221;mem[12621]=153;mem[12622]=153;
        mem[12623]=222;mem[12624]=80;mem[12625]=83;
        mem[12626]=222;mem[12627]=148;mem[12628]=150;
        mem[12629]=222;mem[12630]=152;mem[12631]=153;
        mem[12632]=223;mem[12633]=79;mem[12634]=83;
        mem[12635]=223;mem[12636]=148;mem[12637]=149;
        mem[12638]=223;mem[12639]=152;mem[12640]=153;
        mem[12641]=224;mem[12642]=78;mem[12643]=82;
        mem[12644]=224;mem[12645]=152;mem[12646]=152;
        mem[12647]=225;mem[12648]=77;mem[12649]=81;
        mem[12650]=225;mem[12651]=148;mem[12652]=148;
        mem[12653]=225;mem[12654]=150;mem[12655]=153;
        mem[12656]=226;mem[12657]=76;mem[12658]=80;
        mem[12659]=226;mem[12660]=148;mem[12661]=153;
        mem[12662]=227;mem[12663]=75;mem[12664]=79;
        mem[12665]=227;mem[12666]=148;mem[12667]=151;
        mem[12668]=228;mem[12669]=74;mem[12670]=78;
        mem[12671]=228;mem[12672]=148;mem[12673]=149;
        mem[12674]=228;mem[12675]=151;mem[12676]=152;
        mem[12677]=229;mem[12678]=73;mem[12679]=77;
        mem[12680]=229;mem[12681]=148;mem[12682]=153;
        mem[12683]=230;mem[12684]=71;mem[12685]=76;
        mem[12686]=230;mem[12687]=148;mem[12688]=153;
        mem[12689]=231;mem[12690]=70;mem[12691]=75;
        mem[12692]=231;mem[12693]=77;mem[12694]=78;
        mem[12695]=231;mem[12696]=102;mem[12697]=102;
        mem[12698]=231;mem[12699]=153;mem[12700]=153;
        mem[12701]=232;mem[12702]=69;mem[12703]=73;
        mem[12704]=232;mem[12705]=76;mem[12706]=78;
        mem[12707]=232;mem[12708]=98;mem[12709]=103;
        mem[12710]=232;mem[12711]=149;mem[12712]=149;
        mem[12713]=233;mem[12714]=68;mem[12715]=72;
        mem[12716]=233;mem[12717]=76;mem[12718]=78;
        mem[12719]=233;mem[12720]=80;mem[12721]=103;
        mem[12722]=233;mem[12723]=149;mem[12724]=153;
        mem[12725]=234;mem[12726]=67;mem[12727]=71;
        mem[12728]=234;mem[12729]=76;mem[12730]=103;
        mem[12731]=234;mem[12732]=146;mem[12733]=153;
        mem[12734]=235;mem[12735]=65;mem[12736]=70;
        mem[12737]=235;mem[12738]=76;mem[12739]=102;
        mem[12740]=235;mem[12741]=146;mem[12742]=149;
        mem[12743]=235;mem[12744]=153;mem[12745]=153;
        mem[12746]=236;mem[12747]=64;mem[12748]=69;
        mem[12749]=236;mem[12750]=75;mem[12751]=77;
        mem[12752]=236;mem[12753]=80;mem[12754]=94;
        mem[12755]=236;mem[12756]=99;mem[12757]=102;
        mem[12758]=236;mem[12759]=146;mem[12760]=146;
        mem[12761]=236;mem[12762]=148;mem[12763]=148;
        mem[12764]=236;mem[12765]=152;mem[12766]=153;
        mem[12767]=237;mem[12768]=63;mem[12769]=68;
        mem[12770]=237;mem[12771]=75;mem[12772]=77;
        mem[12773]=237;mem[12774]=81;mem[12775]=83;
        mem[12776]=237;mem[12777]=88;mem[12778]=91;
        mem[12779]=237;mem[12780]=98;mem[12781]=101;
        mem[12782]=237;mem[12783]=148;mem[12784]=148;
        mem[12785]=237;mem[12786]=152;mem[12787]=153;
        mem[12788]=238;mem[12789]=61;mem[12790]=66;
        mem[12791]=238;mem[12792]=68;mem[12793]=69;
        mem[12794]=238;mem[12795]=75;mem[12796]=77;
        mem[12797]=238;mem[12798]=81;mem[12799]=83;
        mem[12800]=238;mem[12801]=87;mem[12802]=91;
        mem[12803]=238;mem[12804]=98;mem[12805]=100;
        mem[12806]=238;mem[12807]=152;mem[12808]=152;
        mem[12809]=239;mem[12810]=60;mem[12811]=65;
        mem[12812]=239;mem[12813]=67;mem[12814]=70;
        mem[12815]=239;mem[12816]=75;mem[12817]=76;
        mem[12818]=239;mem[12819]=81;mem[12820]=82;
        mem[12821]=239;mem[12822]=87;mem[12823]=92;
        mem[12824]=239;mem[12825]=97;mem[12826]=100;
        mem[12827]=239;mem[12828]=149;mem[12829]=153;
        mem[12830]=240;mem[12831]=60;mem[12832]=64;
        mem[12833]=240;mem[12834]=67;mem[12835]=71;
        mem[12836]=240;mem[12837]=74;mem[12838]=76;
        mem[12839]=240;mem[12840]=80;mem[12841]=82;
        mem[12842]=240;mem[12843]=87;mem[12844]=88;
        mem[12845]=240;mem[12846]=90;mem[12847]=92;
        mem[12848]=240;mem[12849]=97;mem[12850]=99;
        mem[12851]=240;mem[12852]=148;mem[12853]=153;
        mem[12854]=241;mem[12855]=60;mem[12856]=63;
        mem[12857]=241;mem[12858]=68;mem[12859]=72;
        mem[12860]=241;mem[12861]=74;mem[12862]=76;
        mem[12863]=241;mem[12864]=80;mem[12865]=82;
        mem[12866]=241;mem[12867]=86;mem[12868]=88;
        mem[12869]=241;mem[12870]=90;mem[12871]=93;
        mem[12872]=241;mem[12873]=96;mem[12874]=98;
        mem[12875]=241;mem[12876]=148;mem[12877]=148;
        mem[12878]=241;mem[12879]=150;mem[12880]=151;
        mem[12881]=241;mem[12882]=153;mem[12883]=153;
        mem[12884]=242;mem[12885]=60;mem[12886]=64;
        mem[12887]=242;mem[12888]=69;mem[12889]=72;
        mem[12890]=242;mem[12891]=74;mem[12892]=76;
        mem[12893]=242;mem[12894]=80;mem[12895]=82;
        mem[12896]=242;mem[12897]=86;mem[12898]=88;
        mem[12899]=242;mem[12900]=91;mem[12901]=93;
        mem[12902]=242;mem[12903]=96;mem[12904]=98;
        mem[12905]=242;mem[12906]=148;mem[12907]=148;
        mem[12908]=242;mem[12909]=150;mem[12910]=151;
        mem[12911]=242;mem[12912]=153;mem[12913]=153;
        mem[12914]=243;mem[12915]=62;mem[12916]=64;
        mem[12917]=243;mem[12918]=70;mem[12919]=75;
        mem[12920]=243;mem[12921]=80;mem[12922]=81;
        mem[12923]=243;mem[12924]=86;mem[12925]=87;
        mem[12926]=243;mem[12927]=91;mem[12928]=94;
        mem[12929]=243;mem[12930]=96;mem[12931]=97;
        mem[12932]=243;mem[12933]=148;mem[12934]=150;
        mem[12935]=243;mem[12936]=152;mem[12937]=153;
        mem[12938]=244;mem[12939]=62;mem[12940]=65;
        mem[12941]=244;mem[12942]=73;mem[12943]=75;
        mem[12944]=244;mem[12945]=79;mem[12946]=81;
        mem[12947]=244;mem[12948]=86;mem[12949]=87;
        mem[12950]=244;mem[12951]=92;mem[12952]=94;
        mem[12953]=244;mem[12954]=148;mem[12955]=149;
        mem[12956]=244;mem[12957]=152;mem[12958]=153;
        mem[12959]=245;mem[12960]=63;mem[12961]=66;
        mem[12962]=245;mem[12963]=73;mem[12964]=75;
        mem[12965]=245;mem[12966]=79;mem[12967]=81;
        mem[12968]=245;mem[12969]=85;mem[12970]=87;
        mem[12971]=245;mem[12972]=92;mem[12973]=95;
        mem[12974]=245;mem[12975]=152;mem[12976]=152;
        mem[12977]=246;mem[12978]=64;mem[12979]=66;
        mem[12980]=246;mem[12981]=73;mem[12982]=74;
        mem[12983]=246;mem[12984]=79;mem[12985]=87;
        mem[12986]=246;mem[12987]=92;mem[12988]=95;
        mem[12989]=246;mem[12990]=152;mem[12991]=153;
        mem[12992]=247;mem[12993]=64;mem[12994]=67;
        mem[12995]=247;mem[12996]=72;mem[12997]=74;
        mem[12998]=247;mem[12999]=76;mem[13000]=87;
        mem[13001]=247;mem[13002]=92;mem[13003]=96;
        mem[13004]=247;mem[13005]=148;mem[13006]=153;
        mem[13007]=248;mem[13008]=65;mem[13009]=68;
        mem[13010]=248;mem[13011]=72;mem[13012]=87;
        mem[13013]=248;mem[13014]=91;mem[13015]=96;
        mem[13016]=248;mem[13017]=148;mem[13018]=151;
        mem[13019]=249;mem[13020]=66;mem[13021]=68;
        mem[13022]=249;mem[13023]=72;mem[13024]=85;
        mem[13025]=249;mem[13026]=90;mem[13027]=92;
        mem[13028]=249;mem[13029]=94;mem[13030]=97;
        mem[13031]=249;mem[13032]=149;mem[13033]=150;
        mem[13034]=250;mem[13035]=66;mem[13036]=69;
        mem[13037]=250;mem[13038]=72;mem[13039]=79;
        mem[13040]=250;mem[13041]=90;mem[13042]=92;
        mem[13043]=250;mem[13044]=95;mem[13045]=97;
        mem[13046]=250;mem[13047]=148;mem[13048]=149;
        mem[13049]=251;mem[13050]=67;mem[13051]=70;
        mem[13052]=251;mem[13053]=72;mem[13054]=75;
        mem[13055]=251;mem[13056]=89;mem[13057]=91;
        mem[13058]=251;mem[13059]=95;mem[13060]=98;
        mem[13061]=251;mem[13062]=148;mem[13063]=149;
        mem[13064]=252;mem[13065]=68;mem[13066]=70;
        mem[13067]=252;mem[13068]=88;mem[13069]=91;
        mem[13070]=252;mem[13071]=96;mem[13072]=98;
        mem[13073]=252;mem[13074]=149;mem[13075]=149;
        mem[13076]=253;mem[13077]=68;mem[13078]=71;
        mem[13079]=253;mem[13080]=88;mem[13081]=90;
        mem[13082]=253;mem[13083]=96;mem[13084]=99;
        mem[13085]=254;mem[13086]=69;mem[13087]=71;
        mem[13088]=254;mem[13089]=87;mem[13090]=90;
        mem[13091]=254;mem[13092]=97;mem[13093]=99;
        mem[13094]=255;mem[13095]=69;mem[13096]=72;
        mem[13097]=255;mem[13098]=87;mem[13099]=89;
        mem[13100]=255;mem[13101]=97;mem[13102]=100;
        mem[13103]=256;mem[13104]=70;mem[13105]=72;
        mem[13106]=256;mem[13107]=87;mem[13108]=89;
        mem[13109]=256;mem[13110]=98;mem[13111]=100;
        mem[13112]=257;mem[13113]=70;mem[13114]=73;
        mem[13115]=257;mem[13116]=87;mem[13117]=89;
        mem[13118]=257;mem[13119]=98;mem[13120]=101;
        mem[13121]=258;mem[13122]=71;mem[13123]=73;
        mem[13124]=258;mem[13125]=88;mem[13126]=88;
        mem[13127]=258;mem[13128]=99;mem[13129]=101;
        mem[13130]=259;mem[13131]=71;mem[13132]=74;
        mem[13133]=259;mem[13134]=99;mem[13135]=102;
        mem[13136]=260;mem[13137]=72;mem[13138]=74;
        mem[13139]=260;mem[13140]=100;mem[13141]=103;
        mem[13142]=260;mem[13143]=149;mem[13144]=149;
        mem[13145]=261;mem[13146]=72;mem[13147]=74;
        mem[13148]=261;mem[13149]=100;mem[13150]=103;
        mem[13151]=261;mem[13152]=149;mem[13153]=153;
        mem[13154]=262;mem[13155]=101;mem[13156]=103;
        mem[13157]=262;mem[13158]=146;mem[13159]=153;
        mem[13160]=263;mem[13161]=101;mem[13162]=103;
        mem[13163]=263;mem[13164]=146;mem[13165]=149;
        mem[13166]=263;mem[13167]=153;mem[13168]=153;
        mem[13169]=264;mem[13170]=146;mem[13171]=146;
        mem[13172]=264;mem[13173]=148;mem[13174]=148;
        mem[13175]=264;mem[13176]=152;mem[13177]=153;
        mem[13178]=265;mem[13179]=148;mem[13180]=148;
        mem[13181]=265;mem[13182]=152;mem[13183]=153;
        mem[13184]=266;mem[13185]=152;mem[13186]=152;
        mem[13187]=267;mem[13188]=150;mem[13189]=153;
        mem[13190]=268;mem[13191]=74;mem[13192]=74;
        mem[13193]=268;mem[13194]=95;mem[13195]=97;
        mem[13196]=268;mem[13197]=148;mem[13198]=153;
        mem[13199]=269;mem[13200]=73;mem[13201]=79;
        mem[13202]=269;mem[13203]=94;mem[13204]=97;
        mem[13205]=269;mem[13206]=148;mem[13207]=150;
        mem[13208]=269;mem[13209]=153;mem[13210]=153;
        mem[13211]=270;mem[13212]=73;mem[13213]=83;
        mem[13214]=270;mem[13215]=94;mem[13216]=97;
        mem[13217]=270;mem[13218]=148;mem[13219]=148;
        mem[13220]=270;mem[13221]=152;mem[13222]=153;
        mem[13223]=271;mem[13224]=73;mem[13225]=85;
        mem[13226]=271;mem[13227]=93;mem[13228]=96;
        mem[13229]=271;mem[13230]=148;mem[13231]=152;
        mem[13232]=272;mem[13233]=74;mem[13234]=85;
        mem[13235]=272;mem[13236]=93;mem[13237]=96;
        mem[13238]=272;mem[13239]=149;mem[13240]=151;
        mem[13241]=273;mem[13242]=74;mem[13243]=76;
        mem[13244]=273;mem[13245]=80;mem[13246]=85;
        mem[13247]=273;mem[13248]=93;mem[13249]=95;
        mem[13250]=274;mem[13251]=74;mem[13252]=76;
        mem[13253]=274;mem[13254]=83;mem[13255]=85;
        mem[13256]=274;mem[13257]=92;mem[13258]=95;
        mem[13259]=275;mem[13260]=73;mem[13261]=75;
        mem[13262]=275;mem[13263]=83;mem[13264]=94;
        mem[13265]=276;mem[13266]=67;mem[13267]=94;
        mem[13268]=277;mem[13269]=67;mem[13270]=93;
        mem[13271]=278;mem[13272]=67;mem[13273]=93;
        mem[13274]=279;mem[13275]=67;mem[13276]=84;
        mem[13277]=279;mem[13278]=90;mem[13279]=93;
        mem[13280]=280;mem[13281]=72;mem[13282]=74;
        mem[13283]=280;mem[13284]=80;mem[13285]=83;
        mem[13286]=280;mem[13287]=90;mem[13288]=92;
        mem[13289]=281;mem[13290]=72;mem[13291]=74;
        mem[13292]=281;mem[13293]=79;mem[13294]=83;
        mem[13295]=281;mem[13296]=89;mem[13297]=92;
        mem[13298]=281;mem[13299]=150;mem[13300]=150;
        mem[13301]=282;mem[13302]=72;mem[13303]=73;
        mem[13304]=282;mem[13305]=77;mem[13306]=83;
        mem[13307]=282;mem[13308]=89;mem[13309]=92;
        mem[13310]=282;mem[13311]=149;mem[13312]=150;
        mem[13313]=282;mem[13314]=153;mem[13315]=153;
        mem[13316]=283;mem[13317]=72;mem[13318]=73;
        mem[13319]=283;mem[13320]=75;mem[13321]=82;
        mem[13322]=283;mem[13323]=89;mem[13324]=94;
        mem[13325]=283;mem[13326]=148;mem[13327]=151;
        mem[13328]=283;mem[13329]=153;mem[13330]=153;
        mem[13331]=284;mem[13332]=72;mem[13333]=79;
        mem[13334]=284;mem[13335]=81;mem[13336]=82;
        mem[13337]=284;mem[13338]=89;mem[13339]=95;
        mem[13340]=284;mem[13341]=148;mem[13342]=148;
        mem[13343]=284;mem[13344]=150;mem[13345]=153;
        mem[13346]=285;mem[13347]=72;mem[13348]=78;
        mem[13349]=285;mem[13350]=91;mem[13351]=95;
        mem[13352]=285;mem[13353]=148;mem[13354]=148;
        mem[13355]=285;mem[13356]=151;mem[13357]=153;
        mem[13358]=286;mem[13359]=72;mem[13360]=76;
        mem[13361]=286;mem[13362]=92;mem[13363]=95;
        mem[13364]=286;mem[13365]=148;mem[13366]=148;
        mem[13367]=286;mem[13368]=151;mem[13369]=152;
        mem[13370]=287;mem[13371]=72;mem[13372]=75;
        mem[13373]=287;mem[13374]=94;mem[13375]=94;
        mem[13376]=288;mem[13377]=69;mem[13378]=73;
        mem[13379]=288;mem[13380]=149;mem[13381]=149;
        mem[13382]=289;mem[13383]=69;mem[13384]=77;
        mem[13385]=289;mem[13386]=149;mem[13387]=153;
        mem[13388]=290;mem[13389]=69;mem[13390]=78;
        mem[13391]=290;mem[13392]=92;mem[13393]=99;
        mem[13394]=290;mem[13395]=146;mem[13396]=153;
        mem[13397]=291;mem[13398]=69;mem[13399]=78;
        mem[13400]=291;mem[13401]=81;mem[13402]=99;
        mem[13403]=291;mem[13404]=146;mem[13405]=149;
        mem[13406]=291;mem[13407]=153;mem[13408]=153;
        mem[13409]=292;mem[13410]=71;mem[13411]=73;
        mem[13412]=292;mem[13413]=75;mem[13414]=78;
        mem[13415]=292;mem[13416]=80;mem[13417]=99;
        mem[13418]=292;mem[13419]=146;mem[13420]=146;
        mem[13421]=292;mem[13422]=148;mem[13423]=148;
        mem[13424]=292;mem[13425]=152;mem[13426]=153;
        mem[13427]=293;mem[13428]=71;mem[13429]=73;
        mem[13430]=293;mem[13431]=80;mem[13432]=99;
        mem[13433]=293;mem[13434]=148;mem[13435]=148;
        mem[13436]=293;mem[13437]=152;mem[13438]=153;
        mem[13439]=294;mem[13440]=63;mem[13441]=64;
        mem[13442]=294;mem[13443]=71;mem[13444]=73;
        mem[13445]=294;mem[13446]=81;mem[13447]=89;
        mem[13448]=294;mem[13449]=97;mem[13450]=99;
        mem[13451]=294;mem[13452]=152;mem[13453]=152;
        mem[13454]=295;mem[13455]=63;mem[13456]=65;
        mem[13457]=295;mem[13458]=71;mem[13459]=72;
        mem[13460]=295;mem[13461]=86;mem[13462]=88;
        mem[13463]=295;mem[13464]=97;mem[13465]=99;
        mem[13466]=295;mem[13467]=150;mem[13468]=152;
        mem[13469]=296;mem[13470]=63;mem[13471]=66;
        mem[13472]=296;mem[13473]=71;mem[13474]=72;
        mem[13475]=296;mem[13476]=85;mem[13477]=87;
        mem[13478]=296;mem[13479]=97;mem[13480]=99;
        mem[13481]=296;mem[13482]=148;mem[13483]=153;
        mem[13484]=297;mem[13485]=63;mem[13486]=67;
        mem[13487]=297;mem[13488]=70;mem[13489]=72;
        mem[13490]=297;mem[13491]=84;mem[13492]=87;
        mem[13493]=297;mem[13494]=97;mem[13495]=99;
        mem[13496]=297;mem[13497]=148;mem[13498]=149;
        mem[13499]=297;mem[13500]=152;mem[13501]=153;
        mem[13502]=298;mem[13503]=64;mem[13504]=67;
        mem[13505]=298;mem[13506]=70;mem[13507]=72;
        mem[13508]=298;mem[13509]=83;mem[13510]=86;
        mem[13511]=298;mem[13512]=97;mem[13513]=99;
        mem[13514]=298;mem[13515]=148;mem[13516]=148;
        mem[13517]=298;mem[13518]=151;mem[13519]=152;
        mem[13520]=299;mem[13521]=66;mem[13522]=67;
        mem[13523]=299;mem[13524]=70;mem[13525]=71;
        mem[13526]=299;mem[13527]=82;mem[13528]=85;
        mem[13529]=299;mem[13530]=97;mem[13531]=98;
        mem[13532]=299;mem[13533]=148;mem[13534]=153;
        mem[13535]=300;mem[13536]=70;mem[13537]=71;
        mem[13538]=300;mem[13539]=81;mem[13540]=85;
        mem[13541]=300;mem[13542]=97;mem[13543]=98;
        mem[13544]=300;mem[13545]=148;mem[13546]=151;
        mem[13547]=300;mem[13548]=153;mem[13549]=153;
        mem[13550]=301;mem[13551]=69;mem[13552]=71;
        mem[13553]=301;mem[13554]=80;mem[13555]=84;
        mem[13556]=301;mem[13557]=97;mem[13558]=98;
        mem[13559]=301;mem[13560]=153;mem[13561]=153;
        mem[13562]=302;mem[13563]=69;mem[13564]=71;
        mem[13565]=302;mem[13566]=80;mem[13567]=83;
        mem[13568]=302;mem[13569]=96;mem[13570]=98;
        mem[13571]=302;mem[13572]=152;mem[13573]=153;
        mem[13574]=303;mem[13575]=69;mem[13576]=70;
        mem[13577]=303;mem[13578]=74;mem[13579]=75;
        mem[13580]=303;mem[13581]=80;mem[13582]=82;
        mem[13583]=303;mem[13584]=96;mem[13585]=98;
        mem[13586]=303;mem[13587]=148;mem[13588]=153;
        mem[13589]=304;mem[13590]=69;mem[13591]=70;
        mem[13592]=304;mem[13593]=72;mem[13594]=75;
        mem[13595]=304;mem[13596]=80;mem[13597]=81;
        mem[13598]=304;mem[13599]=96;mem[13600]=98;
        mem[13601]=304;mem[13602]=148;mem[13603]=151;
        mem[13604]=305;mem[13605]=68;mem[13606]=75;
        mem[13607]=305;mem[13608]=81;mem[13609]=81;
        mem[13610]=305;mem[13611]=96;mem[13612]=98;
        mem[13613]=305;mem[13614]=149;mem[13615]=150;
        mem[13616]=306;mem[13617]=68;mem[13618]=74;
        mem[13619]=306;mem[13620]=96;mem[13621]=98;
        mem[13622]=306;mem[13623]=148;mem[13624]=149;
        mem[13625]=307;mem[13626]=68;mem[13627]=73;
        mem[13628]=307;mem[13629]=91;mem[13630]=93;
        mem[13631]=307;mem[13632]=96;mem[13633]=98;
        mem[13634]=307;mem[13635]=148;mem[13636]=149;
        mem[13637]=308;mem[13638]=68;mem[13639]=72;
        mem[13640]=308;mem[13641]=91;mem[13642]=97;
        mem[13643]=308;mem[13644]=149;mem[13645]=149;
        mem[13646]=309;mem[13647]=68;mem[13648]=70;
        mem[13649]=309;mem[13650]=92;mem[13651]=97;
        mem[13652]=309;mem[13653]=149;mem[13654]=149;
        mem[13655]=310;mem[13656]=69;mem[13657]=69;
        mem[13658]=310;mem[13659]=93;mem[13660]=97;
        mem[13661]=310;mem[13662]=149;mem[13663]=153;
        mem[13664]=311;mem[13665]=95;mem[13666]=97;
        mem[13667]=311;mem[13668]=146;mem[13669]=153;
        mem[13670]=312;mem[13671]=146;mem[13672]=149;
        mem[13673]=312;mem[13674]=153;mem[13675]=153;
        mem[13676]=313;mem[13677]=146;mem[13678]=146;
        mem[13679]=313;mem[13680]=148;mem[13681]=148;
        mem[13682]=313;mem[13683]=152;mem[13684]=153;
        mem[13685]=314;mem[13686]=148;mem[13687]=148;
        mem[13688]=314;mem[13689]=152;mem[13690]=153;
        mem[13691]=315;mem[13692]=152;mem[13693]=152;
        mem[13694]=-1;
    End

    Func(set_gameover_pic)
    mem[12032]=154;mem[12033]=137;mem[12034]=139;
        mem[12035]=155;mem[12036]=115;mem[12037]=122;
        mem[12038]=155;mem[12039]=137;mem[12040]=141;
        mem[12041]=156;mem[12042]=112;mem[12043]=124;
        mem[12044]=156;mem[12045]=136;mem[12046]=142;
        mem[12047]=157;mem[12048]=111;mem[12049]=125;
        mem[12050]=157;mem[12051]=136;mem[12052]=143;
        mem[12053]=158;mem[12054]=109;mem[12055]=126;
        mem[12056]=158;mem[12057]=136;mem[12058]=143;
        mem[12059]=159;mem[12060]=108;mem[12061]=127;
        mem[12062]=159;mem[12063]=136;mem[12064]=144;
        mem[12065]=160;mem[12066]=107;mem[12067]=113;
        mem[12068]=160;mem[12069]=121;mem[12070]=127;
        mem[12071]=160;mem[12072]=142;mem[12073]=144;
        mem[12074]=161;mem[12075]=106;mem[12076]=110;
        mem[12077]=161;mem[12078]=124;mem[12079]=128;
        mem[12080]=161;mem[12081]=143;mem[12082]=145;
        mem[12083]=162;mem[12084]=105;mem[12085]=108;
        mem[12086]=162;mem[12087]=125;mem[12088]=128;
        mem[12089]=162;mem[12090]=144;mem[12091]=145;
        mem[12092]=163;mem[12093]=105;mem[12094]=107;
        mem[12095]=163;mem[12096]=126;mem[12097]=128;
        mem[12098]=163;mem[12099]=144;mem[12100]=145;
        mem[12101]=164;mem[12102]=104;mem[12103]=106;
        mem[12104]=164;mem[12105]=126;mem[12106]=128;
        mem[12107]=164;mem[12108]=145;mem[12109]=145;
        mem[12110]=165;mem[12111]=103;mem[12112]=105;
        mem[12113]=165;mem[12114]=127;mem[12115]=128;
        mem[12116]=165;mem[12117]=145;mem[12118]=145;
        mem[12119]=166;mem[12120]=103;mem[12121]=104;
        mem[12122]=166;mem[12123]=113;mem[12124]=113;
        mem[12125]=166;mem[12126]=127;mem[12127]=128;
        mem[12128]=166;mem[12129]=145;mem[12130]=145;
        mem[12131]=167;mem[12132]=103;mem[12133]=104;
        mem[12134]=167;mem[12135]=111;mem[12136]=115;
        mem[12137]=167;mem[12138]=127;mem[12139]=128;
        mem[12140]=167;mem[12141]=145;mem[12142]=145;
        mem[12143]=168;mem[12144]=102;mem[12145]=103;
        mem[12146]=168;mem[12147]=109;mem[12148]=116;
        mem[12149]=168;mem[12150]=127;mem[12151]=128;
        mem[12152]=168;mem[12153]=145;mem[12154]=145;
        mem[12155]=169;mem[12156]=102;mem[12157]=103;
        mem[12158]=169;mem[12159]=109;mem[12160]=116;
        mem[12161]=169;mem[12162]=126;mem[12163]=127;
        mem[12164]=169;mem[12165]=144;mem[12166]=145;
        mem[12167]=170;mem[12168]=102;mem[12169]=103;
        mem[12170]=170;mem[12171]=108;mem[12172]=116;
        mem[12173]=170;mem[12174]=126;mem[12175]=127;
        mem[12176]=170;mem[12177]=144;mem[12178]=145;
        mem[12179]=171;mem[12180]=102;mem[12181]=103;
        mem[12182]=171;mem[12183]=108;mem[12184]=109;
        mem[12185]=171;mem[12186]=114;mem[12187]=116;
        mem[12188]=171;mem[12189]=125;mem[12190]=126;
        mem[12191]=171;mem[12192]=143;mem[12193]=144;
        mem[12194]=172;mem[12195]=102;mem[12196]=103;
        mem[12197]=172;mem[12198]=108;mem[12199]=108;
        mem[12200]=172;mem[12201]=115;mem[12202]=116;
        mem[12203]=172;mem[12204]=124;mem[12205]=126;
        mem[12206]=172;mem[12207]=142;mem[12208]=144;
        mem[12209]=173;mem[12210]=102;mem[12211]=104;
        mem[12212]=173;mem[12213]=115;mem[12214]=116;
        mem[12215]=173;mem[12216]=124;mem[12217]=125;
        mem[12218]=173;mem[12219]=141;mem[12220]=143;
        mem[12221]=174;mem[12222]=102;mem[12223]=104;
        mem[12224]=174;mem[12225]=114;mem[12226]=116;
        mem[12227]=174;mem[12228]=123;mem[12229]=124;
        mem[12230]=174;mem[12231]=139;mem[12232]=143;
        mem[12233]=175;mem[12234]=102;mem[12235]=105;
        mem[12236]=175;mem[12237]=114;mem[12238]=115;
        mem[12239]=175;mem[12240]=121;mem[12241]=142;
        mem[12242]=176;mem[12243]=102;mem[12244]=106;
        mem[12245]=176;mem[12246]=112;mem[12247]=115;
        mem[12248]=176;mem[12249]=120;mem[12250]=141;
        mem[12251]=177;mem[12252]=103;mem[12253]=114;
        mem[12254]=177;mem[12255]=119;mem[12256]=140;
        mem[12257]=178;mem[12258]=103;mem[12259]=113;
        mem[12260]=178;mem[12261]=119;mem[12262]=139;
        mem[12263]=179;mem[12264]=104;mem[12265]=112;
        mem[12266]=179;mem[12267]=118;mem[12268]=120;
        mem[12269]=179;mem[12270]=127;mem[12271]=137;
        mem[12272]=180;mem[12273]=106;mem[12274]=110;
        mem[12275]=180;mem[12276]=118;mem[12277]=119;
        mem[12278]=180;mem[12279]=131;mem[12280]=133;
        mem[12281]=181;mem[12282]=118;mem[12283]=118;
        mem[12284]=183;mem[12285]=140;mem[12286]=140;
        mem[12287]=184;mem[12288]=139;mem[12289]=141;
        mem[12290]=185;mem[12291]=137;mem[12292]=141;
        mem[12293]=186;mem[12294]=136;mem[12295]=143;
        mem[12296]=187;mem[12297]=134;mem[12298]=144;
        mem[12299]=188;mem[12300]=133;mem[12301]=145;
        mem[12302]=189;mem[12303]=132;mem[12304]=145;
        mem[12305]=190;mem[12306]=132;mem[12307]=145;
        mem[12308]=191;mem[12309]=131;mem[12310]=133;
        mem[12311]=191;mem[12312]=141;mem[12313]=145;
        mem[12314]=192;mem[12315]=130;mem[12316]=132;
        mem[12317]=192;mem[12318]=142;mem[12319]=145;
        mem[12320]=193;mem[12321]=130;mem[12322]=131;
        mem[12323]=193;mem[12324]=143;mem[12325]=145;
        mem[12326]=194;mem[12327]=130;mem[12328]=130;
        mem[12329]=194;mem[12330]=143;mem[12331]=145;
        mem[12332]=195;mem[12333]=130;mem[12334]=130;
        mem[12335]=195;mem[12336]=142;mem[12337]=144;
        mem[12338]=196;mem[12339]=130;mem[12340]=131;
        mem[12341]=196;mem[12342]=141;mem[12343]=144;
        mem[12344]=197;mem[12345]=130;mem[12346]=144;
        mem[12347]=198;mem[12348]=130;mem[12349]=145;
        mem[12350]=199;mem[12351]=130;mem[12352]=145;
        mem[12353]=200;mem[12354]=130;mem[12355]=145;
        mem[12356]=201;mem[12357]=130;mem[12358]=145;
        mem[12359]=202;mem[12360]=143;mem[12361]=145;
        mem[12362]=203;mem[12363]=143;mem[12364]=144;
        mem[12365]=204;mem[12366]=141;mem[12367]=144;
        mem[12368]=205;mem[12369]=140;mem[12370]=143;
        mem[12371]=206;mem[12372]=139;mem[12373]=142;
        mem[12374]=207;mem[12375]=137;mem[12376]=141;
        mem[12377]=208;mem[12378]=134;mem[12379]=140;
        mem[12380]=209;mem[12381]=132;mem[12382]=145;
        mem[12383]=210;mem[12384]=132;mem[12385]=145;
        mem[12386]=211;mem[12387]=131;mem[12388]=145;
        mem[12389]=212;mem[12390]=131;mem[12391]=144;
        mem[12392]=213;mem[12393]=131;mem[12394]=144;
        mem[12395]=214;mem[12396]=134;mem[12397]=137;
        mem[12398]=215;mem[12399]=133;mem[12400]=135;
        mem[12401]=216;mem[12402]=132;mem[12403]=134;
        mem[12404]=217;mem[12405]=131;mem[12406]=133;
        mem[12407]=218;mem[12408]=131;mem[12409]=145;
        mem[12410]=219;mem[12411]=131;mem[12412]=145;
        mem[12413]=220;mem[12414]=131;mem[12415]=145;
        mem[12416]=221;mem[12417]=131;mem[12418]=145;
        mem[12419]=222;mem[12420]=132;mem[12421]=144;
        mem[12422]=223;mem[12423]=134;mem[12424]=138;
        mem[12425]=224;mem[12426]=133;mem[12427]=136;
        mem[12428]=225;mem[12429]=132;mem[12430]=135;
        mem[12431]=226;mem[12432]=131;mem[12433]=133;
        mem[12434]=227;mem[12435]=131;mem[12436]=132;
        mem[12437]=228;mem[12438]=131;mem[12439]=144;
        mem[12440]=229;mem[12441]=131;mem[12442]=145;
        mem[12443]=230;mem[12444]=131;mem[12445]=145;
        mem[12446]=231;mem[12447]=132;mem[12448]=145;
        mem[12449]=232;mem[12450]=134;mem[12451]=145;
        mem[12452]=233;mem[12453]=143;mem[12454]=145;
        mem[12455]=234;mem[12456]=142;mem[12457]=144;
        mem[12458]=235;mem[12459]=141;mem[12460]=144;
        mem[12461]=236;mem[12462]=140;mem[12463]=143;
        mem[12464]=237;mem[12465]=139;mem[12466]=142;
        mem[12467]=238;mem[12468]=137;mem[12469]=141;
        mem[12470]=239;mem[12471]=136;mem[12472]=142;
        mem[12473]=240;mem[12474]=134;mem[12475]=144;
        mem[12476]=241;mem[12477]=133;mem[12478]=144;
        mem[12479]=242;mem[12480]=132;mem[12481]=145;
        mem[12482]=243;mem[12483]=131;mem[12484]=134;
        mem[12485]=243;mem[12486]=139;mem[12487]=145;
        mem[12488]=244;mem[12489]=131;mem[12490]=132;
        mem[12491]=244;mem[12492]=139;mem[12493]=140;
        mem[12494]=244;mem[12495]=142;mem[12496]=145;
        mem[12497]=245;mem[12498]=130;mem[12499]=131;
        mem[12500]=245;mem[12501]=138;mem[12502]=139;
        mem[12503]=245;mem[12504]=143;mem[12505]=145;
        mem[12506]=246;mem[12507]=130;mem[12508]=131;
        mem[12509]=246;mem[12510]=137;mem[12511]=139;
        mem[12512]=246;mem[12513]=144;mem[12514]=145;
        mem[12515]=247;mem[12516]=130;mem[12517]=132;
        mem[12518]=247;mem[12519]=135;mem[12520]=138;
        mem[12521]=247;mem[12522]=144;mem[12523]=145;
        mem[12524]=248;mem[12525]=130;mem[12526]=137;
        mem[12527]=248;mem[12528]=144;mem[12529]=145;
        mem[12530]=249;mem[12531]=130;mem[12532]=136;
        mem[12533]=249;mem[12534]=143;mem[12535]=145;
        mem[12536]=250;mem[12537]=131;mem[12538]=135;
        mem[12539]=250;mem[12540]=143;mem[12541]=144;
        mem[12542]=251;mem[12543]=132;mem[12544]=133;
        mem[12545]=251;mem[12546]=142;mem[12547]=144;
        mem[12548]=252;mem[12549]=141;mem[12550]=143;
        mem[12551]=253;mem[12552]=140;mem[12553]=143;
        mem[12554]=254;mem[12555]=140;mem[12556]=142;
        mem[12557]=255;mem[12558]=140;mem[12559]=140;
        mem[12560]=272;mem[12561]=123;mem[12562]=130;
        mem[12563]=273;mem[12564]=118;mem[12565]=134;
        mem[12566]=274;mem[12567]=115;mem[12568]=137;
        mem[12569]=275;mem[12570]=113;mem[12571]=138;
        mem[12572]=276;mem[12573]=111;mem[12574]=140;
        mem[12575]=277;mem[12576]=109;mem[12577]=116;
        mem[12578]=277;mem[12579]=130;mem[12580]=141;
        mem[12581]=278;mem[12582]=108;mem[12583]=113;
        mem[12584]=278;mem[12585]=133;mem[12586]=142;
        mem[12587]=279;mem[12588]=107;mem[12589]=111;
        mem[12590]=279;mem[12591]=135;mem[12592]=143;
        mem[12593]=280;mem[12594]=106;mem[12595]=109;
        mem[12596]=280;mem[12597]=114;mem[12598]=120;
        mem[12599]=280;mem[12600]=137;mem[12601]=143;
        mem[12602]=281;mem[12603]=105;mem[12604]=107;
        mem[12605]=281;mem[12606]=111;mem[12607]=122;
        mem[12608]=281;mem[12609]=138;mem[12610]=144;
        mem[12611]=282;mem[12612]=104;mem[12613]=106;
        mem[12614]=282;mem[12615]=109;mem[12616]=123;
        mem[12617]=282;mem[12618]=139;mem[12619]=144;
        mem[12620]=283;mem[12621]=104;mem[12622]=105;
        mem[12623]=283;mem[12624]=108;mem[12625]=113;
        mem[12626]=283;mem[12627]=117;mem[12628]=124;
        mem[12629]=283;mem[12630]=140;mem[12631]=145;
        mem[12632]=284;mem[12633]=107;mem[12634]=109;
        mem[12635]=284;mem[12636]=120;mem[12637]=125;
        mem[12638]=284;mem[12639]=141;mem[12640]=145;
        mem[12641]=285;mem[12642]=106;mem[12643]=108;
        mem[12644]=285;mem[12645]=122;mem[12646]=125;
        mem[12647]=285;mem[12648]=142;mem[12649]=145;
        mem[12650]=286;mem[12651]=105;mem[12652]=107;
        mem[12653]=286;mem[12654]=122;mem[12655]=125;
        mem[12656]=286;mem[12657]=142;mem[12658]=145;
        mem[12659]=287;mem[12660]=104;mem[12661]=106;
        mem[12662]=287;mem[12663]=123;mem[12664]=125;
        mem[12665]=287;mem[12666]=143;mem[12667]=145;
        mem[12668]=288;mem[12669]=104;mem[12670]=105;
        mem[12671]=288;mem[12672]=123;mem[12673]=125;
        mem[12674]=288;mem[12675]=143;mem[12676]=145;
        mem[12677]=289;mem[12678]=103;mem[12679]=105;
        mem[12680]=289;mem[12681]=122;mem[12682]=125;
        mem[12683]=289;mem[12684]=143;mem[12685]=145;
        mem[12686]=290;mem[12687]=103;mem[12688]=105;
        mem[12689]=290;mem[12690]=120;mem[12691]=124;
        mem[12692]=290;mem[12693]=143;mem[12694]=145;
        mem[12695]=291;mem[12696]=103;mem[12697]=105;
        mem[12698]=291;mem[12699]=117;mem[12700]=124;
        mem[12701]=291;mem[12702]=143;mem[12703]=144;
        mem[12704]=292;mem[12705]=103;mem[12706]=106;
        mem[12707]=292;mem[12708]=117;mem[12709]=122;
        mem[12710]=292;mem[12711]=142;mem[12712]=144;
        mem[12713]=293;mem[12714]=103;mem[12715]=106;
        mem[12716]=293;mem[12717]=142;mem[12718]=144;
        mem[12719]=294;mem[12720]=103;mem[12721]=107;
        mem[12722]=294;mem[12723]=141;mem[12724]=143;
        mem[12725]=295;mem[12726]=103;mem[12727]=108;
        mem[12728]=295;mem[12729]=140;mem[12730]=142;
        mem[12731]=296;mem[12732]=104;mem[12733]=110;
        mem[12734]=296;mem[12735]=139;mem[12736]=142;
        mem[12737]=297;mem[12738]=104;mem[12739]=111;
        mem[12740]=297;mem[12741]=138;mem[12742]=141;
        mem[12743]=298;mem[12744]=105;mem[12745]=113;
        mem[12746]=298;mem[12747]=136;mem[12748]=139;
        mem[12749]=299;mem[12750]=106;mem[12751]=116;
        mem[12752]=299;mem[12753]=133;mem[12754]=138;
        mem[12755]=300;mem[12756]=107;mem[12757]=137;
        mem[12758]=301;mem[12759]=108;mem[12760]=135;
        mem[12761]=302;mem[12762]=110;mem[12763]=133;
        mem[12764]=303;mem[12765]=113;mem[12766]=130;
        mem[12767]=304;mem[12768]=117;mem[12769]=125;
        mem[12770]=306;mem[12771]=140;mem[12772]=140;
        mem[12773]=307;mem[12774]=138;mem[12775]=140;
        mem[12776]=308;mem[12777]=136;mem[12778]=140;
        mem[12779]=309;mem[12780]=135;mem[12781]=139;
        mem[12782]=310;mem[12783]=133;mem[12784]=137;
        mem[12785]=311;mem[12786]=131;mem[12787]=137;
        mem[12788]=312;mem[12789]=131;mem[12790]=139;
        mem[12791]=313;mem[12792]=132;mem[12793]=141;
        mem[12794]=314;mem[12795]=125;mem[12796]=126;
        mem[12797]=314;mem[12798]=134;mem[12799]=145;
        mem[12800]=315;mem[12801]=125;mem[12802]=127;
        mem[12803]=315;mem[12804]=136;mem[12805]=145;
        mem[12806]=316;mem[12807]=125;mem[12808]=127;
        mem[12809]=316;mem[12810]=138;mem[12811]=145;
        mem[12812]=317;mem[12813]=125;mem[12814]=127;
        mem[12815]=317;mem[12816]=140;mem[12817]=143;
        mem[12818]=317;mem[12819]=145;mem[12820]=145;
        mem[12821]=318;mem[12822]=125;mem[12823]=127;
        mem[12824]=318;mem[12825]=140;mem[12826]=142;
        mem[12827]=318;mem[12828]=145;mem[12829]=145;
        mem[12830]=319;mem[12831]=125;mem[12832]=128;
        mem[12833]=319;mem[12834]=138;mem[12835]=141;
        mem[12836]=319;mem[12837]=144;mem[12838]=145;
        mem[12839]=320;mem[12840]=126;mem[12841]=130;
        mem[12842]=320;mem[12843]=135;mem[12844]=140;
        mem[12845]=320;mem[12846]=143;mem[12847]=144;
        mem[12848]=321;mem[12849]=127;mem[12850]=138;
        mem[12851]=321;mem[12852]=142;mem[12853]=144;
        mem[12854]=322;mem[12855]=128;mem[12856]=136;
        mem[12857]=322;mem[12858]=141;mem[12859]=143;
        mem[12860]=323;mem[12861]=131;mem[12862]=133;
        mem[12863]=323;mem[12864]=140;mem[12865]=143;
        mem[12866]=324;mem[12867]=139;mem[12868]=142;
        mem[12869]=325;mem[12870]=137;mem[12871]=141;
        mem[12872]=326;mem[12873]=136;mem[12874]=142;
        mem[12875]=327;mem[12876]=134;mem[12877]=144;
        mem[12878]=328;mem[12879]=133;mem[12880]=144;
        mem[12881]=329;mem[12882]=132;mem[12883]=145;
        mem[12884]=330;mem[12885]=131;mem[12886]=134;
        mem[12887]=330;mem[12888]=139;mem[12889]=145;
        mem[12890]=331;mem[12891]=131;mem[12892]=132;
        mem[12893]=331;mem[12894]=139;mem[12895]=140;
        mem[12896]=331;mem[12897]=142;mem[12898]=145;
        mem[12899]=332;mem[12900]=130;mem[12901]=131;
        mem[12902]=332;mem[12903]=138;mem[12904]=139;
        mem[12905]=332;mem[12906]=143;mem[12907]=145;
        mem[12908]=333;mem[12909]=130;mem[12910]=131;
        mem[12911]=333;mem[12912]=137;mem[12913]=139;
        mem[12914]=333;mem[12915]=144;mem[12916]=145;
        mem[12917]=334;mem[12918]=130;mem[12919]=132;
        mem[12920]=334;mem[12921]=135;mem[12922]=138;
        mem[12923]=334;mem[12924]=144;mem[12925]=145;
        mem[12926]=335;mem[12927]=130;mem[12928]=137;
        mem[12929]=335;mem[12930]=144;mem[12931]=145;
        mem[12932]=336;mem[12933]=130;mem[12934]=136;
        mem[12935]=336;mem[12936]=143;mem[12937]=145;
        mem[12938]=337;mem[12939]=131;mem[12940]=135;
        mem[12941]=337;mem[12942]=143;mem[12943]=144;
        mem[12944]=338;mem[12945]=132;mem[12946]=133;
        mem[12947]=338;mem[12948]=142;mem[12949]=144;
        mem[12950]=339;mem[12951]=141;mem[12952]=143;
        mem[12953]=340;mem[12954]=140;mem[12955]=143;
        mem[12956]=341;mem[12957]=139;mem[12958]=142;
        mem[12959]=342;mem[12960]=137;mem[12961]=141;
        mem[12962]=343;mem[12963]=135;mem[12964]=139;
        mem[12965]=344;mem[12966]=133;mem[12967]=138;
        mem[12968]=345;mem[12969]=131;mem[12970]=136;
        mem[12971]=346;mem[12972]=131;mem[12973]=134;
        mem[12974]=346;mem[12975]=139;mem[12976]=144;
        mem[12977]=347;mem[12978]=131;mem[12979]=134;
        mem[12980]=347;mem[12981]=137;mem[12982]=145;
        mem[12983]=348;mem[12984]=132;mem[12985]=134;
        mem[12986]=348;mem[12987]=136;mem[12988]=145;
        mem[12989]=349;mem[12990]=132;mem[12991]=145;
        mem[12992]=350;mem[12993]=132;mem[12994]=139;
        mem[12995]=350;mem[12996]=142;mem[12997]=145;
        mem[12998]=351;mem[12999]=132;mem[13000]=135;
        mem[13001]=351;mem[13002]=144;mem[13003]=145;
        mem[13004]=352;mem[13005]=131;mem[13006]=133;
        mem[13007]=352;mem[13008]=143;mem[13009]=145;
        mem[13010]=353;mem[13011]=131;mem[13012]=132;
        mem[13013]=353;mem[13014]=143;mem[13015]=144;
        mem[13016]=354;mem[13017]=131;mem[13018]=131;
        mem[13019]=354;mem[13020]=141;mem[13021]=144;
        mem[13022]=355;mem[13023]=140;mem[13024]=143;
        mem[13025]=356;mem[13026]=140;mem[13027]=142;
        mem[13028]=357;mem[13029]=140;mem[13030]=140;
        mem[13031]=-1;
    End
    Func(set_num_pic)
        mem[1536]=1552;
        mem[1552]=6;mem[1553]=16;mem[1554]=22;
        mem[1555]=7;mem[1556]=13;mem[1557]=22;
        mem[1558]=8;mem[1559]=11;mem[1560]=23;
        mem[1561]=9;mem[1562]=9;mem[1563]=15;
        mem[1564]=9;mem[1565]=22;mem[1566]=23;
        mem[1567]=10;mem[1568]=7;mem[1569]=12;
        mem[1570]=10;mem[1571]=22;mem[1572]=23;
        mem[1573]=11;mem[1574]=5;mem[1575]=9;
        mem[1576]=11;mem[1577]=21;mem[1578]=22;
        mem[1579]=12;mem[1580]=5;mem[1581]=7;
        mem[1582]=12;mem[1583]=20;mem[1584]=22;
        mem[1585]=13;mem[1586]=5;mem[1587]=6;
        mem[1588]=13;mem[1589]=18;mem[1590]=21;
        mem[1591]=14;mem[1592]=5;mem[1593]=6;
        mem[1594]=14;mem[1595]=16;mem[1596]=20;
        mem[1597]=15;mem[1598]=5;mem[1599]=6;
        mem[1600]=15;mem[1601]=14;mem[1602]=19;
        mem[1603]=16;mem[1604]=5;mem[1605]=6;
        mem[1606]=16;mem[1607]=11;mem[1608]=17;
        mem[1609]=17;mem[1610]=5;mem[1611]=15;
        mem[1612]=18;mem[1613]=5;mem[1614]=13;
        mem[1615]=19;mem[1616]=7;mem[1617]=10;
        mem[1618]=-1;
        mem[1537]=1619;
        mem[1619]=9;mem[1620]=22;mem[1621]=23;
        mem[1622]=10;mem[1623]=18;mem[1624]=23;
        mem[1625]=11;mem[1626]=14;mem[1627]=23;
        mem[1628]=12;mem[1629]=9;mem[1630]=23;
        mem[1631]=13;mem[1632]=5;mem[1633]=17;
        mem[1634]=14;mem[1635]=4;mem[1636]=12;
        mem[1637]=15;mem[1638]=4;mem[1639]=8;
        mem[1640]=-1;
        mem[1538]=1641;
        mem[1641]=5;mem[1642]=7;mem[1643]=8;
        mem[1644]=6;mem[1645]=7;mem[1646]=8;
        mem[1647]=7;mem[1648]=6;mem[1649]=8;
        mem[1650]=7;mem[1651]=19;mem[1652]=23;
        mem[1653]=8;mem[1654]=5;mem[1655]=8;
        mem[1656]=8;mem[1657]=17;mem[1658]=23;
        mem[1659]=9;mem[1660]=5;mem[1661]=6;
        mem[1662]=9;mem[1663]=15;mem[1664]=23;
        mem[1665]=10;mem[1666]=5;mem[1667]=5;
        mem[1668]=10;mem[1669]=13;mem[1670]=18;
        mem[1671]=10;mem[1672]=22;mem[1673]=23;
        mem[1674]=11;mem[1675]=4;mem[1676]=5;
        mem[1677]=11;mem[1678]=11;mem[1679]=16;
        mem[1680]=11;mem[1681]=22;mem[1682]=23;
        mem[1683]=12;mem[1684]=4;mem[1685]=5;
        mem[1686]=12;mem[1687]=9;mem[1688]=14;
        mem[1689]=12;mem[1690]=22;mem[1691]=22;
        mem[1692]=13;mem[1693]=4;mem[1694]=12;
        mem[1695]=13;mem[1696]=21;mem[1697]=22;
        mem[1698]=14;mem[1699]=5;mem[1700]=10;
        mem[1701]=14;mem[1702]=21;mem[1703]=22;
        mem[1704]=15;mem[1705]=5;mem[1706]=8;
        mem[1707]=15;mem[1708]=21;mem[1709]=21;
        mem[1710]=16;mem[1711]=20;mem[1712]=21;
        mem[1713]=17;mem[1714]=20;mem[1715]=21;
        mem[1716]=-1;
        mem[1539]=1717;
        mem[1717]=4;mem[1718]=6;mem[1719]=6;
        mem[1720]=5;mem[1721]=6;mem[1722]=6;
        mem[1723]=6;mem[1724]=5;mem[1725]=6;
        mem[1726]=7;mem[1727]=5;mem[1728]=6;
        mem[1729]=7;mem[1730]=13;mem[1731]=13;
        mem[1732]=8;mem[1733]=5;mem[1734]=6;
        mem[1735]=8;mem[1736]=11;mem[1737]=13;
        mem[1738]=9;mem[1739]=4;mem[1740]=5;
        mem[1741]=9;mem[1742]=9;mem[1743]=14;
        mem[1744]=9;mem[1745]=22;mem[1746]=23;
        mem[1747]=10;mem[1748]=4;mem[1749]=5;
        mem[1750]=10;mem[1751]=7;mem[1752]=14;
        mem[1753]=10;mem[1754]=22;mem[1755]=23;
        mem[1756]=11;mem[1757]=4;mem[1758]=10;
        mem[1759]=11;mem[1760]=13;mem[1761]=14;
        mem[1762]=11;mem[1763]=20;mem[1764]=23;
        mem[1765]=12;mem[1766]=4;mem[1767]=8;
        mem[1768]=12;mem[1769]=13;mem[1770]=13;
        mem[1771]=12;mem[1772]=19;mem[1773]=22;
        mem[1774]=13;mem[1775]=5;mem[1776]=6;
        mem[1777]=13;mem[1778]=13;mem[1779]=14;
        mem[1780]=13;mem[1781]=17;mem[1782]=21;
        mem[1783]=14;mem[1784]=13;mem[1785]=20;
        mem[1786]=15;mem[1787]=13;mem[1788]=18;
        mem[1789]=16;mem[1790]=14;mem[1791]=16;
        mem[1792]=-1;
        mem[1540]=1793;
        mem[1793]=4;mem[1794]=16;mem[1795]=19;
        mem[1796]=5;mem[1797]=13;mem[1798]=19;
        mem[1799]=6;mem[1800]=11;mem[1801]=19;
        mem[1802]=7;mem[1803]=8;mem[1804]=14;
        mem[1805]=7;mem[1806]=19;mem[1807]=19;
        mem[1808]=7;mem[1809]=22;mem[1810]=23;
        mem[1811]=8;mem[1812]=6;mem[1813]=12;
        mem[1814]=8;mem[1815]=18;mem[1816]=23;
        mem[1817]=9;mem[1818]=6;mem[1819]=9;
        mem[1820]=9;mem[1821]=17;mem[1822]=23;
        mem[1823]=10;mem[1824]=6;mem[1825]=7;
        mem[1826]=10;mem[1827]=14;mem[1828]=21;
        mem[1829]=11;mem[1830]=12;mem[1831]=19;
        mem[1832]=12;mem[1833]=9;mem[1834]=15;
        mem[1835]=12;mem[1836]=17;mem[1837]=18;
        mem[1838]=13;mem[1839]=7;mem[1840]=13;
        mem[1841]=13;mem[1842]=17;mem[1843]=18;
        mem[1844]=14;mem[1845]=5;mem[1846]=10;
        mem[1847]=14;mem[1848]=16;mem[1849]=17;
        mem[1850]=15;mem[1851]=4;mem[1852]=8;
        mem[1853]=15;mem[1854]=16;mem[1855]=17;
        mem[1856]=16;mem[1857]=4;mem[1858]=6;
        mem[1859]=16;mem[1860]=16;mem[1861]=17;
        mem[1862]=-1;
        mem[1541]=1863;
        mem[1863]=5;mem[1864]=22;mem[1865]=22;
        mem[1866]=6;mem[1867]=11;mem[1868]=15;
        mem[1869]=6;mem[1870]=21;mem[1871]=23;
        mem[1872]=7;mem[1873]=9;mem[1874]=16;
        mem[1875]=7;mem[1876]=22;mem[1877]=23;
        mem[1878]=8;mem[1879]=8;mem[1880]=16;
        mem[1881]=8;mem[1882]=22;mem[1883]=23;
        mem[1884]=9;mem[1885]=6;mem[1886]=10;
        mem[1887]=9;mem[1888]=15;mem[1889]=17;
        mem[1890]=9;mem[1891]=22;mem[1892]=23;
        mem[1893]=10;mem[1894]=5;mem[1895]=9;
        mem[1896]=10;mem[1897]=16;mem[1898]=18;
        mem[1899]=10;mem[1900]=21;mem[1901]=23;
        mem[1902]=11;mem[1903]=4;mem[1904]=8;
        mem[1905]=11;mem[1906]=17;mem[1907]=22;
        mem[1908]=12;mem[1909]=4;mem[1910]=8;
        mem[1911]=12;mem[1912]=18;mem[1913]=22;
        mem[1914]=13;mem[1915]=7;mem[1916]=8;
        mem[1917]=13;mem[1918]=19;mem[1919]=21;
        mem[1920]=14;mem[1921]=7;mem[1922]=8;
        mem[1923]=14;mem[1924]=20;mem[1925]=20;
        mem[1926]=15;mem[1927]=6;mem[1928]=7;
        mem[1929]=16;mem[1930]=6;mem[1931]=7;
        mem[1932]=17;mem[1933]=6;mem[1934]=7;
        mem[1935]=18;mem[1936]=6;mem[1937]=7;
        mem[1938]=-1;
        mem[1542]=1939;
        mem[1939]=4;mem[1940]=19;mem[1941]=21;
        mem[1942]=5;mem[1943]=16;mem[1944]=22;
        mem[1945]=6;mem[1946]=14;mem[1947]=23;
        mem[1948]=7;mem[1949]=12;mem[1950]=18;
        mem[1951]=7;mem[1952]=22;mem[1953]=23;
        mem[1954]=8;mem[1955]=11;mem[1956]=15;
        mem[1957]=8;mem[1958]=23;mem[1959]=23;
        mem[1960]=9;mem[1961]=9;mem[1962]=13;
        mem[1963]=9;mem[1964]=15;mem[1965]=16;
        mem[1966]=9;mem[1967]=22;mem[1968]=23;
        mem[1969]=10;mem[1970]=7;mem[1971]=11;
        mem[1972]=10;mem[1973]=14;mem[1974]=16;
        mem[1975]=10;mem[1976]=22;mem[1977]=23;
        mem[1978]=11;mem[1979]=6;mem[1980]=10;
        mem[1981]=11;mem[1982]=14;mem[1983]=15;
        mem[1984]=11;mem[1985]=21;mem[1986]=22;
        mem[1987]=12;mem[1988]=5;mem[1989]=8;
        mem[1990]=12;mem[1991]=14;mem[1992]=15;
        mem[1993]=12;mem[1994]=20;mem[1995]=22;
        mem[1996]=13;mem[1997]=4;mem[1998]=7;
        mem[1999]=13;mem[2000]=14;mem[2001]=15;
        mem[2002]=13;mem[2003]=19;mem[2004]=21;
        mem[2005]=14;mem[2006]=4;mem[2007]=5;
        mem[2008]=14;mem[2009]=14;mem[2010]=21;
        mem[2011]=15;mem[2012]=14;mem[2013]=20;
        mem[2014]=16;mem[2015]=15;mem[2016]=19;
        mem[2017]=-1;
        mem[1543]=2018;
        mem[2018]=4;mem[2019]=11;mem[2020]=12;
        mem[2021]=5;mem[2022]=10;mem[2023]=12;
        mem[2024]=6;mem[2025]=8;mem[2026]=11;
        mem[2027]=7;mem[2028]=6;mem[2029]=10;
        mem[2030]=7;mem[2031]=21;mem[2032]=23;
        mem[2033]=8;mem[2034]=5;mem[2035]=9;
        mem[2036]=8;mem[2037]=19;mem[2038]=23;
        mem[2039]=9;mem[2040]=4;mem[2041]=7;
        mem[2042]=9;mem[2043]=16;mem[2044]=23;
        mem[2045]=10;mem[2046]=4;mem[2047]=6;
        mem[2048]=10;mem[2049]=14;mem[2050]=20;
        mem[2051]=11;mem[2052]=5;mem[2053]=6;
        mem[2054]=11;mem[2055]=12;mem[2056]=18;
        mem[2057]=12;mem[2058]=5;mem[2059]=6;
        mem[2060]=12;mem[2061]=10;mem[2062]=15;
        mem[2063]=13;mem[2064]=5;mem[2065]=5;
        mem[2066]=13;mem[2067]=8;mem[2068]=13;
        mem[2069]=14;mem[2070]=5;mem[2071]=11;
        mem[2072]=15;mem[2073]=5;mem[2074]=9;
        mem[2075]=16;mem[2076]=5;mem[2077]=7;
        mem[2078]=17;mem[2079]=5;mem[2080]=5;
        mem[2081]=-1;
        mem[1544]=2082;
        mem[2082]=4;mem[2083]=17;mem[2084]=22;
        mem[2085]=5;mem[2086]=7;mem[2087]=8;
        mem[2088]=5;mem[2089]=15;mem[2090]=23;
        mem[2091]=6;mem[2092]=6;mem[2093]=10;
        mem[2094]=6;mem[2095]=14;mem[2096]=23;
        mem[2097]=7;mem[2098]=5;mem[2099]=17;
        mem[2100]=7;mem[2101]=22;mem[2102]=23;
        mem[2103]=8;mem[2104]=5;mem[2105]=6;
        mem[2106]=8;mem[2107]=9;mem[2108]=15;
        mem[2109]=8;mem[2110]=22;mem[2111]=23;
        mem[2112]=9;mem[2113]=4;mem[2114]=5;
        mem[2115]=9;mem[2116]=11;mem[2117]=16;
        mem[2118]=9;mem[2119]=21;mem[2120]=23;
        mem[2121]=10;mem[2122]=4;mem[2123]=5;
        mem[2124]=10;mem[2125]=11;mem[2126]=23;
        mem[2127]=11;mem[2128]=4;mem[2129]=5;
        mem[2130]=11;mem[2131]=7;mem[2132]=12;
        mem[2133]=11;mem[2134]=15;mem[2135]=22;
        mem[2136]=12;mem[2137]=4;mem[2138]=11;
        mem[2139]=12;mem[2140]=17;mem[2141]=21;
        mem[2142]=13;mem[2143]=5;mem[2144]=10;
        mem[2145]=14;mem[2146]=5;mem[2147]=10;
        mem[2148]=15;mem[2149]=8;mem[2150]=9;
        mem[2151]=16;mem[2152]=8;mem[2153]=9;
        mem[2154]=17;mem[2155]=8;mem[2156]=8;
        mem[2157]=-1;
        mem[1545]=2158;
        mem[2158]=4;mem[2159]=12;mem[2160]=15;
        mem[2161]=5;mem[2162]=11;mem[2163]=16;
        mem[2164]=6;mem[2165]=10;mem[2166]=16;
        mem[2167]=7;mem[2168]=9;mem[2169]=12;
        mem[2170]=7;mem[2171]=15;mem[2172]=16;
        mem[2173]=8;mem[2174]=8;mem[2175]=10;
        mem[2176]=8;mem[2177]=15;mem[2178]=16;
        mem[2179]=8;mem[2180]=22;mem[2181]=24;
        mem[2182]=9;mem[2183]=7;mem[2184]=9;
        mem[2185]=9;mem[2186]=15;mem[2187]=16;
        mem[2188]=9;mem[2189]=19;mem[2190]=24;
        mem[2191]=10;mem[2192]=6;mem[2193]=8;
        mem[2194]=10;mem[2195]=14;mem[2196]=15;
        mem[2197]=10;mem[2198]=17;mem[2199]=24;
        mem[2200]=11;mem[2201]=6;mem[2202]=8;
        mem[2203]=11;mem[2204]=13;mem[2205]=22;
        mem[2206]=12;mem[2207]=5;mem[2208]=7;
        mem[2209]=12;mem[2210]=12;mem[2211]=19;
        mem[2212]=13;mem[2213]=5;mem[2214]=6;
        mem[2215]=13;mem[2216]=11;mem[2217]=16;
        mem[2218]=14;mem[2219]=5;mem[2220]=14;
        mem[2221]=15;mem[2222]=6;mem[2223]=12;
        mem[2224]=16;mem[2225]=7;mem[2226]=11;
        mem[2227]=17;mem[2228]=11;mem[2229]=11;
        mem[2230]=-1;

    End
Finish

/*
Begin
    Func(fib,x)
        If(x,<=,1)
            Return(1);
        End
        Var ret;
        ret=0;
        x--;
        ret+=Call(fib,x);
        x--;
        ret+=Call(fib,x);
        Return(ret);
    End
    Var i;
    i=0;
    Loop
        mem[i]=Call(fib,i);
        i++;
        If(i,==,18)
            Break
        End
    End
Finish
*/
/*
Begin
    Mem[0]=1;
    Mem[1]=1;
    Var i;
    i=2;
    Loop
        If(i,==,23)
            Break
        End
        Mem[i]=0;
        i++;
    End
    Func(fib,x)
        If(Mem[x],!=,0)
            Return(Mem[x]);
        End
        Var ret;
        ret=0;
        x--;
        ret+=Call(fib,x);
        x--;
        ret+=Call(fib,x);
        Return(ret);
    End
    i=2;
    Loop
        If(i,==,23)
            Break
        End
        mem[i]=Call(fib,i);
        i++;
    End
Finish
*/
/*
Begin
    Mem[2]=0;
    If(Mem[0],<,0)
        Mem[0]*=-1;
        Mem[1]*=-1;
    End
    Loop
        If(Mem[0],==,0)
            Break
        End
        Mem[2]+=Mem[1];
        Mem[0]--;
    End
Finish
*/
