#include "pb071_io.h"
#include <stdio.h>
#include <stdlib.h>

void drawLine(int length,char fill);
void drawSquare(int size, char fill);
void drawRectangle(int a,int b,char fill);
void drawCircle(int radius, char fill, char space);
void drawEllipse(int aAxis,int bAxis, char fill, char space);
int typeLength();
int typeFill();
int isPrintable(char c){
    return c>=0x21&&c<=0x7e;
}
int subMain(void);

int main(void){
    while(subMain()){
    }
    return 0;
}

int subMain(void)
{
    int length, width, wantLength = 0, wantSpace = 0;
    char fill, space, shape;
    char* shapeName;

    printf("Vyberte obrazec, ktery bude vykreslen: ");
    int ret = scanf(" %c", &shape);
    if(ret == EOF){
        puts("Uzivatel ukoncil vstup");
        return 0;
    }
    if(ret != 1){
        puts("chyba vstupu");
        return 0;
    }
    switch (shape){
    case 'l':
        shapeName = "Cara";
        break;
    case 's':
        shapeName = "Ctverec";
        break;
    case 'r':
        shapeName = "Obdelnik";
        wantLength = 1;
        break;
    case 'c':
        shapeName = "Kruh";
        wantSpace = 1;
        break;
    case 'e':
        shapeName = "Elipsa";
        wantLength = 1;
        wantSpace = 1;
        break;
    case 'h':
        printf("Existujici obrazce:\n l - cara\n s - ctverec\n r - obdelnik\n");
        printf("c - kruh\n e - elipsa\n h - vypise tuto napovedu\n q - ukonci tento program\n");
        return 1;
    case 'q':
        puts("Program bude ukoncen.");
        return 0;
    default:
        printf("Neplatny vstup: %c\n", shape);
        return 1;
    }
    printf("Kreslenym obrazcem bude %s\n",shapeName);
    if(wantLength){
        printf("Zadej delku: ");
        length = typeLength();
    }
    printf("Zadej sirku: ");
    width = typeLength();
    printf("Zadej znak vyplne: ");
    fill = typeFill();
    if(wantSpace){
        printf("Zadej znak okoli: ");
        space = typeFill();
    }
    switch (shape){
    case 'l':
        drawLine(width,fill);
        break;
    case 's':
        drawSquare(width,fill);
        break;
    case 'r':
        drawRectangle(length,width,fill);
        break;
    case 'c':
        drawCircle(width,fill,space);
        break;
    case 'e':
        drawEllipse(length,width,fill,space);
        break;
    default:
        return 0;
    }

    return 1;
}

void drawLine(int length, char fill){
    for(;length>0;length--){
        putchar(fill);
    }
    putchar('\n');
}

void drawSquare(int size, char fill){
    drawRectangle(size,2*size,fill);
}

void drawRectangle(int a,int b,char fill){
    for(;a>0;a--){
        drawLine(b,fill);
    }
}

int typeLength(){
    int a;
    do{
        a = readInt();
        if(a<0) printf("Zaporna delka: %d. Zadej znovu: ",a);
    }while(a<0);
    return a;
}

int typeFill(){
    char c;
    do{
        readEndOfLine();
        c = readChar();
        if(!isPrintable(c)) printf("Netisknutelny znak: %x. Zadej znovu: ",c);
    }while(!isPrintable(c));
    return c;
}

void drawCircle(int width, char fill, char space){
    for(double i=-width/2;i<width/2;i++){
        for(double j=-width;j<=width;j++){
            if(i*i+j*j/4<width*width/4) putchar(fill);
            else putchar(space);
        }
        putchar('\n');
    }
}

void drawEllipse(int aAxis, int bAxis, char fill, char space){
    for(double i=-aAxis/2;i<=aAxis/2;i++){
        for(double j=-bAxis;j<=bAxis;j++){
            if((i*i)/aAxis+(j*j)/(4*bAxis)<=4) putchar(fill);
            else putchar(space);
        }
        putchar('\n');
    }
}
