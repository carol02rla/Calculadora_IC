#include <stdio.h>
#include <math.h>

// Define o comando LIMPA para limpar a tela e comando PAUSA para pausar a execucao
#ifdef __linux__ 
    #include <unistd.h>
    #define LIMPA "clear"
    #define PAUSA sleep(5)
#elif _WIN32
    #include <windows.h>
    #include <stdlib.h>
    #define LIMPA "cls"
    #define PAUSA system("pause")
#else
    #error "OS not supported!"
#endif

#define PI 3.14159265359

float historico[8][9][10];
/* 
    Array tridimensional
    8 (0-7) - numeros armazenados em cada operacao
    9 (0-8) - cada operacao possivel tem uma linha reservada no array
    10 (0-9) - quantidade de operacoes anteriores armazenadas
*/
int cont = 0;

//Função para adição de numeros
float soma(float n1,float n2){
    return n1+n2;
}

//Função para subtração de numeros
float subtracao(float n1,float n2){
    return n1-n2;
}

//Função para divisão de numeros
float divisao(float n1,float n2){
    return n1/n2;
}

//Função para multiplicação de numeros
float multiplica(float n1,float n2){
    return n1*n2;
}

//Função para a potenciação de numeros
int potencia(int n,int o){
    float resultado, i;
    resultado=1;
    i=0;
    while (i!=o){
        resultado=resultado*n;
        i++;
    }
    return resultado;
}

//Função para a radiciação de numeros
float raiz(int n1){
    return sqrt(n1);
}

//Função para obtenção da equação de segundo grau
double *segundograu(float a,float b,float c){
    static double res[3];
    double delta;
    delta=((pow(b, 2))-(4*a*c));
    if (delta<0){
        res[2]=-1.0;
        return res;
    }
    res[0]=((-b)+(sqrt(delta)))/(2*a);
    res[1]=((-b)-(sqrt(delta)))/(2*a);
    
    return res;
}    

//Função para obtenção das raizes de terceiro grau
double *terceirograu(float a,float b,float c,float d){
    static double res[5];
    double A,B,C,q,r,y1,rho,theta,delta,delta2;
    double imPart, realPart;
    A=b/a;
    B=c/a;
    C=d/a;
    
    r=B-A*A/3;
    q=C+2*A*A*A/27-A*B/3;
    
    delta=q*q/4+r*r*r/27;
    
    if (delta >= 0){
        y1=cbrt(-q/2+sqrt(delta))+cbrt(-q/2-sqrt(delta));
        res[0]=(y1-A/3);
        delta2=-3*y1*y1-4*r;
        
        if (delta2>=0){
            res[1]=-y1+sqrt(delta2)/2-A/3;
            res[2]=-y1-sqrt(delta2)/2-A/3;
        }else{
            realPart=(-1*y1)/2;
            res[3]=imPart=sqrt(fabs(delta2))/2.0;
            res[1]=(realPart-(A/3));
            res[2]=(realPart-(A/3));
        }
    }else{
        rho=sqrt((q*q/4)+(delta));
        theta=acos((-1*q)/(2*rho));
        res[0]=(2*(cbrt(rho))/cos(theta/3))-(A/3);
        res[1]=(2*(cbrt(rho))*(cos((theta+2)*PI)/3))-(A/3);
        res[2]=(2*(cbrt(rho))*(cos((theta+4)*PI)/3))-(A/3);
    }
    return res;
}
      
//Função para fatorial de um numero.
int fatorial(int n){
    int resultado;
    for (resultado=1;n>1;n--){
        resultado *= n;
    }
    return resultado;
}


// Funcao para exibir menu principal
void exibeMenuPrincipal() {
    printf("------CALCULADORA------\n");
    printf("\n[1] Realizar uma operacao\n");
    printf("[2] Acessar o historico\n");
    printf("[3] Sair\n");
    printf("\nDigite uma opcao: ");
}

// Funcao para exibir menu de operacoes
void exibeMenuOperacoes() {
    printf("----OPERACOES----\n\n");
    printf("1- SOMA\n");
    printf("2- SUBTRACAO\n");
    printf("3- MULTIPLICACAO\n");
    printf("4- DIVISAO\n");
    printf("5- POTENCIACAO\n");
    printf("6- RADICIACAO\n");
    printf("7- EQUACAO DO 2 GRAU\n");
    printf("8- EQUACAO DO 3 GRAU\n");
    printf("9- FATORIAL\n");
    printf("\nEscolha a operacao que deseja realizar: ");
}

/* Funcao que adiciona as operacoes de soma, subtracao, multiplicacao, 
divisao e potencia ao historico*/
void adicionaAoHistorico(int operacao, float n1, float n2, float resultado) {
    historico[0][operacao-1][cont] = n1;
    historico[1][operacao-1][cont] = n2;
    historico[2][operacao-1][cont] = resultado;
    cont++;
}

// Funcao que adiciona as operacoes de raiz quadrada e fatorial ao historico
void adicionaRaizEFatAoHistorico(int operacao, float numero, float resultado) {
    historico[0][operacao-1][cont] = numero;
    historico[1][operacao-1][cont] = resultado;
    cont++;
}

// Funcao que adiciona a operacao de equacao de segundo grau ao historico
void adicionaEqSegGrauAoHistorico(float n1, float n2, float n3, 
float r1, float r2) {
    historico[0][6][cont] = n1;
    historico[1][6][cont] = n2;
    historico[2][6][cont] = n3;
    historico[3][6][cont] = r1;
    historico[4][6][cont] = r2;
    cont++;
}

// Funcao que adiciona a operacao de equacao de terceiro grau ao historico
void adicionaEqTercGrauAoHistorico(float n1, float n2, float n3, float n4, 
float r1, float r2, float r3, float r4) {
    historico[0][7][cont] = n1;
    historico[1][7][cont] = n2;
    historico[2][7][cont] = n3;
    historico[3][7][cont] = n4;
    historico[4][7][cont] = r1;
    historico[5][7][cont] = r2;
    historico[6][7][cont] = r3;
    historico[7][7][cont] = r4;
    cont++;
}

// Funcao para exibir o historico
void exibeHistorico() {
    printf("---HISTORICO---\n");
    printf("\n_SOMA\n");
    for(int i = 0; i < cont; i++){
        if(historico[0][0][i] == 0 && historico[1][0][i] == 0 &&
        historico[2][0][i] == 0){
            continue;
        } else {
            printf("%.0f + %.0f = %.0f\n", historico[0][0][i], 
            historico[1][0][i], historico[2][0][i]);
        }
    }
    printf("\n_SUBTRACAO\n");
    for(int i = 0; i < cont; i++){
        if(historico[0][1][i] == 0 && historico[1][1][i] == 0 && 
        historico[2][1][i] == 0){
            continue;
        } else {
            printf("%.0f - %.0f = %.0f\n", historico[0][1][i], 
            historico[1][1][i], historico[2][1][i]);
        }
    }
    printf("\n_MULTIPLICACAO\n");
    for(int i = 0; i < cont; i++){
        if(historico[0][2][i] == 0 && historico[1][2][i] == 0 && 
        historico[2][2][i] == 0){
            continue;
        } else {
            printf("%.0f x %.0f = %.0f\n", historico[0][2][i], 
            historico[1][2][i], historico[2][2][i]);
        }
    }
    printf("\n_DIVISAO\n");
    for(int i = 0; i < cont; i++){
        if(historico[0][3][i] == 0 && historico[1][3][i] == 0 && 
        historico[2][3][i] == 0){
            continue;
        } else {
            printf("%.0f / %.0f = %.2f\n", historico[0][3][i], 
            historico[1][3][i], historico[2][3][i]);
        }
    }
    printf("\n_POTENCIACAO\n");
    for(int i = 0; i < cont; i++){
        if(historico[0][4][i] == 0 && historico[1][4][i] == 0 && 
        historico[2][4][i] == 0){
            continue;
        } else {
            printf("%.0f ^ %.0f = %.0f\n", historico[0][4][i], 
            historico[1][4][i], historico[2][4][i]);
        }
    }
    printf("\n_RADICIACAO\n");
    for(int i = 0; i < cont; i++){
        if(historico[0][5][i] == 0 && historico[1][5][i] == 0){
            continue;
        } else {
            printf("Raiz quadrada de %.0f = %.2f\n", historico[0][5][i], 
            historico[1][5][i]);
        }
    }
    printf("\n_EQUACAO DO SEGUNDO GRAU\n");
    for(int i = 0; i < cont; i++){
        if(historico[0][6][i] == 0 && historico[1][6][i] == 0 && 
        historico[2][6][i] == 0 && historico[3][6][i] == 0 && 
        historico[4][6][i] == 0){
            continue;
        } else {
            if (historico[4][6][i] == -9999 || historico[5][6][i] == -9999) {
                printf("%.0fx^2 + (%.0f)x + (%.0f) = 0\n    x nao existe\n", 
                historico[0][6][i], historico[1][6][i], historico[2][6][i]);
            } else {
                printf("%.0fx^2 + (%.0f)x + (%.0f) = 0\n    x1 = %.2f e x2 = %.2f\n", 
                historico[0][6][i], historico[1][6][i], historico[2][6][i], 
                historico[3][6][i], historico[4][6][i], historico[5][6][i]);
            }
        }
    }
    printf("\n_EQUACAO DO TERCEIRO GRAU\n");
    for(int i = 0; i < cont; i++){
        if(historico[0][7][i] == 0 && historico[1][7][i] == 0 && 
        historico[2][7][i] == 0 && historico[3][7][i] == 0 && 
        historico[4][7][i] == 0){
            continue;
        } else {
            printf("%.0lfx^3 + (%.0lf)x^2 + (%.0lf)x + (%.0lf) = 0\n    x1 = %.3lf; \n    x2 = %.3lf + %.3lfi; \n    x3 = %.3lf - %.3lfi\n", 
            historico[0][7][i], historico[1][7][i], historico[2][7][i], 
            historico[3][7][i], historico[4][7][i], historico[5][7][i], 
            historico[7][7][i], historico[6][7][i], historico[7][7][i]);
        }
    }
    printf("\n_FATORIAL\n");
    for(int i = 0; i < cont; i++){
        if(historico[0][8][i] == 0 && historico[1][8][i] == 0){
            continue;
        } else {
            printf("%.0f! = %.0f\n", historico[0][8][i], historico[1][8][i]);
        }
    }
}

//bloco principal do programa
int main(){
    int opcao;
    
    do{
        //adicionando as variáveis necessárias
        int m;
        int n,o;
        double n1,n2,a,b,c,d,res1,res2,res3,res4;
        double *seggrau, *tercgrau;
    
        system(LIMPA);
        exibeMenuPrincipal();
        scanf("%d", &opcao);

        switch(opcao) {
            // Realizar uma operacao
            case 1: { 
                system(LIMPA);
                // outro menu
                exibeMenuOperacoes();
                scanf("%d", &m);

                switch (m) {
                    //bloco da adição
                    case 1:
                    printf("\nDigite os numeros a serem somados: \n");
                    scanf("%lf %lf", &n1, &n2);
                    printf("\nO Resultado de %.0f + %.0f = %.0f\n", n1, n2, soma(n1, n2));
                    adicionaAoHistorico(m, n1, n2, soma(n1, n2));
                    PAUSA;
                    break;
            
                    //bloco da subtração
                    case 2:
                    printf("\nDigite o minuendo e o subtraendo: \n");
                    scanf("%lf %lf", &n1, &n2);
                    printf("\nO Resultado de %.0f - %.0f = %.0f\n", n1, n2, subtracao(n1, n2));
                    adicionaAoHistorico(m, n1, n2, subtracao(n1, n2));
                    PAUSA;
                    break;
                    
                    //bloco da multiplicação
                    case 3:
                    printf("\nDigite os numeros a serem multiplicados: \n");
                    scanf("%lf %lf", &n1, &n2);
                    printf("\nO Resultado de %.0f x %.0f = %.0f\n", n1, n2, multiplica(n1, n2));
                    adicionaAoHistorico(m, n1, n2, multiplica(n1, n2));
                    PAUSA;
                    break;
            
                    //bloco da divisão
                    case 4:
                    printf("\nDigite os numeros a serem divididos: \n");
                    scanf("%lf %lf", &n1, &n2);
                    printf("\nO Resultado de %.0f / %.0f = %.2f\n", n1, n2, divisao(n1, n2));
                    adicionaAoHistorico(m, n1, n2, divisao(n1, n2));
                    PAUSA;
                    break;
            
                    //bloco da exponenciação
                    case 5:
                    printf("\nDigite a base e o expoente: \n");
                    scanf("%d %d", &n, &o);
                    printf("\nO Resultado de %d ^ %d = %d\n", n, o, potencia(n, o));
                    adicionaAoHistorico(m, n, o, potencia(n, o));
                    PAUSA;
                    break;
                    
                    //bloco da radiciação
                    case 6:
                    printf("\nDigite o numero para a raiz quadrada: \n");
                    scanf("%lf",&n1);
                    printf("\nO resultado da raiz quadrada de %.0f = %.2f\n", n1, raiz(n1));
                    adicionaRaizEFatAoHistorico(m, n1, raiz(n1));
                    PAUSA;
                    break;
                    
                    //bloco da equação de segundo grau
                    case 7:
                    printf("\nDigite quais numeros representam A, B e C: \n");
                    scanf(" %lf %lf %lf", &a, &b, &c);
                    
                    seggrau = segundograu(a,b,c);
                    res1 = seggrau[0];
                    res2 = seggrau[1];
                    res3 = seggrau[2];
                    
                    if (res3 == -1.0){
                        printf("\nNao existem raizes reais para a equacao %.0fx^2 + (%.0f)x + (%.0f) = 0\n", a,b,c);
                        adicionaEqSegGrauAoHistorico(a, b, c, -9999, -9999);
                    }else{
                        if (res1*-1==res2 || res1==res2*-1){
                            printf("\nAs raizes para a equacao %.0fx^2 + (%.0f)x + (%.0f) = 0, eh igual a x = +/- %.2f\n", a,b,c,res1);
                            adicionaEqSegGrauAoHistorico(a, b, c, res1, res2);
                        }else{
                            printf("\nAs raizes para a equacao %.0fx^2 + (%.0f)x + (%.0f) = 0, sao iguais a x1 = %.2f e x2 = %.2f\n", a,b,c,res1,res2);
                            adicionaEqSegGrauAoHistorico(a, b, c, res1, res2);
                        
                        }
                    }
                    PAUSA;
                    break;
                    
                    //bloco da equação de terceiro grau
                    case 8:
                    printf("\nDigite quais numeros representam A, B, C e D: \n");
                    scanf("%lf %lf %lf %lf", &a, &b, &c, &d);
                    tercgrau=terceirograu(a,b,c,d);
                    res1=tercgrau[0];
                    res2=tercgrau[1];
                    res3=tercgrau[2];
                    res4=tercgrau[3];
            
                    printf("\nAs raizes para a equacao %.0lfx^3 + (%.0lf)x^2 + (%.0lf)x + (%.0lf) = 0, sao iguais a: \nx1 = %.3lf \nx2 = %.3lf + %.3lfi \nx3 = %.3lf - %.3lfi\n",a,b,c,d,res1,res2,res4,res3,res4);
                    adicionaEqTercGrauAoHistorico(a, b, c, d, res1, res2, res3, res4);
                    PAUSA;
                    break;
            
                    //bloco do fatorial
                    case 9:
                    printf("\nDigite o numero: \n");
                    scanf("%d",&n);
                    printf("\nO resultado do %d! = %d\n", n, fatorial(n));
                    adicionaRaizEFatAoHistorico(m, n, fatorial(n));
                    PAUSA;
                    break;
                    
                    //saida do switch
                    default:
                    printf("Digite uma opcao valida!\n");
                    PAUSA;
                    break;
                }
                break;
            }
            // Acessar o historico
            case 2: { 
                system(LIMPA);
                exibeHistorico();
                PAUSA;
                break;
            }
            // Sair
            case 3: { 
                return 0;
            }
            // Tratamento de erro
            default: {
                printf("Digite uma opcao valida!\n");
                PAUSA;
                break;
            }
        }
    } while (opcao != 3);

    return 0;
}