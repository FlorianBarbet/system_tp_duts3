#include <stdint.h>

/* main */
extern void main(void);

/* linker symbols */
extern char _text_end;
extern char _bss_start;
extern char _bss_end;
extern char _data_start;
extern char _data_end;


/* reset routine */
void _start(void) __attribute__((naked));
void _start(void)
{
    /* Copy data section */
    char *src,*dst;
    for (src = &_text_end, dst = &_data_start ;  dst < &_data_end ; )
	*dst++ = *src++;
    /* Zero BSS */
    for (dst = &_bss_start ; dst < &_bss_end ;)
	*dst = 0;
    
    main();
    while(1);
}



#define IRQ_VEC_SIZE 35

void *_init_vector[35] __attribute__((section(".interrupt_vector"))) = {
    (void*)STACK_END, /* SP value at boot */
    _start, /* reset routine */
};
