//
//  main.cpp
//  BookStoreFinalProject
//
//  Created by Valery on 24.12.2024.
//

#include <iostream>
#include <cstring>
#include "Date.h"
#include "Client.h"
#include "Book.h"
#include "ArrayTemplate.h"

#define Load 0

using namespace std;



int main(int argc, const char * argv[]) {

    FILE* fileBooks = nullptr;
    int amountOfBooks = 0;
    Book* arrBooks = nullptr;

#if Load == 0
    amountOfBooks = 2;
    arrBooks = new Book[2]{{"The Cruel Prince", 380, "Holly Black", 3, "Fantasy", 2, new Client[2]{
        {{1,1,2024}, "Celaena Sardothien", 17, "+3807738829", "yes"},
        {{11,12,2023}, "Kazi", 25, "+380483829", "yes"}
    }},
        {"Shatter Me", 1350, "Tahereh Mafi", 9, "Fantasy", 2, new Client[2]{
            {{1,1,2024}, "Kira", 13, "+38049498829", "yes"},
            {{11,12,2023}, "Maina", 25, "+380488829", "yes"}
        }}
    };
#else
    fileBooks = fopen("Books.bin", "rb");
    if(fileBooks == nullptr) {
        cout << "Error: Unable to load file." << endl;
    } else {
        fread(&amountOfBooks, sizeof(int), 1, fileBooks);
        arrBooks = new Book[amountOfBooks];
        for(int i = 0; i < amountOfBooks; i++) {
            arrBooks[i].loadFromBinFile(fileBooks);
        }
        fclose(fileBooks);
        cout << "Books loaded successfully." << endl;
    }
#endif

    int doingNum = -1;
    Book tempBook;
    char text[100]="";
    int id = -1;
    Client tempClient;

    while(true) {
        cout<<"=============================\n";
        cout<<"\tActions:\n";
        cout<<"=============================\n";
        cout<<"0-Exit\n";
        cout<<"1-Books in stock\n";
        cout<<"2-All Clients\n";
        cout<<"3-Add Book in base\n";
        cout<<"4-Add Client in base\n";
        cout<<"5-All info\n";
        cout<<"6-sort (from lowest to greatest) number of pages\n";
        cout<<"7-sort (from greatest to lowest) number of pages\n";
        cout<<"8-sort by title (alphabetic order)\n";
        cout<<"9-sort (from lowest to greatest) number of books in the series\n";
        cout<<"10-sort (from greatest to lowest) number of books in the series\n";
        cout<<"11-Delete book \n";
        
        cout<<"----------------------------\n";
        cout<<"Enter num to do: ";
        cin>>doingNum;
        
        if(doingNum==0){
            break;
        }
        
        switch (doingNum) {
            case 1:
                for(int i = 0;i<amountOfBooks;i++){
                    cout<<"#"<<i+1<<". "<<arrBooks[i].title<<" "<<endl;
                }
                break;
            case 2:
                for(int i = 0; i<amountOfBooks;i++){
                    for(int j=0;j<arrBooks[i].numOfClients;j++){
                        arrBooks[i].arrClients[j].printClient();
                        cout<<"---------\n";
                    }
                }
                break;
            case 3:
                tempBook.addOnlyBook();
                addItemBack(arrBooks, amountOfBooks, tempBook);
                break;
            case 4:
                cin.ignore();
                cout<<"Input book name: ";
                cin.getline(text, 100);
                id = -1;
                for (int i=0; i<amountOfBooks; i++) {
                    if(strcmp(arrBooks[i].title,text)==0){
                        id = i;
                        break;
                    }
                }
                if(id ==-1){
                    cout<<"Not found. Add new book"<<endl;
                    
                }else{
                    cout<<"Have found"<<endl;
                    tempClient.fillClient();
                    addItemBack(arrBooks[id].arrClients, arrBooks[id].numOfClients, tempClient);
                    
                }
                
                break;
            case 5:
                for(int i = 0;i<amountOfBooks;i++){
                    arrBooks[i].printBook();
                }
                break;
            case 6:
                //sort (from lowest to greatest) number of pages
                sort<Book>(arrBooks,amountOfBooks,[](Book a, Book b){
                    return a.pages>b.pages;
                });
                for(int i = 0;i<amountOfBooks;i++){
                    cout<<arrBooks[i].title<<endl;
                    cout<<arrBooks[i].pages<<endl;
                    
                }
                break;
            case 7:
                //sort (from greatest to lowest) number of pages
                sort<Book>(arrBooks,amountOfBooks,[](Book a, Book b){
                    return a.pages<b.pages;
                });
                for(int i = 0;i<amountOfBooks;i++){
                    cout<<arrBooks[i].title<<endl;
                    cout<<arrBooks[i].pages<<endl;
                    
                }
                break;
            case 8:
                //sort by title (alphabetic order)
                sort<Book>(arrBooks, amountOfBooks, [](Book a, Book b){
                    return strcmp(a.title, b.title)>0;
                });
                
                for(int i = 0;i<amountOfBooks;i++){
                    cout<<arrBooks[i].title<<endl;
                }
                break;
            case 9:
                //sort (from lowest to greatest) number of books in the series
                sort<Book>(arrBooks,amountOfBooks,[](Book a, Book b){
                    return a.inTheSeries>b.inTheSeries;
                });
                for(int i = 0;i<amountOfBooks;i++){
                    cout<<arrBooks[i].title<<endl;
                    cout<<arrBooks[i].inTheSeries<<endl;
                }
                break;
            case 10:
                //sort (from greatest to lowest) number of books in the series
                sort<Book>(arrBooks,amountOfBooks,[](Book a, Book b){
                    return a.inTheSeries<b.inTheSeries;
                });
                for(int i = 0;i<amountOfBooks;i++){
                    cout<<arrBooks[i].title<<endl;
                    cout<<arrBooks[i].inTheSeries<<endl;
                }
                break;
                
            case 11:
            {
                string bookName;
                cout << "Enter the title of the book to delete: ";
                cin.ignore();
                getline(cin, bookName);
                
                arrBooks->deleteBookByTitle(arrBooks, amountOfBooks, bookName);
                break;
            }
                
            default:
                break;
        }
    }
    
    
    //----------------------------------
    // Save arr
    fileBooks = fopen("Books.bin", "wb");
    if (fileBooks == nullptr) {
        cout << "Error: Unable to open file for saving." << endl;
        return 1;
    }
    fwrite(&amountOfBooks, sizeof(int), 1, fileBooks);
    for (int i = 0; i < amountOfBooks; i++) {
        arrBooks[i].saveToBinFile(fileBooks);
    }
    fclose(fileBooks);

    cout << "Data saved successfully.\n";
    delete[] arrBooks;
    
    
    return 0;
}
