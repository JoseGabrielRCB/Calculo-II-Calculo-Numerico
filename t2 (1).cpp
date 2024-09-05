#include <iostream>
#include <vector>
#include <ctime>
#include <iomanip>
#include <limits>
#include <cmath>

using namespace std;

class Matriz
{
private:
    vector<vector<double>> mat;
    int ordem;

public:
    Matriz(int ordem) : ordem(ordem)
    {
        mat.resize(ordem, vector<double>(ordem, 0));
    }

    void carregarElementos()
    {
        cout << "Insira os valores da matriz:\n";
        for (int i = 0; i < ordem; ++i)
        {
            for (int j = 0; j < ordem; ++j)
            {
                cin >> mat[i][j];
            }
        }
    }

    void permutarLinhas(int linha1, int linha2)
    {
        for (int i = 0; i < ordem; ++i)
        {
            swap(mat[linha1][i], mat[linha2][i]);
        }
    }

    void exibirMatriz() const
    {
        for (const auto &linha : mat)
        {
            for (double valor : linha)
            {
                if (fabs(valor) < 1e-10)
                {
                    cout << setw(6) << fixed << setprecision(1) << 0.0 << " ";
                }
                else
                {
                    cout << setw(6) << fixed << setprecision(1) << valor << " ";
                }
            }
            cout << endl;
        }
        cout << endl;
    }

    double calcularDeterminante()
    {
        double det = 1.0;
        int etapa = 1;

        for (int i = 0; i < ordem; ++i)
        {
            int linhaMaior = i;
            for (int k = i + 1; k < ordem; ++k)
            {
                if (fabs(mat[k][i]) > fabs(mat[linhaMaior][i]))
                {
                    linhaMaior = k;
                }
            }

            if (i != linhaMaior)
            {
                permutarLinhas(i, linhaMaior);
                det = -det;
                cout << "Movimento " << etapa++ << " (Inverte de linhas):\n";
                exibirMatriz();
            }

            if (mat[i][i] == 0)
            {
                return 0;
            }

            for (int k = i + 1; k < ordem; ++k)
            {
                double fator = mat[k][i] / mat[i][i];
                for (int j = i; j < ordem; ++j)
                {
                    mat[k][j] -= fator * mat[i][j];
                }
            }

            if (i < ordem - 1)
            {
                cout << "Movimento " << etapa++ << " (Eliminacao de Gauss):\n";
                exibirMatriz();
            }
        }

        for (int i = 0; i < ordem; ++i)
        {
            det *= mat[i][i];
        }

        return det;
    }
};

class Aplicativo
{
public:
    void executar()
    {
        char escolha;

        do
        {
            system("cls"); // Usa "clear" para Unix-like ou "cls" para Windows
            int ordemMatriz;
            cout << "Ordem da matriz (max == 10): ";
            cin >> ordemMatriz;

            while (ordemMatriz > 10 || ordemMatriz <= 0)
            {
                cout << "Valor Invalido\n";
                cout << "Ordem da matriz (max == 10): ";
                cin >> ordemMatriz;
            }

            Matriz matriz(ordemMatriz);
            matriz.carregarElementos();

            clock_t inicio = clock();
            double det = matriz.calcularDeterminante();
            clock_t fim = clock();

            double duracao = static_cast<double>(fim - inicio) / CLOCKS_PER_SEC;

            cout << "Determinante: " << fixed << setprecision(1) << det << endl;
            cout << "Tempo de execucao: " << duracao << " segundos\n";

            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Fazer o calculo de outra matrix (s/n): ";
            escolha = getchar();

        } while (escolha == 's' || escolha == 'S');
    }
};

int main()
{
    Aplicativo app;
    app.executar();
    return 0;
}