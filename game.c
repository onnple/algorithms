//
// Created by Once on 2019/12/9.
//

#include "game.h"
#include <stdio.h>
#include <stdlib.h>

void game_start(void){
    int n, turn = 0;
    while(1){
        printf("[Info] Enter N: \n");
        scanf("%d", &n);
        if(n < 3)
            printf("[Warn] N is too small, please enter again.\n");
        else
            break;
    }
    printf("[Info] Waiting......\n");

    Board *board = game_board_new(n);

    printf("[Info] You first or Computer first? (1/0)\n");
    scanf("%d", &turn);
    int i, j, p, value;
    printf("\n\n");
    while(1){
        if(game_board_is_full(board)){
            printf("\n\n------------- Just So So -------------\n");
            break;
        }
        if(turn){
            printf("[Info] Row & Column: \n");
            scanf("%d %d", &i, &j);
            i = abs(i);
            j = abs(j);
            if(!game_board_is_empty(board, i * n + j)){
                turn = 1;
                continue;
            }
            printf("\n[CHESS]    You: \n");
            game_place(board, i * n + j, Human);
            game_show(board);
            if(game_human_is_win(board)){
                printf("\n\n!!!!!!!!!!!!!  You Win  !!!!!!!!!!!!!\n");
                break;
            }
            turn = 0;
        }
        else{
            printf("\n[CHESS]  Computer: \n");
//            game_find_comp_move_basic(board, &p, &value);
            game_find_comp_move(board, &p, &value, -1, 1);
            game_place(board, p, Comp);
            game_show(board);
            if(value == Win){
                printf("\n\nxxxxxxxxxxxxx  You Lose  xxxxxxxxxxxxx\n");
                break;
            }
            turn = 1;
        }
    }
    game_clear(board);
}

Board *game_board_new(int n){
    if(n < 3){
        perror("n is too small");
        return NULL;
    }
    Board *board = (Board*)malloc(sizeof(Board));
    board->n = n;
    board->grids = (Grid*)malloc(sizeof(Grid) * n * n);
    for (int i = 0; i < n * n; ++i) {
        board->grids[i].state = 0;
        board->grids[i].role = None;
    }
    return board;
}

void game_show(Board *board){
    if(board == NULL)
        return;
    int n = board->n;
    printf("--------------------\n");
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if(board->grids[i * n + j].state == 0)
                printf("*  ");
            else if(board->grids[i * n + j].state == 1 && board->grids[i * n + j].role == Human)
                printf("x  ");
            else if(board->grids[i * n + j].state == 1 && board->grids[i * n + j].role == Comp)
                printf("o  ");
        }
        printf("\n");
    }
    printf("--------------------\n");
}

int game_board_is_empty(Board *board, int p){
    if(p >= board->n * board->n){
        perror("overflow");
        return 0;
    }
    return board->grids[p].state == 0;
}

int game_board_is_full(Board *board){
    if(board == NULL)
        return 0;
    int n = board->n;
    for (int i = 0; i < n * n; ++i) {
        if(board->grids[i].state == 0)
            return 0;
    }
    return 1;
}

// 横线(水平)、直线(垂直)、斜线(对角)
int game_immiediate_comp_win(Board *board, int *bestp){
    int n = board->n;
    int step = 0, left, i, j, p = -1;

    for (i = 0; i < n; ++i) {
        step = 0, left = 0;
        for (j = 0; j < n; ++j) {
            if(board->grids[i * n + j].state == 1 && board->grids[i * n + j].role == Comp)
                step++;
            else if(board->grids[i * n + j].state == 0 && board->grids[i * n + j].role == None){
                left++;
                p = i * n + j;
            }
        }
        if(left == 1 && step + left == n){
            *bestp = p;
            return 1;
        }
    }

    p = -1;
    for (i = 0; i < n; ++i) {
        step = 0, left = 0;
        for (j = 0; j < n; ++j) {
            if(board->grids[i + j * n].state == 1 && board->grids[i + j * n].role == Comp)
                step++;
            else if(board->grids[i + j * n].state == 0 && board->grids[i + j * n].role == None){
                left++;
                p = i + j * n;
            }
        }
        if(left == 1 && step + left == n){
            *bestp = p;
            return 1;
        }
    }

    step = 0, left = 0, p = -1;
    for (i = 0; i < n; ++i) {
        if(board->grids[i * n + i].state == 1 && board->grids[i * n + i].role == Comp)
            step++;
        else if(board->grids[i * n + i].state == 0 && board->grids[i * n + i].role == None){
            left++;
            p = i * n + i;
        }
    }
    if(left == 1 && step + left == n){
        *bestp = p;
        return 1;
    }

    step = 0, left = 0, p = -1;
    for (i = 0; i < n; ++i) {
        if(board->grids[i * n + (n - 1 - i)].state == 1 && board->grids[i * n + (n - 1 - i)].role == Comp)
            step++;
        else if(board->grids[i * n + (n - 1 - i)].state == 0 && board->grids[i * n + (n - 1 - i)].role == None){
            left++;
            p = i * n + (n - 1 - i);
        }
    }
    if(left == 1 && step + left == n){
        *bestp = p;
        return 1;
    }
    return 0;
}

int game_immiediate_human_win(Board *board, int *bestp){
    int n = board->n;
    int step = 0, left, i, j, p = -1;

    for (i = 0; i < n; ++i) {
        step = 0, left = 0;
        for (j = 0; j < n; ++j) {
            if(board->grids[i * n + j].state == 1 && board->grids[i * n + j].role == Human)
                step++;
            else if(board->grids[i * n + j].state == 0 && board->grids[i * n + j].role == None){
                left++;
                p = i * n + j;
            }
        }
        if(left == 1 && step + left == n){
            *bestp = p;
            return 1;
        }
    }

    p = -1;
    for (i = 0; i < n; ++i) {
        step = 0, left = 0;
        for (j = 0; j < n; ++j) {
            if(board->grids[i + j * n].state == 1 && board->grids[i + j * n].role == Human)
                step++;
            else if(board->grids[i + j * n].state == 0 && board->grids[i + j * n].role == None){
                left++;
                p = i + j * n;
            }
        }
        if(left == 1 && step + left == n){
            *bestp = p;
            return 1;
        }
    }

    step = 0, left = 0, p = -1;
    for (i = 0; i < n; ++i) {
        if(board->grids[i * n + i].state == 1 && board->grids[i * n + i].role == Human)
            step++;
        else if(board->grids[i * n + i].state == 0 && board->grids[i * n + i].role == None){
            left++;
            p = i * n + i;
        }
    }
    if(left == 1 && step + left == n){
        *bestp = p;
        return 1;
    }

    step = 0, left = 0, p = -1;
    for (i = 0; i < n; ++i) {
        if(board->grids[i * n + (n - 1 - i)].state == 1 && board->grids[i * n + (n - 1 - i)].role == Human)
            step++;
        else if(board->grids[i * n + (n - 1 - i)].state == 0 && board->grids[i * n + (n - 1 - i)].role == None){
            left++;
            p = i * n + (n - 1 - i);
        }
    }
    if(left == 1 && step + left == n){
        *bestp = p;
        return 1;
    }
    return 0;
}

int game_human_is_win(Board *board){
    int n = board->n;
    int step = 0, i, j;

    for (i = 0; i < n; ++i) {
        step = 0;
        for (j = 0; j < n; ++j) {
            if(board->grids[i * n + j].state == 1 && board->grids[i * n + j].role == Human)
                step++;
        }
        if(step == n)
            return 1;
    }

    for (i = 0; i < n; ++i) {
        step = 0;
        for (j = 0; j < n; ++j) {
            if(board->grids[i + j * n].state == 1 && board->grids[i + j * n].role == Human)
                step++;
        }
        if(step == n)
            return 1;
    }

    step = 0;
    for (i = 0; i < n; ++i) {
        if(board->grids[i * n + i].state == 1 && board->grids[i * n + i].role == Human)
            step++;
    }
    if(step== n)
        return 1;

    step = 0;
    for (i = 0; i < n; ++i) {
        if(board->grids[i * n + (n - 1 - i)].state == 1 && board->grids[i * n + (n - 1 - i)].role == Human)
            step++;
    }
    if(step == n)
        return 1;
    return 0;
}

void game_place(Board *board, int p, Role role){
    if(p >= board->n * board->n){
        perror("overflow");
        return;
    }
    board->grids[p].state = 1;
    board->grids[p].role = role;
}

void game_unplace(Board *board, int p){
    if(p >= board->n * board->n){
        perror("overflow");
        return;
    }
    board->grids[p].state = 0;
    board->grids[p].role = None;
}

void game_find_comp_move_basic(Board *board, int *bestp, int *value){
    int dc, response;
    if(game_board_is_full(board))
        *value = Draw;
    else if(game_immiediate_comp_win(board, bestp))
        *value = Win;
    else{
        *value = Loss;
        int n = board->n;
        for (int i = 0; i < n * n; ++i) {
            if(game_board_is_empty(board, i)){
                game_place(board, i, Comp);
                game_find_human_move_basic(board, &dc, &response);
                game_unplace(board, i);
                if(response > *value){
                    *value = response;
                    *bestp = i;
                }
            }
        }
    }
}

void game_find_human_move_basic(Board *board, int *bestp, int *value){
    int dc, response;
    if(game_board_is_full(board))
        *value = Draw;
    else if(game_immiediate_human_win(board, bestp))
        *value = Loss;
    else{
        *value = Win;
        int n = board->n;
        for (int i = 0; i < n * n; ++i) {
            if(game_board_is_empty(board, i)){
                game_place(board, i, Human);
                game_find_comp_move_basic(board, &dc, &response);
                game_unplace(board, i);
                if(response < *value){
                    *value = response;
                    *bestp = i;
                }
            }
        }
    }
}

// alpha = -1, beta = 1
void game_find_comp_move(Board *board, int *bestp, int *value, int alpha, int beta){
    int dc, response;
    if(game_board_is_full(board))
        *value = Draw;
    else if(game_immiediate_comp_win(board, bestp))
        *value = Win;
    else{
        *value = alpha;
        int n = board->n;
        for (int i = 0; i < n * n && *value < beta; ++i) {
            if(game_board_is_empty(board, i)){
                game_place(board, i, Comp);
                game_find_human_move(board, &dc, &response, *value, beta);
                game_unplace(board, i);
                if(response > *value){
                    *value = response;
                    *bestp = i;
                }
            }
        }
    }
}

void game_find_human_move(Board *board, int *bestp, int *value, int alpha, int beta){
    int dc, response;
    if(game_board_is_full(board))
        *value = Draw;
    else if(game_immiediate_human_win(board, bestp))
        *value = Loss;
    else{
        *value = beta;
        int n = board->n;
        for (int i = 0; i < n * n && *value > alpha; ++i) {
            if(game_board_is_empty(board, i)){
                game_place(board, i, Human);
                game_find_comp_move(board, &dc, &response, alpha, *value);
                game_unplace(board, i);
                if(response < *value){
                    *value = response;
                    *bestp = i;
                }
            }
        }
    }
}

void game_clear(Board *board){
    if(board == NULL)
        return;
    free(board->grids);
    free(board);
}

