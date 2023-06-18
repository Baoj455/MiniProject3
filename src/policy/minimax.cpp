#include <cstdlib>
#include <bits/stdc++.h>
#include "../state/state.hpp"
#include "./minimax.hpp"
#define max(a, b) a > b ? a : b
#define min(a, b) a < b ? a : b

Move tmp_move;
int Minimax::miniMax(State* state, int depth, int player){
    int value;
    state->get_legal_actions();
    auto actions = state->legal_actions;
    if(depth == 0 || !state->legal_actions.size())
        return state->evaluate(state);
    if(!player){
        value = -INT_MAX;
        for(auto &it : actions){
            value = max(value, miniMax(state->next_state(it), depth - 1, 1));
        }
        return value;
    }
    else{
        value = INT_MAX;
        for(auto &it : actions){
            value = min(value, miniMax(state->next_state(it), depth - 1, 0));
        }
        return value;
    }
}
Move Minimax::get_move(State *state, int depth){
    Move move;
    int min = INT_MIN;
    if(!state->legal_actions.size())
        state->get_legal_actions();
    auto actions = state->legal_actions;
    
    for(auto &it : actions){
        int value = miniMax(state, depth, 0);
        if(value > min){
            min = value;
            move = it;
        }
    }
    return move;
}