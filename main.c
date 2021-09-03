#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

int progDinamica(int capacidad, int cantidad, int *capacidades, int *valores, int **solucion, char **colores){
    for(int i =0; i<=capacidad; i++){
        if(capacidades[0] <= i){
            solucion[i][0] = valores[0];
            if(colores)
                colores[i][0] = 'g';
        }
        else{
            solucion[i][0] = 0;
            if(colores)
                colores[i][0] = 'r';
        }
        for(int j=1; j<cantidad; j++){
            int tempValue;
            if(capacidades[j] <= i){
                tempValue = solucion[i - capacidades[j]][j-1] + valores[j];
                if(tempValue>solucion[i][j-1]){
                    solucion[i][j] = tempValue;
                    if(colores)
                        colores[i][j] = 'g';
                }
                else{
                    solucion[i][j] = solucion[i][j-1];
                    if(colores)
                        colores[i][j] = 'r';
                }
            }
            else{
                solucion[i][j] = solucion[i][j-1];
                if(colores)
                    colores[i][j] = 'r';
            }
        }
    }
    return solucion[capacidad][cantidad-1];
}

int greedyBasico(int capacidad, int cantidad, int *capacidades, int *valores, int *solucion){
    int posMayor;
    int valorMayor;
    int valorTotal = 0;
    int utilizado[100] = {0};
    for(int i = 0; i<cantidad; i++){
        valorMayor = -1;
        for(int j = 0; j<cantidad; j++){
            if(((valores[j] > valorMayor && capacidad >= capacidades[j] && valorMayor != -1) || (capacidad >= capacidades[j] && valorMayor == -1)) && !utilizado[j]){
                posMayor = j;
                valorMayor = valores[j];
            }
        }
        if(valorMayor != -1){
            valorTotal += valorMayor;
            capacidad -= capacidades[posMayor];
            utilizado[posMayor] = 1;
            if(solucion)
                solucion[i] = posMayor;
        }
        else
            break;
    }
    return valorTotal;
}

int greedyProporcional(int capacidad, int cantidad, int *capacidades, int *valores, int *solucion){
    int posMayor;
    float valorMayor;
    float valor;
    int valorTotal = 0;
    int utilizado[100] = {0};
    for(int i = 0; i<cantidad; i++){
        valorMayor = -1;
        for(int j = 0; j<cantidad; j++){
            valor = (float)valores[j]/capacidades[j];
            if(((valor > valorMayor && capacidad >= capacidades[j] && valorMayor != -1) || (capacidad >= capacidades[j] && valorMayor == -1)) && !utilizado[j]){
                posMayor = j;
                valorMayor = valor;
            }
        }
        if(valorMayor != -1){
            valorTotal += valores[posMayor];
            capacidad -= capacidades[posMayor];
            utilizado[posMayor] = 1;
            if(solucion)
                solucion[i] = posMayor;
        }
        else
            break;
    }
    return valorTotal;
}

void modoEjemplo(){
    int capacidad = 15;
    int capacidades[6];
    int valores[6];
    int resultado;
    for(int i = 0; i < 6;i++){
        capacidades[i] = (rand() % 7) + 1;
        valores[i] = (rand() % 20) + 1;
    }
    printf("Programacion Dinamica: \n");

    // Inicializacin de la matriz que contiene la solucion de la programacion dinamica
    int **solucionDinamica;
    solucionDinamica = (int **) malloc(16 * sizeof(int*));
    for (int i = 0; i<16; i++) {
        solucionDinamica[i] = (int *) malloc(6 * sizeof(int));
    }

    //Inicializacion de la matriz que contiene los colores de la matriz de la programacion dinamica (g = green, r = red).
    char **colores;
    colores = (char **) malloc(16 * sizeof(char*));
    for (int i = 0; i<16; i++) {
        colores[i] = (char *) malloc(6 * sizeof(char));
    }
    clock_t begin = clock();
    resultado = progDinamica(capacidad, 6, capacidades, valores, solucionDinamica, colores);
    clock_t end = clock();
    printf("Resultado: %d\n", resultado);
    printf("Solucion:\n");
    for(int i =0; i<=capacidad; i++){
        for(int j = 0; j<6;j++){
            printf("%d (%c), ",solucionDinamica[i][j], colores[i][j]);
        }
        printf("\n");
    }
    double tiempo_prog_dinamica = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("Tiempo: %f\n", tiempo_prog_dinamica);
    printf("Greedy Basico: \n");
    begin = clock();

    // En solucion se guarda la solucion, la cual iria de la primera posicion hasta que se encuentre un -1
    int solucionGreedyBasico[6] = {-1,-1,-1,-1,-1,-1};
    resultado = greedyBasico(capacidad, 6, capacidades, valores, solucionGreedyBasico);
    end = clock();
    printf("Resultado: %d\n", resultado);
    printf("Solucion: ");
    int i =0;
    while(solucionGreedyBasico[i] != -1){
        printf("%d, ", solucionGreedyBasico[i]);
        i++;
    }
    printf("\n");
    double tiempo_greedy_basico = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("Tiempo: %f\n", tiempo_greedy_basico);
    printf("Greedy Proporcional: \n");
    int solucionGreedyProporcional[6] = {-1,-1,-1,-1,-1,-1};
    begin = clock();
    resultado = greedyProporcional(capacidad, 6, capacidades, valores, solucionGreedyProporcional);
    end = clock();
    printf("Resultado: %d\n", resultado);
    i =0;
    printf("Solucion: ");
    while(solucionGreedyProporcional[i] != -1){
        printf("%d, ", solucionGreedyProporcional[i]);
        i++;
    }
    printf("\n");
    double tiempo_greedy_prop= (double)(end - begin) / CLOCKS_PER_SEC;
    printf("Tiempo: %f\n", tiempo_greedy_prop);
}

void modoExperimento(int n){
    int capacidad;
    int valor;
    double sumaTotalDinamica, sumaTotalBasico, sumaTotalProporcional;
    int porcCapacidad;
    int resultado;
    int resultadoGreedy;
    int correctasBasico;
    int correctasProporcional;
    double promedioTiemposDinamica[10][10];
    double promedioTiemposBasico[10][10];
    double promedioTiemposProporcional[10][10];
    double porcentajeBasico[10][10];
    double porcentajeProporcional[10][10];
    int valores[100];
    int capacidades[100];
    clock_t begin;
    clock_t end;
    int **solucionDinamica;
    solucionDinamica = (int **) malloc(1001 * sizeof(int*));
    for (int i = 0; i<1001; i++) {
        solucionDinamica[i] = (int *) malloc(100 * sizeof(int));
    }
    for(int i=100; i<=1000; i+=100){
        for(int j=10; j<=100; j+=10){
            sumaTotalDinamica = 0;
            sumaTotalBasico = 0;
            sumaTotalProporcional = 0;
            correctasBasico = 0;
            correctasProporcional = 0;
            for(int k=0; k<n; k++){
                for(int l=0; l<j;l++){
                    porcCapacidad = i*0.4;
                    capacidad = (rand() % porcCapacidad) + 1;
                    valor = (rand()%100)+1;
                    capacidades[l] = capacidad;
                    valores[l] = valor;
                }
                begin = clock();
                resultado = progDinamica(i, j, capacidades, valores, solucionDinamica, NULL);
                end = clock();
                sumaTotalDinamica += (double)(end - begin) / CLOCKS_PER_SEC;
                begin = clock();
                resultadoGreedy = greedyBasico(i, j, capacidades, valores, NULL);
                end = clock();
                sumaTotalBasico += (double)(end - begin) / CLOCKS_PER_SEC;
                if(resultadoGreedy == resultado)
                    correctasBasico++;
                begin = clock();
                resultadoGreedy = greedyProporcional(i, j, capacidades, valores, NULL);
                end = clock();
                sumaTotalProporcional += (double)(end - begin) / CLOCKS_PER_SEC;
                if(resultadoGreedy == resultado)
                    correctasProporcional++;
            }
            promedioTiemposDinamica[(i/100)-1][(j/10)-1] = sumaTotalDinamica/n;
            promedioTiemposBasico[(i/100)-1][(j/10)-1] = sumaTotalBasico/n;
            promedioTiemposProporcional[(i/100)-1][(j/10)-1] = sumaTotalProporcional/n;
            porcentajeBasico[(i/100)-1][(j/10)-1] = (double)correctasBasico*100/n;
            porcentajeProporcional[(i/100)-1][(j/10)-1] = (double)correctasProporcional*100/n;
        }
    }
    printf("El promedio de tiempo que dura la programacion dinamica en milisegundos:\n");
    for(int i=0; i<10;i++){
        for(int j=0;j<10;j++){
            printf("%f, ", promedioTiemposDinamica[i][j]);
        }
        printf("\n");
    }
    printf("El promedio de tiempo que dura el greedy basico en milisegundos:\n");
    for(int i=0; i<10;i++){
        for(int j=0;j<10;j++){
            printf("%f, ", promedioTiemposBasico[i][j]);
        }
        printf("\n");
    }
    printf("El promedio de tiempo que dura el greedy proporcional en milisegundos:\n");
    for(int i=0; i<10;i++){
        for(int j=0;j<10;j++){
            printf("%f, ", promedioTiemposProporcional[i][j]);
        }
        printf("\n");
    }
    printf("El porcentaje de veces que el greedy basico acierta:\n");
    for(int i=0; i<10;i++){
        for(int j=0;j<10;j++){
            printf("%f, ", porcentajeBasico[i][j]);
        }
        printf("\n");
    }
    printf("El porcentaje de veces que el greedy proporcional acierta:\n");
    for(int i=0; i<10;i++){
        for(int j=0;j<10;j++){
            printf("%f, ", porcentajeProporcional[i][j]);
        }
        printf("\n");
    }
}

int main(int argc, char *argv[]){
    srand(time(0));
    if(argc != 2){
        printf("There is required one argument.\n");
        return -1;
    }
    if(strcmp(argv[1],"-X") == 0){
        modoEjemplo();
    }
    else{
        int n;
        if(argv[1][0] == '-' && argv[1][1] == 'E' && argv[1][2] == '=' && isdigit(argv[1][3])){
            sscanf(argv[1], "-E=%d", &n);
            modoExperimento(n);
        }
        else{
            printf("Invalid argument.\n");
        }
    }
    return 0;
}
