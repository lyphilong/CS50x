#include <stdio.h>
#include <cs50.h>
#include <string.h>

int check(string key);

int main(int argc, string argv[]){
    string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    string key_tmp = "VCHPRZGJNTLSKFBDQWAXEUYMOI";
    int flag=0;

    if (argc != 2)
    {
        flag++;
        return flag;
    }
    else
    {
        if(check(argv[1]) == 0)
        {
            string input = get_string("plain text: ");

            printf("ciphertext: ");

            for(int i =0;i<strlen(input);i++)
            {
                if ( (input[i]<='z' && input[i]>= 'a') || (input[i]<='Z' && input[i]>= 'A')  )
                {
                    for(int j =0; j< strlen(argv[1]);j++)
                    {
                        if(input[i] == alphabet[j]) //Nếu plaintext là chữ hoa
                        {
                            if ((argv[1][j]>= 'A') && (argv[1][j] <='Z') ) // Kiểm tra Key có hoa không
                            {
                                printf("%c",argv[1][j]);
                            }
                            else
                            {
                                printf("%c",argv[1][j] - 32); // Nếu Key không là hoa thì biến thành hoa
                            }
                            break;
                        }

                        if (input[i] == alphabet[j] + 32) // Nếu plaintext là chữ thường
                        {
                            if ((argv[1][j]>= 'A') && (argv[1][j] <='Z') )// Kiểm tra Key có hoa không
                            {
                               printf("%c",argv[1][j] + 32); //Nếu Key là hoa thì in chữ thường
                            }
                            else
                            {
                                printf("%c",argv[1][j]); // Nếu không thì in chữ thường
                            }
                        break;
                        }
                   }
                }
                else
                {
                 printf("%c",input[i]);
                }
            }
            printf("\n");
            return flag;
        }
        else {
            flag++;
            return flag;

        }

       // printf("Key must contain 26 characters.\n");

    }
//    printf("\n");

}


int check(string key)
{
    int count =0;
    if(strlen(key) == 26)
    {
        for(int i = 0; i< strlen(key);i++)
        {
            if((key[i]<='z' && key[i]>= 'a') || (key[i]<='Z' && key[i]>= 'A'))
            {
                count++;
                for(int j = i+1; j< strlen(key);j++)
                {
                    if (j == i){
                        break;
                    }
                    if(key[i] == key[j])
                    {
                       count++;
                    }
                }

            }
        }

    }

    if (count == 26){
        return 0;
       // printf("Key must contain 26 characters.");
    }
    return 1;
}