#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <curses.h>
#include <unistd.h>
#define MAX_LEN 20

typedef struct student {
    char name[MAX_LEN];
    long num;
    int year;
    char sex;
    struct student *next;
}list;//学生链表

//获取字符串到指定地址，结果不含换行符
char *s_fgets(char *st,int num){
    char *re_val;
    char *find;
    re_val = fgets(st,num,stdin);
    if(re_val){
        find = strchr(st,'\n');
        if (find)
        {
            *find = '\0';
        }else
            while(getchar() != '\n')
                continue;
    }
    return re_val;
}

//菜单界面
void menu(void) {
    printf("------------------------欢迎来到学生信息管理平台!--------------------------\n");
    printf("                    0.初始化学生信息\n");
    printf("                    1.添加学生信息          \n");
    printf("                    2.删除学生信息\n");
    printf("                    3.检索学生信息\n");
    printf("                    4.查看学生信息\n");
    printf("                    5.帮助文档\n");
    printf("                    6.查看文件中学生信息\n");
    printf("                    7.修改学生信息\n");
    printf("");
    printf("");
    printf("");
    printf("\t\t注：按下9程序退出！\n");
    printf("----------------------------------------------------------------------\n");
    printf("请输入数字(对应你想实现的功能):");
}

//帮助文档
void help(void){
    printf("0.初始化学生信息功能是让使用者标明此学生信息属于哪个班级\n");
    printf("\n按下任意键回到菜单:");
    if (getchar()) {
        system("clear");
        menu();
    }
}

//查看文件中链表内容
void view_in_document(void){
    FILE *fp;
    int ch = 0;
    if ((fp = fopen("student_data.txt", "r")) != NULL) {
        printf("-----------------这是学生信息----------------\n");
        printf("姓名\t学号\t年龄\t性别(f > 女的，m > 男的)\n");
        while ((ch = getc(fp)) != EOF) {
            putchar(ch);
        }
    }
    fclose(fp);
    printf("\n按下任意键回到菜单:");
    if (getchar()) {
        system("clear");
        menu();
    }
}

//查看链表内容
void view_list(list *head){
    list *current = NULL;
    if(head == NULL)
        printf("你没有输入人名！\n");
    else
        printf("-----------------这是学生信息----------------\n");
    printf("姓名\t学号\t年龄\t性别(f > 女的，m > 男的)\n");
    current = head;
    
    while(current != NULL){
        
        printf("%-10s\t%-10ld%d\t%c\n",
               current->name,
               current->num,
               current->year,
               current->sex
               );
        current = current->next;
        
    }
    printf("\n按下任意键回到菜单:");
    if (getchar()) {
        system("clear");
        menu();
    }
}

//初始化学生链表
void ini_student_list(list *head){
    char message[30];
    FILE *fp;
    fp = fopen("student_data.txt", "w");
    printf("请输入这个班级的信息：\n");
    s_fgets(message, 30);
    fprintf(fp, "\t%s\t\n",message);
    printf("录入信息成功！\n");
    fclose(fp);
    printf("按下任意键回到菜单:");
    if (getchar()) {
        system("clear");
        menu();
    }
}

//添加学生信息
list *add_student_message (list *head){
    char input[MAX_LEN];
    list *current, *prev = NULL;
    FILE *fw;
    int i = 0;
    
    if ((fw = fopen("student_data.txt", "a")) != NULL) {
        printf("请输入第一个人的名字：\n");
        while(s_fgets(input,MAX_LEN) != NULL && input[0] != '\0'){
            current = (list *)malloc(sizeof(list));
            if (head == NULL) {
                head = current;
            }
            else {
                
            }
            current->next = NULL;
            strcpy(current->name,input);
            printf("请输入学号：\n");
            scanf("%ld",&current->num);
            printf("请输入年龄：\n");
            scanf("%d",&current->year);
            while (getchar() != '\n') {
                continue;
            }
            printf("请输入性别（f->女，m->男）：\n");
            scanf("%c",&current->sex);
            getchar();
            fprintf(fw, "%s\t%ld\t%d\t%c\n",
                    current->name,
                    current->num,
                    current->year,
                    current->sex);
            printf("请输入第%d个人的名字：\n",i+2);
            prev = current;
            i++;
        }
    }
    fclose(fw);
    printf("录入信息成功！\n");
    printf("按下任意键回到菜单:");
    if (getchar()) {
        system("clear");
        menu();
    }
    return head;
}

//删除学生信息
list *delete_student(list *head){
    list *current = NULL, *temp = NULL;
    int i = 0;
    char arr[MAX_LEN];
    if (head == NULL) {
        printf("目前没有学生信息！");
    }
    current = head;
    printf("请输入要查找学生的姓名:\n");
    s_fgets(arr, MAX_LEN);
    while (current->next != NULL) {
        i++;
        if (strcmp(arr, current->name)) {
            printf("找到了！\n");
            break;
        }
        current = current->next;
    }
    current = head;
    while (i > 2) {
        i--;
        current = current->next;
    }
    temp = current->next;
    current->next = temp->next;
    printf("删除成功！");
    printf("按下任意键回到菜单:");
    if (getchar()) {
        system("clear");
        menu();
    }
    return head;
}

//检索学生信息
list *seek_student(list *head){
    list *current = NULL;
    int i = 0;
    char arr[MAX_LEN];
    
    printf("请输入要查找学生的姓名:\n");
    s_fgets(arr, MAX_LEN);
    while (current->next != NULL) {
        i++;
        if (strcmp(arr, current->name)) {
            printf("找到了！\n");
            printf("%-10s\t%-10ld%d\t%c\n",
                   current->name,
                   current->num,
                   current->year,
                   current->sex
                   );
            break;
        }
        current = current->next;
    }
    printf("按下任意键回到菜单:");
    if (getchar()) {
        system("clear");
        menu();
    }
    return head;
}
//修改学生信息
list *change_student(list *head){
    list *current = NULL;
    int i = 0;
    char arr[MAX_LEN];
    
    printf("请输入要修改学生的姓名:\n");
    s_fgets(arr, MAX_LEN);
    while (current->next != NULL) {
        i++;
        if (strcmp(arr, current->name)) {
            printf("找到了！\n");
            printf("%-10s\t%-10ld%d\t%c\n",
                   current->name,
                   current->num,
                   current->year,
                   current->sex
                   );
            printf("请输入年龄：\n");
            scanf("%d",&current->year);
            printf("请输入学号：\n");
            scanf("%ld",&current->num);
            
            break;
        }
        current = current->next;
    }
    printf("修改成功！\n");
    printf("按下任意键回到菜单:");
    if (getchar()) {
        system("clear");
        menu();
    }
    return head;
}
int main(int argc, char *argv[]){
    int number;
    list *head = NULL;
    system("clear");
    menu();
    while(scanf("%d",&number) == 1){
        getchar();
        switch (number) {
            case 0:
                ini_student_list(head);
                break;
            case 1:
                head = add_student_message(head);
                break;
            case 2:
                head = delete_student(head);
                break;
            case 3:
                head = seek_student(head);
                break;
            case 4:
                view_list(head);
                break;
            case 5:
                help();
                break;
            case 6:
                view_in_document();
                break;
            case 7:
                head = change_student(head);
            case 9:
                exit(EXIT_SUCCESS);
            default:printf("输入有误请再次输入:");
        }
    }
    return 0;
}

