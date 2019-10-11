#include <stdio.h>
#include <iostream>
#include <algorithm>
#include <set>
#include <vector>
#include <map>
#include <list>
#include <deque>
#include <math.h>
#include <cstring>
#include <string.h>
#include <iomanip>
#include <stdlib.h>
#include <sstream>
#include <fstream>

using namespace std ;
#define ll long long

struct Item {
    int item_id ;
    string item_name ;
    int item_amount ;
    int price ;
    string type ;
    string shelf_number ;
    bool operator < ( const Item &a ) const {
        return item_id < a.item_id ;
    }
};

class program {
    private :
    vector < Item > a ;
    public :
    bool checkID(int x){
        for(int i=0;i<a.size();i++){
            if(x==a[i].item_id)
                return false;
        }
        return true ;
    }
    
    int new_item_id(){
        bool y = false ;
        int x;
        while ( !y ){
            cout<<"Enter Item ID\n";
            cin>>x;
            y = checkID(x) ;
            if ( !y )
                cout << "Id not valid , enter another one \n" ;
        }
        return x ;
    }
    
    string new_item_name(){
        string x;
        cout<<"Enter Item Name\n";
        cin>>x;
        return x;
    }
    
    int new_item_amount(){
        int x;
        cout<<"Enter Item Amount\n";
        cin>>x;
        return x;
    }
    
    int new_price(){
        int x;
        cout<<"Enter Price\n";
        cin>>x;
        return x;
    }
    
    string new_type(){
        string x;
        cout<<"Enter Type\n";
        cin>>x;
        return x;
    }
    
    string new_shelf_number(){
        string x;
        cout<<"Enter Shelf Number\n";
        cin>>x;
        return x;
    }
    
    Item insertItem (){
        Item item ;
        item.item_id = new_item_id();
        item.item_name = new_item_name();
        item.item_amount = new_item_amount();
        item.price = new_price();
        item.type = new_type();
        item.shelf_number = new_shelf_number();
        return item;
    }
    
    int fromStringToInt ( string x ){
        int ret = 0 ;
        for ( int i = 0 ; i < x.length() ; ++i ){
            while ( isdigit( x [ i ] ) ){
                int num = x [ i++ ] - '0' ;
                ret = ( ret * 10 ) + num ;
            }
        }
        return ret ;
    }

    void displayAll () {
        cout << "-----------------------------------------\n" ;
        for ( int i = 0 ; i < a.size() - 1 ; ++i ){
            cout << "\t\t\tItem Detail : " << i + 1 << endl ;
            cout << "item Id : " << a [ i ].item_id << endl ;
            cout << "item Name : " << a [ i ].item_name << endl ;
            cout << "item amount : " << a [ i ].item_amount << endl ;
            cout << "price : " << a [ i ].price << endl ;
            cout << "shelf Number : " << a [ i ].shelf_number << endl ;
            cout << "---------------------------\n" ;
        }
        cout << "-----------------------------------------\n" ;
    }

    int searchByBinarySearch ( int id ){
        sort ( a.begin() , a.end() ) ;
        int l = 0 , h = ( int ) a.size() - 1 ;
        while ( l <= h ) {
            int mid = ( l + h ) / 2 ;
            if ( a [ mid ].item_id == id )
                return mid ;
            else{
                if ( a [ mid ].item_id > id )
                    h = mid - 1 ;
                else
                    l = mid + 1 ;
            }
        }
        return -1 ;
    }

    int UpdateById ( int id ){
        int index = searchByBinarySearch( id ) ;
        if ( index == -1 ){
            return -1 ;
        }else{
            cout << "item Id : " << a [ index ].item_id << endl ;
            cout << "item Name : " << a [ index ].item_name << endl ;
            cout << "item amount : " << a [ index ].item_amount << endl ;
            cout << "price : " << a [ index ].price << endl ;
            cout << "shelf Number : " << a [ index ].shelf_number << endl ;
            cout << "------------------------\n" ;
            cout << "Enter The new amount for the item : " ;
            cin >> a [ index ].item_amount ;
            cout << "Item updated succssfully .\n" ;
        }
        return index ;
    }

    int deleteById ( int id ) {
        int index = searchByBinarySearch( id ) ;
        if ( index == -1 )
            return -1 ;
        else{
            vector < Item > b ;
            for ( int i = 0 ; i < a.size() ; ++i )
                if ( i != index )
                    b.push_back( a [ i ] ) ;
            a = b ;
        }
        return index ;
    }

    void insertItemsToFile ( ){
        sort ( a.begin() , a.end() ) ;
        fstream myFile ;
        myFile.open( "myFile.txt" , ios :: out ) ;
        for ( int i = 0 ; i < a.size() ; ++i ){
            Item item = a [ i ] ;
            if ( item.item_id != 0 ){
            
            if ( i ){
                myFile << endl << item.item_id << "|" ;
                myFile << item.item_name << "|" ;
                myFile << item.item_amount << "|" ;
                myFile << item.price << "|" ;
                myFile << item.type << "|" ;
                myFile << item.shelf_number << "|" ;
            }else{
                myFile << item.item_id << "|" ;
                myFile << item.item_name << "|" ;
                myFile << item.item_amount << "|" ;
                myFile << item.price << "|" ;
                myFile << item.type << "|" ;
                myFile << item.shelf_number << "|" ;
            }}
        }
        myFile.close() ;
    }

    void readAllItems (){
        fstream myFile ;
        myFile.open( "myFile.txt" , ios :: in ) ;
        string temp ;
        if ( myFile.is_open() ){
            while ( !myFile.eof() ) {
                Item newItem ;
                getline( myFile , temp , '|' ) ;
                newItem.item_id = fromStringToInt( temp ) ;
                getline( myFile , temp , '|' ) ;
                newItem.item_name = temp ;
                getline( myFile , temp , '|' ) ;
                newItem.item_amount = fromStringToInt( temp ) ;
                getline( myFile , temp , '|' ) ;
                newItem.price = fromStringToInt( temp ) ;
                getline( myFile , temp , '|' ) ;
                newItem.type = temp ;
                getline( myFile , temp , '|' ) ;
                newItem.shelf_number = temp ;
                a.push_back( newItem ) ;
            }
        }
        myFile.close() ;
        
    }

    void clearItemsFromMemory (){
        a.clear() ;
    }

    void displyOneItem ( int index ) {
        cout << "Item Detail:\n" ;
        cout << "item Id : " << a [ index ].item_id << endl ;
        cout << "item Name : " << a [ index ].item_name << endl ;
        cout << "item amount : " << a [ index ].item_amount << endl ;
        cout << "price : " << a [ index ].price << endl ;
        cout << "shelf Number : " << a [ index ].shelf_number << endl ;
        cout << "------------------------\n" ;
    }

    void mainProgram (){
        beg :
        system ( "cls" ) ;
        cout << "----------Welcome To our Program------------\n" ;
        cout << "Enter 1 for Displaying Items.\n" ;
        cout << "Enter 2 to Insert a newItem.\n" ;
        cout << "Enter 3 to Search For Items.\n" ;
        cout << "Enter 4 to Update Item amount .\n" ;
        cout << "Enter 5 to delete Item.\n" ;
        int chois ;
        cin >> chois ;
        if ( chois == 1 ){
			readAllItems () ;
            displayAll() ;
            clearItemsFromMemory();
        }else if ( chois == 2 ){
			readAllItems () ;
            a.push_back ( insertItem() ) ;
            insertItemsToFile () ;
            clearItemsFromMemory();
        }
        else if ( chois == 3 ){
			readAllItems () ;
            int id ;
            cout << "Enter The Id for The Item : " ;
            cin >> id ;
            int index = searchByBinarySearch ( id ) ;
            if ( index == -1 )
                cout << "Item not Found , try Later.\n" ;
            else
                displyOneItem ( index ) ;
            	clearItemsFromMemory();
        }else if ( chois == 4 ){
			readAllItems () ;
            cout << "Enter the ID for The Item You want to update : " ;
            int id ;
            cin >> id ;
            int index = UpdateById ( id ) ;
            if ( index == -1 )
                cout << "Item not Found , try Later.\n" ;
            else
                insertItemsToFile () ;
            clearItemsFromMemory();
        }else if ( chois == 5 ){
			readAllItems () ;
            cout << "Enter the ID for The Item You want to delete : " ;
            int id ;
            cin >> id ;
            int index = deleteById ( id ) ;
            if ( index == -1 )
                cout << "Item not Found , try Later.\n" ;
            else
                insertItemsToFile () ;
            clearItemsFromMemory();
        }else
            cout << "wrong option , try Later.\n" ;
        cout << "Enter 1 to run again : " ;
        int ch ;
        cin >> ch ;
        if ( ch == 1 )
            goto beg ;
    }
    
};

int main(){
    program myProg ;
    myProg.mainProgram() ;
    return 0 ;
}
