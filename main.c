#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <sys/time.h>
#include "functions.h"

#define clear() printf("\033[H\033[J")

//les couleurs
#define RED      "\x1b[31m"
#define GREEN    "\x1b[32m"
#define YELLOW   "\x1b[33m"
#define BLUE     "\x1b[34m"
#define MAGENTA  "\x1b[35m"
#define CYAN     "\x1b[36m"
#define WHITE    "\x1b[0m"






int main () {
    ///variables -------------------------------------------------------------
    
    ///variables menu ------------------
    
    //menus
    char choix;
    typedef enum {
        PSEUDO = 1,       // Menu choix du pseudo
        HOMEPAGE = 2,        // Menu choix de la couleur
        CHARACTER = 3,    // Menu choix du personnage
        SCORES = 4,       // Menu des scores
        GAME = 0,         // Jeu en cours
        DEATH = -1,       // Menu de mort
        PAUSE = -2        // Menu pause
    } Menu;
    Menu menu = PSEUDO;
    bool init = false;
    
    //menu 1
    char* username;
    
    //menu 2
    int NB_COLORS = 7;
    int ch_colors[7] = {'r', 'g', 'y', 'b', 'm', 'c', 'w'};
    char* str_colors[7] = {"Red    ", "Green  ", "Yellow ", "Blue   ", "Magenta", "Cyan   ", "White  "};
    char* str_color = "Red    ";
    char* colors[7] = {RED, GREEN, YELLOW, BLUE, MAGENTA, CYAN, WHITE};
    const char* color = RED;
    bool changing_speed = false;
    bool rainbow = false;
    
    //menu 3
    int index = 0;
    int NB_CHARACTERS = 4;
    
    /*
    //menu score
    FILE* score_file;
    score_file = fopen("scores.txt", "a");
    for (int i=0; i<100; i++) {
        putc('a',score_file);
    }
    fclose(score_file);
    */
    
    ///game variables ------------------
    
    // board variables
    char board[25][130] ;
    int ROW = 25;
    int COL = 130;
    
    // score variables
    int score = 0;
    int clr_index = 0;
    bool dead = false;
    typedef struct {char* username; int score;} profile;
    int NB_PROFILES = 20;
    profile* profiles;
    
    //animation variables
    int jump_frame = 0;
    int height = 0;
    int ANIM_LEN = 22;
    int m[22] = {0,1,1,0,1,1,0,1,0,0,0,0,0,0,-1,0,-1,-1,0,-1,-1};
    int* animation = stack_to_heap(ANIM_LEN, m);
    
    //enemy variables
    int NB_ENEMIES = 5;
    int spawn_time = 0;
    int COOLDOWN = 20;

    // Time variables
    double refresh_rate = 0.06;
    struct timeval last, now; 
    gettimeofday(&last, NULL);
    int nb_cd = 1;
    int speed_cooldown = 1;

    
    
    ///boucle principale ----------------------------------------------------
    int run = true ;
    while (run) {
        
        
        if (menu == PSEUDO) {
            //menu1, choix du pseudo
            username = displayMenu();
            menu = HOMEPAGE;
            init = true;
        }
        
        
        
        else if (menu == HOMEPAGE) {
            if (init) {
                //init du menu2
                displayMenu2(username, changing_speed, str_color, color);
                init = false;
            }
            else {
                //menu2, choix de la couleur + changing speed
                choix = getch();
                if (choix == 't' || choix == 'T') {
                    changing_speed = changing_speed?false:true;
                    init = true;
                }
                if (choix == 'f' || choix == 'F') {
                    rainbow = rainbow?false:true;
                    init = true;
                }
                if (choix == 's' || choix == 'S') {
                    menu = CHARACTER;
                    init = true;
                }
                for (int i=0; i<NB_COLORS; i++) {
                    if (choix == ch_colors[i] && str_color != str_colors[i]) {
                        color = colors[i];
                        str_color = str_colors[i];
                        init = true;
                    }
                }
            }
        }
        
        
        
        else if (menu == CHARACTER) {
            if (init) {
                displayMenu3(color, index);
                init = false;
            }
            else {
                //menu3, choix du personnage
                choix = getch();
                if (choix == 'a' || choix == 'A') {
                    if (index>0) {
                        index--;
                        init = true;
                    }
                }
                if (choix == 'z' || choix == 'Z') {
                    if (index<NB_CHARACTERS-1) {
                        index++;
                        init = true;
                    }
                }
                if (choix == 's' || choix == 'S') {
                    menu = GAME;
                    init = true;
                    
                    //default settings
                    score = 0;
                    jump_frame = 0;
                    height = 0;
                    refresh_rate = 0.06;
                }
            }
        }
        
        
        
        
        else if (menu == SCORES) {
            //menu avec les scores
            menu = GAME; /// en travaux
        }
        
        
        
        
        else if (menu == DEATH) {
            //menu de mort
            printf("\033[?25l");
            if (init) {
                int lines = read_file(&profiles);
                int place = save_score(username, score, lines-1, &profiles);
                read_file(&profiles);
                
                clear();
                printf("\n\nLeaderboard :\n\n");
                printf("                                             | "BLUE" n° "WHITE"|"BLUE); print_centered("Pseudo", 20); printf(WHITE" | "BLUE); print_centered("Score", 5); printf(WHITE"  |\n");
                for (int i = 0; i < lines; i++) {
                    if (i==place) {
                        printf("                                             |-----|---------------------|--------|\n"
                               RED"                                             "WHITE"|"RED"%3d. "WHITE"|"RED,i+1); print_centered(profiles[i].username,20); printf(WHITE" |"RED" %5d  "WHITE"|  (High Score!)\n"
                               ,profiles[i].score);
                    }
                    else {
                        printf("                                             |-----|---------------------|--------|\n"
                               "                                             |%3d. |",i+1); print_centered(profiles[i].username,20); printf(" | %5d  |\n"
                               ,profiles[i].score);
                    }
                }
                printf("                                             --------------------------------------\n");
                printf("Press S to continue");
                
                init = false;
            }
            else {
                choix = getch();
                if (choix == 's' || choix == 'S') {
                    menu = HOMEPAGE;
                    init = true;
                }
            }
        }
        
        
        
        else if (menu == PAUSE) {
            if (init) {
                displayPauseMenu();
                init = false;
            }
            else {
                //menu pause
                choix = getch();
                if (choix == 27) {
                    menu = GAME;
                }
                if (choix == 'm' || choix == 'M') {
                    menu = HOMEPAGE;
                }
            }
        }
        
        
        
        else if (menu == GAME) {
            if (init) {
                // Init everything
                init_board(ROW, COL, board);
                init_text(ROW, COL, board);
                if (changing_speed) {
                    draw_text(ROW, COL, board, "Current speed:", 14, ROW-6, 2);
                    draw_text(ROW, COL, board, "Warning: the increasing speed can cause unwanted flashing", 57, ROW-7, 2);
                }
                print_board(ROW, COL, board, color) ;
                draw_dino(height, ROW, COL, board, index);
                init = false;
            }
            else {
                //check if user is pressing the space bar
                int n  = getch();
                if (n=='x' && jump_frame==0) {
                    jump_frame = 1;
                }
                if (n=='q') {
                    run = false;
                }
                if (n==27) { //if user presses escape, it pauses the game
                    menu = PAUSE;
                }
                
                
                //gets time and checks if a refresh is needed
                gettimeofday(&now, NULL);
                double time_taken = (now.tv_sec - last.tv_sec) + (now.tv_usec - last.tv_usec) * 1e-6;
                
                if (time_taken > refresh_rate) {
                    
                    //updates score
                    score++;
                    //updates speed
                    if (changing_speed && score%100 == 0 && score%speed_cooldown == 0) {
                        refresh_rate = refresh_rate * (0.9);
                        speed_cooldown += nb_cd;
                        nb_cd++;
                    }
                    
                    //jump animation for the dino
                    if (!jump_frame==0) { 
                        height = jump(jump_frame, animation, height);
                        jump_frame = (jump_frame+1)%ANIM_LEN;
                        delete_dino(ROW, COL, board);
                        draw_dino(height, ROW, COL, board, index);
                    }
                    
                    //apllies gravity, refreshs the board
                    gravity(ROW, COL, board, &dead);
                    draw_number(ROW, COL, board, score, ROW-2, 8);
                    if (changing_speed) {
                        draw_number(ROW, COL, board, nb_cd, ROW-6, 16);
                    }
                    if (rainbow) {
                        print_board(ROW, COL, board, colors[index++%NB_COLORS]);
                    } else {
                        print_board(ROW, COL, board, color);
                    }
                    
                    last = now;
                    
                    //spawns an enemy
                    spawn_time++;
                    if (spawn_time>COOLDOWN && rand()%20 == 13) { //valeur totalement arbitraire
                        spawn_time = 0;
                        spawn_enemy(ROW, COL, board, rand()%NB_ENEMIES);
                    }
                    
                    if (dead) {
                        menu = DEATH;
                        init = true;
                        dead = false;
                    }
                    
                }
                usleep(5000); 
            }
        }
    }
}



