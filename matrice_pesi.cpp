#include "matrice_pesi.hpp"
#include "costanti.hpp"
#include <algorithm>
#include <cassert>
#include <fstream>
#include <numeric>
#include <random>
#include <stdexcept>

namespace pf {

Matrice_Pesi::Matrice_Pesi()
    : mp_(N_neuroni, std::vector<double>(N_neuroni))
{}

double Matrice_Pesi::calcolo_elemento_ij(std::vector<Pattern> const& vp,
                                         std::size_t i, std::size_t j)
{
  assert(i < N_neuroni);
  assert(j < N_neuroni);
  double somma_ij{std::accumulate(
      vp.begin(), vp.end(), 0.0, [i, j](double somma, Pattern const& p) {
        return somma + Valore_Neurone(p[i]) * Valore_Neurone(p[j]);
      })};
  double elemento_ij{(i == j) ? 0.0 : somma_ij / N_neuroni};
  return elemento_ij;
}

void Matrice_Pesi::calcolo_matrice(std::vector<Pattern> const& vp)
{
  for (std::size_t i{0}; i != N_neuroni; ++i) {
    for (std::size_t j{0}; j <= i; ++j) {
      (*this)(i, j) = calcolo_elemento_ij(vp, i, j);
      if (i != j) {
        (*this)(j, i) = (*this)(i, j);
      }
    }
  }
  // assert((*this).è_simmetrica());
}

// std::vector<std::vector<double>>::const_iterator Matrice_Pesi::begin()
// const{return mp_.begin();} std::vector<std::vector<double>>::const_iterator
// Matrice_Pesi::end() const{return mp_.end();}

std::vector<double> const& Matrice_Pesi::riga(std::size_t i) const
{
  assert(i < N_neuroni);
  return mp_[i];
}

double& Matrice_Pesi::operator()(std::size_t riga, std::size_t colonna)
{
  assert(riga < N_neuroni);
  assert(colonna < N_neuroni);
  return mp_[riga][colonna];
}

double Matrice_Pesi::operator()(std::size_t riga, std::size_t colonna) const
{
  assert(riga < N_neuroni);
  assert(colonna < N_neuroni);
  return mp_[riga][colonna];
}

void Matrice_Pesi::salva(std::filesystem::path const& file_txt) const
{
  std::ofstream file{file_txt};
  if (!file) {
    std::runtime_error("impossibile creare o aprire il file");
  }
  file << *this;
}

void Matrice_Pesi::carica(std::filesystem::path const& file_txt)
{
  std::ifstream file(file_txt);
  file >> *this;
}

std::ostream& operator<<(std::ostream& out, Matrice_Pesi const& matrix)
{
  std::for_each(matrix.mp_.begin(), matrix.mp_.end(),
                [&out](std::vector<double> const& riga) {
                  out << '\n';
                  std::for_each(riga.begin(), riga.end(),
                                [&out](double n) { out << n << " "; });
                });
  return out;
}

std::istream& operator>>(std::istream& in, Matrice_Pesi& matrix)
{
  for (std::size_t i{0}; i != N_neuroni; ++i) {
    for (std::size_t j{0}; j != N_neuroni; ++j) {
      in >> matrix(i, j);
    }
  }
  return in;
}

} // namespace pf