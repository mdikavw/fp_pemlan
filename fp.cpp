#include <stdlib.h>
#include <stdio.h>
#include <string.h>

const char *FORMAT_TULIS_DATA = "%s,%f,%i\n";
FILE *file;

// declare struct
struct gaji_daerah
{
    char nama_daerah[30];
    float gaji;
    int tahun;
};
typedef struct gaji_daerah gaji_daerah;

// declare functions
void create_data(gaji_daerah data_daerah[]);
void show_data(FILE *file);
int mean(gaji_daerah data[], int len);
int range(gaji_daerah data[], int len);
int iqr(gaji_daerah data[], int len);
int median(gaji_daerah sortedData[], int len);

// main
int main()
{
    gaji_daerah data_daerah[870];
    create_data(data_daerah);
    printf("%i", mean(data_daerah, 870));
}

// function definition
void create_data(gaji_daerah data_daerah[])
{
    // Membaca file dan memasukkan data ke array data_daerah
    file = fopen("Indonesian Salary by Region (1997-2022).csv", "r");

    int read = 0;
    int jumlah_data = 0;
    do
    {
        read = fscanf(file, "%[^,],%f,%i\n", data_daerah[jumlah_data].nama_daerah, &data_daerah[jumlah_data].gaji, &data_daerah[jumlah_data].tahun);
        if (read == 3)
        {
            jumlah_data++;
        }
        if (read != 3 && !feof(file))
        {
            printf("Format file salah\n");
        }
        if (ferror(file))
        {
            printf("Terjadi kesalahan saat membaca file\n");
            return;
        }
    } while (!feof(file));
    fclose(file);

    // Menyimpan data file ke file baru "Data Gaji Berdasarkan Daerah.dat"
    fopen_s(&file, "Data Gaji Berdasarkan Daerah.dat", "w+");
    for (int i = 0; i < jumlah_data; i++)
    {
        fprintf(file, FORMAT_TULIS_DATA, data_daerah[i].nama_daerah, data_daerah[i].gaji, data_daerah[i].tahun);
    }
    printf("Berhasil menuliskan %i data", jumlah_data);
    fclose(file);
}

void show_data(FILE *file)
{
    char output[50];
    if (fgets(output, 50, file) != NULL)
    {
        puts(output);
        return show_data(file);
    }
}

int mean(gaji_daerah data[], int len)
{
    int sum;
    for (int i = 0; i < len; i++)
    {
        sum += data[i].gaji;
    }
    return sum / len;
}

int range(gaji_daerah data[], int len)
{
    return data[0].gaji - data[len - 1].gaji;
}

int iqr(gaji_daerah data[], int len)
{
    int q1, q3;
    q1 = len / 4;
    q3 = len * 3 / 4;
    return data[q3].gaji - data[q1].gaji;
}

int median(gaji_daerah sortedData[], int len)
{
    return 0;
}