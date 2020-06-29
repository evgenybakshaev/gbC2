#include <stdio.h>
#include <string.h>

void recDec2Bin(int n, char *result) {
    if(n <= 0)
        return;
    recDec2Bin(n / 2, result);
    strcat(result, (n % 2 == 0) ? "0" : "1");
}

float recPower(float n, int ex){
    if(ex <= 0)
        return 1;
    return n*recPower(n, ex - 1);
}

float recPower2(float n, int ex){
    if(ex <= 0)
        return 1;
    if(ex % 2 == 0)
        return recPower2(n * n, ex / 2);
    else
        return n*recPower2(n , ex - 1);

}

const int SZX = 8; //Размер доски X
const int SZY = 8; //Размер доски Y

int KingRoutes(int x, int y, int desk[SZX][SZY]){
    if(desk[x][y] == 1)
        return 0;
    if(x == 0 && y == 0)
        return 0;
    else if (x == 0) {
        if (KingRoutes(x, y - 1, desk) == 0 && y != 1) return 0;
        return 1;
    } else if (y == 0) {
        if (KingRoutes(x - 1, y, desk) == 0 && x != 1) return 0;
        return 1;
    }
    //if(x == 0 || y == 0)
    //    return 1;
    return KingRoutes(x - 1, y, desk) + KingRoutes(x, y - 1, desk);
}

int main() {
    //task 1
    char bin[256];
    printf("Decimal\t| Binary\n");
    printf("--------+---------\n");
    for(int i = 0; i <= 15; ++i){
        strcpy(bin, "0b");
        recDec2Bin(i, bin);
        printf(" %d\t| %s\n", i, bin);
    }

    //task 2
    printf("\n");
    float n = 2.5;
    int ex = 2;
    printf("recPower: %f power %d = %f\n", n, ex, recPower(n,ex));
    printf("recPower2: %f power %d = %f\n", n, ex, recPower2(n,ex));

    //task 3
    printf("\n");
    int desk[SZX][SZY];
    memset(desk, 0, SZX*SZY*sizeof(int));

    desk[1][1] = 1;
    desk[0][3] = 1;
    desk[1][3] = 1;
    for(int i = 0; i < SZX; ++i){
        for(int j = 0; j < SZY; ++j){
            printf("%d\t", KingRoutes(i,j, desk));
        }
        printf("\n");
    }
    return 0;
}
