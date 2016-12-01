// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/04/Mult.asm

// Multiplies R0 and R1 and stores the result in R2.
// (R0, R1, R2 refer to RAM[0], RAM[1], and RAM[2], respectively.)

// Put your code here.

//R2=0
//if(R1<0)R3=-R0,R4=-R1
//else R3=R0,R4-R1
//for(int i=0;i<R4;i++)
//  R2+=R4
@2
M=0

@1
D=M
@IFTRUE
D;JGE
@IFFALSE
0;JMP

(IFTRUE)
@0
D=M
@3
M=D
@1
D=M
@4
M=D
@IFEND
0;JMP

(IFFALSE)
@0
D=M
@3
M=-D
@1
D=M
@4
M=-D
(IFEND)

@i
M=0
(LOOPBEGIN)
@i
D=M
@4
D=D-M
@LOOPEND
D;JGE

@3
D=M
@2
M=D+M
@i
M=M+1
@LOOPBEGIN
0;JMP
(LOOPEND)
@LOOPEND
0;JMP