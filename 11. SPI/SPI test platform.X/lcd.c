#include "lcd.h"

void lcd_init(void);
void lcd_command(char *cmd);
void lcd_puts(char *str);

/*
 This Function is for Clear screen without command.
 */
 
void clear_screen(void){
    lcd_command(FIRST_LINE);
    lcd_puts("                ");
    lcd_command(SECOND_LINE);
    lcd_puts("                "); 
}
 
/*
 This Function is for playing introduction.
 */
 
void introduction_screen(void){
    lcd_command(FIRST_LINE);
    lcd_puts("Welcome to");
    lcd_command(SECOND_LINE);
    lcd_puts("circuit Digest");
    __delay_ms(500);
    
    clear_screen();
    lcd_command(FIRST_LINE);
    lcd_puts("mcp4921 with");
    lcd_command(SECOND_LINE);
    lcd_puts("PIC16F877A");
    __delay_ms(350);
}
 