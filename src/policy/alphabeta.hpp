#pragma once
#include "../state/state.hpp"


class Alphabeta{
public:
  static Move get_move(State *state, int depth);
  static int alphaBeta(State *state, int depth, int a, int b, int cur_player);
};