#include<stdio.h>

#include<string.h>

#include<time.h>

#include<conio.h>

#include<windows.h>



//char name[]="record.echo";

int box[4][4] = {0};

void game();

void welcome();

void goodbye();

void new_game();

void move_up();

void move_down();

void move_left();

void move_right();

void new_box();

int total_blank();

void chk_gameover();

int score;

int best;

int flag_gameover ;

int flag_newnum;

FILE * fp;

int main()

{

    welcome();

    Sleep(1500);

    system("cls");

    if((fp = fopen("record.echo","a+")) == NULL)

        printf("打开记录失败\n");

    else

        printf("已打开记录\n");

    game();

    fclose(fp);

    system("del record.echo");

    fp =fopen("record.echo","a+");

    fprintf(fp,"%d",best);

    fclose(fp);

    goodbye();

    return 0;

}

void game()

{

    int i , j;

    fscanf(fp,"%d",&best);

    printf("%d",best);

    new_game();

    char cmd;

    while(1)

    {

        cmd = getch();

        if(flag_gameover)

        {

            if(cmd == 'y' || cmd == 'Y')

            {

                for(i = 0 ; i < 4 ; i++)

                {

                    for( j = 0 ; j < 4 ;j++)

                    {

                        box[i][j] = 0;

                    }

                }

                new_game();

                continue;

            }

            else if(cmd == 'n' || cmd == 'N')

            {



                return ;

            }

            else

            {

                continue;

            }

        }

        flag_newnum = 0;





        switch(cmd)

        {

            case 27:

                goodbye();

                break;

            case 'w':

            case 'W':

            move_up();

            break;

            case 'a':

            case 'A':

            move_left();

            break;

            case 's':

            case 'S':

            move_down();

            break;

            case 'd':

            case 'D':

            move_right();

            break;

        }

        if(flag_newnum)

        {

            new_box();

            refresh_print();

        }

    }

}



void new_game()

{

    system("cls");

    score = 0;

    flag_gameover = 0;

    flag_newnum = 1;

    int i , j , n ;

    srand(time(0));

    n = rand() % 16;

    for( i = 0 ; i < 4 ; i++)

    {

        for( j = 0 ; j < 4 ; j++)

        {

            n--;

            if(n==0)

            {

                box[i][j] = 2;

            }

        }

    }

    new_box();

    system("cls");

    refresh_print();

}





void new_box()

{

     int i , j , n;

     srand(time(0));

     if(total_blank() != 0)

     {

        n = rand() % total_blank();

     }

     else

     {

        n = rand() % 15;

     }

     for (i = 0; i < 4; i++)

     {

         for (j = 0; j < 4; j++)

         {

             if (box[i][j] == 0 && n-- == 0)

             {

                 box[i][j] = 2;

                 return;

             }

         }

     }

 }

int total_blank()

{

    int i , j;

     int n = 0;

     for (i = 0; i < 4; i++)

     {

         for (j = 0; j < 4; j++)

         {

            if(box[i][j] == 0)

            {

                n++;

            }

         }

     }

     return n;

}

void refresh_print()

{

    system("cls");

    int i , j ;

    printf("\n\n\n\n\n");

    printf("\t\t\t\t\t\t************************\n");

    for(i = 0 ; i < 4; i++)

    {

        for(j = 0 ; j < 4 ;j++)

        {

            if(j == 0)

            {

                printf("\t\t\t\t\t\t|");

            }

            if(box[i][j] != 0)

                printf("%-5d|",box[i][j]);

            else

                printf("     |");

        }

        printf("\n");

    }

    printf("\t\t\t\t\t\t************************\n");

    printf("\n");

    printf("\t\t\tw a s d 控制\n\t\t\t按ESC退出\n");

    printf("\t\t\tscore:%d",score);

    printf("\t\tbest:%d",best);



    if(total_blank() == 0)

    {

        chk_gameover();

        if(flag_gameover)

        {

            printf("GAME OVER!!!\n是否继续[y/n?]\n");

        }

    }

}





void move_up()

{

     int i , j , k;

     for (i = 0; i < 4; i++)

     {

         for (j = 1, k = 0; j < 4; j++)

         {

             if (box[j][i] > 0)

             {

                 if (box[k][i] == box[j][i])

                 {

                     box[k][i] <<= 1;

                     score += box[k][i];

                     box[j][i] = 0;

                     best = (score > best ? score : best);

                     flag_newnum = 1;

                 }

                 else if (box[k][i] == 0)

                 {

                     box[k][i] = box[j][i];

                     box[j][i] = 0;

                     flag_newnum = 1;

                 }

                 else

                 {

                     box[++k][i] = box[j][i];

                     if (j != k)

                     {

                         box[j][i] = 0;

                         flag_newnum = 1;

                     }

                 }

             }

         }

     }

 }



void move_down()

 {

     int i , j , k;

     for (i = 0; i < 4; i++)

     {

         for (j = 2, k = 3; j >= 0; j--)

         {

             if (box[j][i] > 0)

             {

                 if (box[k][i] == box[j][i])

                 {

                     box[k][i] <<= 1;

                     score += box[k][i];

                     best = (score > best ? score : best);

                     box[j][i] = 0;

                     flag_newnum = 1;

                 }

                 else if (box[k][i] == 0)

                 {

                     box[k][i] = box[j][i];

                     box[j][i] = 0;

                     flag_newnum = 1;

                 }

                 else

                 {

                     box[--k][i] = box[j][i];

                     if (j != k)

                     {

                         box[j][i] = 0;

                         flag_newnum = 1;

                     }

                 }

             }

         }

     }

 }

void move_left()

{

    int i , j , k;

    for( i = 0 ; i < 4 ; i++)

    {

        for( j = 1, k = 0 ; j < 4 ; j++)

        {

            if(box[i][j] > 0)

            {

                if(box[i][j] == box[i][k])

                {

                    box[i][k] <<= 1;

                    score += box[i][k];

                    best = (score > best ? score : best);

                    box[i][j] = 0;

                    flag_newnum = 1;

                }

                else if(box[i][k] == 0)

                {

                    box[i][k] = box[i][j];

                    box[i][j] = 0;

                    flag_newnum = 1;

                }

                else

                {

                    box[i][++k] = box[i][j];

                    if(j != k)

                    {

                        box[i][j] = 0;

                        flag_newnum = 1;

                    }

                }

            }

        }

    }

}





void move_right()

{

    int i , j , k;

    for( i = 0 ; i < 4 ; i++)

    {

        for( j = 2 , k = 3; j >= 0 ; j--)

        {

            if(box[i][j] > 0)

            {

                if(box[i][j] == box[i][k])

                {

                    box[i][k] <<= 1;

                    score += box[i][k];

                    best = (score > best ? score : best);

                    box[i][j] = 0;

                    flag_newnum = 1;

                }

                else if(box[i][k] == 0)

                {

                    box[i][k] = box[i][j];

                    box[i][j] = 0;

                    flag_newnum = 1;

                }

                else

                {

                box[i][--k] = box[i][j];

                if( j != k)

                {

                    box[i][j] = 0;

                    flag_newnum = 1;

                }

                }

            }

        }

    }

}

void chk_gameover()

{

    int i , j;

    for( i = 0 ; i < 4; i++)

    {

        for( j = 0 ; j < 3 ; j++)

        {

            if(box[i][j] == box[i][j+1] || box[j][i] == box[j+1][i])

            {

                flag_gameover = 0;

                return ;

            }

        }

    }

    flag_gameover = 1;

}

void welcome()

{

    system("color 09");

    printf("\n\n\n\n\n");

    printf("\t\t\t\t\t\t*******************************\n");

    printf("\t\t\t\t\t\t*****   2048   by echo      ***\n");

    printf("\t\t\t\t\t\t*****    suseecho@sina.com  ***\n");

    printf("\t\t\t\t\t\t*******************************\n");

}

void goodbye()

{



    if(fp != NULL)

    {

        fclose(fp);

        system("del record.echo");

        fp =fopen("record.echo","a+");

        fprintf(fp,"%d",best);

        fclose(fp);

    }

    system("cls");

    system("color 0c");

    printf("\n\n\n\n\n");

    printf("\t\t\t\t\t发现bug联系我：\tsuseecho@sina.com\n");

    system("pause");

    exit(0);

}


