#ifndef GRAPHICS_STARTER_DICEROLLER_H
#define GRAPHICS_STARTER_DICEROLLER_H


class diceRoller {
private:

    int value;
    int modifier;

public:

    static int d4(int mod);
    static int d6(int mod);
    static int d8(int mod);
    static int d12(int mod);
    static int d20(int mod);


};


#endif //GRAPHICS_STARTER_DICEROLLER_H
