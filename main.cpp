#include "include/function.hpp"
#include "include/operasi_vektor.hpp"
#include <algorithm>
#include <chrono>
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

namespace layer {

class DenseLayer {
public:
  double (*fungsi_aktivasi)(const double &);
  double (*derivatif_fungsi_aktivasi)(const double &);

  int neuron;
  std::string aktivasi;
  std::vector<std::valarray<double>> kernels;

  DenseLayer(const int &neuron, const std::string &aktivasi,
             const std::pair<size_t, size_t> &kernel_shape,
             const bool &random_kernel) {
    if (aktivasi == "sigmoid") {
      fungsi_aktivasi = Fungsi::Aktivasi::sigmoid;
      derivatif_fungsi_aktivasi = Fungsi::Aktivasi::sigmoid_derivatif;
    } else if (aktivasi == "relu") {
      fungsi_aktivasi = Fungsi::Aktivasi::relu;
      derivatif_fungsi_aktivasi = Fungsi::Aktivasi::relu_derivatif;
    } else if (aktivasi == "tanh") {
      fungsi_aktivasi = Fungsi::Aktivasi::tanh;
      derivatif_fungsi_aktivasi = Fungsi::Aktivasi::tanh_derivatif;
    } else if (aktivasi == "kosong" || aktivasi == "none" ||
               aktivasi == "empty") {
      fungsi_aktivasi = Fungsi::Helper::identitas;
      derivatif_fungsi_aktivasi = Fungsi::Helper::identitas;
    } else {
      std::cerr << "ERROR di fungsi " << __func__ << ": ";
      std::cerr << "argument parameter tidak ada ";
      std::cerr
          << ", yang ada (`relu`, `tanh`, `sigmoid`, atau `none` / `kosong`) ";
      std::cerr << "aktivasi kamu " << aktivasi << std::endl;
      std::exit(EXIT_FAILURE);
    }

    this->aktivasi = aktivasi;
    this->neuron = neuron;

    if (random_kernel) {
      uniform_random_intialization(kernels, kernel_shape, -1.0, 1.0);
    } else {
      unit_matrix_intialization(kernels, kernel_shape);
    }
  }

  DenseLayer(const int &neuron, const std::string &aktivasi,
             const std::vector<std::valarray<double>> &kernel) {
    if (aktivasi == "sigmoid") {
      fungsi_aktivasi = Fungsi::Aktivasi::sigmoid;
      derivatif_fungsi_aktivasi = Fungsi::Aktivasi::sigmoid_derivatif;
    } else if (aktivasi == "relu") {
      fungsi_aktivasi = Fungsi::Aktivasi::relu;
      derivatif_fungsi_aktivasi = Fungsi::Aktivasi::relu_derivatif;
    } else if (aktivasi == "tanh") {
      fungsi_aktivasi = Fungsi::Aktivasi::tanh;
      derivatif_fungsi_aktivasi = Fungsi::Aktivasi::tanh_derivatif;
    } else if (aktivasi == "kosong" || aktivasi == "none" ||
               aktivasi == "empty") {
      fungsi_aktivasi = Fungsi::Helper::identitas;
      derivatif_fungsi_aktivasi = Fungsi::Helper::identitas;
    } else {
      std::cerr << "ERROR di fungsi " << __func__ << ": ";
      std::cerr << "argument parameter tidak ada ";
      std::cerr
          << ", yang ada (`relu`, `tanh`, `sigmoid`, atau `none` / `kosong`) ";
      std::cerr << "aktivasi kamu " << aktivasi << std::endl;
      std::exit(EXIT_FAILURE);
    }

    this->aktivasi = aktivasi;
    this->neuron = neuron;
    this->kernels = kernel;
  }

  DenseLayer(const DenseLayer &layer) = default;

  ~DenseLayer() = default;

  DenseLayer &operator=(const DenseLayer &layer) = default;
  DenseLayer &operator=(DenseLayer &&) = default;
};
} // namespace layer

class NeuralNetwork {
private:
  std::vector<layer::DenseLayer> layers;

  NeuralNetwork(
      const std::vector<std::pair<int, std::string>> &config,
      const std::vector<std::vector<std::valarray<double>>> &kernels) {
    if (config.begin()->second != "none") {
      std::cerr << "ERROR di fungsi " << __func__ << ": ";
      std::cerr << "layer pertama tidak memiliki fungsi aktivasi, tapi ";
      std::cerr << config.begin()->second;
      std::exit(EXIT_FAILURE);
    }

    if (config.size() <= 1) {
      std::cerr << "ERROR di fungsi " << __func__ << ": ";
      std::cerr << "oe ini bukan buat model linear regression, tapi ini neural "
                   "network ";
      std::cerr << "setidaknya kamu harus memiliki 2 layer";
      std::exit(EXIT_FAILURE);
    }

    for (size_t i = 0; i < config.size(); i++) {
      layers.emplace_back(
          layer::DenseLayer(config[i].first, config[i].second, kernels[i]));
    }
    std::cout << "hehey jaringan sudah kita buat " << std::endl;
  }

  std::vector<std::vector<std::valarray<double>>>
  __detail_single_precision(const std::vector<std::valarray<double>> &X) {
    std::vector<std::vector<std::valarray<double>>> details;
    std::vector<std::valarray<double>> current_pass = X;
    details.emplace_back(X);

    for (const auto &l : layers) {
      current_pass = current_pass * l.kernels;
      current_pass = ::apply_function(current_pass, l.fungsi_aktivasi);
      details.emplace_back(current_pass);
    }

    return details;
  }

public:
  NeuralNetwork() = default;

  explicit NeuralNetwork(
      const std::vector<std::pair<int, std::string>> &config) {
    if (config.begin()->second != "none") {
      std::cerr << "ERROR di fungsi " << __func__ << ": ";
      std::cerr << "layer pertama tidak memiliki fungsi aktivasi, tapi ";
      std::cerr << config.begin()->second;
      std::exit(EXIT_FAILURE);
    }

    if (config.size() <= 1) {
      std::cerr << "ERROR di fungsi " << __func__ << ": ";
      std::cerr << "oe ini bukan buat model linear regression, tapi ini neural "
                   "network ";
      std::cerr << "setidaknya kamu harus memiliki 2 layer";
      std::exit(EXIT_FAILURE);
    }

    layers.push_back(layer::DenseLayer(config[0].first, config[0].second,
                                       {config[0].first, config[0].first},
                                       false));

    for (size_t i = 1; i < config.size(); i++) {
      layers.push_back(layer::DenseLayer(config[i].first, config[i].second,
                                         {config[i - 1].first, config[i].first},
                                         true));
    }
  }
  NeuralNetwork(const NeuralNetwork &model) = default;
  ~NeuralNetwork() = default;
  NeuralNetwork &operator=(const NeuralNetwork &model) = default;
  NeuralNetwork(NeuralNetwork &&) = default;
  NeuralNetwork &operator=(NeuralNetwork &&) = default;

  std::pair<std::vector<std::vector<std::valarray<double>>>,
            std::vector<std::vector<std::valarray<double>>>>
  get_xy_dari_csv(const std::string &file_name, const bool &last_label,
                  const bool &normalize, const int &slip_lines = 1) {
    std::ifstream in_file;
    in_file.open(file_name.c_str(), std::ios::in);

    if (!in_file.is_open()) {
      std::cerr << "ERROR di fungsi " << __func__ << ": ";
      std::cerr << "tidak bisa buka filenya: " << file_name << std::endl;
      std::exit(EXIT_FAILURE);
    }
    std::vector<std::vector<std::valarray<double>>> X, Y;
    std::string line;

    for (int i = 0; i < slip_lines; i++) {
      std::getline(in_file, line, '\n');
    }

    while (!in_file.eof() && std::getline(in_file, line, '\n')) {
      std::valarray<double> x_data, y_data;
      std::stringstream ss(line);
      std::string token;
      while (std::getline(ss, token, ',')) {
        x_data = ::insert_element(x_data, std::stod(token));
      }

      if (last_label) {
        y_data.resize(this->layers.back().neuron);
        if (y_data.size() > 1) {
          y_data[x_data[x_data.size() - 1]] = 1;
        } else {
          y_data[0] = x_data[x_data.size() - 1];
        }
        x_data = ::pop_back(x_data);
      } else {
        y_data.resize(this->layers.back().neuron);
        if (y_data.size() > 1) {
          y_data[x_data[x_data.size() - 1]] = 1;
        } else {
          y_data[0] = x_data[x_data.size() - 1];
        }
        x_data = ::pop_back(x_data);
      }
      X.push_back({x_data});
      Y.push_back({y_data});
    }

    if (normalize) {
      X = ::minmax_scaling(X, 0.01, 1.0);
    }
    in_file.close();
    return std::make_pair(X, Y);
  }

  std::vector<std::valarray<double>>
  single_prediksi(const std::vector<std::valarray<double>> &X) {
    auto aktivasi = this->__detail_single_precision(X);
    return aktivasi.back();
  }

  std::vector<std::vector<std::valarray<double>>>
  batch_prediksi(const std::vector<std::vector<std::valarray<double>>> &X) {
    std::vector<std::vector<std::valarray<double>>> prediksi_batch(X.size());
    for (size_t i = 0; i < X.size(); i++) {
      prediksi_batch[i] = this->single_prediksi(X[i]);
    }
    return prediksi_batch;
  }

  void fitting_model(const std::vector<std::vector<std::valarray<double>>> &x_,
                     const std::vector<std::vector<std::valarray<double>>> &y_,
                     const int &epoch = 100, const double &learning_rate = 0.01,
                     const size_t &batch_size = 32,
                     const bool &shuffle = true) {
    std::vector<std::vector<std::valarray<double>>> x = x_, y = y_;

    if (x.size() != y.size()) {
      std::cerr << "ERROR (" << __func__ << ") : ";
      std::cerr << "x dan y ukurannya beda dalam fitting model" << std::endl;
      std::exit(EXIT_FAILURE);
    }

    std::cout << "INFO: memulai training" << std::endl;

    for (int epoch_data = 1; epoch_data <= epoch; epoch_data++) {
      if (shuffle) {
        equal_shuffle(x, y);
      }
      auto start = std::chrono::high_resolution_clock::now();
      double loss = 0, acc = 0;

      for (size_t batch_start = 0; batch_start < x.size();
           batch_start += batch_size) {
        for (size_t i = batch_start;
             i < std::min(x.size(), batch_start + batch_size); i++) {
          std::vector<std::valarray<double>> grad;
          std::vector<std::valarray<double>> cur_error;
          std::vector<std::valarray<double>> prediksi;
          auto aktivasi = this->__detail_single_precision(x[i]);

          std::vector<std::vector<std::valarray<double>>> gradient;
          gradient.resize(this->layers.size());
          for (size_t i = 0; i < gradient.size(); i++) {
            zero_initialization(gradient[i],
                                get_shape(this->layers[i].kernels));
          }
          prediksi = aktivasi.back();
          cur_error = prediksi - y[i];
          loss += sum(apply_function(cur_error, Fungsi::Helper::square));

          if (argmax(prediksi) == argmax(y[i])) {
            acc += 1;
          }

          for (size_t j = this->layers.size() - 1; j >= 1; j--) {
            cur_error = hadamard_product(
                cur_error,
                apply_function(aktivasi[j + 1],
                               this->layers[j].derivatif_fungsi_aktivasi));

            grad = transpose(aktivasi[j]) * cur_error;
            cur_error = cur_error * transpose(this->layers[j].kernels);
            gradient[j] = gradient[j] + grad / double(batch_size);
          }

          for (size_t j = this->layers.size() - 1; j >= 1; j--) {
            this->layers[j].kernels =
                this->layers[j].kernels - gradient[j] * learning_rate;
          }
        }
      }

      auto stop = std::chrono::high_resolution_clock::now();
      auto duration =
          std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

      loss /= x.size();
      acc /= x.size();
      std::cout.precision(0);
      std::cout << ", training: epoch - " << epoch << '/' << epoch_data;
      std::cout << ", loss: " << loss;
      std::cout << ", akurasi: " << acc;
      std::cout << ", waktu: " << duration.count() / 1e6 << " detik";
      std::cout << std::endl;
    }
    return;
  }

  void fitting_dari_csv(const std::string &file_name, const bool &last_label,
                        const int &epochs, const double &learning_rate,
                        const bool &normalize, const int &slip_lines = 1,
                        const size_t &batch_size = 32,
                        const bool &shuffle = true) {
    auto data =
        this->get_xy_dari_csv(file_name, last_label, normalize, slip_lines);
    this->fitting_model(data.first, data.second, epochs, learning_rate,
                        batch_size, shuffle);
    return;
  }

  void evaluasi(const std::vector<std::vector<std::valarray<double>>> &X,
                const std::vector<std::vector<std::valarray<double>>> &Y) {
    std::cout << "INGFO: evaluasi model gass " << std::endl;
    double acc = 0, loss = 0;
    for (size_t i = 0; i < X.size(); i++) {
      std::vector<std::valarray<double>> prediksi = this->single_prediksi(X[i]);

      if (argmax(prediksi) == argmax(Y[i])) {
        acc += 1;
      }
      loss +=
          sum(apply_function((Y[i] - prediksi), Fungsi::Helper::square) * 0.5);
    }

    acc /= X.size();
    loss /= X.size();
    std::cout << "evaluasi loss: " << loss;
    std::cout << ", ini akurasinya: " << acc << std::endl;
    return;
  }

  void evaluasi_dari_csv(const std::string &file_name, const bool &last_label,
                         const bool &normalize, const int &slip_lines = 1) {
    auto data = this->get_xy_dari_csv(file_name, last_label, slip_lines);
    this->evaluasi(data.first, data.second);
    return;
  }

  void save_model(const std::string &_file_name) {
    std::string file_name = _file_name;
    if (file_name.find(".model") == file_name.npos) {
      file_name += ".model";
    }

    std::ofstream out_file;
    out_file.open(file_name.c_str(), std::ofstream::out | std::ofstream::trunc);

    if (!out_file.is_open()) {
      std::cerr << "ERROR di fungsi " << __func__ << ": ";
      std::cerr << "gk bisa buka file: " << file_name << std::endl;
      std::exit(EXIT_FAILURE);
    }

    out_file << layers.size();
    out_file << std::endl;
    for (const auto &layer : this->layers) {
      out_file << layer.neuron << ' ' << layer.aktivasi << std::endl;
      const auto shape = get_shape(layer.kernels);
      out_file << shape.first << ' ' << shape.second << std::endl;
      for (const auto &baris : layer.kernels) {
        for (const auto &value : baris) {
          out_file << value << ' ';
        }
        out_file << std::endl;
      }
    }

    std::cout << "INGPO: model disimpan dengan nama: " << file_name
              << std::endl;
    out_file.close();
    return;
  }

  NeuralNetwork load_model(const std::string &file_name) {
    std::ifstream in_file;
    in_file.open(file_name.c_str());

    if (!in_file.is_open()) {
      std::cerr << "ERROR di fungsi " << __func__ << ": ";
      std::cerr << "gak bisa buka file " << file_name << std::endl;
      std::exit(EXIT_FAILURE);
    }

    std::vector<std::pair<int, std::string>> config;
    std::vector<std::vector<std::valarray<double>>> kernel;
    size_t total_layer = 0;
    in_file >> total_layer;
    for (size_t i = 0; i < total_layer; i++) {
      int neuron = 0;
      std::string aktivasi;
      size_t shape_a = 0, shape_b = 0;
      std::vector<std::valarray<double>> kernel;
      in_file >> neuron >> aktivasi >> shape_a >> shape_b;

      for (size_t r = 0; r < shape_a; r++) {
        std::valarray<double> baris(shape_b);
        for (size_t c = 0; c < shape_b; c++) {
          in_file >> baris[c];
        }
        kernel.push_back(baris);
      }
      // config.emplace_back(make_pair(neuron, aktivasi));
      // kernel.emplace_back(kernel);
    }
    std::cout << "INGPO: model sudah kita load " << std::endl;
    in_file.close();
    return NeuralNetwork(config, kernel);
  }

  void hasil() {
    std::cout << "-----------------------------------------------------"
              << std::endl;
    std::cout << "\t\t model kita dari scracth untuk nn\t\t" << std::endl;
    std::cout << "-----------------------------------------------------"
              << std::endl;
    for (size_t i = 1; i <= layers.size(); i++) {
      std::cout << i << ")";
      std::cout << "neuron: " << layers[i - 1].neuron;
      std::cout << ", aktivasi: " << layers[i - 1].aktivasi;
      std::cout << ", kernel shape: " << get_shape(layers[i - 1].kernels);
      std::cout << std::endl;
    }
    std::cout << "-=-=-=-=--=-=--=" << std::endl;
    return;
  }
};

static void testing() {
  NeuralNetwork testingNN = NeuralNetwork({
      {4, "none"},
      {6, "relu"},
      {3, "sigmoid"},
  });

  testingNN.hasil();

  testingNN.fitting_dari_csv("dataset/iris.csv", true, 100, 0.6, false, 2, 32,
                             true);
  return;
}

int main() {
  testing();
  return 0;
}
