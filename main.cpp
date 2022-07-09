#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <string>
#include <vector>
#include <iterator>
#include <cstring>
#include <json/value.h>
#include <json/writer.h>
#include <json/json.h>
#include <filesystem>
#include <regex>



float version = 0.1;
bool custom = false;
std::string cuname;




bool setup() {
    std::string dname;
    std::string uimn;
    std::string auth;
    std::string git;
    std::string pkgs;
    std::string yn;
    std::string fname;
    std::cout << "Default script name (ex: main) " << std::endl << "> ";
    std::cin >> dname;
    std::cout << std::endl << "Use 'if __name__ == '__main__' ?   [y/n]" << std::endl << "> ";
    std::cin >> uimn;
    std::cout << "Author name " << std::endl << "> ";
    std::cin >> auth;
    std::cout << "Github Profile (write . if you don't want it)" << std::endl << "> ";
    std::cin >> git;
    std::cout << "Packages to import on new projects (separated by space)" << std::endl << "> ";
    std::cin.ignore();
    std::getline(std::cin, pkgs);
    std::cout << "Save this as default config? [y/n] " << std::endl << "> ";
    std::cin >> yn;
    if(yn == "y") {
        fname = "config.json";
    }
    else {
        std::cout << "Config Name " << std::endl << "> ";
        std::cin >> fname;
        fname = fname + ".json";
    }

    std::cout << std::endl;


    Json::Value rootJsonValue;
    rootJsonValue["dname"] = dname;
    rootJsonValue["uimn"] = uimn;
    rootJsonValue["auth"] = auth;
    rootJsonValue["git"] = git;
    rootJsonValue["pkgs"] = pkgs;

    Json::StreamWriterBuilder builder;
    builder["commentStyle"] = "None";
    builder["indentation"] = "   ";


    //std::cout << rootJsonValue << std::endl;


    system("mkdir -p ~/.config/berrynit");
    std::string homedir = getenv("HOME");
    std::string path = homedir + "/.config/berrynit/" + fname;
    std::cout << "Config Saved in " << path << std::endl;
    std::unique_ptr<Json::StreamWriter> writer(builder.newStreamWriter());
    std::ofstream outputFileStream(path);
    writer -> write(rootJsonValue, &outputFileStream);

    

    return true;
}


const char *help = "=============================================================================================================\n"
                    "  --setup    |  Setup berryinit (config is stored in ~/.config/berrynit/config.json\n"
                    "  --select   |  Select a custom config and init (make sure it's located in ~/.config/berrynit/NAME.json\n"
                    "  --version  |  Shows current version\n"
                    "  --init     |  Init your project with custom or default config\n"
                    "============================================================================================================"
                    ;


std::string strip(const std::string &inpt)
{
    auto start_it = inpt.begin();
    auto end_it = inpt.rbegin();
    while (std::isspace(*start_it))
        ++start_it;
    while (std::isspace(*end_it))
        ++end_it;
    return std::string(start_it, end_it.base());
}

int main(int argc, char** argv) {
    if(argc == 1) {
        std::cout << "Missing arguments (try -h)" << std::endl;
        return 0;
    }
    if(std::strcmp(argv[1], "-h") == 0) {
        std::string s1(help);

        std::copy(s1.begin(), s1.end(),
            std::ostream_iterator<char>(std::cout, ""));
        std::cout << std::endl;
        return 0;
    }
    else if(std::strcmp(argv[1], "--version") == 0) {
        std::cout << version << std::endl;
        return 0;
    }
    else if(std::strcmp(argv[1], "--setup") == 0) {
        setup();
        return 0;
    }
    else if(std::strcmp(argv[1], "--select") == 0) {
        custom = true;
        
        if(argc < 3) {
            std::cout << "Missing custom config name" << std::endl;
            return 0;
        } 
        else {
            cuname = argv[3];
        }
        //pass
    }
    else if (std::strcmp(argv[1], "--init") == 0) {
        bool exist;
        std::string homedir = getenv("HOME");
        std::string path = homedir + "/.config/berrynit/config.json";
        std::filesystem::path f{path};
        if (std::filesystem::exists(f)) exist = true;
        else               exist = false;

        if(exist) {
            std::string pathx = homedir + "/.config/berrynit/config.json";
            cuname = pathx;
        }
        else {
            std::cout << "Default Config not found! Please run --setup or use a custom one!" << std::endl;
            return 0;
        }
    }

    else {
        return 0;
    }

    
    Json::Value keys;
    std::string jjk = cuname;
    std::ifstream people_file(jjk, std::ifstream::binary);
    people_file >> keys;

    std::ofstream file;
    std::string dname = keys["dname"].toStyledString();
    std::string auth = keys["auth"].toStyledString();
    std::string git = keys["git"].toStyledString();
    std::string pkgs = keys["pkgs"].toStyledString();
    std::string uimn = keys["uimn"].toStyledString();
    dname = strip(dname);
    auth = strip(auth);
    git = strip(git);
    pkgs = strip(pkgs);


    dname.erase(std::remove( dname.begin(), dname.end(), '\"' ),dname.end());
    auth.erase(std::remove( auth.begin(), auth.end(), '\"' ),auth.end());
    git.erase(std::remove( git.begin(), git.end(), '\"' ),git.end());
    pkgs.erase(std::remove( pkgs.begin(), pkgs.end(), '\"' ),pkgs.end());


    std::string filename = dname + ".py";
    file.open(filename);
    pkgs = std::regex_replace(pkgs, std::regex("\\ "), ", ");
    std::string line1 = "import " + pkgs;

    std::string line2 = "_author_ = '" + auth + "'";
    std::string line3 = "_github_ = '" + git + "'";
    std::string line4 = "def main():";
    std::string line5 = "   pass";
    std::string line6 = "if __name__ == '__main__':";
    std::string line7 = "   main()";


    file<< line1 << std::endl;
    file<< std::endl;
    file<< std::endl;
    file<< line2 << std::endl;
    file<< line3 << std::endl;
    file<< std::endl;
    file<< std::endl;
    file<< std::endl;
    file<< std::endl;
    file<< line4 << std::endl;
    file<< line5 << std::endl;
    file<< std::endl;
    file<< std::endl;
    file<< std::endl;
    file<< std::endl;
    file<< std::endl;
    file<< std::endl;
    if(uimn.find("y") != std::string::npos) {
        file<< line6 << std::endl;
        file<< line7 << std::endl;
    }
    system("mkdir -p src/utils/");
    system("mkdir -p test");
    system("mkdir -p docs");




    
    /*
    std::ifstream myfile; myfile.open("~/.config/berrynit/config.json");
    std::string mystring;
    if ( myfile.is_open() ) { 
        myfile >> mystring; 
        std::cout << mystring; 
    } */


    return 0;
}