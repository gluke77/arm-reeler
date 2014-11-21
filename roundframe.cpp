#include "roundframe.h"
#include "lcd.h"

void RoundFrame::draw()
{
	if (_visible)
		lcd_draw_round_rect(_left, _top, _rite, _bottom, _width, 2);
	else
		lcd_fill_round_rect(_left, _top, _rite, _bottom, 0x00, 2);
}
