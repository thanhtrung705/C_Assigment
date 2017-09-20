#include <stdio.h>
#include <string.h>
#include <stdbool.h>

struct GoStudents {      //Khai báo cấu trúc sinh viên
    char Name[100];
    char DateofBirth[100];
    char PhoneNumber[100];
    char ID[100];
};
typedef struct GoStudents Students;// Gán cấu trức sinhvien thành kiểu dữ liệu SinhVien
Students sv[100];//Khai báo mảng sv ghi thông tin số lương sinh viên
int n;//số lượng sinh viên
unsigned int leng;

bool checkExistID() {
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (strcmp(sv[j].ID, sv[i].ID)==0) {//Vòng lặp so sáng giữa mảng ID lần lượt để tìm ra giá trị trùng
                printf("ID is exist.Please enter different ID\n");
                return true;//Nếu trùng hàm trả về false thực hiện tiếp nhập lại ID
            }
        }
    }
    return false;//Nếu ktra ok hàm trả về false, kết thúc vòng lặp, chuyển sang nhập thông tin kế tiếp
}
int checkIndexID(char a[]){//Check vị trí của ID vừa khai báo
    for(int i = 0; i<n; i++) {
        if (strcmp(sv[i].ID, a) == 0)//Thực hiện vòng lặp so sáng giá trị ID từ 0->n so với giá trị a là ID nhập vào
            return i;                   //Nếu giá trị bằng 0 trả về i là index của ID đó
    }
}

void checkName(int a){//Check độ dài tên
    if (a - 1 < 3)
        printf("Name student is too short. Name student have to larger than 3 characters\n");
    else if (a - 1 > 15)
        printf("Name student is too long. Name student have to smaller than 15 characters\n");
}

void WriteFile() {
    FILE *pt;
    pt = fopen("E:\\C-semester1\\INPUT.txt", "w");
    for (int i = 0; i < n; i++) {
        fprintf(pt, "\nStudent information number %i\n", i + 1);
        fputs("ID: ", pt);
        fputs(sv[i].ID, pt);
        fputs("Student Name: ", pt);
        fputs(sv[i].Name, pt);
        fputs("Date of Birth: ", pt);
        fputs(sv[i].DateofBirth, pt);
        fputs("Phone number: ", pt);
        fputs(sv[i].PhoneNumber, pt);
    }
    fclose(pt);
}

void ReadFile() {
    char str[100];
    FILE *pt;
    pt = fopen("E:\\C-semester1\\INPUT.txt", "r");
    while (fgets(str, 81, pt)) {
        printf("%s", str);
    }
    fclose(pt);
}

void AddListStudents(Students sv[]) {
    printf("Please enter number of students:\n");
    scanf("%d", &n);
    getchar();
    for (int i = 0; i < n; i++) {
        printf("Student information number %i\n", i + 1);
        do {
            printf("Please enter student ID:(Number type)\n");
            fgets(sv[i].ID, 100, stdin);//Gõ ID cần tạo
            checkExistID();//gọi hàm check giá trị ID bị trùng
        } while (checkExistID());
        do {
            printf("Please enter student name\n");
            fgets(sv[i].Name, sizeof(sv[i].Name), stdin);
            leng= strlen(sv[i].Name);
            checkName(leng);
        } while (leng - 1 > 15 || leng - 1 < 3);
        printf("Please enter date of birth:\n");
        fgets(sv[i].DateofBirth, sizeof(sv[i].DateofBirth), stdin);
        printf("Please enter phone number:\n");
        fgets(sv[i].PhoneNumber, sizeof(sv[i].PhoneNumber), stdin);
        WriteFile();
    }
}

void EditStudents() {
    char buffer[100];
    printf("Edit Student Information\n");
    printf("Please enter ID to edit:\n");
    fgets(buffer, 100, stdin);//Gõ ID cần sửa
    checkIndexID(buffer);//Gọi hàm để check vị trí index cần sửa
    printf("Edit Name Student:\n");
    do {
        fgets(sv[checkIndexID(buffer)].Name, sizeof(sv[checkIndexID(buffer)].Name), stdin);//checkIndexID(buffer) là giá trị index hàm trả về
        leng = strlen(sv[checkIndexID(buffer)].Name);
        checkName(leng);//Check độ dài tên
    } while (strlen(sv[checkIndexID(buffer)].Name) - 1 > 15 || strlen(sv[checkIndexID(buffer)].Name) - 1 < 3);
    printf("Edit Date of Birth:\n");
    fgets(sv[checkIndexID(buffer)].DateofBirth, sizeof(sv[checkIndexID(buffer)].DateofBirth), stdin);
    printf("Edit Phone number:\n");
    fgets(sv[checkIndexID(buffer)].PhoneNumber, sizeof(sv[checkIndexID(buffer)].PhoneNumber), stdin);
    WriteFile();
}

void DeleteStudent(char buffer[100]) {//Khai báo biến tạm để nhập ID sinh viên
    printf("Delete Student\n");
    printf("Please enter Student ID to delete\n");
    fgets(buffer, 100, stdin);//Nhập ID cần xóa
    checkIndexID(buffer);//gọi hàm check vị trí trong mảng của ID sinh viên vừa tạo
    for (int i = checkIndexID(buffer); i < n; i++) {//Thực hiện vòng lặp chèn vị trí sinh viên cần xóa bằng vị trí sau nó
        sv[i] = sv[i + 1];
    }
    n--;//Giảm vùng nhớ đi 1 giá trị sau khi xóa
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
    char a[100];
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
                AddListStudents(sv);
                break;
            case '2':
                printf("Review List Students\n");
                ReadFile();
                break;
            case '3':
                //printf("%d", checkIndexID(a));
                EditStudents();
                break;
            case '4':
                DeleteStudent(a);
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