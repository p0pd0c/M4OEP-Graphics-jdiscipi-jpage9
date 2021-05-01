#include "diceRoller.h"
#include "iostream"
#include "random"
#include <ctime>
#include <cstdlib>

int DiceRoller::d4(int mod) {
    return rand() % 4 + 1 + mod;
}

int DiceRoller::d6(int mod) {
    return rand() % 6 + 1 + mod;
}

int DiceRoller::d8(int mod) {
    return rand() % 8 + 1 + mod;
}

int DiceRoller::d12(int mod) {
    return rand() % 12 + 1 + mod;
}

int DiceRoller::d20(int mod) {
    return rand() % 20 + 1 + mod;
}

