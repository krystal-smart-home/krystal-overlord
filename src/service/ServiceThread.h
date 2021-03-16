#pragma once

#include <memory>
#include <thread>

#include "Service.h"

namespace krystal::service {

class ServiceThread {
    struct ThreadWorker {
        void operator()() {
            m_service->run();
        }

        std::shared_ptr<Service> m_service;
    };

public:
    struct Factory {
        virtual std::unique_ptr<ServiceThread> create(std::shared_ptr<Service> service) {
            return std::make_unique<ServiceThread>(service);
        }
    };

    explicit ServiceThread(std::shared_ptr<Service> service)
        : m_thread(ThreadWorker { service }) {
    }

    virtual void join() {
        m_thread.join();
    }

private:
    std::thread m_thread;
};

}