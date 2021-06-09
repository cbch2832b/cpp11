// Copyright 2013 Daniel Parker
// Distributed under Boost license

#include <jsoncons/json.hpp>
#include <jsoncons/source.hpp>
#include <catch/catch.hpp>
#include <sstream>
#include <vector>
#include <utility>
#include <ctime>
#include <new>

TEST_CASE("stream_source tests")
{
    std::string data = "012345678";
    std::istringstream is(data);
    jsoncons::stream_source<char> source(is);

    SECTION("test get and peek")
    {
        char b;

        auto p0 = source.peek();
        CHECK_FALSE(source.eof());
        CHECK(p0.value == '0');
        CHECK(source.position() == 0);
        CHECK(source.read(&b,1) == 1);
        CHECK_FALSE(source.eof());
        CHECK(b == '0');
        CHECK(source.position() == 1);
        auto p1 = source.peek();
        CHECK_FALSE(source.eof());
        CHECK(p1.value == '1');
        CHECK(source.position() == 1);
        CHECK(source.read(&b,1) == 1);
        CHECK_FALSE(source.eof());
        CHECK(b == '1');
        CHECK(source.position() == 2);
        CHECK(source.read(&b,1) == 1);
        CHECK_FALSE(source.eof());
        CHECK(b == '2');
        CHECK(source.position() == 3);
        CHECK(source.read(&b,1) == 1);
        CHECK_FALSE(source.eof());
        CHECK(b == '3');
        CHECK(source.position() == 4);

        auto p4 = source.peek();
        CHECK_FALSE(source.eof());
        CHECK(p4.value == '4');
        CHECK(source.position() == 4);
        CHECK(source.read(&b,1) == 1);
        CHECK_FALSE(source.eof());
        CHECK(b == '4');
        CHECK(source.position() == 5);
        auto p5 = source.peek();
        CHECK_FALSE(source.eof());
        CHECK(p5.value == '5');
        CHECK(source.position() == 5);
        CHECK(source.read(&b,1) == 1);
        CHECK_FALSE(source.eof());
        CHECK(b == '5');
        CHECK(source.position() == 6);
        CHECK(source.read(&b,1) == 1);

        CHECK_FALSE(source.eof());
        CHECK(b == '6');
        CHECK(source.position() == 7);
        CHECK(source.read(&b,1) == 1);
        CHECK_FALSE(source.eof());
        CHECK(b == '7');
        CHECK(source.position() == 8);
        CHECK(source.read(&b,1) == 1);
        CHECK_FALSE(source.eof());
        CHECK(b == '8');
        CHECK(source.position() == 9);
        CHECK(source.read(&b,1) == 0);
        CHECK(source.eof());
    }
}

TEST_CASE("wide stream source tests")
{
    std::wstring data = L"012345678";
    std::wistringstream is(data);
    jsoncons::stream_source<wchar_t> source(is);
}

TEST_CASE("binary_stream_source tests")
{
    std::string data = "012345678";
    std::istringstream is(data);
    jsoncons::binary_stream_source source(is,4);

    SECTION("get and peek")
    {
        uint8_t b;

        auto p0 = source.peek();
        CHECK_FALSE(source.eof());
        CHECK(p0.value == '0');
        CHECK(source.position() == 0);
        CHECK(source.read(&b,1) == 1);
        CHECK_FALSE(source.eof());
        CHECK(b == '0');
        CHECK(source.position() == 1);
        auto p1 = source.peek();
        CHECK_FALSE(source.eof());
        CHECK(p1.value == '1');
        CHECK(source.position() == 1);
        CHECK(source.read(&b,1) == 1);
        CHECK_FALSE(source.eof());
        CHECK(b == '1');
        CHECK(source.position() == 2);
        CHECK(source.read(&b,1) == 1);
        CHECK_FALSE(source.eof());
        CHECK(b == '2');
        CHECK(source.position() == 3);
        CHECK(source.read(&b,1) == 1);
        CHECK_FALSE(source.eof());
        CHECK(b == '3');
        CHECK(source.position() == 4);

        auto p4 = source.peek();
        CHECK_FALSE(source.eof());
        CHECK(p4.value == '4');
        CHECK(source.position() == 4);
        CHECK(source.read(&b,1) == 1);
        CHECK_FALSE(source.eof());
        CHECK(b == '4');
        CHECK(source.position() == 5);
        auto p5 = source.peek();
        CHECK_FALSE(source.eof());
        CHECK(p5.value == '5');
        CHECK(source.position() == 5);
        CHECK(source.read(&b,1) == 1);
        CHECK_FALSE(source.eof());
        CHECK(b == '5');
        CHECK(source.position() == 6);
        CHECK(source.read(&b,1) == 1);
        CHECK_FALSE(source.eof());
        CHECK(b == '6');
        CHECK(source.position() == 7);
        CHECK(source.read(&b,1) == 1);
        CHECK_FALSE(source.eof());
        CHECK(b == '7');
        CHECK(source.position() == 8);

        jsoncons::binary_stream_source source2(std::move(source));
        CHECK(source2.read(&b,1) == 1);
        CHECK_FALSE(source2.eof());
        CHECK(b == '8');
        CHECK(source2.position() == 9);
        CHECK(source2.read(&b,1) == 0);
        CHECK(source2.eof());
    }

    SECTION("ignore")
    {
        source.ignore(1);
        CHECK_FALSE(source.eof());
        CHECK(source.position() == 1);
        auto p1 = source.peek();
        CHECK_FALSE(source.eof());
        CHECK(p1.value == '1');
        CHECK(source.position() == 1);
        source.ignore(7);
        CHECK_FALSE(source.eof());
        CHECK(source.position() == 8);
        source.ignore(2);
        CHECK(source.eof());
        CHECK(source.position() == 9);
    }

    SECTION("read 1, read1")
    {
        std::vector<uint8_t> v(10);
        std::vector<uint8_t> expected = {'0','1','2','3','4','5','6','7','8'};

        std::size_t len = source.read(v.data(),1);
        CHECK_FALSE(source.eof());
        CHECK(len == 1);
        CHECK(std::equal(expected.begin(),expected.begin()+1,v.begin()));
        CHECK(source.position() == 1);

        len = source.read(v.data(),1);
        CHECK_FALSE(source.eof());
        CHECK(len == 1);
        CHECK(std::equal(expected.begin()+1,expected.begin()+2,v.begin()));
        CHECK(source.position() == 2);
    }

    SECTION("read 3, read 4, read 3")
    {
        std::vector<uint8_t> v(10);
        std::vector<uint8_t> expected = {'0','1','2','3','4','5','6','7','8'};

        std::size_t len = source.read(v.data(),3);
        CHECK_FALSE(source.eof());
        CHECK(len == 3);
        CHECK(std::equal(expected.begin(),expected.begin()+3,v.begin()));
        CHECK(source.position() == 3);
        //for (size_t i = 0; i < 3; ++i)
        //{
        //    std::cout << i << ": " << v[i] << " ";
        //}
        //std::cout << std::endl;

        len = source.read(v.data(),4);
        CHECK_FALSE(source.eof());
        CHECK(len == 4);
        CHECK(std::equal(expected.begin()+3,expected.begin()+7,v.begin()));
        CHECK(source.position() == 7);

        len = source.read(v.data(),3);
        CHECK_FALSE(source.eof());
        CHECK(len == 2);
        CHECK(std::equal(expected.begin()+7,expected.begin()+9,v.begin()));
        CHECK(source.position() == 9);
    }

    SECTION("read 9")
    {
        std::vector<uint8_t> v(10);
        std::vector<uint8_t> expected = {'0','1','2','3','4','5','6','7','8'};

        std::size_t len = source.read(v.data(),9);
        CHECK_FALSE(source.eof());
        CHECK(len == 9);
        CHECK(std::equal(expected.begin(),expected.end(),v.begin()));
        CHECK(source.position() == 9);
    }

    SECTION("read 10")
    {
        std::vector<uint8_t> v(10);
        std::vector<uint8_t> expected = { '0','1','2','3','4','5','6','7','8'};

        std::size_t len = source.read(v.data(), 10);
        CHECK_FALSE(source.eof());
        CHECK(len == 9);
        CHECK(std::equal(expected.begin(), expected.end(), v.begin()));
        CHECK(source.position() == 9);
    }
}


