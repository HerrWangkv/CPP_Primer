#include <iostream>
#include <string>
#include <bitset>

std::istream& func(std::istream &is){
    std::string buf;
    //Windows中文件结束标识是 ctrl+Z
    while (is >> buf)
        std::cout << buf << std::endl;
    //is.clear();
    return is;
}

int main() {
    //必须声明为引用，因为不允许流赋值
    std::istream &is = func(std::cin);
    //输出0000(clear之后)/0110(不进行clear)
    std::cout << std::bitset<4>(is.rdstate());
    return 0;
}