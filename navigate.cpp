#include "header.hpp"

string navigate(string path) {
    vector<string> v;
    if (filesystem::exists(path) ) {
        if (filesystem::is_directory(path) || path=="C:/") {
            vector<string> p{".."};
            for (auto i:filesystem::directory_iterator(path)) {
                p.push_back(i.path().filename().generic_string());
            }
            int selected=0;
            do {
                string x="\033[H\033[2J"+path+"\n";
                string prevcol;
                vector<int> s=getConsoleSize();
                int low,high;
                if (p.size()+3>=s[0]) {
                    low=selected+3>=s[0]?selected+3-s[0]:0;
                    high=low+s[0];
                } else {
                    low=0;high=p.size();
                }
                for (int i=low;i<high;i++) {
                    string col=i==selected?"\033[47;30m":"\033[0m";
                    if (prevcol!=col) {
                        x+=col;
                    }
                    prevcol=col;
                    x+=p[i]+'\n';
                }
                x.pop_back();
                cout << x;
                cout << "\033[0m";
                char c=getch();
                while (c<=0) c=getch();
                if (c==72 && selected>0) selected--;
                else if (c==80 && selected<p.size()) selected++;
                else if (c==' ' || c==13) break;
                else if (c==3) return "";
            } while(true);
            string x=p[selected];
            vector<string> np=split(path,'/');
            if (x=="..") {
                if (np.size()>1) np.pop_back();
            } else {
                np.push_back(x);
            }
            string s=join(np,'/');
            s+='/';
            string out=navigate(s);
            return out;
        } else {
            if (path.back()=='/') path.pop_back();
            return path;
        }
    } else {
        if (path.size()!=0) path.pop_back();
        return navigate(path);
    }
    return "";
}