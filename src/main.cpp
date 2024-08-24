 #include <fstream> 
#include <iostream> 
#include <string> 
#include <boost/program_options.hpp>

#include "tape_impl.h"
#include "config_parser.hpp"
#include "merge_sort.h"
#include "utils.hpp"

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

	// input fstream
	std::string input_filename;
	std::cin >> input_filename;
	utils::convertTextIntoBinary(input_filename, "tmp/bin_input");
	std::fstream input_bin("tmp/bin_input", std::ios::in | std::ios::out | std::ios::binary);

	// Output fstream
	std::string output_filename;
	std::cin >> output_filename;
	std::fstream output("tmp/bin_output", std::fstream::in | std::fstream::out | std::fstream::trunc | std::fstream::binary);

	MergeSort sort;

	if(!input_bin.fail()){
		TapeImpl init_tape(input_bin);
		TapeImpl out_tape(output);
		sort(init_tape, out_tape, memory_limit);
		utils::convertBinaryIntoText("tmp/bin_output", output_filename);
	}
	return 0;
}
