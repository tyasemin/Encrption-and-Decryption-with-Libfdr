#include <stdlib.h>
#include <stdio.h>
#include <getopt.h>
#include "fields.h"
#include "jrb.h"
#include <string.h>
#include <math.h>
typedef struct{
 char* kelime;
 int kod;
 char *key;
 int kod_uzunlugu;

}Tree;


void print_codes_with_lead_zeros(Tree *tr_tmp,FILE *fp1);



int main(int argc,char** argv){
       IS is;
       int i;
       JRB t,tmp;
       Tree *tr,*t1;
       int uzunluk;
       int nsize;
       int result=1;
       
       is=new_inputstruct(".kilit");
       t=make_jrb();
       
       
       
       

       int option;
       while((option=getopt(argc,argv,"ed"))!=-1){
             switch(option){
                  //ENKRİPTOLAMA BOLUMU
                  case'e':
                       
                       printf("Enkripto islemi basliyor\n");
                       while(get_line(is)>=0){
                        if(is->NF==2){
                         char* token_key=strtok(is->fields[is->NF-1],"\"");
                         is->fields[is->NF-1]=token_key;
                         tr=malloc(sizeof(Tree));
                         tr->kod_uzunlugu=strlen((is->fields[is->NF-1]));
                         tr->kod=atoi(is->fields[is->NF-1]);
                         //printf("Kod: %d\n",tr->kod);
                         
                         char *token_kelime=strtok(is->fields[0],"\"");
                         is->fields[0]=token_kelime;
                         //printf("Kelime(value): %s\n",token_kelime);
                         
                         uzunluk=strlen(token_kelime);
                         //printf("Kelime(value)uzunlugu: %d\n",uzunluk);
                         
                         for(int i=1;i<is->NF-1;i++){
                          if(is->NF==2){
                           char *token_tmp=strtok(is->fields[i],"\"");
                           is->fields[i]=token_tmp;
                           uzunluk+=(strlen(is->fields[i])+1);
                          
                          }
                         }
                         
                         tr->kelime=(char*)malloc(sizeof(char)*(uzunluk+1));
                         strcpy(tr->kelime,is->fields[0]);
                         
                         uzunluk=strlen(is->fields[0]);
                         
                         for(int i=1;i<is->NF-1;i++){
                            tr->kelime[uzunluk]=' ';
                            strcpy(tr->kelime+uzunluk+1,is->fields[i]);
                            uzunluk+=strlen(tr->kelime+nsize);
                         }
                         
                         tr->key=(char*)malloc(sizeof(char)*(nsize+12));
                         sprintf(tr->key,"%s %10d",tr->kelime,tr->kod);
                         jrb_insert_str(t,tr->key,new_jval_v((void*)tr));
                          }
                        }
                        jettison_inputstruct(is);
                        
                        jrb_traverse(tmp,t){
                        tr=(Tree*) tmp->val.v;
                        //printf("%-40s %d %d\n",tr->kelime,tr->kod,tr->kod_uzunlugu);
                        }
                        
                        IS is_read_file;
                        is_read_file=new_inputstruct(argv[2]);
                        
                        FILE *fp;
                        fp=fopen(argv[3],"w");
                        
                        while(get_line(is_read_file)>=0){
                          for(int i=0;i<is_read_file->NF;i++){
                            jrb_traverse(tmp,t){
                             tr=(Tree*) tmp->val.v;
                             
                             if(!strcmp(tr->kelime,is_read_file->fields[i]))
                             {
                                 
                                 print_codes_with_lead_zeros(tr,fp);
                                 printf("\n");
                                 result=1;
                                 break;
                             
                             }
                             else{
                                //printf("%s",is_read_file->fields[i]);
                                //printf("\n");
                                result=0;
                             
                             } 
                           
                            }
                           if(result==0){
                           printf("%s",is_read_file->fields[i]);
                           printf("\n");
                           fprintf(fp,"%s",is_read_file->fields[i]);
                           fprintf(fp," ");
                           
                           }
                            
                            
                          }
                        
                        }
                        fclose(fp);
                        jettison_inputstruct(is_read_file);
                       
                        break;
                  //-----------------DEKRİPTOLAMA BOLUMU---------------//
                  case 'd':
                     
                
                        printf("Dekripto islemi basliyor\n");
                        
                       while(get_line(is)>=0){
                         if(is->NF==2){
                          
                         char *token_key=strtok(is->fields[is->NF-1],"\"");
                         is->fields[is->NF-1]=token_key;
                         tr=malloc(sizeof(Tree));
                         tr->kod_uzunlugu=strlen((is->fields[is->NF-1]));
                         tr->kod=atoi(is->fields[is->NF-1]);
                         
                         char* token_kelime=strtok(is->fields[0],"\"");
                         is->fields[0]=token_kelime;
                         //printf("Kelime(value): %s\n",token_kelime);
                         
                         uzunluk=strlen(token_kelime);
                         //printf("Kelime(value) uzunlugu:%d\n",uzunluk);
                         
                         for(int i=1;i<is->NF-1;i++){
                          if(is->NF==2){
                          char *token_tmp=strtok(is->fields[i],"\"");
                          is->fields[i]=token_tmp;
                          
                          uzunluk+=(strlen(is->fields[i])+1);
                         
                           } 
                         }
                          
                        tr->kelime=(char*)malloc(sizeof(char)*(uzunluk+1));
                        strcpy(tr->kelime,is->fields[0]);
                         
                         uzunluk=strlen(is->fields[0]);
                         
                         for(int i=1;i<is->NF-1;i++){
                          tr->kelime[uzunluk]=' ';
                          strcpy(tr->kelime+uzunluk+1,is->fields[i]);
                          uzunluk+=strlen(tr->kelime+nsize);
                         }
                         
                         tr->key=(char*)malloc(sizeof(char)*(nsize+12));
                         sprintf(tr->key,"%10d %s",tr->kod,tr->kelime);
                         
                         jrb_insert_str(t,tr->key,new_jval_v((void*)tr));
                          }
                        }
                        
                        jrb_traverse(tmp,t){
                        tr=(Tree*)tmp->val.v;
 
                        }
                        IS is_read_file1;
                        is_read_file1=new_inputstruct(argv[2]);
   
                        FILE *fp1;
                        fp1=fopen(argv[3],"w");
                        
                        while(get_line(is_read_file1)>=0){

                        
                          for(int i=0;i<is_read_file1->NF;i++){
                            jrb_traverse(tmp,t){
                             tr=(Tree*) tmp->val.v;

                             if(tr->kod==atoi(is_read_file1->fields[i]) && tr->kod_uzunlugu==strlen(is_read_file1->fields[i]))
                             {
                                 fprintf(fp1,"%s",tr->kelime);
                                 fprintf(fp1," ");
                                 printf("%s",tr->kelime);
                                 printf("\n");
                                 result=1;
                                 break;
                             
                             }
                             else{
                                
                                result=0;
                             
                             } 
                           
                            }
                           if(result==0){
                           printf("%s",is_read_file1->fields[i]);
                           printf("\n");
                           fprintf(fp1,"%s",is_read_file1->fields[i]);
                           fprintf(fp1," ");
                           
                           }
                            
                            
                          }
                        
                        }
                        fclose(fp1);
                        jettison_inputstruct(is_read_file1);
                        
                        
                       
                        
                        
                        break;
                        
                  default:
                        printf("Error");
                   
             }
       
       }
       return 0;
       
}

void print_codes_with_lead_zeros(Tree *tr_tmp,FILE *fp1){
      
      int total_length=tr_tmp->kod_uzunlugu;
      int tmp=tr_tmp->kod;
      int current_length=0;
      int difference=0;
      
      do{
      
        current_length++;
        tmp /=10;
      }
      while(tmp!=0);

      difference=total_length-current_length;
      
      for(int i=0;i<difference;i++){
       
          printf("0");
          fprintf(fp1,"0");
        }
        
       printf("%d",tr_tmp->kod);
       fprintf(fp1,"%d",tr_tmp->kod);
       fprintf(fp1," ");
}


