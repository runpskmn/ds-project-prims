#include "graphics.h"
#include "vertex.h"
#include "edge.h"
#include "iostream"
#include "limits.h"
#include "fstream"
#include <vector>
#include "function.h"
#include <sstream>
#include <string>
#include <bits/stdc++.h>
#include "prims_algo.h"
using namespace std;

vector<Vertex> vertexs;
vector<Edge> edges;
Function func = Function();
int vertexNum = 0;
int mainScreen, secondScreen;
int clicked = 0;
string fileName = "input.txt";

void draw(){
    func.drawMenu(mainScreen);

    for(Vertex v : vertexs){
        v.draw();
    }

    for(Edge e : edges){
        e.draw();
    }
}

int findVertexIndex(){
     int index = -1;
     clearmouseclick(WM_LBUTTONDOWN);
     while(index == -1){
        if(ismouseclick(WM_LBUTTONDOWN)){
            for(int i=0;i<vertexs.size();++i){
                if(vertexs[i].inCircle(mousex(), mousey())){
                    cout << vertexs[i].getName();
                    vertexs[i].setSelect(true);
                    index = i;
                    break;
                }
            }
            if(index > -1){
                cleardevice();
                draw();
            }
        }
        clearmouseclick(WM_LBUTTONDOWN);
        delay(100);
    }
    return index;
}

int main(){
    int matrix[100][100];
    bool rft;
    char c;
    int startIndex;
    string myText;
    vector<string> str;
    ifstream MyReadFile(fileName);
    bool foundFile = false;

    while(!foundFile){
        cout << "Do you want to read from text file ? [y/n] : ";
        cin >> c;
        rft = toupper(c) == 'Y' ? true : false;

        if(!rft){
            foundFile = true;
            cout << "Enter number of vertex : ";
            cin >> vertexNum;

            cout << "\n=============== Enter your Adjacency matrix ==============" << endl;
            for(int row = 0;row < vertexNum;++row){
                for(int col = 0;col < vertexNum;++col){
                    cin >> matrix[row][col];
                }
            }
        }else{
            if (MyReadFile) {
                foundFile = true;
                while(getline(MyReadFile, myText)){
                    str = func.split(myText, ' ');
                    if(str.size() > 1){
                        for(int i = 0;i<str.size();++i){
                            matrix[vertexNum][i] = stoi(str[i]);
                        }
                        vertexNum++;
                    }else{
                        startIndex = stoi(myText)-1;
                    }
                }
                cout << "\n========== Your Adjacency matrix from text file.==========" << endl;
                for(int row = 0;row < vertexNum;++row){
                    for(int col = 0;col < vertexNum;++col){
                        cout << matrix[row][col] << " ";
                    }
                    cout  << endl;
                }
            }else{
                cout << "File " << fileName << " doesn't exists" << endl;
            }
        }
    }

    mainScreen = initwindow(1200, 800, "Graph");
    setcurrentwindow(mainScreen);
    draw();
    cout << "\n==================== Create the graph ====================" << endl;
    char vName[15];
    int temp = -1;
    while(clicked < vertexNum){
        if(clicked != temp)
    printf(" - Press on Graph interface to create vertex v%d : ",clicked+1);

        if(ismouseclick(WM_LBUTTONDOWN)){
            int posX =  mousex();
            int posY =  mousey();
            if(posX >= 0 && posX < 900){
                sprintf(vName, "v%d", clicked+1);
                vertexs.push_back(Vertex(posX, posY, vName));
                draw();
                clicked++;
                cout << "created." << endl;
            }
            clearmouseclick(WM_LBUTTONDOWN);
        }else
            temp = clicked;
        delay(100);
    }

    for(int row=0;row<vertexNum;++row){
        for(int col = row;col < vertexNum;++col){
            if(matrix[row][col] >= 1){
                edges.push_back(Edge(vertexs[row], vertexs[col], matrix[row][col]));
            }
        }
    }


    cout << "=========== The graph was created successfully ===========" << endl << endl;
    if(rft)
        cout << "Start vertex : " << vertexs[startIndex].getName() << endl;
    cleardevice();
    draw();
    func.drawInfo(vertexs.size(), edges.size(), 0, mainScreen);

    while(true){
        if(GetAsyncKeyState(VK_SHIFT) && GetAsyncKeyState('E')){
            cout << "==================== Edit edge weight ====================" << endl;
            int source, dest, temp;
            int index = -1;
            cout << "Click at source vertex : ";
            source = findVertexIndex();
            cout << endl;
            cout << "Click at destination vertex : ";
            dest = findVertexIndex();
            cout << endl;
            if(dest < source){
                temp = dest;
                dest = source;
                source = temp;
            }
            for(int i=0;i<edges.size();++i){
                if(edges[i].inLine(vertexs[source], vertexs[dest])){
                    index = i;
                    break;
                }
            }
            if(index == -1){
                cout << "Wrong vertex. Please try again." << endl;
                vertexs[source].setSelect(false);
                vertexs[dest].setSelect(false);
                cleardevice();
                draw();
                func.drawInfo(vertexs.size(), edges.size(), edges.size()*2, mainScreen);
            }else{
                vertexs[source].setSelect(false);
                vertexs[dest].setSelect(false);
                edges[index].setSelect(true);
                cleardevice();
                draw();
                func.drawInfo(vertexs.size(), edges.size(), edges.size(), mainScreen);

                cout << "Enter new weight : ";
                int newWeight;
                cin >> newWeight;
                edges[index].setWeight(newWeight);
                edges[index].setSelect(false);
                cleardevice();
                draw();
                func.drawInfo(vertexs.size(), edges.size(), edges.size(), mainScreen);
            }

        }else if(GetAsyncKeyState(VK_SHIFT) && GetAsyncKeyState('R')){
            cout << "==================== Edit vertex name ====================" << endl;
            cout << "Click at vertex to edit : ";
            int index = findVertexIndex();
            cout << endl;
            char name[100];
            cout << "Enter new name : ";
            cin >> name;
            for(int i=0;i<edges.size();++i){
                Vertex vA = edges[i].getVertexA();
                Vertex vB = edges[i].getVertexB();
                Vertex newV = vertexs[index];
                newV.setName(name);
                if(strcmp(vA.getName(), vertexs[index].getName()) == 0){
                    edges[i].setVertexA(newV);
                }
                if(strcmp(vB.getName(), vertexs[index].getName()) == 0){
                    edges[i].setVertexB(newV);
                }
            }
            vertexs[index].setName(name);
            vertexs[index].setSelect(false);
            cleardevice();
            draw();
            func.drawInfo(vertexs.size(), edges.size(), edges.size(), mainScreen);
        }else if(ismouseclick(WM_LBUTTONDOWN)){
            int x = mousex();
            int y = mousey();
            clearmouseclick(WM_LBUTTONDOWN);
            if(x >= 600 && x <= 1190 && y >= 710 && y <= 740){
                cout << "==================== Prim's Algorithm ====================" << endl;
                Prims p = Prims(vertexs, edges);
                if(!rft){
                    cout << "Click on vertex to select begin vertex : ";
                    startIndex = findVertexIndex();
                    cout << endl;
                    vertexs[startIndex].setSelect(false);
                    draw();
                }
                char minSum[50];
                int sum = p.primsAlgo(startIndex, 0);
                sprintf(minSum, "Minimum spanning tree : %d", sum);
                cout << "Minimum spanning tree : " << sum << endl;
                secondScreen = initwindow((vertexs.size()+1)*60+80, (vertexs.size()+1)*40+100, "Show Table", 0, 0, false, false);
                p.draw(mainScreen, secondScreen, minSum);
                setcurrentwindow(mainScreen);
                closegraph(secondScreen);
                cleardevice();
                draw();
                func.drawInfo(vertexs.size(), edges.size(), edges.size()*2, mainScreen);
                cout << "Finished." << endl;
            }else if(x >= 600 && x <= 1190 && y >= 670 && y <= 700){
                func.saveToImage(mainScreen, 0, 0, 895, 800, "graph.jpg");
            }else if(x >= 900 && x <= 1050 && y >= 750 && y <= 780){
                cout << "==================== Re-draw the graph ===================" << endl;
                cleardevice();
                func.drawMenu(mainScreen);
                vertexs.clear();
                edges.clear();
                clicked = 0;
                char vName[15];
                int temp = -1;
                while(clicked < vertexNum){
                    if(clicked != temp)
                printf(" - Press on Graph interface to create vertex v%d : ",clicked+1);

                    if(ismouseclick(WM_LBUTTONDOWN)){
                        int posX =  mousex();
                        int posY =  mousey();
                        if(posX >= 0 && posX < 900){
                            sprintf(vName, "v%d", clicked+1);
                            vertexs.push_back(Vertex(posX, posY, vName));
                            draw();
                            clicked++;
                            cout << "created." << endl;
                        }
                        clearmouseclick(WM_LBUTTONDOWN);
                    }else
                        temp = clicked;
                    delay(100);
                }

                for(int row=0;row<vertexNum;++row){
                    for(int col = row;col < vertexNum;++col){
                        if(matrix[row][col] >= 1){
                            edges.push_back(Edge(vertexs[row], vertexs[col], matrix[row][col]));
                        }
                    }
                }


                cout << "=========== The graph was created successfully ===========" << endl << endl;
                cleardevice();
                draw();
                func.drawInfo(vertexs.size(), edges.size(), 0, mainScreen);
            }else if(x >= 1060 && x <= 1190 && y >= 750 && y <= 780){
                if(!rft){
                    cleardevice();
                    func.drawMenu(mainScreen);
                    cout << "Enter number of vertex : ";
                    cin >> vertexNum;

                    cout << "\n=============== Enter your Adjacency matrix ==============" << endl;
                    for(int row = 0;row < vertexNum;++row){
                        for(int col = 0;col < vertexNum;++col){
                            cin >> matrix[row][col];
                        }
                    }

                    vertexs.clear();
                    edges.clear();
                    clicked = 0;
                    char vName[15];
                    int temp = -1;
                    while(clicked < vertexNum){
                        if(clicked != temp)
                    printf(" - Press on Graph interface to create vertex v%d : ",clicked+1);

                        if(ismouseclick(WM_LBUTTONDOWN)){
                            int posX =  mousex();
                            int posY =  mousey();
                            if(posX >= 0 && posX < 900){
                                sprintf(vName, "v%d", clicked+1);
                                vertexs.push_back(Vertex(posX, posY, vName));
                                draw();
                                clicked++;
                                cout << "created." << endl;
                            }
                            clearmouseclick(WM_LBUTTONDOWN);
                        }else
                            temp = clicked;
                        delay(100);
                    }

                    for(int row=0;row<vertexNum;++row){
                        for(int col = row;col < vertexNum;++col){
                            if(matrix[row][col] >= 1){
                                edges.push_back(Edge(vertexs[row], vertexs[col], matrix[row][col]));
                            }
                        }
                    }


                    cout << "=========== The graph was created successfully ===========" << endl << endl;
                    cleardevice();
                    draw();
                    func.drawInfo(vertexs.size(), edges.size(), 0, mainScreen);
                }else{
                    cout << "Read file from text file can't to use this function." << endl;
                }
            }
        }
    }

    getch();
}
