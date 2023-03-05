#include <iostream>
#include <getopt.h>
#include <string>
#include <vector>

using namespace std;


const float frequencies[] = {
	0.09589269,  //a	
	0.0177612 ,  //b
	0.02999077,  //c	
	0.03774841,  //d	
	0.10904081,  //e	
	0.0017506 ,  //f
	0.00219812,  //g	
	0.02497482,  //h	
	0.06686138,  //i	
	0.02305759,  //j	
	0.03528082,  //k	
	0.05720782,  //l	
	0.0360545 ,  //m
	0.05917244,  //n
	0.08029999,  //o
	0.03114961,  //p
	0.00005933,  //q
	0.04396827,  //r
	0.0558597 ,  //s	
    0.05385289,  //t
	0.03579031,  //u
	0.03952464,  //v
	0.00054266,  //w
	0.0003591 ,  //x	
    0.02857512,  //y
	0.03302643,  //z
};

const char symbols_by_frequency[]{
	'e', //0.10904081 	
    'a', //0.09589269 	
	'o', //0.08029999 
	'i', //0.06686138 	
	'n', //0.05917244 
	'l', //0.05720782 	
	's', //0.0558597  	
    't', //0.05385289 
	'r', //0.04396827 
	'v', //0.03952464 
	'd', //0.03774841 	
	'm', //0.0360545  
	'u', //0.03579031 
	'k', //0.03528082 	
	'z', //0.03302643 
	'p', //0.03114961 
	'c', //0.02999077 	
    'y', //0.02857512 
	'h', //0.02497482 	
	'j', //0.02305759 	
	'b', //0.0177612  
	'g', //0.00219812 	
	'f', //0.0017506  
	'w', //0.00054266 
	'x', //0.0003591  	
	'q', //0.00005933 
};

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

std::vector<int> get_counts(std::string str)
{
    std::vector<int> counts(26, 0);
    for (int i = 0; i < str.size(); i++)
    {
        int num = char_to_num(str[i]);
        if ( num != -1)
        {
            counts[num] += 1;
        }
    }
    return counts;
}

std::vector<int> arg_max_n(const std::vector<int>& numbers, int count)
{
    std::vector<int> numbers_copy(numbers); 
    std::vector<int> result;
    for( int n = 0; n < count; n++)
    {
        int max = -1;
        int max_index = -1;
        for ( int i = 0; i < numbers_copy.size(); i++)
        {
            if ( numbers_copy[i] > max )
            {
                max = numbers_copy[i];
                max_index = i;
            }
        }
        numbers_copy[max_index] = -1;
        result.push_back(max_index);
    }
    
    return result;
}

bool verify_key(int a, int b, std::vector<int>& arg_max_vector)
{
    for ( int  i = 0; i < arg_max_vector.size(); i++)
    {
        int symbol_num = char_to_num(symbols_by_frequency[i]);
        if ( (a* symbol_num + b) % 26 != arg_max_vector[i])
        {
            return false;
        }
    }
    return true;
}

void get_key_candidates(std::vector<int>& arg_max_vector)
{
    for ( int a : {1, 3, 5, 7, 9, 11, 15, 17, 19, 21, 23, 25 })
    {
        for ( int b = 0; b < 26; b++ )
        {
            if ( verify_key(a, b, arg_max_vector))
            {
                std::cout << "a:" << a << " b:" << b << '\n';
            }
        }
    }
}

void find_key_and_decrypt(Arguments& arguments)
{
    std::vector<int> counts = get_counts(arguments.input_string);
    for ( int num : counts)
    {
        std::cout << num << ' ';
    }
    std::cout << '\n';
    int max_n = 2;
    std::vector<int> arg_max_vector = arg_max_n(counts, max_n);
    for ( int i : arg_max_vector )
    {
        std::cout << "Arg max: " << char(i+'a') << ":" << counts[i] << '\n';
    }
    get_key_candidates(arg_max_vector);
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