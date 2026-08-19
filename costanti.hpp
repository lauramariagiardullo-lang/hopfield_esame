#ifndef PF_COSTANTI_HPP
#define PF_COSTANTI_HPP
#include <cstddef>

namespace pf {
inline constexpr std::size_t altezza_immagine   = 10;
inline constexpr std::size_t larghezza_immagine = 10;
inline constexpr std::size_t N_neuroni = altezza_immagine * larghezza_immagine;
inline constexpr int limite_colore     = 127;
} // namespace pf

#endif