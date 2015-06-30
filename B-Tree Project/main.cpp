#include <iostream>
#include <fstream>
#include <vector>
#include "BTree.h" 
#include <stdio.h>      
#include <stdlib.h>     
#include <time.h> 
using namespace std ; 
int main(int argc , char** argv){
	int m , numberOfRecords , value , ref,deleteValue  , target;
	BTree obj , *obj2; /*
	cout<<"\tB-Tree Project \t"<<endl;
	char ch ; 
	cout<<"Please  Create Index File"<<endl; 
	cout<<"Enter the M  vlaue :"<<endl;
	cin >> m ; 
	cout<<"Enter the number of Records    :"<<endl;
	cin >> numberOfRecords ;
	obj.CreateIndexFileFile("BTree.txt" , numberOfRecords, m );
	cout<<"\n\tCreated !! "<<endl;
	while (true ){
		cout<<"1- Show the intial records"<<endl;
		cout<<"2- Insert New Record At index"<<endl;
		cout<<"3- Search A record "<<endl;
		cout<<"4- Delete Record From Index"<<endl;
		cout<<"5- Bouns Part "<<endl;
		cout<<"6- Exit !"<<endl;
		cin >> ch ; 
		switch (ch){
			case '1':
				obj.DisplayIndexFileContent("BTree.txt",m);
				break ;	
			case '2':
				cout<<"Enter the Value"<<endl;
				cin >> value ;
				cout<<"Enter the Reference"<<endl;
				cin >> ref ;
				obj.InsertNewRecordAtIndex ("BTree.txt", value, ref);
				break;
				
			case '3':
				cout<<"Enter the Target"<<endl;
				cin>> target ;
				cout<<obj.SearchARecord("BTree.txt", target , m)<<endl;
				break;
			case '4':
				cout<<"Enter the Value that u want to delete it "<<endl;
				cin>> deleteValue ; 
				obj.DeleteRecordFromIndex ("BTree.txt" , deleteValue, m ) ;
				break;
			case '5':
			{
				int i = 0 , n ;
				cout<<"Enter the number of record! "<<endl;
				cin >> numberOfRecords;
				obj.CreateIndexFileFile("BTree.txt" , numberOfRecords, m );
				cout<< "Created  "<<numberOfRecords <<" Records !"<<endl<<endl;
				cout<<"Enter the number of rundom number that you want to insert it "<<endl;
				cin>>n;
				while (i < n){
					
	 				int	r1 = rand() % 100;   //int x = rand( )%100;
	 				int r2 = rand() % 1000;
	 				obj.InsertNewRecordAtIndex ("BTree.txt", r1, r2);
	 				i++;
	 			}
	 			break; 
	 		}
	 		case '6':
	 			return 0 ; 
		}
		
	}
	*/

	obj.CreateIndexFileFile("BTree.txt" , 10, 5 );
 	obj.DisplayIndexFileContent("BTree.txt" , 5 );
 	obj.InsertNewRecordAtIndex ("BTree.txt", 3 , 12);
	obj.InsertNewRecordAtIndex ("BTree.txt", 7 , 24);
	obj.InsertNewRecordAtIndex ("BTree.txt", 10, 48);
	obj.InsertNewRecordAtIndex ("BTree.txt", 24, 60);
	obj.InsertNewRecordAtIndex ("BTree.txt", 14, 72);
	obj.InsertNewRecordAtIndex ("BTree.txt", 19, 84);
    obj.InsertNewRecordAtIndex ("BTree.txt", 30, 96);
    obj.InsertNewRecordAtIndex ("BTree.txt", 15, 108);
    obj.InsertNewRecordAtIndex ("BTree.txt", 1 , 120);
    obj.InsertNewRecordAtIndex ("BTree.txt", 5 , 132);
    obj.InsertNewRecordAtIndex ("BTree.txt", 2 , 144); 
    obj.InsertNewRecordAtIndex ("BTree.txt", 8 , 156); 
    obj.InsertNewRecordAtIndex ("BTree.txt", 9 , 168); 
    obj.InsertNewRecordAtIndex ("BTree.txt", 6 , 180); 
    obj.InsertNewRecordAtIndex ("BTree.txt", 11, 192); 
    obj.InsertNewRecordAtIndex ("BTree.txt", 12, 204);
    obj.InsertNewRecordAtIndex ("BTree.txt", 17, 216); 
    obj.InsertNewRecordAtIndex ("BTree.txt", 18, 228); 
    obj.InsertNewRecordAtIndex ("BTree.txt", 32, 240);
	cout<<endl ;
//	obj.DisplayIndexFileContent("BTree.txt" , 5 );
//	cout<<obj.SearchARecord("BTree.txt", 100 , 5)<<endl;
	
	obj.DeleteRecordFromIndex ("BTree.txt" , 10 , 5 ) ;
	obj.DisplayIndexFileContent("BTree.txt",5 );
	cout<<endl;
    obj.DeleteRecordFromIndex ("BTree.txt" , 9 , 5 ) ;
    cout<<endl<<endl;
   obj.DisplayIndexFileContent("BTree.txt",5 );
    obj.DeleteRecordFromIndex ("BTree.txt" , 8 , 5 );
  // obj.DeleteRecordFromIndex ("BTree.txt" ,7 , 5 );
 //  obj.DeleteRecordFromIndex ("BTree.txt" , 6 , 5 ) ;
    cout<<endl;
    obj.DisplayIndexFileContent("BTree.txt",5 );
    cout<<endl;
 	//obj.DeleteRecordFromIndex ("BTree.txt" , 3 , 5 ) ;
 	//obj.DeleteRecordFromIndex ("BTree.txt" , 7 , 5 ) ;
 	//obj.DeleteRecordFromIndex ("BTree.txt" , 6 , 5 ) ;
    //obj.DeleteRecordFromIndex ("BTree.txt" , 100 , 5 ) ;
	cout<<endl;
//	obj.DisplayIndexFileContent("BTree.txt",5 );
	
	return 0;	
}


















//Bouns Part
	 
