class Snake{
    private:
    static void Title(){
        Call(Snake_Title);
        }
    static void GameOver(){
        Call(GameOver,Global["score"]);
        }
    public:
    static void Main(){
        for(int i=0;i<16;i++)
            Mem[i]=-(1<<i);
        Mem[16]=-1;
        for(int i=0;i<15;i++)
            Mem[i+16]=(1<<i+1)-1;
        Mem[31]=-1;
        for(int i=0;i<32;i++)
            Mem[(i<<4)+32]=i;
        Output::Init();
        Snake::Title();
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
                Output::Clean();
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
                    Output::DrawRect(x,xx,y,yy,1);
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
                Output::DrawRect(x,xx,y,yy,1);
                Output::Update();
            End
            Snake::GameOver();
        End
        }
    };
