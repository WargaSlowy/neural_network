#ifndef OPERASI_VEKTOR_HPP_
#define OPERASI_VEKTOR_HPP_

#include <algorithm>
#include <chrono>
#include <cstdlib>
#include <iostream>
#include <iterator>
#include <ostream>
#include <random>
#include <utility>
#include <valarray>
#include <vector>

namespace OperasiVektor {
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

/**
 * @brief fungsi untuk inialisasi dengan nilai random yang tersebar nantinya
 * secara seragam (uniform) dalam suatu rentang tertentu
 *
 * @tparam T tipe data yang diberikan
 * @param A vektor yang diberikan
 * @param shape ukuran dari vektor
 * @param low nilai terkecil
 * @param high nilai tertinggi
 */
template <typename T>
void uniform_random_intialization(std::vector<std::valarray<T>> &A,
                                  const std::pair<size_t, size_t> &shape,
                                  const T &low, const T &high) {
  // clear value yang terdapat pada vektor A
  A.clear();
  // generator untuk bilangan random
  // menggunakan default_random_engine
  // - aman
  // - lebih akurat
  // - fleksibel
  std::default_random_engine generator(
      // seeding acak berdasarkan waktu dari sistem
      // memastikan bahwasanya tiap kali program dijalankan
      // hasilnya akan selalu berbeda
      std::chrono::system_clock::now().time_since_epoch().count());
  // akan menghasilkan angka random antara low dan high nya tadi
  std::uniform_real_distribution<T> distribusi_nilai(low, high);
  // looping untuk membuat matriks sesuai ukuran dari si shape
  for (size_t i = 0; i < shape.first; i++) {
    std::valarray<T> baris;
    baris.resize(shape.second);
    for (auto &b : baris) {
      b = distribusi_nilai(generator);
    }
    A.push_back(baris);
  }
  return;
}

/**
 * @brief fungsi untuk inialisasi sebagai matriks nantinya untuk matriks
 * identitas
 *
 * @tparam T tipe data yang diberikan nantinya
 * @param A vektor yang nantikan akan dibuat matriks identitas
 * @param shape ukuran vektor yang diberikan
 */
template <typename T>
void unit_matrix_intialization(std::vector<std::valarray<T>> &A,
                               std::pair<size_t, size_t> &shape) {
  // menghapus elemen value yang terdapat pada matriks
  A.clear();
  // looping per baris dari tiap si vektor
  for (size_t i = 0; i < shape.first; i++) {
    // setiap barisnya nantinya akan diisi nilai awal 0
    // lalu kita akan ubah elemen ke i nya menjadi 1
    // yang nantinya membuat efek diagonal
    std::valarray<T> baris;
    baris.resize(shape.second);
    baris[i] = T(1);
    A.push_back(baris);
  }
  return;
}

/**
 * @brief fungsi untuk membuat matriks nol
 *
 * @tparam T tipe data yang diberikan
 * @param A vektor yang akan dibuat matriks nol
 * @param shape ukuran dari sebuah matriks yang akan dibuat
 */
template <typename T>
void zero_initialization(std::vector<std::valarray<T>> &A,
                         const std::pair<size_t, size_t> &shape) {
  // jika ada data sebelumnya maka kita hapus denga fungsi clear
  A.clear();
  // looping untuk setiap dari baris
  for (size_t i = 0; i < shape.first; i++) {
    // membuat satu baris dengan ukuran dari shape second
    // setiap baris adalah object yang akan di resize ke ukuran yang
    // pas, semua elemen nantinya akan ototmatis diinialisasi ke default
    // nilainya (disini nilainya adalah 0)
    std::valarray<T> baris;
    baris.resize(shape.second);
    A.push_back(baris);
  }
  return;
}

/**
 * @brief fungsi untuk menjumlahkan semua nilai dalam seluruh baris dan kolom
 * dari matriks
 *
 * @tparam T tipe data yang diberikan
 * @param A matriks yang akan dihitung baris dan kolomnya
 * @return T hasil dari hitung semua baris dan kolom (value)
 */
template <typename T> T sum(const std::vector<std::valarray<T>> &A) {
  // inialisasi hasil untuk menampung jumlah total
  T hasil = 0;
  // looping tiap elemen pada matriks
  for (const auto &matriks : A) {
    // a.sum() (sum adalah fungsi bawaan dari si std::valarray) yang akan
    // ngejumlahin semua elemen dalam baris tersebut
    hasil += matriks.sum();
  }
  return hasil;
}

/**
 * @brief fungsi untuk mengabil jumlah ukuran baris dan kolom dari vektor
 *
 * @tparam T tipe data yang akan diberikan
 * @param A vektor yang akan dihitung baris dan kolomnya
 * @return std::pair<size_t, size_t> jumlah ukuran baris dan kolom dari vektor
 */
template <typename T>
std::pair<size_t, size_t> get_shape(const std::vector<std::valarray<T>> &A) {
  const size_t sub_ukuran =
      (
          // iterator ke baris pertama
          // ini adalah bagian dari object dari baris pertama si A
          *A.begin())
          .size(); // jumlah elemen dalam baris (ini adalah jumlah dari si
                   // kolom)

  for (const auto &a : A) {
    if (a.size() != sub_ukuran) {
      std::cerr << "ERROR di fungsi " << __func__ << ": ";
      std::cerr << "panjang matriks / vektor tidak sama" << std::endl;
      std::exit(EXIT_FAILURE);
    }
  }
  // return dari jumlah baris dan kolom
  return std::make_pair(A.size(),  // jumlah dari baris
                        sub_ukuran // jumlah dari kolomnya
  );
}

/**
 * @brief fungsi untuk normalisasi data dengan menggunakan metode rumus minmax
 *
 * @tparam T tipe template dari suatu tipe data
 * @param A vektor yang akan di normalisasikan
 * @param low nilai rendah
 * @param high nilai tinggi
 */
template <typename T>
std::vector<std::vector<std::valarray<T>>>
minmax_scaling(const std::vector<std::vector<std::valarray<T>>> &A,
               const T &low, const T &high) {
  // kita buat salinan dari input agar tidak ngerusakin data aslinya
  std::vector<std::vector<std::valarray<T>>> B = A;
  // fungsi untuk mengembalikan baris dan kolom dari B elemen 0
  const auto shape = get_shape(B[0]);
  // cek validasi dari vektor
  if (shape.first != 1) {
    std::cerr << "ERROR di fungsi " << __func__ << ": ";
    std::cerr << "vektor yang diberikan tidak support untuk normalisasi data, "
                 "shape: ";
    std::cerr << shape << std::endl;
    std::exit(EXIT_FAILURE);
  }

  // looping per kolom
  for (size_t i = 0; i < shape.second; /* ini adalah jumlah kolom */ i++) {
    // untuk setiap fitur dari i, kita akan cari nilai terkecil dan terbesar
    // di seluruh sampel atau kolom
    // fungsi ini penting banget karena normalisasi dilakukan berdasarkan
    // distribusi fitur
    T min = B[0][0][i], max = B[0][0][i];
    for (size_t j = 0; j < B.size(); j++) {
      min = std::min(min, B[j][0][i]);
      max = std::max(max, B[j][0][i]);
    }

    // gass fungsi minmax scaling
    // return semua nilai fitur dari i akan berada dalam rentang low dan high
    for (size_t j = 0; j < B.size(); j++) {
      B[j][0][i] = ((B[j][0][i] - min) / (max - min)) * (high - low) + low;
    }
  }

  return B;
}

/**
 * @brief fungsi untuk mencari posisi (indeks) dari elemen terbesar dalam satu
 * baris data
 *
 * @tparam T tipe data vektor yang diberikan
 * @param A vektor yang akan dihitung argmax nya
 * @return size_t posisi indeks yang dimana terdapat nilai tertingginya
 */
template <typename T> size_t argmax(const std::vector<std::valarray<T>> &A) {
  // untuk validasi format data
  // (jumlah baris, jumlah kolom)
  const auto shape = get_shape(A);

  // validasi apakah data nantinya berupa vektor baris tunggal
  if (shape.first != 1) {
    // jika jumlah baris bukan 1 maka error, karena fungsi ini hanya akan bisa
    // dipakai untuk vektor baris tunggal
    std::cerr << "ERROR di fungsi " << __func__ << ": ";
    std::cerr << "vektor yang diberikan tidak support untuk fungsi argmax"
              << std::endl;
    std::exit(EXIT_FAILURE);
  }

  return std::distance(std::begin(A[0]),
                       std::max_element(std::begin(A[0]), std::end(A[0])));
}

/**
 * @brief fungsi untuk mengkalikan setiap elemen dalam matriks / vektor dengan
 * nilai skalar yang diberikan
 *
 * @tparam T tipe data yang diberikan
 * @param A vektor yang akan dikalikan dengan nilai skalar
 * @param value nilai skalar
 * @return std::vector<std::valarray<T>> hasil vektor dari perkalian skalar
 */
template <typename T>
std::vector<std::valarray<T>> operator*(const std::vector<std::valarray<T>> &A,
                                        const T &value) {
  // menyalin data dari input parameter ke variabel lokal
  std::vector<std::valarray<T>> B = A;
  // looping melalui setiap baris dan kita kalikan dengan nilai
  // skalar
  for (auto &baris : B) {
    baris = baris * value;
  }
  return B;
}

/**
 * @brief fungsi untuk menambahkan setiap elemen dalam matriks / vektor dengan
 * nilai skalar yang diberikan
 *
 * @tparam T tipe data yang diberikan
 * @param A vektor yang akan ditambahkan dengan nilai skalar
 * @param value nilai skalar
 * @return std::vector<std::valarray<T>> hasil vektor dari pertambahan skalar
 */
template <typename T>
std::vector<std::valarray<T>> operator+(const std::vector<std::valarray<T>> &A,
                                        const T &value) {
  // menyalin data dari input parameter ke variabel lokal
  std::vector<std::valarray<T>> B = A;
  // looping melalui setiap baris dan kita tambahkan dengan nilai
  // skalar
  for (auto &baris : B) {
    baris = baris + value;
  }
  return B;
}

/**
 * @brief fungsi untuk membagikan setiap elemen dalam matriks / vektor dengan
 * nilai skalar yang diberikan
 *
 * @tparam T tipe data yang diberikan
 * @param A vektor yang akan dibagikan dengan nilai skalar
 * @param value nilai skalar
 * @return std::vector<std::valarray<T>> hasil vektor dari pembagian skalar
 */
template <typename T>
std::vector<std::valarray<T>> operator/(const std::vector<std::valarray<T>> &A,
                                        const T &value) {
  // menyalin data dari input parameter ke variabel lokal
  std::vector<std::valarray<T>> B = A;
  // looping melalui setiap baris dan kita bagikan dengan nilai
  // skalar
  for (auto &baris : B) {
    baris = baris / value;
  }
  return B;
}

/**
 * @brief fungsi untuk transpose matriks
 *
 * @tparam T tipe data yang diberikan
 * @param A vektor yang akan di transpose
 * @return std::vector<std::valarray<T>> hasil transpose dari matriks yang
 * diberikan
 */
template <typename T>
std::vector<std::valarray<T>>
transpose(const std::vector<std::valarray<T>> &A) {
  // fungsi untuk mengembalikan sebuah ukuran matriks dalam bentuk
  // jumlah baris dan jumlah kolom
  const auto shape = get_shape(A);
  // kita buat salinan untuk matriks A ke B
  std::vector<std::valarray<T>> B;

  // loop per kolom untuk membuat sebuah baris baru
  for (size_t j = 0; j < shape.second; j++) {
    // buat satu baris untuk matriks transpose
    // panjang baris sama dengan jumlah baris dari matriks aslinya
    // karena baris baru berasal dari kolom yang lama
    std::valarray<T> baris;
    baris.resize(shape.first);
    // looping untuk mengisi baris baru dengan elemen dari si kolom
    // ambil elemen ke-i dari kolom si j dari matriks aslinya (A),
    // lalu kita masukin ke baris `baris`
    for (size_t i = 0; i < shape.first; i++) {
      baris[i] = A[i][j];
    }
    B.push_back(baris);
  }
  return B;
}

/**
 * @brief fungsi untuk menjumlahkan dua matriks elemen per elemen, selama ukuran
 * yang diberikan sama
 *
 * @tparam T tipe data yang diberikan
 * @param A vektor nilai pertama
 * @param B vektor nilai kedua
 * @return std::vector<std::valarray<T>> hasil pejumlahan matriks antara A dan B
 */
template <typename T>
std::vector<std::valarray<T>>
operator+(const std::vector<std::valarray<T>> &A,
          const std::vector<std::valarray<T>> &B) {
  // mengambil ukuran atau shape dari tiap matriks
  const auto shape_a = get_shape(A);
  const auto shape_b = get_shape(B);

  // cek validasi apakah si kolom dan baris dari vektor atau matriks A dan B
  // sama
  if (shape_a.first != shape_b.first || shape_a.second != shape_b.second) {
    std::cerr << "ERROR di fungsi " << __func__ << ": ";
    std::cerr << "vektor yang diberikan memiliki shape yang berbeda: ";
    std::cerr << shape_a << " dan " << shape_b << std::endl;
    std::exit(EXIT_FAILURE);
  }

  // matriks baru tempat simpan hasil penjumlahan antara A dan B
  std::vector<std::valarray<T>> C;
  // looping melalui setiap baris dan kita lakukan penjumlahan
  for (size_t i = 0; i < A.size(); i++) {
    // kita tambahkan lalu masukkan ke dalam vektor si C
    C.push_back(A[i] + B[i]);
  }
  return C;
}

/**
 * @brief fungsi untuk mengurangkan dua matriks elemen per elemen, selama ukuran
 * yang diberikan sama
 *
 * @tparam T tipe data yang diberikan
 * @param A vektor nilai pertama
 * @param B vektor nilai kedua
 * @return std::vector<std::valarray<T>> hasil pengurangan matriks antara A dan
 * B
 */
template <typename T>
std::vector<std::valarray<T>>
operator-(const std::vector<std::valarray<T>> &A,
          const std::vector<std::valarray<T>> &B) {
  // mengambil ukuran atau shape dari tiap matriks
  const auto shape_a = get_shape(A);
  const auto shape_b = get_shape(B);

  // cek validasi apakah si kolom dan baris dari vektor atau matriks A dan B
  // sama
  if (shape_a.first != shape_b.first || shape_a.second != shape_b.second) {
    std::cerr << "ERROR di fungsi " << __func__ << ": ";
    std::cerr << "vektor yang diberikan memiliki shape yang berbeda: ";
    std::cerr << shape_a << " dan " << shape_b << std::endl;
    std::exit(EXIT_FAILURE);
  }

  // matriks baru tempat simpan hasil penjumlahan antara A dan B
  std::vector<std::valarray<T>> C;
  // looping mel113alui setiap baris dan kita lakukan penjumlahan
  for (size_t i = 0; i < A.size(); i++) {
    // kita kurangkan lalu masukkan ke dalam vektor si C
    C.push_back(A[i] - B[i]);
  }
  return C;
}

/**
 * @brief fungsi untuk menghitung hasil perkalian antara 2 matriks
 *
 * @tparam T tipe data yang diberikan
 * @param A vektor yang memiliki kolom yang sama dengan si vektor / matriks B
 * @param B vektor yang memiliki baris yang sama dengan si vektor / matriks A
 * @return std::vector<std::valarray<T>> hasil dari perkalian antara 2 vektor a
 * dan b
 */
template <typename T>
std::vector<std::valarray<T>> multiply(const std::vector<std::valarray<T>> &A,
                                       const std::vector<std::valarray<T>> B) {
  // ambil ukuran dari tiap vektor yang diberikan
  const auto shape_a = get_shape(A);
  const auto shape_b = get_shape(B);

  // cek validasi antara 2 vektor
  // jika kolom dari vektor a itu tidak sama dari baris si vektor b
  // maka akan throw error
  if (shape_a.second != shape_b.first) {
    std::cerr << "ERROR di fungsi " << __func__ << ": ";
    std::cerr << "vektor ini tidak bisa digunakan untuk oeprasi perkaian "
                 "karena baris dan kolom berbeda";
    std::cerr << shape_a << " dan " << shape_b << std::endl;
    std::exit(EXIT_FAILURE);
  }

  // buat vektor dengan nama variabelnya hasil
  std::vector<std::valarray<T>> hasil;
  // looping melalui tiap baris dari vektor si A
  for (size_t i = 0; i < shape_a.first; i++) {
    // buat baris baru untuk matriks si hasil
    // panjang baris baru sama dengan jumlah kolom dari si matriks B
    std::valarray<T> baris;
    baris.resize(shape_b.second);
    for (size_t j = 0; j < shape_b.second; j++) {
      for (size_t k = 0; k < shape_a.second; k++) {
        // hitung nilai elemen matriks hasil perkalian
        // ambil elemen -k dari baris i di matriks A
        // kalikan dengan elemen J dari kolom k di matriks B
        // tambahkan ke elemen hasil dari baris[j]
        baris[j] += A[i][k] * B[k][j];
      }
    }
    hasil.push_back(baris);
  }
  return hasil;
}

} // namespace OperasiVektor

#endif // !OPERASI_VEKTOR_HPP_
