//huffman decoding program using recursive functions
#include <bits/stdc++.h>  
using namespace std;

//storing the input data as the frequency of the charcter
map<char, int> frequency;

//storing the character and huffman code that is assigned to the provided character
map<char, string> code;

//functio for Huffman tree node 
struct MinHeapNode 
{ 

	char element; 						//input character
	int freq;							//frequency of the provided input character
	MinHeapNode *left, *right;  		//left and right child for heap node

	MinHeapNode(char element, int freq) 
	{ 
 	left = right = NULL; 
 	this->element = element; 
 	this->freq = freq; 
	} 
};

//function to arrange the element in the priority order based on the frequency of the elements
struct compare 
{ 
	bool operator()(MinHeapNode* l, MinHeapNode* r) 
	{ 
 	return (l->freq > r->freq); 
	} 
};

//Function to display the characters
void printCode(struct MinHeapNode* root, string str) 
{ 
	if (!root) 
 	return; 
	if (root->element != '$') 
 	cout << root->element << ": " << str << "\n"; 
	printCode(root->left, str + "0"); 
	printCode(root->right, str + "1"); 
} 

//function to store the characters with their codes
void storeCode(struct MinHeapNode* root, string str) 
{ 
	if (root==NULL) 
 	return; 
	if (root->element != '$') 
 	code[root->element]=str; 
	storeCode(root->left, str + "0"); 
	storeCode(root->right, str + "1"); 
}

//store heap tree with their priority order
priority_queue<MinHeapNode*, vector<MinHeapNode*>, compare> po;

//create the huffman tree storing the MinHeapNode
void Huffman(int size) 
{ 
	struct MinHeapNode *left, *right, *temp; 
   	map<char,int> :: iterator it=frequency.begin();
   	while(it!=frequency.end()){
       po.push(new MinHeapNode(it->first,it->second));
       it++;
   	}
 
	while (po.size() != 1) 
	{	 
 		left = po.top(); 
 		po.pop(); 
 		right = po.top(); 
 		po.pop(); 
 		temp = new MinHeapNode('$', left->freq + right->freq); 
 		temp->left = left; 
 		temp->right = right; 
 		po.push(temp); 
	} 
	storeCode(po.top(), ""); 
}  

//decoding the encoded string 
string decode(struct MinHeapNode* root, string str) 
{
   string out = ""; 
   
   struct MinHeapNode* curr = root; 
   for (int i=0;i<str.size();i++){ 
      if (str[i] == '0'){
          //if current bit is 0 then moves towards the left node.
          curr = curr->left; 
      }else{
          //if current bit is 1 then move towards the right node.
          curr = curr->right; 
      }
 
       //leaf node is encountered 
       if (curr->left==NULL and curr->right==NULL){ 
           out += curr->element; 
           curr = root; 
       } 
   } 
   //cout<<out<<endl
   return out+'\0'; 
}


int main() 
{ 
	string str = "strong"; 
	string s1,s2; 
   //frequency of the characte
	for (int i=0; i<str.size(); i++){
 		frequency[str[i]]++;
   	}
      
	Huffman(str.length()); 
	cout << "The characters with their Huffman codes are:"<<endl; 
   	map<char,string> ::iterator it=code.begin();
	while(it!=code.end()){
       cout<<it->first<<" "<<it->second<<endl;
       it++;
   	}

	for(int i=0;i<str.size();i++){
       s1=s1+code[str[i]];
   	}
	//print the encoded data
	cout << "Encoded Huffman string is:" << s1 << endl;

	s2 = decode(po.top(),s1); 
	//print the decoded data
	cout << "Decoded Huffman string is:" << s2 << endl; 
	return 0; 
  
} 
