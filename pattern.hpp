#ifndef PF_GET_PATTERN_HPP
#define PF_GET_PATTERN_HPP
#include "costanti.hpp"
#include <SFML/Graphics.hpp>
#include <algorithm>
#include <cassert>
#include <filesystem>
#include <stdexcept>
#include <vector>

namespace pf {
enum class Stato_Neurone : int8_t
{
  positivo = +1,
  negativo = -1,
};

int Valore_Neurone(Stato_Neurone s)
{
  int v{static_cast<int>(s)};
  return v;
}
class Pattern
{
 private:
  std::vector<Stato_Neurone> pattern_;

 public:
  Pattern()
      : pattern_(N_neuroni){};

  std::size_t size() const
  {
    return pattern_.size();
  }

  auto begin() const
  {
    return pattern_.begin();
  }
  auto end() const
  {
    return pattern_.end();
  }
};

bool operator==(Pattern const& a, Pattern const& b)
{
  assert(a.size() == N_neuroni);
  assert(b.size() == N_neuroni);
  return std::equal(a.begin(), a.end(), b.begin());
}
} // namespace pf
#endif