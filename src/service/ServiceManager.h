#pragma once

#include <vector>

#include "Service.h"
#include "ServiceThread.h"
#include "core/Log.h"

namespace krystal::service {

class ServiceManager {
public:
    explicit ServiceManager(std::shared_ptr<ServiceThread::Factory> serviceThreadFactory);

    void addService(std::shared_ptr<Service> service);
    void start();

private:
    void startServices();
    void startThreads();
    void waitForThreads();
    void shutdownServices();

    std::shared_ptr<ServiceThread::Factory> m_serviceThreadFactory;

    std::vector<std::shared_ptr<Service>> m_services;
    std::vector<std::unique_ptr<ServiceThread>> m_threads;
};

}