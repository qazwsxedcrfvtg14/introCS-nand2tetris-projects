#include"compiler.h"
#include"builtin_class.h"
Begin
    #include"builtin_lib.h"
    Output::Init();
    Math::Init();
    Array::Init();
    //Func
    /*Var p,p2;
    p=Array::Alloc(8);
    mem[0]=p;
    p2=Array::Alloc(8);
    mem[1]=p2;
    Array::Free(p);
    p=Array::Alloc(8);
    mem[3]=p;
    Array::Free(p2);
    Array::Free(p);
    */

    mem[20]=87;
    mem[21]=8;
    mem[22]=Math::Mod(mem[20],mem[21]);
    mem[20]/=mem[21];
    mem[23]=Math::Max(mem[20],mem[21]);
    mem[24]=Math::Min(mem[21],mem[20]);
Finish
