#pragma once

namespace krystal::core {

class Service {
public:
    virtual void update() = 0;

    virtual void onStart() = 0;
    virtual void onStop() = 0;
};
}
