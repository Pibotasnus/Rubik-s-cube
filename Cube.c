// ENSA-M RUBIK's CUBE SOLVER

#include <stdio.h>
#include <stdlib.h>


#define N 3

#define DEPTH_MAX 10

typedef enum {JAUNE, BLEU, ROUGE, ORANGE, BLANC, VERT} couleur;
typedef enum {UP, DOWN, FRONT, BACK, LEFT, RIGHT,CUP,CDOWN,CFRONT,CBACK,CLEFT,CRIGHT} face;

face solution[DEPTH_MAX+1];
face sol[DEPTH_MAX+1];
// x -> columns / y -> lines; [x][y]=(0,0) -> upper left corner
// [making each face in front viewpoint]
// B face seen from this viewpoint: 2 left/right shifts of view

int U[N][N];
int D[N][N];
int R[N][N];
int L[N][N];
int F[N][N];
int B[N][N];


void move_CU0() { // trigo-move [making each face in front viewpoint]
    // U update
    int s1=U[0][1],s2=U[0][2];
    U[0][2]=U[0][0];
    U[0][1]=U[1][0];
    U[0][0]=U[2][0];
    U[1][0]=U[2][1];
    U[2][0]=U[2][2];
    U[2][1]=U[1][2];
    U[2][2]=s2;
    U[1][2]=s1;
    // F/L/B/R update
    int s0=F[0][0];
    s1=F[1][0]; s2=F[2][0];
    F[0][0]=L[0][0];
    F[1][0]=L[1][0];
    F[2][0]=L[2][0];
    L[0][0]=B[0][0];
    L[1][0]=B[1][0];
    L[2][0]=B[2][0];
    B[0][0]=R[0][0];
    B[1][0]=R[1][0];
    B[2][0]=R[2][0];
    R[0][0]=s0;
    R[1][0]=s1;
    R[2][0]=s2;
}
void move_U0() { // trigo-move [making each face in front viewpoint]
    // U update
    int s1=U[1][2],s2=U[2][2];
    U[2][2]=U[2][0];
    U[2][0]=U[0][0];
    U[0][0]=U[0][2];
    U[1][2]=U[2][1];
    U[2][1]=U[1][0];
    U[1][0]=U[0][1];
    U[0][2]=s2;
    U[0][1]=s1;
    // F/L/B/R update
    int s0=B[0][0];
    s1=B[1][0]; s2=B[2][0];
    B[0][0]=L[0][0];
    B[1][0]=L[1][0];
    B[2][0]=L[2][0];
    L[0][0]=F[0][0];
    L[1][0]=F[1][0];
    L[2][0]=F[2][0];
    F[0][0]=R[0][0];
    F[1][0]=R[1][0];
    F[2][0]=R[2][0];
    R[0][0]=s0;
    R[1][0]=s1;
    R[2][0]=s2;
}
void move_D0() { // trigo-move [making each face in front viewpoint]
    // D update
    int s1=D[1][2],s2=D[2][2];
    D[2][2]=D[2][0];
    D[2][0]=D[0][0];
    D[0][0]=D[0][2];
    D[1][2]=D[2][1];
    D[2][1]=D[1][0];
    D[1][0]=D[0][1];
    D[0][2]=s2;
    D[0][1]=s1;
    // F/L/B/R update
    int s0=F[0][2];
    s1=F[1][2]; s2=F[2][2];
    F[0][2]=L[0][2];
    F[1][2]=L[1][2];
    F[2][2]=L[2][2];
    L[0][2]=B[0][2];
    L[1][2]=B[1][2];
    L[2][2]=B[2][2];
    B[0][2]=R[0][2];
    B[1][2]=R[1][2];
    B[2][2]=R[2][2];
    R[0][2]=s0;
    R[1][2]=s1;
    R[2][2]=s2;
}
void move_CD0() { // trigo-move [making each face in front viewpoint]
    // cD update
    int s1=D[0][1],s2=D[0][2];
    D[0][2]=D[0][0];
    D[0][1]=D[1][0];
    D[0][0]=D[2][0];
    D[1][0]=D[2][1];
    D[2][0]=D[2][2];
    D[2][1]=D[1][2];
    D[2][2]=s2;
    D[1][2]=s1;
     // F/L/B/R update
    int s0=F[0][2];
    s1=F[1][2]; s2=F[2][2];
    F[0][2]=R[0][2];
    F[1][2]=R[1][2];
    F[2][2]=R[2][2];
    R[0][2]=B[0][2];
    R[1][2]=B[1][2];
    R[2][2]=B[2][2];
    B[0][2]=L[0][2];
    B[1][2]=L[1][2];
    B[2][2]=L[2][2];
    L[0][2]=s0;
    L[1][2]=s1;
    L[2][2]=s2;
}
void move_CF0() { // trigo-move [making each face in front viewpoint]
    // CF update
    int s1=F[0][1],s2=F[0][2];
    F[0][2]=F[0][0];
    F[0][1]=F[1][0];
    F[0][0]=F[2][0];
    F[1][0]=F[2][1];
    F[2][0]=F[2][2];
    F[2][1]=F[1][2];
    F[2][2]=s2;
    F[1][2]=s1;
    // U/D/L/R update
    int s0=U[0][2];
    s1=U[1][2]; s2=U[2][2];
    U[0][2]=R[0][0];
    U[1][2]=R[0][1];
    U[2][2]=R[0][2];
    R[0][0]=D[2][0];
    R[0][1]=D[1][0];
    R[0][2]=D[0][0];
    D[0][0]=L[2][0];
    D[1][0]=L[2][1];
    D[2][0]=L[2][2];
    L[2][0]=s2;
    L[2][1]=s1;
    L[2][2]=s0;
}
void move_F0() { // trigo-move [making each face in front viewpoint]
    // F update
    int s1=F[1][2],s2=F[2][2];
    F[2][2]=F[2][0];
    F[2][0]=F[0][0];
    F[0][0]=F[0][2];
    F[1][2]=F[2][1];
    F[2][1]=F[1][0];
    F[1][0]=F[0][1];
    F[0][2]=s2;
    F[0][1]=s1;
    // D/L/U/R update
    int s0=L[2][0];
    s1=L[2][1]; s2=L[2][2];
    L[2][0]=D[0][0];
    L[2][1]=D[1][0];
    L[2][2]=D[2][0];
    D[0][0]=R[0][2];
    D[1][0]=R[0][1];
    D[2][0]=R[0][0];
    R[0][0]=U[0][2];
    R[0][1]=U[1][2];
    R[0][2]=U[2][2];
    U[0][2]=s2;
    U[1][2]=s1;
    U[2][2]=s0;
}
void move_CB0() { // trigo-move [making each face in front viewpoint]
    // CB update
    int s1=B[0][1],s2=B[0][2];
    B[0][2]=B[0][0];
    B[0][1]=B[1][0];
    B[0][0]=B[2][0];
    B[1][0]=B[2][1];
    B[2][0]=B[2][2];
    B[2][1]=B[1][2];
    B[2][2]=s2;
    B[1][2]=s1;
    // U/D/L/R update
    int s0=U[0][0];
    s1=U[1][0]; s2=U[2][0];
    U[0][0]=L[0][2];
    U[1][0]=L[0][1];
    U[2][0]=L[0][0];
    L[0][0]=D[0][2];
    L[0][1]=D[1][2];
    L[0][2]=D[2][2];
    D[0][2]=R[2][2];
    D[1][2]=R[2][1];
    D[2][2]=R[2][0];
    R[2][0]=s0;
    R[2][1]=s1;
    R[2][2]=s2;
}
void move_B0() { // trigo-move [making each face in front viewpoint]
    // B update
    int s1=B[1][2],s2=B[2][2];
    B[2][2]=B[2][0];
    B[2][0]=B[0][0];
    B[0][0]=B[0][2];
    B[1][2]=B[2][1];
    B[2][1]=B[1][0];
    B[1][0]=B[0][1];
    B[0][2]=s2;
    B[0][1]=s1;
    // U/L/D/R update
    int s0=U[0][0];
    s1=U[1][0]; s2=U[2][0];
    U[0][0]=R[2][0];
    U[1][0]=R[2][1];
    U[2][0]=R[2][2];
    R[2][0]=D[2][2];
    R[2][1]=D[1][2];
    R[2][2]=D[0][2];
    D[2][2]=L[0][2];
    D[1][2]=L[0][1];
    D[0][2]=L[0][0];
    L[0][2]=s0;
    L[0][1]=s1;
    L[0][0]=s2;
}
void move_CL0() { // trigo-move [making each face in front viewpoint]
    // CL update
    int s1=L[0][1],s2=L[0][2];
    L[0][2]=L[0][0];
    L[0][1]=L[1][0];
    L[0][0]=L[2][0];
    L[1][0]=L[2][1];
    L[2][0]=L[2][2];
    L[2][1]=L[1][2];
    L[2][2]=s2;
    L[1][2]=s1;
    // U/D/F/B update
    int s0=U[0][0];
    s1=U[0][1]; s2=U[0][2];
    U[0][0]=F[0][0];
    U[0][1]=F[0][1];
    U[0][2]=F[0][2];
    F[0][0]=D[0][0];
    F[0][1]=D[0][1];
    F[0][2]=D[0][2];
    D[0][0]=B[2][2];
    D[0][1]=B[2][1];
    D[0][2]=B[2][0];
    B[2][0]=s2;
    B[2][1]=s1;
    B[2][2]=s0;
}
void move_L0() { // trigo-move [making each face in front viewpoint]
    // L update
   int s1=L[1][2],s2=L[2][2];
    L[2][2]=L[2][0];
    L[2][0]=L[0][0];
    L[0][0]=L[0][2];
    L[1][2]=L[2][1];
    L[2][1]=L[1][0];
    L[1][0]=L[0][1];
    L[0][2]=s2;
    L[0][1]=s1;
    // U/D/F/B update
    int s0=U[0][0];
    s1=U[0][1]; s2=U[0][2];
    U[0][0]=B[2][2];
    U[0][1]=B[2][1];
    U[0][2]=B[2][0];
    B[2][2]=D[0][0];
    B[2][1]=D[0][1];
    B[2][0]=D[0][2];
    D[0][0]=F[0][0];
    D[0][1]=F[0][1];
    D[0][2]=F[0][2];
    F[0][0]=s0;
    F[0][1]=s1;
    F[0][2]=s2;
}
void move_CR0() { // trigo-move [making each face in front viewpoint]
    // CR update
    int s1=R[0][1],s2=R[0][2];
    R[0][2]=R[0][0];
    R[0][1]=R[1][0];
    R[0][0]=R[2][0];
    R[1][0]=R[2][1];
    R[2][0]=R[2][2];
    R[2][1]=R[1][2];
    R[2][2]=s2;
    R[1][2]=s1;
    // U/D/F/B update
    int s0=U[2][0];
    s1=U[2][1]; s2=U[2][2];
    U[2][0]=B[0][2];
    U[2][1]=B[0][1];
    U[2][2]=B[0][0];
    B[0][0]=D[2][2];
    B[0][1]=D[2][1];
    B[0][2]=D[2][0];
    D[2][0]=F[2][0];
    D[2][1]=F[2][1];
    D[2][2]=F[2][2];
    F[2][0]=s0;
    F[2][1]=s1;
    F[2][2]=s2;
}
void move_R0() { // trigo-move [making each face in front viewpoint]
    // R update
    int s1=R[1][2],s2=R[2][2];
    R[2][2]=R[2][0];
    R[2][0]=R[0][0];
    R[0][0]=R[0][2];
    R[1][2]=R[2][1];
    R[2][1]=R[1][0];
    R[1][0]=R[0][1];
    R[0][2]=s2;
    R[0][1]=s1;
    // U/D/F/B update
    int s0=U[2][0];
    s1=U[2][1]; s2=U[2][2];
    U[2][0]=F[2][0];
    U[2][1]=F[2][1];
    U[2][2]=F[2][2];
    F[2][0]=D[2][0];
    F[2][1]=D[2][1];
    F[2][2]=D[2][2];
    D[2][0]=B[0][2];
    D[2][1]=B[0][1];
    D[2][2]=B[0][0];
    B[0][2]=s0;
    B[0][1]=s1;
    B[0][0]=s2;
}

int check_face(int face[N][N]) {   //ici je crois qu'il faut faire N=3
    int i,j;
    int color_mid=face[1][1];
    for (i=0;i<N;i++)
	    {
            for (j=0;j<N;j++)
			{
            if (face[i][j]!=color_mid) return 0;
             }
        }
    return 1;
}

int is_solved() {
    if (!check_face(U)) return 0;
    if (!check_face(D)) return 0;
    if (!check_face(L)) return 0;
    if (!check_face(R)) return 0;
    if (!check_face(F)) return 0;
    if (!check_face(B)) return 0;
    return 1;
}
void optiMove()
{
    int i,j,l;
    for(i=1;i<=DEPTH_MAX;i++)
    {
        sol[i]=solution[i];

        for(j=i;j<=i+2;j++)
        {
            /*if ((j==i+2) && (sol[i]==solution[j]))
            {
                switch(sol[i])
                {
                    case UP: {sol[i]=CUP; break;}
                    case DOWN: {sol[i]=CDOWN; break;}
                    case LEFT: {sol[i]=CLEFT; break;}
                    case RIGHT: {sol[i]=CRIGHT; break;}
                    case BACK: {sol[i]=CBACK; break;}
                    case FRONT: {sol[i]=CFRONT; break;}
                    default:break;
                }
             }*/
             if (sol[i]!=solution[j])
                {
                sol[i]= solution[j];
                break;
                }
        }
        for(j=i;j<=i+3;j++)
        {
            if(sol[i]!=solution[j])
            {
                sol[i]=solution[j];
                break;
            }
        }
    }
}

void solve(int depth, int u, int d, int l, int r, int f, int b, int played) {

    solution[depth]=played;

    if (is_solved()) {
        printf("Rubik's cube solved in %d steps !!\n", depth);
        int k,j;
        for (k=1;k<=depth;k++) {
            optiMove();
            printf("move[%d]=",k);
            switch (sol[k])
            {
            case UP: { printf("UP\n"); break; }
            case DOWN: { printf("DOWN\n"); break; }
            case FRONT: { printf("FRONT\n"); break; }
            case BACK: { printf("BACK\n"); break; }
            case RIGHT: { printf("RIGHT\n"); break; }
            case LEFT: { printf("LEFT\n"); break; }
            default: break;
            }
        }
        getchar();
        return;
    }

    if (depth>=DEPTH_MAX) return;

    if (u<3) {
        move_U0();
        solve(depth+1, u+1, 0, 0, 0, 0, 0, UP);
        move_CU0();
    }

    if (d<3) {
        move_D0();
        solve(depth+1, 0, d+1, 0, 0, 0, 0, DOWN);
        move_CD0();
    }

    if (l<3) {
        move_L0();
        solve(depth+1, 0, 0, l+1, 0, 0, 0, LEFT);
        move_CL0();
    }

    if (r<3) {
        move_R0();
        solve(depth+1, 0, 0, 0, r+1, 0, 0, RIGHT);
        move_CR0();
    }

    if (f<3) {
        move_F0();
        solve(depth+1, 0, 0, 0, 0, f+1, 0, FRONT);
        move_CF0();
    }

    if (b<3) {
        move_B0();
        solve(depth+1, 0, 0, 0, 0, 0, b+1, BACK);
        move_CB0();
    }

}

void inits() {

    F[0][0]=ROUGE;
    F[1][0]=JAUNE;
    F[2][0]=ROUGE;
    F[0][1]=BLEU;
    F[1][1]=JAUNE;
    F[2][1]=BLEU;
    F[0][2]=ROUGE;
    F[1][2]=JAUNE;
    F[2][2]=ROUGE;

    L[0][0]=VERT;
    L[1][0]=VERT;
    L[2][0]=VERT;
    L[0][1]=ROUGE;
    L[1][1]=ROUGE;
    L[2][1]=ROUGE;
    L[0][2]=VERT;
    L[1][2]=VERT;
    L[2][2]=VERT;

    R[0][0]=BLEU;
    R[1][0]=BLEU;
    R[2][0]=BLEU;
    R[0][1]=ORANGE;
    R[1][1]=ORANGE;
    R[2][1]=ORANGE;
    R[0][2]=BLEU;
    R[1][2]=BLEU;
    R[2][2]=BLEU;

    U[0][0]=JAUNE;
    U[1][0]=ORANGE;
    U[2][0]=JAUNE;
    U[0][1]=JAUNE;
    U[1][1]=VERT;
    U[2][1]=JAUNE;
    U[0][2]=JAUNE;
    U[1][2]=ORANGE;
    U[2][2]=JAUNE;

    D[0][0]=BLANC;
    D[1][0]=ROUGE;
    D[2][0]=BLANC;
    D[0][1]=BLANC;
    D[1][1]=BLEU;
    D[2][1]=BLANC;
    D[0][2]=BLANC;
    D[1][2]=ROUGE;
    D[2][2]=BLANC;

    B[0][0]=ORANGE;
    B[1][0]=BLANC;
    B[2][0]=ORANGE;
    B[0][1]=VERT;
    B[1][1]=BLANC;
    B[2][1]=VERT;
    B[0][2]=ORANGE;
    B[1][2]=BLANC;
    B[2][2]=ORANGE;
}


int main() {
    inits();
    solve(0, 0, 0, 0, 0, 0, 0, -1);
    return 0;
           }

