#ifndef BASEACTION_H
#define BASEACTION_H

#include "DefaultConstants.h"

// class BaseAction {
// public:
//     virtual ~BaseAction() = default;
//     virtual void Execute() = 0;
//     virtual void getAction() = 0;
// };

// class ClickAction : public BaseAction{
// public:
//     ClickAction(ClickMode mode, int x, int y) : mode(mode), x(x), y(y) {}
//     void Execute() override {
//         switch (mode) {
//         case ClickMode::LEFT: std::cout << "Click Left\n"; break;
//         case ClickMode::RIGHT: std::cout << "Click Right\n"; break;
//         case ClickMode::WHEELUP: std::cout << "Click Wheel\n"; break;
//         case ClickMode::MOVE: std::cout << "Move Mouse to (" << x << ", " << y << ")\n"; break;
//         }
//     }
// private:
//     ClickMode mode;
//     int x, y;
// }

#endif // BASEACTION_H
