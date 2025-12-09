#include <iostream>
#include <cmath>
#include <cstring>
#include <map>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

// Factor used for normalisation
const double factor = 1/sqrt(10);

// Grey code mappings
map<string, int> grey = { {"00", -3}, {"01", -1}, {"10", 3}, {"11", 1} };
map<int, string> grey_r = { {-3, "00"}, {-1, "01"}, {3, "10"}, {1, "11"} };

// https://cppscripts.com/cpp-split-string-by-delimiter
vector<string> splitString(const string& str, char delimiter) {
    vector<string> tokens;
    stringstream ss(str);
    string token;
    while (getline(ss, token, delimiter)) {
        if (!empty(token)) {
            tokens.push_back(token);
        }
    }
    return tokens;
}

/**
 * Modulate binary number into complex number.
 *
 * @param num Binary string, e.g. "1100", "10100011"
 */
void modulate(string num) {
    string s;

    // Used to correct length of binary strings, so they're divisible by 4
    string zeros = "0000";
    // Go through number in lengths of 4
    for (int i=0; i<num.size(); i+=4) {
        s = num.substr(i, 4);
        int size = s.size();
        // Correct length of string
        if (size < 4) {
            s.append(zeros.substr(0, 4-size));
        }

        // Find value in Grey mapping
        int number1 = grey[s.substr(0,2)];
        int number2 = grey[s.substr(2,2)];

        // Multiply by factor
        double final1 = number1 * factor;
        double final2 = number2 * factor;

        // Make output nicer
        char spacer1 = final1 > 0 ? ' ' : '\0';
        char spacer2 = final2 > 0 ? ' ' : '\0';

        cout<<spacer1<<final1<<" "<<spacer2<<final2<<endl;
   } 
}

/**
 * Demodulate decimal number into binary.
 *
 * Prints a 2-digit binary string to output.
 * @param num Decimal number, e.g. "-0.948683, 0.316228"
 */
void demodulate(string num) {
    // Divide by factor
    double r = stod(num)/factor;
    // Print according to thresholds
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
    // Modulating
    if (strcmp(argv[1], "-m") == 0) {
        // From STDIN
        if (strcmp(argv[2], "-b") == 0) {
            string number(argv[3]);
            modulate(number);
        }
        // From file, process all lines
        else if (strcmp(argv[2], "-f") == 0) {
            ifstream f(argv[3]);
            string number;
            while(getline(f, number)) {
                modulate(number);
            }
        }
        else {
            fprintf(stderr, "Invalid modulation input mode");
            return 1;
        }
    // Demodulating
    } else if (strcmp(argv[1], "-d") == 0) {
        if (strcmp(argv[2], "-f") == 0) {
            ifstream f(argv[3]);
            string line;
            // Process each line
            while (getline(f, line)){
                // Get real and imaginary parts
                vector<string> numbers = splitString(line, ' ');
                if (numbers.size()!=2) {
                    continue;
                }
                // Process real and imaginary parts individually because it's the same
                string real = numbers[0];
                string imag = numbers[1];
                demodulate(real);
                demodulate(imag);
            }
            cout<<endl;
        }
        else {
            fprintf(stderr, "Invalid demodulation input mode");
            return 1;
        }
    }
    else {
        fprintf(stderr, "Invalid mode");
        return 1;
    }

    return 0;
}