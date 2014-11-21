#ifndef _LCD_H_INCLUDED
#define _LCD_H_INCLUDED

#include "common.h"

#ifdef __cplusplus__
extern "C" {
#endif /* __cplusplus__ */

// For Yurka's board swap a0 and cs
// bus p0.16-p0.23
// a0 - p0.25
// cs - p0.24
// rd - p0.2
// wr - p0.3
// rst - p0.5

#define LCD_BUS_DIR   (IO0DIR)
#define LCD_BUS_SET   (IO0SET)
#define LCD_BUS_CLR   (IO0CLR)
#define LCD_BUS_PIN   (IO0PIN)

#define LCD_BUS_SHIFT (16)
#define LCD_BUS_MASK  (0x00FF0000)

#define LCD_BUS_INIT  (PINSEL1 &= ~0x0000FFFF)

#define LCD_BUS_WRITE (LCD_BUS_DIR |= LCD_BUS_MASK)
#define LCD_BUS_READ  (LCD_BUS_DIR &= ~LCD_BUS_MASK)

#define LCD_BUS_GET_DATA        ((char)((LCD_BUS_PIN & LCD_BUS_MASK) >> LCD_BUS_SHIFT))
#define LCD_BUS_SET_DATA(byte)  { LCD_BUS_SET = (((int)(byte)) << LCD_BUS_SHIFT) & LCD_BUS_MASK; LCD_BUS_CLR = (~(((int)(byte)) << LCD_BUS_SHIFT)) & LCD_BUS_MASK; }

//#define LCD_BUS_GET_DATA		lcd_bus_get_data()
//#define LCD_BUS_SET_DATA(ch)	lcd_bus_set_data(ch)

#define LCD_A_DIR     (IO0DIR)
#define LCD_A_SET     (IO0SET)
#define LCD_A_CLR     (IO0CLR)
#define LCD_A_PIN     (IO0PIN)

#define LCD_A_BIT     (25)

#define LCD_A_INIT    {PINSEL1 &= ~0x000C0000; LCD_A_DIR |= (1L << LCD_A_BIT);}

#define LCD_SET_A     (LCD_A_SET = (1L << LCD_A_BIT))
#define LCD_CLEAR_A   (LCD_A_CLR = (1L << LCD_A_BIT))

#define LCD_CS_DIR     (IO0DIR)
#define LCD_CS_SET     (IO0SET)
#define LCD_CS_CLR     (IO0CLR)
#define LCD_CS_PIN     (IO0PIN)

#define LCD_CS_BIT     (24)

#define LCD_CS_INIT    {PINSEL1 &= ~0x000030000; LCD_CS_DIR |= (1L << LCD_CS_BIT);}

#define LCD_SET_CS     (LCD_CS_SET = (1L << LCD_CS_BIT))
#define LCD_CLEAR_CS   (LCD_CS_CLR = (1L << LCD_CS_BIT))

#define LCD_RD_DIR     (IO0DIR)
#define LCD_RD_SET     (IO0SET)
#define LCD_RD_CLR     (IO0CLR)
#define LCD_RD_PIN     (IO0PIN)

#define LCD_RD_BIT     (2)

#define LCD_RD_INIT    {PINSEL0 &= ~0x00000030; LCD_RD_DIR |= (1L << LCD_RD_BIT);}

#define LCD_SET_RD     (LCD_RD_SET = (1L << LCD_RD_BIT))
#define LCD_CLEAR_RD   (LCD_RD_CLR = (1L << LCD_RD_BIT))

#define LCD_WR_DIR     (IO0DIR)
#define LCD_WR_SET     (IO0SET)
#define LCD_WR_CLR     (IO0CLR)
#define LCD_WR_PIN     (IO0PIN)

#define LCD_WR_BIT     (3)

#define LCD_WR_INIT    {PINSEL0 &= ~0x000000C0; LCD_WR_DIR |= (1L << LCD_WR_BIT);}

#define LCD_SET_WR     (LCD_WR_SET = (1L << LCD_WR_BIT))
#define LCD_CLEAR_WR   (LCD_WR_CLR = (1L << LCD_WR_BIT))

#define LCD_RESET_DIR     (IO0DIR)
#define LCD_RESET_SET     (IO0SET)
#define LCD_RESET_CLR     (IO0CLR)
#define LCD_RESET_PIN     (IO0PIN)

#define LCD_RESET_BIT     (5)

#define LCD_RESET_INIT    {PINSEL0 &= ~0x00000C00; LCD_RESET_DIR |= (1L << LCD_RESET_BIT);}

#define LCD_SET_RESET     (LCD_RESET_SET = (1L << LCD_RESET_BIT))
#define LCD_CLEAR_RESET   (LCD_RESET_CLR = (1L << LCD_RESET_BIT))

void lcd_init(void);

void lcd_clear_cgram(void);
void lcd_load_font(void);

void lcd_fill_text(char);

void lcd_write_data_intel(char ch);
void lcd_write_cmd_intel(char ch);
char lcd_read_intel(void);

void lcd_write_data_m68k(char ch);
void lcd_write_cmd_m68k(char ch);
char lcd_read_m68k(void);

void lcd_write_data_m6800(char ch);
void lcd_write_cmd_m6800(char ch);
char lcd_read_m6800(void);

void lcd_write_data(char ch);
void lcd_write_cmd(char ch);
char lcd_read(void);

void lcd_fill_graph(char, int);
void lcd_plot(int, int, int);
void lcd_line(int, int, int, int, int);
void lcd_frame(int, int, int, int, int);
void lcd_hor_line(int, int, int, char, int);
void lcd_fill_rect(int, int, int, int, char, int);
void lcd_fill_graph(char /* byte */, int layer);

void lcd_draw_round_rect(int /* left */, int /* top */, int /* rite */, int /* bottom */, int /* width */, int /* layer */);
void lcd_fill_round_rect(int /* left */, int /* top */, int /* rite */, int /* bottom */, char /* brush */, int /* layer */);

void lcd_set_layer(int, int);

void lcd_set_cursor(int);
void lcd_set_text_cursor(int, int);
int lcd_get_cursor(void);
void lcd_puts(char *);

//void lcd_bus_set_data(char);
//char lcd_bus_get_data(void);

#define CSRW    	(0x46)
#define CSRR    	(0x47)
#define MWRITE  	(0x42)
#define MREAD   	(0x43)
#define SYSTEM_SET	(0x40)
#define DISPLAY_OFF	(0x58)
#define DISPLAY_ON	(0x59)
#define SCROLL		(0x44)
#define CSRFORM		(0x5d)
#define CSR_RIGHT	(0x4c)
#define CSR_LEFT	(0x4d)
#define CSR_UP		(0x4e)
#define CSR_DOWN	(0x4f)
#define OVLAY		(0x5b)
#define CGRAM_ADDR	(0x5c)
#define HDOT_SCR	(0x5a)
#define	GRAYSCALE	(0x60)

#define LCD_FB_OFFSET		(0x2000)

#define LCD_TEXT_OFFSET		(LCD_FB_OFFSET)
#define LCD_TEXT_SIZE		(1200)

#define LCD_GRAPH1_OFFSET	(LCD_TEXT_OFFSET)
#define LCD_GRAPH1_SIZE		(9600)

#define LCD_GRAPH2_OFFSET	(LCD_GRAPH1_OFFSET + LCD_GRAPH1_SIZE)
#define LCD_GRAPH2_SIZE		(9600)

#define LCD_GRAPH_OFFSET	(LCD_GRAPH2_OFFSET)
#define LCD_GRAPH_SIZE		(LCD_GRAPH2_SIZE)

#define LCD_GRAPH3_OFFSET	(LCD_GRAPH2_OFFSET + LCD_GRAPH2_SIZE)
#define LCD_GRAPH3_SIZE		(9600)

#define LCD_BYTES_PER_LINE	(40)
#define LCD_VERTICAL_LINES	(240)

#define LCD_CGRAM_OFFSET		(0x0000)
#define LCD_CGRAM_CHAR_BASE		(LCD_CGRAM_OFFSET)

#define LCD_LAYER_OFF			(0)
#define LCD_LAYER_ON			(1)
#define LCD_LAYER_SLOW_BLINK	(2)
#define LCD_LAYER_FAST_BLINK	(3)

#ifdef __cplusplus__
}
#endif /* __cplusplus__ */

#endif /* _LCD_H_INCLUDED */
