#include <iostream>
#include <getopt.h>
#include <string>

using namespace std;

bool handle_arguments(int argc, char *argv[])
{
    int opt;
    int a;
    int b;
    std::string input_file_name;
    std::string output_file_name;
    while((opt = getopt(argc, argv, ":edca:b:f:o:")) != -1) 
    {
        switch(opt) 
        {
            case 'e':
                std::cerr << "encryption\n";
                break;
            case 'd': 
                std::cerr << "decryption\n";
                break;
            case 'c': 
                std::cerr << "decryption, unknown key\n";
                break;
            case 'a':
                try
                {
                    a = stoi(optarg);
                }
                catch (...)
                {
                    std::cerr << "key a needs to be integer\n";
                    return false;
                }            
                std::cerr << "key a is " << a << "\n";
                break;
            case 'b':
                try
                {
                    b = stoi(optarg);
                }
                catch (...)
                {
                    std::cerr << "key b needs to be integer\n";
                    return false;
                }            
                std::cerr << "key b is " << b << "\n";
                break;
            case 'f': 
                std::cerr << "input filename: " << optarg << "\n"; 
                break;
            case 'o': 
                std::cerr << "output filename: " << optarg << "\n"; 
                break;
            case ':': 
                std::cerr << "option '" << char(optopt) << "' needs a value\n"; 
                break; 
            case '?': 
                std::cerr << "unknown option: " << char(optopt) << "\n" ;
                break; 
        }
    }
    return true;
}

int main(int argc, char *argv[])
{

    handle_arguments(argc, argv);

}