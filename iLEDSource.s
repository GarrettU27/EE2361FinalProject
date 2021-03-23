.include "xc.inc"

.text                       ;BP (put the following data in ROM(program memory))

; This is a library, thus it can *not* contain a _main function: the C file will
; define main().  However, we
; we will need a .global statement to make available ASM functions to C code.
; All functions utilized outside of this file will need to have a leading 
; underscore (_) and be included in a comment delimited list below.
.global _write_0, _write_1, _delay_100us, _delay_1ms
    
    _write_0:
	      ;0.0625 uS per cycle
	      ;5.6 cycles required for 0.35uS (rounded to 6)
	      ;20 cycles total for 1.25uS
    inc LATA  ;1 cycle
    repeat #3 ;1 cycle to set
    nop       ;4 cycles from repeating
    dec LATA  ;1 cycle to set
    repeat #6 ;1 cycle to set
    nop       ;7 cycles to repeat
    return    ;3 cycles to return
	      ;2 cycles to call next
	      ;1 cycle for increase

    _write_1:
		  ;0.0625 uS per cycle
		  ;11.2 cycles required for .7 uS (rounded to 11)
		  ;20 cycles total for 1.25uS
	inc LATA  ;1 cycle
	repeat #8 ;1 cycle to set
	nop       ;9 cycles from repeating
	dec LATA  ;1 cycle
	repeat #1 ;1 cycle
	nop       ;2 cycles from repeating
	return    ;3 cycles to return
		  ;2 cycles to call next
		  ;1 cycle for increase         
		  ;have to call a clear if this is the last one, because there is
		  ;no delay from the next call
    
    _delay_100us:
		    ;0.0625 uS per cycle
		    ;1600 cycles required
		    ;2 cycles to call
       repeat #1593 ;1 cycle to set
       nop          ;1594 cycles from repeats
       return       ;3 cycles to return

    _delay_1ms:
		      ;0.0625 uS per cycle
		      ;16000 cycles required
		      ;2 cycles to call
	repeat #15993 ;1 cycle to set
	nop           ;15994 cycles from repeats
	return        ;3 cycles to return


