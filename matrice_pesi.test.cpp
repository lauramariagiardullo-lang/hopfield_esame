
#include "matrice_pesi.hpp"
#include "costanti.hpp"
#include "doctest.h"
#include <fstream>

TEST_CASE("Testo Matrice_Pesi - costruttore -inizalizzazione a 0.0")
{
  pf::Matrice_Pesi hebbs;
  for (std::size_t i{0}; i != pf::N_neuroni; ++i) {
    for (std::size_t j{0}; j != pf::N_neuroni; ++j) {
      CHECK(hebbs(i, j) == 0.0);
    }
  }
}

TEST_CASE("Testo Matrice_Pesi - calcolo_elemento_ij - vettore pattern vuoto")
{
  std::vector<pf::Pattern> vp{};
  REQUIRE(vp.empty());
  std::size_t i{2};
  std::size_t j{21};
  pf::Matrice_Pesi hebbs;
  CHECK_THROWS(hebbs.calcolo_elemento_ij(vp, i, j));
}

TEST_CASE("Testo Matrice_Pesi - calcolo_matrice - vettore pattern vuoto")
{
  std::vector<pf::Pattern> vp{};
  REQUIRE(vp.empty());
  pf::Matrice_Pesi hebbs;
  CHECK_THROWS(hebbs.calcolo_matrice(vp));
}

TEST_CASE("Testo Matrice_Pesi - calcolo_matrice - uso di un singolo pattern")
{
  pf::Pattern p;
  p[1]  = pf::Stato_Neurone::negativo;
  p[2]  = pf::Stato_Neurone::negativo;
  p[3]  = pf::Stato_Neurone::negativo;
  p[4]  = pf::Stato_Neurone::negativo;
  p[5]  = pf::Stato_Neurone::negativo;
  p[16] = pf::Stato_Neurone::negativo;
  p[25] = pf::Stato_Neurone::negativo;
  p[26] = pf::Stato_Neurone::negativo;
  std::vector<pf::Pattern> vp{p};
  pf::Matrice_Pesi hebbs;
  hebbs.calcolo_matrice(vp);
  CHECK(hebbs(0, 0) == 0.0);
  CHECK(hebbs(0, 1) == doctest::Approx(-1 / pf::N_neuroni).epsilon(1e-5));
  CHECK(hebbs(1, 0) == doctest::Approx(-1 / pf::N_neuroni).epsilon(1e-5));
  CHECK(hebbs(30, 29) == doctest::Approx(1 / pf::N_neuroni).epsilon(1e-5));
  CHECK(hebbs(13, 6) == doctest::Approx(1 / pf::N_neuroni).epsilon(1e-5));
  CHECK(hebbs(6, 13) == doctest::Approx(1 / pf::N_neuroni).epsilon(1e-5));
  CHECK(hebbs(5, 16) == doctest::Approx(1 / pf::N_neuroni).epsilon(1e-5));
  CHECK(hebbs(16, 27) == doctest::Approx(-1 / pf::N_neuroni).epsilon(1e-5));
}

TEST_CASE("Testo Matrice_Pesi - calcolo_matrice - 3 pattern")
{
  pf::Pattern p1;
  p1[2]  = pf::Stato_Neurone::negativo;
  p1[3]  = pf::Stato_Neurone::negativo;
  p1[5]  = pf::Stato_Neurone::negativo;
  p1[19] = pf::Stato_Neurone::negativo;
  p1[24] = pf::Stato_Neurone::negativo;
  pf::Pattern p2;
  p2[6]  = pf::Stato_Neurone::negativo;
  p2[13] = pf::Stato_Neurone::negativo;
  p2[3]  = pf::Stato_Neurone::negativo;
  p2[29] = pf::Stato_Neurone::negativo;
  p2[11] = pf::Stato_Neurone::negativo;
  pf::Pattern p3;
  p3[24] = pf::Stato_Neurone::negativo;
  p3[17] = pf::Stato_Neurone::negativo;
  p3[14] = pf::Stato_Neurone::negativo;
  p3[19] = pf::Stato_Neurone::negativo;
  p3[8]  = pf::Stato_Neurone::negativo;

  std::vector<pf::Pattern> vp{p1, p2, p3};
  pf::Matrice_Pesi hebbs;
  hebbs.calcolo_matrice(vp);
  CHECK(hebbs(3, 3) == 0.0);
  CHECK(hebbs(24, 19) == doctest::Approx(3 / pf::N_neuroni).epsilon(1e-5));
  CHECK(hebbs(2, 3) == doctest::Approx(1 / pf::N_neuroni).epsilon(1e-5));
  CHECK(hebbs(2, 19) == doctest::Approx(-1 / pf::N_neuroni).epsilon(1e-5));
  CHECK(hebbs(14, 8) == doctest::Approx(3 / pf::N_neuroni).epsilon(1e-5));
}

TEST_CASE("Testo Matrice_Pesi - calcolo_matrice - verifico diagonale nulla")
{
  pf::Pattern p1;
  p1[2]  = pf::Stato_Neurone::negativo;
  p1[3]  = pf::Stato_Neurone::negativo;
  p1[4]  = pf::Stato_Neurone::negativo;
  p1[19] = pf::Stato_Neurone::negativo;
  p1[24] = pf::Stato_Neurone::negativo;
  pf::Pattern p2;
  p2[6]  = pf::Stato_Neurone::negativo;
  p2[13] = pf::Stato_Neurone::negativo;
  p2[17] = pf::Stato_Neurone::negativo;
  p2[1]  = pf::Stato_Neurone::negativo;
  p2[11] = pf::Stato_Neurone::negativo;
  pf::Pattern p3;
  p3[24] = pf::Stato_Neurone::negativo;
  p3[7]  = pf::Stato_Neurone::negativo;
  p3[14] = pf::Stato_Neurone::negativo;
  p3[19] = pf::Stato_Neurone::negativo;
  p3[26] = pf::Stato_Neurone::negativo;

  pf::Matrice_Pesi hebbs;
  std::vector<pf::Pattern> vp{p1, p2, p3};
  hebbs.calcolo_matrice(vp);
  for (std::size_t i{0}; i != pf::N_neuroni; ++i) {
    CHECK(hebbs(i, i) == 0);
  }
}

TEST_CASE("Testo Matrice_Pesi - verifico simmetria")
{
  pf::Pattern p1;
  p1[2]  = pf::Stato_Neurone::negativo;
  p1[3]  = pf::Stato_Neurone::negativo;
  p1[4]  = pf::Stato_Neurone::negativo;
  p1[19] = pf::Stato_Neurone::negativo;
  p1[24] = pf::Stato_Neurone::negativo;
  pf::Pattern p2;
  p2[6]  = pf::Stato_Neurone::negativo;
  p2[13] = pf::Stato_Neurone::negativo;
  p2[17] = pf::Stato_Neurone::negativo;
  p2[1]  = pf::Stato_Neurone::negativo;
  p2[11] = pf::Stato_Neurone::negativo;
  pf::Pattern p3;
  p3[24] = pf::Stato_Neurone::negativo;
  p3[7]  = pf::Stato_Neurone::negativo;
  p3[14] = pf::Stato_Neurone::negativo;
  p3[19] = pf::Stato_Neurone::negativo;
  p3[26] = pf::Stato_Neurone::negativo;

  pf::Matrice_Pesi hebbs;
  std::vector<pf::Pattern> vp{p1, p2, p3};
  hebbs.calcolo_matrice(vp);
  {
    for (std::size_t i{0}; i != pf::N_neuroni; ++i) {
      for (std::size_t j{0}; j != pf::N_neuroni; ++j) {
        CHECK(hebbs(i, j) == hebbs(j, i));
      }
    }
  }
}

TEST_CASE("Testo Matrice_Pesi - salvataggio su file contenuto in una cartella "
          "inesistente")
{
  std::filesystem::path p1{"cartella inesistente"};
  std::filesystem::path p2{p1 / "file_test"};
  REQUIRE(std::filesystem::exists(p1) == false);
  pf::Matrice_Pesi hebbs;
  CHECK_THROWS(hebbs.salva(p2));
}

TEST_CASE("Testo Matrice_Pesi - caricamento da file inesistente")
{
  std::filesystem::path p{"file_inesistente"};
  pf::Matrice_Pesi hebbs;
  REQUIRE(std::filesystem::exists(p) == false);
  CHECK_THROWS(hebbs.carica(p));
}

TEST_CASE("Testo Matrice_Pesi - caricamento da formato dati incompatibile")
{
  pf::Matrice_Pesi hebbs;
  std::filesystem::path p{"file_test"};
  std::ofstream file{p};
  REQUIRE(file);
  file << 1. << " " << 2. << " " << 7. << " " << "ciao \n";
  file.close();
  CHECK_THROWS(hebbs.carica(p));
  std::filesystem::remove(p);
}

TEST_CASE("Testo Matrice_Pesi - salva e carica lo stesso oggetto")
{
  std::filesystem::path p{"test_file"};
  pf::Matrice_Pesi iniziale;
  iniziale(1, 5) = 3.5;
  iniziale(3, 8) = 2.;
  iniziale(9, 7) = -2.1;
  pf::Matrice_Pesi finale;
  iniziale.salva(p);
  finale.carica(p);
  CHECK(iniziale == finale);
  std::filesystem::remove(p);
}
