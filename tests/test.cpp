#include <gtest/gtest.h>
#include <fstream>

#include "../src/tape_impl.h"
#include "../src/merge_sort.h"
#include "../src/config_parser.hpp"
#include "../src/utils.hpp"

// end of file
TEST(TapeImpl, end_of_file){
    std::fstream test("write_data", std::ios::in | std::ios::out);
    utils::convertTextIntoBinary("write_data", "write_bin");
    std::fstream test_bin("write_bin", std::fstream::in | std::fstream::out | std::fstream::trunc | std::fstream::binary);
    TapeImpl test_tape_empty(test_bin);
    EXPECT_TRUE(test_tape_empty.isEnd());

    std::fstream test1("read_data", std::ios::in | std::ios::out);
    utils::convertTextIntoBinary("read_data", "read_bin");
    std::fstream test_bin1("read_bin", std::fstream::in | std::fstream::out | std::fstream::trunc | std::fstream::binary);

    TapeImpl test_tape(test_bin1);
    EXPECT_FALSE(test_tape.isEnd());
}

// get position
TEST(TapeImpl, get_position){
    std::fstream test("read_data", std::ios::in | std::ios::out);
    utils::convertTextIntoBinary("read_data", "read_bin");
    std::fstream test_bin("read_bin", std::fstream::in | std::fstream::out | std::fstream::trunc | std::fstream::binary);

    TapeImpl test_tape(test_bin);
    EXPECT_EQ(test_tape.getPosition(), 231321);
}
//
//// move
TEST(TapeImpl, move){
    std::fstream test("read_data", std::ios::in | std::ios::out);
    utils::convertTextIntoBinary("read_data", "read_bin");
    std::fstream test_bin("read_bin", std::fstream::in | std::fstream::out | std::fstream::trunc | std::fstream::binary);

    TapeImpl test_tape(test_bin);
    test_tape.moveRight();
    EXPECT_EQ(test_tape.getPosition(), 1);
    test_tape.moveLeft();
    EXPECT_EQ(test_tape.getPosition(), 0);
}

//// read
TEST(TapeImpl, read_element){
    std::fstream test("read_data", std::ios::in | std::ios::out);
    utils::convertTextIntoBinary("read_data", "read_bin");
    std::fstream test_bin("read_bin", std::fstream::in | std::fstream::out | std::fstream::trunc | std::fstream::binary);

    TapeImpl test_tape(test_bin);
    EXPECT_EQ(test_tape.readElement(), 1);
}

//// write
TEST(TapeImpl, write_element){
    std::fstream test("write_data", std::ios::in | std::ios::out);
    utils::convertTextIntoBinary("write_data", "write_bin");
    std::fstream test_bin("write_bin", std::fstream::in | std::fstream::out | std::fstream::trunc | std::fstream::binary);

    TapeImpl test_tape(test_bin);
    test_tape.writeElement(10);
    EXPECT_EQ(test_tape.readElement(), 10);
}


