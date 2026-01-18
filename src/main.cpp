#include <iostream>
#include <string>

int positive_char(const std::string& input_line,const std::string& pattern ){
    for(char c: pattern){
        for(char i : input_line){
            if(i == c){
                return 1;
            }
        }
    }
    return 0;
}

int negative_char(const std::string& input_line,const std::string& pattern ){
    for(char c: pattern){
        for(char i : input_line){
            if(i != c){
                return 1;
            }
        }
    }
    return 0;
}

bool match_pattern(const std::string& input_line, const std::string& pattern) {
    if (pattern.length() == 1) {
        return input_line.find(pattern) != std::string::npos;
    }
    if(pattern.length() == 2)
    {
      if(pattern =="\\d" ){
        for(char c : input_line){
            if(c>='0' && c<='9'){
                return true;
            }
        }
        return false;
    }
    if(pattern == "\\w"){
        for(char c:input_line){
            if((c>='0' && c<='9') || (c>='a' && c<='z') || (c>='A' && c<='z')|| (c == '_')){
                return true;
            }
        }
        return false;
    }
    }
    
    if((pattern.front() == '[') && (pattern.back() == ']') )
    {
        if(pattern[1]=='^'){
                return negative_char(input_line, pattern.substr(2,pattern.length() - 3) ); 
        }
        else
          return positive_char(input_line, pattern.substr(1,pattern.length() - 2) ); 
    }

    else {
        throw std::runtime_error("Unhandled pattern " + pattern);
    }
}

int main(int argc, char* argv[]) {
    // Flush after every std::cout / std::cerr
    std::cout << std::unitbuf;
    std::cerr << std::unitbuf;

    // You can use print statements as follows for debugging, they'll be visible when running tests.
    std::cerr << "Logs from your program will appear here" << std::endl;

    if (argc != 3) {
        std::cerr << "Expected two arguments" << std::endl;
        return 1;
    }

    std::string flag = argv[1];
    std::string pattern = argv[2];

    if (flag != "-E") {
        std::cerr << "Expected first argument to be '-E'" << std::endl;
        return 1;
    }

    // TODO: Uncomment the code below to pass the first stage
    //
    std::string input_line;
    std::getline(std::cin, input_line);
    
    try {
        if (match_pattern(input_line, pattern)) {
            return 0;
        } else {
            return 1;
        }
    } catch (const std::runtime_error& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }
}
