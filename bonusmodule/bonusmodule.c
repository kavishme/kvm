#include <linux/module.h>
#include <linux/kernel.h>
//#include <linux/init.h>
#include <linux/slab.h>

#include "vmxstat.h"

#define PERMISSION 0
#define EXIT_REASON_EXCEPTION_NMI 0
#define EXIT_REASON_EXTERNAL_INTERRUPT 1
#define EXIT_REASON_TRIPLE_FAULT 2

#define EXIT_REASON_PENDING_INTERRUPT 7
#define EXIT_REASON_NMI_WINDOW 8
#define EXIT_REASON_TASK_SWITCH 9
#define EXIT_REASON_CPUID 10
#define EXIT_REASON_HLT 12
#define EXIT_REASON_INVD 13
#define EXIT_REASON_INVLPG 14
#define EXIT_REASON_RDPMC 15
#define EXIT_REASON_RDTSC 16
#define EXIT_REASON_VMCALL 18
#define EXIT_REASON_VMCLEAR 19
#define EXIT_REASON_VMLAUNCH 20
#define EXIT_REASON_VMPTRLD 21
#define EXIT_REASON_VMPTRST 22
#define EXIT_REASON_VMREAD 23
#define EXIT_REASON_VMRESUME 24
#define EXIT_REASON_VMWRITE 25
#define EXIT_REASON_VMOFF 26
#define EXIT_REASON_VMON 27
#define EXIT_REASON_CR_ACCESS 28
#define EXIT_REASON_DR_ACCESS 29
#define EXIT_REASON_IO_INSTRUCTION 30
#define EXIT_REASON_MSR_READ 31
#define EXIT_REASON_MSR_WRITE 32
#define EXIT_REASON_INVALID_STATE 33
#define EXIT_REASON_MSR_LOAD_FAIL 34
#define EXIT_REASON_MWAIT_INSTRUCTION 36
#define EXIT_REASON_MONITOR_TRAP_FLAG 37
#define EXIT_REASON_MONITOR_INSTRUCTION 39
#define EXIT_REASON_PAUSE_INSTRUCTION 40
#define EXIT_REASON_MCE_DURING_VMENTRY 41
#define EXIT_REASON_TPR_BELOW_THRESHOLD 43
#define EXIT_REASON_APIC_ACCESS 44
#define EXIT_REASON_EOI_INDUCED 45
#define EXIT_REASON_EPT_VIOLATION 48
#define EXIT_REASON_EPT_MISCONFIG 49
#define EXIT_REASON_INVEPT 50
#define EXIT_REASON_RDTSCP 51
#define EXIT_REASON_PREEMPTION_TIMER 52
#define EXIT_REASON_INVVPID 53
#define EXIT_REASON_WBINVD 54
#define EXIT_REASON_XSETBV 55
#define EXIT_REASON_APIC_WRITE 56
#define EXIT_REASON_INVPCID 58
#define EXIT_REASON_PML_FULL 62
#define EXIT_REASON_XSAVES 63
#define EXIT_REASON_XRSTORS 64
#define EXIT_REASON_PCOMMIT 65
#define VCPU_ARR_SIZE 1

static int REQUEST = 1;
char *exit_names[TOTAL_EXITS] = {NULL};
//struct cmpe_stat *stat_data;//[VCPU_ARR_SIZE] = {0};
//void *stat_data;

// MODULE_AUTHOR("Kavish Jain, kavishme@gmail.com");
MODULE_LICENSE("GPL");
// MODULE_DESCRIPTION("Module to get VM stats from VMM running over KVM");

module_param(REQUEST, int, S_IRUGO);
MODULE_PARM_DESC(REQUEST, "The type of statistics needed. Can be one of {1, 2, 3, 4}");

void answer1(void)
{
    unsigned int cpu = 0, i = 0;
    unsigned long texits;
    struct cmpe_stat *pstat = NULL;
    int vcpus = 0;

    vcpus = getvcpucount();

    if (vcpus >= 1)
    {
        pstat = kmalloc(sizeof(struct cmpe_stat) * vcpus, PERMISSION);
        if (pstat != NULL)
        {
            exportstats(pstat, vcpus);
            for (i = 0; i < TOTAL_EXITS; ++i)
            {
                texits = 0;
                if (exit_names[i] != NULL)
                {
                    for (cpu = 0; cpu < vcpus; ++cpu)
                    {
                        texits += pstat[cpu].texits[i];
                    }
                    printk(KERN_ERR "\n Bonus%d %s:%lu", REQUEST, exit_names[i], texits);
                }
            }
            kfree(pstat);
        }
        else
        {
            printk(KERN_ERR "\n Bonus%d Not enough memory available.", REQUEST);
        }
    }
    else
    {
        printk(KERN_ERR "\n Bonus%d No vCPU running.", REQUEST);
    }
}

void answer2(void)
{
    unsigned int cpu = 0;
    unsigned long tevents;
    struct cmpe_stat *pstat = NULL;
    int vcpus = 0;

    vcpus = getvcpucount();
    printk(KERN_ERR "\n Bonus%d vCPU #%d", REQUEST, vcpus);

    if (vcpus >= 1)
    {
        pstat = kmalloc(sizeof(struct cmpe_stat) * vcpus, PERMISSION);
        if (pstat != NULL)
        {
            exportstats(pstat, vcpus);

            for (cpu = 0; cpu < vcpus; ++cpu)
            {
                tevents = 0;
                tevents = pstat[cpu].nmi_injections + pstat[cpu].irq_injections + pstat[cpu].excep_injections;
                printk(KERN_ERR "\n Bonus%d vCPU %u has %lu total event injected", REQUEST, cpu, tevents);
            }
            kfree(pstat);
        }
        else
        {
            printk(KERN_ERR "\n Bonus%d Not enough memory available.", REQUEST);
        }
    }
    else
    {
        printk(KERN_ERR "\n Bonus%d No vCPU running.", REQUEST);
    }
}

void answer3(void)
{
    unsigned int cpu = 0;
    unsigned int avgexits;
    unsigned long duration;
    struct timespec ts;
    struct cmpe_stat *pstat = NULL;
    int vcpus = 0;

    vcpus = getvcpucount();
    printk(KERN_ERR "\n Bonus%d vCPU #%d", REQUEST, vcpus);

    if (vcpus >= 1)
    {
        pstat = kmalloc(sizeof(struct cmpe_stat) * vcpus, PERMISSION);
        if (pstat != NULL)
        {
            exportstats(pstat, vcpus);
            getnstimeofday(&ts);

            for (cpu = 0; cpu < vcpus; ++cpu)
            {
                avgexits = 0;
                duration = 0;
                duration = pstat[cpu].starttime - ts.tv_sec;
                avgexits = pstat[cpu].exits/duration;
                printk(KERN_ERR "\n Bonus%d vCPU %u has %u average exits per sec", REQUEST, cpu, avgexits);
            }
            kfree(pstat);
        }
        else
        {
            printk(KERN_ERR "\n Bonus%d Not enough memory available.", REQUEST);
        }
    }
    else
    {
        printk(KERN_ERR "\n Bonus%d No vCPU running.", REQUEST);
    }
}

void answer4(void)
{
    unsigned int cpu = 0, i = 0;    
    unsigned long long avglatency = 0;
    struct cmpe_stat *pstat = NULL;
    int vcpus = 0;

    vcpus = getvcpucount();
    printk(KERN_ERR "\n Bonus%d vCPU #%d", REQUEST, vcpus);

    if (vcpus >= 1)
    {
        pstat = kmalloc(sizeof(struct cmpe_stat) * vcpus, PERMISSION);
        if (pstat != NULL)
        {
            exportstats(pstat, vcpus);

            for (cpu = 0; cpu < vcpus; ++cpu)
            {
                for (i = 0; i < TOTAL_EXITS; ++i)
                {
                    if (exit_names[i] != NULL)
                    {
                        avglatency = 0;
                        if(pstat[cpu].texits[i] != 0)
                        {
                            avglatency = pstat[cpu].latency[i] / pstat[cpu].texits[i];
                            printk(KERN_ERR "\n Bonus%d vCPU %u has %llu average latency to process exit type %s", REQUEST, cpu, avglatency, exit_names[i]);
                        }
                        else
                        {
                            printk(KERN_ERR "\n Bonus%d vCPU %u has 0 exists of type %s", REQUEST, cpu,exit_names[i]);
                        }
                    }
                }
            }
            kfree(pstat);
        }
        else
        {
            printk(KERN_ERR "\n Bonus%d Not enough memory available.", REQUEST);
        }
    }
    else
    {
        printk(KERN_ERR "\n Bonus%d No vCPU running.", REQUEST);
    }
}

int init_module(void)
{
    unsigned int i = 0;

    printk(KERN_ERR "\n Bonus%d Start", REQUEST);
    for (i = 0; i < TOTAL_EXITS; ++i)
    {
        exit_names[i] = NULL;
    }

    exit_names[EXIT_REASON_EXCEPTION_NMI] = "EXCEPTION_NMI\0";
    exit_names[EXIT_REASON_EXTERNAL_INTERRUPT] = "EXTERNAL_INTERRUPT\0";
    exit_names[EXIT_REASON_TRIPLE_FAULT] = "TRIPLE_FAULT\0";
    exit_names[VMSTAT_VMX_EXIT_REASONS_FAILED_VMENTRY] = "EXIT_REASONS_FAILED_VMENTRY\0";
    exit_names[VMSTAT_VMX_EXIT_REASONS_OTHER] = "EXIT_REASONS_UNKNOWN\0";
    exit_names[EXIT_REASON_PENDING_INTERRUPT] = "PENDING_INTERRUPT\0";
    exit_names[EXIT_REASON_NMI_WINDOW] = "NMI_WINDOW\0";
    exit_names[EXIT_REASON_TASK_SWITCH] = "TASK_SWITCH\0";
    exit_names[EXIT_REASON_CPUID] = "CPUID\0";
    exit_names[EXIT_REASON_HLT] = "HLT\0";
    exit_names[EXIT_REASON_INVLPG] = "INVLPG\0";
    exit_names[EXIT_REASON_RDPMC] = "RDPMC\0";
    exit_names[EXIT_REASON_RDTSC] = "RDTSC\0";
    exit_names[EXIT_REASON_VMCALL] = "VMCALL\0";
    exit_names[EXIT_REASON_VMCLEAR] = "VMCLEAR\0";
    exit_names[EXIT_REASON_VMLAUNCH] = "VMLAUNCH\0";
    exit_names[EXIT_REASON_VMPTRLD] = "VMPTRLD\0";
    exit_names[EXIT_REASON_VMPTRST] = "VMPTRST\0";
    exit_names[EXIT_REASON_VMREAD] = "VMREAD\0";
    exit_names[EXIT_REASON_VMRESUME] = "VMRESUME\0";
    exit_names[EXIT_REASON_VMWRITE] = "VMWRITE\0";
    exit_names[EXIT_REASON_VMOFF] = "VMOFF\0";
    exit_names[EXIT_REASON_VMON] = "VMON\0";
    exit_names[EXIT_REASON_CR_ACCESS] = "CR_ACCESS\0";
    exit_names[EXIT_REASON_DR_ACCESS] = "DR_ACCESS\0";
    exit_names[EXIT_REASON_IO_INSTRUCTION] = "IO_INSTRUCTION\0";
    exit_names[EXIT_REASON_MSR_READ] = "MSR_READ\0";
    exit_names[EXIT_REASON_MSR_WRITE] = "MSR_WRITE\0";
    exit_names[EXIT_REASON_MWAIT_INSTRUCTION] = "MWAIT_INSTRUCTION\0";
    exit_names[EXIT_REASON_MONITOR_TRAP_FLAG] = "MONITOR_TRAP_FLAG\0";
    exit_names[EXIT_REASON_MONITOR_INSTRUCTION] = "MONITOR_INSTRUCTION\0";
    exit_names[EXIT_REASON_PAUSE_INSTRUCTION] = "PAUSE_INSTRUCTION\0";
    exit_names[EXIT_REASON_MCE_DURING_VMENTRY] = "MCE_DURING_VMENTRY\0";
    exit_names[EXIT_REASON_TPR_BELOW_THRESHOLD] = "TPR_BELOW_THRESHOLD\0";
    exit_names[EXIT_REASON_APIC_ACCESS] = "APIC_ACCESS\0";
    exit_names[EXIT_REASON_EPT_VIOLATION] = "EPT_VIOLATION\0";
    exit_names[EXIT_REASON_EPT_MISCONFIG] = "EPT_MISCONFIG\0";
    exit_names[EXIT_REASON_INVEPT] = "INVEPT\0";
    exit_names[EXIT_REASON_PREEMPTION_TIMER] = "PREEMPTION_TIMER\0";
    exit_names[EXIT_REASON_WBINVD] = "WBINVD\0";
    exit_names[EXIT_REASON_APIC_WRITE] = "APIC_WRITE\0";
    exit_names[EXIT_REASON_EOI_INDUCED] = "EOI_INDUCED\0";
    exit_names[EXIT_REASON_INVALID_STATE] = "INVALID_STATE\0";
    exit_names[EXIT_REASON_MSR_LOAD_FAIL] = "MSR_LOAD_FAIL\0";
    exit_names[EXIT_REASON_INVD] = "INVD\0";
    exit_names[EXIT_REASON_INVVPID] = "INVVPID\0";
    exit_names[EXIT_REASON_INVPCID] = "INVPCID\0";
    exit_names[EXIT_REASON_XSAVES] = "XSAVES\0";
    exit_names[EXIT_REASON_XRSTORS] = "XRSTORS\0";
    exit_names[EXIT_REASON_PCOMMIT] = "PCOMMIT\0";

    switch (REQUEST)
    {
    case 1:
        printk(KERN_ERR "\n Bonus%d Total exits for running VM are:", REQUEST);
        answer1();
        break;

    case 2:
        printk(KERN_ERR "\n Bonus%d Total number of events injected, per CPU:", REQUEST);
        answer2();
        break;

    case 3:
        printk(KERN_ERR "\n Bonus%d Average number of exits per second, per CPU:", REQUEST);
        answer3();
        break;

    case 4:
        printk(KERN_ERR "\n Bonus%d Average latency to process each exit (in cycles), per exit type, per CPU:", REQUEST);
        answer4();
        break;

    default:
        printk(KERN_ERR "\n Bonus Pass a argument while inserting module. arg can only be one of {1,2,3,4}");
        break;
    }
    return 0;
}

void cleanup_module(void)
{
    printk(KERN_ERR "\n Bonus%d End", REQUEST);
}

// module_init(init_stats);
// module_exit(stat_close);