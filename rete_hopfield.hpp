#include "costanti.hpp"
#include "pattern.hpp"
#include <filesystem>
#include <vector>

namespace pf {
class Matrice_Pesi
{
  std::vector<std::vector<double>> mp_;

 public:
  double operator()(int riga, int colonna) const
  {
    return mp_[riga][colonna];
  }
  void salva(std::filesystem::path const& file_txt) const
  {}
  void carica(std::filesystem::path const& file_txt) const
  {}
};

class Rete_hopfield
{
  Matrice_Pesi hebbs_;

 public:
  bool convergenza(Pattern const& precedente, Pattern const& attuale)
  {
    return precedente == attuale;
  }
}
} // namespace pf