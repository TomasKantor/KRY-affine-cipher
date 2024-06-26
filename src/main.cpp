#include <iostream>
#include <getopt.h>
#include <string>
#include <vector>
#include <numeric>
#include <fstream>
#include <sstream>

using namespace std;
const int alphabet_size = 26;

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

typedef struct Arguments{
  int a;
  int b;
  char type;
  std::string input_string;
  std::string input_file;
  std::string output_file;
} arguments;

bool handle_arguments(int argc, char *argv[], Arguments& arguments)
{
    int opt;
    int a = -1;
    int b = -1;
    char type = 'n';
    std::string input_file_name;
    std::string output_file_name;
    while((opt = getopt(argc, argv, ":edcta:b:f:o:")) != -1) 
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
            case 't':
                type = 't';
                std::cerr << "Running test\n";
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
                arguments.input_file = std::string(optarg);
                break;
            case 'o': 
                std::cerr << "output filename: " << optarg << "\n";
                arguments.output_file = std::string(optarg);

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
        arguments.input_string = std::string(argv[index]);
    }

    arguments.a = a;
    arguments.b = b;
    arguments.type = type;
    return true;
}

// converts uppercase or lowercase letter to position in alphabet
int char_to_num(char c)
{
    if ( c >= 'A' and c <= 'Z')
    {
        return c - 'A';
    }
    if ( c >= 'a' and c <= 'z' )
    {
        return c - 'a';
    }
    return -1;
}

// encrypts input string given a and b
std::string encrypt(Arguments& arguments)
{
    int a = arguments.a;
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
            answer += char((a*x  + b) % alphabet_size + 'A');
        }
    }
    return answer;
}

// finds multiplicative inverse by looping over candidates
int multiplicative_inverse(int a)
{
    for (int i = 1; i < alphabet_size; i += 2)
    {
        if ( ( i*a ) % alphabet_size == 1 )
        {
            return i;
        }
    }
    return -1;
}

// decrypts input string given a and b
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
            answer += char( ( a_inverse*( (x - b + alphabet_size)) ) % alphabet_size + 'A');
        }
    }
    return answer;
}

// return vector of counts of characters in str
std::vector<int> get_counts(std::string str)
{
    std::vector<int> counts(alphabet_size, 0);
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

// computes deviation between two vectors
float get_deviation(const std::vector<float> v1, const float v2[])
{
    float deviation = 0.0;
    for (int i = 0; i < alphabet_size; i++)
    {
        deviation += (v1[i] - v2[i])*(v1[i] - v2[i]);
    }
    return deviation;
}

// trys all keys, computes deviations and saves best pair to arguments.a and arguments.b
float brute_force_analysis(Arguments& arguments)
{
    std::vector<int> counts = get_counts(arguments.input_string);
    std::vector<float> count_guess(alphabet_size);
    int sum_counts = std::accumulate(counts.begin(), counts.end(), 0);
    int best_a_inverse;
    int best_b;
    float best_deviation = alphabet_size;
    // loop over a inverse get a later
    for ( int a_inverse : {1, 3, 5, 7, 9, 11, 15, 17, 19, 21, 23, 25 })
    {
        for ( int b = 0; b < alphabet_size; b++ )
        {
            // rearrange counts based on key par (a, b)
            for ( int x = 0; x < alphabet_size; x++)
            {
                int index_x = ( a_inverse*( (x - b + alphabet_size)) )%alphabet_size;
                count_guess[index_x] = float(counts[x]) / sum_counts;
            }
            // get deviation
            float deviation = get_deviation(count_guess, frequencies);
            // find best deviation
            if ( deviation < best_deviation)
            {
                best_a_inverse = a_inverse;
                best_b = b;
                best_deviation = deviation;
            }            
        }
    }
    // find a based on a inverse
    int best_a = multiplicative_inverse(best_a_inverse);
    arguments.a = best_a;
    arguments.b = best_b;
    return best_deviation;
}

void test_csv()
{
    std::ifstream file;
    file.open("data/ciphertext.csv");
    std::ofstream output("data/ciphertext_output.csv");
    vector<string> row;
    string line, word;
    Arguments arguments;
    while(getline(file, line))
    {
        // read line to row
        row.clear();
        stringstream str(line);
        while(getline(str, word, ','))
        {
            row.push_back(word);
        }
        // crack the code
        float deviation = brute_force_analysis(arguments);
        std::string decrypted = decrypt(arguments);
        // output answer to file
        output << row[0] << ',';
        arguments.input_string = row[1];
        output << arguments.a << ',' << arguments.b << ',';
        output << decrypted << '\n';

        std::cerr << "a:" << arguments.a << " b:" << arguments.b << " deviation: " << deviation << '\n';
    }
}

void decrypt_unknown_key(Arguments& arguments)
{
    // get input string
    std::fstream input_stream;
    input_stream.open(arguments.input_file, ios::in);
    getline(input_stream, arguments.input_string);
    // find keys
    brute_force_analysis(arguments);
    // decrypt text
    std::string answer = decrypt(arguments);
    // output decrypt text to file
    std::ofstream output_stream;
    output_stream.open(arguments.output_file);
    output_stream << answer;
    output_stream.close();
    // print keys
    std::cout << "a=" << arguments.a << ",b=" << arguments.b << std::endl;
}

void choose_job(Arguments& arguments)
{
    if (arguments.type == 'e')
    {
        std::string answer = encrypt(arguments);
        std::cout << answer << '\n';
    }
    else if (arguments.type == 'd')
    {
        std::string answer = decrypt(arguments);
        std::cout << answer << '\n';
    }
    else if (arguments.type == 'c')
    {
        decrypt_unknown_key(arguments);
    }
    else if (arguments.type == 't')
    {
        test_csv();
    }
}

int main(int argc, char *argv[])
{
    Arguments arguments;
    handle_arguments(argc, argv, arguments);
    choose_job(arguments);
}