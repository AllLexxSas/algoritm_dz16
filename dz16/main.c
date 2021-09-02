#include <stdio.h>

void _print(char *str)
{
    for(int i = 0; str[i] != '\0'; i++)
        printf("%c ",str[i]);

    printf("\n");

}


char encrypt(char *a ,int key)
{
    int s = *a + key%25;
    if((*a>='A' && *a<='Z') || (*a>='a' && *a<='z'))
    {
        if(*a>='A' && *a<='Z' && s > 'Z')
            *a =  s-26;
        else if(*a>='a' && *a<='z' && s > 'z')
            *a = s-26;
        else
            *a = s;
    }
    return -1;
}

char decipher (char *a, int key)
{
    int s = *a - key%25;
    if((*a >= 'A' && *a<= 'Z') || (*a >= 'a' && *a<= 'z'))
    {
        if(*a >= 'A' && *a<= 'Z' && s < 'A')
             *a = s +26;
        else if(*a >= 'a' && *a <= 'z' && s < 'a')
            *a = s + 26;
        else
            *a= s;
    }
    return -1;
}

void caesa_cipher(char * str, int key)
{
    for(int i = 0; str[i] != '\0'; i++)
        encrypt( &str[i] , key);
}

void decoding (char * str, int key)
{
    for(int i = 0; str[i] != '\0'; i++)
        decipher( &str[i] , key);
}


int main()
{
    char j[] = "privet_mir";
    int kay = 16784;
    _print(j);
    caesa_cipher(j , kay );
   _print(j);
    decoding(j,kay);

   _print(j);


    return 0;
}
