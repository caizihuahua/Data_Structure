#include <stdio.h>
#include <stdlib.h>

void bitin(const char* name,unsigned char** str){
    FILE* f = fopen(name,"rb");
    int index=0;
    unsigned char c = (unsigned char)fgetc(f);
    while(!feof(f)){
        //将得到的字节存入 buf 中
        unsigned char* buf = (unsigned char*)malloc(9*sizeof(unsigned char));
        for (int i = 7; i >= 0; i--){
            buf[7-i] = (c&(1<<i)?'1':'0');
        }
        buf[8]='\0';
        // 将 buf 写入 str 中去
        str[index++] = buf;
        c = (unsigned char)fgetc(f);
    }
    fclose(f);
}

void bitout(const char* name,unsigned char** str){
    FILE* f = fopen(name,"wb");
    while(*str){
        unsigned int buf = 0;
        for(int i=0;i<8;i++){
            // 根据str中得到的每个字节，保存到 buf 中，进而写入文件中
            buf |= (*(*str+i)-'0')<< (7-i);
        }
        fputc(buf,f);
        str = str+1;
    }
}

// 调控输出，每八个换行
void show(unsigned char** str){
    int index = 0;
    while(*str){
        printf("%s ",*str);
        if (++index % 8 == 0) putchar('\n');
        str++;
    }
    printf("\n");
}


int main(int argc,char** argv){
    if (argc < 3) {
        printf("请在命令行参数中输入两个文件名\n");
        return 2;
    }
    // 接受从 argv[1] 文件中内容，将其每个字节序列化到 str 中
    unsigned char** str = (unsigned char**)malloc(256*sizeof(unsigned char*));
    bitin(argv[1],str);
    show(str);
    bitout(argv[2],str);
    return 0;
}