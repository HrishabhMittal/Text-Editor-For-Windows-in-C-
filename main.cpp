#include "edit.cpp"
#include "header.hpp"
#include "navigate.cpp"
#ifdef _WIN32
#define SAVEKEY "s"
#define EXITKEY "c"
#else
#define SAVEKEY "w"
#define EXITKEY "e"
#endif
int main() {
    enableEscapeSquences();
    cout << "simple text editor made by hrishabh mittal\n"
            "navigate file selection menu with arrow keys and enter key to select file\n"
            "ctrl+" SAVEKEY " saves the file\n"
            "ctrl+" EXITKEY " exits the file without saving\n"
            "press enter...";
    while (_getch()!=ENTER);
    string prevpath=filesystem::absolute(".").generic_string();
    while (true) {
        cout << "\033[H\033[2J";
        string path=navigate(prevpath);
        if (path!="") handleFile(path);
        else break;
        vector<string> npp=split(path,'/');
        npp.pop_back();
        prevpath=join(npp,'/')+'/';
    }
}
