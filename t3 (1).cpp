#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define MAX 10 // Define a ordem da matriz com no maximo 10

// Funcao para imprimir o sistema com os valores atualizados
void imprimirSistema(double solucao[MAX], int n, int passo)
{
    printf("\nMOvimento %d:\n", passo);
    printf("Atual Solução:\n");
    for (int i = 0; i < n; i++)
    {
        printf("x%d = %8.7f\n", i + 1, solucao[i]); // Imprime o valor de cada variável do sistema fornecido
    }
    printf("\n"); // Quebra de linha
}

// Funcao para calcular o erro maximo
double maiorValor(double valores[], int n)
{
    double maior = valores[0];
    for (int i = 1; i < n; i++)
    {
        if (maior < abs(valores[i]))
        {
            maior = abs(valores[i]);
        }
    }
    return maior;
}

// Funcao para calcular o erro maximo
double calcularErro(double xAtual[], double xAnterior[], int n)
{
    double resultados[n];

    // Calcular o erro máximo relativo
    for (int i = 0; i < n; i++)
    {
        resultados[i] = fabs(xAtual[i] - xAnterior[i]);
    }
    double erro = maiorValor(resultados, n) / maiorValor(xAtual, n);
    return erro;
}
// Funcao para calcular o determinante da matriz
double calcularDeterminante(double mat[MAX][MAX], int n)
{
    double det = 1.0;
    double temp[MAX][MAX];
    int i, j, k;

    // Cria uma copia da matriz
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            temp[i][j] = mat[i][j];
        }
    }

    // Reducao da matriz para triangular
    for (i = 0; i < n; i++)
    {
        // Encontrar a linha com o maior valor absoluto na coluna atual
        int maxLinha = i;
        for (k = i + 1; k < n; k++)
        {
            if (fabs(temp[k][i]) > fabs(temp[maxLinha][i]))
            {
                maxLinha = k;
            }
        }

        // Trocar as linhas se necessario
        if (i != maxLinha)
        {
            for (j = 0; j < n; j++)
            {
                double tempValor = temp[i][j];
                temp[i][j] = temp[maxLinha][j];
                temp[maxLinha][j] = tempValor;
            }
            det = -det;
        }

        // Verificar se o pivô é zero
        if (temp[i][i] == 0)
        {
            return 0;
        }

        // Eliminacao gaussiana
        for (k = i + 1; k < n; k++)
        {
            double fator = temp[k][i] / temp[i][i];
            for (j = i; j < n; j++)
            {
                temp[k][j] -= fator * temp[i][j];
            }
        }
        det *= temp[i][i];
    }

    return det;
}

// Funcao principal para o metodo de Gauss-Seidel
void gaussSeidel(double coef[MAX][MAX], double termos[MAX], double solucao[MAX], int n, double precisao)
{
    double xAnterior[MAX]; // Armazena a solução anterior
    double erro;           // Armazena o erro máximo
    int iteracao = 1;      // Contador de iterações

    // Verificar se a matriz é singular
    double determinante = calcularDeterminante(coef, n);
    if (determinante == 0)
    {
        printf("O sistema e impossivel ou indeterminado (determinante e zero).\n");
        return;
    }

    // Inicio da medicao do tempo
    clock_t inicio = clock();

    // Executa o método de Gauss-Seidel até que o erro seja menor que a precisão desejada
    do
    {
        // Copia a solucao atual para xAnterior
        for (int i = 0; i < n; i++)
        {
            xAnterior[i] = solucao[i];
        }

        // Metodo de Gauss-Seidel
        for (int i = 0; i < n; i++)
        {
            double soma = termos[i]; // Inicializa a soma com o termo independente
            for (int j = 0; j < n; j++)
            {
                if (i != j)
                {
                    soma -= coef[i][j] * solucao[j]; // Subtrai os produtos dos coeficientes e as soluções anteriores
                }
            }
            solucao[i] = soma / coef[i][i]; // Atualiza a solução para a variável i
        }

        // Calculo do erro chamando a função de erro
        erro = calcularErro(solucao, xAnterior, n);

        // Exibicao do sistema, erro e solucao a cada passo
        imprimirSistema(solucao, n, iteracao);
        printf("Erro: %8.7f\n", erro);

        iteracao++; // Incrementa o contador de iterações

    } while (erro > precisao); // Continua até que o erro seja menor que a precisão desejada

    // Fim da medicao do tempo
    clock_t fim = clock();
    double tempo_execucao = ((double)(fim - inicio)) / CLOCKS_PER_SEC;

    // Exibicao da solucao final
    printf("\nSolucao final:\n");
    for (int i = 0; i < n; i++)
    {
        printf("x%d = %8.7f\n", i + 1, solucao[i]);
    }
    printf("Tempo de execucao: %f segundos\n", tempo_execucao);
}

int main()
{
    int n;
    double coef[MAX][MAX];
    double termos[MAX];
    double solucao[MAX];
    double precisao;

    // Entrada da ordem da matriz
    printf("Ordem da matriz (max 10): ");
    scanf("%d", &n);

    if (n > MAX)
    {
        printf("A ordem maxima permitida e 10.\n");
        return 1;
    }

    // Entrada dos coeficientes da matriz
    printf("Coeficientes da matriz:\n");
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            scanf("%lf", &coef[i][j]);
        }
    }

    // Entrada dos termos independentes
    printf("Termos independentes:\n");
    for (int i = 0; i < n; i++)
    {
        scanf("%lf", &termos[i]);
    }

    // Entrada da solucao inicial
    printf("Solucao inicial:\n");
    for (int i = 0; i < n; i++)
    {
        scanf("%lf", &solucao[i]);
    }

    // Entrada da precisao desejada
    printf("Precisao desejada: ");
    scanf("%lf", &precisao);

    // Chamada da funcao do metodo de Gauss-Seidel
    gaussSeidel(coef, termos, solucao, n, precisao);

    return 0;
}
