#include"all.h"
#define LEN sizeof(struct student)
#define GESHI "%-8d%-15s%-12.1lf%-12.1lf%-12.1lf%-12.1lf\n"
#define DATA stu[i].num,stu[i].name,stu[i].xuanxiu,stu[i].shiyan,stu[i].bixiu,stu[i].sum
struct student{
        int num;
        char name[11];
        double xuanxiu;
        double shiyan;
        double bixiu;
        double sum;
};
struct student stu[50];
void menu(){
        system("clear");
        printf("\n\n\n\n");
        printf("\t\t|-------------------STUDENT-------------------|\n");
        printf("\t\t|\t 0.exit                               |\n");
        printf("\t\t|\t 1.input record                       |\n");
        printf("\t\t|\t 2.search record                      |\n");
        printf("\t\t|\t 3.delete record                      |\n");
        printf("\t\t|\t 4.modify record                      |\n");
        printf("\t\t|\t 5.insert record                      |\n");
        printf("\t\t|\t 6.order                              |\n");
        //printf("\t\t|\t 7.number                             |\n");
        printf("\t\t|---------------------------------------------|\n");
        printf("\t\t\t choose(0-7):\n");
}
void show(){
        FILE *fp;
        int i = 0,m = 0;
        fp = fopen("data.txt","rb");
        while(!feof(fp)){
                if(fread(&stu[m],LEN,1,fp) == 1){
                        m++;
                }
        }
        fclose(fp);
        for(i;i<m;i++){
                printf("学号    姓名          选修课成绩  实验课成绩  必修课成绩  总成绩\n");
                printf(GESHI,DATA);
        }
}
void input(){
         int i = 0;
         int m = 0;
         char choose[2];
         FILE *fp;
         if((fp = fopen("data.txt","a+")) == NULL){
                 printf("文件不存在\n");
                 return;
         }
         while(!feof(fp)){
                 if(fread(&stu[m],LEN,1,fp) == 1){
                         m++;
                 }
         }
         fclose(fp);
         if(m==0){
                 printf("文件中没有记录\n");
         }
         else{
                 show();
         }
         if((fp = fopen("data.txt","ab")) == NULL){
                 printf("文件不存在\n");
                 return;
         }
         printf("输入学生信息?(y/n):\n");
         scanf("%s",choose);
         while(strcmp(choose,"Y") == 0 || strcmp(choose,"y") == 0){
                 printf("pls input number\n");
                 scanf("%d",&stu[m].num);
                 for(i;i<m;i++){
                         if(stu[i].num == stu[m].num){
                                 printf("学号已经存在\n");
                                 fclose(fp);
                                 return;
                         }
                 }
                 printf("name:\n");
                 scanf("%s",stu[m].name);
                 printf("选修课成绩:\n");
                 scanf("%lf",&stu[m].xuanxiu);
                 printf("必修课成绩:\n");
                 scanf("%lf",&stu[m].bixiu);
                 printf("实验课成绩:\n");
                 scanf("%lf",&stu[m].shiyan);
                 stu[m].sum = stu[m].xuanxiu + stu[m].bixiu + stu[m].shiyan;
                 if(fwrite(&stu[m],LEN,1,fp) != 1){
                         printf("不能保存喵\n");
                 }
                 else{
                         printf("%s被保存\n",stu[m].name);
                         m++;
                 }
                 printf("继续?(y/n):\n");
                 scanf("%s",choose);
         }
         fclose(fp);
         printf("OK\n");
}
void search(){
        FILE *fp;
        int num = 0;
        int i = 0;
        int m = 0;
        char choose[2];
        strcpy(choose,"y");
        if((fp = fopen("data.txt","rb")) == NULL){
                printf("文件不存在\n");
                return;
        }
        while(!feof(fp)){
                if((fread(&stu[m],LEN,1,fp)) == 1){
                        m++;
                }
        }
                fclose(fp);
                if(m == 0){
                        printf("文件中没有记录\n");
                        return;
                }
                while(strcmp(choose,"y") == 0||strcmp(choose,"Y") == 0){
                        system("clear");
                        num = 0;
                        i = 0;
                        printf("请输入number:\n");
                        scanf("%d",&num);
                        for(i;i<m;i++){
                                if(stu[i].num == num){
                                        printf("学号    姓名          选修课成绩  实验课成绩  必修课成绩  总成绩\n");
                                        printf(GESHI,DATA);
                                        break;
                                }
                        }
                        if(i == m){
                                printf("没有该学号\n");
                        }
                        printf("coninue?(y/n)\n");
                        scanf("%s",choose);
                }
}
void delete(){
        FILE *fp;
        int num = 0;
        int i = 0;
        int m = 0;
        char choose[2];
        char del_choose[2];
        strcpy(choose,"y");
        if((fp = fopen("data.txt","r+")) == NULL){
                printf("文件不存在\n");
                return;
        }
        while(!feof(fp)){
                if(fread(&stu[m],LEN,1,fp) == 1){
                m++;
                }
        }
        fclose(fp);
        while(strcmp(choose,"y") == 0||strcmp(choose,"Y") == 0){
                printf("请输入学生学号\n");
                scanf("%d",&num);
                i = 0;
                for(i;i<m;i++){
                        if(num == stu[i].num){
                                printf("i find it,你真的要删除吗?(y/n)\n");
                                scanf("%s",del_choose);
                                if(strcmp(del_choose,"y") == 0||strcmp(del_choose,"Y") == 0){
                                        for(int j = i;j<m;j++){
                                                stu[j] = stu[j+1];
                                        }
                                        m--;
                                        fp = fopen("data.txt","wb");
                                        fwrite(stu,LEN,m,fp);
                                        fclose(fp);
                                printf("删除成功\n");
                                break;
                                }
                                else{
                                        printf("好的，不删除\n");
                                        break;
                                }
                        }
                }
                if( i == m){
                        printf("没找到该学生!\n");
                }
                printf("continue?(y/n)\n");
                scanf("%s",choose);
        }
}
void modify(){
        FILE *fp;
        int i = 0,j = 0,m = 0,num = 0;
        char choose[2];
        if((fp = fopen("data.txt","r+")) == NULL){
                printf("文件不存在\n");
                return;
        }
        while(!feof(fp)){
                if(fread(&stu[m],LEN,1,fp) == 1){
                        m++;
                }
        }
        if(m == 0){
                printf("文件中没有记录\n");
                fclose(fp);
                return;
        }
        show();
        while(1){
                printf("请输入要修改的学生学号\n");
                scanf("%d",&num);
                for(i = 0;i<m;i++){
                        if(num == stu[i].num){
                                printf("i find it,开始修改他的信息\n");
                                printf("name:");
                                scanf("%s",stu[i].name);
                                printf("选修课成绩:");
                                scanf("%lf",&stu[i].xuanxiu);
                                printf("实验课成绩:");
                                scanf("%lf",&stu[i].shiyan);
                                printf("必修课成绩:");
                                scanf("%lf",&stu[i].bixiu);
                                printf("修改成功!\n");
                                stu[i].sum = stu[i].xuanxiu + stu[i].shiyan + stu[i].bixiu;
                                fseek(fp,i * LEN,SEEK_SET);
                                if(fwrite(&stu[i],LEN,1,fp) != 1){
                                     printf("不能保存喵\n");
                                }
                                else{
                                         printf("%s保存\n",stu[m].name);
                                }
                                break;
                        }
                }
                if(i == m){
                       printf("没有找到这名学生的学号!\n");
                       break;
                }
                fclose(fp);
                printf("continue?(y/n)\n");
                scanf("%s",choose);
                if(strcmp(choose,"n") == 0||strcmp(choose,"N") == 0){
                        break;
                }
        }
}
void insert(){
        FILE *fp;
        int i = 0, j = 0, k = 0, m = 0, num = 0;
        char choose[2];
        strcpy(choose,"y");
        if((fp = fopen("data.txt","r+")) == NULL){
                printf("文件不存在！\n");
                return;
        }
        while(!feof(fp)){
                if(fread(&stu[m],LEN,1,fp) == 1){
                        m++;
                }
        }
        if(m == 0){
                printf("文件没有记录\n");
                fclose(fp);
                return;
        }
        while(strcmp(choose,"Y") == 0 || strcmp(choose,"y") == 0){
                i=0;
                show();
        printf("请输入要插在哪个学号的同学后面捏\n");
        scanf("%d",&num);
        for(i;i<m;i++){
                if(num == stu[i].num){
                        break;
                }
        }
        if(i == m){
                printf("无该学号的学生!\n");
                continue;
        }
        else{
                for(j = m-1;j>i;j--){
                        stu[j+1] = stu[j];
                }
        }
        printf("输入学生信息\n");
                 printf("pls input number\n");
                 scanf("%d",&stu[i+1].num);
                 for(k = 0;k<m;k++){
                         if(k!=i+1){
                         if(stu[k].num == stu[i+1].num){
                                 printf("学号已经存在\n");
                                 fclose(fp);
                                 return;
                         }
                         }
                 }
                 printf("name:\n");
                 scanf("%s",stu[i+1].name);
                 printf("选修课成绩:\n");
                 scanf("%lf",&stu[i+1].xuanxiu);
                 printf("必修课成绩:\n");
                 scanf("%lf",&stu[i+1].bixiu);
                 printf("实验课成绩:\n");
                 scanf("%lf",&stu[i+1].shiyan);
                 stu[i+1].sum = stu[i+1].xuanxiu + stu[i+1].bixiu + stu[i+1].shiyan;
                 m++;
                 if((fp = fopen("data.txt","wb")) == NULL){
                         printf("不能打开!\n");
                         return;
                 }
                 for(k = 0;k<=m;k++){
                         if(fwrite(&stu[k],LEN,1,fp)!=1){
                                 printf("不能保存！\n");
                         }
                 }
                 fclose(fp);
                 printf("继续?(y/n):\n");
                 scanf("%s",choose);
         }
}
void order(){
        struct student temp;
        FILE *fp;
        int i = 0, j = 0, k = 0, m = 0, num = 0;
        char choose[2];
        strcpy(choose,"y");
        if((fp = fopen("data.txt","r+")) == NULL){
                printf("文件不存在！\n");
                return;
        }
        while(!feof(fp)){
                if(fread(&stu[m],LEN,1,fp) == 1){
                        m++;
                }
        }
        fclose(fp);
        if(m == 0){
                printf("文件没有记录\n");
                return;
        }
        for(i;i<m - 1;i++){
                for(j = i + 1;j<m;j++){
                        if(stu[i].sum < stu[j].sum){
                                temp = stu[i];
                                stu[i] = stu[j];
                                stu[j] = temp;
                        }
                }
        }
        if((fp = fopen("data.txt","wb")) == NULL){
                         printf("文件不存在!\n");
                         return;
                 }
                 for(k = 0;k<m;k++){
                         if(fwrite(&stu[k],LEN,1,fp)!=1){
                                 printf("不能保存！\n");
                         }
                 }
                 fclose(fp);
}
void main(){
        //stu[0].num = -1;
        //strcpy(stu[0].name,"test");
        int n=0;
        while(1){
                menu();
                scanf("%d",&n);
                switch(n){
                        case 1:
                                input();
                                break;
                        case 2:
                                search();
                                break;
                        case 3:
                                delete();
                                break;
                        case 4:
                                modify();
                                break;
                        case 5:
                                insert();
                                break;
                        case 6:
                                order();
                                break;
                        case 0:
                                break;
                        default:
                                printf("输入一个0-7的整数\n");
                                break;

                }
                if(n==0){
                        printf("欢迎下次光临\n");
                        break;
                }
        }
}
