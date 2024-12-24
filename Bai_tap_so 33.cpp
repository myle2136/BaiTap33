#include <stdio.h>
#include <stdlib.h>
typedef struct 
{
    int tu ;
    int mau;
} PhanSo;
int timUCLN(int a, int b) 
{
    while (b != 0) 
	{
        int temp = b;
        b = a % b;
        a = temp;
    }
    return abs(a);
}
PhanSo rutGonPhanSo(PhanSo ps) 
{
    int ucln = timUCLN(ps.tu, ps.mau);
    ps.tu /= ucln;
    ps.mau /= ucln;
    if (ps.mau < 0) 
	{ 
        ps.tu = -ps.tu;
        ps.mau = -ps.mau;
    }
    return ps;
}
float giaTriPhanSo(PhanSo ps)
{
    return (float)ps.tu / ps.mau;
}

void ghiPhanSoVaoTapTin(PhanSo ps[], int n, const char* tenTapTin) 
{
    FILE* file = fopen(tenTapTin, "w");
    for (int i = 0; i < n; i++) 
	{
        fprintf(file, "%d %d\n", ps[i].tu, ps[i].mau);
    }
    fclose(file);
}
void hienThiDanhSach(PhanSo ps[], int n) 
{
    printf("Danh sach phan so (da rut gon):\n");
    for (int i = 0; i < n; i++) 
	{
        PhanSo psRutGon = rutGonPhanSo(ps[i]);
        printf("%d/%d\n", psRutGon.tu, psRutGon.mau);
    }
}
PhanSo timPhanSoNhoNhat(PhanSo ps[], int n) 
{
    PhanSo min = ps[0];
    for (int i = 1; i < n; i++) 
	{
        if (giaTriPhanSo(ps[i]) < giaTriPhanSo(min)) 
		{
            min = ps[i];
        }
    }
    return min;
}
int demPhanSoNhoNhat(PhanSo ps[], int n, PhanSo min) 
{
    int count = 0;
    float minValue = giaTriPhanSo(min);
    for (int i = 0; i < n; i++) 
	{
        if (giaTriPhanSo(ps[i]) == minValue) 
		{
            count++;
        }
    }
    return count;
}
void sapXepGiamDan(PhanSo ps[], int n) 
{
    for (int i = 0; i < n - 1; i++) 
	{
        for (int j = i + 1; j < n; j++) 
		{
            if (giaTriPhanSo(ps[i]) < giaTriPhanSo(ps[j])) 
			{
                PhanSo temp = ps[i];
                ps[i] = ps[j];
                ps[j] = temp;
            }
        }
    }
}

int main() 
{
    int n;
    printf("Nhap so luong phan so: ");
    scanf("%d", &n);

    PhanSo ps[n];
    for (int i = 0; i < n; i++) 
	{
        printf("Nhap tu so va mau so cua phan so thu %d: ", i + 1);
        scanf("%d %d", &ps[i].tu, &ps[i].mau);
    }
    ghiPhanSoVaoTapTin
	(ps, n, "danhsachphansos.txt");
    hienThiDanhSach(ps, n);
    PhanSo min = timPhanSoNhoNhat(ps, n);
    printf("Phan so nho nhat: %d/%d\n", min.tu, min.mau);
    int count = demPhanSoNhoNhat(ps, n, min);
    printf("So luong phan so nho nhat: %d\n", count);
    sapXepGiamDan(ps, n);
    printf("Danh sach phan so sau khi sap xep giam dan:\n");
    hienThiDanhSach(ps, n);
    return 0;
}
