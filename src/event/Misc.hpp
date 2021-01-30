#pragma once

#include <xvent/Event.h>

#define DECLARE_EVENT(Event) struct Event : xvent::EventBase<Event>

