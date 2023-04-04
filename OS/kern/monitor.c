// Simple command-line kernel monitor useful for
// controlling the kernel and exploring the system interactively.

#include <inc/assert.h>
#include <inc/memlayout.h>
#include <inc/stdio.h>
#include <inc/string.h>
#include <inc/x86.h>

#include <kern/console.h>
#include <kern/kdebug.h>
/* <<<<<<< HEAD */
#include <kern/trap.h>
/* ======= */
#include <kern/monitor.h>
/* >>>>>>> lab2 */

#define CMDBUF_SIZE 80  // enough for one VGA text line

struct Command {
  const char *name;
  const char *desc;
  // return -1 to force monitor to exit
  int (*func)(int argc, char **argv, struct Trapframe *tf);
};

static struct Command commands[] = {
    {"help", "Display this list of commands", mon_help},
    {"kerninfo", "Display information about the kernel", mon_kerninfo},
};

/***** Implementations of basic kernel monitor commands *****/

int mon_help(int argc, char **argv, struct Trapframe *tf) {
  int i;

  for (i = 0; i < ARRAY_SIZE(commands); i++)
    cprintf("%s - %s\n", commands[i].name, commands[i].desc);
  return 0;
}

int mon_kerninfo(int argc, char **argv, struct Trapframe *tf) {
  extern char _start[], entry[], etext[], edata[], end[];

  cprintf("Special kernel symbols:\n");
  cprintf("  _start                  %08x (phys)\n", _start);
  cprintf("  entry  %08x (virt)  %08x (phys)\n", entry, entry - KERNBASE);
  cprintf("  etext  %08x (virt)  %08x (phys)\n", etext, etext - KERNBASE);
  cprintf("  edata  %08x (virt)  %08x (phys)\n", edata, edata - KERNBASE);
  cprintf("  end    %08x (virt)  %08x (phys)\n", end, end - KERNBASE);
  cprintf("Kernel executable memory footprint: %dKB\n",
          ROUNDUP(end - entry, 1024) / 1024);
  return 0;
}

int mon_backtrace(int argc, char **argv, struct Trapframe *tf) {
  uint32_t ebp =
      read_ebp();  // pri pokretanju kernela ebp je postavljen na 0,
                   // a mi smo putem funkcije read_ebp dobili njegovu vrijednost
                   //

  cprintf("Stack backtrace: \n");

  while (ebp) {
    uint32_t *eip =
        (uint32_t *)(ebp + 4);  // znamo da je eip na 4 bajta nizoj mem adresi u
                                // steku od ebp te smo ga tu i pronasli

    cprintf("ebp %08x eip %08x args %08x %08x %08x %08x %08x \n", ebp, *eip,
            *(eip + 1), *(eip + 2), *(eip + 3), *(eip + 4), *(eip + 5));
    // spram konvencije za stek, argumenti nam se nalaze odma iznad, odnosno
    // ispod eipa, te smo te uint32_t pointere koji imaju 4 bajta sabrali sa 1-5
    // i dobili tacne lokacije
    // tako smo putem funkcije cprintf ispisali ebp, eip , te args u zeljenom
    // formatu
    //

    struct Eipdebuginfo info;  // stuct Eipdebuginfo nam je struktura koja nosi
                               // podatake o eipu i preko nje cemo dobiti ono
                               // sto zelimo ispisati u funkciji backtrace


    bool result = debuginfo_eip(
        *eip,
        &info);  // Proslijedili smo eip i adresu struct Eipdebuginfo info
                 // u koju ce funkcija debuginfo_eip pohraniti trazene
                 // vrijednosti
                 // Funckija je zavrsena i u bool result smo dobili true ili
                 // false , debuginfo_eip vrati 0 ako su vrijednosti pronadjene
                 // nakon toga smo pod uslovom da je result = 0, putem cprintf
                 // ispisali trazene vrijednosti u trazenom formatu
    if (!result) {
      cprintf("%s:%d: %.*s+%u\n",
              info.eip_file,        // naziv fajla koji debagiramo, te se ispise
                                    // njegov path, te ga ispisemo sa %s
              info.eip_line,        // broj linija fajla koji gledamo
              info.eip_fn_namelen,  // duzina naziva funkcije, koja se uzme
                                    // u sintaksi %.* i oduzme se broj karaktera
                                    // od string fn_name pri ispisu
              info.eip_fn_name,     // naziv funkcije u kojoj se nalazi eip
              eip - info.eip_fn_addr);  // adresa eipa - startna adresa funkcije
                                        // tako ispisemo tacnu adresu gdje je
                                        // taj fajl primjera radi ispisan nam je
                                        // entry sa vrijednosti 0

      //
    }
    ebp = *(uint32_t *)ebp;
  }

  return 0;
}

/***** Kernel monitor command interpreter *****/

#define WHITESPACE "\t\r\n "
#define MAXARGS 16

static int runcmd(char *buf, struct Trapframe *tf) {
  int argc;
  char *argv[MAXARGS];
  int i;

  // Parse the command buffer into whitespace-separated arguments
  argc = 0;
  argv[argc] = 0;
  while (1) {
    // gobble whitespace
    while (*buf && strchr(WHITESPACE, *buf)) *buf++ = 0;
    if (*buf == 0) break;

    // save and scan past next arg
    if (argc == MAXARGS - 1) {
      cprintf("Too many arguments (max %d)\n", MAXARGS);
      return 0;
    }
    argv[argc++] = buf;
    while (*buf && !strchr(WHITESPACE, *buf)) buf++;
  }
  argv[argc] = 0;

  // Lookup and invoke the command
  if (argc == 0) return 0;
  for (i = 0; i < ARRAY_SIZE(commands); i++) {
    if (strcmp(argv[0], commands[i].name) == 0)
      return commands[i].func(argc, argv, tf);
  }
  cprintf("Unknown command '%s'\n", argv[0]);
  return 0;
}

void monitor(struct Trapframe *tf) {
  char *buf;

/* <<<<<<< HEAD */
	if (tf != NULL)
		print_trapframe(tf);
/* ======= */
  cprintf("Welcome to the JOS kernel monitor!\n");
  cprintf("Type 'help' for a list of commands.\n");
/* >>>>>>> lab2 */

  while (1) {
    buf = readline("K> ");
    if (buf != NULL)
      if (runcmd(buf, tf) < 0) break;
  }
}
