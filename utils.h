#include <fstream>
#include <iostream>
#include <utility>

namespace utils{
    void convertTextIntoBinary(std::string& input_filename, std::string &tmp_filename) {
        try{
            std::ifstream input(input_filename);
    		std::ofstream out(tmp_filename, std::ios::binary);
    		int cnt = 0;
            int32_t x;
    		while (!input.eof()) {
                int32_t x;
                input >> x;
    			out.write((char*)&x, sizeof(x));
    			cnt++;
    		}
            input.close();
    		out.close();
        }
        catch(...){
            throw;
        }
    }

    void convertBinaryIntoText(std::string& input_filename, std::string &tmp_filename) {
        std::ifstream input(input_filename, std::ios::binary);
		std::ofstream out(tmp_filename);

		int cnt = 0;
		int32_t x;
		while(input.read((char*)&x, sizeof(x))){

			out << x << " ";
			cnt++;
		}
		//std::cout << cnt << std::endl;
		input.close();
		out.close();
    }
}