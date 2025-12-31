#include <stdio.h>
#include <stdlib.h>
#include <time.h>

char map[200][200];
int visited[200][200];
int ROWS, COLS;

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
//int moverightup(int x1 ,int y1 , int x2 , int y2){
//    if( x1>=0 && y1>=0 && x2>=0 && y2>=0){
//        if((x1 == x2)&&(y1 == y2)){
//            return 1 ;
//        }else if((map[x1][y1+1] == '.' &&(moverightup(x1 , y1+1 , x2 , y2) == 1)) || (x1-1>=0 && map[x1-1][y1] == '.' &&(moverightup(x1-1 , y1 , x2 , y2) == 1))){
//            return 1;
//        }else{
//            return 0;
//        }
//    } else{return 0;}
//}
//int moverighdown(int x1 ,int y1 , int x2 , int y2){
//    if(x1>=0 && y1>=0 && x2>=0 && y2>=0){
//        if((x1 == x2) && (y1 == y2)) {
//            return 1;
//        }else if((map[x1+1][y1] == '.' && moverighdown(x1+1 , y1 , x2 , y2) == 1) || ( map[x1][y1+1] == '.' && moverighdown(x1 , y1+1 , x2 , y2) == 1)){
//            return 1;
//        }else{
//            return 0;
//        }
//    } else{
//        return 0;
//    }
//}
//int CanMove(int x1 ,int y1 , int x2 , int y2){
//    if(x1>x2 && y1<y2){
//        return moverightup(x1 ,y1 , x2 , y2);
//    } else if(x1>x2 && y1>y2){
//        return moverighdown(x2 , y2 , x1 , y1);
//    } else if(x1<x2 && y1<y2){
//        return moverighdown(x1 , y1 , x2 , y2);
//    } else{
//        return moverightup(x2 ,y2 , x1 , y1);
//    }
//}
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

    // پیدا کردن اولین خانه زوج
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

    // چک همه خانه‌های زوج
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
int checkendgame(int x1 , int y1 , int x2 , int y2){
    if(x1 == x2 && y1 == y2){
        return 1;
    }
    return 0;
}
int main() {
    srand(time(NULL));

    int n , m;
    scanf("%d %d" , &n ,&m);

    int H , R , W;
    scanf("%d %d %d" , &H ,&R ,&W);

    while(checkendgame(x1 , y1 , x2 , y2) == 0){
    }
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
        printf("\n");
        printf("\n");
        for (int i = 0; i < 2*n-1; i+=2) {
            for (int j = 0; j < 2*m-1; j+=2) {
                printf("%c " , map[i][j]);
            }
            printf("\n");
        }
    } else{
        printf("No Exist !!!\n");
    }
    return 0;
}
