#include "include/operasi_vektor.hpp"
#include <utility>
#include <valarray>

int main() {

  auto p = std::make_pair(2.6712727417247124, 2.781238192839182);
  std::cout << p << std::endl;
  std::valarray<double> array_kita = {2.34689, 4.2678, 3.3333333, 2.3, 4.2, 5.5, 6.7};
  std::cout << array_kita;

  std::valarray<int> array_pertama = {1, 2, 3};
  auto array_kedua = insert_element(array_pertama, 4);
  std::cout << array_kedua;

  return 0;
}
