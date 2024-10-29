#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <conio.h>
#include <windows.h>
#include <filesystem>
using namespace std;
void clearScreen() {
    cout << "\x1B[2J\x1B[H";
}
vector<vector<char>> dat{{}};
vector<int> curpos{0,0};
int savePos=curpos[1];
vector<int> offset{0,0};
int enableEscapeSquences() {
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hOut == INVALID_HANDLE_VALUE)
    {
        return GetLastError();
    }

    DWORD dwMode = 0;
    if (!GetConsoleMode(hOut, &dwMode))
    {
        return GetLastError();
    }

    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    if (!SetConsoleMode(hOut, dwMode))
    {
        return GetLastError();
    }
    return 0;
}
vector<int> getConsoleSize() {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    int columns, rows;

    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
    return {rows-3,columns-3};
}
vector<int> windowSize=getConsoleSize();
void print(vector<vector<char>> x) {
    cout << "\033[?12l";
    cout << "\033[H";
    string s;
    for (int i=0;i<windowSize[0]+3;i++) {
        for (int j=0;j<windowSize[1]+3;j++) {
            if (i+offset[0]<x.size() && j+offset[1]<x[i+offset[0]].size()) s.push_back(x[i+offset[0]][j+offset[1]]);
            else s.push_back(' ');
        }
        s.push_back('\n');
    }
    s.pop_back();
    cout << s;
    cout << "\033[?12h";
}
template<typename T>
void splice(T &vec1,int index=0,int num=0,T vec2={}) {
    if (index>vec1.size() || index<0) return;
    T newvec = {};
    for (int i=0;i<index;i++) {
        newvec.push_back(vec1[i]);
    }
    for (auto i:vec2) {
        newvec.push_back(i);
    }
    for (int i=index+num;i<vec1.size();i++) {
        newvec.push_back(vec1[i]);
    }
    vec1=newvec;
}
template<typename T>
T slice(T vec,int i=0,int j=-1) {
    if (j==-1) j=vec.size();
    T out;
    for (int ind=0;ind<j;ind++) {
        if (i+ind>=0 && i+ind<vec.size()) out.push_back(vec[i+ind]);
    }
    return out;
}
void moveto(int x,int y) {
    cout << "\033["+to_string(x+1)+';'+to_string(y+1)+'H';
}
vector<string> split(string s,char c) {
    vector<string> out;
    string temp;
    for (char i:s) {
        if (i==c) {
            out.push_back(temp);
            temp="";
        } else temp+=i;
    }
    if (temp!="") out.push_back(temp);
    return out;
}
string join(vector<string> v,char c) {
    string out;
    for (string i:v) {
        out+=i+c;
    }
    out.pop_back();
    return out;
}