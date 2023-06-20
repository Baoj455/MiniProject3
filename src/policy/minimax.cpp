#include <cstdlib>
#include <bits/stdc++.h>
#include "../state/state.hpp"
#include "./minimax.hpp"
#define max(a, b) a > b ? a : b
#define min(a, b) a < b ? a : b

int Minimax::miniMax(State* state, int depth, int init_player){
    
    if(depth == 0 || !state->legal_actions.size())
        return state->evaluate(init_player);
    int value;
    state->get_legal_actions();
    auto actions = state->legal_actions;
    if(state->player == init_player){
        value = INT_MIN;
        for(auto &it : actions){
            value = max(value, miniMax(state->next_state(it), depth - 1, init_player));
        }
        return value;
    }
    else{
        value = INT_MAX;
        for(auto &it : actions){
            value = min(value, miniMax(state->next_state(it), depth - 1, init_player));
        }
        return value;
    }
}
Move Minimax::get_move(State *state, int depth){
    Move next_move;
    int max = INT_MIN;
    if(!state->legal_actions.size())
        state->get_legal_actions();
    auto actions = state->legal_actions;
    int value;
    for(auto& it : actions){
        value = miniMax(state->next_state(it), depth - 1, state->player);
        if(value > max){
            max = value;
            next_move = it;
        }
    }
    return next_move;
}