//
//  Client.h
//  BookStoreFinalProject
//
//  Created by Valery on 24.12.2024.
//

#ifndef Client_h
#define Client_h




#include <iostream>
#include "Date.h"
#include <cstring>
using namespace std;

struct Client{
    Date ofBuy;
    char name[100]="";
    int age = 0;
    char phone[50] = "";

    char wantToBuy[10]="";
    
    void fillClient(){
        cout<<"Enter date of making the order: ";
        cin>>ofBuy.day>>ofBuy.month>>ofBuy.year;
        
        cout<<"Your name: ";
        cin.ignore();
        cin.getline(name,100);
        
        cout<<"Your age: ";
        cin>>age;
        
        cout<<"Your phone: ";
        cin>>phone;
        
        
        cout<<"Do you want to but it? : ";
        cin>>wantToBuy;
        
        
    }
    void printClient(){
        cout<<"\t Date: "<<ofBuy.toString("%d.%m.%Y")<<endl;
        cout<<"\t Name: "<<name<<endl;
        cout<<"\t Age: "<<age<<endl;
        cout<<"\t Phone: "<<phone<<endl;

        cout<<"\t Want to buy?: "<<wantToBuy<<endl;

   
    }
    void saveToBinFile(FILE* file){
        
        fwrite(&ofBuy, sizeof(Date), 1, file); //save date
        
        int sizenameC = strlen(name)+1;
        fwrite(&sizenameC, sizeof(int), 1, file); //save name-title
        fwrite(name, sizeof(char), sizenameC, file);
        
        fwrite(&age, sizeof(int), 1, file); //save pages
        
        int sizephone = strlen(phone)+1;
        fwrite(&sizephone, sizeof(int), 1, file); //save author
        fwrite(phone, sizeof(char), sizephone, file);
        
        
        int sizewantToBuy = strlen(wantToBuy)+1;
        fwrite(&sizewantToBuy, sizeof(int), 1, file); //save genre
        fwrite(wantToBuy, sizeof(char), sizewantToBuy, file);
        
        
    }
    
    void loadFromBinFile(FILE* file){
        
        fread(&ofBuy, sizeof(Date), 1, file);
        
          int sizenameC1 = 0;
          fread(&sizenameC1, sizeof(int), 1, file);
          fread(name, sizeof(char), sizenameC1, file);
          
          fread(&age, sizeof(int), 1, file);
          
          int sizename2 = 0;
          fread(&sizename2, sizeof(int), 1, file);
          fread(phone, sizeof(char), sizename2, file);
          
          
          int sizename3 = 0;
          fread(&sizename3, sizeof(int), 1, file);
          fread(wantToBuy, sizeof(char), sizename3, file);

          
      }

};

#endif /* Client_h */
