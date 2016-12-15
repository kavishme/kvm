#ifndef ARCH_X86_KVM_VMXSTAT_H
#define ARCH_X86_KVM_VMXSTAT_H

#include <asm/vmx.h>
#include <linux/time.h>

struct vmx_stat{
        int exits[EXIT_REASON_PCOMMIT+1];
        int allexits;
        int totalexits;
        struct timespec starttime;
        struct timespec endtime;
        int irq_injections;
        int nmi_injections;
        int exception_injections;
};

/*
printk("TIME: %.2lu:%.2lu:%.2lu:%.6lu \r\n",
                   (curr_tm.tv_sec / 3600) % (24),
                   (curr_tm.tv_sec / 60) % (60),
                   curr_tm.tv_sec % 60,
                   curr_tm.tv_nsec / 1000);
*/

#endif