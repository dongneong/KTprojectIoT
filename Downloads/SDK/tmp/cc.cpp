#include <Process.h>
#include <stdio.h>

int main(){
system("ls > green");
char tmp[256];
ifstream fin(green);
while(fin>>tmp)
{
	printf(tmp);
}
fin.close();
return 0;
}
