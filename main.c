#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>

FILE *archivo;

void terminaPdf(){
    fputs("\\end{document}", archivo);
    fclose(archivo);
    system("cd Latex && pdflatex main.tex && mv ./main.pdf ../resultado.pdf && cd .. && evince resultado.pdf");
}

void crearPdf(){
    archivo = fopen("Latex/main.tex", "w");
    if(archivo == NULL){
        printf("No se pudo abrir Latex/main.tex");
        exit(0);
    }
    char inicio[] = "\\documentclass[a4paper]{article}\n\\input{head}\n\\begin{document}\n\n%-------------------------------\n%	TITLE SECTION\n%-------------------------------\n\n\\fancyhead[C]{}\n\\hrule \\medskip % Upper rule\n\\begin{minipage}{0.295\\textwidth} % Left side of title section\n\\raggedright\nIO\\\\ % Your lecture or course\n\\footnotesize % Authors text size\n\\hfill\\\\\nJose Pablo Fernández Cubillo, 2019047740 \\\\% Your name, your matriculation number\nRoberto Vidal Patiño, 2019065537% Your name, your matriculation number\n\\end{minipage}\n\\begin{minipage}{0.4\\textwidth} % Center of title section\n\\centering \n\\large % Title text size\nProyecto 1\\\\ % Assignment title and number\n\\normalsize % Subtitle text size\nMochila Dinámica vs. MochilaGreedy\\\\ % Assignment subtitle\n\\end{minipage}\n\\begin{minipage}{0.295\\textwidth} % Right side of title section\n\\raggedleft\n\\today\\\\ % Date\n\\footnotesize % Email text size\n\\hfill\\\\\npablof5181@estudiantec.cr\\\\\nrobertovidal@estudiantec.cr% Your email\n\\end{minipage}\n\\medskip\\hrule % Lower rule\n\\bigskip\n\n%-------------------------------\n%	CONTENTS\n%-------------------------------\n";
    fputs(inicio, archivo);
}

void quita0sDerecha(char numero[17], int ponePorcentaje){
    int i = 14;
    for(; i >= 1; i--){
        if(numero[i] == '\0'){
            continue;
        }
        if(numero[i] == '0'){
            numero[i] = '\0';
        } else if(numero[i] == '.'){
            numero[i] = '\0';
            i--;
            break;
        } else {
            break;
        }
    }
    if(ponePorcentaje){
        numero[i+1] = '\\';
        numero[i+2] = '%';
    }
    printf("%s\n",numero);
}

void crearTablaExperimento(double matriz[10][10], char tipoTabla[], char nombre[], int ponePorcentaje){
    char numeroInt[4];
    char numeroDouble[17] = {'\0'};
    fputs("\\section{", archivo);
    fputs(tipoTabla, archivo);
    fputs(" usando ", archivo);
    fputs(nombre, archivo);
    fputs("}\n\n\\begin{table}[H]\n\\centering\n\\relax\n\\resizebox{\\textwidth}{!} {%\n\\begin{tabular}{|c|c|c|c|c|c|c|c|c|c|c|}\n\\cline{2-11}\n \\multicolumn{1}{c}{} & \\multicolumn{10}{|c|}{\\textbf{Cantidad de objetos}} \\\\\n", archivo);
    for(int i = 0; i <= 10; i++){
        fputs("\\hline\n", archivo);
        for(int j = 0; j <= 10; j++){
            if(i == 0){
                if(j == 0){
                    fputs("Mochila", archivo);
                } else {
                    sprintf(numeroInt, "%d", j*10);
                    fputs(numeroInt, archivo);
                }
            } else if(j == 0){
                sprintf(numeroInt, "%d", i*100);
                fputs(numeroInt, archivo);
            } else {
                sprintf(numeroDouble, "%f", matriz[i-1][j-1]);
                quita0sDerecha(numeroDouble, ponePorcentaje);
                fputs(numeroDouble, archivo);
            }
            if(j == 10){
                fputs(" \\\\\n", archivo);
            } else {
                fputs(" & ", archivo);
            }
        }
        fputs("\\hline\n", archivo);
    }
    fputs("\\end{tabular}%\n}\n\\caption{", archivo);
    fputs(tipoTabla, archivo);
    fputs(" usando ", archivo);
    fputs(nombre, archivo);
    fputs(".}\n\\end{table}\n", archivo);
}

void crearTitulosEjemplo(char titulo[], int resultado, double tiempo, int solucion[6]){
    char numeroInt[4]= {'\0', '\0', '\0', '\0'};
    char numeroDouble[17] = {'\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0'};
    fputs("\\section{", archivo);
    fputs(titulo, archivo);
    fputs("}\n", archivo);
    sprintf(numeroInt, "%d", resultado);
    fputs("\\textbf{Resultado:} ", archivo);
    fputs(numeroInt, archivo);
    sprintf(numeroDouble, "%f", tiempo);
    quita0sDerecha(numeroDouble, 0);
    fputs("\n\n\\textbf{Tiempo:} ", archivo);
    fputs(numeroDouble, archivo);
    fputs("\n\n\\textbf{Solución:} ", archivo);
    char sol[13] = {'\0'};
    int contar = 0;
    for(int i = 0; i < 6; i++){
        if(solucion[i] != -1){
            sol[contar] = 'A'+solucion[i];
            contar++;
            sol[contar] = '-';
            contar++;
        }
    }
    if(contar > 0){
        sol[contar-1] = '\0';
    }
    fputs(sol, archivo);
}

void crearTablaEjemplo(int **solucionDinamica, char **colores){
    char numeroInt[4]= {'\0', '\0', '\0', '\0'};
    fputs("\n\n\\begin{table}[H]\n\\centering\n\\relax\n\\begin{tabular}{|c|c|c|c|c|c|c|}\n", archivo);
    for(int i = 0; i <= 16; i++){
        fputs("\\hline\n", archivo);
        for(int j = 0; j <= 6; j++){
            if(i == 0){
                if(j != 0){
                    fputc(j+'A'-1, archivo);
                }
            } else if(j == 0){
                sprintf(numeroInt, "%d", i-1);
                fputs(numeroInt, archivo);
            } else {
                sprintf(numeroInt, "%d", solucionDinamica[i-1][j-1]);
                fputs(numeroInt, archivo);
                if(colores[i-1][j-1] == 'g'){
                    fputs(" \\cellcolor{green!50}", archivo);
                } else if(colores[i-1][j-1] == 'r'){
                    fputs(" \\cellcolor{red!50}", archivo);
                }
            }
            if(j == 6){
                fputs(" \\\\\n", archivo);
            } else {
                fputs(" & ", archivo);
            }
        }
        if(i == 16){
            fputs("\\hline\n", archivo);
        }
    }
    fputs("\\end{tabular}\n\\caption{Tabla usando programación dinámica.}\n\\end{table}\n", archivo);
}

void resultadoDinamicaEjemplo(int **solucionDinamica, char **colores, int *valores, int resultado[6]){
    int n = 15;
    int m = 5;
    int i = 0;
    while(n >= 0 && m >= 0){
        if(colores[n][m] == 'g'){
            resultado[i] = m;
            n = n - valores[m];
            i++;
        }
        m = m - 1;
    }
}

void crearSuma(int lista[6]){
    char numeroInt[4]= {'\0', '\0', '\0', '\0'};
    for(int i = 0; i < 6; i++){
        sprintf(numeroInt, "%d", lista[i]);
        fputs(numeroInt, archivo);
        fputs("x_{\\text{", archivo);
        fputc('A'+i, archivo);
        fputs("}}", archivo);
        if(i != 5){
            fputc('+', archivo);
        }
    }
}

void formaMatematica(int capacidades[6], int valores[6]){
    fputs("\\section{Forma matemática}\n \\textbf{Maximizar:}\n\n", archivo);
    fputs("$$Z=", archivo);
    crearSuma(valores);
    fputs("$$", archivo);
    fputs("\\textbf{Sujeto a:}\n\n$$", archivo);
    crearSuma(capacidades);
    fputs("\\leq 15$$\n\n$$x_i = 0 \\text{ o } 1$$", archivo);
}

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
    int resultadoPD;
    int resultadoGB;
    int resultadoGP;
    for(int i = 0; i < 6;i++){
        capacidades[i] = (rand() % 7) + 1;
        valores[i] = (rand() % 20) + 1;
    }

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
    resultadoPD = progDinamica(capacidad, 6, capacidades, valores, solucionDinamica, colores);
    clock_t end = clock();
    double tiempo_prog_dinamica = (double)(end - begin) / CLOCKS_PER_SEC;

    // En solucion se guarda la solucion, la cual iria de la primera posicion hasta que se encuentre un -1
    begin = clock();
    int solucionGreedyBasico[6] = {-1,-1,-1,-1,-1,-1};
    resultadoGB = greedyBasico(capacidad, 6, capacidades, valores, solucionGreedyBasico);
    end = clock();
    double tiempo_greedy_basico = (double)(end - begin) / CLOCKS_PER_SEC;

    int solucionGreedyProporcional[6] = {-1,-1,-1,-1,-1,-1};
    begin = clock();
    resultadoGP = greedyProporcional(capacidad, 6, capacidades, valores, solucionGreedyProporcional);
    end = clock();
    double tiempo_greedy_prop= (double)(end - begin) / CLOCKS_PER_SEC;

    int sol[6] = {-1,-1,-1,-1,-1,-1};
    resultadoDinamicaEjemplo(solucionDinamica, colores, capacidades, sol);
    crearPdf();
    formaMatematica(capacidades, valores);
    crearTitulosEjemplo("Programación dinámica", resultadoPD, tiempo_prog_dinamica, sol);
    crearTablaEjemplo(solucionDinamica, colores);
    crearTitulosEjemplo("Greedy básico", resultadoGB, tiempo_greedy_basico, solucionGreedyBasico);
    crearTitulosEjemplo("Greedy proporcional", resultadoGP, tiempo_greedy_prop, solucionGreedyProporcional);
    terminaPdf();


    printf("Programacion Dinamica: \n");
    printf("Resultado: %d\n", resultadoPD);
    printf("Solucion:\n");
    for(int i =0; i<=capacidad; i++){
        for(int j = 0; j<6;j++){
            printf("%d (%c), ",solucionDinamica[i][j], colores[i][j]);
        }
        printf("\n");
    }
    printf("Tiempo: %f\n", tiempo_prog_dinamica);

    printf("Greedy Basico: \n");    
    printf("Resultado: %d\n", resultadoGB);
    printf("Solucion: ");
    int i =0;
    while(solucionGreedyBasico[i] != -1){
        printf("%d, ", solucionGreedyBasico[i]);
        i++;
    }
    printf("\n");
    printf("Tiempo: %f\n", tiempo_greedy_basico);

    printf("Greedy Proporcional: \n");    
    printf("Resultado: %d\n", resultadoGP);
    i =0;
    printf("Solucion: ");
    while(solucionGreedyProporcional[i] != -1){
        printf("%d, ", solucionGreedyProporcional[i]);
        i++;
    }
    printf("\n");
    printf("Tiempo: %f\n", tiempo_greedy_prop);

    for (int i = 0; i<16; i++) {
        free(solucionDinamica[i]);
        free(colores[i]);
    }
    free(solucionDinamica);
    free(colores);
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
    crearPdf();
    crearTablaExperimento(promedioTiemposDinamica, "Promedios de tiempo en milisegundos", "programación dinámica", 0);
    crearTablaExperimento(promedioTiemposBasico, "Promedios de tiempo en milisegundos", "greedy básico", 0);
    crearTablaExperimento(promedioTiemposProporcional, "Promedios de tiempo en milisegundos", "greedy proporcional", 0);
    crearTablaExperimento(porcentajeBasico, "Porcentaje de aciertos", "greedy básico", 1);
    crearTablaExperimento(porcentajeProporcional, "Porcentaje de aciertos", "greedy proporcional", 1);
    terminaPdf();
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
    for (int i = 0; i<1001; i++) {
        free(solucionDinamica[i]);
    }
    free(solucionDinamica);
}

void mostrarAyuda(){
    printf("Parece que necesitas ayuda.\n\n");
    printf("Comando\tExplicación");
    printf("\n\n-X\tEl programa resolverá un solo caso aleatorio del problema 0/1 de la\n\tmochila con un algoritmo de programación dinámica, un greedy básico y un\n\tgreedy proporcional. La mochila tiene una capacidad de 15. Habrá 6\n\tobjetos con sus capacidades c_i <= 7 y sus valores 0 < v_i <= 20 ambos\n\tgenerados aleatoriamente. Se despliega un pdf hecho en Latex con los\n\tresultados.");
    printf("\n\n-E=n\tEn este caso n debe ser un número entero positivo distinto de 0. El\n\tprograma resolverá 100n casos diferentes del problema 0/1 de la mochila\n\tcon un algoritmo de programación dinámica, un greedy básico y un greedy\n\tproporcional. La capacidad de la mochila se varı́a desde 100 hasta 1000,\n\ty la cantidad de objetos se varı́a desde 10 hasta 100 objetos Para cada\n\tuno de los n casos en la combinación de cierta capacidad de mochila y\n\tcantidad de objetos, se generarán aleatoriamente las capacidades y\n\tvalores de cada objeto, con las restricciones de que todas las\n\tcapacidades sean mayores que 0, pero que ninguno sea mayor al 40 %% de la\n\tcapacidad de la mochila, y que 0 < v_i <= 100, donde v_i es cada valor\n\tdel objeto. Se muestran los resultados de ejecución de los tres\n\talgoritmos con tablas de promedios de tiempo de ejecución y para los\n\tgreedy se les coloca también tablas con los porcentajes de éxito.\n");
}

int main(int argc, char *argv[]){
    srand(time(0));
    if(argc != 2){
        mostrarAyuda();
        return -1;
    }
    if(strcmp(argv[1],"-X") == 0){
        modoEjemplo();
    }
    else{
        int n;
        if(argv[1][0] == '-' && argv[1][1] == 'E' && argv[1][2] == '=' && isdigit(argv[1][3])){
            sscanf(argv[1], "-E=%d", &n);
            if(n <= 0){
                modoExperimento(n);
            } else {
                mostrarAyuda();
            }
        }
        else{
            mostrarAyuda();
        }
    }
    return 0;
}
