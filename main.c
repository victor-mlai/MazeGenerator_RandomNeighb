#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    int x,y;
}muchie;

typedef struct nod
{
    int x,y;    // coordonate
}pct;

void wait(int seconds)
{
    clock_t endwait;
    endwait = clock() + seconds * CLOCKS_PER_SEC ;
    while (clock() < endwait) {}
}

int valid( int **mat, muchie st[500], int k)
{
    int i;
    if( mat[ st[k].x ][ st[k].y ] == 1 )
        return 0;
    for(i=1;i<k;i++)
        if( st[k].x == st[i].x && st[k].y == st[i].y )
            return 0;
    return 1;
}

void afisare( int **mat, int height, int width )
{
    int i,j;
    static int zid= 254;
    printf("\n");
    for(j=0;j<width;j++)
        printf(" %-2d",j);
    printf("\n");
    for(i=0;i<height;i++)
    {
        for(j=0;j<width;j++)
            switch (mat[i][j])
            {
                case 0: printf("   "); break;
                case 1: printf("%c%c%c",zid,zid,zid); break;
                case 3: printf(" <-"); break;
                case 2: printf(" v "); break;
                case 4: printf(" ^ "); break;
                case 5: printf("-> "); break;
               // default: break;
            }
        printf(" %d\n",i);
    }
    printf("\n");
}

void afisare2( int **mat, int height, int width )
{
    int i,j;
    static int zid= 254;
    printf("\n");
    for(j=0;j<width;j++)
        printf(" %-2d",j);
    printf("\n");
    for(i=0;i<height;i++)
    {
        for(j=0;j<width;j++)
            switch (mat[i][j])
            {
                case 0: printf("   "); break;
                case 1: printf("%c%c%c",zid,zid,zid); break;
                case 3: printf(" <-"); break;
                case 2: printf(" v "); break;
                case 4: printf(" ^ "); break;
                case 5: printf("-> "); break;
               // default: break;
            }
        printf(" %d\n",i);
    }
    printf("\n");
}

void tipar( int **mat, muchie st[500], int k, int *ok, int *p, int height, int width )
{
    int i;
    *ok=1;
    mat[ height-3 ][1] =5;

    for(i=1;i<k;i++)
    {
        switch(p[i+1])
        {
            case 1: mat[ st[i].x][ st[i].y ]  = 5;  break;
            case 2: mat[ st[i].x][ st[i].y ]  = 2;  break;
            case 3: mat[ st[i].x][ st[i].y ]  = 3;  break;
            case 4: mat[ st[i].x][ st[i].y ]  = 4;  break;
            default:    break;
        }
    }

    switch(p[i])
        {
        case 1: mat[ st[i].x][ st[i].y ]  = 5;  break;
        case 2: mat[ st[i].x][ st[i].y ]  = 2;  break;
        case 3: mat[ st[i].x][ st[i].y ]  = 3;  break;
        case 4: mat[ st[i].x][ st[i].y ]  = 4;  break;
        default:    break;
        }
    switch(p[1])
        {
        case 1: mat[ st[1].x][ st[1].y ]  = 5;  break;
        case 2: mat[ st[1].x][ st[1].y ]  = 2;  break;
        case 3: mat[ st[1].x][ st[1].y ]  = 3;  break;
        case 4: mat[ st[1].x][ st[1].y ]  = 4;  break;
        default:    break;
        }
    system("cls");
    afisare(mat,height,width);
}

int main()
{
    int **maze, i, j, n, m;
    srand((unsigned int)time(NULL));


    //printf("nr linii = ");
    //scanf("%d",&n);
    //printf("nr coloane = ");
    //scanf("%d",&m);

    int size = 31;

    maze = malloc( size*sizeof(int*) );
    for( i=0; i < size ; i++)
        maze[i] = calloc( size, sizeof(int) );

    // creare labirint random

    for( i=0; i<size ; i++ )
        for( j=0; j<size; j++ )
            maze[i][j] = !(i==0 || j == 0 || i==size-1 || j==size-1);   // maze edge = 0

    afisare(maze,size,size);

    int pr, dr, k;

    pct *a = calloc( (size/2)*(size/2)+1, sizeof(pct) );
    pct *vec = calloc( 4, sizeof(pct) );

    a[0].x = a[0].y = (size-2)/4*2+2;   // start from middle

    maze[ a[0].x ][ a[0].y ] = 0;

    int nr_puncte = 1;

    system("cls");
    afisare(maze,size,size);

    while( nr_puncte > 0 ){  // cat timp am puncte ce au vecini
        pr = (rand())%nr_puncte;
        k = 0;

        if( maze[ a[pr].x - 2 ][ a[pr].y ] != 0 ){
            vec[k].x = a[pr].x - 2;
            vec[k].y = a[pr].y;
            k++;
        }

        if( maze[ a[pr].x ][ a[pr].y - 2 ] != 0 ){
            vec[k].x = a[pr].x;
            vec[k].y = a[pr].y - 2;
            k++;
        }

        if( maze[ a[pr].x + 2 ][ a[pr].y ] != 0 ){
            vec[k].x = a[pr].x + 2;
            vec[k].y = a[pr].y;
            k++;
        }

        if( maze[ a[pr].x ][ a[pr].y + 2 ] != 0 ){
            vec[k].x = a[pr].x;
            vec[k].y = a[pr].y + 2;
            k++;
        }

        if( k == 0 ){
            a[pr] = a[nr_puncte-1];
            nr_puncte--;
        } else {
            nr_puncte++;
            dr = (rand())%k;
            a[nr_puncte-1] = vec[dr];
            maze[ vec[dr].x ][ vec[dr].y ] = 0;
            maze[ (vec[dr].x + a[pr].x)/2 ][ (vec[dr].y + a[pr].y)/2 ] = 0;

            system("cls");
            afisare(maze,size,size);
        }
    }

    maze[size-3][1] = 0;
    maze[2][size-2] = 0;

    system("cls");
    afisare(maze,size,size);

    n = m = size;

    printf(" Afisati solutie?\nd\\n\n");
    if( getch() == 'n' )
        return 0;

    /* rezolvare labirint */
        maze[ n-3 ][1] = 1;

    muchie *st;
    int  *p;
    st = (muchie*)calloc( (n*m/2) , sizeof(muchie) );
    p  = calloc( (n*m/2) , sizeof(int)  );

    st[1].x = n-3;
    st[1].y = 2;

    //bt();

    int as,ev,ok=0;
    muchie d[5]={{0,0},{0,1},{1,0},{0,-1},{-1,0}};

    k=2;
    while(k>1)
    {
        as=1;ev=0;
        while( as!=0 && ev!=1 )
        {
            if(p[k]<4)
            {
                p[k]++;
                st[k].x = st[k-1].x + d[ p[k] ].x;
                st[k].y = st[k-1].y + d[ p[k] ].y;
                as=1;
                ev = valid(maze, st, k);
            }
            else
                as=0;
        }
        if(as)
            if( st[k].x==1 || st[k].x==n || st[k].y==1 || st[k].y==m )
            {
                tipar(maze, st, k, &ok, p, n, m);
                break;
            }
            else
            {
                k++;
                p[k]=0;
            }
        else k--;
    }

    if(!ok)
        printf("Nu exista solutii\n");

/* eliberare memorie alocata */
    for( i=1; i <= n ; i++)
        free(maze[i]);
    free(maze);
    return 0;
}
