#ifndef PF_COSTANTI_HPP
#define PF_COSTANTI_HPP
#include <cstddef>
#include <filesystem>

namespace pf {
inline constexpr std::size_t altezza_immagine   = 30;
inline constexpr std::size_t larghezza_immagine = 30;
inline constexpr int N_neuroni     = altezza_immagine * larghezza_immagine;
inline constexpr int limite_colore = 127;
inline const std::filesystem::path path_cartella_immagini{
    "immagini_addestramento_rete"};
inline const std::filesystem::path path_file_matrice_pesi{"matrice_hebb.txt"};
inline constexpr int N_immagini_usate_per_addestramento{11};
} // namespace pf

#endif