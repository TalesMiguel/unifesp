// Nome: Tales Miguel Machado Pereira
// RA: 140247

#include <stdio.h>

int dividir(int dividendo, int divisor){
    int quociente;

    if(dividendo<divisor){
        quociente=0;
    }
    else{
        quociente = 1 + dividir(dividendo - divisor, divisor);
    }
    return quociente;
}

int main(){
    int n, i, d, p, v, resultado, x, y, vales;
    int final[10];

    do{
        scanf("%d", &n);
    }
    while (n<1 || n>10);

    // iterando sobre N
    for(i=0; i<n; i++){

        // dinheiro D para comprar os livros
        do{
            scanf("%d", &d);
        }
        while (d<0);

        // preco P de cada livro
        do{
            scanf("%d", &p);
        }
        while (p<1);

        // vale-compras V 
        // numero de vales para ganhar um livro extra
        // a cada compra, ganha um vale
        do{
            scanf("%d", &v);
        }
        while (!(v>1));

        resultado = dividir(d, p);
        vales = dividir(resultado,v);

        for(x=resultado; x>=v; x=y){
            y = dividir(x,v);
            resultado += y;
        }
        
        if(y != 0){
            resultado+=y-1;
        }if(x==v){
            resultado+=x;
        }
        final[i] = resultado;
    }
    for(i=0; i<n; i++){
        printf("%d\n", final[i]);
    }
}
    