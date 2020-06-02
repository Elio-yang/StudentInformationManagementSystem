#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct MyStu MyStudent;
typedef struct node Node;
typedef Node *pNode;

struct MyStu {
    char name [20];
    int age;
    long ID;
    double score;
};

struct node {
    MyStudent student;
    pNode next;
};

static pNode head = NULL;

/***********FUNCTION***********/
void InputStudentInformation();

void PrintStudentInformation();

void SaveStudentInformation();

void ReadStudentInformation();

int CountStudentNumber();

pNode FindStudent();

pNode FinePrevious(pNode Cur);

void ModifyStudentInformation();

void DeleteStudentInformation();

void Menu();

void KeyDown();

void SubMenu();

/***********FUNCTION***********/

#define PATH "DATA.txt"

int main() {
    for (;;) {
        Menu();
        KeyDown();
        system("pause");
        system("cls");
    }
    return 0;
}

void Menu() {
    printf("********************************************************\n");
    printf("==============欢迎使用高校学生成绩管理系统==============\n");
    printf("\t=============请选择功能列表==============\n");
    printf("\t**************1.录入学生信息**************\n");
    printf("\t**************2.输出学生信息**************\n");
    printf("\t**************3.统计学生人数**************\n");
    printf("\t**************4.查找学生信息**************\n");
    printf("\t**************5.修改学生信息**************\n");
    printf("\t**************6.删除学生信息**************\n");
    printf("\t**************0.退 出 系 统**************\n");
    printf("********************************************************\n");
}

void KeyDown() {
    int choice;
    printf("Function to chose (0~6):\n");
    scanf("%d", &choice);
    switch (choice) {
        case 1:
            InputStudentInformation();
            SaveStudentInformation();
            break;
        case 2:
            PrintStudentInformation();
            break;
        case 3:
            printf("Total students is %d\n", CountStudentNumber());
            break;
        case 4:
        {
            pNode Find = FindStudent();
            if (Find != NULL) {
                printf("NUM:%ld\tNAME:%s\tAGE:%d\tSCORE:%lf",
                       Find->student.ID,
                       Find->student.name,
                       Find->student.age,
                       Find->student.score);
            }
            break;
        }
        case 5:
            ModifyStudentInformation();
            SaveStudentInformation();
            break;
        case 6:
            DeleteStudentInformation();
            SaveStudentInformation();
            break;
        case 0:
            printf("Welcome to use again!");
            exit(0);
        default:
            printf("Invalid Input!");
            break;
    }
}

void InputStudentInformation() {
    pNode NewNode = (pNode)malloc(sizeof(Node));
    if (head==NULL) {
        head = (pNode)malloc(sizeof(Node));
        head->next = NewNode;
        NewNode->next = NULL;
    }
    else {
        pNode tmp = head->next;
        head->next = NewNode;
        NewNode->next = tmp;
    }
    printf("Name:\n");
    scanf("%s", NewNode->student.name);
    printf("NUM:\n");
    scanf("%ld", &NewNode->student.ID);
    printf("AGE:\n");
    scanf("%d", &NewNode->student.age);
    printf("SCORE:\n");
    scanf("%lf", &NewNode->student.score);
    printf("DONE");
}

void PrintStudentInformation() {
    system("cls");
    printf("********************************************************\n");
    printf("==============欢迎使用高校学生成绩管理系统==============\n");
    printf("********************************************************\n");
    pNode tmp = head->next;
    while (tmp != NULL) {
        printf("NUM:%ld\tNAME:%s\tAGE:%d\tSCORE:%lf\n",
               tmp->student.ID,
               tmp->student.name,
               tmp->student.age,
               tmp->student.score);
        tmp = tmp->next;

    }
}

void SaveStudentInformation() {
    FILE *fp = fopen(PATH, "w+");
    if (!fp) {
        printf("FAIL");
        exit(0);
    }
    pNode tmp;
    tmp = head->next;
    while (tmp != NULL) {
        fwrite(&tmp->student, sizeof(Node), 1, fp);
        tmp = tmp->next;
    }
    fclose(fp);
    printf("SAVE DONE!");
}

void ReadStudentInformation() {
    FILE *read = fopen(PATH, "r");
    if (!read) {
        printf("FAIL");
        exit(0);
    }
    MyStudent stu;
    while (fread(&stu, sizeof(MyStudent), 1, read)) {
        pNode tmp = (pNode)malloc(sizeof(Node));
        memcpy(tmp, &stu, sizeof(MyStudent));
        if (head->next == NULL) {
            head->next = tmp;
            tmp->next = NULL;
        }
        else {
            pNode tmp_ = head->next;
            head->next = tmp;
            tmp->next = tmp_;
        }
    }
    fclose(read);
    printf("LOAD DONE!");
}

int CountStudentNumber() {
    int cnt = 0;
    pNode tmp;
    tmp = head->next;
    while (tmp != NULL) {
        cnt++;
        tmp = tmp->next;
    }
    return cnt;
}


pNode FindStudent() {
    printf("Enter student ID:\n");
    long id_f;
    scanf("%ld", &id_f);
    pNode tmp;
    tmp = head->next;
    while (tmp != NULL) {
        if (tmp->student.ID == id_f) {
            return tmp;
        }
        tmp = tmp->next;
    }
    printf("ERROR ID! \n");
    return NULL;
}
pNode FinePrevious(pNode Cur) {
    pNode tmp;
    tmp = head;
    while (tmp != NULL) {
        if (tmp->next == Cur) {
            return tmp;
        }
        tmp = tmp->next;
    }
    return NULL;
}


void ModifyStudentInformation() {
    pNode Find = FindStudent();
    if (Find == NULL) {
        printf("ID ERROR!");
        return;
    }
    SubMenu();
    char ch;
    scanf("%c", &ch);
    switch (ch) {
        case 'a':
            printf("Enter new name:\n");
            scanf("%s", Find->student.name);
            printf("MODIFY DONE!\n");
            break;
        case 'b':
            printf("Enter new ID:\n");
            scanf("%ld", &Find->student.ID);
            printf("MODIFY DONE!\n");
            break;
        case 'c':
            printf("Enter new age:\n");
            scanf("%d", &Find->student.age);
            printf("MODIFY DONE!\n");
            break;
        case 'd':
            printf("Enter new score:\n");
            scanf("%lf", &Find->student.score);
            printf("MODIFY DONE!\n");
            break;
        case 'q':
            printf("Welcome to using this system again!");
            break;
        default:
            printf("Invalid Input");
            break;
    }
}

void DeleteStudentInformation() {
    pNode Cur = FindStudent();
    if (Cur == NULL) {
        return;
    }
    pNode Prev = FinePrevious(Cur);
    if (Cur->next == NULL) {
        Prev->next = NULL;
        free(Cur);
    }
    else {
        pNode tmp = Cur->next;
        Cur->next = NULL;
        Prev->next = tmp;
        free(Cur);
    }

}


void SubMenu() {
    printf("********************************************************\n");
    printf("==============欢迎使用高校学生成绩管理系统==============\n");
    printf("\t=============请选择功能列表==============\n");
    printf("\t**************a.修改姓名**************\n");
    printf("\t**************b.修改学号**************\n");
    printf("\t**************c.修改年龄**************\n");
    printf("\t**************d.修改成绩**************\n");
    printf("\t**************q.退出系统**************\n");
    printf("********************************************************\n");
}