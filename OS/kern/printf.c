// Simple implementation of cprintf console output for the kernel,
// based on printfmt() and the kernel console's cputchar().

#include <inc/types.h>
#include <inc/stdio.h>
#include <inc/stdarg.h>


static void
putch(int ch, int *cnt) // printa karakter na screen po trenutnoj lokaciji kursora 
{                     // 
	cputchar(ch);
	*cnt++;
}

int
vcprintf(const char *fmt, va_list ap)
{
	int cnt = 0;

	vprintfmt((void*)putch, &cnt, fmt, ap); // vratiti ce karakter koji treba biti ispisan
	return cnt; // karakter ce vratiti ali u int formatu, sto ce biti ascii
}

int
cprintf(const char *fmt, ...) // ispis outputa direktno na konzolu
                            // fmt je const char* koji se proslijedi
{                         // kao lista argumenata u start
	va_list ap;
	int cnt;

	va_start(ap, fmt); // va_start je invoked i moze poceti citati va_list argumente, a fmt je counter
	cnt = vcprintf(fmt, ap); // proslijedjen cc * fmt i ap va_lista 
	va_end(ap); // va_list i va_args su zavrsili sa davanjem vrijednosti cc* fmt
  // cnt je vracen 

	return cnt;
}

