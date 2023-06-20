#include <cstdlib>
#include <bits/stdc++.h>
#include "../state/state.hpp"
#include "./alphabeta.hpp"
#define max(a, b) a > b ? a : b
#define min(a, b) a < b ? a : b

int Alphabeta::alphaBeta(State* state, int depth, int a, int b, int init_player){
    int value;
    if(depth == 0||!state->legal_actions.size())
        return state->evaluate(init_player);

    state->get_legal_actions();
    auto actions = state->legal_actions;
    if(state->player == init_player){
        value = INT_MIN;
        for(auto &it : actions){
            value = max(value, alphaBeta(state->next_state(it), depth - 1, a, b, init_player));
            a = max(a, value);
            if(a >= b)
                break;
        }
        return value;
    }
    else{
        value = INT_MAX;
        for(auto &it : actions){
            value = min(value, alphaBeta(state->next_state(it), depth - 1, a, b, init_player));
            b = min(b, value);
            if(b <= a)
                break;
        }
        return value;
    }
}
Move Alphabeta::get_move(State *state, int depth){
    Move next_move;
    int max = INT_MIN;
    if(!state->legal_actions.size())
        state->get_legal_actions();
    auto actions = state->legal_actions;
    int value;
    for(auto& it : actions){
        value = alphaBeta(state->next_state(it), depth - 1, INT_MIN, INT_MAX, state->player);
        if(value > max){
            max = value;
            next_move = it;
        }
    }
    return next_move;
}