#include "ServiceManager.h"

namespace krystal::service {

ServiceManager::ServiceManager(std::shared_ptr<ServiceThread::Factory> serviceThreadFactory)
    : m_serviceThreadFactory(serviceThreadFactory) {
}

void ServiceManager::addService(std::shared_ptr<Service> service) {
    m_services.push_back(service);
    KRYSTAL_INFO("Service {} added.", service->getName());
}

void ServiceManager::start() {
    startServices();
    startThreads();
    waitForThreads();
    shutdownServices();
}

void ServiceManager::startServices() {
    for (auto& service : m_services) {
        auto name = service->getName();

        KRYSTAL_INFO("Initializing service {}.", name);
        service->onInit();
        KRYSTAL_INFO("Service {} initialized.", name);
    }
}

void ServiceManager::startThreads() {
    m_threads.reserve(m_services.size());

    for (auto& service : m_services) {
        m_threads.emplace_back(m_serviceThreadFactory->create(service));
        KRYSTAL_INFO("Service {} started in thread.", service->getName());
    }
}

void ServiceManager::waitForThreads() {
    KRYSTAL_INFO("Waiting for services to finish work.");
    for (auto& thread : m_threads)
        thread->join();
}

void ServiceManager::shutdownServices() {
    for (auto& service : m_services) {
        auto name = service->getName();

        KRYSTAL_INFO("Shutting down service {}.", name);
        service->onShutdown();
        KRYSTAL_INFO("Service {} shutted down.", name);
    }
}
}