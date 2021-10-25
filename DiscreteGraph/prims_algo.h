
using namespace std;

class Prims{
private :
    vector<string> str;
    int *usedVertex;
    int *key;
    int *parent;
    vector<string> tree;
    vector<Vertex> vertexs;
    vector<Edge> edges;
    vector<string> vName;
    int vSize;
    int eSize;
    Function func;

public :
    Prims(){};

    Prims(vector<Vertex> vertexs, vector<Edge> edges){
        this->vertexs = vertexs;
        this->edges = edges;
        this->vSize= vertexs.size();
        this->eSize = edges.size();
        this->usedVertex = new int[vSize];
        this->key = new int[vSize];
        this->parent = new int[vSize];
        this->func = Function();
        for(int i=0;i<vSize;++i){
            usedVertex[i] = 1;
            key[i] = INT_MAX;
            parent[i] = -1;
        }
    }

    int primsAlgo(int index, int round){
        vName.push_back(vertexs[index].getName());
        if(round == vSize-1)
            return 0;

        int min = INT_MAX;
        usedVertex[index] = 0;
        string message = "";
        for(Edge e : edges){
            int vIndex = -1;
            int weight;
            char *vName = vertexs[index].getName();
            if(strcmp(e.getVertexA().getName(), vName) == 0){
                vIndex = vertexIndex(e.getVertexB());
                weight = e.getWeight();
            }else if(strcmp(e.getVertexB().getName(), vName) == 0){
                vIndex = vertexIndex(e.getVertexA());
                weight = e.getWeight();
            }

            if(vIndex > -1 && weight < key[vIndex]){
                key[vIndex] = weight;
                parent[vIndex] = index;
            }
        }

        for(int i=0;i<vSize;++i){
            if(key[i] <= min && usedVertex[i] != 0 && parent[i] != -1){
                min = key[i];
                index = i;
            }
        }
        tree.push_back(to_string(parent[index]) + " " + to_string(index));

        for(int i=0;i<vSize;++i){
            if(usedVertex[i] == 0)
                message += "-|";
            else if(key[i] == INT_MAX)
                message += "infinity|";
            else
                message += to_string(key[i]) + ", " + vertexs[parent[i]].getName() + "|";
        }
        str.push_back(message);

        return min + primsAlgo(index, round+1);
    }

    int vertexIndex(Vertex v){
        int index = 0;
        for(int i=0;i<vSize;++i){
            if(strcmp(vertexs[i].getName(), v.getName()) == 0){
                index = i;
                break;
            }
        }
        return index;
    }

    void draw(int mainScreen, int secondScreen, char* minSum){
        int round = -1;
        bool isExit = false;
        bool vHilight[vSize+1][vSize];
        bool eHilight[eSize+1][eSize];
        for(int row=0;row<vSize;++row){
            for(int col=0;col<vSize;++col){
                vHilight[row][col] = false;

            }
        }

        for(int row=0;row<eSize;++row){
            for(int col=0;col<eSize;++col){
                eHilight[row][col] = false;
            }
        }

        while(true){
            if(isExit)
                break;
            setcurrentwindow(secondScreen);
            setlinestyle(0, 0, 3);
            setcolor(LIGHTGREEN);
            rectangle(150, (vSize+1)*40+30, 250, (vSize+1)*40+60);
            setcolor(LIGHTRED);
            rectangle((vSize+1)*60-60, (vSize+1)*40+30, (vSize+1)*60+40, (vSize+1)*40+60);
            setcolor(LIGHTGRAY);
            outtextxy((vSize+1)*60-45, (vSize+1)*40+37, "     EXIT       ");

            if(round == -1){
                setcolor(LIGHTGRAY);
                rectangle(40, (vSize+1)*40+30, 140, (vSize+1)*40+60);
                outtextxy(72, (vSize+1)*40+37, "BACK");
                outtextxy(160, (vSize+1)*40+37, "     START     ");
            }else{
                setcolor(LIGHTGREEN);
                rectangle(40, (vSize+1)*40+30, 140, (vSize+1)*40+60);
                setcolor(LIGHTGRAY);
                outtextxy(163, (vSize+1)*40+37, "NEXT STEP");
                outtextxy(72, (vSize+1)*40+37, "BACK");
            }

            if(round >= vSize-2){
                setcolor(LIGHTBLUE);
                rectangle(260, (vSize+1)*40+30, 373, (vSize+1)*40+60);
                setcolor(LIGHTGRAY);
                outtextxy(265, (vSize+1)*40+37, "SAVE TO IMAGE");

                setcurrentwindow(mainScreen);
                setcolor(LIGHTBLUE);
                outtextxy(40, 760, minSum);
            }
            setcurrentwindow(secondScreen);

            while(ismouseclick(WM_LBUTTONDOWN)){
                int x = mousex();
                int y = mousey();
                clearmouseclick(WM_LBUTTONDOWN);
                setcurrentwindow(mainScreen);
                if(x >= 40 && x <= 140 && y >= (vSize+1)*40 && y <= (vSize+1)*40+60 && round > -1){ //CLICK BACK BUTTON
                    round--;
                }else if(x >= 150 && x <= 250 && y >= (vSize+1)*40 && y <= (vSize+1)*40+60 && round < vSize){ //CLICK NEXT BUTTON
                    round++;
                    if(round > -1){
                        for(int i=0;i<vSize;++i)
                            vHilight[round+1][i] = vHilight[round][i];

                        for(int i=0;i<eSize;++i)
                            eHilight[round+1][i] = eHilight[round][i];

                    }
                }else if(x >= (vSize+1)*60-60 && x <= (vSize+1)*60+40 && y >= (vSize+1)*40 && y <= (vSize+1)*40+60){ //CLICK EXIT BUTTON
                    isExit = true;
                }else if(x >= 260 && x <= 425 && y >= (vSize+1)*40 && y <= (vSize+1)*40+60 && round >= vSize-2){ //CLICK SAVE TO IMAGE BUTTON
                    func.saveToImage(mainScreen, 0, 0, 895, 800, "graphPrims.jpg");
                    func.saveToImage(secondScreen, 0, 25, (vSize+1)*60+80, (vSize+1)*40+15, "table.jpg");
                }else
                    continue;
                if(round >= -1 && round < vSize-1){
                    if(round > -1){
                        vector<string> vTarget = func.split(tree[round], ' ');
                        int vIndex1 = stoi(vTarget[0]);
                        int vIndex2 = stoi(vTarget[1]);
                        int temp;
                        if(vIndex1 > vIndex2){
                            temp = vIndex1;
                            vIndex1 = vIndex2;
                            vIndex2 = temp;
                        }


                        vHilight[round+1][vIndex1] = true;
                        vHilight[round+1][vIndex2] = true;
                        for(int i=0;i<eSize;++i){
                            if(strcmp(edges[i].getVertexA().getName(), vertexs[vIndex1].getName()) == 0 && strcmp(edges[i].getVertexB().getName(), vertexs[vIndex2].getName()) == 0){
                                eHilight[round+1][i] = true;
                                break;
                            }
                        }
                    }
                    cleardevice();
                    func.drawMenu(mainScreen);
                    for(Vertex v : vertexs)
                        v.draw();

                    for(Edge e : edges)
                        e.draw();

                    /* DRAW GRAPH PATH */
                    for(int i=0;i<vSize;++i){
                        if(vHilight[round+1][i])
                            vertexs[i].draw(true);
                    }

                    for(int i=0;i<eSize;++i){
                        if(eHilight[round+1][i])
                            edges[i].draw(true);
                    }

                    /* DRAW TABLE */
                    setcurrentwindow(secondScreen);
                    cleardevice();
                    for(int i=1;i<=round+2;++i){
                        rectangle(40,i*40,(vSize+1)*60+40,i*40+40);
                    }

                    for(int i=100,j=0;i<(vSize+1)*60+40+60;i+=60,j++){
                        if(i == 100)
                            outtextxy(i-35,50,"N");
                        else
                            outtextxy(i-40,50,vertexs[j-1].getName());

                        for(int j=1;j<=round+2;++j)
                            line(i,j*40,i,j*40+40);
                    }

                    /* DRAW TEXT TO TABLE */
                    for(int count=0;count<round+1;++count){
                        int msgID =0;
                        vector<string> msg = func.split(str[count], '|');
                        char * c = new char [vName[count].length()+1];
                        strcpy (c, vName[count].c_str());
                        for(int i=100,j=0;i<(vSize+1)*60+40+60;i+=60,j++){
                            if(i==100){
                                outtextxy(i-55, (count+2)*40+10,c);
                            }else{
                                strcpy (c, msg[msgID].c_str());
                                outtextxy(i-55,(count+2)*40+10, c);
                                msgID++;
                            }
                        }
                    }

                }

            }
        }
    }

};
