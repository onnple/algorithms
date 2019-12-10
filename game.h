//
// Created by Once on 2019/12/9.
//

#ifndef ALGORITHMS_GAME_H
#define ALGORITHMS_GAME_H

typedef enum ptype{
    Loss, Draw, Win
} PType;

typedef enum role{
    Comp, Human, None
} Role;

typedef struct grid{
    int state;
    Role role;
} Grid;

typedef struct board{
    int n;
    Grid *grids;
} Board;

extern void game_start(void);
extern void game_show(Board *board);
extern Board *game_board_new(int n);
extern int game_board_is_empty(Board *board, int p);
extern int game_board_is_full(Board *board);
extern int game_immiediate_comp_win(Board *board, int *bestp);
extern int game_immiediate_human_win(Board *board, int *bestp);
extern int game_human_is_win(Board *board);
extern void game_place(Board *board, int p, Role role);
extern void game_unplace(Board *board, int p);
extern void game_find_comp_move_basic(Board *board, int *bestp, int *value);
extern void game_find_human_move_basic(Board *board, int *bestp, int *value);
extern void game_find_comp_move(Board *board, int *bestp, int *value, int alpha, int beta);
extern void game_find_human_move(Board *board, int *bestp, int *value, int alpha, int beta);
extern void game_clear(Board *board);

#endif //ALGORITHMS_GAME_H
