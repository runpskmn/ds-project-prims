class Edge{
private:
    int weight;
    Vertex a;
    Vertex b;
    bool isSelect = false;

public:
    Edge(){};

    Edge(Vertex a, Vertex b, int weight){
        this->a = a;
        this->b = b;
        this->weight = weight;
    }

    void setWeight(int weight){
        this->weight = weight;
    }

    int getWeight(){
        return weight;
    }

    Vertex getVertexA(){
        return a;
    }

    Vertex getVertexB(){
        return b;
    }

    Vertex getOppVertex(Vertex v){
        return strcmp(v.getName(), a.getName()) == 0 ? a : b;
    }

    bool isLoop(){
        return strcmp(a.getName(), b.getName()) == 0 ? true : false;
    }

    void setVertexA(Vertex v){
        this->a = v;
    }

    void setVertexB(Vertex v){
        this->b = v;
    }

    bool inLine(Vertex a, Vertex b){
        if(strcmp(this->a.getName(), a.getName()) == 0 && strcmp(this->b.getName(), b.getName()) == 0){
            isSelect = true;
            return true;
        }else{
            isSelect = false;
            return false;
        }
    }

    void setSelect(bool isSelect){
        this->isSelect = isSelect;
    }

    void draw(){
        setcolor(isSelect ? RED : LIGHTBLUE);
        setlinestyle(0,0,3);
        settextstyle(10, 0, 2);
        char text[10];
        sprintf(text, "%d", weight);
        if(isLoop()){
            ellipse(a.getX(), a.getY(), 0, 180, 10, 35);
            outtextxy( a.getX()-3 , a.getY()-60, text);
        }else{
            line(a.getX(), a.getY(), b.getX(), b.getY());
            outtextxy((a.getX() + b.getX())/2 ,((a.getY() + b.getY())/2)+5, text);
        }
    }

    void draw(bool hilight){
        setcolor(RED);
        setlinestyle(0,0,3);
        settextstyle(10, 0, 2);
        char text[10];
        sprintf(text, "%d", weight);
        if(isLoop()){
            ellipse(a.getX(), a.getY(), 0, 180, 10, 35);
            outtextxy( a.getX()-3 , a.getY()-60, text);
        }else{
            line(a.getX(), a.getY(), b.getX(), b.getY());
            outtextxy((a.getX() + b.getX())/2 ,((a.getY() + b.getY())/2)+5, text);
        }
    }
};


