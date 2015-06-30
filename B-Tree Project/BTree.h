#include <iostream>
#include <fstream>
#include <vector>
using namespace std ; 
class BTree {
	public : 
		int value ; 
		int reference ;
		
		BTree(int value , int reference ){
			
			this->value = value ; 
			this->reference = reference ;	
		}
		BTree (){}
		void CreateIndexFileFile (char *filename, int numberOfRecords , int m ) ;
		void DisplayIndexFileContent (char *filename, int m ) ;
		BTree InsertNewRecordAtIndex (char *filename, int recordID, int ref , int m , int m2 , bool isHead) ;
		void DeleteRecordFromIndex (char *filename, int RecordID , int m ) ;
		int SearchARecord (char *filename, int RecordID ,int m ) ;
	    vector<BTree> readNodes(char * filename ,int index , int m );
		void  writeNodes(vector<BTree>nodes, char* filename,int  index, int m , int root);
		vector<BTree> splitLeft (vector<BTree>nodes  );
		bool isLeaf (char* filename , int m , int index );
		BTree split(vector<BTree>nodes,char *filename , int index , int m , int root , bool isHead );
		vector<BTree>  splitRight (vector<BTree>nodes   );
		int  getDirection (char * filename , int m , int index , int recordID,bool isInsert);
		BTree add(char *filename  , vector<BTree>nodes ,int m ,int recordID, int index, int index2 , int root , bool isHead);
		int InsertNewRecordAtIndex (char *filename, int RecordID, int Reference);
		bool   deleteLeaf(char *filename ,int  m , int valueIndex ,int recordID);
		int updateRoot(char *filename , int valueIndex, int m , int node , int recordID );
		int deleteRecord( char * filename , int recordID , int m , int valueIndex);
		int  balance (char * filename ,int m , int parentIndex , int valueIndex,int recordID );
		int merge ( char *filename, int m ,int  rightRef  ,int leftRef ,int valueIndex,int recordID);
};
