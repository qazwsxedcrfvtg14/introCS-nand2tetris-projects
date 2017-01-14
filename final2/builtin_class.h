class Output{
    public:
    static const int Gray_Mask=50;
    static Var Init(){
        return Call(Output_Init);
        }
    static Var Clean(){
        return Call(Output_Clean);
        }
    static Var Update(){
        return Call(Output_Update);
        }
    template<typename T0,typename T1,typename T2,typename T3,typename T4>
    static Var DrawRect(T0 x1, T1 x2, T2 y1, T3 y2, T4 col){
        return Call(Output_DrawRect,x1,x2,y1,y2,col);
        }
    template<typename T0,typename T1,typename T2>
    static Var DrawVerticalLine(T0 x, T1 y1, T2 y2){
        return Call(Output_DrawVerticalLine,x,y1,y2);
        }
    template<typename T0,typename T1,typename T2>
    static Var DrawNumber(T0 n, T1 x, T2 y){
        return Call(Output_DrawNumber,n,x,y);
        }
    };

class Input{
    public:
    static void Update(){
        If(mem[KBD],!=,0)
            Global["KBD"]=mem[KBD];
        End
        }
    static void Clean(){
        Global["KBD"]=0;
        }
    static obj Key(){
        return Global["KBD"];
        }
    static Var WaitEnter(){
        return Call(Input_WaitEnter);
        }
    };
class Math{
    public:
        static void Init(){
            mem[0] = 1;
            mem[1] = 2;
            mem[2] = 4;
            mem[3] = 8;
            mem[4] = 16;
            mem[5] = 32;
            mem[6] = 64;
            mem[7] = 128;
            mem[8] = 256;
            mem[9] = 512;
            mem[10] = 1024;
            mem[11] = 2048;
            mem[12] = 4096;
            mem[13] = 8192;
            mem[14] = 16384;
            mem[15] = -32768;
            }
        template<typename T0,typename T1>
        static Var Bit(T0 x,T1 n){
            return Call(Math_Bit,x,n);
            }
        template<typename T0>
        static Var TwoToThe(T0 n){
            return Call(Math_TwoToThe,n);
            }
        template<typename T0>
        static Var Abs(T0 x){
            return Call(Math_Abs,x);
            }
        template<typename T0,typename T1>
        static Var LeftShift(T0 x,T1 y){
            return Call(Math_LeftShift,x,y);
            }
        template<typename T0>
        static Var Lowbit(T0 x){
            return Call(Math_Lowbit,x);
            }
        template<typename T0,typename T1>
        static Var Xor(T0 x,T1 y){
            return Call(Math_Xor,x,y);
            }
        template<typename T0,typename T1>
        static Var Multiply(T0 x,T1 y){
            return Call(Math_Multiply,x,y);
            }
        template<typename T0,typename T1>
        static Var Divide(T0 x,T1 y){
            return Call(Math_Divide,x,y);
            }
        template<typename T0,typename T1>
        static Var Mod(T0 x,T1 y){
            return Call(Math_Mod,x,y);
            }
        template<typename T0,typename T1>
        static Var Max(T0 x,T1 y){
            return Call(Math_Max,x,y);
            }
        template<typename T0,typename T1>
        static Var Min(T0 x,T1 y){
            return Call(Math_Min,x,y);
            }
    };

void obj::operator*=(int x){
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
        Math::Divide(*this,x).toD();
        put("@"+ToStr(id));
        run_star();
        put("M=D");
        return;
        //throw "error: *= only support -1,0,1";
        }
    }
void obj::operator*=(const obj &x){
    Math::Multiply(*this,x).toD();
    put("@"+ToStr(id));
    run_star();
    put("M=D");
    return;
    }
void obj::operator/=(int x){
    Math::Divide(*this,x).toD();
    put("@"+ToStr(id));
    run_star();
    put("M=D");
    }
void obj::operator/=(const obj &x){
    Math::Divide(*this,x).toD();
    put("@"+ToStr(id));
    run_star();
    put("M=D");
    }
class Array{
    private:
        static const int mask11=-16384;
        static const int umask11=16383;
        static const int mask10=-32768;
        static const int umask10=32767;
        static const int mask01=16384;
        static const int umask01=-16385;
    public:
    static void Init(){
        mem[Array_Pool_Begin]=(Array_Pool_Size-2)|mask01;
        mem[Array_Pool_Begin+Array_Pool_Size-1]=0x3fff|mask10;
        }
    template<typename T0>
    static Var Alloc(T0 size){
        return Call(Array_Alloc,size);
        }
    template<typename T0>
    static void Free(T0 p){
        Call(Array_Free,p);
        }
    };
