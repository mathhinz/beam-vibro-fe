#include <catch2/catch_test_macros.hpp>

#include <read_file.hxx>

namespace
{
auto const testsPath =
    std::string{"/Users/mathiashinz/Documents/mhz-projects/dev_env/"
                "vibro-fe/tests/"};
}

TEST_CASE("MAT1 Long Card")
{
    auto const filePath = testsPath + std::string{"mat1Long.bdf"};
    auto const path     = std::filesystem::path{filePath};
    auto const objs     = NastranIO::readNastranFile(path);
    REQUIRE(objs.mat1Map.size() == 1);
}

TEST_CASE("MAT1 Short Card")
{
    auto const filePath = testsPath + std::string{"mat1Short.bdf"};
    auto const path     = std::filesystem::path{filePath};
    auto const objs     = NastranIO::readNastranFile(path);
    REQUIRE(objs.mat1Map.size() == 1);
}

TEST_CASE("GRID Long Card")
{
    auto const filePath = testsPath + std::string{"gridLong.bdf"};
    auto const path     = std::filesystem::path{filePath};
    auto const objs     = NastranIO::readNastranFile(path);
    REQUIRE(objs.gridMap.size() == 1);
}

TEST_CASE("GRID Short Card")
{
    auto const filePath = testsPath + std::string{"gridShort.bdf"};
    auto const path     = std::filesystem::path{filePath};
    auto const objs     = NastranIO::readNastranFile(path);
    REQUIRE(objs.gridMap.size() == 1);
}