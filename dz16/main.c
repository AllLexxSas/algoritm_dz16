#include <stdio.h>
#include <stdlib.h>
#include <math.h>


//--------------------------Начало первого задания-------------------------------
//вывод содержимого на экран
void _print(char *str)
{
    for(int i = 0; str[i] != '\0'; i++)
        printf("%c ",str[i]);
    printf("\n");
}

//шифровка отельного символа. смещаем символ на согласно ключа
char encrypt(char *a ,int key)
{
    int s = *a + key%25; //длаем ключ кратынй 25(сколько букв в английском алфавите)
    if((*a>='A' && *a<='Z') || (*a>='a' && *a<='z'))
    {
        if(*a>='A' && *a<='Z' && s > 'Z') //если ключ сдвинул символ дальше,
            *a =  s-26;                   //чем придел заглавных букв, то переходим то переходим в начало алфавита
        else if(*a>='a' && *a<='z' && s > 'z')//то же самое для строчных букв
            *a = s-26;
        else
            *a = s;
    }
    return -1;
}

//расшифровка
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
//пробегаем по симвомам строки и шифруем их
void caesa_cipher(char * str, int key)
{
    for(int i = 0; str[i] != '\0'; i++)
        encrypt( &str[i] , key);
}
//расшифровываем строку
void decoding (char * str, int key)
{
    for(int i = 0; str[i] != '\0'; i++)
        decipher( &str[i] , key);
}


//Реализовать шифрование и расшифровку цезаря с передаваемым в функцию сообщением и ключом
void task1()
{
    char j[] = "privet_mir";
    int kay = 16784;
    _print(j);
    caesa_cipher(j , kay );
   _print(j);
    decoding(j,kay);
   _print(j);
}
//----------------------------конец первого задания-----------------------------------

//-------------------------------второе задание---------------------------------------
//Реализовать шифрование и расшифровку перестановками с передаваемым в функцию сообщением и количеством столбцов
//инициализируем двухмерный массив
char** init_array(size_t columns,size_t line)
{
    char** a =(char**)malloc(line*sizeof(char*));
    for(int i= 0; i<line;i++)
    {
        a[i]=(char*)malloc(sizeof(char));
    }
    return a;
}

//заполнение двухмерного массива из строки. пустые ячейки заполняются 'A'
void filling_array(char **code ,char* arr,int line, int columns, int array_size)
{
    int q = 0;
    for(int i= 0; i < line ; i++)
        for(int j = 0; j < columns ; j++)
            code[i][j] = q<array_size-1?arr[q++]:'A';
}

//смена символов в местами ячейках массива
void swap_vallue(char *a, char *b)
{
    char temp = *a;
    *a = *b;
    *b = temp;
}

//меняем колонки согласно полученному ключу
void swap_columns(char **code, int colum_size, int column_one,int column_two)
{
    for(int i=0 ; i < colum_size; i++)
    {
        swap_vallue(&code[i][column_one-1],&code[i][column_two-1]);
    }
}

//получаем из ключа столбыу которые нужно сменить
//(пример если ключ будит 43421 - вернется массив 1 2 4 3 )
int* get_key(int key,int number_column)
{
    int *_key=(int*)malloc(sizeof(int));
    int ii = 0;
    for(int i = key ;i != number_column;i/=10)
    {
        key = key/10*10;
        _key[ii] = i-key;
        key/=10;
        ii++;
    }
    return _key;
}

//кодируем массив
void swap_columns_to_key(char **code ,int line, int columns,int key)
{
    int *_get_key = get_key(key,columns);
    for(int i = 0 ; i < columns;i+=2 )
            swap_columns(code,columns,_get_key[i],_get_key[i+1]);
}

//вывод двухмерного массива на экран
void print_array_data(char** arr,int line, int columns)
{
    for(int i= 0; i < line ; i++){
        for(int j = 0; j < columns ; j++)
            printf("%5c",arr[i][j]);
        printf("\n");
    }
}

//освобождаем память
void free_array(char** arr,size_t columns)
{
    for(int i= 0; i < columns ; i++){
        free(arr[i]);
    }
    free(arr);
}

void code_array(char* arr,int key,int array_size)
{
    //41234
    int number_columns = key/10000;//получаем из ключа количестов столбцов
    int number_line = ceil(array_size/(double)number_columns); // получаем количество столбцов

    char **code = init_array(number_columns,number_line); //инициализируем двухмерный массив, согласно рассчитаным стобцам и строкам

    filling_array (code,arr,number_line, number_columns,array_size);//заполняем двухмерный массив из переданной строки

    print_array_data(code, number_columns, number_line);

    swap_columns_to_key(code,number_line, number_columns,key);//кодируем массив
    printf("\n");
    print_array_data(code, number_columns, number_line);

    swap_columns_to_key(code,number_line, number_columns,key);//раскодируем массив
    printf("\n");

    print_array_data(code, number_columns, number_line);
    free_array(code,number_line);//чистим память
}

void task2()
{

    char a[] = "qwertyuiopzxcvb";
    printf("code string - %s\n",a);
    code_array(a,44123,sizeof(a));
    //filling_table();
}

int main()
{


    task2();


    return 0;
}
