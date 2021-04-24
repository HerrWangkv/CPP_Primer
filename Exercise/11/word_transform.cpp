#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <stdexcept> // runtime_error
using std::cout;
using std::endl;
using std::getline;
using std::ifstream;
using std::istringstream;
using std::map;
using std::runtime_error;
using std::string;

map<string, string> buildMap(ifstream &map_file) {
    map<string, string> trans_map;
    string key;
    string value;
    while (map_file >> key && getline(map_file, value)) {
        if (value.size() > 1)
            trans_map[key] = value.substr(1);//跳过前导空格
        else
            throw runtime_error("no rule for " + key);
    }
    return trans_map;
}

const string &transform(const string &s, const map<string, string> &m) {
    auto map_it = m.find(s);
    if (map_it != m.cend())
        return map_it->second;
    else
        return s;
}

void word_transform(ifstream &map_file, ifstream &input) {
    auto trans_map = buildMap(map_file);
    string text;
    while (getline(input, text)) {
        //从string对象中读取单词
       istringstream stream(text);
       string word;
       bool firstword = true;//控制是否打印空格
       while(stream >> word) {
           if (firstword)
               firstword = false;
            else
                cout << " ";
            cout << transform(word, trans_map);
       }
       cout << endl;
    }

}
int main() {
    ifstream if1("./mapping_rule.txt");
    ifstream if2("./original_text.txt");
    word_transform(if1, if2);
    return 0;
}