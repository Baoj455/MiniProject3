#include <cstdlib>
#include <bits/stdc++.h>
#include "../state/state.hpp"
#include "./minimax.hpp"


int Minimax::miniMax(State* state, int depth, int cur_player){
    
    if(depth == 0)
        return state->evaluate(cur_player);
    int value;
    state->get_legal_actions();
    auto actions = state->legal_actions;
    if(state->player==cur_player){
        value = INT_MIN;
        for(auto &it : actions){
            value = std::max(value, miniMax(state->next_state(it), depth - 1, cur_player));
        }
        return value;
    }
    else{
        value = INT_MAX;
        for(auto &it : actions){
            value = std::min(value, miniMax(state->next_state(it), depth - 1, cur_player));
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