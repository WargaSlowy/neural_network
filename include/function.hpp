#ifndef FUNCTION_HPP_
#define FUNCTION_HPP_

#include <cmath>

namespace Fungsi {
namespace Aktivasi {

/**
 * @brief fungsi sigmoid
 *
 * fungsi ini mengambil nilai numerik x dan nantinya akan dirubah
 * menjadi antara nilai 0 dan 1
 *
 * @param x nilai logit yang diberikan
 * @return double hasil kalkulasi sigmoid
 */
double sigmoid(const double &x) { return 1.0 / (1.0 + std::exp(-x)); }

/**
 * @brief fungsi turunan dari sigmoid
 *
 * fungsi ini nantinya akan digunakan untuk menghitung gradient error terhadapat
 * si bobot (backpropagation) dan juga nantinya akan mengupdate parameter si
 * model selama fase training
 *
 * @param y input yang merupakan hasil dari output si sigmoid
 * @return double hasil dari turunan sigmoid
 */
double sigmoid_derivatif(const double &y) { return y * (1.0 - y); }

/**
 * @brief fungsi relu untuk mencegah / mengurangi terjadinya vanishing gradient
 *
 * @param x nilai yang diberikan
 * @return double hasil jika lebih dari input maka outputnya input itu sendiri
 * jika kurang dari 0, maka 0
 */
double relu(const double &x) { return std::max(0.0, x); }

/**
 * @brief fungsi relu derivatif
 *
 * @param x nilai yang diberikan output dari fungsi relu
 * @return double hasil dari turunan fungsi relu derivatif
 */
double relu_derivatif(const double &x) { return x >= 0.0 ? 1.0 : 0.0; }

/**
 * @brief fungsi aktivasi tanh untuk menghasilkan nilai rentang antara -1 sampai
 * 1
 *
 * @param x nilai yang akan dihitung
 * @return double akan menghasilkan 1 jika positif besar 0 jika positif kecil
 */
double tanh(const double &x) { return 2.0 / (1.0 + std::exp(-2.0 * x)) - 1.0; }

/**
 * @brief fungsi turunan dari tanh
 *
 * @param y nilai output dari fungsi tanh yang dihitung
 * @return double hasil dari turunan fungsi tanh
 */
double tanh_derivatif(const double &y) { return 1.0 - y * y; }

} // namespace Aktivasi

namespace Helper {

/**
 * @brief fungsi identitas untuk transformasi non-linear nantinya di bagian
 * akhir data
 *
 * @param x nilai yang akan di return
 * @return double hasil dari fungsi identitas
 */
double identitas(const double &x) { return x; }

/**
 * @brief fungsi square
 *
 * @param x nilai yang akan di square dengan x
 * @return int hasil square dari nilai x
 */
double square(const double &x) { return x * x; }
} // namespace Helper

} // namespace Fungsi
#endif // !FUNCTION_HPP_
