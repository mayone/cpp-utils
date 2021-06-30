#include <stdio.h>
#include <string.h>
#include <sys/sysctl.h>
#include <sys/utsname.h>

void sysInfo();
void byteOrder();
void detailInfo();

int main(int argc, char const *argv[])
{
    sysInfo();
    byteOrder();
    // detailInfo();

    return 0;
}

void sysInfo()
{
    int ret;
    char str[256];
    size_t size_str;

    printf("CPU:\t\t");
    size_str = sizeof(str);
    ret = sysctlbyname("machdep.cpu.brand_string", str, &size_str, NULL, 0);
    printf("%s\n", str);

    printf("Vendor:\t\t");
#if defined(__APPLE__)
    printf("Apple\n");
#elif defined(__linux__)
    printf("Linux\n");
#elif defined(WIN32) || defined(_WIN32)
    printf("Windows\n");
#else
    printf("Unknown\n");
#endif

    printf("OS:\t\t");
    size_str = sizeof(str);
    ret = sysctlbyname("kern.ostype", str, &size_str, NULL, 0);
    printf("%s ", str);
    size_str = sizeof(str);
    ret = sysctlbyname("kern.osrelease", str, &size_str, NULL, 0);
    printf("Kernel Version %s\n", str);
}

void byteOrder()
{
    union
    {
        short s;
        char c[sizeof(short)];
    } un;
    un.s = 0x0102;

    printf("Byteorder:\t");
    if (sizeof(short) == 2)
    {
        if (un.c[0] == 1 && un.c[1] == 2)
        {
            printf("big-endian\n");
        }
        else if (un.c[0] == 2 && un.c[1] == 1)
        {
            printf("little-endian\n");
        }
        else
        {
            printf("unknown\n");
        }
    }
    else
    {
        printf("sizeof(short) = %lu\n", sizeof(short));
    }
}

void detailInfo()
{
    int ret;
    char str[256];
    size_t size_str;
    int num;
    size_t size_num;

    printf("Info by sysctl:\n");
    size_str = sizeof(str);
    ret = sysctlbyname("kern.ostype", str, &size_str, NULL, 0);
    printf("ostype:\t\t%s\n", str);
    size_str = sizeof(str);
    ret = sysctlbyname("kern.hostname", str, &size_str, NULL, 0);
    printf("hostname:\t%s\n", str);
    size_str = sizeof(str);
    ret = sysctlbyname("kern.osrelease", str, &size_str, NULL, 0);
    printf("osrelease:\t%s\n", str);
    size_str = sizeof(str);
    ret = sysctlbyname("kern.version", str, &size_str, NULL, 0);
    printf("version:\t%s\n", str);
    size_num = sizeof(num);
    ret = sysctlbyname("hw.activecpu", &num, &size_num, NULL, 0);
    printf("activecpu:\t%d\n", num);

    printf("------------------------------\n");

    struct utsname buf;
    uname(&buf);

    printf("Info by uname:\n");
    printf("sysname:\t%s\n", buf.sysname);
    printf("nodename:\t%s\n", buf.nodename);
    printf("release:\t%s\n", buf.release);
    printf("version:\t%s\n", buf.version);
    printf("machine:\t%s\n", buf.machine);
}