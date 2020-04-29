#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>


typedef uint8_t  BYTE;


int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "Usage: ./recover image\n");
        return 1;
    }

    FILE *file = fopen(argv[1], "r"); //Con trỏ mở file
    FILE *out = NULL; //Dùng để ghi file

    BYTE buffer[512]; //Bộ nhớ đệm
    char filename[8]; //Tên file khi in ra ###.jpg

    int countFile = 0; //Đếm ảnh jpg đc tìm thấy

    if (!file) //Kiểm tra có file hay không
    {
        return 1;
    }



    while (1)
    {
        //Đếm số lượng byte để đọc, 1 file jpg cần 512 byte
        size_t bytesRead  = fread(buffer, sizeof(BYTE), 512, file); //Đọc file từ bộ nhớ

        //Khi end of file thì thoát khỏi vòng lặp && số lượng buffer hết
        if (bytesRead == 0 && feof(file))
        {
            break;
        }


        // Nếu tìm đc file kế tiếp thì cần đóng file lần trước ghi lai rồi mới ghi tiếp
        // Dấu hiệu phát hiện file jpg dựa vào 4 ký tự đầu tiên
        if (out != NULL && buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            fclose(out);
        }

        // Nếu phát hiện ra bất kỳ file jpg nào thì đếu mở file lên để ghi và tiến hành đếm file jpg
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            sprintf(filename, "%03i.jpg", countFile);
            out = fopen(filename, "w"); //dùng con trỏ file mở file và ghi vào
            countFile++; //Nếu thấy dấu hiệu jpg thì đếm + 1
        }

        //Miễn sao có file thì sẽ ghi file
        if (out != NULL)
        {
            fwrite(buffer, sizeof(BYTE), 512, out);
        }
    }


    //đóng file mở và ghi
    fclose(file);
    fclose(out);

    //Nếu thành công thì trả về 0
    return 0;
}
