#include <iostream>
#include <string>
#include <vector>

std::vector<std::string> parsepattern(std::string p){
    std::vector<std::string>arr;
    for(int i =0;i<p.length();i++){
        // if(p[i]== '^'){
        //     std::string s="";
        //     while(p[i]!=' '){
        //         s=s+p[i];
        //         i++;
        //     }
        //      arr.push_back(s);
        // }
        if(p[i] == '\\'){
            arr.push_back(std::string("\\")+p[i+1]);
            i++;
        }
       else  if(p[i] == '['){
           std::string s = "";
            while(p[i]!=']'){
                s=s+p[i];
                i++;
            }
            s+=']';
            arr.push_back(s);
        }
        else{
            arr.push_back(std::string(1,p[i]));
        }
    }
    return arr;
}


bool positive_char_group(const std::string& input_line,const std::string& pattern ){
    for(char c: pattern){
        for(char i : input_line){
            if(i == c){
                return true;
            }
        }
    }
    return false;
}

bool negative_char_group(const std::string& input_line,const std::string& pattern ){
    for(char c: input_line){
        int count =0;
        for(char i : pattern){
            if(i == c){
                count++;
            }
        }
        if(count==0){
            return true;
        }
    }
    return false;
}

bool digit_matcher(const std::string& input_line, const std::string& pattern){
 for(char c : input_line){
            if(c>='0' && c<='9'){
                return true;
            }
        }
        return false;
}


bool firstRule(char s,std::string &pattern){
  
   
     if(pattern == "\\d"){
       
       if((s>='0' && s<='9'))
            {
                return true;
            }
    }
    else if(pattern == "\\w"){
         if((s>='0' && s<='9') || (s>='a' && s<='z') || (s>='A' && s<='z')|| (s == '_'))
            {
                return true;
            }
    }
    else if(pattern.front() == '[' && pattern.back()==']'){
        if(pattern[1] == '^'){
            return negative_char_group(std::string(1, s), pattern.substr(2, pattern.length() - 3));
        }
        else{
            return positive_char_group(std::string(1, s), pattern.substr(1, pattern.length() - 2));
        }
    }
    
    else {
        if(s==pattern[0]){
            return true;
        }
    }
    return false;
}


bool word_char_matcher(const std::string& input_line, const std::string& pattern){
        for(char c:input_line){
            if((c>='0' && c<='9') || (c>='a' && c<='z') || (c>='A' && c<='z')|| (c == '_')){
                return true;
            }
        }
        return false;
}

bool patternChecker(std::string s, int j, std::vector<std::string>&pattern){
    int k = j;
    for(int i = 0;i<pattern.size();i++){
        if(pattern[i] == "$"){
            if(k == s.size()){
                return true;
            }
            else{
                return false;
            }
        }
        else{

        
        if(firstRule(s[k],pattern[i])){
            k++;
        }
        else{
          
            return false;
        }
        }
    }
    return true;
}


bool match_pattern(const std::string& input_line, const std::string& pattern) {
    std::vector<std::string> arr = parsepattern(pattern);
    if(pattern[0]=='^'){
        arr.erase(arr.begin());
        if(patternChecker(input_line,0,arr)){
            return true;
        }
        return false;
    }
    else{

    
   for(int i = 0;i<input_line.size();i++){
     
      if(firstRule(input_line[i],arr[0])){
          if(patternChecker(input_line,i,arr)){
             
              return true;
              
          }
      }
  }
    
    return false;
    }

    // else {
    //     throw std::runtime_error("Unhandled pattern " + pattern);
    // }
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
