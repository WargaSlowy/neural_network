#include "include/operasi_vektor.hpp"
#include <algorithm>
#include <iterator>
#include <utility>
#include <valarray>
#include <vector>

int main() {

  // auto p = std::make_pair(2.6712727417247124, 2.781238192839182);
  // std::cout << p << std::endl;
  // std::valarray<double> array_kita =
  // {2.34689, 4.2678, 3.3333333, 2.3, 4.2, 5.5, 6.7}; std::cout << array_kita;
  //
  // std::valarray<int> array_pertama = {1, 2, 3};
  // auto array_kedua = insert_element(array_pertama, 4);
  // std::cout << array_kedua;

  // std::valarray<int> data_kita = {20, 30, 40, 50};
  // std::cout << "sebelum fungsi pop front: " << data_kita << std::endl;
  // data_kita = pop_front(data_kita);
  // std::cout << "sesudah fungsi dari pop front: " << data_kita << std::endl;
  // std::cout << "sebelum fungsi dari pop back: " << data_kita << std::endl;
  // data_kita = pop_back(data_kita);
  // std::cout << "sesudah fungsi dari pop back: " << data_kita << std::endl;

  // std::vector<std::vector<std::valarray<double>>> A = {
  //     {{1.1, 2.2}}, {{3.3, 4.4}}, {{5.5, 6.6}}};
  //
  // std::vector<std::vector<std::valarray<double>>> B = {
  //     {{10.0}},
  //     {{20.0}},
  //     {{30.0}},
  // };
  //
  // std::cout << "sebelum adanya shuffling:\n";
  // for (size_t i = 0; i < A.size(); ++i) {
  //   std::cout << "A[" << i << "] = {" << A[i][0][0] << ", " << A[i][0][1]
  //             << "} -> ";
  //   std::cout << "B[ " << i << "] = {" << B[i][0][0] << "}\n";
  // }
  //
  // equal_shuffle(A, B);
  // std::cout << std::endl;
  // std::cout << "setelah shuffle:";
  // for (size_t i = 0; i < A.size(); ++i) {
  //   std::cout << "A[" << i << "] = {" << A[i][0][0] << ", " << A[i][0][1]
  //             << "} -> ";
  //   std::cout << "B[ " << i << "] = {" << B[i][0][0] << "}\n";
  // }

  // std::vector<std::valarray<double>> matriks;
  // std::pair<size_t, size_t> shape = {3, 4};
  // double low = 0.0, high = 1.0;
  //
  // uniform_random_intialization(matriks, shape, low, high);
  //
  // std::cout.precision(4);
  // std::cout << "matriks hasil inisialisasi yang kita acak:" << std::endl;
  // for (const auto &baris : matriks) {
  //   std::cout << baris << std::endl;
  // }

  // std::vector<std::valarray<double>> matriks;
  // std::pair<size_t, size_t> shape = {3, 4};
  //
  // unit_matrix_intialization(matriks, shape);
  //
  // std::cout << "matriks hasil inisialisasi matriks indentitas:" << std::endl;
  // for (const auto &baris : matriks) {
  //   std::cout << baris;
  // }

  // std::vector<std::valarray<double>> matriks;
  // std::pair<size_t, size_t> shape = {4, 4};
  // zero_initialization(matriks, shape);
  //
  // for (const auto &baris : matriks) {
  //   for (double value : baris) {
  //     std::cout << value << " ";
  //   }
  //   std::cout << std::endl;
  // }

  // std::vector<std::valarray<int>> matriks = {
  // {1, 2, 3},
  // {4, 5, 6},
  // };
  //
  // int total = sum(matriks);
  // std::cout << "totalnya adalah: " << total << std::endl;

  // std::vector<std::valarray<int>> matriks = {
  //     {1, 2, 3},
  //     {4, 5, 4},
  //     {6, 7, 8},
  // };
  //
  // auto shape = get_shape(matriks);
  // std::cout << "ukuran dari matriks adalah: " << shape.first << " x "
  //           << shape.second << std::endl;

  // std::vector<std::vector<std::valarray<double>>> dataset = {
  //     {{1.0, 2.0}}, {{3.0, 4.0}}, {{5.0, 6.0}}};
  //
  // auto normalisasi = minmax_scaling(dataset, 0.0, 1.0);
  //
  // for (const auto &sampel : normalisasi) {
  //   for (const auto &layer : sampel) {
  //     for (double value : layer) {
  //       std::cout << value << " ";
  //     }
  //     std::cout << std::endl;
  //   }
  // }

  // std::vector<std::valarray<double>> nilai_kita = {
  //     {2.0, 1.0, 5.0, 8.3, 4.2},
  // };
  //
  // size_t indeks_tertinggi = argmax(nilai_kita);
  // std::cout << "indeks nilai maksimum terdapat di elemen ke -> "
  //           << indeks_tertinggi << std::endl;

  // std::vector<std::valarray<int>> matriks_kita = {
  //     {1, 2},
  //     {5, 3},
  // };
  //
  // std::vector<std::valarray<int>> B = matriks_kita * 3;
  // for (const auto &baris : B) {
  //   for (int value : baris) {
  //     std::cout << value << " ";
  //   }
  //   std::cout << std::endl;
  // }

  // std::vector<std::valarray<double>> matriks_kita = {
  //     {1.3, 2.30, 3.3},
  //     {4.20, 5.5, 6.10},
  // };
  //
  // std::vector<std::valarray<double>> B = transpose(matriks_kita);
  // std::cout << "hasilnya: " << std::endl;
  // for (const auto &baris : B) {
  //   for (double value : baris) {
  //     std::cout << value << " ";
  //   }
  //   std::cout << std::endl;
  // }

  // std::vector<std::valarray<int>> vektor_kita = {
  //     {1, 2},
  //     {3, 4},
  // };
  //
  // std::vector<std::valarray<int>> matriks_kita_B = {
  //     {5, 6},
  //     {7, 8},
  // };
  //
  // std::vector<std::valarray<int>> C = vektor_kita + matriks_kita_B;
  // for (const auto &baris : C) {
  //   for (int value : baris) {
  //     std::cout << value << " ";
  //   }
  //   std::cout << std::endl;
  // }

  // std::vector<std::valarray<int>> matriks_a = {{1, 2, 3}, {4, 5, 6}};
  // std::vector<std::valarray<int>> matriks_b = {
  //     {7, 8},
  //     {9, 10},
  //     {11, 12},
  // };
  //
  // std::vector<std::valarray<int>> hasil =
  //     OperasiVektor::multiply(matriks_a, matriks_b);
  // std::cout << "hasilnya adalah: " << std::endl;
  // for (const auto &baris : hasil) {
  //   for (int value : baris) {
  //     std::cout << value << " ";
  //   }
  //   std::cout << std::endl;
  // }

  std::vector<std::valarray<int>> matriks_a = {
      {1, 2},
      {3, 4},
  };
  std::vector<std::valarray<int>> matriks_b = {{5, 6}, {7, 8}};

  auto hasil = OperasiVektor::hadamard_product(matriks_a, matriks_b);

  std::cout << "hasil hadamard_product " << std::endl;
  for (const auto &baris : hasil) {
    for (int value : baris) {
      std::cout << value << " ";
    }
    std::cout << std::endl;
  }

  return 0;
}
