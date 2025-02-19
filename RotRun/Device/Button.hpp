#ifndef ___BUTTON__CLASS
#define ___BUTTON__CLASS

extern "C" {

#include "spike/hub/button.h"

}

/* ボタン */
class Button {
public:
    Button()
    {
        ;
    }

    bool isLeftPressed();
    bool isCenterPressed();
    bool isRightPressed();
    bool isBluetoothPressed();
};

#endif // ___BUTTON__CLASS
