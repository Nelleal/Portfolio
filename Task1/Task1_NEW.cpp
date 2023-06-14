#include <iostream>
#include <string>
#include <map>

using namespace std;

// task ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

/*
Нужно конвертировать исходную строку, в новую строку, где каждый символ заменяется на символ:
“(”, если символ встречается только один раз,
")“, если символ встречается больше одного раза.
При решении программа должна игнорировать заглавные буквы, при определении дубликатов(т.е.“А” и “а” - это один и тот же символ).Код должен работать с кириллицей и с латиницей.
Пример входных и выходных данных :
"din" = > "((("
"recede" = > "()()()"
"Success" = > ")())())"
"(( @" = > "))(("
*/

// myTest ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void debug_PrintText(char c, int i, string s) {
    //cout << c << " = " << i << " = " << s << endl;
}

bool compareTwoString(string a, string b) {
    return a == b;
}






// solution ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

string convertTextUseMap(string text) {
    string convertedText;
    map<char, int> uniqueChar;

    for (auto element : text) {
        char c = tolower(element);
        uniqueChar[c] += 1;
    }

    for (auto element : text) {
        char c = tolower(element);
        if (uniqueChar[c] > 1){
            convertedText += ")";
            debug_PrintText(c, uniqueChar[c],")");
        }
        else {
            convertedText += "(";
            debug_PrintText(c, uniqueChar[c],"(");
        }
    }

    return convertedText;
}

string convertTextUseConut(string text) {
    string newText;
    string convertedText;

    for (auto element : text) {
        char c = tolower(element);
        newText += c;
    }

    for (auto element : newText) {
        int value = count(newText.begin(), newText.end(), element);

        if (value > 1) {
            convertedText += ")";
            debug_PrintText(element, value, ")");
        }
        else {
            convertedText += "(";
            debug_PrintText(element, value, "(");
        }
    }

    return convertedText;
}

string convertTextUseTwoFor(string text) {
    string newText;
    string convertedText;
    char c;

    for (auto currentChar : text) {
        int count = 0;
        c = tolower(currentChar);
        for (auto element : text) {
            char newC = tolower(element);
            if (c == newC) {
                count += 1;
            }
        }
        if (count > 1) {
            convertedText += ")";
            debug_PrintText(c, count, ")");
        }
        else {
            convertedText += "(";
            debug_PrintText(c, count, "(");
        }
    }

    return convertedText;
}

int main() {

    //cout << endl << convertTextUseMap("Hi mY frIend") << endl;

    //cout << endl << convertTextUseConut("Hi mY frIend") << endl;

    //cout << endl << convertTextUseTwoFor("Hi mY frIend") << endl;

    cout << compareTwoString(convertTextUseMap("din"), "(((") << endl;
    cout << compareTwoString(convertTextUseMap("recede"), "()()()") << endl;
    cout << compareTwoString(convertTextUseMap("Success"), ")())())") << endl;
    cout << compareTwoString(convertTextUseMap("(( @"), "))((") << endl;

    return 0;
}