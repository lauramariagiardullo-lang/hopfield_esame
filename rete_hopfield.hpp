#include <filesystem>
#include <vector>

class Matrice_Pesi
{
  std::vector<std::vector<double>> mp;

 public:
 
  double operator()(int riga, int colonna) const
  {
    return mp[riga][colonna];
  }
  void salva(std::filesystem::path const& file_txt) const
  {}
  void carica(std::filesystem::path const& file_txt) const
  {}

};

class Rete_hopfield
{
  Matrice_Pesi Hebbs;

 public:
}