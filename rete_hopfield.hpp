#include "matrice_pesi.hpp"

namespace pf {

class Rete_hopfield
{
  Matrice_Pesi hebbs_;

 public:
  bool convergenza(Pattern const& precedente, Pattern const& attuale)
  {
    return precedente == attuale;
  }
};
} // namespace pf