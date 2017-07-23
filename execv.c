#include <stdlib.h>
#include <unistd.h>
int main(int argc, char ** argv)
{
     if (!fork())
     {
         execv("getconf -a | grep -i cache", {"myDir"});      }
}