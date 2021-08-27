#include <iostream>
#include <io.h> //�������� �������������� ������� �����-������
#include <fcntl.h>
#include <process.h>

unsigned char encrypt(unsigned char symbol1)
{
    symbol1 = symbol1 ^ (1 | (1 << 2) | (1 << 4) | (1 << 6)); // ��������� ������� ����� 01010101 ����� XOR(^)
    symbol1 = (symbol1 >> 3) | (symbol1 << (8 - 3)); 
    return symbol1;
    //XOR(^): 1 ^ 1 = 0; 1 ^ 0 = 1; 0 ^ 1 = 1; 0 ^ 0 = 0;
    //unsigned char, � �� char, ����� �������� ������ ������ ��� ����� 0. ��� ���������� ��� ����, ����� ��� ��������� ������ ������
    //����� ������� ����������� ������ (�� ��������� ��� ����������� ������ ��������� �����, � � unsigned ���������� �� ������ 0(�������������)
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
        fileDescriptor = _open(filename, _O_RDWR | _O_BINARY); // ��������� ���� � ������ ��� ������ ��� ������
        int lenght = _lseek(fileDescriptor, 0, 2);// �������� ����� �����. lseek ���������� ���������� ����������� ��������. ����������, ����� �������� �����,
        //���������� ��������� �� ������ ������ ����� �����. ��� ����� ����������� ��� �� ��������� � �������� �� ������ ���������� 
        //���������� ��������. ������ �������� - ���������� �����, ������ �������� -  ���������� ��������, �� ������� �� ����� ����������, 
        //(������������� ����� - ����� ������, ������������� - �����)
        // ������ �������� -������ �� ����� ����������: 0-�� ������, 1-�� ������� �������, 2-�� �����.
        _lseek(fileDescriptor, 0, 0);
        char* buffer = (char*)malloc(sizeof(char) * lenght); // ���������� ��������� �� ������ ������� ������� ������ �������� lenght
        char* bufferEncrypted = (char*)malloc(sizeof(char) * lenght);
        _read(fileDescriptor, buffer, lenght);
        for (int i = 0; i < lenght; i++)
        {
            bufferEncrypted[i] = encrypt(buffer[i]);
        }
        _close(fileDescriptor);
        const char* filename2 = "encrypted.txt";
        fileDescriptor = _open(filename2, _O_RDWR | _O_BINARY | _O_CREAT | _O_TRUNC, _S_IREAD | _S_IWRITE);// ������� ����, ��������� ��� ������ � ������
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
        int lenght = _lseek(fileDescriptor, 0, 2);// �������� ����� �����. lseek ���������� ���������� ����������� ��������. ����������, ����� �������� �����,
        //���������� ��������� �� ������ ������ ����� �����. ��� ����� ����������� ��� �� ��������� � �������� �� ������ ���������� 
        //���������� ��������. ������ �������� - ���������� �����, ������ �������� -  ���������� ��������, �� ������� �� ����� ����������, 
        //(������������� ����� - ����� ������, ������������� - �����)
        // ������ �������� -������ �� ����� ����������: 0-�� ������, 1-�� ������� �������, 2-�� �����.
        _lseek(fileDescriptor, 0, 0);
        char* buffer = (char*)malloc(sizeof(char) * lenght); // ���������� ��������� �� ������ ������� ������� ������ �������� lenght
        char* bufferDecrypted = (char*)malloc(sizeof(char) * lenght);
        _read(fileDescriptor, buffer, lenght);
        for (int i = 0; i < lenght; i++)
        {
            bufferDecrypted[i] = decrypt(buffer[i]);
        }
        _close(fileDescriptor);
        const char* filename2 = "decrypted.txt";
        fileDescriptor = _open(filename2, _O_RDWR | _O_BINARY | _O_CREAT | _O_TRUNC, _S_IREAD | _S_IWRITE);// ������� ����, ��������� ��� ������ � ������
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


