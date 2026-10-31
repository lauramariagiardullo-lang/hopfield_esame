#ifndef PF_RETE_HOPFIELD_HPP
#define PF_RETE_HOPFIELD_HPP

#include "matrice_pesi.hpp"
#include <algorithm>
#include <cassert>
#include <cmath>
#include <iostream>
#include <numeric>
#include <string>

namespace pf {

class Rete_Hopfield
{
  Matrice_Pesi hebb_;

 public:
  Rete_Hopfield() = default;
  explicit Rete_Hopfield(std::filesystem::path const& file_matrice);
  explicit Rete_Hopfield(
      std::size_t n,
      std::filesystem::path const& file_matrice); // solo per i test

  void apprendimento(std::filesystem::path const& cartella_img,
                     std::filesystem::path const& file_txt);

  void aggiornamento_singolo_neurone(Pattern& corrotto, std::size_t i) const;

  Pattern aggiornamento_pattern(Pattern& corrotto);

  double funzione_energia(Pattern const& p) const;

  Pattern convergenza(Pattern& corrotto, std::vector<double>& vettore_energia);

  Pattern richiamo(char metodo_corruzione, Pattern const& originale,
                   std::vector<double>& vettore_energia);

  void pattern_originale_vs_pattern_finale(Pattern const& originale,
                                           Pattern const& finale) const;
};

} // namespace pf
#endif