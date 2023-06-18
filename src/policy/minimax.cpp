#include <cstdlib>
#include <bits/stdc++.h>
#include "../state/state.hpp"
#include "./minimax.hpp"
#define max(a, b) a > b ? a : b
#define min(a, b) a < b ? a : b

int Minimax::miniMax(State* state, int depth, int player){
    int value;
    state->get_legal_actions();
    auto actions = state->legal_actions;
    if(depth == 0 || !state->legal_actions.size())
        return state->evaluate();
    if(!player){
        value = INT_MIN;
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
    int max = INT_MIN;
    int min = INT_MAX;
    if(!state->legal_actions.size())
        state->get_legal_actions();
    auto actions = state->legal_actions;
    int player = state->player;
    
    for(auto &it : actions){
        int value = miniMax(state, depth, player);
        if(!player){
            if(value > max){
                max = value;
                move = it;
            }
        }
        else{
            if(value < min){
                min = value;
                move = it;
            }
        }
    }
    return move;
}