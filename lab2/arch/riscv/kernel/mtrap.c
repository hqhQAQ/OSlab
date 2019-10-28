void mtrap_handler(unsigned long* regs, unsigned long mcause, unsigned long mepc) 
{
    // interrupt
   if((long)mcause < 0) {

   }
   // exception
   else {
       switch (mcause)
       {
       case 9:
            unsigned long *mtimecmp = (unsigned long *)0x2004000;
            unsigned long *mtime = (unsigned long *)0x200BFF8;
            *mtimecmp = *mtime + 100000;
            break;   
       default:
           break;
       }
   }
}
