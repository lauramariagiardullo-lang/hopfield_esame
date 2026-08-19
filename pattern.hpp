#ifndef PF_GET_PATTERN_HPP
#define PF_GET_PATTERN_HPP
#include <string>
#include <vector>
#include <filesystem>

namespace pf {
enum class Stato_Neurone : int8_t
{
  positivo = +1,
  negativo = -1,
};

inline int Valore_Neurone(Stato_Neurone s)
{
  int v{static_cast<int>(s)};
  return v;
}

class Pattern
{
 private:
  std::vector<Stato_Neurone> pattern_;

 public:
  explicit Pattern();

  explicit Pattern(std::size_t n,
                   Stato_Neurone sn); // solo per semplificare i test, evitando
                                      // un numero eccessivo di neuroni

  std::size_t size() const;

  std::vector<Stato_Neurone>::iterator begin();
  std::vector<Stato_Neurone>::iterator end();
  std::vector<Stato_Neurone>::const_iterator begin() const;
  std::vector<Stato_Neurone>::const_iterator end() const;

  Stato_Neurone& operator[](std::size_t i);
  Stato_Neurone const& operator[](std::size_t i) const;

  friend bool operator==(Pattern const& a, Pattern const& b);
};

Pattern corruzione_rumore_casuale(Pattern const& originale, double probabilità);

Pattern corruzione_taglio(Pattern const& originale,
                          std::string metà_selezionata);

std::vector<Pattern> insieme_pattern(std::filesystem::path const& cartella_immagini);

} // namespace pf
#endif