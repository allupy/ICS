#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 100
#define Max_Name_Length 20  //每个索引最大长度
#define Number 11   //关键字索引
typedef struct SymbolTable{
	char name[Max_Name_Length];
	int LOC ;  //
}ST;
// Function prototypes
void read_asm_file(const char *filename, char lines[][MAX_LINE_LENGTH], int *num_lines);
void write_output_file(const char *filename, const char *output[], int num_lines);
void assemble(char lines[][MAX_LINE_LENGTH], int num_lines, char *output[]);
void translate_instruction(const char *instruction, char *machine_code);

// TODO: Define any additional functions you need to implement the assembler, e.g. the symbol table.

int main(int argc, char *argv[])
{
	// Command-line argument parsing
	if (argc != 3)
	{
		fprintf(stderr, "Usage: %s <input_file.asm> <output_file.txt>\n", argv[0]);
		return 1;
	}
	
	char input_filename[100];
	char output_filename[100];
	strcpy(input_filename, argv[1]);
	strcpy(output_filename, argv[2]);
	
	char lines[100][MAX_LINE_LENGTH]; // Assuming a maximum of 100 lines
	int num_lines = 0;
	read_asm_file(input_filename, lines, &num_lines);
	
	char *output[100]; // Output array of strings
	for (int i = 0; i < 100; i++)
	{
		output[i] = (char *)malloc(MAX_LINE_LENGTH * sizeof(char));
	}
	//printf("%s",lines[0]);
	assemble(lines, num_lines, output);
	write_output_file(output_filename, (const char **)output, num_lines);
	
	// Free allocated memory
	for (int i = 0; i < 100; i++)
	{
		free(output[i]);
	}
	return 0;
}

void read_asm_file(const char *filename, char lines[][MAX_LINE_LENGTH], int *num_lines)
{
	FILE *file = fopen(filename, "r");
	if (file == NULL)
	{
		fprintf(stderr, "Unable to open file: %s\n", filename);
		exit(1);
	}
	
	char line[MAX_LINE_LENGTH];
	while (fgets(line, MAX_LINE_LENGTH, file))
	{
		strcpy(lines[*num_lines], line);      //一行一行的读
		(*num_lines)++;
	}
	
	fclose(file);
}

void write_output_file(const char *filename, const char *output[], int num_lines)
{
	FILE *file = fopen(filename, "w");
	if (file == NULL)
	{
		fprintf(stderr, "Unable to open file: %s\n", filename);
		exit(1);
	}
	
	for (int i = 0; i < num_lines; i++)
	{
		fprintf(file, "%s\n", output[i]);      //
	}
	
	fclose(file);
}
int Initialize(char ASM[][Max_Name_Length],char DEC[][Max_Name_Length]){//把汇编码文件读到ASM里边
	FILE*fp;
	fp=fopen("sample.txt","r");
	if (fp == NULL)
	{
		fprintf(stderr, "Unable to open file: \n" );
		return -1;
	}
	for(int i=0;i<Number;i++){
		fscanf(fp,"%s",ASM[i]);
		//printf("%s\n",ASM[i]);
		fscanf(fp,"%s",DEC[i]);
		//printf("%s\n",DEC[i]);
	}
	return 0;
}

void assemble(char lines[][MAX_LINE_LENGTH], int num_lines, char *output[])
{
	// TODO: Implement the assembly process
	// Implement the 2-pass process described in textbook.
	//the first pass:creating the symbol table
	char ASM[Number][Max_Name_Length];
	char DEC[Number][Max_Name_Length];
	ST Table[MAX_LINE_LENGTH];
	char temp[Max_Name_Length];
	int j=0,k=0,p=0,m=0;
	//int LOC=0;              //Memory Location
	if(Initialize(ASM,DEC)==-1){return ;}  //错误文件读取排除
	int length=0;
	for(int u=0;u<num_lines-1;u++){
		length=strlen(lines[u]);
		lines[u][length-1]='\0';         //辅助输入，完善之前
		//printf("%s\n",lines[u]);
	}
	//第一趟遍历 找出所有table并删除
	//printf("a");
	for (int i = 0; i < num_lines; i++)
	{   
		j=0;
		//printf("OK");
		while(lines[i][j]!=' '&&lines[i][j]!='\0') //标签开头一般没有空格，标签和其他的东西由空格隔开
		{
			temp[k++]=lines[i][j++];    //可以说是把每一行的开头一个小词语放到temp里边
		}
		//printf("OK");
		temp[k]='\0';
		//printf("%s\n",temp);
		for (p=0; p<Number; p++)
		{
			if(!strcmp(temp,ASM[p])){   //把这些小词语和指令名字对比，是标签的成立条件为不是指令
				break;
			}
			
		}
		if(p==Number){
			strcpy(Table[m].name,temp);
			Table[m].LOC=i; //例如：第二行标签Main 应该为3000+1-1=3000
			//建立table
			//printf("%s %d",Table[m].name,Table[m].LOC);
			j++;m++;
			strcpy(lines[i],&lines[i][j]); //把标签后面的一段具体指令放到这句话里面，叠掉了指令
			//移除标签
		}
		k=0;
		//printf("%s\n",lines[i]);
	}
	int pos=0;
	for (int i = 0; i < num_lines; i++)
	{   
		j=0;pos=0;
		while(lines[i][j]!='\0')
		{   k=0;
			while(lines[i][j]!=' '&&lines[i][j]!='\0'&&lines[i][j]!='#')
			{
				temp[k++]=lines[i][j++];
			}
			temp[k]='\0';
			for (p=0; p<Number; p++)
			{
				if(!strcmp(temp,ASM[p]))
				{   if(p==7||p==8){output[i][0]='\n';output[i][1]='\0';break;}
					else{strcpy(&output[i][pos],DEC[p]);
						pos+=strlen(DEC[p]);
						break;}
					
				}
				
			}
			if(p==7||p==8){break;}
			if(p==Number)
			{
				for(p=0;p<m;p++)
				{
					if(!strcmp(temp,Table[p].name))
					{   int loc=Table[p].LOC;
						loc=loc-i-1;
						if(loc<0){
							loc=512+loc;
						}
						printf("aa%d\n",Table[p].LOC);
						int loc2=0;
						char binary0[9];
						for(p=0;p<9;p++){binary0[p]='0';}
						p=0;
						while(loc){
							loc2=loc/2;
							binary0[p]=loc-2*loc2+48;
							p++;
							loc=loc/2;
						}
						for(int k=8;k>=0;k--){
							temp[k]=binary0[8-k];
						}
						temp[9]='\0';
						
						printf("%s\n",temp);
						strcpy(&output[i][pos],temp);
						pos+=strlen(temp);
						break;
					}
				}   
			}
			if(lines[i][j]=='#')
			{                       //十进制转二进制
				char binary[5]={'0','0','0','0','0'};
				int flag=0;
				if(lines[i][j+1]=='-'){
					j++;
					flag=1;
				}
				int val[2]={0};
				p=0;
				while(lines[i][++j]!='\0'){
					val[p]=lines[i][j]-48;
					p++;
				}
				//printf("%daa",p);
				if(p==2){val[0]=10*val[0]+val[1];}
				p=0;
				if(flag==1){val[0]=32-val[0];}
				//printf("%d",val[0]);
				while(val[0]){
					val[1]=val[0]/2;
					binary[p]=val[0]-2*val[1]+48; 
					p++;
					val[0]=val[0]/2;
				}
				for(k=5;k>=1;k--){
					temp[k]=binary[5-k];
				}
				temp[6]='\0';
				temp[0]='1';
				//printf("\n%s",temp);
				strcpy(&output[i][pos],temp);
				pos+=5;
				break;
			}
			if(lines[i][j]==' '){j++;}
		}
	}
}


