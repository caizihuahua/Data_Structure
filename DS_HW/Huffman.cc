#include <iostream>
#include <cstring>
#include <string>
#include <algorithm>
#include <vector>

class HuffmanCode{
public:
    unsigned char ch = 0;
    std::string huffcode = "";
    int weight = 0;
    HuffmanCode* left = nullptr;
    HuffmanCode* right = nullptr;
    
public:
    HuffmanCode(unsigned char ch,const std::string& huffcode,int weight, HuffmanCode* left, HuffmanCode* right)
    :ch(ch),huffcode(huffcode),weight(weight),left(left),right(right)
    {}
    HuffmanCode()
    :ch(0),huffcode(""),weight(0),left(nullptr),right(nullptr)
    {}


    static std::string codebook[256];
    static int weights[256];

    static void HuffTree(HuffmanCode& root){
        if(!(root.left&&root.right)){
            codebook[root.ch] = root.huffcode.data()?root.huffcode:"0";
            return;
        }
        root.left->huffcode = root.huffcode + root.left->huffcode;
        root.right->huffcode = root.huffcode + root.right->huffcode;
        HuffTree(*root.left);
        HuffTree(*root.right);
    }

    static void HuffCodebook(int* weights){
        std::vector<HuffmanCode*> cds;
        for(int i=0;i<256;i++){
            if(weights[i]!=0){
                HuffmanCode* cw = new HuffmanCode((unsigned char)i,"",weights[i],nullptr,nullptr);
                cds.emplace_back(cw);
            }
        }
        std::sort(cds.begin(),cds.end(),[](HuffmanCode* a,HuffmanCode* b){return a->weight<b->weight;});
        while(cds.size()>1){
            HuffmanCode* leftchild = cds.at(0);
            leftchild->huffcode = "0";
            HuffmanCode* rightchild = cds.at(1);
            rightchild->huffcode = "1";
            HuffmanCode* innercode = new HuffmanCode(0,"",cds.at(0)->weight+cds.at(1)->weight,leftchild,rightchild);

            cds.erase(cds.begin(),cds.begin()+2);
            cds.emplace(cds.begin(),innercode);
            std::sort(cds.begin(),cds.end(),[](HuffmanCode* a,HuffmanCode* b){return a->weight<b->weight;});
        }
        HuffTree(*cds.at(0));
    }
public:
    static void HuffEncode(const char* srcfile,const char* huffile){
        FILE* fsrc = fopen(srcfile,"rb");
        unsigned char c = (unsigned char)fgetc(fsrc);
        while(!feof(fsrc)){
            weights[c] += 1;
            c = (unsigned char)fgetc(fsrc);
        }
        HuffCodebook(weights);
        fclose(fsrc);

        FILE* fhuf = fopen(huffile,"wb");
        for(int i=0;i<256;i++){
            if(codebook[i]!=""){
                fputc((unsigned char)i,fhuf);
                std::string s = codebook[i];
                fputs(s.data(),fhuf);
                fputc(0xFF,fhuf);
            }
        }
        fputc(0xFE,fhuf);
        // fflush(fhuf);
        fsrc = fopen(srcfile,"rb");
        c = (unsigned char)fgetc(fsrc);
        int index = 0;
        unsigned char tmp = 0;
        while (!feof(fsrc)){
            for(int i=0;i<codebook[c].size();i++){
                tmp |= ((codebook[c][i]=='0')?0x0:0x1)<<(7-index);
                index++;
                if(index==8){
                    index = 0;
                    fputc(tmp,fhuf);
                    tmp = 0;
                }
            }
            c = (unsigned char)fgetc(fsrc);
        }
        
        if(index!=0){
            fputc(0xFE,fhuf);
            fputc((unsigned char)index,fhuf);
            fputc(tmp,fhuf);
        }
        fclose(fsrc);
        fclose(fhuf);
    }
    static void HuffDecode(const char* huffile,const char* srcfile){
        FILE* fhuf = fopen(huffile,"rb");
        FILE* fsrc = fopen(srcfile,"wb");
        unsigned char c = (unsigned char)fgetc(fhuf);
        while(c != 0xFE){
            std::string hufcode;
            unsigned char tmp = (unsigned char)fgetc(fhuf);
            while(tmp != 0xFF){
                hufcode += (tmp-'0')?'1':'0';
                tmp = (unsigned char)fgetc(fhuf);
            }          
            codebook[c] = hufcode;
            c = (unsigned char)fgetc(fhuf);
        }
        c = (unsigned char)fgetc(fhuf);

        std::string tmp = "";
        while(!feof(fhuf) && c!=0xFE){
            for(int i=0;i<8;i++){
                tmp += (c&(1<<(7-i)))?'1':'0';
                for(int j=0;j<256;j++){
                    if(codebook[j] == tmp) {
                        fputc(j,fsrc);
                        fflush(fsrc);
                        tmp = "";
                        break;
                    }
                }
            }
            c = (unsigned char)fgetc(fhuf);
        }
        if(c==0xFE){
            int left_num = (int)fgetc(fhuf);
            c = (unsigned char)fgetc(fhuf);
            for(int i=0;i<left_num;i++){
                tmp += (c&(1<<(7-i)))?'1':'0';
                for(int j=0;j<256;j++){
                    if(codebook[j] == tmp) {
                        fputc(j,fsrc);
                        fflush(fsrc);
                        tmp = "";
                        break;
                    }
                }
            }
        }
        return;
    }

};


std::string HuffmanCode::codebook[256];
int HuffmanCode::weights[256];

int main(int agrc,char** argv){
    if(agrc != 4){
        std::cout<<"请依次输入 encode/decode 源文件名 编码后文件名"<<std::endl;
    }
    if(!strcmp(argv[1],"encode")){
        HuffmanCode::HuffEncode(argv[2],argv[3]);
    }else if (!strcmp(argv[1],"decode")){
        HuffmanCode::HuffDecode(argv[3],argv[2]);
    }
    
    return 0;
}