#include "common.h"
#include "rtc.h"
#include "lcd.h"
#include "timer.h"

#define _LCD_M6800

void lcd_write_cmd(char ch)
{
#ifdef _LCD_M6800
  lcd_write_cmd_m6800(ch);
#endif /* _LCD_M6800 */

#ifdef _LCD_M68K
  lcd_write_cmd_m68k(ch);
#endif /* _LCD_M68K */

#ifdef _LCD_INTEL
  lcd_write_cmd_intel(ch);
#endif /* _LCD_INTEL */
}

void lcd_write_data(char ch)
{
#ifdef _LCD_M6800
  lcd_write_data_m6800(ch);
#endif /* _LCD_M6800 */

#ifdef _LCD_M68K
  lcd_write_data_m68k(ch);
#endif /* _LCD_M68K */

#ifdef _LCD_INTEL
  lcd_write_data_intel(ch);
#endif /* _LCD_INTEL */
}

char lcd_read(void)
{
#ifdef _LCD_M6800
  return lcd_read_m6800();
#endif /* _LCD_M6800 */

#ifdef _LCD_M68K
  return lcd_read_m68k();
#endif /* _LCD_M68K */

#ifdef _LCD_INTEL
  return lcd_read_intel();
#endif /* _LCD_INTEL */
}

/*
void lcd_write_cmd_intel(char ch)
{
  LCD_SET_RD;
  LCD_SET_WR;
  LCD_SET_A;
  LCD_BUS_SET_DATA(ch);
  LCD_CLEAR_CS;
  LCD_CLEAR_WR;
  _delay_us(1);
  LCD_SET_WR;
  LCD_SET_CS;
}

void lcd_write_data_intel(char ch)
{
  LCD_SET_RD;
  LCD_SET_WR;
  LCD_CLEAR_A;
  LCD_BUS_SET_DATA(ch);
  LCD_CLEAR_CS;
  LCD_CLEAR_WR;
  _delay_us(1);
  LCD_SET_WR;
  LCD_SET_CS;
}

char lcd_read_intel(void)
{
  char  ch;

  LCD_BUS_READ;
  LCD_SET_RD;
  LCD_SET_WR;
  LCD_SET_A;
  LCD_CLEAR_CS;
  LCD_CLEAR_RD;
  _delay_us(1);
  ch = LCD_BUS_GET_DATA;
  LCD_SET_RD;
  LCD_SET_CS;
  
  LCD_BUS_WRITE;

  return ch;
}

*/
void lcd_write_cmd_m6800(char ch)
{
  _delay_us(5);
  LCD_CLEAR_RD;
  LCD_SET_A;
  LCD_CLEAR_WR;
  LCD_CLEAR_CS;
  LCD_BUS_SET_DATA(ch);
  LCD_SET_RD;
  _delay_us(1);
  LCD_CLEAR_RD;
  LCD_SET_CS;
}

void lcd_write_data_m6800(char ch)
{
  _delay_us(1);
  LCD_CLEAR_RD;
  LCD_CLEAR_CS;
  LCD_CLEAR_A;
  LCD_CLEAR_WR;
  LCD_BUS_SET_DATA(ch);
//  _delay_us(10);
  LCD_SET_RD;
  _delay_us(1);
  LCD_CLEAR_RD;
  LCD_SET_CS;
}

char lcd_read_m6800(void)
{
  char  ch;

  _delay_us(5);
  LCD_BUS_READ;
  LCD_CLEAR_RD;
  LCD_CLEAR_CS;
  LCD_SET_A;
  LCD_SET_WR;
  LCD_SET_RD;
  _delay_us(1);
  ch = LCD_BUS_GET_DATA;
  LCD_CLEAR_RD;
  LCD_SET_CS;
  LCD_BUS_WRITE;

  return ch;
}
/*
void lcd_write_cmd_m68k(char ch)
{
  LCD_SET_RD;
  LCD_SET_A;
  LCD_CLEAR_WR;
  LCD_CLEAR_CS;
  LCD_BUS_SET_DATA(ch);
  _delay_us(1);
  LCD_CLEAR_RD;
  _delay_us(1);
  LCD_SET_RD;
  LCD_SET_CS;
}

void lcd_write_data_m68k(char ch)
{
  LCD_SET_RD;
  LCD_CLEAR_CS;
  LCD_CLEAR_A;
  LCD_CLEAR_WR;
  LCD_BUS_SET_DATA(ch);
  _delay_us(1);
  LCD_CLEAR_RD;
  _delay_us(1);
  LCD_SET_RD;
  LCD_SET_CS;
}

char lcd_read_m68k(void)
{
  char  ch;

  LCD_BUS_READ;
  LCD_SET_RD;
  LCD_CLEAR_CS;
  LCD_SET_A;
  LCD_SET_WR;
  LCD_CLEAR_RD;
  _delay_us(1);
  ch = LCD_BUS_GET_DATA;
  LCD_SET_RD;
  LCD_SET_CS;
  
  LCD_BUS_WRITE;

  return ch;
}
*/

void lcd_init(void)
{
	LCD_BUS_INIT;
	LCD_BUS_WRITE;
	LCD_A_INIT;
	LCD_SET_A;
	LCD_CS_INIT;
	LCD_SET_CS;
	LCD_RD_INIT;
	LCD_SET_RD;
	LCD_WR_INIT;
	LCD_SET_WR;

	LCD_RESET_INIT;
  
	_delay_ms(2);
	LCD_SET_RESET;
	_delay_ms(5);
	LCD_CLEAR_RESET;
	_delay_ms(2);
	LCD_SET_RESET;
  
	lcd_write_cmd(SYSTEM_SET);
	lcd_write_data(0x35);	// 0 0 IV 1 W/S M2 0 M0 
							// IV = 0 - screen origin compensation on, 1 - off
							// W/S = 0 - single panel, 1 - dual panel
							// M2 = 0 - char height 8 px, 1 - 16 px
							// M0 = 0 - CGROM, 1 - CGRAM
	lcd_write_data(0x87);	// MOD 0 0 0 (FX-1)[3:0]
							// MOD = 0 - 16 line AC drive, 1 - 2 frame AC drive
	lcd_write_data(0x0F);   // 0 0 0 0 (FY-1)[3:0]
	lcd_write_data(LCD_BYTES_PER_LINE - 1);			// C/R*bpp-1 
	lcd_write_data(0x39);							// TC/R + 1, TC/R >= C/R + 2
	lcd_write_data(LCD_VERTICAL_LINES - 1);			// L/F-1
	lcd_write_data(LO_BYTE(LCD_BYTES_PER_LINE));	// AP lo
	lcd_write_data(HI_BYTE(LCD_BYTES_PER_LINE));	// AP hi

	lcd_write_cmd(SCROLL);
	lcd_write_data(LO_BYTE(LCD_TEXT_OFFSET)); 	// SAD1 lo
	lcd_write_data(HI_BYTE(LCD_TEXT_OFFSET));	// SAD1 hi
	lcd_write_data(LCD_VERTICAL_LINES - 1);		// SL1
	lcd_write_data(LO_BYTE(LCD_GRAPH2_OFFSET));	// SAD2 lo
	lcd_write_data(HI_BYTE(LCD_GRAPH2_OFFSET));	// SAD2 hi
	lcd_write_data(LCD_VERTICAL_LINES - 1);		// SL2
	lcd_write_data(LO_BYTE(LCD_GRAPH3_OFFSET));	// SAD3 lo
	lcd_write_data(HI_BYTE(LCD_GRAPH3_OFFSET));	// SAD3 hi
	lcd_write_data(0x00);	// SAD4 lo	
	lcd_write_data(0x00);	// SAD4 hi   

	lcd_write_cmd(CGRAM_ADDR);
	lcd_write_data(LO_BYTE(LCD_CGRAM_OFFSET));
	lcd_write_data(HI_BYTE(LCD_CGRAM_OFFSET));
	
	lcd_write_cmd(HDOT_SCR);
	lcd_write_data(0x00);	// 0 0 0 0 0 HDOT_SCR[2:0]
	
	lcd_write_cmd(OVLAY);
	lcd_write_data(0x01);	// 0 0 0 OV DM1 DM0 MX[1:0]   
							// OV = 0 - 2 layers, 1 - 3 layers
							// DM1 = 0 - screen block 3 text mode, 1 - graphic mode
							// DM0 = 0 - screen block 1 text mode, 1 - graphic mode
							// MX = 0 - L1 or L2 or L3, 1 - (L1 xor L2) or L3, 2 - (L1 and L2) or L3
							
	lcd_write_cmd(DISPLAY_ON);
	lcd_write_data(0x00);	// FP5 FP4 FP3 FP2 FP1 FP0 FC1 FC0
							// FP5-4 - SAD3, FP3-2 - SAD2, FP1-0 - SAD1, FC - cursor
							// 0 - off, 1 - on, 2 - slow blink, 3 - fast blink
 	
	lcd_write_cmd(CSRFORM);
	lcd_write_data(0x00);	// 0 0 0 0 (CRX-1)[3:0]
	lcd_write_data(0x00); 	// CM 0 0 0 (CRY-1)[3:0], CM = 0 - underscore, 1 - block
	
	lcd_write_cmd(CSR_RIGHT);
  
	lcd_write_cmd(CSRW);
	lcd_write_data(0x00);
	lcd_write_data(0x00);

//	lcd_clear_cgram();
	lcd_load_font();
  
}

void lcd_set_layer(int layer, int mode)
{
	static char display_mode = 0x00;

	layer &= 0x03;
	mode &= 0x03;

	CLEARBITS(display_mode, 0x03 << (layer << 1));
	SETBITS(display_mode, mode << (layer << 1));

	lcd_write_cmd(DISPLAY_ON);
	lcd_write_data(display_mode);
}

void lcd_fill_text(char ch)
{     
  int i;
  
  lcd_set_cursor(LCD_TEXT_OFFSET);
   
  lcd_write_cmd(MWRITE);
  for (i = 0; i < LCD_TEXT_SIZE; i++)
    lcd_write_data(ch);
}

//***********************************************
void lcd_plot(int x,int y, int layer)
{  
	char b; 
	char offset;          
	int a;

	a = y * 40 + x / 8;

	if (3 == layer)
  		a += LCD_GRAPH3_OFFSET;
	else if (2 == layer)
		a += LCD_GRAPH2_OFFSET;
	else 
		a += LCD_GRAPH1_OFFSET;


	offset = x - ((x / 8) * 8); 

	lcd_set_cursor(a);
	lcd_write_cmd(MREAD);
	b = lcd_read();
	b |= (0x80 >> offset);
	lcd_set_cursor(a);
	lcd_write_cmd(MWRITE);
	lcd_write_data(b); 
}          
 
//************************************************************************
void lcd_line(int startx, int starty, int endx, int endy, int layer)
{
   int t, distance;
   int xerr=0,yerr=0,delta_x,delta_y;
   int incx, incy;

   delta_x=endx-startx;
   delta_y=endy-starty;    

   if (delta_x>0) incx=1;
   else  if (delta_x==0) incx=0;
   else  incx= -1;
   if (delta_y>0) incy=1;
   else  if (delta_y==0) incy=0;
   else  incy= -1;
          
   if(delta_x<0) delta_x=-delta_x;
   if(delta_y<0) delta_y=-delta_y;
   if (delta_x>delta_y) distance=delta_x;
   else                 distance=delta_y;

   for (t=0; t<=distance+1; t++) 
   {
      lcd_plot(startx,starty, layer);
      xerr+=delta_x;
      yerr+=delta_y;
      if (xerr>distance)   {xerr-=distance; startx+=incx; }
      if (yerr>distance)   {yerr-=distance; starty+=incy; }
   }
} 
 
//***********************************************
void lcd_frame(int x0, int y0, int x1, int y1, int layer)
{    
   lcd_hor_line(x0,y0,x1, 0xFF, layer);
   lcd_line(x0,y0,x0,y1, layer);
   lcd_line(x1,y0,x1,y1, layer);
   lcd_hor_line(x0,y1,x1, 0xFF, layer);
}

//***********************************************
void lcd_fill_graph(char byte, int layer)
{                   
	int i;  
	int goffset;
	int gsize;
  
    if (3 == layer)
	{
		goffset = LCD_GRAPH3_OFFSET;
		gsize = LCD_GRAPH3_SIZE;
	}
	else if (2 == layer)
	{
		goffset = LCD_GRAPH2_OFFSET;
		gsize = LCD_GRAPH2_SIZE;
	}
  	else
	{
		goffset = LCD_GRAPH1_OFFSET;
		gsize = LCD_GRAPH1_SIZE;
	}

	lcd_set_cursor(goffset);
 	lcd_write_cmd(MWRITE);
	for (i = 0; i < gsize; i++)
		lcd_write_data(byte); 
}          

void lcd_hor_line(int left, int y, int rite, char byte, int layer)
{                   
	int i;
	int pos;
	int count;  
	int goffset;
	int left_bits;
	int rite_bits;
	char tmp_byte;
  
    if (3 == layer)
		goffset = LCD_GRAPH3_OFFSET;
	else if (2 == layer)
		goffset = LCD_GRAPH2_OFFSET;
  	else
		goffset = LCD_GRAPH1_OFFSET;

	pos = goffset + y * LCD_BYTES_PER_LINE + left / 8;
	count = rite / 8 - left / 8 + 1;
		
	left_bits = left & 0x07;		
	rite_bits = rite & 0x07;

	lcd_set_cursor(pos);
	lcd_write_cmd(MREAD);
	tmp_byte = lcd_read();

	if (count < 2)
	{
		for (i = 7 - left_bits; i >= 7 - rite_bits; i--)
			if (byte)
				SETBIT(tmp_byte, i);
			else
				CLEARBIT(tmp_byte, i);
	}
	else 
	{
		for (i = 7 - left_bits; i >= 0; i--)
			if (byte)
				SETBIT(tmp_byte, i);
			else
				CLEARBIT(tmp_byte, i);
	}
		
	lcd_set_cursor(pos);
	lcd_write_cmd(MWRITE);
	lcd_write_data(tmp_byte);
		
	for (i = 0; i < count - 2; i++)
		lcd_write_data(byte); 

	if (count < 2)
		return;

	lcd_set_cursor(pos + count - 1);
	lcd_write_cmd(MREAD);
	tmp_byte = lcd_read();
	
	for (i = 7; i > 7 - rite_bits; i--)
		if (byte)
			SETBIT(tmp_byte, i);
		else
			CLEARBIT(tmp_byte, i);
	lcd_set_cursor(pos + count - 1);
	lcd_write_cmd(MWRITE);
	lcd_write_data(tmp_byte);
}


void lcd_fill_rect(int left, int top, int rite, int bottom, char byte, int layer)
{                   
	int y;

	for (y = top; y <= bottom; y++)
		lcd_hor_line(left, y, rite, byte, layer);
}

void lcd_set_cursor(int pos)
{
  lcd_write_cmd(CSRW);
  lcd_write_data((char)(pos & 0x000000FF));
  lcd_write_data((char)((pos >> 8) & 0x000000FF));
}

int lcd_get_cursor()
{
	int	res;
	
	lcd_write_cmd(CSRR);
	
	res = lcd_read();
	res |= (lcd_read() << 8);

	return res;
}


void lcd_puts(char * ch)
{
//  lcd_set_cursor(0);
  lcd_write_cmd(MWRITE);
  while (*ch)
    lcd_write_data(*ch++);
}

void lcd_bus_set_data(char ch)
{
	int i;
	i = (int)ch;
	i <<= LCD_BUS_SHIFT;
	LCD_BUS_SET = i & LCD_BUS_MASK;
	LCD_BUS_CLR = (~i) & LCD_BUS_MASK;
}

char lcd_bus_get_data(void)
{
	int i;
	i = LCD_BUS_PIN;
	i &= LCD_BUS_MASK;
	i >>= LCD_BUS_SHIFT;

	return (char)i;
}

extern char font[256][16];

void lcd_load_font(void)
{
	int i, j;

	lcd_write_cmd(CSR_RIGHT);
	lcd_set_cursor(LCD_CGRAM_CHAR_BASE);
	lcd_write_cmd(MWRITE);

	for (i = 0; i < 256; i++)
		for (j = 0; j < 16; j++)
			lcd_write_data(font[i][j]);
}

void lcd_clear_cgram(void)
{
	int i;

	lcd_write_cmd(CSR_RIGHT);
	lcd_set_cursor(LCD_CGRAM_CHAR_BASE);
	lcd_write_cmd(MWRITE);

	for (i = 0; i < 256 * 16; i++)
		lcd_write_data(0x00);

}

void lcd_set_text_cursor(int x, int y)
{
	lcd_set_cursor(LCD_TEXT_OFFSET + y * LCD_BYTES_PER_LINE + x);
}

void lcd_draw_round_rect(int left, int top, int rite, int bottom, int width, int layer)
{
	int w, l, r, t, b;

	for (w = 0; w < width; w++)
	{
		l = left + w;
		t = top + w;
		r = rite - w;
		b = bottom - w;

		if ((r - l < 16) && (b - t < 16))
			lcd_frame(l, t, r, b, layer);
		else
		{
			lcd_hor_line(l + 2, t, r - 1, 0xFF, layer);
			lcd_hor_line(l + 2, b, r - 1, 0xFF, layer);
			lcd_line(l, t + 2, l, b - 2, layer);
			lcd_line(r, t + 2, r, b - 2, layer);
			lcd_plot(l + 1, t + 1, layer);
			lcd_plot(r - 1, t + 1, layer);
			lcd_plot(l + 1, b - 1, layer);
			lcd_plot(r - 1, b - 1, layer);
		}
	}
}

void lcd_fill_round_rect(int left, int top, int rite, int bottom, char brush, int layer)
{
	int	i;
	
	if ((rite - left < 16) && (bottom - top < 16))
		lcd_fill_rect(left, top, rite, bottom, brush, layer);
	else
	{
		lcd_hor_line(left + 2, top, rite - 2, brush, layer);
		lcd_hor_line(left + 2, bottom, rite - 2, brush, layer);
		lcd_hor_line(left + 1, top + 1, rite - 1, brush, layer);
		lcd_hor_line(left + 1, bottom -1, rite - 1, brush, layer);

		for (i = top + 2; i < bottom - 1; i++)
			lcd_hor_line(left, i, rite, brush, layer);
	}
}
