 #include <fstream> 
#include <iostream> 
#include <string> 
#include <boost/program_options.hpp>

#include "tape_impl.h"
#include "config_parser.hpp"
#include "merge_sort.h"
#include "utils.h"

int main(int argc, char** argv) 
{ 
	namespace po = boost::program_options;
    
    std::string conf_path;
	int memory_limit = 8;

	Config& config = Config::getInstanceConfig();

	//command line parse
	try {
    	po::options_description desc("General options");
    	desc.add_options()
    	    ("help,h", "produce help message")
    	    ("config,c", po::value<std::string>(), "set configuration file path")
			("memory_limit,m", po::value<int>(), "set memory limit (bytes)")
			;

    	po::variables_map vm;
		po::parsed_options parsed = po::command_line_parser(argc, argv).options(desc).allow_unregistered().run();
    	po::store(parsed, vm);
    	po::notify(vm);

    	if (vm.count("help")) {
    	    std::cout << desc << "\n";
    	    return 0;
    	}

    	else if (vm.count("config")) {
            conf_path = vm["config"].as<std::string>();
			config.readConfig(conf_path);
			std::cout << "Configuration path "
    	         << conf_path << ".\n";

    	}

		else if (vm.count("memory_limit")) {
			if( vm["memory_limit"].as<int>() < 8 ) {
				std::cerr << "Memory limit must be greater or equal 8 bytes\n";
    			return 1;
			}

			memory_limit = vm["memory_limit"].as<int>();
		} 
		
		else {
    	    std::cout << "Using default configuration.\n";
    	}
    }
    catch(std::exception& e) {
        std::cerr << "error: " << e.what() << "\n";
        return 1;
    }
    catch(...) {
        std::cerr << "Exception of unknown type!\n";
    	return 1;
    }

	// input file stream
	//std::ifstream input("test_tape");
	std::string input_tmp_filename = "tmp_input_bin";
	std::string input_filename = "test_tape";

	utils::convertTextIntoBinary(input_filename, input_tmp_filename);
	std::fstream input_bin(input_tmp_filename, std::ios::in | std::ios::out | std::ios::binary);

	//Temporary fstreams for merging
	std::fstream tmp1("tmp1", std::ios::in | std::ios::out | std::ios::binary);
	std::fstream tmp2("tmp2", std::ios::in | std::ios::out | std::ios::binary);

	// Output fstream
	std::string output_bin_filename = "tmp_output_bin", output_filename = "out";
	std::fstream ouput(output_bin_filename, std::ios::in | std::ios::out | std::ios::binary);

	if(!input_bin.fail()){
		TapeImpl init_tape(input_bin);
		
		TapeImpl tape_tmp1(tmp1);
		TapeImpl tape_tmp2(tmp2);

		TapeImpl out_tape(ouput);

		MergeSort sort;
		sort(init_tape, out_tape, tape_tmp1, tape_tmp2, 16);
		std::string tmp_out1 = "tmp_non_bin1";
		std::string tmp_out2 = "tmp_non_bin2";
		std::string tmp_out1_bin = "tmp1";
		std::string tmp_out2_bin = "tmp2";

		utils::convertBinaryIntoText(tmp_out1_bin, tmp_out1);
		utils::convertBinaryIntoText(tmp_out2_bin, tmp_out2);

		std::ofstream final_out("final_out");

	}
	
	return 0;
}
