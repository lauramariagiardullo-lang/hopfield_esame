
#include "pattern.hpp"
#include "costanti.hpp"
#include "doctest.h"

TEST_CASE("testo costruttore (parametrico) - size, stato neuroni")
{
  pf::Pattern p1(7, pf::Stato_Neurone::negativo);
  pf::Pattern p2(5, pf::Stato_Neurone::positivo);
  CHECK(p1.size() == 7);
  CHECK(p2.size() == 5);
  CHECK(p1[0] == pf::Stato_Neurone::negativo);
  CHECK(p1[3] == pf::Stato_Neurone::negativo);
  CHECK(p1[6] == pf::Stato_Neurone::negativo);
  CHECK(p2[1] == pf::Stato_Neurone::positivo);
  CHECK(p2[4] == pf::Stato_Neurone::positivo);
  CHECK(p2[3] == pf::Stato_Neurone::positivo);
}

TEST_CASE("testo Valore_Neurone - pattern misto: positivo e negativo")
{
  pf::Pattern p(10, pf::Stato_Neurone::positivo);
  p[0] = pf::Stato_Neurone::negativo;
  p[6] = pf::Stato_Neurone::negativo;
  p[7] = pf::Stato_Neurone::negativo;
  CHECK(pf::Valore_Neurone(p[0]) == -1);
  CHECK(pf::Valore_Neurone(p[6]) == -1);
  CHECK(pf::Valore_Neurone(p[7]) == -1);
  CHECK(pf::Valore_Neurone(p[2]) == 1);
  CHECK(pf::Valore_Neurone(p[4]) == 1);
  CHECK(pf::Valore_Neurone(p[8]) == 1);
}

TEST_CASE("testo size - pattern vuoto")
{
  pf::Pattern p(0, pf::Stato_Neurone::positivo);
  CHECK(p.size() == 0);
}

TEST_CASE("testo size - pattern della rete")
{
  pf::Pattern p;
  CHECK(static_cast<int>(p.size()) == pf::N_neuroni);
}

TEST_CASE("testo size - pattern con 13 elementi")
{
  pf::Pattern p(13, pf::Stato_Neurone::positivo);
  CHECK(p.size() == 13);
}

TEST_CASE("testo begin e end - pattern vuoto")
{
  pf::Pattern p(0, pf::Stato_Neurone::positivo);
  CHECK(p.begin() == p.end());
}

TEST_CASE("testo begin e end - sola lettura")
{
  pf::Pattern const p_const(8, pf::Stato_Neurone::positivo);
  pf::Pattern p_non_const(10, pf::Stato_Neurone::negativo);
  p_non_const[0] = pf::Stato_Neurone::positivo;
  CHECK(*(p_const.begin()) == pf::Stato_Neurone::positivo);
  CHECK(*(p_const.end() - 1) == pf::Stato_Neurone::positivo);
  CHECK(*(p_non_const.begin()) == pf::Stato_Neurone::positivo);
  CHECK(*(p_non_const.end() - 1) == pf::Stato_Neurone::negativo);
}

TEST_CASE("testo begin e end - modifica elementi")
{
  pf::Pattern p(9, pf::Stato_Neurone::negativo);
  *(p.begin())   = pf::Stato_Neurone::positivo;
  *(p.end() - 1) = pf::Stato_Neurone::positivo;
  CHECK(*(p.begin()) == pf::Stato_Neurone::positivo);
  CHECK(*(p.end() - 1) == pf::Stato_Neurone::positivo);
}

TEST_CASE("testo begin e end - distanza tra gli iteratori")
{
  pf::Pattern p(6, pf::Stato_Neurone::positivo);
  CHECK((p.end() - p.begin()) == 6);
}

TEST_CASE("testo [] - solo lettura")
{
  pf::Pattern const p1(10, pf::Stato_Neurone::positivo);
  pf::Pattern p2(10, pf::Stato_Neurone::negativo);
  CHECK(p1[0] == pf::Stato_Neurone::positivo);
  CHECK(p1[3] == pf::Stato_Neurone::positivo);
  CHECK(p1[7] == pf::Stato_Neurone::positivo);
  CHECK(p1[9] == pf::Stato_Neurone::positivo);
  CHECK(p2[1] == pf::Stato_Neurone::negativo);
  CHECK(p2[2] == pf::Stato_Neurone::negativo);
  CHECK(p2[4] == pf::Stato_Neurone::negativo);
  CHECK(p2[8] == pf::Stato_Neurone::negativo);
}

TEST_CASE("testo [] - modifica elementi")
{
  pf::Pattern p(9, pf::Stato_Neurone::positivo);
  p[0] = pf::Stato_Neurone::negativo;
  p[5] = pf::Stato_Neurone::negativo;
  p[7] = pf::Stato_Neurone::negativo;
  CHECK(p[0] == pf::Stato_Neurone::negativo);
  CHECK(p[5] == pf::Stato_Neurone::negativo);
  CHECK(p[7] == pf::Stato_Neurone::negativo);
  CHECK(p[1] == pf::Stato_Neurone::positivo);
}

TEST_CASE("testo == - pattern uguale a se stesso")
{
  pf::Pattern p(8, pf::Stato_Neurone::negativo);
  CHECK(p == p);
}

TEST_CASE("testo == - pattern con lunghezza diversa")
{
  pf::Pattern p1(8, pf::Stato_Neurone::positivo);
  pf::Pattern p2(5, pf::Stato_Neurone::positivo);
  CHECK((p1 == p2) == false);
}

TEST_CASE("testo == - pattern con stessa lunghezza ma tutti i valori diversi")
{
  pf::Pattern p1(7, pf::Stato_Neurone::positivo);
  pf::Pattern p2(7, pf::Stato_Neurone::negativo);
  CHECK((p1 == p2) == false);
}

TEST_CASE("testo == - pattern con stessa lunghezza e 3 valori diversi")
{
  pf::Pattern p1(9, pf::Stato_Neurone::positivo);
  pf::Pattern p2(9, pf::Stato_Neurone::positivo);
  p2[3] = pf::Stato_Neurone::negativo;
  p2[6] = pf::Stato_Neurone::negativo;
  p2[7] = pf::Stato_Neurone::negativo;
  CHECK((p1 == p2) == false);
}

TEST_CASE("testo == - pattern misti uguali")
{
  pf::Pattern p1(6, pf::Stato_Neurone::positivo);
  pf::Pattern p2(6, pf::Stato_Neurone::negativo);
  p1[1] = pf::Stato_Neurone::negativo;
  p1[2] = pf::Stato_Neurone::negativo;
  p1[4] = pf::Stato_Neurone::negativo;
  p2[0] = pf::Stato_Neurone::positivo;
  p2[3] = pf::Stato_Neurone::positivo;
  p2[5] = pf::Stato_Neurone::positivo;
  CHECK(p1 == p2);
}

TEST_CASE("testo == - pattern della rete e pattern parametrico uguali")
{
  pf::Pattern p_rete;
  pf::Pattern p_parametrico(pf::N_neuroni, pf::Stato_Neurone::positivo);
  CHECK(p_rete == p_parametrico);
}

TEST_CASE("testo == - due pattern vuoti")
{
  pf::Pattern p1(0, pf::Stato_Neurone::positivo);
  pf::Pattern p2(0, pf::Stato_Neurone::positivo);
  CHECK(p1 == p2);
}

TEST_CASE("testo * - double per stato neurone")
{
  double pos{8.0};
  double neg{-15.6};
  pf::Stato_Neurone np{pf::Stato_Neurone::positivo};
  pf::Stato_Neurone nn{pf::Stato_Neurone::negativo};
  CHECK((pos * np) == 8.0);
  CHECK((pos * nn) == -8.0);
  CHECK((neg * np) == -15.6);
  CHECK((neg * nn) == 15.6);
}

TEST_CASE("testo * - 0.0 per stato neurone")
{
  CHECK((0.0 * pf::Stato_Neurone::positivo) == 0.0);
  CHECK((0.0 * pf::Stato_Neurone::negativo) == 0.0);
}

TEST_CASE("testo * - stato neurone per double")
{
  double pos{8.3};
  double neg{-9.4};
  pf::Stato_Neurone np{pf::Stato_Neurone::positivo};
  pf::Stato_Neurone nn{pf::Stato_Neurone::negativo};
  CHECK((np * pos) == 8.3);
  CHECK((nn * pos) == -8.3);
  CHECK((np * neg) == -9.4);
  CHECK((nn * neg) == 9.4);
}

TEST_CASE("testo * - stato neurone per 0.0")
{
  CHECK((pf::Stato_Neurone::positivo * 0.0) == 0.0);
  CHECK((pf::Stato_Neurone::negativo * 0.0) == 0.0);
}

TEST_CASE("Testo curruzione_rumore_casule - probabilità nulla")
{
  double probabilità{0.0};
  std::size_t n{6};
  pf::Pattern originale(n, pf::Stato_Neurone::positivo);
  originale[2] = pf::Stato_Neurone::negativo;
  originale[4] = pf::Stato_Neurone::negativo;
  pf::Pattern corrotto{pf::corruzione_rumore_casuale(originale, probabilità)};
  CHECK(corrotto == originale);
}

TEST_CASE("Testo corruzione_rumore_casuale - probabilità = 1")
{
  double probabilità{1.};
  std::size_t n{6};
  pf::Pattern originale(n, pf::Stato_Neurone::negativo);
  originale[1] = pf::Stato_Neurone::positivo;
  originale[2] = pf::Stato_Neurone::positivo;
  pf::Pattern opposto(n, pf::Stato_Neurone::positivo);
  opposto[1] = pf::Stato_Neurone::negativo;
  opposto[2] = pf::Stato_Neurone::negativo;
  pf::Pattern corrotto{pf::corruzione_rumore_casuale(originale, probabilità)};
  CHECK(corrotto == opposto);
}

TEST_CASE("Testo corruzione_rumore_casuale - pattern originale vuoto")
{
  pf::Pattern originale(0, pf::Stato_Neurone::negativo);
  pf::Pattern corrotto{pf::corruzione_rumore_casuale(originale, 0.8)};
  CHECK(corrotto.size() == 0);
  CHECK(originale == corrotto);
}

TEST_CASE("testo corruzione_rumore_casuale - probabilità corruzione intermedia")
{
  pf::Pattern originale(13, pf::Stato_Neurone::positivo);
  pf::Pattern corrotto{pf::corruzione_rumore_casuale(originale, 0.6)};
  CHECK(originale.size() == corrotto.size());
  CHECK((originale == corrotto) == false);
}
