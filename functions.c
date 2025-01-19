#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <termios.h>
#include <poll.h>
#include <string.h>
#include <unistd.h>

#define clear() printf("\033[H\033[J")

//les couleurs
#define RED      "\x1b[31m"
#define GREEN    "\x1b[32m"
#define YELLOW   "\x1b[33m"
#define BLUE     "\x1b[34m"
#define MAGENTA  "\x1b[35m"
#define CYAN     "\x1b[36m"
#define WHITE    "\x1b[0m"


/// /!\ Ne pas toucher à cette fonction, je ne la comprend pas.
int acquisition_time ;
int getch() { 
    int ch;
    struct termios oldattr, newattr;

    tcgetattr(STDIN_FILENO, &oldattr);
    newattr = oldattr;
    newattr.c_lflag &= ~ICANON;
    newattr.c_lflag &= ~ECHO;
    newattr.c_cc[VMIN] = 1;
    newattr.c_cc[VTIME] = 0;
    tcsetattr(STDIN_FILENO, TCSANOW, &newattr);
    struct pollfd mypoll = { STDIN_FILENO, POLLIN|POLLPRI };
    
    if( poll(&mypoll, 1, acquisition_time) )
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldattr);

    return ch; 
}
/// Fin /!\





//transforme un tableau stack en tableau heap
int* stack_to_heap(int len, int* m) {
    int* n = malloc(sizeof(int)*len) ;
    for (int i = 0; i < len; i++) {
      n[i] = m[i];
    }
    return n;
}

//fct auxiliare pour get un string avec getchar
char* getstr() {
    int i = 0;
    int ch;
    char* str = malloc(sizeof(int)*20);
    while((ch = getchar()) != '\n' && ch != EOF ) {
        str[i++] = ch;
    }
    str[i] = '\0';
    return str;
}

//premier menu
char* displayMenu() {
    printf(RED"\n"
           "\n"
           "                                    Si vous constatez un problème, essayez de relancer le jeu                          \n"
           "\n"
           "\n"
           "\n"
           "\n"
           "                     _    _ _           _   _                                                          ___  \n"
           "                    | |  | | |         | | ( )                                                        |__ \\ \n"
           "                    | |  | | |__   __ _| |_|/ ___   _   _  ___  _   _ _ __   _ __   __ _ _ __ ___   ___  ) |\n"
           "                    | |/\\| | '_ \\ / _` | __| / __| | | | |/ _ \\| | | | '__| | '_ \\ / _` | '_ ` _ \\ / _ \\/ / \n"
           "                    \\  /\\  / | | | (_| | |_  \\__ \\ | |_| | (_) | |_| | |    | | | | (_| | | | | | |  __/_|  \n"
           "                     \\/  \\/|_| |_|\\__,_|\\__| |___/  \\__, |\\___/ \\__,_|_|    |_| |_|\\__,_|_| |_| |_|\\___(_)  \n"
           "                                                     __/ |                                                  \n"
           "                                                    |___/                                                   \n"
           "\n"
           "Press any key (max 20 characters):\n"
           WHITE);
    return getstr();

}

//joli ascii art du menu
void displayMenu2(char* name, bool changing_speed, char* str_color, const char* color) {
    clear();
    printf(GREEN"                                                                                                           \n"
           "  +----------------------------------+                                                                              \n"
           "  |                                  |\n"
           "  |       Jeu dev par TraZe          |                                   welcome %s\n"
           "  |                                  |\n"
           "  +----------------------------------+\n"
           "\n"
           "                                 __                          _        __            _       _   \n"
           "                                 \\ \\ _   _ _ __ __ _ ___ ___(_) ___  / _\\_ __  _ __(_)_ __ | |_ \n"
           "                                  \\ \\ | | | '__/ _` / __/ __| |/ __| \\ \\| '_ \\| '__| | '_ \\| __|\n"
           "                               /\\_/ / |_| | | | (_| \\__ \\__ \\ | (__  _\\ \\ |_) | |  | | | | | |_ \n"
           "                               \\___/ \\__,_|_|  \\__,_|___/___/_|\\___| \\__/ .__/|_|  |_|_| |_|\\__|\n"
           "                                                                        |_|                      \n"
           "                                01100100 01101001 01101110 01101111 01110010 01110101 01101110\n"
           "\n"
           "\n"
           "                                                                              +----------------------------------+\n"
           "                Press T: increasing speed = "WHITE"%s"GREEN"                               |         Press S to start         |\n"
           "                Press (R,G,Y,B,M,C,W): color = %s%s"GREEN"                        +----------------------------------+\n\n"
           "                                                                                High Score: 31415926535\n"
           "\n"
           "\n"
           "Press any key: \n"WHITE
           , name, changing_speed?"On ":"Off", color, str_color
           );

}

void print_character (int index) {
    if (index == 0) {
        printf( "                                                              ___                  \n"
                "                                                             /  0\\_               \n"
                "                                              <Press A       |    v|     Press Z>  \n"
                "                                                            /     /                \n"
                "\n"
                "                                                             Dino                  \n"
                );
    }
    if (index == 1) {
        printf( "                                                                                   \n"
                "                                                             /\\_/\\               \n"
                "                                              <Press A      ( o.o )      Press Z>  \n"
                "                                                             > ^ <                 \n"
                "\n"
                "                                                             Chat                  \n" ///quasi sûr que vous allez prendre celui-là
                );
    }
    if (index == 2) {
        printf( "                                                             _____                 \n"
                "                                                            | @ @ |                \n"
                "                                              <Press A      |  _  |      Press Z>  \n"
                "                                                            /  |  \\               \n"
                "\n"
                "                                                             Ghast                 \n"
                );
    }
    if (index == 3) {
        printf( "                                                             .----                \n"
                "                                                            / O O \\              \n"
                "                                              <Press A      | \\_/ |      Press Z>\n"
                "                                                            '----'                \n"
                "\n"
                "                                                             Smiley               \n"
                );
    }
}

//un troisième menu parce que pourquoi pas :p
void displayMenu3(const char* color, int index) {
    clear();
    printf("%s\n"
           "\n"
           "               ___ _                                                          _                          _            \n"
           "              / __\\ |__   ___   ___  ___  ___   _   _  ___  _   _ _ __    ___| |__   __ _ _ __ __ _  ___| |_ ___ _ __ \n"
           "             / /  | '_ \\ / _ \\ / _ \\/ __|/ _ \\ | | | |/ _ \\| | | | '__|  / __| '_ \\ / _` | '__/ _` |/ __| __/ _ \\ '__|\n"
           "            / /___| | | | (_) | (_) \\__ \\  __/ | |_| | (_) | |_| | |    | (__| | | | (_| | | | (_| | (__| ||  __/ |   \n"
           "            \\____/|_| |_|\\___/ \\___/|___/\\___|  \\__, |\\___/ \\__,_|_|     \\___|_| |_|\\__,_|_|  \\__,_|\\___|\\__\\___|_|   \n"
           "                                                |___/                                                                 \n"
           "\n"
           "\n"
           "\n"
           , color
           );
           
    print_character(index);           
           
    printf("%s\n"
           "\n"
           "\n"
           "\n"
           "Press S to start: \n"WHITE
           , color
           );

}

//menu pause
void displayPauseMenu() {
    clear();
    printf(RED"\n"
           "\n"
           "                                             Press M to go back to title screen                                  \n"
           "\n"
           "\n"
           "\n"
           "\n"
           "                                                                                                                        \n"
           "                    PPPPPPPPPPPPPPPPP                                                                                   \n"
           "                    P::::::::::::::::P                                                                                  \n"
           "                    P::::::PPPPPP:::::P                                                                                 \n"
           "                    PP:::::P     P:::::P                                                                                \n"
           "                      P::::P     P:::::Paaaaaaaaaaaaa  uuuuuu    uuuuuu      ssssssssss       eeeeeeeeeeee              \n"
           "                      P::::P     P:::::Pa::::::::::::a u::::u    u::::u    ss::::::::::s    ee::::::::::::ee            \n"
           "                      P::::PPPPPP:::::P aaaaaaaaa:::::au::::u    u::::u  ss:::::::::::::s  e::::::eeeee:::::ee          \n"
           "                      P:::::::::::::PP           a::::au::::u    u::::u  s::::::ssss:::::se::::::e     e:::::e          \n"
           "                      P::::PPPPPPPPP      aaaaaaa:::::au::::u    u::::u   s:::::s  ssssss e:::::::eeeee::::::e          \n"
           "                      P::::P            aa::::::::::::au::::u    u::::u     s::::::s      e:::::::::::::::::e           \n"
           "                      P::::P           a::::aaaa::::::au::::u    u::::u        s::::::s   e::::::eeeeeeeeeee            \n"
           "                      P::::P          a::::a    a:::::au:::::uuuu:::::u  ssssss   s:::::s e:::::::e                     \n"
           "                    PP::::::PP        a::::a    a:::::au:::::::::::::::uus:::::ssss::::::se::::::::e                    \n"
           "                    P::::::::P        a:::::aaaa::::::a u:::::::::::::::us::::::::::::::s  e::::::::eeeeeeee            \n"
           "                    P::::::::P         a::::::::::aa:::a uu::::::::uu:::u s:::::::::::ss    ee:::::::::::::e            \n"
           "                    PPPPPPPPPP          aaaaaaaaaa  aaaa   uuuuuuuu  uuuu  sssssssssss        eeeeeeeeeeeeee            \n"
           "                                                                                          \n"
           "                                                                                          \n"
           "                                                                                          \n"
           "                                                                                          \n"
           "\n"
           "Press escape to resume the game:\n"
           WHITE);
}



// Initializes the board.
void init_board(int row, int col, char board[row][col]) {
    for (int j = 0; j < col; j++) {
        if (j%4 == 0 || j%4 == 1) {
            board[0][j] = '=' ;
        } else {
            board[0][j] = '-' ;
        }
        
    }
    for (int i = 1; i < row; i++) {
        for (int j = 0; j < col; j++)
            board[i][j] = ' ' ;
    }
}

// Prints the game board.
void print_board(int row, int col, char board[row][col], const char* color) {
    clear();
    for (int i = row-1; i >= 0 ; i--) {
        for (int j = 0; j < col; j++)
            printf("%s%c"WHITE, color, board[i][j]);
        printf("\n");
    }
}

// Applies Gravity to the board.
void gravity(int row, int col, char board[row][col], bool* collision) {
    int height = 1 ; 
    for (int i = 1; i < 6; i++) {
        for (int j = 0; j < col; j++) {
            if (board[i][j] == 'X') {
    	        board[i][j] = ' ' ;
        	    if (j > 0) {
        	        if (board[i][j-1] != ' ' && board[i][j-1] != 'X') {
        	            *collision = true;
        	        }
        	        board[i][j-1] = 'X' ;
        	    }
            }
        }
    }
    for (int j=0; j<col-1; j++) {
        board[0][j] = board[0][j+1];
    }
    board[0][col-1] = board[0][col-5];
}

//draws the cute lil character
void draw_dino (int height, int row, int col, char board[row][col], int index) {
    int pos = 4;
    if (index == 0) { // Dino
        board[height+3][pos+3] = '0' ;
        board[height+1][pos-1] = '/' ;
        board[height+2][pos] = '|' ;
        board[height+3][pos] = '/' ;
        board[height+4][pos+1] = '_' ;
        board[height+4][pos+2] = '_' ;
        board[height+4][pos+3] = '_' ;
        board[height+3][pos+4] = '\\' ;
        board[height+2][pos+5] = 'v' ;
        board[height+3][pos+5] = '_' ;
        board[height+2][pos+6] = '|' ;
        board[height+1][pos+4] = '/' ;
    }
    if (index == 1) {  // Chat
        board[height+1][pos] = '>';
        board[height+1][pos+2] = '^';
        board[height+1][pos+4] = '<';
        board[height+2][pos-1] = '(';
        board[height+2][pos+1] = 'o';
        board[height+2][pos+2] = '.';
        board[height+2][pos+3] = 'o';
        board[height+2][pos+5] = ')';
        board[height+3][pos] = '/';
        board[height+3][pos+1] = '\\';
        board[height+3][pos+2] = '_';
        board[height+3][pos+3] = '/';
        board[height+3][pos+4] = '\\';

    }
    if (index == 2) {  // Ghast
        board[height+1][pos] = '/';
        board[height+1][pos+3] = '|';
        board[height+1][pos+6] = '\\';
        board[height+2][pos] = '|';
        board[height+2][pos+4] = '_';
        board[height+2][pos+6] = '|';
        board[height+3][pos] = '|';
        board[height+3][pos+3] = '@';
        board[height+3][pos+5] = '@';
        board[height+3][pos+6] = '|';
        board[height+4][pos+1] = '_';
        board[height+4][pos+2] = '_';
        board[height+4][pos+3] = '_';
        board[height+4][pos+4] = '_';
        board[height+4][pos+5] = '_';
    }
    if (index == 3) {  // Smiley
        board[height+1][pos-1] = '\'';
        board[height+1][pos] = '-';
        board[height+1][pos+1] = '-';
        board[height+1][pos+2] = '-';
        board[height+1][pos+3] = '-';
        board[height+1][pos+4] = '-';
        board[height+1][pos+5] = '\'';
        board[height+2][pos-1] = '|';
        board[height+2][pos] = ' ';
        board[height+2][pos+1] = '\\';
        board[height+2][pos+2] = '_';
        board[height+2][pos+3] = '/';
        board[height+2][pos+5] = '|';
        board[height+3][pos-1] = '/';
        board[height+3][pos] = ' ';
        board[height+3][pos+1] = 'O';
        board[height+3][pos+2] = ' ';
        board[height+3][pos+3] = 'O';
        board[height+3][pos+5] = '\\';
        board[height+4][pos] = '-';
        board[height+4][pos+1] = '-';
        board[height+4][pos+2] = '-';
        board[height+4][pos+3] = '-';
        board[height+4][pos+4] = '-';

    }
}

//efface le potit dino :(
void delete_dino (int row, int col, char board[row][col]) {
    for (int i=1; i<10; i++) {
        for (int j=3; j<11; j++) {
            if (board[i][j]!='X') {
                board[i][j] = ' ';
            }
        }
    }
}

//renvoie le nombre de chiffres de l'entier fourni en base 10
int get_size(int nb) {
    int size = 0;
    if (nb == 0) {
        return 1;
    }
    while (nb >= 1) {
        nb = nb / 10;
        size++;
    }
    return size;
}

//draw un nombre donné à l'écran en base 10
void draw_number (int row, int col, char board[row][col], int nb, int x, int y) { //dérivée de nine_invasion
    int len = get_size(nb);
    int n;
    for (int i=len; i>0; i--) {
        n = nb%10;
        nb = nb / 10;
        board[x][y + i] = n + '0';
    }
}

//draw un texte donné à l'écran
void draw_text (int row, int col, char board[row][col], char* text, int len, int x, int y) {
     for (int j=0; j<len; j++) {
         board[x][y+j] = text[j];
     }
}

//affiche les différents textes et nombres
void init_text (int row, int col, char board[row][col]) {
    char* text;
    draw_text(row, col, board, text="Score:", 6, row-2, 2);
    draw_text(row, col, board, text="Press X to jump", 15, row-4, 2);
}

//animates the dino's jump
int jump(int frame, int* animation, int height) {
    return height + animation[frame];
}

//makes an "enemy" spawn
void spawn_enemy(int row, int col, char board[row][col], int index) {
    if (index==0) {
        board[1][col-1] = 'X' ;
        board[1][col-2] = 'X' ;
        board[2][col-2] = 'X' ;
        board[1][col-3] = 'X' ;
    }
    if (index==1) {
        board[1][col-2] = 'X' ;
        board[2][col-2] = 'X' ;
    }
    if (index==2) {
        board[1][col-2] = 'X' ;
        board[2][col-2] = 'X' ;
        board[1][col-1] = 'X' ;
        board[2][col-1] = 'X' ;
    }
    if (index==3) {
        board[1][col-3] = 'X' ;
        board[2][col-3] = 'X' ;
        board[1][col-2] = 'X' ;
        board[1][col-1] = 'X' ;
        board[2][col-1] = 'X' ;
    }
    if (index==4) {
        board[1][col-1] = 'X' ;
        board[2][col-1] = 'X' ;
        board[3][col-1] = 'X' ;
    }
}


void print_centered(char* text, int width) {
    int len = strlen(text);
    int padding = (width-len) / 2;

    if (padding > 0) {
        printf("%*s%s%*s", padding, "", text, width - len - padding, "");
    } else {
        printf("%s", text);
    }
}

typedef struct {char* username; int score;} profile;

int read_file(profile** profiles) {
    FILE* f = fopen("scores.txt", "r");
    if (f == NULL) return 0;
    char t_username[20];
    int t_score;
    int lines = 0;
    while (fscanf(f, "%20s - %d\n", t_username, &t_score) == 2) {
        lines++;
    }

    *profiles = malloc(sizeof(profile) * lines);
    if (*profiles == NULL) {
        fclose(f);
        return 0; 
    }
    rewind(f);

    for (int i=0; i<lines; i++) {
        fscanf(f, "%20s - %d\n", t_username, &t_score);
        (*profiles)[i].username = strdup(t_username);
        (*profiles)[i].score = t_score;
    }
    fclose(f);
    return lines;
}

int save_score(char* username, int score, int lines, profile** profiles) {
    int i=0;
    while(i<lines-1 && score<(*profiles)[i].score) i++;
    for(int j=lines-1; j>i; j--) {
        (*profiles)[j] = (*profiles)[j-1];
    }
    (*profiles)[i] = (profile){username, score};
    
    FILE* f = fopen("scores.txt", "w");
    for(int k=0; k<lines+1; k++) {
        fprintf(f, "%s - %d\n", (*profiles)[k].username, (*profiles)[k].score);
    }
    fclose(f);
    
    return i;
    
}




