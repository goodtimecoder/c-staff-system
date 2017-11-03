#include<stdio.h>

void main()
{
    int n;
	menu();
	scanf("%d",&n);
	while(n)
	{
	    switch(n)
		{
		    case 1:in();break;
			case 2:search();break;
			case 3:del();break;
			case 4:modify();break;
			case 5:insert();break;
			case 6:order();break;
		    case 7:total();break;
			case 8:show();break;
			case 9:help();break;
			default:break;
		}
		getchar();
		menu();
		scanf("%d",&n);
	}
}
