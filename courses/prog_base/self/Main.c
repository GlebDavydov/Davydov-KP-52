#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int main() {
    float price;
    float h;
    float m;
    printf("Vvedit' chas\n");
    scanf("%d, %d", &h, &m);
    float time =60*h+m;
    int code;
    printf("vvedit' kod\n");
    scanf("%d", &code);
    float taryf;
    if(code>=10&&code<=999){
    switch(code){
        case 44:
            taryf =0.77;
            price =taryf*time;
            printf("%f", &price);
            break;
        case 62:
            taryf =0.8;
            price =taryf*time;
            printf("%f", &price);
            break;
        case 32:
            taryf =0.95;
            price =taryf*time;
            printf("&f", &price);
            break;
        case 692:
        case 697:
            taryf =1.5;
            price =taryf*time;
            printf("&f", &price);
            break;
        default:
            taryf =1;
            price =taryf*time;
            printf("&f", &price);
        }
    }
    else printf("Nevirnyj kod");
    return 0;
}

