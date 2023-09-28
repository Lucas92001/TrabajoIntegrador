#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>
int NUM_DIGITOS = 5;
int NUM_INTENTOS = 10;
int NUM_JUGADORES = 10;
struct Jugador
{
    char nombre[50];
    int intentos;
    int tiempo;
};
void inicializarJugador(struct Jugador *jugador)
{
    jugador->intentos = 0;
    jugador->nombre[0] = '\0';
    jugador->tiempo = 0;
}
int generarNumeroAleatorio()
{
    return rand() % 90000 + 10000;
}
int compararJugadores(const void *a, const void *b)
{
    const struct Jugador *jugadorA = (const struct Jugador *)a;
    const struct Jugador *jugadorB = (const struct Jugador *)b;
    if (jugadorA->intentos == jugadorB->intentos)
    {
        return (jugadorA->tiempo < jugadorB->tiempo) ? -1 : 1;
    }
    return (jugadorA->intentos - jugadorB->intentos);
}
void compararNumeros(int numeroOculto, int numeroPropuesto, int *correctos, int *malUbicados, char
numCorrectos[], char numCorrectosMalOrdenados[])
{
    int digitosOcultos[NUM_DIGITOS];
    int digitosPropuestos[NUM_DIGITOS];
    for (int i = NUM_DIGITOS - 1; i >= 0; i--)
    {
        digitosOcultos[i] = numeroOculto % 10;
        numeroOculto /= 10;
        digitosPropuestos[i] = numeroPropuesto % 10;numeroPropuesto /= 10;
    }
    int correctosCount = 0;
    int malUbicadosCount = 0;
    for (int i = 0; i < NUM_DIGITOS; i++)
    {
        if (digitosPropuestos[i] == digitosOcultos[i])
        {
            correctosCount++;
            numCorrectos[i] = digitosPropuestos[i] + '0';
        }
        else
        {
            for (int j = 0; j < NUM_DIGITOS; j++)
            {
                if (digitosPropuestos[i] == digitosOcultos[j])
                {
                    malUbicadosCount++;
                    numCorrectosMalOrdenados[i] = digitosPropuestos[i] + '0';
                    break;
                }
            }
        }
    }
    *correctos = correctosCount;
    *malUbicados = malUbicadosCount;
}
int main()
{
    char respuesta;
    struct Jugador ranking[NUM_JUGADORES];
    for (int i = 0; i < NUM_JUGADORES; i++)
    {
        inicializarJugador(&ranking[i]);
    }
    do
    {
        srand(time(NULL));
        printf("\nBienvenido al juego La Palabra del Día con números.\n");
        printf("Ingresa tu nombre (debe ser una palabra y sin espacios): ");
        char nombre[50];
        scanf("%s", nombre);printf("\n\nHola, %s. vamos a jugar un juego.\n", nombre);
        printf("\nLa consigna es la siguiente: debes tratar de adivinar \n un número de 5 dígitos que solo yo y Dios sabemos\n");
        printf("\nTe diré cuantas y cuáles cifras acertaste \nexactamente, cuáles son incorrectas, y cuáles están, pero en otra posición.\n");
        printf("\nTienes 10 intentos.\n(Presione ENTER para comenzar el juego)");
        getchar();
        getchar();
        printf("\n============================\n");
        printf("¡Que empiece el juego!\n");
   
        int numeroOculto = generarNumeroAleatorio();
   //     printf("\nNumero oculto: %d \n", numeroOculto);
        time_t inicio = time(NULL);
       
        int numero, intentosRealizados = 1;
        while (intentosRealizados <= NUM_INTENTOS)
        {
            printf("\nIntento %d: Ingresa un numero de %d cifras: ", intentosRealizados, NUM_DIGITOS);
            scanf("%d", &numero);
            int longitud;
            longitud= floor(log10(abs(numero)))+1;
            while (longitud != 5){
                printf("Por favor coloca un numero de %d cifras: ", NUM_DIGITOS);
                scanf("%d", &numero);
                longitud= floor(log10(abs(numero)))+1;
            }
            int correctos = 0, malUbicados = 0;
            char numerosCorrectos[NUM_DIGITOS];
            char numerosCorrectosMalOrdenados[NUM_DIGITOS];
            for (int i = 0; i < NUM_DIGITOS; i++)
            {
                numerosCorrectos[i] = '-';
                numerosCorrectosMalOrdenados[i] = '-';
            }
            compararNumeros(numeroOculto, numero, &correctos, &malUbicados, numerosCorrectos,
numerosCorrectosMalOrdenados);
            if (correctos == NUM_DIGITOS)
            {
                printf("\nFelicidades! Adivinaste el numero secreto en %d intentos.\n", intentosRealizados);
                time_t fin = time(NULL);
                int tiempo = fin - inicio;
                int minutos, segundos;
                if (tiempo > 60)
                {
                    minutos = tiempo / 60;
                    segundos = tiempo % 60;
                }struct Jugador jugador;
                strcpy(jugador.nombre, nombre);
                jugador.intentos = intentosRealizados;
                jugador.tiempo = tiempo;
                for (int i = 0; i < NUM_JUGADORES; i++)
                {
                    if (ranking[i].intentos == 0)
                    {
                        ranking[i] = jugador;
                        break;
                    }
                }
                if (tiempo < 60)
                {
                    printf("- Te demoraste: %ds\n", tiempo);
                }
                else
                {
                    printf("Te demoraste: %dm %ds\n", minutos, segundos);
                }
                break;
            }
            else
            {
                printf("- Resultado del intento %d:\n", intentosRealizados);
                printf("- Digitos correctos en la posicion correcta: ");
                for (int i = 0; i < NUM_DIGITOS; i++)
                {
                    printf("%c", numerosCorrectos[i]);
                }
                printf("\n- Digitos correctos en la posicion incorrecta: ");
                for (int i = 0; i < NUM_DIGITOS; i++)
                {
                    printf("%c", numerosCorrectosMalOrdenados[i]);
                }
                printf("\n- Digitos incorrectos: %d numeros\n", NUM_DIGITOS - (correctos + malUbicados));
                if (intentosRealizados == NUM_INTENTOS)
                {
                    printf("\nLo siento, has agotado tus %d intentos. El numero secreto era %d.\n",
NUM_INTENTOS, numeroOculto);
                }
                else
                {
                    printf("Sigue intentando...\n");
                }
            }
            intentosRealizados++;}
        qsort(ranking, NUM_JUGADORES, sizeof(struct Jugador), compararJugadores);
        printf("\nRanking:\n");
        int posicion = 0;
        for (int i = 0; i < NUM_JUGADORES; i++)
        {
            if (ranking[i].intentos > 0)
            {
                printf("%d. %s - Intentos: %d, ", posicion + 1, ranking[i].nombre, ranking[i].intentos);
                int tiempo = ranking[i].tiempo;
                int minutos = tiempo / 60;
                int segundos = tiempo % 60;
                if (tiempo < 60)
                {
                    printf("Tiempo: %ds\n", tiempo);
                }
                else
                {
                    printf("Tiempo: %dm %ds\n", minutos, segundos);
                }
                posicion++;
            }
        }
        printf("\n\n¿Deseas jugar otra vez? (S/N): ");
        scanf(" %s", &respuesta);
    } while (respuesta == 'S' || respuesta == 's');
    printf("\nGracias por jugar.\n");
    return 0;
}