/*By :: Hani Aboudeshisha      Independent Study    Hunter College   Summer 2013   
Professor :: Christina Zamfirescu
-------------------------------------------Program Description---------------------------------------------
+ The goal of this program is to reconstruct all possible RNA strands from its fragments obtained by the silicing enzymes
G and UC . Two identical RNA strands are needed, the first is treated with G-slicing enzyme and the second is treated with 
UC-slicing enzyme. The fragments of both treatment is saved into a file - the first line is the G fragments 
and the second line is the UC fragment.
The program will then read the file and do the following:
    1- conclude the last fragment
    2- do some analysis by 'virtually splicing each fragment by its opposite enzyme, 
    3- then conclude the first fragment  
    4- then a garph will be constructed where outer bases are the vertices and the inner bases are the edges
    5- finally, the program will determine all possible RNA strands that could be reconstructed and output it.
NOTE1 : five files are attached -(input1-5)- that cover most of the cases like{ different ends, similar ends, more than one RNA 
 could be reconstructed ,...etc..} Just go to line 50 and change the number for a quick testing.
NOTE2 : If you are using windows machine, please go to lines 55,and 345 and uncomment the system pause    */




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
//------------------------------------------------
 string input; 
   string  Gfragments;
    string UCfragments;
	ifstream in;
	in.open("input2.txt");

	if(!in)
	{
		cout<<"No input file"<<endl;
	//	system("pause");
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
//------------------------------------------------
    char split_char = ',';
    istringstream G_split(Gfragments);
    vector<string> G_tokens;
    for (string each; getline(G_split, each, split_char); G_tokens.push_back(each));
    //------------------------Entering UC Freagments, spelited into tokens, save into a vector -------------------//
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
         tkn=G_tokens[i];
         char last = tkn[tkn.length()-1];
         if ( last != 'G'){ 
              lastFragment1 = tkn;
              counter++;
              //NOTE: last fragment will show either in G or UC but not in both Unless it ends with A.. and it must show up
              }
         }
    //--------------------------------------------------------------------------------------------------------//     
    for ( int i=0; i < UC_tokens.size() ; i++){
          tkn=UC_tokens[i];
          char last2 = tkn[tkn.length()-1];
          if ( last2 != 'U'&& last2 !='C'){ 
              lastFragment2 = tkn;
              counter++;
              }
         }     
   //Now, we need to determine the first fragment.. in order to this ,we need to further splicing- cross splicing
   // and do some analysis.//   better to use if else if else
   if (counter ==1 && lastFragment1.size() >0 && lastFragment2.size()==0 ) { lastFragment= lastFragment1;}
   else if (counter ==1 && lastFragment2.size() >0 && lastFragment1.size()==0 ) { lastFragment= lastFragment2;}
   else if ( counter > 1 && lastFragment1[lastFragment1.length()-1]== 'A' && lastFragment2[lastFragment2.length()-1] =='A'){ // if ends with A
         if ( lastFragment1.length()> lastFragment2.length()) { lastFragment= lastFragment1;}
          else { lastFragment= lastFragment2;}
     }
       
  else if (counter > 1 && lastFragment1[lastFragment1.length()-1]!= 'A' &&  lastFragment2[lastFragment2.length()-1] !='A')       
   if (counter > 1 && lastFragment1[lastFragment1.length()-1]!= lastFragment2[lastFragment2.length()-1] !='A')
   { cout <<" ERROR ENTERING FRAGMENTS!, PLEASE TRY AGAIN  "<<endl;
                     cout<<" EXISTING !! "<<endl;
                     clock_t start_time = clock();
                     clock_t end_time =  5000 + start_time;
                     while(clock() != end_time){};
                     exit (0) ;
                   }                
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
//---------------------------------------------------------------------------------------//     
 string tk; 
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
//------------------------------------------------------------------------------------------//
vector <string > intersect;
intersect = intersection(innerBases, outerBases);   
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
//------------------------------------------------------------------------------------------//
string comp0=vDifferences[0];
string comp1=vDifferences[1];
if ( comp0[comp0.length()-1]== lastFragment[lastFragment.length()-1] && comp1[comp1.length()-1]!= lastFragment[lastFragment.length()-1]){
     firstFragment = comp1;
     lastFrag = comp0;
     cout /*<<" : 1 :"*/<<endl;}
//-----------------------     
else if ( comp0[comp0.length()-1]!= lastFragment[lastFragment.length()-1] && comp1[comp1.length()-1]== lastFragment[lastFragment.length()-1]){
     firstFragment = comp0;
     lastFrag = comp1;
     cout /*<<" : 2 :"*/<<endl;}
//--------------------
else if ( comp0[comp0.length()-1]== lastFragment[lastFragment.length()-1] && comp1[comp1.length()-1]== lastFragment[lastFragment.length()-1]){
     if (lastFragment.find(comp0) != string::npos && !lastFragment.find(comp1) != string::npos   )
     { lastFrag = comp0; firstFragment= comp1;cout /*<<" : 3 :"*/<<endl;}
   //  if(comp0.length()> comp1.length()){ lastFrag = comp0; firstFragment= comp1;cout <<" : 3 :"<<endl;}
      if (lastFragment.find(comp1) != string::npos && !lastFragment.find(comp0) != string::npos   )
     { lastFrag = comp1; firstFragment= comp0;cout /*<<" : 4 :"*/<<endl;}    
   //  if(comp0.length()< comp1.length()){ lastFrag = comp1; firstFragment= comp0;cout <<" : 4 :"<<endl;}
     }
else{
     firstFragment= comp1;
     lastFrag= comp0; 
     cout /*<<" : 5 : "*/<<endl;}    
     


//---------------------------------------------------------------------------------------- 
 cout<<"First fragment is : "<< firstFragment <<endl;
 cout<<"Last fragment is  : "<<lastFrag<<endl; 
 //------------------------------NOW, we start the graph analysis to find closed Eluerian circuites -------------//  
 //=============================================================================================================///   
   // The elements must be sorted to output all the combinations
  std::sort (graphVec.begin(),graphVec.end());
  string strg="";
  do {
     for ( int i=0; i<graphVec.size(); i++){
         strg+=graphVec[i];
         }
     /*seperate s into tokens - using sstream- then push into a temp vector, then get vec[0] and seperated into tokens by '/'
     if ( first token == firstafarg && last token == first token of v[1] && last token of v[1] == first token ofv[2] and so on 
     till && last takon of v[size()-1] == lastFragment;; then push the string s into a vectore of possible RNA and that is it !!*/    
     if ( strg[0] == firstFragment[0] && strg[strg.size()-2]==lastFrag[lastFrag.length()-1]){ 
          VectorOfPermut.push_back(strg);}         
      strg="";        
    //This printing can be improved to handle any number of sentences, not only four.
   // std::cout << graphVec[0] <<"*"<< graphVec[1] <<"*"<< graphVec[2] <<"*"<< graphVec[3] << '\n';
  } while ( std::next_permutation(graphVec.begin(),graphVec.end()) );
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
        if ( Search[j]!= '/' && Search[j] != '*'){
              N+=Search[j];}
        if( Search[j]=='/'){ 
            N="";  // clear
            }
             if (Search[j] == '*'){
                           z++;
                           R=N ;
                           int k = j+1;
                           while ( Search[k] != '/' && Search[k] !='*' && k< Search.length()-1){
                               G  +=Search[k];
                               k++;}
                               if ( G==R){
                                o++;
                               } 
                               N="";
                               G.clear();
                               R.clear();
                               j=k;
                               }                            
                       }                    
              if (z==o){
                        vv.push_back( Search);
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
                   Final_Results.push_back (a);
                   a.clear();                         
                }                                                                  
}                 
if (Final_Results.size()>0){
                            cout<<"There are "<< Final_Results.size()<< " possiblities "<<endl;
                            cout<<"----------------------------"<<endl;
                            for( int a=0; a <Final_Results.size();a++){
                                 cout<< Final_Results[a]<<endl;
                                 }}      
///--------------------------END---------------------------------------------------------------
//  system("pause");
   return 0;
}
