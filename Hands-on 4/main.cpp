/*
 * Hands-on 4 - Tabla de frecuencia extendida
 * Probabilidad y Estadistica 2026B - TecMM, Unidad Academica Zapopan
 * Autor: Julio Emiliano Palacios Bustamante
 *
 * Agrupa en clases un dataset de numeros reales (30 o mas datos) e imprime,
 * en el orden del enunciado:
 *   1. Numero de clases            5. Frecuencia relativa (fr)
 *   2. Limites de clase            6. Frecuencia absoluta acumulada (Fa)
 *   3. Frecuencia absoluta (f)     7. Frecuencia relativa acumulada (fra)
 *   4. Marca de clase (Xc)         8. Porcentaje (%)
 *
 * Procedimiento:
 *   k = ceil(1 + 3.322 * log10(n))        (regla de Sturges)
 *   R = max - min                          (rango)
 *   A = R / k, redondeada hacia arriba a la precision de los datos (amplitud)
 *   Clases [Li, Ls) con Ls = Li + A; la ultima clase incluye el maximo.
 *
 * Entradas: ninguna. El dataset esta declarado en el codigo.
 *
 * Compilar:  g++ -std=c++17 -Wall -Wextra -pedantic main.cpp -o hands-on4
 * Ejecutar:  ./hands-on4        (Windows: .\hands-on4.exe)
 */

#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

namespace {

// ---------------------------------------------------------------------------
// Datos y constantes
// ---------------------------------------------------------------------------

// Dataset de ejemplo: tiempo de traslado a la escuela, en minutos, de 40
// estudiantes. Numeros reales con un decimal.
const std::vector<double> kData = {
    12.5, 15.0, 18.3, 20.1, 21.4, 22.8, 23.5, 24.0, 25.6, 26.2,
    27.9, 28.4, 29.0, 30.5, 31.2, 31.8, 32.7, 33.3, 34.1, 35.0,
    35.6, 36.4, 37.2, 38.0, 38.9, 39.5, 40.3, 41.7, 42.2, 43.8,
    44.5, 45.1, 46.9, 48.0, 49.6, 51.3, 53.0, 54.7, 56.2, 58.4};

constexpr std::size_t kMinimumDataSize = 30;   // minimo que pide el enunciado
constexpr int kDataDecimals = 1;               // decimales con que vienen los datos
constexpr double kSturgesFactor = 3.322;       // k = 1 + 3.322 * log10(n)
constexpr double kPercentFactor = 100.0;

constexpr int kValueDecimals = 2;   // decimales de limites y marca de clase
constexpr int kRatioDecimals = 4;   // decimales de fr y fra
constexpr int kNarrowColumn = 8;
constexpr int kWideColumn = 18;

// Factor para pasar los datos a unidades enteras (decimas, con 1 decimal).
// Contar en enteros evita errores de redondeo justo en los limites de clase.
const double kScale = std::pow(10.0, kDataDecimals);

// ---------------------------------------------------------------------------
// Modelo
// ---------------------------------------------------------------------------

struct FrequencyClass {
    int number = 0;                     // numero de clase (1..k)
    double lower = 0.0;                 // limite inferior Li
    double upper = 0.0;                 // limite superior Ls
    double midpoint = 0.0;              // marca de clase Xc
    int absolute = 0;                   // f
    double relative = 0.0;              // fr
    int cumulative = 0;                 // Fa
    double cumulativeRelative = 0.0;    // fra
    double percent = 0.0;               // %
};

struct FrequencyTable {
    std::size_t sampleSize = 0;
    double minimum = 0.0;
    double maximum = 0.0;
    double range = 0.0;
    double width = 0.0;
    std::vector<FrequencyClass> classes;
};

long long toUnits(double value) {
    return std::llround(value * kScale);
}

double fromUnits(long long units) {
    return static_cast<double>(units) / kScale;
}

// Regla de Sturges, redondeada hacia arriba.
int sturgesClassCount(std::size_t sampleSize) {
    const double n = static_cast<double>(sampleSize);
    return static_cast<int>(std::ceil(1.0 + kSturgesFactor * std::log10(n)));
}

FrequencyTable buildFrequencyTable(const std::vector<double>& data) {
    if (data.size() < kMinimumDataSize) {
        throw std::invalid_argument("el dataset debe tener al menos 30 datos");
    }

    const auto [minIt, maxIt] = std::minmax_element(data.begin(), data.end());
    const long long minUnits = toUnits(*minIt);
    const long long rangeUnits = toUnits(*maxIt) - minUnits;
    if (rangeUnits == 0) {
        throw std::domain_error("todos los datos son iguales: no se pueden formar clases");
    }

    const int classCount = sturgesClassCount(data.size());

    // Amplitud redondeada hacia arriba: ceil(R / k) en unidades enteras.
    const long long widthUnits = (rangeUnits + classCount - 1) / classCount;

    // Frecuencia absoluta de cada clase.
    std::vector<int> counts(static_cast<std::size_t>(classCount), 0);
    for (const double value : data) {
        const long long offset = toUnits(value) - minUnits;
        // La division entera da la clase; el maximo puede caer justo en el
        // limite superior de la ultima clase, por eso se limita a k - 1.
        const long long index = std::min<long long>(offset / widthUnits, classCount - 1);
        ++counts[static_cast<std::size_t>(index)];
    }

    FrequencyTable table;
    table.sampleSize = data.size();
    table.minimum = *minIt;
    table.maximum = *maxIt;
    table.range = fromUnits(rangeUnits);
    table.width = fromUnits(widthUnits);

    const double n = static_cast<double>(data.size());
    int cumulative = 0;
    for (int i = 0; i < classCount; ++i) {
        FrequencyClass row;
        row.number = i + 1;
        row.lower = fromUnits(minUnits + i * widthUnits);
        row.upper = fromUnits(minUnits + (i + 1) * widthUnits);
        row.midpoint = (row.lower + row.upper) / 2.0;
        row.absolute = counts[static_cast<std::size_t>(i)];
        row.relative = row.absolute / n;
        cumulative += row.absolute;
        row.cumulative = cumulative;
        row.cumulativeRelative = cumulative / n;
        row.percent = row.relative * kPercentFactor;
        table.classes.push_back(row);
    }

    // Invariante: la ultima frecuencia acumulada debe ser n.
    if (static_cast<std::size_t>(cumulative) != data.size()) {
        throw std::logic_error("la suma de frecuencias no coincide con n");
    }

    return table;
}

// ---------------------------------------------------------------------------
// Salida
// ---------------------------------------------------------------------------

// "[Li, Ls)" para las clases intermedias y "[Li, Ls]" para la ultima.
std::string formatLimits(const FrequencyClass& row, bool isLast) {
    std::ostringstream out;
    out << std::fixed << std::setprecision(kValueDecimals)
        << '[' << row.lower << ", " << row.upper << (isLast ? ']' : ')');
    return out.str();
}

void printSummary(const FrequencyTable& table) {
    std::cout << std::fixed << std::setprecision(kValueDecimals)
              << "Hands-on 4 - Tabla de frecuencia extendida\n"
              << "Datos: n = " << table.sampleSize << '\n'
              << "Minimo = " << table.minimum << "   Maximo = " << table.maximum << '\n'
              << "Rango (R) = " << table.range << '\n'
              << "Numero de clases (k, Sturges) = " << table.classes.size() << '\n'
              << "Amplitud (A) = " << table.width << "\n\n";
}

void printHeader() {
    std::cout << std::setw(kNarrowColumn) << "Clase"
              << std::setw(kWideColumn) << "Limites"
              << std::setw(kNarrowColumn) << "f"
              << std::setw(kNarrowColumn + 2) << "Xc"
              << std::setw(kNarrowColumn + 2) << "fr"
              << std::setw(kNarrowColumn) << "Fa"
              << std::setw(kNarrowColumn + 2) << "fra"
              << std::setw(kNarrowColumn + 2) << "%" << '\n';
}

void printRow(const FrequencyClass& row, bool isLast) {
    std::cout << std::setw(kNarrowColumn) << row.number
              << std::setw(kWideColumn) << formatLimits(row, isLast)
              << std::setw(kNarrowColumn) << row.absolute
              << std::setprecision(kValueDecimals)
              << std::setw(kNarrowColumn + 2) << row.midpoint
              << std::setprecision(kRatioDecimals)
              << std::setw(kNarrowColumn + 2) << row.relative
              << std::setw(kNarrowColumn) << row.cumulative
              << std::setw(kNarrowColumn + 2) << row.cumulativeRelative
              << std::setprecision(kValueDecimals)
              << std::setw(kNarrowColumn + 2) << row.percent << '\n';
}

void printTotals(const FrequencyTable& table) {
    double relativeSum = 0.0;
    double percentSum = 0.0;
    for (const FrequencyClass& row : table.classes) {
        relativeSum += row.relative;
        percentSum += row.percent;
    }

    std::cout << std::setw(kNarrowColumn) << "Total"
              << std::setw(kWideColumn) << ""
              << std::setw(kNarrowColumn) << table.sampleSize
              << std::setw(kNarrowColumn + 2) << ""
              << std::setprecision(kRatioDecimals)
              << std::setw(kNarrowColumn + 2) << relativeSum
              << std::setw(kNarrowColumn) << ""
              << std::setw(kNarrowColumn + 2) << ""
              << std::setprecision(kValueDecimals)
              << std::setw(kNarrowColumn + 2) << percentSum << '\n';
}

void printTable(const FrequencyTable& table) {
    printHeader();
    const std::size_t lastIndex = table.classes.size() - 1;
    for (std::size_t i = 0; i < table.classes.size(); ++i) {
        printRow(table.classes[i], i == lastIndex);
    }
    printTotals(table);
}

}  // namespace

int main() {
    try {
        const FrequencyTable table = buildFrequencyTable(kData);

        std::cout << std::fixed;
        printSummary(table);
        printTable(table);

        return EXIT_SUCCESS;
    } catch (const std::exception& error) {
        std::cerr << "Error: " << error.what() << '\n';
        return EXIT_FAILURE;
    }
}
