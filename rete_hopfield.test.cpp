#include "rete_hopfield.hpp"
#include "doctest.h"
#include <fstream>

TEST_CASE("testo aggiornamento_singolo_neurone - somma positiva")
{
  std::filesystem::path p{"file"};
  pf::Pattern corrotto(6, pf::Stato_Neurone::positivo);
  corrotto[2] = pf::Stato_Neurone::negativo;
  corrotto[0] = pf::Stato_Neurone::negativo;
  pf::Matrice_Pesi matrix(6);
  matrix(1, 4) = 8.7;
  matrix(4, 1) = 8.7;
  matrix(1, 3) = 6.2;
  matrix(3, 1) = 6.2;
  matrix(1, 2) = 2.1;
  matrix(2, 1) = 2.1;
  matrix(1, 0) = -1.0;
  matrix(0, 1) = -1.0;
  matrix.salva(p);
  pf::Rete_Hopfield rete(6, p);
  rete.aggiornamento_singolo_neurone(corrotto, 1);
  CHECK(corrotto[1] == pf::Stato_Neurone::positivo);
  std::filesystem::remove(p);
}

TEST_CASE("testo aggiornamento_singolo_neurone - somma negativa")
{
  std::filesystem::path p{"file"};
  pf::Pattern corrotto(5, pf::Stato_Neurone::negativo);
  corrotto[1] = pf::Stato_Neurone::positivo;
  corrotto[3] = pf::Stato_Neurone::positivo;
  pf::Matrice_Pesi matrix(5);
  matrix(2, 1) = -3.6;
  matrix(1, 2) = -3.6;
  matrix(2, 4) = 4.8;
  matrix(4, 2) = 4.8;
  matrix(2, 0) = 1.1;
  matrix(0, 2) = 1.1;
  matrix.salva(p);
  pf::Rete_Hopfield rete(5, p);
  rete.aggiornamento_singolo_neurone(corrotto, 2);
  CHECK(corrotto[2] == pf::Stato_Neurone::negativo);
  std::filesystem::remove(p);
}

TEST_CASE("testo aggiornamento_singolo_neurone - somma nulla")
{
  std::filesystem::path p{"file"};
  pf::Pattern corrotto1(5, pf::Stato_Neurone::positivo);
  pf::Pattern corrotto2(5, pf::Stato_Neurone::negativo);
  pf::Matrice_Pesi matrix(5);
  matrix(1, 0) = 1.0;
  matrix(0, 1) = 1.0;
  matrix(1, 2) = -1.0;
  matrix(2, 1) = -1.0;
  matrix.salva(p);
  pf::Rete_Hopfield rete(5, p);
  rete.aggiornamento_singolo_neurone(corrotto1, 1);
  rete.aggiornamento_singolo_neurone(corrotto2, 1);
  CHECK(corrotto1[1] == pf::Stato_Neurone::positivo);
  CHECK(corrotto2[1] == pf::Stato_Neurone::negativo);
  std::filesystem::remove(p);
}
