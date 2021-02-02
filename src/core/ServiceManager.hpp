#pragma once

#include <concepts>
#include <iostream>
#include <memory>
#include <type_traits>
#include <vector>

#include <xvent/EventEngine.h>

#include "Logger.h"
#include "Service.h"
#include "Thread.h"

namespace krystal::core {

// clang-format off
template <typename Thread = krystal::core::Thread> requires std::derived_from<Thread, IThread> 
class ServiceManager {
    // clang-format on

public:
    explicit ServiceManager() {
    }

    void registerService(std::shared_ptr<Service> service) {
        // TODO: check if name doesn't already exist in map
        auto serviceName = service->getName();

        service->setEventEmitter(m_eventEngine.createEmitter());

        m_services[serviceName] = service;
        m_eventEngine.registerEventListener(service);
        KRYSTAL_INFO("Service {} registered", serviceName);
    }

    int getServicesCount() const {
        return m_services.size();
    }

    void start() {
        for (auto& [name, service] : m_services) {
            KRYSTAL_INFO("Service {} starting", name);
            service->start();
            KRYSTAL_INFO("Service {} started", name);
        }

        m_threads.reserve(m_services.size());
        for (auto& [name, service] : m_services) {
            KRYSTAL_INFO("Creating thread for service {}", name);
            m_threads.emplace_back(Thread{ &ServiceManager::threadWorker, this, service });
        }

        KRYSTAL_INFO("All service threads created and started");
        for (auto& thread : m_threads)
            thread.join();

        for (auto& [name, service] : m_services) {
            KRYSTAL_INFO("Service {} stopping", name);
            service->stop();
            KRYSTAL_INFO("Service {} stopped", name);
        }
    }

private:
    void threadWorker(std::shared_ptr<Service> service) {
        while (true) {
            auto serviceName = service->getName();
            auto eventProvider = m_eventEngine.getEventProvider(serviceName);

            if (auto state = service->update(eventProvider); state != ServiceState::active)
                break;
        }
    }

    xvent::EventEngine m_eventEngine;

    std::unordered_map<std::string, std::shared_ptr<Service>> m_services;
    std::vector<Thread> m_threads;
};
}
