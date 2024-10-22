#include <cstdint>
#include <iostream>
#include <fstream>
#include <bitset>

#define LENGTH 1
#define MAXLEN 300
#define STUDENT_ID_LAST_DIGIT 9



int16_t lab1(int16_t n) {
    // initialize
	int16_t If_Odd=n;
	int16_t flag=0;
	int16_t k = 1;//k用来取与
	while(If_Odd>0){
		If_Odd=If_Odd-2;
	}
	if(If_Odd==0){       //偶数  取反运算
		n=~n;//TODO
		n=n+1;		
	}	                        //奇数  直接算0
	for(int i=1;i<=16;i++){
		if(!(n&k)){
				flag++;
		}
			k=k+k;
	}

    return flag+STUDENT_ID_LAST_DIGIT;
}

int16_t lab2(int16_t n) {
   int16_t v=3,d=1;
	for(int i=1;i<n;i++){
		if(d==1){
			v=v+v+2;
		}
		if(d==-1){
			v=v+v-2;
		}
		if(v>=4096) v=v-4096;
		int16_t temp = v;
//		printf("%d\n",v);
		while(temp>=0){
			if(temp==0) {
				d=~d;
				d++;
				break;
			}
			temp=temp-8;
		}
		temp=v-8;
		while(temp>=0){
			temp=temp-10;
			if(temp == 0) {
				d=~d;
				d++;
			}
		}
	}
	return v;
}

int16_t lab3(char s1[], char s2[]) {
	char*p = s1;
	char*q = s2;
	while(*p==*q){
		p++;
		q++;
		if(!*p||!*q) break;
	}
	
	return *p-*q;
}
void put(int16_t *memory, int16_t n,int16_t &num);
void remove(int16_t *memory, int16_t n,int16_t &num){
	if(n==0) return;
	if(n==1){
		if(num==1){
			memory[num]=1;
			num++;
		}
		else{
			memory [num]=memory[num-1]+1;
			num++;
		}
	}
	else {
		remove(memory,n-2,num);
		int16_t a=1;
		for(int i=1;i<n;i++){
			a=a+a;
		}
		memory[num]=memory[num-1]+a;
		num++;
		put(memory,n-2,num);
		remove(memory,n-1,num);
	}
}
void put(int16_t *memory, int16_t n,int16_t &num){
	if(n==0) return;
	if(n==1){
		memory[num]=memory[num-1]-1;
		num++;
	}
	else{
		put(memory,n-1,num);
		remove(memory,n-2,num);
		int16_t a=-1;
		for(int i=1;i<n;i++){
			a=a+a;
			//TODO
		}
		memory[num]=memory[num-1]+a;
		num++;
		put(memory,n-2,num);
	}
}
int16_t lab4(int16_t *memory, int16_t n) {
	int16_t loc =1;
	memory[0]=n;
	remove(memory,n,loc);
	return loc;
}

int main() {
    std::fstream file;
    file.open("test.txt", std::ios::in);

    // lab1
    int16_t n = 0;
    std::cout << "===== lab1 =====" << std::endl;
    for (int i = 0; i < LENGTH; ++i) {
        file >> n;
        std::cout << lab1(n) << std::endl;
    }

    // lab2
    std::cout << "===== lab2 =====" << std::endl;
    for (int i = 0; i < LENGTH; ++i) {
        file >> n;
        std::cout << lab2(n) << std::endl;
    }

    // lab3
    std::cout << "===== lab3 =====" << std::endl;
    char s1[MAXLEN]; char s2[MAXLEN];
    for (int i = 0; i < LENGTH; ++i) {
        file >> s1 >> s2;
        std::cout << lab3(s1, s2) << std::endl;
    }
    
    // lab4
    std::cout << "===== lab4 =====" << std::endl;
    int16_t memory[MAXLEN], move;
    for (int i = 0; i < LENGTH; ++i) {
        file >> n;
        int16_t state = 0;
        move = lab4(memory, n);
        for(int j = 0; j < move; ++j){
			std::cout << std::bitset<16>(memory[j]) << std::endl;
			//printf("%d\n",memory[j]);
        }
    }
    
    file.close();
    return 0;
}
