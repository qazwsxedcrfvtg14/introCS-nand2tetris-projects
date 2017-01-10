class Output{
    public:
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
    static Var WaitEnter(){
        return Call(Input_WaitEnter);
        }
    };
