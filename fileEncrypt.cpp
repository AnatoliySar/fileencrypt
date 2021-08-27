#include <iostream>
#include <io.h> //содержит низкоуровневые функции ввода-вывода
#include <fcntl.h>
#include <process.h>

unsigned char encrypt(unsigned char symbol1)
{
    symbol1 = symbol1 ^ (1 | (1 << 2) | (1 << 4) | (1 << 6)); // наложение битовой маски 01010101 через XOR(^)
    symbol1 = (symbol1 >> 3) | (symbol1 << (8 - 3)); 
    return symbol1;
    //XOR(^): 1 ^ 1 = 0; 1 ^ 0 = 1; 0 ^ 1 = 1; 0 ^ 0 = 0;
    //unsigned char, а не char, чтобы знаковый разряд всегда был равен 0. Это необходимо для того, чтобы при побитовом сдвиге вправо
    //левые разряды заполнялись нулями (по умолчанию они заполняются знаком исходного числа, а у unsigned переменной он всегда 0(положительный)
}
unsigned char decrypt(unsigned char symbol1)
{
    symbol1 = (symbol1 << 3) | (symbol1 >> (8 - 3));
    symbol1 = symbol1 ^ (1 | (1 << 2) | (1 << 4) | (1 << 6));
    return symbol1;
}

int startEncryption()
{
    printf("If u press \"1\", File \"to encrypt\" will be encrypted and saved into \"encrypted\".\nIf u press \"2\", File \"encrypted\" will be decrypted and saved into \"decrypted\".\nAny other symbol will terminate the program.\n");
    int var;
    scanf("%d", &var);
    switch (var)
    {
    case 1:
    {
        const char* filename = "to_encrypt.txt";
        int fileDescriptor;
        fileDescriptor = _open(filename, _O_RDWR | _O_BINARY); // открывает файл в режиме для чтения или записи
        int lenght = _lseek(fileDescriptor, 0, 2);// ПОЛУЧАЕМ ДЛИНУ ФАЙЛА. lseek возвращает количество прочитанных символов. Изначально, после открытия файла,
        //дескриптор указывает на первый символ этого файла. нам нужно передвинуть его на последний и получить на выходе количество 
        //пройденных символов. первый аргумент - дескриптор файла, второй аргумент -  количество символов, на которое мы будем сдвигаться, 
        //(положительное число - сдвиг вправо, отрицательное - влево)
        // третий аргумент -откуда мы будем сдвигаться: 0-из начала, 1-из текущей позиции, 2-из конца.
        _lseek(fileDescriptor, 0, 0);
        char* buffer = (char*)malloc(sizeof(char) * lenght); // возвращает указатель на первый элемент массива памяти размером lenght
        char* bufferEncrypted = (char*)malloc(sizeof(char) * lenght);
        _read(fileDescriptor, buffer, lenght);
        for (int i = 0; i < lenght; i++)
        {
            bufferEncrypted[i] = encrypt(buffer[i]);
        }
        _close(fileDescriptor);
        const char* filename2 = "encrypted.txt";
        fileDescriptor = _open(filename2, _O_RDWR | _O_BINARY | _O_CREAT | _O_TRUNC, _S_IREAD | _S_IWRITE);// создает файл, дуступный для чтения и записи
        _write(fileDescriptor, bufferEncrypted, lenght);
        _close(fileDescriptor);
        //_spawnle()
        printf("Done.\n\n");
        break;
    }
    case 2:
    {
        const char* filename = "encrypted.txt";
        int fileDescriptor;
        fileDescriptor = _open(filename, _O_RDWR | _O_BINARY);
        int lenght = _lseek(fileDescriptor, 0, 2);// ПОЛУЧАЕМ ДЛИНУ ФАЙЛА. lseek возвращает количество прочитанных символов. Изначально, после открытия файла,
        //дескриптор указывает на первый символ этого файла. нам нужно передвинуть его на последний и получить на выходе количество 
        //пройденных символов. первый аргумент - дескриптор файла, второй аргумент -  количество символов, на которое мы будем сдвигаться, 
        //(положительное число - сдвиг вправо, отрицательное - влево)
        // третий аргумент -откуда мы будем сдвигаться: 0-из начала, 1-из текущей позиции, 2-из конца.
        _lseek(fileDescriptor, 0, 0);
        char* buffer = (char*)malloc(sizeof(char) * lenght); // возвращает указатель на первый элемент массива памяти размером lenght
        char* bufferDecrypted = (char*)malloc(sizeof(char) * lenght);
        _read(fileDescriptor, buffer, lenght);
        for (int i = 0; i < lenght; i++)
        {
            bufferDecrypted[i] = decrypt(buffer[i]);
        }
        _close(fileDescriptor);
        const char* filename2 = "decrypted.txt";
        fileDescriptor = _open(filename2, _O_RDWR | _O_BINARY | _O_CREAT | _O_TRUNC, _S_IREAD | _S_IWRITE);// создает файл, дуступный для чтения и записи
        _write(fileDescriptor, bufferDecrypted, lenght);
        _close(fileDescriptor);
        printf("Done.\n\n");
        break;
    }
    default:
        printf("Exit.");
        return 0;
    }
    startEncryption();
    return 0;
}
int main()
{
    return startEncryption();
}


