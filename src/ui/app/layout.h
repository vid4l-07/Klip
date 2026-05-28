#pragma once
#include "ui/rect.h"

class Layout {
	public:
	static Rect centered_rect(Rect screen, int width, int height);
	static void split_rect(const Rect org_rect, Rect& rect1, Rect& rect2);
};
