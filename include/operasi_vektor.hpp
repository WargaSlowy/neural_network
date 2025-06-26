#ifndef OPERASI_VEKTOR_HPP_
#define OPERASI_VEKTOR_HPP_

#include <iostream>
#include <ostream>
#include <valarray>

/**
 * @brief menampilkan kostum output ke output stream std::cout
 *
 * memungkinkan cetak nilai std::pair seperti
 * std::cout << std::make_pair(2, 5)
 *
 * @tparam T tipe data dari elemen si pair
 * @param out output stream yang sudah di format
 * @param A pasangan nilai yang diberikan
 * @return std::ostream& referensi ke output std::cout
 */
template <typename T>
std::ostream &operator<<(std::ostream &out, const std::pair<T, T> &A) {
  // set presisi angka menjadi 4 digit desimal
  out.precision(4);
  // format output sebagai (nilai_pertama, nilai_kedua)
  std::cout << "(" << A.first << ", " << A.second << ")";
  return out;
}

/**
 * @brief menampilkan isi array ke output std::cout
 *
 * memungkinkan untuk cetak data seperti
 * std::cout << valarray_buatan_kita;
 *
 * @tparam T tipe data yang terdapat pada elemen valarray
 * @param out output stream untuk std::cout
 * @param A valarray yang ingin ditampilkan
 * @return std::ostream& referensi ke outpu std::coutnya
 */
template <typename T>
std::ostream &operator<<(std::ostream &out, const std::valarray<T> &A) {
  // set nilai presisinya menjadi 4 digit desimal
  out.precision(4);

  // looping semua elemen yang terdapat
  // pada valarray
  for (const auto &a : A) {
    std::cout << a << " ";
  }
  std::cout << std::endl;
  return out;
}

/**
 * @brief menambahkan elemen baru ke akhir dari std::valarray
 *
 * karena si valarray ini tadi tidak bisa di resize secara dynamic
 * maka kita akan membuat valarray baru dengan ukuran ditambahkan 1
 *
 * @tparam T tipe data elemen
 * @param A valarray aslinya
 * @param elemen elemen yang ingin ditambahkan
 * @return std::valarray<T> valarray baru dari elemen yang lama
 */
template <typename T>
std::valarray<T> insert_element(const std::valarray<T> &A, const T &elemen) {
  // kita membuat valarray baru dengan ukuran nantinya ditambahkan
  // dengan 1
  std::valarray<T> B;

  // fungsi untuk menambahkan satu elemen
  B.resize(A.size() + 1);
  // kita salin valarray lama ke valarray baru
  for (size_t i = 0; i < A.size(); i++) {
    B[i] = A[i];
  }
  // kita tambahin nilai baru di elemen si B
  B[B.size() - 1] = elemen;
  return B;
}

#endif // !OPERASI_VEKTOR_HPP_
