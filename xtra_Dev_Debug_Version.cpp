
/*DEVELOPMENT VERSION... SHOWS ALL THE STEPS AND LOGICS USED TO DETERMINE THE RNA STRAND COMPOSITION*/

#include <iostream>
#include <string.h>
#include <algorithm>
#include <list>
#include <sstream>
#include <vector>
#include <string>
#include <ctime>
#include <functional>
#include <fstream>
//#include <boost/tokenizer.hpp>
//#include <boost/foreach.hpp>
using namespace std;
vector<string> intersection(vector<string> &v1, vector<string> &v2)
{

    vector<string> v3;

    sort(v1.begin(), v1.end());
    sort(v2.begin(), v2.end());

    set_intersection(v1.begin(),v1.end(),v2.begin(),v2.end(),back_inserter(v3));

    return v3;
}
//----------------------------------------------MAIN()---------------------------------------------------------------//

int main(){
      std::vector<std::string> VectorOfPermut;
      vector <string> Final_Results;
    //------------------------Entering G Fragmentes ,splited into tolkens , save into a vector-----------------//
   // cout<<" please enter G fragments seperated by ',' "<< endl;
 //   string Gfragments;
  //  cin >> Gfragments;
  //-------------------------------------------
   string input; 
   string  Gfragments;
    string UCfragments;
	ifstream in;
	in.open("input2.txt");

	if(!in)
	{
		cout<<"No input file"<<endl;
		system("pause");
		return 1;
	}

	while(!in.eof())
	{
		
		getline(in,input);
		Gfragments = input;
		getline(in,input);
		UCfragments= input;
	}
	in.close();
  //--------------------------------------------
    char split_char = ',';
    istringstream G_split(Gfragments);
    vector<string> G_tokens;
    for (string each; getline(G_split, each, split_char); G_tokens.push_back(each));
    //------------------------Entering UC Freagments, spelited into tokens, save into a vector -------------------//
        
  //  cout<<" please enter UC fragments seperated by ',' "<< endl;
  //  string UCfragments;
 //   cin >> UCfragments;
   // char split_char = ',';
    istringstream UC_split(UCfragments);
    vector<string> UC_tokens;
    for (string each; getline(UC_split, each, split_char); UC_tokens.push_back(each));
    //------------------------OUTPUT TESTING  ----------------------------------------------------------------//
    string lastFrag;
    string lastFragment;
    string lastFragment1;
    string lastFragment2;
    string firstFragment;
    int counter=0;
    string tkn;
    for ( int i=0; i < G_tokens.size() ; i++){
         cout<< G_tokens[i]<<"-";
         tkn=G_tokens[i];
         char last = tkn[tkn.length()-1];
        // cout << last<<endl;
         if ( last != 'G'){ 
           //   cout << last<<endl;
              lastFragment1 = tkn;
              counter++;
             // cout <<"last fragment1 is "<< lastFragment1<<endl;
              //NOTE: last fragment will show either in G or UC but not in both Unless it ends with A.. and it must show up
              }
           //   cout <<"last fragment1 is "<< lastFragment1<<endl;
         }
         cout <<"last fragment1 is "<< lastFragment1<<endl;
    //--------------------------------------------------------------------------------------------------------//     
         cout<<endl;
    for ( int i=0; i < UC_tokens.size() ; i++){
         cout<< UC_tokens[i]<<"-";
          tkn=UC_tokens[i];
          char last2 = tkn[tkn.length()-1];
         // cout << last2<<endl;
          if ( last2 != 'U'&& last2 !='C'){ 
            //  cout << last2<<endl;
              lastFragment2 = tkn;
              counter++;
            //  cout <<"last fragment2 is "<< lastFragment2<<endl;
              }
         }  
        cout <<"last fragment2 is "<< lastFragment2<<endl;    
   //Now, we need to determine the first fragment.. in order to this ,we need to further splicing- cross splicing
   // and do some analysis.//   better to use if else if else
   if (counter ==1 && lastFragment1.size() >0 && lastFragment2.size()==0 ) { lastFragment= lastFragment1;}
  else if (counter ==1 && lastFragment2.size() >0 && lastFragment1.size()==0 ) { lastFragment= lastFragment2;}
  else if ( counter > 1 && lastFragment1[lastFragment1.length()-1]== 'A' && lastFragment2[lastFragment2.length()-1] =='A'){ // if ends with A
      if ( lastFragment1.length()> lastFragment2.length()) { lastFragment= lastFragment1;}
       else { lastFragment= lastFragment2;}
       }
       
  else if (counter > 1 && lastFragment1[lastFragment1.length()-1]!= 'A' &&  lastFragment2[lastFragment2.length()-1] !='A')
   { cout <<" ERROR ENTERING FRAGMENTS!, PLEASE TRY AGAIN  "<<endl;
                     cout<<" EXISTING !! "<<endl;
                     clock_t start_time = clock();
                     clock_t end_time =  90000 + start_time;
                     while(clock() != end_time){};
                     exit (0) ;
                   } 
    cout<<"last fragment after analysis is : "<<lastFragment<<endl;               
//-----------------------------------------------------------------------------------------
   //Now, we need to determine the first fragment.. in order to this ,we need to further splicing- cross splicing
   // and do some analysis.//
   /// ----After second enzyme treatment:  For G fragments: -------------------------------
   vector<string> vecG_CU;
   string s="";
   string temp;
   char c;
   /// seperate by / to indicate UC enzyme vertual fragaments
   for (int k =0; k< G_tokens.size(); k++){
        temp = G_tokens[k];
        for ( int w =0; w< temp.length() ; w++){
            if (temp[w]== 'G' || temp[w] =='A'){
                          s += temp[w];
                          }
            if (temp[w] == 'C' || temp[w] == 'U'){
                          s+= temp[w];
                          s+= '/';     
                          }   
        } 
             if (s[s.length()-1] == '/'){s = s.substr(0, s.size()-1);} // remove '/' if it is located at end,will happen with lastFragment
        
              vecG_CU.push_back(s); 
              s.clear();
   }                        
cout<<" After second enzyme'UC' treatment: "<<endl;
cout<<" The 'virtual' fragments for 'G' enzyme fragments are :" <<endl;
        
 for (int t=0; t< vecG_CU.size(); t++){
     cout << vecG_CU[t]<<endl;
     }  
///---------After second enzyme treatment: for UC fragments: ------------------------------------
   vector<string> vecCU_G;
   string ss="";
   string temp1;
   for (int k =0; k< UC_tokens.size(); k++){
        temp1 = UC_tokens[k];
        for ( int w =0; w< temp1.length() ; w++){
            if (temp1[w]== 'U' || temp1[w] =='A' || temp1[w] == 'C' ){
                          ss += temp1[w];
                          }
            if (temp1[w] == 'G' ){
                          ss+= temp1[w];
                          ss+= '/';
                          }   
        } 
              if (ss[ss.length()-1] == '/'){ss = ss.substr(0, ss.size()-1);}
              vecCU_G.push_back(ss); 
              ss.clear();
   }  
cout << "--------------------------------------"<<endl;                         
cout<<" After second enzyme'G' treatment: "<<endl;
cout <<"The 'virtual' fragments for UC fragments are:"<<endl;
 for (int t=0; t< vecCU_G.size(); t++){
     cout << vecCU_G[t]<<endl;
     }   
///------------------FINDING FIRST FRAGMENT ------------------------------------------------//
/*push fragment with no'/' from both vectors into a vector<string> outerBases & and fragments with at least two'/' into another vector
vector<string> graphVec . then iterate through graphVec and push middle tokens into another vector<string> innerBases, sort both vectors
innerBse and outerBase and push intersection into a vectore<string> intersect
http://stackoverflow.com/questions/19483663/vector-intersection-in-c
compare two bases in that vector, if they are equal in length , see which is a subset of firstFragment, and the other become 
the firstFragment, if they are not equal in length , the shorter become the firstFragment*/  
cout<<"-----------------------------------------"<<endl;
vector<string> outerBases;
vector<string> graphVec;
vector<string> innerBases;
string tokn;
//-------------------------------------------------------------------------------------//
 for (int t=0; t< vecG_CU.size(); t++){
      tokn = vecG_CU[t];
     // tokn+='*';
      if (tokn.find('/') != std::string::npos){ 
                         tokn+='*';
                         graphVec.push_back(tokn);}
           else { outerBases.push_back(tokn);}
         
   }   
 //--------------------------------------------------------------------------------------//
  for (int t=0; t< vecCU_G.size(); t++){
      tokn = vecCU_G[t];
      if (tokn.find('/') != std::string::npos){ 
                         tokn+='*';
                         graphVec.push_back(tokn);}
           else { outerBases.push_back(tokn);}
   }  
 //--------------------------------------------------------------------------------------//
 cout << " the following are the graph units "<<endl;  // the ones that contains '/' within
 for (int t=0; t<graphVec.size(); t++){
     cout<< graphVec[t]<<endl;
     }
cout<<" the following are the outer bases"<<endl;  // the undividable fragments, the ones that contain no '/'    
 for (int t=0; t<outerBases.size(); t++){
     cout<< outerBases[t]<<endl;
     }
//---------------------------------------------------------------------------------------//     
 cout<<"-----------------------------------------"<<endl;
 string tk;
// int no=0;
 cout << " the inner bases are :"<<endl; 
 for (int t=0; t<graphVec.size(); t++){
     int no=0;
      tk = graphVec[t];
       for ( int r =0; r<tk.size();r++){  // find how many '/' are there , if >= 2 then it contains innerTokens or edges
           if ( tk[r] == '/') { no++;} 
           }
           if( no > 1){
              char split_char = '/';
              istringstream split(tk);
              vector<string> intokens;
              for (string each; getline(split, each, split_char); intokens.push_back(each));
              for ( int a=1; a < intokens.size()-1;a++){
              innerBases.push_back(intokens[a]);}
              }  
               
       } 
 //----------------------------------------------------------------------------------------//          
  if ( innerBases.size()>0){
       cout <<" inner bases are: "<<endl;
       for (int i =0; i < innerBases.size(); i++)
       {             
        cout<< innerBases[i]<<endl;       
        }
 } 
//------------------------------------------------------------------------------------------//
vector <string > intersect;
intersect = intersection(innerBases, outerBases);  
if ( intersect.size()>0){
     cout<<" the intersicts are : "<<endl;
     for (int e =0; e < intersect.size();e++){
         cout<< intersect[e]<<endl;
         }
  } 
//------------------------------------------------------------------------------------------//
// copy the outerabases vector
vector <string> ends;
ends = outerBases;
//--------------------------------------------------------------------------------------

  // For the set_symmetric_difference algorithm to work, 
  // the source ranges must be ordered!    
  vector<string> sortedV1(intersect);
  vector<string> sortedV2(ends);

  sort(sortedV1.begin(),sortedV1.end());
  sort(sortedV2.begin(),sortedV2.end());

  // Now that we have sorted ranges (i.e., containers), find the differences    
  vector<string> vDifferences;

  set_symmetric_difference(
    sortedV1.begin(),
    sortedV1.end(),
    sortedV2.begin(),
    sortedV2.end(),
    back_inserter(vDifferences));
    if (vDifferences.size()>0){  // actually it should be ==2
                               cout<< " the ends bases are : "<<endl;
                               cout<<"***********************"<<endl;}
                            /*  for (int p=0; p<vDifferences.size(); p++){
                                   cout<<vDifferences[p]<<endl;}} 
                               cout<<"***********************"<<endl; */  
 
//------------------------------------------------------------------------------------------//

string comp0=vDifferences[0];
string comp1=vDifferences[1];
if ( comp0[comp0.length()-1]== lastFragment[lastFragment.length()-1] && comp1[comp1.length()-1]!= lastFragment[lastFragment.length()-1]){
     firstFragment = comp1;
     lastFrag = comp0;
     cout <<" : 1 :"<<endl;}
//-----------------------     
else if ( comp0[comp0.length()-1]!= lastFragment[lastFragment.length()-1] && comp1[comp1.length()-1]== lastFragment[lastFragment.length()-1]){
     firstFragment = comp0;
     lastFrag = comp1;
     cout <<" : 2 :"<<endl;}
//--------------------
else if ( comp0[comp0.length()-1]== lastFragment[lastFragment.length()-1] && comp1[comp1.length()-1]== lastFragment[lastFragment.length()-1]){
     if (lastFragment.find(comp0) != string::npos && !lastFragment.find(comp1) != string::npos   )
     { lastFrag = comp0; firstFragment= comp1;cout <<" : 3 :"<<endl;}
   //  if(comp0.length()> comp1.length()){ lastFrag = comp0; firstFragment= comp1;cout <<" : 3 :"<<endl;}
      if (lastFragment.find(comp1) != string::npos && !lastFragment.find(comp0) != string::npos   )
     { lastFrag = comp1; firstFragment= comp0;cout <<" : 4 :"<<endl;}    
   //  if(comp0.length()< comp1.length()){ lastFrag = comp1; firstFragment= comp0;cout <<" : 4 :"<<endl;}
     }
else{
     firstFragment= comp1;
     lastFrag= comp0; 
     cout <<" : 5 : "<<endl;}    
     
 cout<<"First fragment is : "<< firstFragment <<endl;
 cout<<"Last fragment is  : "<<lastFrag<<endl;

//------------------------------------------------------------------------------------------//
/*if(vDifferences[0].length() < vDifferences[1].length()){ firstFragment= vDifferences[0];
                                         lastFrag=vDifferences[1];
                                         cout <<"1"<<endl;}
else if(vDifferences[0].length()> vDifferences[1].length()) { firstFragment= vDifferences[0]; //<---------------
                                         lastFrag=vDifferences[1];
                                         cout<<"2"<<endl;} 
else if(vDifferences[0]== vDifferences[1])                  { firstFragment= vDifferences[0];
                                         lastFrag=vDifferences[1];
                                         cout<<"3"<<endl;}
 
else if  (vDifferences[0].length() == vDifferences[1].length() && lastFragment.find(vDifferences[0]) != std::string::npos){//<--check
      lastFrag=vDifferences[0];
      firstFragment=vDifferences[1];
      cout<<"4"<<endl;}
else {
    firstFragment =vDifferences[1];
    lastFrag=vDifferences[0];
    cout<<"5"<<endl;}  
 cout<<" first fragment is : "<< firstFragment <<endl;
 cout<<" last fragment is  : "<<lastFrag<<endl; */
 //------------------------------NOW, we start the graph analysis to find closed Eluerian circuites -------------//
 /*Start with the firstFragment, compare it to first tokens in vector graphVec , if found pushit into vector or string , use the last 
 token to search for first matching token of the rest and so on, it must end with the lastFrag and graphVec must be covered to empty*/      
/*std::sort (myVectorOfStrings.begin(),myVectorOfStrings.end());


  std::cout << "The 4! possible permutations with 4 elements:\n";
  do {
    //This printing can be improved to handle any number of sentences, not only four.
    std::cout << myVectorOfStrings[0] << ' ' << myVectorOfStrings[1] << ' ' << myVectorOfStrings[2] << ' ' << myVectorOfStrings[3] << '\n';
  } while ( std::next_permutation(myVectorOfStrings.begin(),myVectorOfStrings.end()) );
*/                
     //Define an ostream iterator for strings
   //------------------------------------------------------------------------------------------------//  
  /*  typedef ostream_iterator<string> StrOstreamIt;
    StrOstreamIt outIt(cout, "*") ;   
    int start = graphVec.begin() ; 
    int end = graphVec.end() ;   
        // Generate all possible permutations

    cout << "After calling next_permutation:" << endl ;
    while ( next_permutation(start, end) )
    {
        copy(start, end, outIt) ;
        cout << endl ;
    }       
    */
 //========================================================================================================================//
/*
 // next_permutation example
#include <iostream>     // std::cout
#include <algorithm>    // std::next_permutation, std::sort
#include <string>       // std::string
#include <vector>       // std::vector
#include <boost/tokenizer.hpp>
#include <boost/foreach.hpp>
using namespace std;
int main () {
    
  std::string sentence1 = " CC/GCU/AUU ";
  std::string sentence2 = " AA/AU/CU ";
  std::string sentence3 = " AC/U/GGU ";
  std::string sentence4 = " CC/C/GGC/U ";

  // Store all the elements in a container ( here a std::vector)
  std::vector<std::string> myVectorOfStrings;  
  std::vector<std::string> VectorOfPermut;    
  // In the vector we add all the sentences.
  // Note : It is possible to do myVectorOfStrings.push_back("Some sentence");
  myVectorOfStrings.push_back(sentence1);
  myVectorOfStrings.push_back(sentence2);
  myVectorOfStrings.push_back(sentence3);
  myVectorOfStrings.push_back(sentence4);

  // The elements must be sorted to output all the combinations
  std::sort (myVectorOfStrings.begin(),myVectorOfStrings.end());

  string s="";
  std::cout << "The 4! possible permutations with 4 elements:\n";
  do {
     for ( int i=0; i< myVectorOfStrings.size(); i++){
         s+=myVectorOfStrings[i];
         }
     /*seperate s into tokens - using sstream- then push into a temp vector, then get vec[0] and seperated into tokens by '/'
     if ( first token == firstafarg && last token == first token of v[1] && last token of v[1] == first token ofv[2] and so on 
     till && last takon of v[size()-1] == lastFragment;; then push the string s into a vectore of possible RNA and that is it !!*/    
         
 /*     cout<<s<<endl;
      s="";   
      
      
    //This printing can be improved to handle any number of sentences, not only four.
   // std::cout << myVectorOfStrings[0] <<"*"<< myVectorOfStrings[1] <<"*"<< myVectorOfStrings[2] <<"*"<< myVectorOfStrings[3] << '\n';
  } while ( std::next_permutation(myVectorOfStrings.begin(),myVectorOfStrings.end()) );

  system("pause");
  return 0;
  //----------------------------------------------------------------------------------------------
}
*/  
/*// next_permutation example
#include <iostream>     // std::cout
#include <algorithm>    // std::next_permutation, std::sort
#include <string>       // std::string
#include <vector>       // std::vector
#include <boost/tokenizer.hpp>
#include <boost/foreach.hpp>
using namespace std;
int main () {
    
  std::string sentence1 = " CC/GCU/AUU ";
  std::string sentence2 = " AA/AU/CU ";
  std::string sentence3 = " AC/U/GGU ";
  std::string sentence4 = " CC/C/GGC/U ";

  // Store all the elements in a container ( here a std::vector)
  std::vector<std::string> myVectorOfStrings;  
  std::vector<std::string> VectorOfPermut;    
  // In the vector we add all the sentences.
  // Note : It is possible to do myVectorOfStrings.push_back("Some sentence");
  myVectorOfStrings.push_back(sentence1);
  myVectorOfStrings.push_back(sentence2);
  myVectorOfStrings.push_back(sentence3);
  myVectorOfStrings.push_back(sentence4);

  // The elements must be sorted to output all the combinations
  std::sort (myVectorOfStrings.begin(),myVectorOfStrings.end());

  string s="";
  std::cout << "The 4! possible permutations with 4 elements:\n";
  do {
     for ( int i=0; i< myVectorOfStrings.size(); i++){
         s+=myVectorOfStrings[i];
         }
     /*seperate s into tokens - using sstream- then push into a temp vector, then get vec[0] and seperated into tokens by '/'
     if ( first token == firstafarg && last token == first token of v[1] && last token of v[1] == first token ofv[2] and so on 
     till && last takon of v[size()-1] == lastFragment;; then push the string s into a vectore of possible RNA and that is it !!
     //--------------------------------------------------------------------------------------------------------------
     //THIS CODE IS NOT TESTED YET.
     vector < string> temp;
     vector <string> possibleRNA;
     istringstream iss(s);

    do
    {
        string sub;
        iss >> sub;
        temp.push_back(sub);
    } while (iss); 
    for ( int i = 0; i< temp.size();i++){
        if( firstTKN(temp[i]) == firstFragment){
            int counterA=0;
            for (int j=0; j<temp.size()-1;j++){
               if (lastTKN(temp[j])== firstTkn(temp[j+1]){
                    counterA++; 
                    }
                if (counterA== temp.size()-1){ 
                               possibleRNA.push_back(s);
                    }                    
                }
     
           }
     } 
     
     
     
     */    
         
 /*     cout<<s<<endl;
      s="";   
      
      
    //This printing can be improved to handle any number of sentences, not only four.
   // std::cout << myVectorOfStrings[0] <<"*"<< myVectorOfStrings[1] <<"*"<< myVectorOfStrings[2] <<"*"<< myVectorOfStrings[3] << '\n';
  } while ( std::next_permutation(myVectorOfStrings.begin(),myVectorOfStrings.end()) );

  system("pause");
  return 0;
}*/ 
///-----------------------------------------------------------------------------------------------------------------------
/*
//function to find firstTKN //
string firstTKN( string x){
istringstream ss(x);
string token;
vector< string> y;
while (getline(ss, token, '/')) {
y.push_back(token) ; }
return y[0];
} 
//---------------------------------------
//function to find  lastTKN//
string lastTKN( string x){
istringstream ss(x);
string token;
vector< string> y;
while (getline(ss, token, '/')) {  // or while ss>> token;
y.push_back(token) ; }
return y[y.size()-1];
}  



*/
    
 //===========================================================================================================================///   
   // The elements must be sorted to output all the combinations
  std::sort (graphVec.begin(),graphVec.end());

  string strg="";
//  std::cout << "The possibles are:\n";
  do {
     for ( int i=0; i<graphVec.size(); i++){
         strg+=graphVec[i];
         }
     /*seperate s into tokens - using sstream- then push into a temp vector, then get vec[0] and seperated into tokens by '/'
     if ( first token == firstafarg && last token == first token of v[1] && last token of v[1] == first token ofv[2] and so on 
     till && last takon of v[size()-1] == lastFragment;; then push the string s into a vectore of possible RNA and that is it !!*/    
         
  //   cout<<strg<<endl;
     if ( strg[0] == firstFragment[0] && strg[strg.size()-2]==lastFrag[lastFrag.length()-1]){ 
          VectorOfPermut.push_back(strg);}
          
      strg="";   
      
      
    //This printing can be improved to handle any number of sentences, not only four.
   // std::cout << graphVec[0] <<"*"<< graphVec[1] <<"*"<< graphVec[2] <<"*"<< graphVec[3] << '\n';
  } while ( std::next_permutation(graphVec.begin(),graphVec.end()) );
  //cout<<" the following are the possible matches:"<<endl;
  for (int i =0; i<VectorOfPermut.size(); i++){
  //    cout<<VectorOfPermut[i]<<endl;
      }
 //------************************************************---



vector <string> vv;
for (int i =0; i<VectorOfPermut.size(); i++){
    int z=0;
    int o=0;
    string G;
    string R;
    string N="";
    string Search = VectorOfPermut[i];
    for ( int j= 0; j< Search.length()-1; j++){
       //string N="";
        if ( Search[j]!= '/' && Search[j] != '*'){
              N+=Search[j];}
             // cout<<"1:"<<N<<"&"<<endl;
        if( Search[j]=='/'){ 
                 // cout<<"1:"<<N<<"&"<<endl;
            N="";  // clear
            }
          /*  for ( t ; t<Search.size()-1&& Search[t] != '/' &&Search[t]!='*'  ;t++){
                N = Search[t];
                if ( Search[t] == '/'){
                    // int p = t+1;
                     N="";}*/
             if (Search[j] == '*'){
                           z++;
                    //       cout << " z:"<<z<<endl;
                           R=N ;
                    //       cout <<" R is : "<<R <<endl;
                           int k = j+1;
                           while ( Search[k] != '/' && Search[k] !='*' && k< Search.length()-1){
                               G  +=Search[k];
                               k++;}
                        //       cout<< " G is : "<<G <<endl;
                               if ( G==R){
                                o++;
                        //       cout<<"o:" <<o<<endl;
                        //       cout << "A possible Path Has Found!!"<<endl;
                               } 
                               N="";
                               G.clear();
                               R.clear();
                               j=k;
                               }
                             
                       }
                    
              if (z==o){
                        cout << "A possible Path Has Found!!"<<endl;
                        vv.push_back( Search);
                        }
                        }   
                        
        if (vv.size()>0){
                       cout<<" the paths are:"<<endl;
                       for (int i=0; i<vv.size();i++){
                           cout <<vv[i]<<endl;
                           }
                           
                           }
  ///-------------------------------------------------------------------------------//
                           
  if (vv.size()>0){
               string m; 
               string a,b;      
               for (int i=0; i<vv.size();i++){
                m= vv[i];
                for ( int y= 0; y < m.length(); y++){
                 if ( m[y] != '/' && m[y] != '*' ){
                      a+=m[y];}
                 if ( m[y]=='*'){
                  int s = y;
                  while (  m[s]!= '/'){
                        b += m[s];
                        s++;
                        }
                        y=s;
                        }                                             
                  }
 // cout << a<< endl;    
 Final_Results.push_back (a);  
 a.clear();     
                }                            
                    
// cout << a<< endl;    
// Final_Results.push_back (a);
               
}
cout<<"****************************"<<endl;                 
if (Final_Results.size()>0){
                            cout<<" the results are:"<<endl;
                            for( int a=0; a <Final_Results.size();a++){
                                 cout<< Final_Results[a]<<endl;
                                 }}   
    
     
///--------------------------END---------------------------------------------------------------
   system("pause");
   return 0;
}
