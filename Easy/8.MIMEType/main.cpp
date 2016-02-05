/******************************************
 The Goal
MIME types are used in numerous internet protocols to associate a media type (html, image, video ...) with the content sent. The MIME type is generally inferred from the extension of the file to be sent.

You have to write a program that makes it possible to detect the MIME type of a file based on its name.
  Rules
You are provided with a table which associates MIME types to file extensions. You are also given a list of names of files to be transferred and for each one of these files, you must find the MIME type to be used.

The extension of a file is defined as the substring which follows the last occurrence, if any, of the dot character within the file name.
If the extension for a given file can be found in the association table (case insensitive, e.g. TXT is treated the same way as txt), then print the corresponding MIME type. If it is not possible to find the MIME type corresponding to a file, or if the file doesn’t have an extension, print UNKNOWN.
***********************************************/

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

int N; // Number of elements which make up the association table.
int Q; // Number Q of file names to be analyzed.

string extension(string s);
string knownExt(map<string,string> &m, string s);
inline void convertUpper(string& str,string& converted);
inline void convertLower(string& str,string& converted);

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/
int main()
{
    cin >> N; cin.ignore();
    cin >> Q; cin.ignore();
    
    map<string,string> mime;
    
    string a;
    for (int i = 0; i < N; i++) {
        pair<string,string> p;
        cin>>a>>p.second; cin.ignore();
        convertLower(a,p.first);
        mime.insert(p);
    }
    
    string fname[Q];
    for (int i = 0; i < Q; i++) {
        getline(cin, fname[i]);
    }
    
    
    string ext,type,lowExt;
    for(int i=0;i<Q;++i){
        lowExt="";
        ext = extension(fname[i]);
        convertLower(ext,lowExt);        
        if(lowExt!=""){
            type = knownExt(mime,lowExt);
            if(type!=""){
                cout << type << endl;
            }
            else cout << "UNKNOWN" << endl;
        }
        else cout << "UNKNOWN" << endl;
    }
}


string extension(string s){
    int i = s.length()-1;
    
    if(s[s.length()-1]=='.') return "";
    else{
        while(i>=0 && s[i]!='.') i--;

        if(i>=0)return s.substr(i+1,s.length());
        else return "";
    }
}


string knownExt(map<string,string> &m, string s){
    string sLow;
    convertLower(s,sLow);
  
    bool found = false;
    map<string,string>::iterator it;
    it=m.find(sLow);
    if (it!=m.end()) return it->second;
    else return "";
}


inline void convertLower(string& str,string& converted){
	for(short i = 0; i < str.size(); ++i)
		converted += tolower(str[i]);
}
