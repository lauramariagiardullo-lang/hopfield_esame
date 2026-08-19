#ifndef PF_RETE_HOPFIELD_HPP
#define PF_RETE_HOPFIELD_HPP

#include "matrice_pesi.hpp"
#include <cassert>
#include <cmath>
#include <numeric>

namespace pf {

class Rete_Hopfield
{
  Matrice_Pesi hebbs_;

 public:
  void apprendimento(std::filesystem::path const& cartella_img,
                     std::filesystem::path const& file_txt)
  {
    auto paths{insieme_pattern(cartella_img)};
    hebbs_.calcolo_matrice(paths);
    hebbs_.salva(file_txt);
  }

  void aggiornamento_singolo_neurone(Pattern& corrotto, std::size_t i) const

  {
    assert(i < altezza_immagine);
    auto const& riga_i{hebbs_.riga(i)};

    double somma{std::inner_product(riga_i.begin(), riga_i.end(),
                                    corrotto.begin(), 0.0)};
    Stato_Neurone neurone_aggiornato{somma > 0 ? Stato_Neurone::positivo
                                               : Stato_Neurone::negativo};
    corrotto[i] = neurone_aggiornato;
  }

  Pattern aggiornamento_pattern(Pattern& corrotto)
  {
    for (std::size_t i{0}; i != corrotto.size(); ++i) {
      aggiornamento_singolo_neurone(corrotto, i);
    }
    return corrotto;
  }

  Pattern convergenza(Pattern& corrotto)
  {
    auto precedente{corrotto};
    auto attuale{aggiornamento_pattern(corrotto)};
    if (precedente == attuale) {
      return attuale;
    } else {
      return convergenza(corrotto);
    }
  }

  void richiamo();
};
} // namespace pf

#endif