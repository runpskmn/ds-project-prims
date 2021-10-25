#include "graphics.h"

class Vertex{
private :
    int posX, posY;
    char name[10];
    bool isSelect = false;

public :
    Vertex(){}

    Vertex(int posX, int posY, char *name){
        this->posX = posX;
        this->posY = posY;
        strcpy(this->name, name);
    }

    int getX(){ return posX; }

    int getY(){ return posY; }

    char* getName(){
        return name;
    }

    void setName(char *name){
        strcpy(this->name, name);
    }

    bool inCircle(int x, int y){
        if(x >= posX-15 && x <= posX+15 && y >= posY-15 && y <= posY+15)
            return true;
        else
            return false;

    }

    void setSelect(bool isSelect){
        this->isSelect = isSelect;
    }

    void draw(){
        setcolor(isSelect ? RED : LIGHTBLUE);
        circle(posX ,posY, 15);
        setfillstyle(SOLID_FILL,isSelect ? RED : LIGHTBLUE);
        floodfill(posX, posY, isSelect ? RED : LIGHTBLUE);
        settextstyle(10, 0, 2);
        setcolor(WHITE);
        outtextxy(posX-strlen(name)*5,posY+20,name);
    }

    void draw(bool hilight){
        setcolor(RED);
        setlinestyle(0,0,5);
        circle(posX ,posY, 15);
        setfillstyle(SOLID_FILL,RED);
        floodfill(posX, posY, RED);
        settextstyle(10, 0, 2);
        setcolor(WHITE);
        outtextxy(posX-strlen(name)*5,posY+20,name);
    }
};

