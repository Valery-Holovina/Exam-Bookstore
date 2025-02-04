//
//  Book.h
//  BookStoreFinalProject
//
//  Created by Valery on 24.12.2024.
//

#ifndef Book_h
#define Book_h

#include "Client.h"

struct Book{
    char title[100]="";
    int pages = 0;
    char author[100]="";
    int inTheSeries = 0;
    char genre[50]="";
    
    int numOfClients = 0;
    Client* arrClients = nullptr;
    
    void fillBook(){
        cout<<"Title: ";
        cin.ignore();
        cin.getline(title,100);
        
        cout<<"Pages: ";
        cin>>pages;
        
        cout<<"Author: ";
        cin.ignore();
        cin.getline(author,100);
        
        cout<<"Amount of books in the series: ";
        cin>>inTheSeries;
        
        cout<<"Genre: ";
        cin.ignore();
        cin.getline(genre,50);
        
        numOfClients = 1;
        arrClients= new Client[1];
        arrClients[0].fillClient();


    }
    void printBook(){
        cout<<"---------------------------\n";
        cout<<"Title: "<<title<<endl;
        cout<<"Pages: "<<pages<<endl;
        cout<<"Author: "<<author<<endl;
        cout<<"In the series: "<<inTheSeries<<endl;
        cout<<"Genre: "<<genre<<endl;
        cout<<"Clients: "<<numOfClients<<endl;
        
        for(int i = 0 ;i<numOfClients;i++){
            cout<<"\t #"<<i+1<<endl;
            arrClients[i].printClient();
        }
        cout<<"---------------------------\n";





    }
    void addOnlyBook(){
        cout<<"Title: ";
        cin.ignore();
        cin.getline(title,100);
        
        cout<<"Pages: ";
        cin>>pages;
        
        cout<<"Author: ";
        cin.ignore();
        cin.getline(author,100);
        
        cout<<"Amount of books in the series: ";
        cin>>inTheSeries;
        
        cout<<"Genre: ";
        cin.ignore();
        cin.getline(genre,50);
        
        numOfClients = 0;
        arrClients= nullptr;

    }
    
    
    void saveToBinFile(FILE* file){
        
        int sizename = strlen(title)+1;
        fwrite(&sizename, sizeof(int), 1, file); //save name-title
        fwrite(title, sizeof(char), sizename, file);
        
        fwrite(&pages, sizeof(int), 1, file); //save pages
        
        int sizeauthor = strlen(author)+1;
        fwrite(&sizeauthor, sizeof(int), 1, file); //save author
        fwrite(author, sizeof(char), sizeauthor, file);
        
        fwrite(&inTheSeries, sizeof(int), 1, file); //save num in the series
        
        
        int sizegenre = strlen(genre)+1;
        fwrite(&sizegenre, sizeof(int), 1, file); //save genre
        fwrite(genre, sizeof(char), sizegenre, file);
        
        
        fwrite(&numOfClients, sizeof(int), 1, file);
        if (numOfClients > 0) {
            for (int i = 0; i < numOfClients; i++) {
                arrClients[i].saveToBinFile(file);
            }
        }

        
        
    }
    
        void loadFromBinFile(FILE* file){
              int sizename = 0;
              fread(&sizename, sizeof(int), 1, file);
              fread(title, sizeof(char), sizename, file);
              
              fread(&pages, sizeof(int), 1, file);
              
              int sizename2 = 0;
              fread(&sizename2, sizeof(int), 1, file);
              fread(author, sizeof(char), sizename2, file);
              
              fread(&inTheSeries, sizeof(int), 1, file);
              
              int sizename3 = 0;
              fread(&sizename3, sizeof(int), 1, file);
              fread(genre, sizeof(char), sizename3, file);
              
            fread(&numOfClients, sizeof(int), 1, file);
            if (numOfClients > 0) {
                arrClients = new Client[numOfClients];
                for (int i = 0; i < numOfClients; i++) {
                    arrClients[i].loadFromBinFile(file);
                }
            }
              
          }


    
    void deleteBookByTitle(Book* &arrBooks, int &amountOfBooks, const string &title) {
        int index = -1;
        for (int i = 0; i < amountOfBooks; i++) {
            if (arrBooks[i].title == title) {
                index = i;
                break;
            }
        }
        if (index == -1) {
            cout << "Book not found!" << endl;
            return;
        }

        delete[] arrBooks[index].arrClients; // Delete dynamically allocated Client array
        for (int i = index; i < amountOfBooks - 1; i++) {
            arrBooks[i] = arrBooks[i + 1];
        }
        
        Book* temp = new Book[amountOfBooks - 1];
        for (int i = 0; i < amountOfBooks - 1; i++) {
            temp[i] = arrBooks[i];
        }
        delete[] arrBooks;
        arrBooks = temp;
        amountOfBooks--;
        cout << "Book deleted successfully!" << endl;
    }
    
    


};



#endif /* Book_h */
