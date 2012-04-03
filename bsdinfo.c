/*
 *  Copyright (c) 2011 Jakub Szafrański <samu@pirc.pl>
 * 
 *  All rights reserved.
 * 
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *  1. Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *  2. Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution.
 * 
 *  THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 *  ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 *  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 *  ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 *  FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 *  DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 *  OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 *  HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 *  LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 *  OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 *  SUCH DAMAGE.
 */
 
#include <sys/types.h>
#include <sys/sysctl.h>

#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/timespec.h>
#include <time.h>
#include <sys/proc.h>
#include <kvm.h>

#include <stdlib.h>
#include <stdio.h>
#include <pwd.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <sys/proc.h>
#include <sys/user.h>
#include <sys/sysctl.h>
#include <kvm.h>
#include <ufs/ufs/quota.h>

#define O_RDONLY 0x0000
#define _POSIX2_LINE_MAX 2048
#define _PATH_DEVNULL "/dev/null"

int psysctl(char *name)
{
    char buf[256];
    size_t size = sizeof(buf);
    
    if (sysctlbyname(name, &buf, &size, NULL, 0) != 0) {
        return (1);
    }
    printf("%s", buf);
    return (0);
}

int printval(char *val, char *name) 
{
    printf("\033[1;31m%s:\033[0;0m ", val);
    psysctl(name);
}

int printuptime() 
{
    struct timespec tp;
    time_t uptime;
    int days, hrs, i, mins, secs;
    char buf[256];
    
    if (clock_gettime(CLOCK_UPTIME, &tp) != -1) {
        uptime = tp.tv_sec;
        if (uptime > 60)
            uptime += 30;
        days = uptime / 86400;
        uptime %= 86400;
        hrs = uptime / 3600;
        uptime %= 3600;
        mins = uptime / 60;
        secs = uptime % 60;
        (void)printf("\033[1;31mUptime: \033[0;0m");
        if (days > 0)
            (void)printf("%d day%s ", days, days > 1 ? "s" : "");
        if (hrs > 0 && mins > 0)
            (void)printf("%d:%02d", hrs, mins);
        else if (hrs == 0 && mins > 0) 
            (void)printf("00:%02d", hrs, mins);
        else 
            (void)printf("00:00");
    }
}

int printmem()
{
    printf("\033[1;31mRAM:\033[0;0m ");
    unsigned long int ram_size;
    size_t len_size = sizeof(ram_size);
    sysctlbyname("hw.physmem", &ram_size, &len_size, NULL, 0);
    
    unsigned long int ram_usage;
    size_t len_usage = sizeof(ram_usage);
    sysctlbyname("vm.stats.vm.v_free_count", &ram_usage, &len_usage, NULL, 0);

    unsigned long int ram_pagesize;
    size_t len_pagesize = sizeof(ram_pagesize);
    sysctlbyname("vm.stats.vm.v_page_size", &ram_pagesize, &len_pagesize, NULL, 0);

    ram_usage = (ram_size - (ram_usage*ram_pagesize)) / 1048576;
    ram_size = ram_size / 1048576;
    printf("%dM / %dM", ram_usage, ram_size);
    return (0);
    
}

int main()
{
    int i, proc_count = 0;
    char *cuname;
    char buf[_POSIX2_LINE_MAX];
    const char *execf, *coref;
    static kvm_t *kd;
    struct kinfo_proc *kp;
    static int nproc;
    static struct kinfo_proc *plist;
    
    execf = NULL;
    coref = _PATH_DEVNULL;
    kd = kvm_openfiles(execf, coref, NULL, O_RDONLY, buf);
    plist = kvm_getprocs(kd, KERN_PROC_PROC, 0, &nproc);

    for (i = 0, kp = plist; i < nproc; i++, kp++) proc_count++;
    
    printf("\n");
    printf("\033[1;31m  ```                        `\033[0;0m       \n");
    printf("\033[1;31m s` `.....---.......--.```   -/\033[0;0m      "); printval("OS", "kern.ostype"); printf(" "); psysctl("hw.machine_arch"); printf("\n");
    printf("\033[1;31m +o   .--`         /y:`      +.\033[0;0m      "); printval("Hostname", "kern.hostname");  printf("\n");
    printf("\033[1;31m  yo`:.            :o      `+-\033[0;0m       "); printval("Kernel", "kern.osrelease");  printf("\n");
    printf("\033[1;31m   y/               -/`   -o/\033[0;0m        "); printuptime(); printf("\n");
    printf("\033[1;31m  .-                  ::/sy+:.\033[0;0m       "); printf("\033[1;31mProcesses:\033[0;0m %d\n", proc_count);
    printf("\033[1;31m  /                     `--  /\033[0;0m       "); printmem(); printf("\n");
    printf("\033[1;31m `:                          :`\033[0;0m      "); printval("CPU", "hw.model");  printf("\n");
    printf("\033[1;31m `:                          :`\033[0;0m      \n");
    printf("\033[1;31m  /                          /\033[0;0m       \n");
    printf("\033[1;31m  .-                        -.\033[0;0m       \n");
    printf("\033[1;31m   --                      -.\033[0;0m        \n");
    printf("\033[1;31m    `:`                  `:`\033[0;0m         \n");
    printf("\033[1;31m      .--             `--.\033[0;0m           \n");
    printf("\033[1;31m         .---.....----.\033[0;0m              \n");
    printf("\n");

    return (0);
}
