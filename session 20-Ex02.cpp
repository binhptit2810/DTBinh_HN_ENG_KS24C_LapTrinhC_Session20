#include <stdio.h>
#include <string.h>

typedef struct {
    char masanpham[20];
    char tensanpham[50];
    float gianhap;
    float giaban;
    int soluong;
} SanPham;

// Khai bao cac ham
void nhapThongTinSanPham(SanPham *sp);
void hienThiDanhSachSanPham(SanPham *ds, int n);
void nhapSanPham(SanPham *ds, int *n, float *doanhthu);
void capNhatThongTinSanPham(SanPham *ds, int n);
void sapXepSanPhamTheoGia(SanPham *ds, int n, int tang);
int timKiemSanPham(SanPham *ds, int n, char *ten);
void banSanPham(SanPham *ds, int n, float *doanhthu);
void hienThiDoanhThu(float doanhthu);

int main(){
    SanPham dsSanPham[100];
    int soLuongSanPham = 0, choice;
    float doanhthu = 0;

    do {
        printf("\nMENU\n");
        printf("1. Nhap so luong va thong tin san pham\n");
        printf("2. Hien thi danh sach san pham\n");
        printf("3. Nhap san pham\n");
        printf("4. Cap nhat thong tin san pham\n");
        printf("5. Sap xep san pham theo gia (tang/giam)\n");
        printf("6. Tim kiem san pham\n");
        printf("7. Ban san pham\n");
        printf("8. Doanh thu hien tai\n");
        printf("9. Thoat\n");
        printf("Lua chon cua ban: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: {
                printf("Nhap so luong san pham: ");
                scanf("%d", &soLuongSanPham);
                for (int i = 0; i < soLuongSanPham; i++) {
                    printf("\nNhap thong tin san pham thu %d:\n", i + 1);
                    nhapThongTinSanPham(&dsSanPham[i]);
                    doanhthu -= dsSanPham[i].soluong * dsSanPham[i].gianhap;
                }
                break;
            }
            case 2:
                hienThiDanhSachSanPham(dsSanPham, soLuongSanPham);
                break;
            case 3:
                nhapSanPham(dsSanPham, &soLuongSanPham, &doanhthu);
                break;
            case 4:
                capNhatThongTinSanPham(dsSanPham, soLuongSanPham);
                break;
            case 5: {
                int tang;
                printf("Nhap 1 de sap xep tang, 0 de sap xep giam: ");
                scanf("%d", &tang);
                sapXepSanPhamTheoGia(dsSanPham, soLuongSanPham, tang);
                break;
            }
            case 6: {
                char ten[50];
                printf("Nhap ten san pham can tim: ");
                scanf(" %[^\n]", ten);
                int viTri = timKiemSanPham(dsSanPham, soLuongSanPham, ten);
                if (viTri != -1) {
                    printf("Thong tin san pham tim thay:\n");
                    hienThiDanhSachSanPham(&dsSanPham[viTri], 1);
                } else {
                    printf("Khong tim thay san pham!\n");
                }
                break;
            }
            case 7:
                banSanPham(dsSanPham, soLuongSanPham, &doanhthu);
                break;
            case 8:
                hienThiDoanhThu(doanhthu);
                break;
            case 9:
                printf("Thoat chuong trinh.\n");
                break;
            default:
                printf("Lua chon khong hop le!\n");
        }
    } while (choice != 9);

    return 0;
}

// Dinh nghia cac ham
void nhapThongTinSanPham(SanPham *sp) {
    printf("Nhap ma san pham: ");
    scanf("%s", sp->masanpham);
    printf("Nhap ten san pham: ");
    scanf(" %[^\n]", sp->tensanpham);
    printf("Nhap gia nhap: ");
    scanf("%f", &sp->gianhap);
    printf("Nhap gia ban: ");
    scanf("%f", &sp->giaban);
    printf("Nhap so luong: ");
    scanf("%d", &sp->soluong);
}

void hienThiDanhSachSanPham(SanPham *ds, int n) {
    for (int i = 0; i < n; i++) {
        printf("\nSan pham thu %d:\n", i + 1);
        printf("Ma san pham: %s\n", ds[i].masanpham);
        printf("Ten san pham: %s\n", ds[i].tensanpham);
        printf("Gia nhap: %.2f\n", ds[i].gianhap);
        printf("Gia ban: %.2f\n", ds[i].giaban);
        printf("So luong: %d\n", ds[i].soluong);
    }
}

void nhapSanPham(SanPham *ds, int *n, float *doanhthu) {
    char ma[20];
    printf("Nhap ma san pham: ");
    scanf("%s", ma);

    for (int i = 0; i < *n; i++) {
        if (strcmp(ds[i].masanpham, ma) == 0) {
            int soluong;
            printf("San pham da ton tai. Nhap so luong can them: ");
            scanf("%d", &soluong);
            ds[i].soluong += soluong;
            *doanhthu -= soluong * ds[i].gianhap;
            return;
        }
    }

    printf("San pham moi. Nhap thong tin:\n");
    nhapThongTinSanPham(&ds[*n]);
    *doanhthu -= ds[*n].soluong * ds[*n].gianhap;
    (*n)++;
}

void capNhatThongTinSanPham(SanPham *ds, int n) {
    char ma[20];
    printf("Nhap ma san pham can cap nhat: ");
    scanf("%s", ma);

    for (int i = 0; i < n; i++) {
        if (strcmp(ds[i].masanpham, ma) == 0) {
            printf("Nhap thong tin moi cho san pham co ma %s:\n", ma);
            nhapThongTinSanPham(&ds[i]);
            return;
        }
    }
    printf("Khong tim thay san pham voi ma %s!\n", ma);
}

void sapXepSanPhamTheoGia(SanPham *ds, int n, int tang) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if ((tang && ds[i].giaban > ds[j].giaban) || (!tang && ds[i].giaban < ds[j].giaban)) {
                SanPham temp = ds[i];
                ds[i] = ds[j];
                ds[j] = temp;
            }
        }
    }
}

int timKiemSanPham(SanPham *ds, int n, char *ten) {
    for (int i = 0; i < n; i++) {
        if (strstr(ds[i].tensanpham, ten) != NULL) {
            return i;
        }
    }
    return -1;
}

void banSanPham(SanPham *ds, int n, float *doanhthu) {
    char ma[20];
    printf("Nhap ma san pham can ban: ");
    scanf("%s", ma);

    for (int i = 0; i < n; i++) {
        if (strcmp(ds[i].masanpham, ma) == 0) {
            int soluong;
            printf("Nhap so luong can ban: ");
            scanf("%d", &soluong);
            if (soluong > ds[i].soluong) {
                printf("Khong con du hang!\n");
            } else if (ds[i].soluong == 0) {
                printf("Het hang!\n");
            } else {
                ds[i].soluong -= soluong;
                *doanhthu += soluong * ds[i].giaban;
                printf("Ban thanh cong!\n");
            }
            return;
        }
    }
    printf("Khong tim thay san pham voi ma %s!\n", ma);
}

void hienThiDoanhThu(float doanhthu) {
    printf("Doanh thu hien tai: %.2f\n", doanhthu);
}

