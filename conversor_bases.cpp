// Conversor de bases numéricas
// Bases suportadas: Binário (2), Octal (8), Decimal (10), Hexadecimal (16) e Base 36
#include <algorithm>
#include <climits>
#include <cstdlib>
#include <iostream>
#include <string>

struct Base {
    int valor;
    std::string nome;
};

const Base BASES[] = {
    {2,  "Binario (base 2)"},
    {8,  "Octal (base 8)"},
    {10, "Decimal (base 10)"},
    {16, "Hexadecimal (base 16)"},
    {36, "Base 36 (0-9 e A-Z)"}
};
const int TOTAL_BASES = sizeof(BASES) / sizeof(BASES[0]);

std::string aparar(const std::string& s) {
    size_t ini = s.find_first_not_of(" \t\r\n");
    if (ini == std::string::npos) return "";
    size_t fim = s.find_last_not_of(" \t\r\n");
    return s.substr(ini, fim - ini + 1);
}

int valorDoDigito(char c) {
    if (c >= '0' && c <= '9') return c - '0';
    if (c >= 'A' && c <= 'Z') return c - 'A' + 10;
    if (c >= 'a' && c <= 'z') return c - 'a' + 10;
    return -1;
}

char digitoDoValor(int v) {
    return static_cast<char>(v < 10 ? '0' + v : 'A' + (v - 10));
}

bool lerNumero(const std::string& entrada, int base, bool& negativo,
               unsigned long long& modulo, std::string& erro) {
    std::string t = aparar(entrada);
    negativo = false;
    modulo = 0;
    size_t i = 0;

    if (!t.empty() && (t[0] == '-' || t[0] == '+')) {
        negativo = (t[0] == '-');
        i = 1;
    }
    if (i >= t.size()) {
        erro = "Digite um numero.";
        return false;
    }

    for (; i < t.size(); ++i) {
        int d = valorDoDigito(t[i]);
        if (d < 0 || d >= base) {
            erro = std::string("Digito invalido '") + t[i] +
                   "' para a base " + std::to_string(base) + ".";
            return false;
        }
        // Verifica overflow antes de multiplicar
        if (modulo > (ULLONG_MAX - d) / base) {
            erro = "Numero grande demais (limite de 64 bits).";
            return false;
        }
        modulo = modulo * base + d;
    }

    if (modulo == 0) negativo = false;  // evita "-0"
    return true;
}

std::string formatarNaBase(unsigned long long n, int base, bool negativo) {
    if (n == 0) return "0";
    std::string r;
    while (n > 0) {
        r += digitoDoValor(static_cast<int>(n % base));
        n /= base;
    }
    if (negativo) r += '-';
    std::reverse(r.begin(), r.end());
    return r;
}

int lerOpcao(const std::string& mensagem, int minimo, int maximo) {
    while (true) {
        std::cout << mensagem;
        std::string linha;
        if (!std::getline(std::cin, linha)) std::exit(0); 
        std::string t = aparar(linha);
        try {
            size_t pos = 0;
            int v = std::stoi(t, &pos);
            if (pos == t.size() && v >= minimo && v <= maximo) return v;
        } catch (...) {
            
        }
        std::cout << "Opcao invalida. Digite um numero de "
                  << minimo << " a " << maximo << ".\n";
    }
}

void mostrarMenu(const std::string& titulo, bool incluirTodas) {
    std::cout << "\n" << titulo << "\n";
    for (int i = 0; i < TOTAL_BASES; ++i) {
        std::cout << "  " << (i + 1) << " - " << BASES[i].nome << "\n";
    }
    if (incluirTodas) std::cout << "  0 - Todas as bases\n";
}

int main() {
    std::cout << "=== CONVERSOR DE BASES ===\n";

    while (true) {
        // 1) Base de origem
        mostrarMenu("Base de ORIGEM:", false);
        int origem = lerOpcao("Escolha (1-5): ", 1, TOTAL_BASES) - 1;

        // 2) Base de destino
        mostrarMenu("Base de DESTINO:", true);
        int destino = lerOpcao("Escolha (0-5): ", 0, TOTAL_BASES) - 1;  // -1 = todas

        // 3) Número a converter
        bool negativo = false;
        unsigned long long modulo = 0;
        std::string erro;

        while (true) {
            std::cout << "\nDigite o numero em " << BASES[origem].nome << ": ";
            std::string entrada;
            if (!std::getline(std::cin, entrada)) return 0;
            if (lerNumero(entrada, BASES[origem].valor, negativo, modulo, erro)) break;
            std::cout << "Erro: " << erro << "\n";
        }

        // 4) Resultado
        std::cout << "\nResultado:\n";
        if (destino >= 0) {
            std::cout << "  " << BASES[destino].nome << ": "
                      << formatarNaBase(modulo, BASES[destino].valor, negativo) << "\n";
        } else {
            for (int i = 0; i < TOTAL_BASES; ++i) {
                std::cout << "  " << BASES[i].nome << ": "
                          << formatarNaBase(modulo, BASES[i].valor, negativo) << "\n";
            }
        }

        // 5) Continuar?
        std::cout << "\nConverter outro numero? (1 = sim, 0 = sair)\n";
        if (lerOpcao("Escolha: ", 0, 1) == 0) break;
    }

    std::cout << "Ate mais!\n";
    return 0;
}