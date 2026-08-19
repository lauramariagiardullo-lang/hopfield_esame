#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "immagine.hpp"
#include "doctest.h"
#include <fstream>

TEST_CASE("testo get_file_names - cartella vuota")
{
  std::filesystem::path p{"cartella"};
  REQUIRE(std::filesystem::create_directory(p));
  REQUIRE(std::filesystem::is_empty(p));
  CHECK_THROWS(pf::get_file_names(p));
  std::filesystem::remove_all(p);
}

TEST_CASE("testo get_file_names - no regular file disponibili")
{
  std::filesystem::path p1{"cart_1"};
  std::filesystem::path p2{p1 / "cart_2"};
  std::filesystem::path p3{p1 / "cart 3"};
  REQUIRE(std::filesystem::create_directories(p2));
  REQUIRE(std::filesystem::create_directories(p3));
  CHECK_THROWS(pf::get_file_names(p1));
  std::filesystem::remove_all(p1);
}

TEST_CASE("testo get_file_names - path fornito non corrisponde a una cartella "
          "- path è un file")
{
  std::filesystem::path p{"file"};
  std::ofstream file{"file"};
  REQUIRE(file);
  CHECK_THROWS(pf::get_file_names(p));
  std::filesystem::remove(p);
}

TEST_CASE("testo get_file_names - path inesistente")
{
  std::filesystem::path p{"path"};
  CHECK_THROWS(pf::get_file_names(p));
}

TEST_CASE("testo get_file_names - tre file con stessa estensione")
{
  std::filesystem::path p{"cartella"};
  REQUIRE(std::filesystem::create_directory(p));
  std::ofstream file1(p / "img_a.png");
  std::ofstream file2(p / "img_b.png");
  std::ofstream file3(p / "img_c.png");
  REQUIRE(file1);
  REQUIRE(file2);
  REQUIRE(file3);
  std::vector<std::filesystem::path> risultato{pf::get_file_names(p)};
  std::sort(risultato.begin(), risultato.end());
  CHECK(risultato
        == std::vector<std::filesystem::path>{
            p / "img_a.png", p / "img_b.png", p / "img_c.png"});
  std::filesystem::remove_all(p);
}

TEST_CASE("testo get_file_names - quattro file con estensioni diverse")
{
  std::filesystem::path p{"cartella"};
  REQUIRE(std::filesystem::create_directory(p));
  std::ofstream file1{p / "file_a.txt"};
  std::ofstream file2{p / "file_b.png"};
  std::ofstream file3{p / "file_c.jpg"};
  std::ofstream file4{p / "file_d.mp3"};
  REQUIRE(file1);
  REQUIRE(file2);
  REQUIRE(file3);
  REQUIRE(file4);
  std::vector<std::filesystem::path> risultato{pf::get_file_names(p)};
  std::sort(risultato.begin(), risultato.end());
  CHECK(risultato
        == std::vector<std::filesystem::path>{
            p / "file_a.txt", p / "file_b.png", p / "file_c.jpg",
            p / "file_d.mp3"});
  std::filesystem::remove_all(p);
}
