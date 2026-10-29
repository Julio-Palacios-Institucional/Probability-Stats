/*
 * Hands-on 3 - Regresion lineal simple (Caso Benetton)
 * Probabilidad y Estadistica 2026B - TecMM, Unidad Academica Zapopan
 * Autor: Julio Emiliano Palacios Bustamante
 *
 * Compilar:  g++ -std=c++17 -Wall -Wextra -pedantic main.cpp -o hands-on3
 * Ejecutar:  ./hands-on3        (Windows: .\hands-on3.exe)
 */

#include <cmath>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <numeric>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

namespace {

// ---------------------------------------------------------------------------
// Datos y constantes
// ---------------------------------------------------------------------------

// Caso Benetton (fuente: https://www.displayr.com/what-is-linear-regression/).
// Solo se usan las columnas Advertising (x) y Sales (y), en millones de euros.
const std::vector<double> kAdvertising = {23, 26, 30, 34, 43, 48, 52, 57, 58};
const std::vector<double> kSales = {651, 762, 856, 1063, 1190, 1298, 1421, 1440, 1518};

// Cinco valores de Advertising que no aparecen en el dataset y quedan dentro
// de su rango observado [23, 58], para no extrapolar fuera de los datos.
const std::vector<double> kNewAdvertising = {25, 32, 40, 50, 55};

constexpr int kDecimals = 4;            // decimales al imprimir
constexpr int kColumnWidth = 16;        // ancho de cada columna de la tabla
constexpr double kZeroTolerance = 1e-12;    // denominador considerado cero
constexpr double kCheckTolerance = 1e-9;    // tolerancia de la prueba de control

// ---------------------------------------------------------------------------
// Modelo
// ---------------------------------------------------------------------------

// Modelo de regresion lineal simple ajustado por minimos cuadrados.
// Los coeficientes se calculan una sola vez, en el constructor.
class SimpleLinearRegression {
public:
    SimpleLinearRegression(const std::vector<double>& x, const std::vector<double>& y);

    double intercept() const { return intercept_; }   // b0
    double slope() const { return slope_; }           // b1

    // Prediccion: y^ = b0 + b1 * x
    double predict(double x) const { return intercept_ + slope_ * x; }

private:
    double intercept_ = 0.0;
    double slope_ = 0.0;
};

SimpleLinearRegression::SimpleLinearRegression(const std::vector<double>& x,
                                               const std::vector<double>& y) {
    if (x.size() != y.size()) {
        throw std::invalid_argument("x e y deben tener el mismo numero de datos");
    }
    if (x.size() < 2) {
        throw std::invalid_argument("se necesitan al menos 2 datos");
    }

    // Las cuatro sumas de las ecuaciones normales.
    const double n = static_cast<double>(x.size());
    const double sumX = std::accumulate(x.begin(), x.end(), 0.0);                // Sx
    const double sumY = std::accumulate(y.begin(), y.end(), 0.0);                // Sy
    const double sumXY = std::inner_product(x.begin(), x.end(), y.begin(), 0.0); // Sxy
    const double sumXX = std::inner_product(x.begin(), x.end(), x.begin(), 0.0); // Sx^2

    // D = n * Sx^2 - (Sx)^2. Es cero cuando todos los x son iguales.
    const double denominator = n * sumXX - sumX * sumX;
    if (std::fabs(denominator) < kZeroTolerance) {
        throw std::domain_error("todos los valores de x son iguales: no hay pendiente unica");
    }

    // b1 primero, porque b0 depende de el.
    slope_ = (n * sumXY - sumX * sumY) / denominator;
    intercept_ = (sumY - slope_ * sumX) / n;
}

// ---------------------------------------------------------------------------
// Verificacion
// ---------------------------------------------------------------------------

bool nearlyEqual(double a, double b) {
    return std::fabs(a - b) < kCheckTolerance;
}

// Prueba de control con el dataset del Hands-on 1, cuyo resultado se conoce:
// D = {(1,4), (2,7), (3,10), (4,13), (5,16)}  ->  b0 = 1, b1 = 3.
// Si falla, el error esta en el calculo, no en los datos de Benetton.
void verifyWithKnownDataset() {
    const SimpleLinearRegression control({1, 2, 3, 4, 5}, {4, 7, 10, 13, 16});
    if (!nearlyEqual(control.intercept(), 1.0) || !nearlyEqual(control.slope(), 3.0)) {
        throw std::logic_error("la prueba de control (Hands-on 1) no dio b0 = 1, b1 = 3");
    }
}

// ---------------------------------------------------------------------------
// Salida
// ---------------------------------------------------------------------------

// Ecuacion como texto, con los coeficientes ya sustituidos.
std::string formatEquation(const SimpleLinearRegression& model) {
    std::ostringstream out;
    out << std::fixed << std::setprecision(kDecimals)
        << "Sales = " << model.intercept()
        << (model.slope() < 0.0 ? " - " : " + ")
        << std::fabs(model.slope()) << " * Advertising";
    return out.str();
}

void printCoefficients(const SimpleLinearRegression& model, std::size_t sampleSize) {
    std::cout << "Hands-on 3 - Regresion lineal simple (Caso Benetton)\n"
              << "Datos: n = " << sampleSize
              << " (x = Advertising, y = Sales, millones de euros)\n\n"
              << "b0 (intercepto) = " << model.intercept() << '\n'
              << "b1 (pendiente)  = " << model.slope() << "\n\n"
              << "Ecuacion de regresion:\n"
              << "  " << formatEquation(model) << "\n\n";
}

void printPredictions(const SimpleLinearRegression& model,
                      const std::vector<double>& newAdvertising) {
    std::cout << "Predicciones de Sales:\n"
              << std::setw(kColumnWidth) << "Advertising"
              << std::setw(kColumnWidth) << "Sales" << '\n';

    for (const double advertising : newAdvertising) {
        std::cout << std::setw(kColumnWidth) << advertising
                  << std::setw(kColumnWidth) << model.predict(advertising) << '\n';
    }
}

}  // namespace

int main() {
    try {
        verifyWithKnownDataset();

        const SimpleLinearRegression model(kAdvertising, kSales);

        std::cout << std::fixed << std::setprecision(kDecimals);
        printCoefficients(model, kAdvertising.size());
        printPredictions(model, kNewAdvertising);

        return EXIT_SUCCESS;
    } catch (const std::exception& error) {
        std::cerr << "Error: " << error.what() << '\n';
        return EXIT_FAILURE;
    }
}
