#pragma once

#include <queue>
#include <string>

#include "ControllerModel.h"

namespace krystal::device {

class Controller {
public:
    explicit Controller(const std::string& name)
        : m_model(name, generateId()) {
    }

    ~Controller() {
        s_freeIds.push(m_model.id);
    }

    int getId() const {
        return m_model.id;
    }

    std::string getName() const {
        return m_model.name;
    }

private:
    ControllerModel m_model;

    static int generateId() {
        static int lastFreeId = 0;

        if (s_freeIds.size() != 0) {
            auto id = s_freeIds.front();
            s_freeIds.pop();
            return id;
        }

        return lastFreeId++;
    }

    inline static std::queue<int> s_freeIds;
};
}
