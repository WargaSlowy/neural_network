#include "include/operasi_vektor.hpp"
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

  std::vector<std::vector<std::valarray<double>>> A = {
      {{1.1, 2.2}}, {{3.3, 4.4}}, {{5.5, 6.6}}};

  std::vector<std::vector<std::valarray<double>>> B = {
      {{10.0}},
      {{20.0}},
      {{30.0}},
  };

  std::cout << "sebelum adanya shuffling:\n";
  for (size_t i = 0; i < A.size(); ++i) {
    std::cout << "A[" << i << "] = {" << A[i][0][0] << ", " << A[i][0][1]
              << "} -> ";
    std::cout << "B[ " << i << "] = {" << B[i][0][0] << "}\n";
  }

  equal_shuffle(A, B);
  std::cout << std::endl;
  std::cout << "setelah shuffle:";
  for (size_t i = 0; i < A.size(); ++i) {
    std::cout << "A[" << i << "] = {" << A[i][0][0] << ", " << A[i][0][1]
              << "} -> ";
    std::cout << "B[ " << i << "] = {" << B[i][0][0] << "}\n";
  }

  hitung::angka;

  return 0;
}
