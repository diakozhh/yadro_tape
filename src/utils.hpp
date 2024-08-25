#pragma once 

#include <fstream>
#include <iostream>
#include <utility>

namespace utils{
    /**
     * @brief The function of converting a text file to binary file
     * 
     * @param input_filename Text file name
     * @param tmp_filename Binary file name after converting
     */
    static void convertTextIntoBinary(const std::string& input_filename, const std::string &tmp_filename) {
        std::ifstream input(input_filename);
        if(!input.is_open()) {
		    throw std::ifstream::failure("Cannot open file");
        }
        std::ofstream out(tmp_filename, std::ios::binary);
		while (!input.eof()) {
            int32_t x;
            input >> x;
			out.write((char*)&x, sizeof(x));
		}
        input.close();
		out.close();
    }
    /**
     * @brief The function of converting a binary file to text file
     * 
     * @param input_filename Binary file name
     * @param tmp_filename Text file name after converting
     */
    static void convertBinaryIntoText(const std::string& input_filename, const std::string &tmp_filename) {
        std::ifstream input(input_filename, std::ios::binary);
		std::ofstream out(tmp_filename);
		int32_t x;
		while(input.read((char*)&x, sizeof(x))){

			out << x << " ";
		}
		input.close();
		out.close();
    }
}