
using namespace std;
class Function{
public:
    Function(){}

    void drawMenu(int mainScreen){
        setcurrentwindow(mainScreen);
        setcolor(WHITE);
        setlinestyle(0,0,3);
        rectangle(900, 10, 1190, 460);
        settextstyle(10, 0, 3);
        outtextxy(980, 15, "HOW TO USE");
        settextstyle(3, 0, 1);
        outtextxy(910, 55, " - Click on this interface to create a");
        outtextxy(910, 75, "    vertex.");
        outtextxy(910, 105, " - Click at 'PRIM'S ALGORITHM' button");
        outtextxy(910, 125, "    to find minimum spanning tree with");
        outtextxy(910, 145, "    Prim's Algorithm.");
        outtextxy(910, 175, " - Press Shift+E to change edge weight.");
        outtextxy(910, 195, "    Click at source vertex and destination");
        outtextxy(910, 215, "    vertex of edge do you want to");
        outtextxy(910, 235, "    change, then enter new weight on");
        outtextxy(910, 255, "    console.");
        outtextxy(910, 285, " - Press Shift+R to rename vertex.");

        rectangle(900, 470, 1190, 660);
        settextstyle(10, 0, 3);
        outtextxy(975, 485, "GRAPH INFO.");


        settextstyle(3, 0, 1);
        setcolor(RGB(135,206,250));
        rectangle(900, 670, 1190, 700);
        outtextxy(965, 677, "SAVE GRAPH TO IMAGE");

        setcolor(LIGHTGREEN);
        rectangle(900, 710, 1190, 740);
        outtextxy(972, 717, "PRIM'S ALGORITHM");

        setcolor(RGB(255,160,122));
        rectangle(900, 750, 1050, 780);
        outtextxy(905, 757, "RE-DRAW GRAPH");

        setcolor(LIGHTRED);
        rectangle(1060, 750, 1190, 780);
        outtextxy(1075, 757, "NEW GRAPH");
    }

    void drawInfo(int vNum, int eNum, int sum, int screen){
        setcurrentwindow(screen);

        char text[100];
        settextstyle(3, 0, 1);
        setcolor(LIGHTBLUE);
        sprintf(text, "Vertex : %d",vNum);
        outtextxy(910, 515, text);
        sprintf(text, "Edge : %d", eNum);
        outtextxy(910, 545, text);
        sprintf(text, "Sum of degrees : %d", eNum*2);
        outtextxy(910, 575, text);
    }

    vector<string> split (const string &s, char delim) {
        vector<string> result;
        stringstream ss (s);
        string item;

        while (getline (ss, item, delim)) {
            result.push_back (item);
        }

        return result;
    }

    void saveToImage(int screenID, int x1, int y1, int x2, int y2, char *fileName){
        setcurrentwindow(screenID);
        writeimagefile(fileName, x1, y1, x2, y2);
        cout << "save image successful." << endl;
    }
};

