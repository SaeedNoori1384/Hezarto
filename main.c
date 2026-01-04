#include <stdio.h>
#include <stdlib.h>
#include <time.h>

char map[200][200];
int visited[200][200];
int ROWS, COLS;

int Cx ,Cy;
int Rdecarty_x[50];
int Rdecarty_y[50];
int Hdecarty_x[50];
int Hdecarty_y[50];
int depth(int x1 , int y1 , int x2 , int y2){
    int a = x1-x2;
    int b = y1-y2;
    if(a<0){
        a = -a;
    }
    if(b<0){
        b = -b;
    }
    return a+b;
}
int dx[4] = {0, 0, 2, -2};
int dy[4] = {2, -2, 0, 0};

void dfs(int x, int y) {
    visited[x][y] = 1;

    for (int d = 0; d < 4; d++) {
        int nx = x + dx[d];
        int ny = y + dy[d];

        int wx = x + dx[d] / 2;
        int wy = y + dy[d] / 2;

        if (nx >= 0 && ny >= 0 && nx < ROWS && ny < COLS) {
            if (!visited[nx][ny] && map[wx][wy] == '.') {
                dfs(nx, ny);
            }
        }
    }
}
int IsMapFullyConnected(int n, int m) {
    ROWS = 2*n - 1;
    COLS = 2*m - 1;

    for (int i = 0; i < ROWS; i++)
        for (int j = 0; j < COLS; j++)
            visited[i][j] = 0;

    int sx = -1, sy = -1;
    for (int i = 0; i < ROWS; i += 2) {
        for (int j = 0; j < COLS; j += 2) {
            if (map[i][j] != '_'
                && map[i][j] != '|') {
                sx = i;
                sy = j;
                break;
            }
        }
        if (sx != -1) break;
    }

    if (sx == -1) return 0;

    dfs(sx, sy);

    for (int i = 0; i < ROWS; i += 2) {
        for (int j = 0; j < COLS; j += 2) {
            if (!visited[i][j])
                return 0;
        }
    }
    return 1;
}

//t = 1   V |
//t = 2   H _
int putwalls(int n ,int m , int r){
    int e = 1;
    int s = 1;
    for (int i = 0; i < 2*n-1 && s==1; i++) {
        for (int j = 0; j < 2*m-1 && s==1; j++) {
            if(i%2 == 0 && j%2 == 1){
                if(e == r){
                    map[i][j] = '|';
                    s = 0;
                } else{
                    e++;
                }
            }else if(i%2 == 1){
                if(e == r){
                    map[i][j] = '_';
                    s = 0;
                } else{
                    e++;
                }
            }
        }
    }
}
void makerandommap(int n , int m , int R , int H ,int W){
    int ok = 0 ;
    while (ok != 1){
        for (int i = 0; i < 2*n-1; i++) {
            for (int j = 0; j < 2*m-1; j++) {
                map[i][j] = '.';
            }
        }
        int array[2][R+H+1];
        int r = rand()%(n*m);
        map[2*(r/n)][2*(r%m)]= 'C';
        array[0][0] = 2*(r/n);
        array[1][0] = 2*(r%m);
        int j = 0;
        while (j != H){
            r = rand()%(n*m);
            if(map[2*(r/n)][2*(r%m)] == '.'){
                map[2*(r/n)][2*(r%m)] = 'H';
                array[0][j+1] = 2*(r/n);
                array[1][j+1] = 2*(r%m);
                j++;
            }
        }
        int i = 0;
        while (i != R){
            r = rand()%(n*m);
            if(map[2*(r/n)][2*(r%m)] == '.') {
                map[2 * (r / n)][2 * (r % m)] = 'R';
                array[0][j+i+1] = 2*(r/n);
                array[1][j+i+1] = 2*(r%m);
                i++;
            }
        }
        int o[W];
        int q = 0;
        while (q != W){
            r = rand()%((n-1)*(3*m-2)+(m-1));
            r++;
            int t = 0 ;
            for (int k = 0; k < W; k++) {
                if(o[k] == r){
                    t = 1;
                }
            }
            if(t == 0){
                o[q] = r;
                q++;
            } else{
                continue;
            }
        }
        for (int k = 0; k < W; k++) {
            putwalls(n , m , o[k]);
        }
        int y = 0;
        for (int k = 0; k < R+H+1 && y==0; k++) {
            for (int l = k+1; l < R+H+1 && y==0; l++) {
                if(depth(array[0][k] , array[1][k] , array[0][l] , array[1][l]) < 4){
                    y = 1;
                }
            }
        }
        int P[2][n*m];
        i = 0;
        for (int k = 0; k < 2*n-1; k+=2) {
            for (int l = 0; l < 2*m-1; l+=2) {
                P[0][i] = k;
                P[1][i] = l;
                i++;
            }
        }
        if(y == 1 || !IsMapFullyConnected(n , m)){
            ok = 0;
        } else{
            ok = 1;
        }
    }
}
// 1    |   up
// 2   ___  right
// 3    |   down
// 4   ___  left
int moveRunner(int n , int m , int direct , int wich){
    if(direct == 8 && Rdecarty_x[wich]-2>=0){
        if(map[Rdecarty_x[wich]-2][Rdecarty_y[wich]] == '.' && map[Rdecarty_x[wich]-1][Rdecarty_y[wich]] != '|' && map[Rdecarty_x[wich]-1][Rdecarty_y[wich]] != '_'){
            map[Rdecarty_x[wich]-2][Rdecarty_y[wich]] = 'R';
            map[Rdecarty_x[wich]][Rdecarty_y[wich]] = '.';
            Rdecarty_x[wich]-=2 ;
        } else if((map[Rdecarty_x[wich]-2][Rdecarty_y[wich]] == 'C' && map[Rdecarty_x[wich]-1][Rdecarty_y[wich]] != '|' && map[Rdecarty_x[wich]-1][Rdecarty_y[wich]] != '_')||(map[Rdecarty_x[wich]-2][Rdecarty_y[wich]] == 'H' && map[Rdecarty_x[wich]-1][Rdecarty_y[wich]] != '|' && map[Rdecarty_x[wich]-1][Rdecarty_y[wich]] != '_')){
            Rdecarty_x[wich]-=2;
        } else{
            printf("Sorry !\nYou cant go there!!!\n\n");
        }
    }else if(direct == 6 && Rdecarty_y[wich]+2<=2*m-2){
        if(map[Rdecarty_x[wich]][Rdecarty_y[wich]+2] == '.' && map[Rdecarty_x[wich]][Rdecarty_y[wich]+1] != '|' && map[Rdecarty_x[wich]][Rdecarty_y[wich]+1] != '_'){
            map[Rdecarty_x[wich]][Rdecarty_y[wich]+2] = 'R';
            map[Rdecarty_x[wich]][Rdecarty_y[wich]] = '.';
            Rdecarty_y[wich]+=2;
        } else if((map[Rdecarty_x[wich]][Rdecarty_y[wich]+2] == 'C' && map[Rdecarty_x[wich]][Rdecarty_y[wich]+1] != '|' && map[Rdecarty_x[wich]][Rdecarty_y[wich]+1] != '_')||(map[Rdecarty_x[wich]][Rdecarty_y[wich]+2] == 'H' && map[Rdecarty_x[wich]][Rdecarty_y[wich]+1] != '|' && map[Rdecarty_x[wich]][Rdecarty_y[wich]+1] != '_')){
            Rdecarty_y[wich]+=2;
        } else{
            printf("Sorry !\nYou cant go there!!!\n\n");
        }
    }else if(direct == 2 && Rdecarty_x[wich]+2<=2*n-2){
        if(map[Rdecarty_x[wich]+2][Rdecarty_y[wich]] == '.' && map[Rdecarty_x[wich]+1][Rdecarty_y[wich]] != '|' && map[Rdecarty_x[wich]+1][Rdecarty_y[wich]] != '_'){
            map[Rdecarty_x[wich]+2][Rdecarty_y[wich]] = 'R';
            map[Rdecarty_x[wich]][Rdecarty_y[wich]] = '.';
            Rdecarty_x[wich]+=2;
        }else if((map[Rdecarty_x[wich]+2][Rdecarty_y[wich]] == 'C' && map[Rdecarty_x[wich]+1][Rdecarty_y[wich]] != '|' && map[Rdecarty_x[wich]+1][Rdecarty_y[wich]] != '_')||(map[Rdecarty_x[wich]+2][Rdecarty_y[wich]] == 'H' && map[Rdecarty_x[wich]+1][Rdecarty_y[wich]] != '|' && map[Rdecarty_x[wich]+1][Rdecarty_y[wich]] != '_')){
            Rdecarty_x[wich]+=2;
        } else{
            printf("Sorry !\nYou cant go there!!!\n\n");
        }
    }else if(direct == 4 && Rdecarty_y[wich]-2>=0){
        if(map[Rdecarty_x[wich]][Rdecarty_y[wich]-2] == '.' && map[Rdecarty_x[wich]][Rdecarty_y[wich]-1] != '|' && map[Rdecarty_x[wich]][Rdecarty_y[wich]-1] != '_'){
            map[Rdecarty_x[wich]][Rdecarty_y[wich]-2] = 'R';
            map[Rdecarty_x[wich]][Rdecarty_y[wich]] = '.';
            Rdecarty_y[wich]-=2;
        }else if((map[Rdecarty_x[wich]][Rdecarty_y[wich]-2] == 'C' && map[Rdecarty_x[wich]][Rdecarty_y[wich]-1] != '|' && map[Rdecarty_x[wich]][Rdecarty_y[wich]-1] != '_')||(map[Rdecarty_x[wich]][Rdecarty_y[wich]-2] == 'H' && map[Rdecarty_x[wich]][Rdecarty_y[wich]-1] != '|' && map[Rdecarty_x[wich]][Rdecarty_y[wich]-1] != '_')){
            Rdecarty_y[wich]-=2;
        } else{
            printf("Sorry !\nYou cant go there!!!\n\n");
        }
    }
}
int moveHunter(int H_random , int R_random ){
    if(Hdecarty_y[H_random]>Rdecarty_y[R_random] && map[Hdecarty_x[H_random]][Hdecarty_y[H_random]-2] == '.' && map[Hdecarty_x[H_random]][Hdecarty_y[H_random]-1] != '|' && map[Hdecarty_x[H_random]][Hdecarty_y[H_random]-1] == '_'){
        map[Hdecarty_x[H_random]][Hdecarty_y[H_random]-2] = 'H';
        map[Hdecarty_x[H_random]][Hdecarty_y[H_random]] = '.';
        Hdecarty_y[H_random]-=2;
    }else if(Hdecarty_y[H_random]<Rdecarty_y[R_random] && map[Hdecarty_x[H_random]][Hdecarty_y[H_random]+2] == '.' && map[Hdecarty_x[H_random]][Hdecarty_y[H_random]+1] != '_' && map[Hdecarty_x[H_random]][Hdecarty_y[H_random]+1] != '|'){
        map[Hdecarty_x[H_random]][Hdecarty_y[H_random]+2] = 'H';
        map[Hdecarty_x[H_random]][Hdecarty_y[H_random]] = '.';
        Hdecarty_y[H_random]+=2;
    }else if(Hdecarty_x[H_random]>Rdecarty_x[R_random] && map[Hdecarty_x[H_random]-2][Hdecarty_y[H_random]] == '.' && map[Hdecarty_x[H_random]-1][Hdecarty_y[H_random]] != '_' && map[Hdecarty_x[H_random]-1][Hdecarty_y[H_random]] != '|'){
        map[Hdecarty_x[H_random]-2][Hdecarty_y[H_random]] = 'H';
        map[Hdecarty_x[H_random]][Hdecarty_y[H_random]] = '.';
        Hdecarty_x[H_random]-=2;
    }else if(Hdecarty_x[H_random]<Rdecarty_x[R_random] && map[Hdecarty_x[H_random]+2][Hdecarty_y[H_random]] == '.' && map[Hdecarty_x[H_random]+1][Hdecarty_y[H_random]] != '_' && map[Hdecarty_x[H_random]+1][Hdecarty_y[H_random]] != '|'){
        map[Hdecarty_x[H_random]+2][Hdecarty_y[H_random]] = 'H';
        map[Hdecarty_x[H_random]][Hdecarty_y[H_random]] = '.';
        Hdecarty_x[H_random]+=2;
    }
}
// win R 1
// win H 2
// not end 0
int checkendgame(int R , int H){
    for (int i = 0; i < R; i++) {
        for (int j = 0; j < H; j++) {
            if(Rdecarty_x[i] == Hdecarty_x[j] && Rdecarty_y[i] == Hdecarty_y[j]){
                return 2;
            }
        }
    }
    for (int i = 0; i < R; i++){
        if(Rdecarty_x[i] == Cx && Rdecarty_y[i] == Cy){
            return 1;
        }
    }
    return 0;
}       //                      H            R
int Game(int n , int m  , int random , int mohre){
    printf("\n\nStart of game : ...\n\n");
    int direct ;
    while (1){
        for (int i = 0; i < mohre; i++) {
            scanf("%d" , &direct);
            moveRunner(n , m , direct , i);
            for (int i = 0; i < 2*n-1; i++) {
                for (int j = 0; j < 2*m-1; j++) {
                    printf(" %c " , map[i][j]);
                }
                printf("\n");
            }
            printf("\n");
            printf("\n");
        }
        printf("Now is the turn for hunters ...\nHa Ha Ha Ha Ha Ha ..........\n\n");
        for (int i = 0; i < random; i++) {
            int t = rand()%mohre;  //  R_random
            int p = rand()%random; //  H_random
            moveHunter(p , t);
            moveHunter(p , t);
        }
        for (int i = 0; i < 2*n-1; i++) {
            for (int j = 0; j < 2*m-1; j++) {
                printf(" %c " , map[i][j]);
            }
            printf("\n");
        }
        printf("\n");
        printf("\n");
        if(checkendgame(mohre,random) == 2){
            printf("Hunters won :(\n\n");
            break;
        } else if(checkendgame(mohre,random) == 1){
            printf("Congradulations\nYou won :)\n\n");
            break;
        }
    }
}
int main() {
    srand(time(NULL));

    int n , m;
    scanf("%d %d" , &n ,&m);

    int H , R , W;
//    R = 1;
//    H = 1;
    scanf("%d %d %d",&R, &H, &W);
//    scanf("%d" , &W);
    int t = n*m;
    if(t%2 == 0){
        t = t/2;
    } else{
        t = (t/2)+1;
    }
    if(R+H+1 <= t){
        makerandommap(n , m , R , H , W);
        for (int i = 0; i < 2*n-1; i++) {
            for (int j = 0; j < 2*m-1; j++) {
                printf(" %c " , map[i][j]);
            }
            printf("\n");
        }
    } else{
        printf("No Exist !!!\n");
    }
    int r = 0;
    for (int i = 0; i < 2*n-1; i++) {
        for (int j = 0; j < 2*m-1; j++) {
            if(map[i][j] == 'R'){
                Rdecarty_x[r]= i ;
                Rdecarty_y[r] = j;
                r++;
            }
        }
    }
    r = 0;
    for (int i = 0; i < 2*n-1; i++) {
        for (int j = 0; j < 2*m-1; j++) {
            if(map[i][j] == 'H'){
                Hdecarty_x[r] = i;
                Hdecarty_y[r] = j;
                r++;
            }
        }
    }
    for (int i = 0; i < 2*n-1; i++) {
        for (int j = 0; j < 2*m-1; j++) {
            if(map[i][j] == 'C'){
                Cx = i;
                Cy = j;
            }
        }
    }
//    for (int i = 0; i < R; i++) {
//        printf("%d ",Rdecarty_x[i]);
//        printf(" %d\n",Rdecarty_y[i]);
//    }
//    for (int i = 0; i < H; i++) {
//        printf("%d ",Hdecarty_x[i]);
//        printf(" %d\n",Hdecarty_y[i]);
//    }
    Game(n , m ,H , R);
    return 0;
}
