#include "header.hpp"
void writeFile(string filename) {
    ofstream file(filename);
    int ind=0;
    for (vector<char> i:dat) {
        ind++;
        for (char j:i) {
            file<<j;
        } 
        if (ind!=dat.size()) file<<endl;
    }
    file.close();
}
bool handleKeys(string &f) {
    windowSize=getConsoleSize();
    char x=_getch();
    if (x==3) {
        return false;
    } else if (x==19) { 
        writeFile(f);
    } else if (x<=0) {
        while (x<=0) x=_getch();
        switch (x) {
            case 72: if (curpos[0]!=0) {
                curpos[0]--; 
                int min=savePos>dat[curpos[0]].size()?dat[curpos[0]].size():savePos;
                if (curpos[1]>min) {
                    curpos[1]=min;
                } else if (curpos[1]<min) {
                    curpos[1]=min;
                }
            } break;
            case 75:
                if (curpos[1]!=0) {
                    curpos[1]--;
                } else if (curpos[0]!=0) {
                    curpos[0]--;
                    curpos[1]=dat[curpos[0]].size();
                } savePos=curpos[1];break;
            case 80: if (curpos[0]+1<dat.size()) {
                curpos[0]++;
                int min=savePos>dat[curpos[0]].size()?dat[curpos[0]].size():savePos;
                if (curpos[1]>min) {
                    curpos[1]=min;
                } else if (curpos[1]<min) {
                    curpos[1]=min;
                }
            } break;
            case 77:
                if (curpos[1]<dat[curpos[0]].size()) {
                    curpos[1]++;
                }
                else if (curpos[0]+1<dat.size()) {
                    curpos[0]++;
                    curpos[1]=0;
                } savePos=curpos[1];break;
        }
        if (curpos[0]>offset[0]+windowSize[0]) offset[0]=curpos[0]-windowSize[0];
        else if (curpos[0]<offset[0]) offset[0]=curpos[0];
        if (curpos[1]>offset[1]+windowSize[1]) offset[1]=curpos[1]-windowSize[1];
        else if (curpos[1]<offset[1]) offset[1]=curpos[1];
        print(dat);
        moveto(curpos[0]-offset[0],curpos[1]-offset[1]);
    } else if (x==13) {
        vector<vector<char>> x={slice(dat[curpos[0]],0,curpos[1]),slice(dat[curpos[0]],curpos[1])};
        splice(dat,curpos[0],1,x);
        curpos[0]++;
        if (curpos[0]>offset[0]+windowSize[0]) offset[0]=curpos[0]-windowSize[0];
        curpos[1]=0;
        offset[1]=0;
        print(dat);
        moveto(curpos[0]-offset[0],curpos[1]-offset[1]);
        savePos=curpos[1];
    } else if (x==8) {
        if (curpos[1]!=0) {
            splice(dat[curpos[0]],curpos[1]-1,1);
            curpos[1]--;
            if (curpos[1]<offset[1]) offset[1]=curpos[1];
            print(dat);
            moveto(curpos[0]-offset[0],curpos[1]-offset[1]);
        } else if (curpos[0]!=0) {
            int size=dat[curpos[0]-1].size();
            splice(dat[curpos[0]-1],dat[curpos[0]-1].size(),0,dat[curpos[0]]);
            splice(dat,curpos[0],1);
            curpos[0]--;
            if (curpos[0]<offset[0]) offset[0]=curpos[0];
            curpos[1]=size;
            if (curpos[1]>offset[1]+windowSize[1]) offset[1]=curpos[1]-windowSize[1];
            print(dat);
            moveto(curpos[0]-offset[0],curpos[1]-offset[1]);
        }
        savePos=curpos[1];    
    } else if (x==9) {
        splice(dat[curpos[0]],curpos[1],0,{' ',' ',' ',' '});
        curpos[1]+=4;
        if (curpos[1]>offset[1]+windowSize[1]) offset[1]=curpos[1]-windowSize[1];
        print(dat);
        moveto(curpos[0]-offset[0],curpos[1]-offset[1]);
        savePos=curpos[1];
    } else {
        splice(dat[curpos[0]],curpos[1],0,{x});
        curpos[1]++;
        if (curpos[1]>offset[1]+windowSize[1]) offset[1]=curpos[1]-windowSize[1];
        print(dat);
        moveto(curpos[0]-offset[0],curpos[1]-offset[1]);
        savePos=curpos[1];
    }
    return true;
}
void loadFile(string filename) {
    dat={{}};
    string s;
    ifstream file(filename);
    getline(file,s,'\0');
    for (char i:s) {
        if (i=='\n') {
            dat.push_back({});
        } else dat.back().push_back(i);
    }
    file.close();
}
void handleFile(string filename) {
    loadFile(filename);
    clearScreen();
    print(dat);
    curpos={0,0};
    cout << "\033[H";
    while (handleKeys(filename));
}