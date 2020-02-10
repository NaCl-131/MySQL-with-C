#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include "function.h"
#define username root
#define userpassword 123
FILE *fp1,*fp2,*fp3,*fp4;
char commmand[255];
char databases[80][21];
int u=0;//数据库数量
int w=0;//数据表数量
int n=0;//表内数据数量
int h=0;//数据行数
int i,j;
int drop=0;
int inuse=0;
char tabletouse[80];
char databasesname[80];
//char databasesnamebuf[80];
char tablename[][81];
char data[][20];
char table[][80],type[][20];
void login()//用户名为root,密码为123
{
    printf("C:\\>");
    char log[80];
    char pw[80];
    int i=0;
    gets(log);
    if(strcmp(log,"mysql -u root -q")==0)
    {
        printf("Enter password:");
        while(1)
        {
            pw[i]=getch();
            if((pw[i]!='\r')&&(pw[i]!='\b'))
            {
                printf("*");
            }
            if(pw[i]=='\r')
            {
                break;
            }
            if(pw[i]=='\b')
            {
                printf("\b \b");
                i=i-2;
            }
            i++;
        }
        pw[i]='\0';
        if(strcmp("123",pw)==0)
        {
            printf("\nWelcome to the MySQL monitor.  Commands end with ;\n");
        }
        else
        {
            printf("\nERROR 1045 (28000): Access denied for user \'root\'@\'localhost\' (using password: YES)\n");
        }

    }
    else
    {
        printf("\'%s\' 不是内部或外部命令，也不是可运行的程序或批处理文件。\n",log);
    }
}
void show_databases()
{
    int i=0;
    printf("+--------------------+\n| Database           |\n+--------------------+\n");
    printf("| information_schema |\n| mysql              |\n| performance_schema |\n| sakila             |\n| sys                |\n| world              |\n");
    for(; i<u; i++)
    {
        printf("| %-19s|\n",databases[i]);

    }
    printf("+--------------------+\n");
}
void create_database()
{
	printf("Please input database name:\n");
    char database[20]= {0};
    gets(database);
    strcpy(databases[u++],database);
    reference();
    printf("OK!\n");
}
void drop_database()
{
    int i;
    int drop=0;
    char database[20]= {0};
    gets(database);
    for(i=0; i<u; i++)
    {
        if(strcmp(database,databases[i])==0)
        {
            drop=1;
            break;
        }
    }
    if(drop==0)
        printf("error!");
    else
    {
        for(; i<u; i++)
        {
            strcpy(databases[i],databases[i+1]);
        }
        u--;
    }
    reference();
}
void drop_tablename()
{
    printf("Please input table name:\n");
    int i;
    int drop=0;
    char table[20]= {0};
    gets(table);
    for(i=0; i<w; i++)
    {
        if(strcmp(table,tablename[i])==0)
        {
            drop=1;
            break;
        }
    }
    if(drop==0)
        printf("error!");
    else
    {
        for(; i<u; i++)
        {
            strcpy(tablename[i],tablename[i+1]);
        }
        w--;
    }
    reference_tablename();
}
void use()
{
    int i;
    int y=0;
    printf("Please input the databases name:\n");
    gets(databasesname);
    //strcpy(databasesnamebuf,databasesname);
    for(i=0; i<u; i++)
    {
        if(strcmp(databasesname,databases[i])==0)
        {
            y=1;
            break;
        }
    }
    if(y==0)
        printf("error!");
    else
    {
        strcat(databasesname,".txt\0");
        //fp2=fopen(databasesname,"a+");
        inuse=1;
        printf("database changed\n");
    }
    scan_tablename();
}
void create_table()
{
    int have=0,i=0;
    int fin =0;
    char tab[80]= {0},lei[10]= {0},tablenamebuf[80];
    printf("Please input table name:\n");
    gets(tablenamebuf);
    scan_tablename();
    for(; i<w; i++)
    {
        if(tablenamebuf==tablename[i])
        {
            have=1;
            break;
        }
    }
    if(have==1)
    {
        printf("Table already exists\n");
        exit(0);
    }
    else
    {
        fp1=fopen(databasesname,"a");
        fprintf(fp1,"%s\n",tablenamebuf);
        strcat(tablenamebuf,".txt\0");
        fp2=fopen(tablenamebuf,"a");
    }
    printf("Please input name and type:\n(use \" \"to divide and use \";\"to end.)\n");
    while(1)
    {

        scanf("%s %s",tab,lei);
        int i=0,j=0;
        while(lei[i])
        {
            if(lei[i]==';')
            {
                fin=1;
                //printf("===lei==");
            }
            i++;
        }
        if(fin==0)
        {
            fprintf(fp2,"%s %s\n",tab,lei);
        }
        if(fin==1)
        {
            lei[i-1]='\0';
            fprintf(fp2,"%s %s\n",tab,lei);
            printf("OK!");
            break;
        }
    }
}
void show_tables()
{
    int i;
    scan_tablename();
    printf("+-------------------------+\n");
    printf("|Table_in_%-16s|\n",databasesname);
    printf("+-------------------------+\n");
    for(i=0; i<w; i++)
    {
        printf("|%-25s|\n",tablename[i]);
    }
    printf("+-------------------------+\n");
}
void alter_table()
{
//    scanf()
    printf("Please input table name:\n");
    gets(tabletouse);
    //printf("==%s==",tabletouse);
    scan_tablename();
    scan_table();
    for(i=0; i<=w; i++)
    {
        if(strcmp(tablename[i],tabletouse)==0)
        {
            printf("find the table\n");
            break;

        }
    }
    if(i>w)
    {
        printf("Do not find the table\n");
        exit(0);
    }

    printf("Please input your command:\n");
    gets(commmand);
   // printf("command=%s",commmand);
    if(strcmp("drop",commmand)==0)
    {
        printf("Please input the name:\n");
        char namebuf[80];
        gets(namebuf);
        for(i=0; i<n; i++)
        {
            if(strcmp(namebuf,table[i])==0)
            {
                drop=1;
                break;
            }
        }
        if(drop==0)
            printf("error!");
        else
        {
            for(; i<n; i++)
            {
                strcpy(table[i],table[i+1]);
            }
            n--;
        }
        reference_table();
    }

    if(strcmp("modify",commmand)==0)
    {
        printf("Please input the table and type:\n");
        char tablebuf[20],typebuf[20];
        scanf("%s %s",tablebuf,typebuf);
        for(i=0; i<n; i++)
        {
            if(strcmp(tablebuf,table[i])==0)
            {
                drop=1;
                break;
            }
        }
        if(drop==0)
            printf("error!");
        else
        {
            strcpy(type[i],typebuf);
        }
    }
    if(strcmp("add",commmand)==0)
    {
        printf("Please input new name and new type:\n");
        printf("PS:如果原来表中有数据将被全部清除\n");
        char newname[80],newtype[20];
        scanf("%s %s",newname,newtype);
        //printf("%s %s",newname,newtype);
        printf("Input first or after:\n");
        char com[20];
        gets(com);
        gets(com);
        //printf("com=%s",com);
//       gets(com);
        //      printf("哈哈哈哈哈哈哈哈哈");
        if(strcmp(com,"first")==0)
        {

            for(i=n; i>=0; i--)
            {
                strcpy(table[i+1],table[i]);
                strcpy(type[i+1],type[i]);
            }
            strcpy(table[0],newname);
            strcpy(type[0],newtype);
            n++;
            reference_table();
            delete_form();
        }
        else if(strcmp("after",com)==0)
        {
            printf("input the name:\n");
            char buf[80];
            gets(buf);
            for(i=0; i<n; i++)
            {

                if(strcmp(buf,table[i])==0)
                {
                    break;
                }
            }
            for(j=n; j>=i+1; j--)
            {
                strcpy(table[j+1],table[j]);
                strcpy(type[j+1],type[j]);
            }
            strcpy(table[i+1],newname);
            strcpy(type[i+1],newtype);
            n++;
            reference_table();
            delete_form();
        }
        else
        {
            printf("error\n");
        }
    }
}
//华农自科小小刘 
void insert_into()
{
    char buff[50];
    printf("Please input table name:\n");
    gets(tabletouse);
    //strcpy(buff,databasesnamebuf);
    strcpy(buff,tabletouse);
    strcat(buff,"_data.txt");
    fp4=fopen(buff,"a");
    if(fp4==NULL) printf("error");
    printf("Please input data:\n(use \" \" to divide.use \";\" to end)\n");
    char buf[255];
    int end=0;
    while(1)
    {
        scanf("%s",buf);
        for(i=0; i<strlen(buf); i++)
        {
            if(buf[i]==';')
            {
                buf[i]='\0';
                fprintf(fp4,"%s\n",buf);
                end=1;
                break;
            }
        }
        if(end==0)
        {
            fprintf(fp4,"%s\n",buf);
        }
        if(end==1){
        printf("OK!\n");
        fclose(fp4);
        break;}

    }
}
void select()
{
    printf("Please input table name：\n");
    gets(tabletouse);
    scan_data();
    scan_table();
    //for(i=0;i<h;i++)
    //printf("==%s==\n",data[i]);
    int j;
   /* for(i=0;i<h;i++)
    {
        for(j=0;j<strlen(data[i]);j++)
        {
            if(data[i][j]==' ')
            {
                data[i][j]='|';
            }
        }
       // printf("===%s===",data[i]);
    }*/
    //printf("|");
     for(i=0;i<n;i++)
     {
         printf("+---------");
     }
     printf("+\n");
    for(i=0;i<n;i++)
    {
        printf("|%-10s",table[i]);
    }
    printf("|\n");
     for(i=0;i<n;i++)
     {
         printf("+---------");
     }
     printf("+\n");
    for(i=0;i<h;i++)
    {
         printf("|%-10s",data[i]);
         if((i+1)%n==0&&i!=0)
        {
        	printf("|\n");
        }
    }
     for(i=0;i<n;i++)
     {
         printf("+---------");
     }
     printf("+\n");

}
void update()
{
    printf("Please input table name:\n");
    gets(tabletouse);
    //strcpy(buff,databasesnamebuf);
    //strcpy(buff,tabletouse);
   // strcat(buff,"_data.txt");
    scan_data();
    scan_table();
    printf("Please input where you want to update:\n");
    char where[20],what[20];
    gets(where);
    strcpy(what,strchr(where,'=')+1);
    where[strlen(where)-strlen(what)-1]='\0';
    printf("%s\n",where);
    for(i=0; i<h; i++)
    {
        if(strcmp(what,data[i])==0)
        {
            printf("=====OK====\n");
            break;
        }
    }
    int p;
    for(p=0; p<n; p++)
    {
        printf("test\n");
        if(strcmp(where,table[p])==0)
        {
            printf("=====OK2====\n");
            break;
        }
    }
     printf("Please input what you want to update:\n");
    char change[80],changewhat[80];
    gets(change);
    strcpy(changewhat,strchr(change,'=')+1);
    change[strlen(change)-strlen(changewhat)-1]='\0';
   printf("%s %s \n",change,changewhat);
    int k;
    for(k=0; k<n; k++)
    {
        if(strcmp(change,table[k])==0)
        {
            //printf("=====OK3=====\n");
            break;
        }
    }

    //printf("i=%d j=%d k=%d",i,j,k);
    strcpy(data[i+k-j],changewhat);
     printf("num=%d %s\n",i+k-j,data[i+k-j]);
    for(i=0; i<h; i++)
    {
        printf("%s\n",data[i]);
    }
   // getch();
   reference_data();
}
void delete_form()
{
    char buff[50];
    printf("Please input table name:\n");
    gets(tabletouse);
    //strcpy(buff,databasesnamebuf);
    strcpy(buff,tabletouse);
    strcat(buff,"_data.txt");
    fp4=fopen(buff,"w");
    if(fp4==NULL) printf("error");
    fprintf(fp4,"\0");
}
void describe()
{
	printf("Please input table name:\n");
    gets(tabletouse);
    // strcat(tabletouse,".txt");
    scan_table();
    printf("+-----------+--------------+\n");
    printf("| Field     | Type         |\n+-----------+--------------+\n");
    for( i=0; i<n; i++)
    {
        printf("| %-10s| %-13s|\n",table[i],type[i]);
    }
    printf("+-----------+--------------+\n");
}
void scan()
{
    u=0;
    char buff[255];
    while (!feof(fp1))//数据库读取
    {
        fgets(buff,255,fp1);
        int ln = 0;
        ln=strlen(buff);
        buff[ln-1]='\0';
        strcpy(databases[u], buff);
        // printf("===%s===",databases[u]);
        u++;
    }
    u--;
    fclose(fp1);
}
void scan_tablename()
{
    // printf("IN");
    fp2=fopen(databasesname,"r+");
    w=0;
    char buff[255];
    while (!feof(fp2))
    {
        fgets(buff,255,fp2);
        //printf("==ININ==");
        int ln = 0;
        ln=strlen(buff);
        buff[ln-1]='\0';
        strcpy(tablename[w], buff);
        // printf("%s",tablename[w]);
        w++;
    }
    w--;
     fclose(fp2);
}
void scan_table()
{
    char buff[255];
    n=0;
    //printf("Test");
    char buf[40];
    //strcpy(buf,databasesnamebuf);
    strcpy(buf,tabletouse);
    strcat(buf,".txt\0");
    //printf("==%s",buf);
    fp3=fopen(buf,"r+");
    //fp2=fopen(databasesname,"w");
    while (!feof(fp3))
    {
        fgets(buff, 255,fp3);
        //       printf("Test");
        int ln = 0, lt;
        strcpy(table[n], buff);//保存已读取信息
        ln = strlen(table[n]);
        strcpy(type[n], (strchr(table[n], ' ')+1));//字符串分离
        lt=strlen(type[n]);
        type[n][lt-1]='\0';
        table[n][ln - lt-1] = '\0';//字符串分隔
        //printf("===%s====%s===",table[n],type[n]);
        n++;
    }
    n--;
     fclose(fp3);
}
void scan_data()
{
	h=0;
    char buf[82],buff[255];
    strcpy(buf,tabletouse);
    strcat(buf,"_data.txt");
    fp4=fopen(buf,"r");
    int ln = 0;
    while(!feof(fp4))
    {
        fgets(buff,255,fp4);
        ln=strlen(buff);
        buff[ln-1]='\0';
        strcpy(data[h], buff);
        //printf("==%s==\n",data[h]);
        h++;
    }
    h--;
    fclose(fp4);
}
void reference()
{
    fp1=fopen("databases.txt","w");
    int i;
    for (i = 0; i < u; i++)
    {
        fprintf(fp1, "%s\n", databases[i]);
    }
    fclose(fp1);
}
void reference_data()
{
	char buf[20];
    strcpy(buf,tabletouse);
    strcat(buf,"_data.txt");
    fp4=fopen(buf,"w");
    for (i = 0; i < h; i++)
    {
        fprintf(fp4, "%s\n", data[i]);
    }
    fclose(fp4);
}
void reference_tablename()
{
    fp2=fopen(databasesname,"w");
    int i;
    for (i = 0; i < w; i++)
    {
        fprintf(fp2, "%s\n", tablename[i]);
    }
    fclose(fp2);
}
void reference_table()
{
    char buf[40];
   // strcpy(buf,databasesnamebuf);
    strcpy(buf,tabletouse);
    strcat(buf,".txt\0");
    fp3=fopen(buf,"w");
    int i;
    for (i = 0; i < n; i++)
    {
        fprintf(fp3, "%s %s\n",table[i],type[i]);
       // printf("%s %s\n",table[i],type[i]);
    }
    fclose(fp3);
}
void Exit()
{
    printf("mysql>bye");
    exit(0);
}

int main()
{
	login();
    fp1=fopen("databases.txt","r+");
    scan();
    while(1)
    {
        fp1=fopen("databases.txt","r+");
        printf("mysql>");
        gets(commmand);
        if(strcmp("exit",commmand)==0)
        {
            Exit();
        }
        else if(strcmp("show",commmand)==0)
        {
            show_databases();
        }
        else if(strcmp("create",commmand)==0)
        {
            create_database();
        }
        else if(strcmp("drop",commmand)==0)
        {
            drop_database();
        }
        else if(strcmp("use",commmand)==0)
        {
            use();
        }
        else if(strcmp("create table",commmand)==0&&inuse==1)
        {
            create_table();
        }
        else if(strcmp("describe",commmand)==0&&inuse==1)
        {

            describe();
        }
        else if(strcmp("drop table",commmand)==0&&inuse==1)
        {
            drop_tablename();
        }
        else if(strcmp("alter",commmand)==0&&inuse==1)
        {
            alter_table();
        }
        else if(strcmp("show tables",commmand)==0&&inuse==1)
        {
            show_tables();
        }
        else if(strcmp("insert",commmand)==0&&inuse==1)
        {
            insert_into();
        }
        else if(strcmp("select",commmand)==0&&inuse==1)
        {
            select();
        }
         else if(strcmp("update",commmand)==0&&inuse==1)
        {
            update();
        }
        else if(strcmp("delete",commmand)==0&&inuse==1)
        {
        	delete_form();
        }
        else
        {
            printf("error!\n");
        }
    }
}
