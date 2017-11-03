#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define LEN sizeof(struct staff)
#define FORMAT "%-8d%-15s%-6d%-8d%-8d%\n"
#define DATA stu[i].num,stu[i].name,stu[i].age,stu[i].time,stu[i].salary

struct staff
{
    int num;
	char name[15];
	int age;
	int time;
	int salary;
};

struct staff stu[50];
void in();
void show();
void show();
void order();
void del();
void modify();
void menu();
void insert();
void total();
void search();
void help();

/*
*界面函数
*/
void menu()
{
	printf("\n\n\n\n\n");
	printf("\t\t|--------------staff---------------|\n");
	printf("\t\t|\t 0.exit                         |\n");
	printf("\t\t|\t 1.input record                 |\n");
	printf("\t\t|\t 2.search record                |\n");
	printf("\t\t|\t 3.delete record                |\n");
	printf("\t\t|\t 4.modify record                |\n");
	printf("\t\t|\t 5.insert record                |\n");
	printf("\t\t|\t 6.order                        |\n");
	printf("\t\t|\t 7.totle number                 |\n");
	printf("\t\t|\t 8.show                         |\n");
	printf("\t\t|\t 9.help                         |\n");
	printf("\t\t|----------------------------------|\n");
	printf("\t\t\t chose(0-9):");
}

/*
*input函数
*/
void in()
{
    int i,m = 0,snum;
    char ch[2];
	FILE *fp;
	if((fp = fopen("data.txt","a+")) == NULL)//用读写方式打开一个文本文件，同时指针指向文件末端。若fopen返回值是一个空值则进入if语句，显示不能打开这个文件
	{
	    printf("can not open\n");
		return;
	}

    while(!feof(fp))//文件指针不在文件尾端时，进入循环。第一次写入数据时，指针指向末端，feof函数返回值是非0值
    {
        if(fread(&stu[m],LEN,1,fp) == 1)//把fp指针指向的文件中数据写入stu数组，每次读取一个led字节大小数据，调用成功则返回一个1
	    {
	        m++;
	    }
    }
    fclose(fp);
    if(m == 0)//文本中没有数据
    {
        printf("no record\n");
    }
    else
    {
        system("clear");//清屏
	    show();
    }
    if((fp = fopen("data.txt","wb")) == NULL)
    {
        printf("can not open\n");
	    return;
    }
    for(i = 0; i < m; i++)//将读入stu中的数据重新写入fp中
    {
        fwrite(&stu[i],LEN,1,fp);
    }
    printf("please input(y/n):");
    scanf("%s",ch);
    while(strcmp(ch,"y") == 0 || strcmp(ch,"Y") == 0)//判断输入的字符是否为’y‘和‘Y’
    {
        printf("number:");
	    scanf("%d",&snum);
	    for(i = 0; i < m; i++)//查看输入工号有无重复
		{
	        if(stu[i].num == snum)
		    {
		        printf("the number is existing!please input a new num\n");//工号重复时提示重新输入
				printf("number:");
				scanf("%d",&snum);
			    i = 0;//查看重新输入的工号是否再次重复
		    }
	    }
		stu[m].num = snum;
	    printf("name:");//输入一个员工姓名信息
	    scanf("%s",stu[m].name);
	    printf("age:");
    	scanf("%d",&stu[m].age);
	    printf("time:");
    	scanf("%d",&stu[m].time);
     	printf("salary:");
	    scanf("%d",&stu[m].salary);
	    if(fwrite(&stu[m],LEN,1,fp) != 1)//将员工信息写入文件
	    {
	        printf("can not save");
	    	getchar();
    	}
	    else
	    {
	        printf("%s save\n",stu[m].name);
		    m++;
	    }
	    printf("continue input(y/n):");
	    scanf("%s",ch);
    }
    fclose(fp);
	printf("ok\n");
}

/*
 * delete函数
 */
 
void del()
{
	FILE *fp;
	int snum,i,j,m = 0;
	char ch[2];
	if((fp = fopen("data.txt","r+")) == NULL)//用读写方式打开一个文本文件，若fopen返回值是一个空值则进入if语句，显示不能打开这个文件
	{
		printf("can not open\n");
		return;
	}
	while( !feof(fp) ) //文件指针不在文件尾端时，进入循环 
	{
        if(fread(&stu[m],LEN,1,fp) == 1) //把fp指针指向的文件中数据写入stu数组，每次读取一个led字节大小数据，调用成功则返回一个1，统计已有员工数
	    {
		    m++;
	    }
	}
	fclose(fp);
	if(m == 0) 
	{
		printf("no record!\n");
		return;
	}
	
    show();
	printf("please input the number:");
	scanf("%d",&snum);
	
	for(i = 0; i < m; i++)
	{
		if(snum == stu[i].num)//找到了要删除的员工工号
		{    
			printf("find the staff,delete?(y/n)");
			scanf("%s",ch);
			if(strcmp(ch,"Y") == 0||strcmp(ch,"y") == 0)
			{
			    for(j = i; j < m; j++)//删除的员工在数组中位置用后一个员工填补，依此类推
				{
			    	stu[j] = stu[j+1];
				}
			}
			m--;
			if((fp = fopen("data.txt","wb")) == NULL)
			{ 
			    printf("can not open\n");
			    return;
			}
			for(j = 0; j < m; j++)
			{
			    if(fwrite(&stu[j] ,LEN,1,fp) != 1)//将剩余员工保存回文本中
			    { 
			        printf("can not save!\n");
				    getchar();
			    }
			}
			fclose(fp);
			printf("delete successfully!\n");
			return;
		}
	}
		printf("not search delete staff！\n");
}
/*
*修改员工信息
*/
void modify()
{
	FILE *fp;
    int i,j,m = 0,snum;
	
    if((fp = fopen("data.txt","r+")) == NULL)
    {
		printf("can not open\n");
		return;
	}
    while( !feof(fp) )//统计已有员工数
	{		
        if(fread(&stu[m],LEN,1,fp) == 1)
		{
	    	m++;
		}
	}
    if(m == 0) 
    {
	    printf("no record!\n");
	    fclose(fp);
	    return;//没有员工信息时退出该函数
    }
	
    show();
    printf("please input the number of the staff which do you want to modify!\n");
    printf("modify number:");
    scanf("%d",&snum);
	
    for(i = 0; i < m; i++)
    {
 	    if(snum == stu[i].num)
	    {
	        printf("find the staff!you can modify!\n");
	        printf("name:");
	        scanf("%s",stu[i].name);
            printf("age:");
	        scanf("%d",&stu[i].age);
	        printf("time:");
    	    scanf("%d",&stu[i].time);
	        printf("salary:");
        	scanf("%d",&stu[i].salary);
	        printf("modify successful!");
	  
	        if((fp = fopen("data.txt","wb")) == NULL)
            { 
                printf("can not open\n");
				return;
	        }
	        for(j = 0;j < m; j++)
			{
	            if(fwrite(&stu[j] ,LEN,1,fp) != 1)//将全部员工保存回文本
                {
			       printf("can not save!"); 
				   getchar();
		        }
			}
	        fclose(fp);
	        return ;
	    }	 
    }
	printf("not modify information！\n");
 }
/*
*查找员工
*/ 
void search()
{ 
    FILE *fp;
    int snum,i,m = 0;
    char ch[2];
	
    if((fp = fopen("data.txt","rb")) == NULL)
    {
		printf("can not open\n");
		return;
    }
    while( !feof(fp) )//统计已有员工数
	{		
        if(fread(&stu[m],LEN,1,fp)==1)
		{
			m++;
		}
	}
    fclose(fp);
    if(m == 0)
	{
		printf("no record!\n");
		return;
	}
	
    printf("please input the number:");
    scanf("%d",&snum);
	
    for(i = 0; i < m; i++)
	{
        if(snum == stu[i].num)//找到该工号
        { 
	        printf("find the staff,show?(y/n)");
            scanf("%s",ch);
		
            if(strcmp(ch,"Y") == 0 || strcmp(ch,"y") == 0) 
            {
                printf("number  name          age   time   salary\t\n");
                printf(FORMAT,DATA);//输出信息，参数宏定义
	            break;
            }
        }
	}	 
    if(i == m)//没有找到该工号
	{
        printf("can not find the staff!\n");
	}
}

/*
*插入一个员工工号
*/ 
  
void insert()
{ 
    FILE *fp;
    int i,j,k,m = 0,snum,snum1;
	
    if((fp=fopen("data.txt","r+")) == NULL)
    {
		printf("can not open\n");
		return;
    }
    while( !feof(fp) )
	{		
        if(fread(&stu[m],LEN,1,fp) == 1)
	    {
		    m++;
	    }
	}
    if(m == 0) 
	{
	    printf("no record!\n");
        fclose(fp);
        return;
    }
	
    printf("please input position where do you want to insert!(input the number)\n");
    scanf("%d",&snum);
	
    for(i = 0; i < m; i++)
	{
	    if(snum == stu[i].num)//找到要插入工号的位置
		{
		    break;
		}
		
		if(i == m-1)//没有找到插入工号位置
		{
		    printf("not search you want insert position,please input a num again\n");
		    scanf("%d",&snum);
			i = 0;
		}
	}
	for(j = m-1; j > i; j--)//插入一个员工，最后面员工在数组中位置后退一位，即数组下标加一
	{
        stu[j+1] = stu[j];
	}
	
	printf("now please input the new information.\n");
    printf("number:");
	scanf("%d",&snum1);
	
	for(k = 0; k < m; k++)//判断插入工号是否存在
	{
	    if(stu[k].num == snum1)
	    {
	        printf("the number is existing,please input another num:\n");
	        scanf("%d",&snum1);
			k = 0;
	    }
	}
	stu[i+1].num = snum1;//确定没有重复工号，将该工号赋给数组中的元素
	printf("name:");
	scanf("%s",stu[i+1].name);
    printf("age:");
	scanf("%d",&stu[i+1].age);
    printf("time:");
	scanf("%d",&stu[i+1].time);
	printf("salary:");
	scanf("%d",&stu[i+1].salary);
	if((fp = fopen("data.txt","wb")) == NULL)
    { 
        printf("can not open\n");
        return;
    }
	for(k = 0;k <= m; k++)
	{
	    if(fwrite(&stu[k],LEN,1,fp) != 1)//将插入员工一起保存到文件中
        { 
	        printf("can not save!");
	        getchar();
	    }
	}
    fclose(fp);
}
/*
*统计员工数
*/
void total()
{
	FILE *fp;
    int m = 0;
	
    if((fp = fopen("data.txt","r+")) == NULL)
    {
		printf("can not open file or not have staff record\n");
		return;
	}
    while( !feof(fp) )  
	{
	    if(fread(&stu[m],LEN,1,fp) == 1) 
	    {
		    m++;//统计员工数
	    }
	}
    if(m == 0)
	{
		printf("no record!\n");
		fclose(fp);
		return;
	}
    printf("the num are %d staff!\n",m);//输出人数
    fclose(fp);
}
/*
*冒泡排序，工号大的在上
*/
void order()
{  
    FILE *fp;
    struct staff t;
    int i = 0,j = 0,m = 0;
	
    if((fp = fopen("data.txt","r+")) == NULL)
    { 
	    printf("can not open or not have staff record!\n");
        return;
    }
    while( !feof(fp) )
	{		
        if(fread(&stu[m] ,LEN,1,fp) == 1) 
	    {
	        m++;
	    }
	}
    fclose(fp);
	
    if(m == 0) 
    {
	    printf("no record!\n");
	    return;
    }
	
    for(i = 0; i < m-1; i++)//冒泡排序
	{
      for(j = i+1; j < m; j++)//找到最大值，并将最大值放在stu数组下标为0的数组
	  {
        if(stu[i].num < stu[j].num)
        { 
	        t=stu[i];
			stu[i]=stu[j];
			stu[j]=t;
	    }
	  }
	}
	if((fp = fopen("data.txt","wb")) == NULL)
    {
		printf("can not open\n");
		return;
    }
    for(i = 0; i < m; i++)
	{
        if(fwrite(&stu[i] ,LEN,1,fp) != 1)//将排序的数据保存到文本中
        { 
            printf("%s can not save!\n"); 
            getchar();
        }
	}
    fclose(fp);
	show();//调用show函数显示从大到小排序好的工号
    printf("save successfully\n");
}
  
/*
*显示所有员工信息
*/  
  
void show()
{ 
    FILE *fp;
    int i,m = 0;
	
	if((fp = fopen("data.txt","rb")) == NULL)//没有员工信息记录时提示添加员工信息
    {
		printf("not have staff information，please choice 1 input first staff information\n");
		return;
    }
    while( !feof(fp) )
    {
       if(fread(&stu[m],LEN,1,fp) == 1) 
       m++;
    }  
    fclose(fp);
    printf("number  name          age   time   salary\t\n");
    for(i = 0; i < m; i++)
    { 
	    printf(FORMAT,DATA);//输出信息，参数宏定义
    }
}

void help()
{
	printf("choose 1 is input a staff information!\n");
	printf("choose 2 is search a staff information!\n");
	printf("choose 3 is delete a staff information!\n");
	printf("choose 4 is modify a staff information!\n");
	printf("choose 5 is insert a staff information!\n");
	printf("choose 6 is employee information sequencing!\n");
	printf("choose 7 is totle staff number!\n");
	printf("choose 8 is show all staff information!\n");
	printf("choose 9 is check use system help!\n");
	printf("choose 0 is quit system!\n");
}
