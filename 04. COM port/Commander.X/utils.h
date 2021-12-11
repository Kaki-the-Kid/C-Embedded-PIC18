/* 
 * File:   utils.h
 * Author: Christian
 *
 * Created on September 27, 2019, 9:16 AM
 */

#ifndef UTILS_H
#define	UTILS_H

#ifdef	__cplusplus
extern "C" {
#endif

    // Read a line from Serial port, with option to enter passwords.
    void readline(char *str, bool password);

#ifdef	__cplusplus
}
#endif

#endif	/* UTILS_H */

