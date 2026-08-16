#include "costanti.hpp"
#include "pattern.hpp"
#include <cassert>
#include <numeric>
#include <fstream>

namespace pf {
class Matrice_Pesi
{
  std::vector<std::vector<double>> mp_;

 public:
  double calcolo_elemento_ij(std::vector<Pattern> const& vp, int i, int j)
  {
    double somma_ij{std::accumulate(
        vp.begin(), vp.end(), 0.0,
        [i, j](double somma_ij, Pattern const& p) { p[i] * p[j]; })};
    double elemento_ij{(i == j) ? 0.0 : somma_ij / N_neuroni};
    return elemento_ij;
  }

  void calcolo_matrice(std::vector<Pattern> const& vp)
  {


    assert(mp_.è_simmetrica());
  }


  bool è_simmetrica(){

  }

  auto begin() const
  {
    return mp_.begin();
  }
  auto end() const
  {
    return mp_.end();
  }
  double operator()(int riga, int colonna) const
  {
    return mp_[riga][colonna];
  }
  void salva(std::filesystem::path const& file_txt) const
  {
    std::ofstream file{file_txt};
    if (!file) {
      std::runtime_error("impossibile creare o aprire il file");
    }
    file << *this;
  }
  void carica(std::filesystem::path const& file_txt)
  {
    std::ifstream file(file_txt);
    file >> *this;
  }
};

std::ostream& operator<<(std::ostream& out, Matrice_Pesi const& matrix)
{
  std::for_each(
      matrix.begin(), matrix.end(), [&out](std::vector<double> const& riga) {
        out << '\n';
        std::for_each(riga.begin(), riga.end(), [&out](double n) { out << n; });
      });
  return out;
}

std::istream& operator>>(std::istream& in, Matrice_Pesi const& matrix)
{}
} // namespace pf