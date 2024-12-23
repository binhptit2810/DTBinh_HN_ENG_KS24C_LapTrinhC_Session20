#include <stdio.h>
#include <string.h>

typedef struct {
    char masach[20];
    char tensach[50];
    char tacgia[50];
    float giatien;
    char theloai[30];
} Sach;
// Khai bao cac ham
void nhapThongTinSach(Sach *s);
void hienThiThongTinSach(Sach *s, int n);
void themSach(Sach *s, int *n, int vitri);
void xoaSachTheoMa(Sach *s, int *n, char *ma);
void capNhatThongTinSach(Sach *s, int n, char *ma);
void sapXepSachTheoGia(Sach *s, int n, int tang);
int timKiemSachTheoTen(Sach *s, int n, char *ten);

int main(){
    Sach dsSach[100];
    int soLuongSach = 0, choice;
    do {
        printf("\nMENU\n");
        printf("1. Nhap so luong va thong tin sach\n");
        printf("2. Hien thi thong tin sach\n");
        printf("3. Them sach vao vi tri\n");
        printf("4. Xoa sach theo ma sach\n");
        printf("5. Cap nhat thong tin sach theo ma sach\n");
        printf("6. Sap xep sach theo gia (tang/giam)\n");
        printf("7. Tim kiem sach theo ten sach\n");
        printf("8. Thoat\n");
        printf("Lua chon cua ban: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1: {
                printf("Moi ban nhap so luong sach: ");
                scanf("%d", &soLuongSach);
                for (int i = 0; i < soLuongSach; i++) {
                    printf("\nNhap thong tin sach thu %d:\n", i + 1);
                    nhapThongTinSach(&dsSach[i]);
                }
                break;
            }
            case 2:
                hienThiThongTinSach(dsSach, soLuongSach);
                break;
            case 3: {
                int vitri;
                printf("Nhap vi tri can them: ");
                scanf("%d", &vitri);
                themSach(dsSach, &soLuongSach, vitri);
                break;
            }
            case 4: {
                char ma[20];
                printf("Nhap ma sach can xoa: ");
                scanf("%s", ma);
                xoaSachTheoMa(dsSach, &soLuongSach, ma);
                break;
            }
            case 5: {
                char ma[20];
                printf("Nhap ma sach can cap nhat: ");
                scanf("%s", ma);
                capNhatThongTinSach(dsSach, soLuongSach, ma);
                break;
            }
            case 6: {
                int tang;
                printf("Nhap 1 de sap xep tang, 0 de sap xep giam: ");
                scanf("%d", &tang);
                sapXepSachTheoGia(dsSach, soLuongSach, tang);
                break;
            }
            case 7: {
                char ten[50];
                printf("Nhap ten sach can tim: ");
                scanf(" %[^\n]", ten);
                int viTri = timKiemSachTheoTen(dsSach, soLuongSach, ten);
                if (viTri != -1) {
                    printf("Thong tin sach tim thay:\n");
                    hienThiThongTinSach(&dsSach[viTri], 1);
                } else {
                    printf("Khong tim thay sach!\n");
                }
                break;
            }
            case 8:
                printf("Thoat chuong trinh.\n");
                break;
            default:
                printf("Lua chon khong hop le!\n");
        }
    } while (choice!= 8);

    return 0;
}
// Dinh nghia cac ham
void nhapThongTinSach(Sach *s) {
    printf("Nhap ma sach: ");
    scanf("%s", s->masach);
    printf("Nhap ten sach: ");
    scanf(" %[^\n]", s->tensach);
    printf("Nhap tac gia: ");
    scanf(" %[^\n]", s->tacgia);
    printf("Nhap gia tien: ");
    scanf("%f", &s->giatien);
    printf("Nhap the loai: ");
    scanf(" %[^\n]", s->theloai);
}

void hienThiThongTinSach(Sach *s, int n) {
    for (int i = 0; i < n; i++) {
        printf("\nSach thu %d:\n", i + 1);
        printf("Ma sach: %s\n", s[i].masach);
        printf("Ten sach: %s\n", s[i].tensach);
        printf("Tac gia: %s\n", s[i].tacgia);
        printf("Gia tien: %.2f\n", s[i].giatien);
        printf("The loai: %s\n", s[i].theloai);
    }
}

void themSach(Sach *s, int *n, int vitri) {
    if (vitri < 0 || vitri > *n) {
        printf("Vi tri khong hop le!\n");
        return;
    }
    for (int i = *n; i > vitri; i--) {
        s[i] = s[i - 1];
    }
    printf("Nhap thong tin sach moi:\n");
    nhapThongTinSach(&s[vitri]);
    (*n)++;
}
void xoaSachTheoMa(Sach *s, int *n, char *ma) {
    int found = 0;
    for (int i = 0; i < *n; i++) {
        if (strcmp(s[i].masach, ma) == 0) {
            for (int j = i; j < *n - 1; j++) {
                s[j] = s[j + 1];
            }
            (*n)--;
            found = 1;
            break;
        }
    }
    if (!found) {
        printf("Khong tim thay sach voi ma %s!\n", ma);
    }
}

void capNhatThongTinSach(Sach *s, int n, char *ma) {
    for (int i = 0; i < n; i++) {
        if (strcmp(s[i].masach, ma) == 0) {
            printf("Nhap thong tin moi cho sach co ma %s:\n", ma);
            nhapThongTinSach(&s[i]);
            return;
        }
    }
    printf("Khong tim thay sach voi ma %s!\n", ma);
}

void sapXepSachTheoGia(Sach *s, int n, int tang) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if ((tang && s[i].giatien > s[j].giatien) || (!tang && s[i].giatien < s[j].giatien)) {
                Sach temp = s[i];
                s[i] = s[j];
                s[j] = temp;
            }
        }
    }
}

int timKiemSachTheoTen(Sach *s, int n, char *ten) {
    for (int i = 0; i < n; i++) {
        if (strstr(s[i].tensach, ten) != NULL) {
            return i;
        }
    }
    return -1;
}

