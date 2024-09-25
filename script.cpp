#include <iostream>
#include <filesystem>
#include <ostream>
#include <string>
#include <fstream>
#include <algorithm>
#include <vector>

namespace fs = std::filesystem;
std::ofstream outfile("Compile.md");

//STRIDE = Spoofing, Tampering, Repudiation, Information Disclosure,
//Denial of Service, Elevation of privilege

std::vector<std::vector<std::string>> STRIDE = {{}, {}, {}, {}, {}, {}};

std::string path = "./known-cyber-attacks";

void define(std::string pathname) {
    std::ifstream file(pathname+"/README.md");

    std::string text;
    std::string line;

    while(std::getline(file, line)) text += line += '\n';

    std::transform(text.begin(), text.end(), text.begin(),
    [](unsigned char c){ return std::tolower(c); });


    std::vector<std::string> options = {"spoofing", "tampering",
        "repudiation", "information disclosure", "denial of service",
        "of privilege"};

    if(text.find("n/a") == std::string::npos) {

        int i = 0;
        for(auto option: options){
            if(text.find(option) != std::string::npos) STRIDE[i].push_back(pathname.substr(path.size()+1));
            i++;
        }
    } else {
        
        for(int j = 0; j < options.size() - 1; j++) {
            int found = text.find("n/a");

            if(text.find(options[j]) < found && text.find(options[j+1]) < found) {
                STRIDE[j].push_back(pathname.substr(path.size()+1));
            }

            text = text.substr(text.find(options[j+1]));
        }

        if(text.find("n/a") == std::string::npos) STRIDE[5].push_back(pathname.substr(path.size() + 1));
    }

}

int main() {
    for(const auto& entry : fs::directory_iterator(path)) {
        std::string result = entry.path();

        std::string do_not_include[] = {"Template", "README.md", ".git"};

        bool output = true;
        for(auto dni: do_not_include) {
            if(dni.find(result.substr(path.size()+1)) != std::string::npos) {
                output = false;
            }
        }

        if(output) {
            define(result);
            outfile << result.substr(path.size()+1) << std::endl;
        }
    }
    
    for(auto arr: STRIDE) {
        std::cout << std::endl;
        for(auto s: arr) {
            std::cout << s << std::endl;
        }
    }

    outfile.close();
}