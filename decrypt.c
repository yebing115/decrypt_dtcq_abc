#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int primes[7] = {0x2717, 0x2719, 0x2735, 0x2737, 0x274d, 0x2753, 0x2755};

void dump_file(char* file_name, char* buf, unsigned long size) {
    char *write_file_name = malloc(strlen(file_name) + strlen(".zip") + 1);
    strcpy(write_file_name, file_name);
    strcat(write_file_name, ".zip");
    FILE *fp = fopen(write_file_name, "wb");
    fwrite(buf, 1, size, fp);
    fclose(fp);
}

void decrypt(char* ori, char* decrypted, size_t size, char* file_name, size_t file_name_length) {
    int prime = 0;
    int k = 0;
    for (; k < 7; k++) {
        if (size % primes[k]) {
            prime = primes[k];
            break;
        }
    }

    int i = 0;
    int j = 0;

    do {
        long long temp = j * prime;
        temp = temp % size;
        decrypted[(long)temp] = ori[j] ^ file_name[i];
        ++j;
        i = (i + 1) % file_name_length;
    } while (j < size);
}

int main(int argc, const char *argv[])
{
    char *file_name = argv[1];
    FILE *fp = fopen(file_name, "rb");

    unsigned char *pBuffer = NULL;
    unsigned char *dBuffer = NULL;
    unsigned long size = 0;
    fseek(fp,0,SEEK_END);
    size = ftell(fp);
    fseek(fp,0,SEEK_SET);
    pBuffer = (unsigned char*)malloc(size);
    size = fread(pBuffer,sizeof(unsigned char), size, fp);
    printf("file buffer got\n");
    fclose(fp);

    dBuffer = (unsigned char*)malloc(size);
    decrypt(pBuffer, dBuffer, size, file_name, strlen(file_name));
    dump_file(file_name, dBuffer, size);

    free(pBuffer);
    free(dBuffer);

    return 0;
}
