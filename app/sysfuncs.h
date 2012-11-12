#ifndef	_SYSFUNCS_H
#define	_SYSFUNCS_H


#include <stdint.h>

void sei(void);
void cli(void);


#define	MEMORY_BARRIER()

#define CLI_SEI_BUG_MEMORY_BARRIER()

extern uint8_t SREG;

#endif	/* _SYSFUNCS_H */
