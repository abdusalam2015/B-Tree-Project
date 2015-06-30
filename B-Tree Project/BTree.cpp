#include <iostream>
#include <algorithm>
#include <vector>
#include  "BTree.h"
#define RECORD_LENGTH  8
typedef vector<BTree> vec ;
using namespace std ; 
	void BTree :: CreateIndexFileFile  (char *filename, int numberOfRecords , int m ){
		   	fstream  file;
			file.open("BTree.txt" , ios::out|ios::binary );
			BTree *record ; 
			int v = 0 ;
			for (int i = 1 ; i <= numberOfRecords ; i++){
				record = new BTree (-1,0)  ; 
				file.write ((char*)&record ,RECORD_LENGTH );
				if(i == numberOfRecords) v = -1;
				else v = i ;
				record = new BTree (v,0); 
				file.write ((char*)&record , RECORD_LENGTH );
				for (int j = 0 ; j < m -1; j++){
					record = new BTree (-1,-1); 
					file.write((char*)&record , RECORD_LENGTH );
				}
			}
			file.close();
}

void BTree :: DisplayIndexFileContent (char *filename, int m ) {
	BTree  *record   ;
	fstream file ;
	file.open(filename , ios::in|ios::binary);
	file.read((char*)&record , RECORD_LENGTH);
	int counter = 1 ; 
	while (true){
	if(file.eof()) break ;
	cout << record->value << "," << record->reference <<" ";
	if(counter == m+1){
		cout<<endl;
		counter  = 0 ; 
	}
 	counter++;
	file.read((char*)&record , RECORD_LENGTH);
	}
	file.close();
}
bool sortVector(const BTree & b1, const BTree & b2)
{
   if (b1.value != b2.value) return b1.value < b2.value;
   return b1.value < b2.value;
}
void printVector(vector <BTree> vec ){
	cout<< "\n----------vector-----------"<<endl;
	for (int i = 0 ; i< vec.size() ; i++){
		cout<< vec.at(i).value <<"," <<vec.at(i).reference << endl; 
	}
}
vector<BTree> BTree :: readNodes(char * filename , int index , int m ){
	fstream file2 ;
	BTree *record ;
	vector<BTree>nodes;
	int seekValue = m * index ;
	file2.open(filename ,  ios::in|ios::binary);
	file2.seekg( (RECORD_LENGTH )  * seekValue , ios::beg);
	file2.read((char*)&record  , RECORD_LENGTH);
	for(int i =0 ; i < m ; i++){
		file2.read((char*)&record  , RECORD_LENGTH);
	//	if(record->value != -1 ) {
				if(record->reference != -1) nodes.push_back(*record); // check  the first element is value or index 
				else break;	 				
	//	}else break;	
	}
	file2.close();
	return nodes;
}
	
void BTree :: writeNodes(vector<BTree>nodes, char* filename , int index , int m ,int root){
	fstream file2 ;
	BTree *record ;
	file2.open(filename ,  ios::out|ios::in|ios::binary);
	int newM = m + 1;   
//printVector(nodes);
	int newIndex = index ; 
	file2.seekg( ( RECORD_LENGTH  * newIndex * newM ), ios::beg );
	file2.read((char*)& record , RECORD_LENGTH);
 	if(record->value == -1){ // update next empty
 	//	cout<<index <<"  "<<root<<"  "<< record->value<<"  "<<newIndex<<" "<<endl;
    	file2.read((char*)& record , RECORD_LENGTH);
		file2.seekp( (RECORD_LENGTH) , ios::beg );
		record = new BTree( record->value , 0) ;			
		file2.write ((char*)& record , RECORD_LENGTH) ;
	//	cout<<index <<"  "<<root<<"  "<< record->value<<endl;
	}
	file2.seekp( (RECORD_LENGTH * newIndex * newM ), ios::beg);
	  record = new BTree( root , 0 ) ; // update first record that describe this nodes is leaf or root (0 is leaf , 1 is root)
	file2.write ((char*)& record , RECORD_LENGTH ) ;
	BTree *newRecord ;	
	for(int i = 0  ; i < nodes.size(); i++){
		newRecord = new BTree (nodes.at(i).value , nodes.at(i).reference);
		file2.write ((char*)&newRecord , RECORD_LENGTH);
	}
	file2.close();
}
vector<BTree> BTree :: splitLeft (vector<BTree>nodes  ){
	vector <BTree> leftNodes ;
	BTree *record2;
	int middle = nodes.size() / 2 ;
	for (int i = 0 ; i < nodes.size()-1 ; i++){
		if(i >= middle){
		record2 = new BTree (-1 , -1);
		leftNodes.push_back(*record2);
		}else{
		record2 = new BTree (nodes.at(i).value , nodes.at(i).reference);
		leftNodes.push_back(*record2);
		}
	}
	return leftNodes;
}

vector<BTree> BTree :: splitRight (vector<BTree>nodes  ){
	vector <BTree> rightNodes ;
	BTree *record2;
	int middle = nodes.size() / 2 ;
	for (int i = middle , j = 0 ; j < nodes.size()-1 ; j++ ,i++){
		if(j >= middle){
		record2 = new BTree (-1,-1);
		rightNodes.push_back(*record2);	
		}else{
		record2 = new BTree (nodes.at(i).value , nodes.at(i).reference);
		rightNodes.push_back(*record2);
		}
		
	}
	return rightNodes;	
}
 bool BTree :: isLeaf (char* filename , int m , int index ){
 	fstream file ;
 	BTree *record;
 	int newM = m+1 ;
 	file.open(filename , ios::out | ios::in | ios::binary );
 	file.seekg ( (RECORD_LENGTH ) * newM * index , ios::beg ); // seek first column
	file.read((char*)& record  , RECORD_LENGTH); 
	file.close();
	if(record->value == 1 )return false  ; 
	else return true   ; 
 }
  
 BTree  BTree:: split(vector<BTree>nodes , char *filename , int index , int m  , int root , bool isHead ){
 	fstream file  ;
 	BTree *record , *record2 , * record3 = new BTree(0,0) , *res;
 	file.open(filename , ios::out | ios::in | ios::binary );
 	file.seekg ( ( RECORD_LENGTH ) , ios::beg );
 	file.read((char*)& record  , RECORD_LENGTH); 
 	int newNodesIndex = record->value , n1 , n2 ; //index of next Empty  
 	vec   rightNodes , leftNodes  , rootNodes ; 
 	rightNodes = splitRight(nodes);
 	leftNodes  = splitLeft(nodes) ;
 	int i = 0  , 	  newM = m+1 ; ; 
 	while (leftNodes.at(i).reference != -1){// get last value (greatest)
 	  n1 = leftNodes.at(i).value;
 	  n2 = rightNodes.at(i).value; 
 	  i++;
 		}
 	 	if(isHead){
 			file.seekg ( ( RECORD_LENGTH ) , ios::beg );
		 	file.read((char*)& record2  , RECORD_LENGTH); 
		 	newNodesIndex = record2->value;
		 	
		 	res = new BTree (n1 , newNodesIndex );
		 	rootNodes.push_back(*res);
		 	file.seekg ( ( RECORD_LENGTH ) * newNodesIndex* newM , ios::beg );
		 	file.seekg ( ( RECORD_LENGTH ) , ios::cur );
		 	file.read((char*)& record2  , RECORD_LENGTH);
		 	int newNodesIndex2	= record2->value;
		 	res = new BTree (n2 , newNodesIndex2 );
		 	rootNodes.push_back(*res);
		 	sort(rootNodes.begin() , rootNodes.end() , sortVector );
			 for(int i = rootNodes.size() ; i< nodes.size() ; i++)	{
			 	record3= new BTree(-1,-1);
			 	rootNodes.push_back(*record3);
			 }
		    writeNodes(leftNodes, filename ,  newNodesIndex ,m , root );
			writeNodes(rootNodes , filename ,index , m , 1 );
			writeNodes(rightNodes, filename , newNodesIndex2 ,m , root );
			return *record3; 
		 } 	
 //	file.seekp((RECORD_LENGTH) * index * newM , ios::beg );
	writeNodes(rightNodes, filename , index , m , root );
	writeNodes(leftNodes, filename , newNodesIndex ,m , root );
	res = new BTree (n1 , newNodesIndex );
 	return *res ;  
 	}
 BTree BTree :: add(char *filename  , vector<BTree>nodes ,int m ,int recordID, int index, int index2 , int root , bool isHead){
 vec rootNodes ; 
 	BTree *record = new BTree(-1,-1) ; 
	if(nodes.size() <= m ){
		writeNodes(nodes , filename , index , m , root  );
		return *record;
	}else {                      
			*record = split( nodes , filename, index , m , root , isHead  );                                                                                 
	}
		return *record;
 }
 int BTree :: getDirection (char * filename , int m , int index , int recordID , bool isInsert){
 	fstream file;
	int  nextIndex = 0;
 	BTree * newRecord2  , * record ;                                          
 	file.open(filename , ios::out | ios::in | ios::binary );
 	file.seekg ( (RECORD_LENGTH) * m * index , ios::beg);  		
	file.read ((char*) &record  , RECORD_LENGTH);
	file.read ((char*) &record  , RECORD_LENGTH);
	int j =0 ; 
	while ( record->reference != -1 || j == m ){		// search  newValue  reference ! in other words ,Looking for any side will go to
	
		if (recordID <=record->value){//
		    newRecord2 = record ; 
			nextIndex = newRecord2->reference  ;
		    break; 
		} else if (recordID > record->value) {
			newRecord2 = record ;
			nextIndex  = newRecord2->reference  ;
			
		}
		file.read((char*) &record  , RECORD_LENGTH);
		j++;
		if(isInsert){
		if( recordID > newRecord2->value  && ( record->reference == -1 || j == m )){
		nextIndex = newRecord2->reference ;  // if the recordID greater than nodes than its parent ,,, write it   insted of its parent 
		file.seekp ( (RECORD_LENGTH) * -2 , ios::cur) ;
		BTree *record3 = new BTree (recordID , newRecord2->reference);
		file.write ((char*)& record3 , RECORD_LENGTH) ;
		break;
	   }
		}
	   if(j==m)return -1;
 }
 return nextIndex ; 
}
int BTree :: InsertNewRecordAtIndex (char *filename, int recordID, int ref   ){
	
	InsertNewRecordAtIndex( filename ,   recordID ,   ref ,   5 , 1 , true );
}

BTree  BTree :: InsertNewRecordAtIndex(char *filename , int recordID , int ref , int m ,int  index , bool isHead ){
	fstream file  ;
 	BTree record , *record2 ;
 	int newM = m + 1  , index2 = index; 
 	vec nodes  ; 
 	int root  =  0 ; 
 	file.open(filename , ios::out | ios::in | ios::binary );
 	file.seekg ( ( RECORD_LENGTH ) * newM * index  , ios::beg );
 	bool leaf = isLeaf(filename , m , index);
 	
	if(leaf){
		nodes = readNodes( filename , index , newM );
		record2 = new BTree (recordID,ref);
		nodes.push_back(*record2);
		sort(nodes.begin() , nodes.end() , sortVector );	
	    record = add(filename , nodes , m , recordID , index2 , index , root ,isHead);
		return record ;
		}else {
			
	    index2 = getDirection (filename , newM  , index , recordID , true );
		record = InsertNewRecordAtIndex (filename ,   recordID,   ref ,   m  , index2 , false );
		if(record.reference != -1 ){
		nodes = readNodes(filename , index , newM );
		nodes.push_back(record);
		sort(nodes.begin() , nodes.end() , sortVector);	
		root = 1; 
		return  add( filename , nodes ,  m , recordID , index , index2, root, isHead);
		}else {
			BTree *rec = new BTree(-1,-1); 
			                                 
			  return *rec ;      
		}                                                                              
	}
}
int BTree:: SearchARecord (char *filename, int recordID , int m ) {

	fstream file  ;
 	BTree *record ;
 	int newM = m + 1 , index = 1 ;
 
 	file.open(filename , ios::in | ios::binary );
	for (int i = 1 ; i < m ; i++){
		file.seekg( ( RECORD_LENGTH ) * newM * index   , ios::beg );
		file.read ((char*) & record  , RECORD_LENGTH);
		 for (int j = 1 ; j <= m ; j++){
		 	file.read ((char*) & record  , RECORD_LENGTH);
			  if(record->value == recordID ){
			  	
			  	file.close();
			  	return index ;
			  }
		}
	index = getDirection(filename , newM , index , recordID,false );
	//cout<<index<<" here"<<endl;
	if(index == -1 || index >10) {//////////////////////
	
		return -1;
	}
	 }
	 file.close();
	 
	 return -1;
} 
bool BTree :: deleteLeaf(char *filename ,int  m , int valueIndex , int recordID){
 	BTree *record ;
 	vec nodes ; 
 	int newM = m + 1 , size  ;
 	nodes = readNodes(filename , valueIndex , newM );
 	record = new BTree (-1,-1);
 	for(int i = 0 ; i < nodes.size() ; i++){
 		if (nodes.at(i).value == recordID){
		 	nodes.erase (nodes.begin()+i );	
		 	size = nodes.size();
		 	for(int j = nodes.size()-1 ; j < m-1 ; j++){ // add zeroes in end of vector to write it in file
		 		nodes.push_back(*record) ;	
			 }
 			writeNodes( nodes,  filename ,valueIndex , m ,  0);
 			break;
		 }
	 }
	
	 if(size < m/2)return false ; 
	 return true ; 
}
void BTree::  DeleteRecordFromIndex (char *filename, int recordID , int m ) {
	int valueIndex =  SearchARecord ( filename,   recordID ,  m ) ; 
	if(valueIndex != -1) {
		int node = deleteRecord (filename , recordID , m , valueIndex);
		updateRoot(filename , valueIndex, m , node , recordID);
		
		}else {
		cout<<recordID<<"   NOT Found!! "<<valueIndex<<endl;
		return ;
		}
	
}

int BTree :: updateRoot(char *filename , int valueIndex, int m , int node , int recordID ){
	int newM = m + 1 , ref = 1 ;
	BTree *record ;
	vec nodes = readNodes(filename , valueIndex , newM );
	cout<<" BBB "<<endl;
	printVector(nodes);
	for(int i = 0 ; i < nodes.size() ; i++){
 		if (nodes.at(i).value == recordID){
		  	nodes.at(i).value = node ;
			   ref =  nodes.at(i).reference;
 			writeNodes( nodes , filename , valueIndex , m , 1);
 			break;
		 }
	 }
	 return ref;
}
int  BTree:: merge ( char *filename, int m ,int  rightRef  ,int leftRef ,int valueIndex,int recordID){
	int newM = m+1 ;
	int newIndex ;
	vec rightNodes , leftNodes ;
	vec singleNode , emptyVect ;
	singleNode = readNodes(filename   , valueIndex , newM );
	 
	if( rightRef != -1 ){
	  rightNodes = readNodes(filename , rightRef , newM);
	  for(int i =  0 ; i< singleNode.size(); i++){
		rightNodes.push_back(singleNode.at(i));
		}
		newIndex = rightRef;
	}else{
	  leftNodes = readNodes(filename , leftRef , newM ); 
	  for(int i =  0 ; i< singleNode.size(); i++){
		leftNodes.push_back(singleNode.at(i));
		}
		newIndex  = leftRef;
	}
	singleNode.clear();
	for(int i =  0 ; i<m/2; i++){
		BTree *ob = new BTree(-1,-1);
		singleNode.push_back(*ob);
		}
	cout<<valueIndex<<"  jjjj"<<endl;
//	printVector(emptyVect);
	writeNodes( rightNodes , filename , rightRef , m , 0);
	writeNodes( singleNode , filename , valueIndex , m , -1);	
	//update first record that pointer to next empty 
	
	fstream file1 ;
	BTree *record,*obj ,*obj2 ,*newRecord;
	file1.open(filename ,  ios::out|ios::in|ios::binary);
	file1.seekg( RECORD_LENGTH  , ios::beg );
	file1.read((char*)&record , RECORD_LENGTH);
	file1.seekg(RECORD_LENGTH *2, ios::beg);  
	while(true ){
	if(record->value == -1){
		file1.seekp( (RECORD_LENGTH)*-1 , ios::cur );
		record = new BTree( valueIndex , 0 );			
		file1.write ((char*)& record , RECORD_LENGTH) ;
		file1.close();
		break; 
	}
	file1.read((char*)&record , RECORD_LENGTH);
}
return newIndex;
}

int BTree:: balance (char * filename ,int m , int parentIndex , int valueIndex , int recordID){
		int newM = m +1  , rightRef = -1 , leftRef = -1  ; 
		vec siblingsNode = readNodes(filename , parentIndex , newM);
		vec singleNode = readNodes(filename  , valueIndex , newM );
		for(int i = 0 ; i < siblingsNode.size() ; i++){// get the right of node that will be a sibling  to the single node
			if (siblingsNode.at(i).reference == valueIndex ){
				
				if (i != 0)	rightRef = siblingsNode.at(i-1).reference;
				  if(i == 0) leftRef = siblingsNode.at(i+1).reference;	
				break; 	
			}	
		}
		vec v2 = readNodes(filename  , rightRef , newM ); // read right sibling of node 
		vec v3 = readNodes(filename  , leftRef , newM );
		if(v2.size() > m/2){// if it is has greater than m/2 nodes 
			int rightValue = v2.at(v2.size()-1).value ; 
			int nextParent = v2.at(v2.size()-2).value ; // value that will be parent instead of value that take off
			int rightNodeRef = v2.at(v2.size()-1).reference;
			BTree * record = new BTree (rightValue,rightNodeRef);
			singleNode.push_back(*record);
			sort(singleNode.begin() , singleNode.end() , sortVector );
			writeNodes( singleNode , filename , valueIndex , m , 0);
		    bool isBalance = deleteLeaf(filename , m , rightRef , rightValue);
		    updateRoot(filename , parentIndex, m , nextParent, rightValue);
		    return valueIndex;
		}else if(v3.size() > m/2){	// left sibling  // check here 
			cout<<" V3 "<<endl;
			int leftValue = v2.at(0).value ; //first value 
			int nextParent = v2.at(1).value; // value that will be parent instead of value that take off
			int leftNodeRef = v2.at(0).reference;
			BTree * record = new BTree (leftValue,leftNodeRef);
			singleNode.push_back(*record);
			sort(singleNode.begin() , singleNode.end() , sortVector );
			writeNodes( singleNode , filename , valueIndex , m , 0);
		    bool isBalance = deleteLeaf(filename , m , leftRef , leftValue);
		    updateRoot(filename , parentIndex, m , nextParent, leftValue);
		    return valueIndex;
		    
		}else{	 			
			int newIndex =  merge( filename, m , rightRef , leftRef , valueIndex, recordID); 
			// remove  .. 
		//	siblingsNode
			for(int i =  0 ; i<siblingsNode.size() ; i++){
				if(siblingsNode.at(i).reference == valueIndex){
				siblingsNode.erase(siblingsNode.begin()+i);
					break ;
				}
			} 
			
			for(int i =siblingsNode.size()-1 ; i< m ; i++){
				BTree *obj = new BTree(-1,-1);
				siblingsNode.push_back(*obj);
				
			}
			cout<<" DSSSS"<<endl;
			printVector(siblingsNode);
			writeNodes(siblingsNode,filename , parentIndex , m , 1);
			return newIndex;
		}
		
}
int BTree:: deleteRecord (char * filename , int recordID , int m , int valueIndex ){
	int newM = m + 1 , rightRef ,   newNode = valueIndex ;
	int node = valueIndex , oldIndex = 0 ;
	static int parentIndex ;   // to keep the parent of node ; 
	static bool isBalance;
	static int index ; 
	if( isLeaf(filename , m , valueIndex )){
		isBalance = deleteLeaf(filename , m , valueIndex , recordID);
		vec n = readNodes(filename  , valueIndex , newM );
		if(!isBalance){
			
			  newNode = balance (filename , m , parentIndex , valueIndex ,recordID   );	
		//	updateRoot(filename , valueIndex, m , node , recordID);		   			   
		}
		vec nodes = readNodes(filename  ,   newNode , newM );
		node = nodes.at(nodes.size()-1).value ;
		return node ;
		
	}else{// not leaf
		parentIndex =  valueIndex ; 
		valueIndex = getDirection ( filename, newM , valueIndex , recordID , false );
		node = deleteRecord ( filename ,   recordID , m , valueIndex );
		updateRoot(filename , valueIndex, m , node , recordID);
		return node ;
	} 
			
} 
