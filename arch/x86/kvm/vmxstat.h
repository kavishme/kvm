#ifndef ARCH_X86_KVM_VMXSTAT_H
#define ARCH_X86_KVM_VMXSTAT_H

#include <linux/time.h>

#define MAX_CPU                         10

#define STAT_INTR_TYPE_EXT_INTR         0
#define STAT_INTR_TYPE_NMI_INTR	        1
#define STAT_INTR_TYPE_IRQ_INTR         2

#define TOTAL_EVENTS                    3
#define TOTAL_EXITS                     66

struct vmx_stat{
        unsigned int exits[TOTAL_EXITS];
        unsigned int events[TOTAL_EVENTS];
        unsigned int allexits;
        unsigned int totalexits;
        unsigned long starttime;
        unsigned long endtime;
        unsigned int irq_injections;
        unsigned int nmi_injections;
        unsigned int exception_injections;
};


// #define VMX_EXIT_REASONS_FAILED_VMENTRY 0x80000000

// #define EXIT_REASON_EXCEPTION_NMI 0
// #define EXIT_REASON_EXTERNAL_INTERRUPT 1
// #define EXIT_REASON_TRIPLE_FAULT 2

// #define EXIT_REASON_PENDING_INTERRUPT 7
// #define EXIT_REASON_NMI_WINDOW 8
// #define EXIT_REASON_TASK_SWITCH 9
// #define EXIT_REASON_CPUID 10
// #define EXIT_REASON_HLT 12
// #define EXIT_REASON_INVD 13
// #define EXIT_REASON_INVLPG 14
// #define EXIT_REASON_RDPMC 15
// #define EXIT_REASON_RDTSC 16
// #define EXIT_REASON_VMCALL 18
// #define EXIT_REASON_VMCLEAR 19
// #define EXIT_REASON_VMLAUNCH 20
// #define EXIT_REASON_VMPTRLD 21
// #define EXIT_REASON_VMPTRST 22
// #define EXIT_REASON_VMREAD 23
// #define EXIT_REASON_VMRESUME 24
// #define EXIT_REASON_VMWRITE 25
// #define EXIT_REASON_VMOFF 26
// #define EXIT_REASON_VMON 27
// #define EXIT_REASON_CR_ACCESS 28
// #define EXIT_REASON_DR_ACCESS 29
// #define EXIT_REASON_IO_INSTRUCTION 30
// #define EXIT_REASON_MSR_READ 31
// #define EXIT_REASON_MSR_WRITE 32
// #define EXIT_REASON_INVALID_STATE 33
// #define EXIT_REASON_MSR_LOAD_FAIL 34
// #define EXIT_REASON_MWAIT_INSTRUCTION 36
// #define EXIT_REASON_MONITOR_TRAP_FLAG 37
// #define EXIT_REASON_MONITOR_INSTRUCTION 39
// #define EXIT_REASON_PAUSE_INSTRUCTION 40
// #define EXIT_REASON_MCE_DURING_VMENTRY 41
// #define EXIT_REASON_TPR_BELOW_THRESHOLD 43
// #define EXIT_REASON_APIC_ACCESS 44
// #define EXIT_REASON_EOI_INDUCED 45
// #define EXIT_REASON_EPT_VIOLATION 48
// #define EXIT_REASON_EPT_MISCONFIG 49
// #define EXIT_REASON_INVEPT 50
// #define EXIT_REASON_RDTSCP 51
// #define EXIT_REASON_PREEMPTION_TIMER 52
// #define EXIT_REASON_INVVPID 53
// #define EXIT_REASON_WBINVD 54
// #define EXIT_REASON_XSETBV 55
// #define EXIT_REASON_APIC_WRITE 56
// #define EXIT_REASON_INVPCID 58
// #define EXIT_REASON_PML_FULL 62
// #define EXIT_REASON_XSAVES 63
// #define EXIT_REASON_XRSTORS 64
// #define EXIT_REASON_PCOMMIT 65

/*
printk("TIME: %.2lu:%.2lu:%.2lu:%.6lu \r\n",
                   (curr_tm.tv_sec / 3600) % (24),
                   (curr_tm.tv_sec / 60) % (60),
                   curr_tm.tv_sec % 60,
                   curr_tm.tv_nsec / 1000);
*/

#endif