/* 
 * File:   timer.h
 * Author: christian
 *
 * Created on September 27, 2019, 9:30 AM
 */

#ifndef TIMER_H
#define	TIMER_H

#ifdef	__cplusplus
extern "C" {
#endif

    void timer_interrupt(void);
    
    void timer_start(void);
    
    void timer_stop(void);
    
    void timer_setdisplay(int display);
    
    void timer_cleardisplay(int display);
    
    void timer_write(int display, char input, bool dot);
    
    void timer_writeInt(int amount);
    
    bool timer_running();


#ifdef	__cplusplus
}
#endif

#endif	/* TIMER_H */

