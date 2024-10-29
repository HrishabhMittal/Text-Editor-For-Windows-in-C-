#include "edit.cpp"
#include "navigate.cpp"
#include <sstream>
int main() {
    enableEscapeSquences();
    cout << "simple text editor made by hrishabh mittal\n"
            "navigate file selection menu with arrow keys and enter key to select file\n"
            "ctrl+s saves the file\n"
            "ctrl+c exits the file without saving\n"
            "press enter...";
    while (_getch()!=13);
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