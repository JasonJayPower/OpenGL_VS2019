#pragma once

#include "Types.h"

enum class EventType {
	None = 0,
	KeyPressed, KeyReleased,
	MouseButtonPressed, MouseButtonReleased, MouseMoved
};

struct Event {
	EventType eventType;
	union {
		struct {
			s32 width;
			s32 height;
		} size;
		struct {
			s32 x;
			s32 y;
		} position;
		struct {
			s32 button;
			s32 mods;
		} mouse;
		struct {
			s32 key;
			s32 mods;
		} keyboard;
	};
};