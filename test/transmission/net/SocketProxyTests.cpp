#include "transmission/net/SocketProxy.h"

#include <gtest/gtest.h>

#include "mocks/TcpSocketMock.hpp"

using namespace krystal;
using namespace krystal::transmission;
using namespace testing;

namespace {

class SocketProxyTests : public Test {
public:
    void SetUp() override {
        m_mock = std::make_shared<TcpSocketMock>();
        m_proxy = std::make_shared<SocketProxy>(m_mock);
    }

    std::shared_ptr<TcpSocketMock> m_mock;
    std::shared_ptr<SocketProxy> m_proxy;
};

TEST_F(SocketProxyTests, givenBindCall_whenSocketReturnNegative_shouldThrow) {
    EXPECT_CALL(*m_mock, bind()).Times(1).WillOnce(Return(-1));

    EXPECT_THROW(m_proxy->bind(), core::NetError);
}

TEST_F(SocketProxyTests, givenBindCall_whenSocketReturnZero_shouldForwardValue) {
    EXPECT_CALL(*m_mock, bind()).Times(1).WillOnce(Return(0));

    EXPECT_EQ(m_proxy->bind(), 0);
}

TEST_F(SocketProxyTests, givenListenCall_whenSocketReturnNegative_shouldThrow) {
    EXPECT_CALL(*m_mock, listen(_)).Times(1).WillOnce(Return(-1));

    EXPECT_THROW(m_proxy->listen(), core::NetError);
}

TEST_F(SocketProxyTests, givenListenCall_whenSocketReturnZero_shouldForwardValue) {
    EXPECT_CALL(*m_mock, listen(_)).Times(1).WillOnce(Return(0));

    EXPECT_EQ(m_proxy->listen(), 0);
}

TEST_F(SocketProxyTests, givenAcceptCall_whenSocketReturnNullptr_shouldThrow) {
    EXPECT_CALL(*m_mock, accept()).Times(1).WillOnce(Return(nullptr));

    EXPECT_THROW(m_proxy->accept(), core::NetError);
}

TEST_F(SocketProxyTests, givenAcceptCall_whenSocketReturnSocket_shouldForwardValue) {
    auto sock = std::make_shared<TcpSocketMock>();
    EXPECT_CALL(*m_mock, accept()).Times(1).WillOnce(Return(sock));

    EXPECT_EQ(m_proxy->accept(), sock);
}

TEST_F(SocketProxyTests, givenSendCall_whenSocketReturnDifferentBytesAmountThanExpected_shouldThrow) {
    auto expectedBytes = 512;
    std::string buffer(expectedBytes, 'x');

    EXPECT_CALL(*m_mock, send(_)).Times(1).WillOnce(Return(expectedBytes - 1));

    EXPECT_THROW(m_proxy->send(buffer), core::NetError);
}

TEST_F(SocketProxyTests, givenSendCall_whenSocketReturnExpectedBytesAmount_shouldForwardValue) {
    auto expectedBytes = 512;
    std::string buffer(expectedBytes, 'x');

    EXPECT_CALL(*m_mock, send(_)).Times(1).WillOnce(Return(expectedBytes));

    EXPECT_EQ(m_proxy->send(buffer), expectedBytes);
}

TEST_F(SocketProxyTests, givenReceiveCall_whenSocketReturnDifferentBytesAmountThanExpected_shouldThrow) {
    auto expectedBytes = 512;
    std::string buffer(expectedBytes, 'x');
    EXPECT_CALL(*m_mock, receive(_)).Times(1).WillOnce(Return(std::make_pair(buffer, expectedBytes - 1)));

    EXPECT_THROW(m_proxy->receive(expectedBytes), core::NetError);
}

TEST_F(SocketProxyTests, givenReceiveCall_whenSocketReturnExpectedBytesAmount_shouldForwardValue) {
    auto expectedBytes = 512;
    std::string buffer(expectedBytes, 'x');

    EXPECT_CALL(*m_mock, receive(_)).Times(1).WillOnce(Return(std::make_pair(buffer, expectedBytes)));

    auto [recvBuffer, recvBytes] = m_proxy->receive(expectedBytes);
    EXPECT_EQ(recvBuffer, buffer);
    EXPECT_EQ(recvBytes, expectedBytes);
}

TEST_F(SocketProxyTests, givenCloseCall_shouldCallSocket) {
    EXPECT_CALL(*m_mock, close()).Times(1);

    m_proxy->close();
}
}
