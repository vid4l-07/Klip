#include "layout.h"
#include "ui/rect.h"

Rect Layout::centered_rect(Rect screen, int width, int height){
	return {
		(screen.width  - width)  / 2,
        (screen.height - height) / 2,
        width,
        height
	};
}

