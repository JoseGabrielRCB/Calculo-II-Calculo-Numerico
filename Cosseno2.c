#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define pi 3.14159265359
#define piRad 180.0

int Ajustar_90(long double x) // verifica se é um multiplo EXTATO de 90 em 360 graus
{
    if (x < 0.0) // caso seja negativo, retona o positivo
    {
        x *= -1; // tranforma em positivo
    }

    if (x > 360.0) // verifica se o numero é maior que 360
    {
        return Ajustar_90(x - 360.0); // caso seja, reduz ate que seja menor
    } // assim acha o menor valor possivel no circulo trigonometrico

    if (x == 90.0) // verifica se o valor reduzido é 90
    {
        return 1; // retorna verdadeiro
    }

    return 0; // retorna falso
}

long double Conversor_PI(long double x) // COnversor para radianos
{
    return x *= (pi / piRad); // retorna valor convetido
}

int fat(int valor, int aux) // funcao recursiva de fatorial
{
    if (aux <= 1) // caso o aux tenha terminado de decrementar
    {
        return 1; // retorna 1 que nao altera na multi
    }
    

    return fat(valor, aux - 1) * aux;
    // decremente valor de aux ate que seja menor que 2 e *
    // retorna multi final(fatorial)
}

long double cosX(long double x) // calcula o cosseno de X
{
    long double coss = 1; // incia o valor
    int sinal = -1;       // inicia o controlador de sinal

    for (int i = 1; i < 100; i++)
    {

        coss += (pow(x, i * 2) * 1.0 / fat(i * 2, i * 2)) * (sinal); // Formula que calcula aproximadamente o cosseno
        sinal *= -1;                                                 // altera o sinal entre positivo e nagetivo
    }

    return (coss); // retorna o valor do COSS(valor aproximado do cosseno)
}

void menu() // menu primario do sistema
{
    long double x; // incia o valor com o maximo de bits para a precisão
    int aux = 0;   // inicia valor de auxiliar
    printf("DESCUBRA O VALOR DO COSSENO\n\n");

    printf("\nO VALOR ESTA EXPRESSO  EM RADIANOS OU GRAUS\n1-radianos\n2-graus\n");
    scanf("%d", &aux); // recebe o modo em que o usuario vai expressar o angulo

    printf("INSIRA O VALOR DESEJADO\n");
    scanf("%Lf", &x); // insere valo

    if (aux == 1) // expressão em radianos
    {

            long double aux2 = x;
                                 // converte o valor em NUM
            long double aux = cos(x);             // AUX recebe o cos aproximado de x(erro ao tentar fazer print direto)
            printf("COS %Lf PI: %Lf", aux2, aux); // printa o valor para o usuario
    }
    if (aux == 2) // expressão em graus
    {

        system("clear"); // limpa tela para o usuario

        if (Ajustar_90(x) == 1) // verifica se é 90 ou um valor de 90  + x*360
        {
            printf("COS %Lf : %d\n", x, 0); // printa resultado de 90
                                            // e seus correspondentes no circulotrigonometrico
        }
        else
        {
            long double aux2 = x;     // guarda valor de X
            x = Conversor_PI(x);      // converte para radianos
            long double aux = cos(x); // recebe resultado da funcao

            printf("COS %Lf : %Lf\n", aux2, aux); // printa resultado
        }
    }
}

int main()
{
    menu(); // inicia menu principal
    return 0;
}