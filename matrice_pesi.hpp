#ifndef PF_MATRICE_PESI_HPP
#define PF_MATRICE_PESI_HPP
#include "pattern.hpp"
#include <filesystem>
#include <vector>

namespace pf {
class Matrice_Pesi
{
  std::vector<std::vector<double>> mp_;

 public:
  explicit Matrice_Pesi();

  double calcolo_elemento_ij(std::vector<Pattern> const& vp, std::size_t i,
                             std::size_t j);

  void calcolo_matrice(std::vector<Pattern> const& vp);

  // bool è_simmetrica(){}

  // std::vector<std::vector<double>>::const_iterator begin() const;
  // std::vector<std::vector<double>>::const_iterator end() const;

  std::vector<double> const& riga(std::size_t i) const;

  double& operator()(std::size_t riga, std::size_t colonna);
  double operator()(std::size_t riga, std::size_t colonna) const;

  void salva(std::filesystem::path const& file_txt) const;
  void carica(std::filesystem::path const& file_txt);

  friend std::ostream& operator<<(std::ostream& out,
                                  Matrice_Pesi const& matrix);
};

std::istream& operator>>(std::istream& in, Matrice_Pesi& matrix);
} // namespace pf

#endif