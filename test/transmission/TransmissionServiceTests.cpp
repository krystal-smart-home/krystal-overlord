#include "transmission/TransmissionService.hpp"

#include <gtest/gtest.h>

#include "mocks/EventProviderWrapper.hpp"
#include "mocks/TcpSocketMock.hpp"

using namespace krystal;
using namespace krystal::transmission;
using namespace testing;

namespace {

class TransmissionServiceStartStopTests : public Test {
public:
    EventProviderWrapper m_eventProviderWrapper;
    std::shared_ptr<TcpSocketFactoryMock> m_socketFactory = std::make_shared<TcpSocketFactoryMock>();
};

TEST_F(TransmissionServiceStartStopTests, whenCreatingService_shouldCreateSocket) {
    EXPECT_CALL(*m_socketFactory, create(_)).Times(1);

    TransmissionService{ m_socketFactory };
}

TEST_F(TransmissionServiceStartStopTests, whenStartingService_shouldBindAndListenSocket) {
    EXPECT_CALL(*m_socketFactory, create(_)).Times(1).WillOnce(Return(m_socketFactory->socketMock));
    EXPECT_CALL(*m_socketFactory->socketMock, bind()).Times(1);
    EXPECT_CALL(*m_socketFactory->socketMock, listen(_)).Times(1);

    TransmissionService{ m_socketFactory }.start();
}

TEST_F(TransmissionServiceStartStopTests, whenStoppingService_shouldCloseSocket) {
    EXPECT_CALL(*m_socketFactory, create(_)).Times(1).WillOnce(Return(m_socketFactory->socketMock));
    EXPECT_CALL(*m_socketFactory->socketMock, close()).Times(1);

    TransmissionService{ m_socketFactory }.stop();
}
}
