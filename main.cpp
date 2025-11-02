#include <iostream>
#include <cmath>
#include <cstring>
#include <map>

using namespace std;

const double factor = 1/sqrt(10);

map<string, int> grey = { {"00", -3}, {"01", -1}, {"10", 3}, {"11", 1} };

void modulate(string num) {
    string s;
    string zeros = "0000";
    for (int i=0; i<num.size(); i+=4) {
        s = num.substr(i, 4);
        int size = s.size();
        if (size < 4) {
            s.append(zeros.substr(0, 4-size));
        }

        int number1 = grey[s.substr(0,2)];
        int number2 = grey[s.substr(2,2)];
        double final1 = number1 * factor;
        double final2 = number2 * factor;

        char spacer1 = final1 > 0 ? ' ' : '\0';
        char spacer2 = final2 > 0 ? ' ' : '\0';

        cout<<spacer1<<final1<<" "<<spacer2<<final2<<endl;
   } 
}

int main(int argc, char* argv[]) {
    if (strcmp(argv[1], "-m") == 0) {
        if (strcmp(argv[2], "-b") == 0) {
            string number(argv[3]);
            modulate(number);
        }
        else if (strcmp(argv[2], "-f") == 0) {
            cout<<"Not implemented, TODO"<<endl;
            return 1;
        } 
    }

    return 0;
}