#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "pattern.hpp"
#include "doctest.h"

TEST_CASE("Testo curruzione_rumore_casule - probabilità nulla")
{
  double probabilità{0.0};
  std::size_t n{6};
  pf::Pattern originale(n, pf::Stato_Neurone::positivo);
  originale[2]=pf::Stato_Neurone::negativo;
  originale[4]=pf::Stato_Neurone::negativo;
  pf::Pattern corrotto{pf::corruzione_rumore_casuale(originale, probabilità)};
  CHECK(corrotto == originale);
}

TEST_CASE("Testo corruzione_rumore_casuale - probabilità = 1"){
    double probabilità{1.};
    std::size_t n{6};
    pf::Pattern originale(n, pf::Stato_Neurone::negativo);
    originale[1]=pf::Stato_Neurone::positivo;
    originale[2]=pf::Stato_Neurone::positivo;
    pf::Pattern opposto(n,pf::Stato_Neurone::positivo);
    opposto[1]=pf::Stato_Neurone::negativo;
    opposto[2]=pf::Stato_Neurone::negativo;
    pf::Pattern corrotto{pf::corruzione_rumore_casuale(originale, probabilità)};
    CHECK(corrotto==opposto);
}

