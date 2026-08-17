#include "pattern.hpp"
namespace pf {

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

} // namespace pf