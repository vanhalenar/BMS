#include <iostream>
#include <cmath>
#include <cstring>
#include <map>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

const double factor = 1/sqrt(10);

map<string, int> grey = { {"00", -3}, {"01", -1}, {"10", 3}, {"11", 1} };
map<int, string> grey_r = { {-3, "00"}, {-1, "01"}, {3, "10"}, {1, "11"} };


template <typename Out>
void split(const std::string &s, char delim, Out result) {
    std::istringstream iss(s);
    std::string item;
    while (std::getline(iss, item, delim)) {
        if (!empty(item))
            *result++ = item;
    }
}

std::vector<std::string> split(const std::string &s, char delim) {
    std::vector<std::string> elems;
    split(s, delim, std::back_inserter(elems));
    return elems;
}

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

void demodulate(string num) {
    double r = stod(num)/factor;
    if (r < -2) {
        cout<<"00";
    } else if (r < 0) {
        cout<<"01";
    } else if (r < 2) {
        cout<<"11";
    } else {
        cout<<"10";
    }
}

int main(int argc, char* argv[]) {
    if (strcmp(argv[1], "-m") == 0) {
        if (strcmp(argv[2], "-b") == 0) {
            string number(argv[3]);
            modulate(number);
        }
        else if (strcmp(argv[2], "-f") == 0) {
            ifstream f(argv[3]);
            string number;
            getline(f, number); //TODO multiline support?
            modulate(number);
        } 
    } else if (strcmp(argv[1], "-d") == 0) {
        if (strcmp(argv[2], "-f") == 0) {
            ifstream f(argv[3]);
            string numbers[2];
            string line;
            while (getline(f, line)){
                vector<string> numbs = split(line, ' ');
                if (numbs.size()!=2) {
                    continue;
                }
                string real = numbs[0];
                string imag = numbs[1];
                demodulate(real);
                demodulate(imag);
            }
            cout<<endl;
        }
    }

    return 0;
}