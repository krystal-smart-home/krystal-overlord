#pragma once

#include <concepts>
#include <iostream>
#include <memory>
#include <type_traits>
#include <vector>

#include "Service.h"
#include "Thread.h"

namespace krystal::core {

// clang-format off
template <typename Thread = krystal::core::Thread> requires std::derived_from<Thread, IThread> 
class ServiceManager {
    // clang-format on

public:
    ServiceManager()
        : m_isRunning(true) {
    }

    void registerService(std::shared_ptr<Service> service) {
        m_services.push_back(service);
    }

    int getServicesCount() const {
        return m_services.size();
    }

    void start() {
        for (auto& service : m_services)
            service->start();

        m_threads.reserve(m_services.size());
        for (auto& service : m_services)
            m_threads.emplace_back(Thread{ &ServiceManager::threadWorker, this, service });

        for (auto& thread : m_threads)
            thread.join();

        for (auto& service : m_services)
            service->stop();
    }

private:
    void threadWorker(std::shared_ptr<Service>& service) {
        while (m_isRunning) {
            service->update(m_isRunning);
        }
    }

    std::atomic_bool m_isRunning;
    std::vector<std::shared_ptr<Service>> m_services;
    std::vector<Thread> m_threads;
};
}
