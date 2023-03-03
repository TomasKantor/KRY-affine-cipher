#include <iostream>
#include <getopt.h>
#include <string>

using namespace std;

typedef struct Arguments{
  int a;
  int b;
  char type;
  std::string input_string;
} arguments;

bool handle_arguments(int argc, char *argv[], Arguments& arguments)
{
    int opt;
    int a = -1;
    int b = -1;
    char type = 'n';
    std::string input_file_name;
    std::string output_file_name;
    while((opt = getopt(argc, argv, ":edca:b:f:o:")) != -1) 
    {
        switch(opt) 
        {
            case 'e':
                type = 'e';
                std::cerr << "encryption\n";
                break;
            case 'd': 
                type = 'd';
                std::cerr << "decryption\n";
                break;
            case 'c':
                type = 'c';
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
    for (int index = optind; index < argc; index++)
    {
        printf ("Input text is %s\n", argv[index]);
        arguments.input_string = std::string(argv[index]);
    }

    arguments.a = a;
    arguments.b = b;
    arguments.type = type;
    return true;
}

int char_to_num(char c)
{
    if ( c >= 65 and c <= 90)
    {
        return c - 65;
    }
    if ( c >= 97 and c <= 122 )
    {
        return c - 97;
    }
    return -1;
}

void encrypt(Arguments& arguments)
{
    int a = arguments.a;
    int b = arguments.b;

    for (int i = 0; i < arguments.input_string.length(); i++)
    {
        char x = char_to_num(arguments.input_string[i]);
        if ( x == -1)
        {
            std::cout << ' ';
        }
        else
        {
            std::cout << char((a*x  + b)%26 + 65);
        }
    }
    std::cout << "\n";
}

int multiplicative_inverse(int a)
{
    for (int i = 0; i < 26; i++)
    {
        if ( ( i*a ) % 26 == 1 )
        {
            return i;
        }
    }
    return -1;
}

std::string decrypt(Arguments& arguments)
{
    int a_inverse = multiplicative_inverse(arguments.a);
    if ( a_inverse == -1)
    {
        std::cerr << "No inverse for a: " << arguments.a << std::endl;
        return "";
    }
    int b = arguments.b;
    std::string answer;
    for (int i = 0; i < arguments.input_string.length(); i++)
    {
        char x = char_to_num(arguments.input_string[i]);
        if ( x == -1)
        {
            answer += ' ';
        }
        else
        {
            answer += char( ( a_inverse*( (x - b + 26)) )%26 + 65);
        }
    }
    return answer;
}

void find_key_and_decrypt(Arguments& arguments)
{
    for ( int a = 0; a < 26; a++)
    {
        
        for ( int b = 0; b < 26; b++ )
        {
            arguments.a = a;
            arguments.b = b;
            std::string answer = decrypt(arguments);
            if (answer.length() != 0)
            {
                std::cout << "a: " << a << " b: " << b << ' ' << answer << std::endl;
            }
            
        }
    }
}

void choose_job(Arguments& arguments)
{
    if (arguments.type == 'e')
    {
        encrypt(arguments);
    }
    else if (arguments.type == 'd')
    {
        std::string answer = decrypt(arguments);
        std::cout << answer << '\n';
    }
    else if (arguments.type == 'c')
    {
        find_key_and_decrypt(arguments);
    }
}

int main(int argc, char *argv[])
{
    Arguments arguments;
    handle_arguments(argc, argv, arguments);
    choose_job(arguments);
}