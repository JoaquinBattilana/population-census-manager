#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

enum estado {NUMERO, PALABRA};
#define MAXLINEA 80
#define CNTDATOSNUM 4
#define BLOQUE 10

int getLine(char *, int []);

int main(void){
    int v[MAXLINEA];
    char * s;
    getLine(s,v);
    printf("%d,%d,%d,%s,%d", v[0], v[1], v[2], s, v[3]);
}

int getLine(char * s, int v[MAXLINEA]){
	int estado=NUMERO;
        int i=0,error=0;
        char c;
        int numero=0;
        int cantidad=0;
        int total=0;
        do{
            c=getchar();
            cantidad++;
            total++;
            switch(estado){
                        case NUMERO:
                         if(isdigit(c))
                                 numero=numero*10+(c-'0');
                         else if((c==',' || c=='\n' || c==EOF) && cantidad>0){
                                 cantidad=0;
                                 v[i++]=numero;
                                 numero=0;
                                 if(i==3)
                                        estado=PALABRA;
                         }
                         else
                               error=1;
                         break;
                        case PALABRA:
                          if(isalpha(c)){
                                if(cantidad%BLOQUE==0)
                                        s=realloc(NULL, cantidad+BLOQUE);
                                s[cantidad]=c;
                                cantidad++;
			}
                          else if(c==',' && cantidad>0){
                                s[cantidad]='\0';
                                cantidad=0;
                                estado=NUMERO;
                         }
                         else
                                error=1;
                         break;
             }
        }while(c!=EOF && c!='\n' && !error && cantidad <= MAXLINEA);
        if ( cantidad > MAXLINEA)
              error=1;
        return error;
}