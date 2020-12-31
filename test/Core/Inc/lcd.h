#ifndef LCD_H
#define LCD_H

void tempo_us(uint16_t t);
void enable();
void lcd_write(unsigned char c);
void lcd_puts(const char *s);
void lcd_printd(uint16_t c);
void lcd_putc(char c);
void lcd_goto(unsigned char pos);
void lcd_clear();
void lcd_init();

#endif
