#ifndef OPERASI_VEKTOR_HPP_
#define OPERASI_VEKTOR_HPP_

#include <chrono>
#include <cstdlib>
#include <iostream>
#include <ostream>
#include <utility>
#include <valarray>
#include <vector>

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

/**
 * @brief fungsi untuk menghapus element pertama yang terdapat pada array
 *
 * @tparam T template parameter yang akan menampung nilai numerik
 * @param A vektor atau array yang akan diberikan nantinya
 * @return std::valarray<T> hasil penghapusan dari elemen pertama
 */
template <typename T> std::valarray<T> pop_front(const std::valarray<T> &A) {
  // membuat valarray baru
  std::valarray<T> B;
  // resize dengan ukuran dikurangkan dengan 1
  B.resize(A.size() - 1);
  // looping untuk mengkopi data dari A ke B
  for (size_t i = 1; i < A.size(); ++i) {
    B[i - 1] = A[i];
  }

  return B;
}

/**
 * @brief fungsi untuk menghapus elemen terakhir yang terdapat pada array atau
 * list
 *
 * @tparam T parameter yang menampung jenis nilai numerik
 * @param A vektor atau list yang diberikan
 * @return std::valarray<T> hasil baru dengan menghapus elemen terakhir yang
 * terdapat pada list
 */
template <typename T> std::valarray<T> pop_back(const std::valarray<T> &A) {
  // membuat valarray baru
  std::valarray<T> B;
  // resize B dengan size dikurangkan dengan 1
  B.resize(A.size() - 1);
  // copy elemen A ke B dengan menghapus elemen terakhir
  for (size_t i = 0; i < A.size() - 1; i++) {
    B[i] = A[i];
  }
  return B;
}

/**
 * @brief fungsi equal shuffle
 *
 * fungsi ini bertujuan juga untuk nantinya model tidak terbias dengan urutan
 * pada array tertentu, jadi kita akan mengacak data array beserta labelnya
 * secara bersamaan
 *
 * @tparam T template paramater yang akan dimasukkan tipe data nilai
 * @param A input data (misalnya fitur atau citra)
 * @param B input data tapi untuk label (hasil prediksi)
 */
template <typename T>
void equal_shuffle(std::vector<std::vector<std::valarray<T>>> &A,
                   std::vector<std::vector<std::valarray<T>>> &B) {
  // cek apakah size dari A dan B itu sama
  if (A.size() != B.size()) {
    std::cerr << "ERROR di fungsi " << __func__ << ": ";
    std::cerr << "tidak bisa shuffeling dua vektor dengan size yang berbeda ";
    std::cerr << A.size() << " dan " << B.size() << std::endl;
    std::exit(EXIT_FAILURE);
  }

  for (size_t i = 0; i < A.size(); i++) {
    // untuk menetapkan seed random berdasarkan waktu sistem
    std::srand(std::chrono::system_clock::now().time_since_epoch().count());
    // menghasilkan angka acak antara 0 sampai size dari A - 1
    size_t random_index = std::rand() % A.size();
    // swap elemen ke i dengan elemen acak di vektor A dan B secara sama
    // fungsi swap ini memastikan bahwa pair data tetap cocok setelah
    // di random
    std::swap(A[i], A[random_index]);
    std::swap(B[i], B[random_index]);
  }
  return;
}

#endif // !OPERASI_VEKTOR_HPP_
