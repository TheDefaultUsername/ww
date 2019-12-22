#ifndef KEYPRESS_H
#define KEYPRESS_H

#include <QKeyEvent>

class _KeysPressed {
public:
    _KeysPressed(): key({0,0}) {}
    bool Inventory() {return key.named._Inventory;}
    bool Right() {return key.named._Right;}
    bool Left() {return key.named._Left;}
    bool Up() {return key.named._Up;}
    bool Down() {return key.named._Down;}
    bool Jump() {return key.named._Jump;}
    bool Use() {return key.named._Use;}
    bool Esc() {return key.named._Esc;}
    void sInventory(bool c) {key.named._Inventory=c;}
    void sRight(bool c) {key.named._Right=c;}
    void sLeft(bool c) {key.named._Left=c;}
    void sUp(bool c) {key.named._Up=c;}
    void sDown(bool c) {key.named._Down=c;}
    void sJump(bool c) {key.named._Jump=c;}
    void sUse(bool c) {key.named._Use=c;}
    void sEsc(bool c) {key.named._Esc=c;}
public:
    union {
        int unparsed[2];
        struct {
            bool _Inventory;
            bool _Right;
            bool _Left;
            bool _Up;
            bool _Down;
            bool _Jump;
            bool _Use;
            bool _Esc;
        } named;
    } key;
};

class _Keys{
public:
    _Keys() {}
    int Inventory;
    int Right;
    int Left;
    int Up;
    int Down;
    int Jump;
    int Use;
    int Esc;
};

#endif // KEYPRESS_H
