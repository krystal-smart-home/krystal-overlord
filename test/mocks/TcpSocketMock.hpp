#pragma once

#include <gmock/gmock.h>

#include "transmission/net/TcpSocket.h"

using namespace krystal::transmission::net;

struct TcpSocketMock : public ITcpSocket {
    MOCK_METHOD(int, bind, (), (override));
    MOCK_METHOD(int, listen, (int), (override));
    MOCK_METHOD(void, close, (), (override));
    MOCK_METHOD(std::shared_ptr<ITcpSocket>, accept, (), (override));
    MOCK_METHOD(int, send, (const std::string&), (override));
    MOCK_METHOD((std::pair<std::string, int>), receive, (uint16_t), (override));
};

struct TcpSocketFactoryMock : public ITcpSocket::Factory {
    MOCK_METHOD(std::shared_ptr<ITcpSocket>, create, (int), (override));

    std::shared_ptr<TcpSocketMock> socketMock = std::make_shared<TcpSocketMock>();
};
