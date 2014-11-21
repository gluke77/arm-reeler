#include "roundbutton.h"

#include "roundbutton.h"
#include "lcd.h"

void RoundButton::draw()
{
	int i;
	int count;

	if (!_visible)
	{
		count = strlen(_text);
		
		lcd_fill_rect(_left, _top, _rite + 1, _bottom, 0x00, 2);
		//lcd_fill_round_rect(_left, _top, _rite + 1, _bottom, 0x00, 2);
		lcd_set_text_cursor(_x, _y);
		lcd_write_cmd(MWRITE);
		for (i = 0; i < count; i++)
			lcd_write_data(' ');
	}
	else
	{
		if (_pressed)
			lcd_fill_round_rect(_left, _top, _rite, _bottom, 0xFF, 2);
		else
		{
			lcd_fill_rect(_left, _top, _rite, _bottom, 0x00, 2);
			//lcd_fill_round_rect(_left, _top, _rite, _bottom, 0x00, 2);
			lcd_draw_round_rect(_left, _top, _rite, _bottom, 4, 2);
		}

		lcd_set_text_cursor(_x, _y);
		lcd_puts(_text);
	}
}
