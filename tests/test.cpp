#include <gtest/gtest.h>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream> 

#include "tape_impl.h"
#include "merge_sort.h"
#include "config_parser.hpp"
#include "utils.hpp"

std::string test_data = "tests/test_data/";
std::string test_data_tmp = "tests/test_data_tmp/";

TEST(TapeImpl, end_of_file){
    std::fstream test(test_data + "write_data", std::ios::in | std::ios::out);
    utils::convertTextIntoBinary(test_data + "write_data", test_data_tmp + "write_bin");
    std::fstream test_bin(test_data_tmp + "write_bin", std::fstream::in | std::fstream::out | std::fstream::trunc | std::fstream::binary);
    TapeImpl test_tape_empty(test_bin);
    EXPECT_TRUE(test_tape_empty.isEnd());

    std::fstream test1(test_data + "read_data", std::ios::in | std::ios::out);
    utils::convertTextIntoBinary(test_data + "read_data", test_data_tmp + "read_bin");
    std::fstream test_bin1(test_data_tmp + "read_bin", std::fstream::in | std::fstream::out | std::fstream::binary);
    TapeImpl test_tape(test_bin1);
    EXPECT_FALSE(test_tape.isEnd());

    test.close();
    test_bin.close();
    test1.close();
    test_bin1.close();
}

TEST(TapeImpl, get_position){
    std::fstream test(test_data + "read_data", std::ios::in | std::ios::out);
    utils::convertTextIntoBinary(test_data + "read_data", test_data_tmp + "read_bin");
    std::fstream test_bin(test_data_tmp + "read_bin", std::fstream::in | std::fstream::out | std::fstream::binary);

    TapeImpl test_tape(test_bin);
    EXPECT_EQ(test_tape.getPosition(), 0);

    test.close();
    test_bin.close();
}

TEST(TapeImpl, move){
    std::fstream test(test_data + "read_data", std::ios::in | std::ios::out);
    utils::convertTextIntoBinary(test_data + "read_data", test_data_tmp + "read_bin");
    std::fstream test_bin(test_data_tmp + "read_bin", std::fstream::in | std::fstream::out | std::fstream::binary);

    TapeImpl test_tape(test_bin);
    test_tape.moveRight();
    EXPECT_EQ(test_tape.getPosition(), 1);
    test_tape.moveLeft();
    EXPECT_EQ(test_tape.getPosition(), 0);

    test.close();
    test_bin.close();
}

TEST(TapeImpl, read_element){
    std::fstream test(test_data + "read_data", std::ios::in | std::ios::out);
    utils::convertTextIntoBinary(test_data + "read_data", test_data_tmp + "read_bin");
    std::fstream test_bin(test_data_tmp + "read_bin", std::fstream::in | std::fstream::out | std::fstream::binary);

    TapeImpl test_tape(test_bin);
    EXPECT_EQ(test_tape.readElement(), 1);

    test.close();
    test_bin.close();
}

TEST(TapeImpl, write_element){
    std::fstream test(test_data + "write_data", std::ios::in | std::ios::out);
    utils::convertTextIntoBinary(test_data + "write_data", test_data_tmp + "write_bin");
    std::fstream test_bin(test_data_tmp + "write_bin", std::fstream::in | std::fstream::out | std::fstream::trunc | std::fstream::binary);

    TapeImpl test_tape(test_bin);
    test_tape.writeElement(10);
    EXPECT_EQ(test_tape.readElement(), 10);

    test.close();
    test_bin.close();
}

TEST(TapeImpl, sort){
    std::fstream test(test_data + "unsort_data", std::ios::in | std::ios::out);
    utils::convertTextIntoBinary(test_data + "unsort_data", test_data_tmp + "unsort_data_bin");
    std::fstream test_bin(test_data_tmp + "unsort_data_bin", std::fstream::in | std::fstream::out | std::fstream::binary);

	std::fstream ouput(test_data_tmp + "sort_data_bin", std::fstream::in | std::fstream::out | std::fstream::trunc | std::fstream::binary);


    TapeImpl test_tape(test_bin);
    TapeImpl test_out_tape(ouput);
    MergeSort sort;
    sort(test_tape, test_out_tape, 8);
    utils::convertBinaryIntoText(test_data_tmp + "sort_data_bin", test_data_tmp + "sort_data");
    std::fstream output_merge(test_data_tmp + "sort_data", std::fstream::in | std::fstream::out | std::fstream::trunc);


    std::string s_unsort;
    std::getline(test, s_unsort);
    std::istringstream ss(s_unsort);
    std::vector<int32_t> buf;
    int32_t elem;
    while( ss >> elem)
        buf.push_back(elem);

    std::sort(buf.begin(), buf.end());
    std::fstream ouput_algo(test_data_tmp + "sort_data_algo", std::fstream::in | std::fstream::out | std::fstream::trunc);
    
    for( int32_t write_elem : buf){
        ouput_algo << write_elem << " ";
    }

    std::string sort_algo_string;
    std::getline(ouput_algo, sort_algo_string);

    std::string sort_algo_merge;
    std::getline(output_merge, sort_algo_merge);
    EXPECT_TRUE(sort_algo_merge==sort_algo_string);

    test.close();
    test_bin.close();
    ouput.close();
    output_merge.close();
    ouput_algo.close();
}