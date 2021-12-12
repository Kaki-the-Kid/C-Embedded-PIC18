/* 
 * File:   lcd.h
 * Author: Karsten
 *
 * Created on December 11, 2021, 11:24 PM
 */

#ifndef LCD_H
#define	LCD_H

#define FIRST_LINE 0x80
#define SECOND_LINE 0xC0

void lcd_init(void);
void lcd_command(char *);
void lcd_puts(char *);

void clear_screen(void);
void introduction_screen(void);


#endif	/* LCD_H */

