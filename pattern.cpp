#include "pattern.hpp"
#include "costanti.hpp"
#include "immagine.hpp"
#include <algorithm>
#include <cassert>
#include <filesystem>
#include <random>
#include <stdexcept>
#include <vector>

namespace pf {

Pattern::Pattern()
    : pattern_(N_neuroni, Stato_Neurone::positivo)
{}

Pattern::Pattern(std::size_t n,
                 Stato_Neurone sn) // solo per semplificare i test, evitando un
                                   // numero eccessivo di neuroni
    : pattern_(n, sn)
{}

std::size_t Pattern::size() const
{
  return pattern_.size();
}

std::vector<Stato_Neurone>::iterator Pattern::begin()
{
  return pattern_.begin();
}

std::vector<Stato_Neurone>::iterator Pattern::end()
{
  return pattern_.end();
}

std::vector<Stato_Neurone>::const_iterator Pattern::begin() const
{
  return pattern_.begin();
}
std::vector<Stato_Neurone>::const_iterator Pattern::end() const
{
  return pattern_.end();
}

Stato_Neurone& Pattern::operator[](std::size_t i)
{
  assert(i < N_neuroni);
  return pattern_[i];
}

Stato_Neurone const& Pattern::operator[](std::size_t i) const
{
  assert(i < N_neuroni);
  return pattern_[i];
}

bool operator==(Pattern const& a, Pattern const& b)
{
  assert(a.size() == N_neuroni);
  assert(b.size() == N_neuroni);
  return std::equal(a.pattern_.begin(), a.pattern_.end(), b.pattern_.begin());
}

Pattern corruzione_rumore_casuale(Pattern const& originale, double probabilità)
{
  std::random_device r;
  std::default_random_engine eng{r()};
  std::bernoulli_distribution bernoulli(probabilità);
  Pattern corrotto{originale};
  std::for_each(corrotto.begin(), corrotto.end(), [&](Stato_Neurone& s) {
    if (bernoulli(eng)) {
      s = (s == Stato_Neurone::positivo) ? Stato_Neurone::negativo
                                         : Stato_Neurone::positivo;
    }
  });
  assert(originale.size() == corrotto.size());
  return corrotto;
}

Pattern corruzione_taglio(Pattern const& originale,
                          std::string metà_selezionata)
{
  Pattern corrotto{originale};
  auto inverti = [](Stato_Neurone& sn) {
    sn = (sn == Stato_Neurone::positivo) ? Stato_Neurone::negativo
                                         : Stato_Neurone::positivo;
  };
  if (metà_selezionata == "sup") {
    std::for_each(corrotto.begin(), corrotto.begin() + static_cast<unsigned int>(corrotto.size()) / 2,
                  inverti);

  } else if (metà_selezionata == "inf") {
    std::for_each(corrotto.begin() + static_cast<unsigned int>(corrotto.size()) / 2, corrotto.end(),
                  inverti);

  } else {
    throw std::runtime_error("porzione di taglio non riconosciuta");
  }
  return corrotto;
}

std::vector<Pattern>
insieme_pattern(std::filesystem::path const& cartella_immagini)
{
  auto path{get_file_names(cartella_immagini)};
  std::vector<Pattern> p;
  std::for_each(path.begin(), path.end(), [&](std::filesystem::path const& percorso) {
    Immagine img(percorso);
    p.push_back(img.binarizzazione());
  });
  return p;
}

} // namespace pf