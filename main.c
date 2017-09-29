/*
 *Created by TRUNGDT
 * 29/09/2017.
 * Version x.x.x
*/
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

struct GoStudents {      //Khai báo cấu trúc sinh viên
    char Name[100];
    char DateofBirth[100];
    char PhoneNumber[100];
    char ID[100];
};
typedef struct GoStudents Students;// Gán cấu trức GoStudents thành kiểu dữ liệu SinhVien
Students sv[100];//Khai báo mảng sv ghi thông tin số lương sinh viên
int n; //số lượng sinh viên
unsigned int leng;
int counter;
int x;
//Kiem tra ID da ton tai hay chua.
bool checkExistID(char a[], int k) {
    for (int i = 0; i < k; i++) {
        if (strcmp(sv[i].ID, a) == 0) {
            printf("ID is existed.Please enter different ID\n");
            return true;
        }
    }
    return false;
}

//Check vị trí của ID vừa khai báo
int checkIndexID() {
    char buffer[100];
    int i;
    do {
        printf("Please enter ID to edit/delete:\n");
        fgets(buffer, 100, stdin);
        for (i = 0; i < (n + counter); i++) {
            if (strcmp(sv[i].ID, buffer) == 0)//Thực hiện vòng lặp so sáng giá trị ID từ 0->n so với giá trị a là ID nhập vào
                return i;
        }
        printf("ID is not exist!!!\n");
    } while (strcmp(sv[i].ID, buffer) != 0);
}

void checkName(int a) {//Check độ dài tên
    if (a - 1 < 3)
        printf("Name student is too short. Name student have to larger than 3 characters\n");
    else if (a - 1 > 15)
        printf("Name student is too long. Name student have to smaller than 15 characters\n");
}

void WriteFile() {
    FILE *pt;
    if(counter == 0)//mở file với chế độ ghi khi file đang trắng
        pt=fopen("E:\\C-semester1\\INPUT.txt", "w");
    else
        pt = fopen("E:\\C-semester1\\INPUT.txt", "a");//mở file khi file có sẵn dữ liệu, áp dụng khi mở file lần chạy compile sau
    for (int i = counter; i <  n + counter; i++) {
        fputs("\n", pt);
        fputs(sv[i].ID, pt);
        fputs(sv[i].Name, pt);
        fputs(sv[i].DateofBirth, pt);
        fputs(sv[i].PhoneNumber, pt);
    }
    counter+=n;//Nhập n sau lần compile đầu tiên sẽ cộng với counter ra tổng số sinh viên đã có.
    fclose(pt);
}

void ReadFile() {
    char buffer[100];
    int k;
    counter=0;//Đọc lại file từ đầu đến cuối.
    FILE *pt;
    pt = fopen("E:\\C-semester1\\INPUT.txt", "r");
    for(k = 0; fgets(buffer,100, pt); k++){
        printf("Student information number %d\n", k+1);
        printf("Student ID: ");
        fgets(sv[k].ID, 100, pt);
        printf("%s", sv[k].ID);
        printf("Name of Student: ");
        fgets(sv[k].Name, 100, pt);
        printf("%s", sv[k].Name);
        printf("Date of Birth: ");
        fgets(sv[k].DateofBirth, 100, pt);
        printf("%s", sv[k].DateofBirth);
        printf("Phone number: ");
        fgets(sv[k].PhoneNumber, 100, pt);
        printf("%s\n", sv[k].PhoneNumber);
        counter++;//khi mở file lúc đóng compile phần mềm đếm lên để khi nhập mới sẽ điên vào nối tiếp file.
    }
    fclose(pt);
}


void AddListStudents() {
    char buffer[100];
    printf("Please enter number of students:\n");
    scanf("%d", &n);
    getchar();
    for (int i = counter; i < (n + counter); i++) {//(n + counter): duyệt số phần từ sau lần chạy compile sau
        printf("Student information number %i\n", i + 1);
        int k = 1;  //Kiem tra dieu kien thuc hien vong lap
        do {
            printf("Please enter student ID:(Number type)\n");
            fgets(buffer, 100, stdin);
            if (checkExistID(buffer, i) == false) {
                strcpy(sv[i].ID, buffer);
                k--;// k=0 trả về false, thoát vòng lặp.
            }
        } while (k);
        do {
            printf("Please enter student name\n");
            fgets(sv[i].Name, sizeof(sv[i].Name), stdin);
            leng = strlen(sv[i].Name);
            checkName(leng);
        } while (leng - 1 > 15 || leng - 1 < 3);
        printf("Please enter date of birth:\n");
        fgets(sv[i].DateofBirth, sizeof(sv[i].DateofBirth), stdin);
        printf("Please enter phone number:\n");
        fgets(sv[i].PhoneNumber, sizeof(sv[i].PhoneNumber), stdin);
    }
    WriteFile();
}

void EditStudents() {
    printf("Edit Student Information\n");
//    printf("Please enter ID to edit:\n");
//    fgets(buffer, 100, stdin);//Gõ ID cần sửa
    int k = checkIndexID();//Gọi hàm để check vị trí index cần sửa
    printf("Edit Name Student:\n");
    do {
        fgets(sv[k].Name, sizeof(sv[k].Name), stdin);//checkIndexID(buffer) là giá trị index hàm trả về
        leng = strlen(sv[k].Name);
        checkName(leng);//Check độ dài tên
    } while (strlen(sv[k].Name) - 1 > 15 || strlen(sv[k].Name) - 1 < 3);
    printf("Edit Date of Birth:\n");
    fgets(sv[k].DateofBirth, sizeof(sv[k].DateofBirth), stdin);
    printf("Edit Phone number:\n");
    fgets(sv[k].PhoneNumber, sizeof(sv[k].PhoneNumber), stdin);
    n = counter;//Gán giá trị đếm cho n rồi chuyển counter về 0 dể thực hiện vòng lặp ghi file từ khi counter =0.
    counter = 0 ;
    WriteFile();
}

void DeleteStudent() {//Khai báo biến tạm để nhập ID sinh viên
    printf("Delete Student\n");
    int k = checkIndexID();//gọi hàm check vị trí trong mảng của ID sinh viên vừa tạoThực hiện vòng lặp chèn vị trí sinh viên cần xóa bằng vị trí sau nó
    n = counter;
    counter = 0;
    for(k; k < n; k++) {
        sv[k] = sv[k + 1];
    }
    n--;
    WriteFile();
}


/*void TIM_KIEM_THEO_TEN(Students sv[], char ten[100]) {
    int k = 0;
    for (int i = 0; i < n; i++) {
        if (strcmp(sv[i].Name, ten) == 0) {
            printf("Thong tin sinh vien thu %d\n", i + 1);
            printf("Ho ten sinh vien %s\n", sv[i].Name);
            printf("Ngay sinh sinh vien %s\n", sv[i].DateofBirth);
            printf("So dien thoai sinh vien %s\n", sv[i].PhoneNumber);
            k=1;
        }
    }
    if (k == 0)
        printf("Khong tim thay sinh vien\n");*/

choice() {
    while (true) {
        char option;
        printf("\n==============MENU============\n");
        printf("1.Add List Students\n");
        printf("2.Review List Students\n");
        printf("3.Edit Student Information\n");
        printf("4.Delete Student\n");
        printf("5.Exit\n");
        printf("-------------------------------\n");
        printf("Please enter your choice(1-->5): \n");
        scanf("%s", &option);
        getchar();//Xoa bo ki tu NULL khi bam enter xuong dong
        switch (option) {
            case '1':
                printf("Add List Students\n");
                AddListStudents();
                break;
            case '2':
                printf("Review List Students\n");
                ReadFile();
                break;
            case '3':
                EditStudents();
                break;
            case '4':
                DeleteStudent();
                break;
/*            case '5':
                printf("Tim kiem sinh vien\n");
                printf("Nhap gia tri tim kiem\n");
                scanf(" %s", ten);
                TIM_KIEM_THEO_TEN(sv, ten);*/
                break;
            case '5':
                break;
            default:
                printf("Please enter your choice again(Number from 1 to 5)\n");
                break;
        }
        if (option == '5')
            break;
    }
}

void main() {
    choice();
}