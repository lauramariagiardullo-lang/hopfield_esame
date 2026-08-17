#include "matrice_pesi.hpp"
#include <cmath>

namespace pf {

class Rete_Hopfield
{
  Matrice_Pesi hebbs_;

 public:
  Rete_Hopfield(std::filesystem::path const& file_txt)
  {
    hebbs_.carica(file_txt);
  }

  bool aggiornamento_singolo_neurone(Pattern& corrotto, int i) const

  {
    auto const& riga_i{hebbs_.riga(i)};

    double somma{std::inner_product(riga_i.begin(), riga_i.end(),
                                    corrotto.begin(), 0.0)};
    int neurone_aggiornato{somma > 0 ? +1 : -1};
    return neurone_aggiornato == corrotto[i];
    corrotto[i] = neurone_aggiornato;
  }

  bool convergenza(Pattern const& precedente, Pattern const& attuale)
  {
    return precedente == attuale;
  }
};
} // namespace pf