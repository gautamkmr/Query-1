#include<vector>
#include<string.h>
#include<fstream>
#include<map>
#include<stdlib.h>
#include<algorithm>
#include<iostream>
using namespace std;

  map<int, vector<string> >mp;
  map<string, vector<int> >dict;
  vector<int> res;  //will contain all line where query has been matched 

void intersection(vector<int> &vec, bool flag)
{
  if(!flag) //first set
  {
     for(int i=0;i<vec.size(); i++)
       res.push_back(vec[i]);
  }
  else  //find the intersection
  {
     vector<int> tmp;
     tmp.clear();
     int i=0;
     int j=0;
     while(i<res.size() && j<vec.size())
     {
       if(res[i]==vec[j]){
         tmp.push_back(res[i]);
         i++;
         j++;
       }
       else if(res[i]<vec[j])
         i++;
       else
         j++;
     } 
    //copy the content of temp to the answer
     res.clear();
     i=0;
     while(i<tmp.size())
      res.push_back(tmp[i++]);
  }
}
void sort_dictionary()  //will be helpful to find the intersection 
{
   map<string, vector<int> >::iterator dictit;
   for(dictit = dict.begin(); dictit != dict.end(); dictit++)
   {
      sort(dictit->second.begin(), dictit->second.end()); 
   }
}
void print()
{
  map<int, vector<string> >::iterator mpit;
  map<string, vector<int> >::iterator dictit;
  for(mpit = mp.begin(); mpit != mp.end(); mpit++)
  {
     cout<<mpit->first<<":";
     for(int j=0;j<mpit->second.size();j++)
      cout<<mpit->second[j]<<" ";
     cout<<"\n";
  }
  for(dictit = dict.begin(); dictit != dict.end(); dictit++)
  {
     cout<<dictit->first<<":";
     for(int j=0;j<dictit->second.size();j++)
      cout<<dictit->second[j]<<" ";
     cout<<"\n";
  }

}

void handle_query(string str, int line_count) {
char * line = new char[str.size() + 1];
std::copy(str.begin(), str.end(), line);
line[str.size()] = '\0'; // don't forget the terminating 0

  // don't forget to free the string after finished using it
  bool *visit = new bool[line_count+1];
  bool *temp = new bool[line_count+1];
  memset(visit,false, line_count+1);
  memset(temp,false, line_count+1);
  char *pch;
  char *newLine = strchr(line, '\n');
  if(newLine)
   *newLine = 0;
  pch = strtok(line," ,.-");
  bool flag = false;
  while(pch != NULL)
  {
    if(!strcmp(pch,"EOF"))
    {
       cout<<"Exit !!!\n";
       exit(0);
    }
    std::string key(pch); 
    
    if(dict.find(key) != dict.end())
    {
      vector<int> tmp;
      for(int i=0;i<dict[key].size();i++)
      {
        int j = dict[key][i];  
        tmp.push_back(j);
      }
      intersection(tmp,flag);
    }
    else 
     cout<<pch<<" not found\n";
    flag = true;  
    pch = strtok (NULL, " ,.-");
  }
  
  for(int i=0;i<res.size();i++)
  { 
    for(int j=0; j<mp[res[i]].size(); j++)
     cout<<mp[res[i]][j];
  }
 delete[] line;
 delete[] visit;
 delete[] temp;
 res.clear();
}

void handle_line(char *line, int line_count) {
  std::string str(line);
  mp[line_count].push_back(str);
  char *pch;
  char *newLine = strchr(line, '\n');
  if(newLine)
   *newLine = 0;
  pch = strtok(line," \n");
  while(pch != NULL)
  {   
    std::string str(pch);
    if(dict.find(str)==dict.end())
    {
       vector<int> tmp;
       tmp.push_back(line_count);
       dict.insert(make_pair(str,tmp));
    }
    else
    {
       dict[str].push_back(line_count);
    }
    pch = strtok (NULL, " ,.-");
  }
}

int main(int argc, char *argv[]) {

    int size = 1024, pos;    
    int c;
    char *buffer = (char *)malloc(size);
    int line_count=1;
    FILE *f = fopen(argv[1], "r");
    if(!f)
    {
       cout<<"File not found\n";
       exit(-1);
     }
    if(f) {
      do { // read all lines in file
        pos = 0;
        do{ // read one line
          c = fgetc(f);
          if(c != EOF) buffer[pos++] = (char)c;
          if(pos >= size - 1) { // increase buffer length - leave room for 0
            size *=2;
            buffer = (char*)realloc(buffer, size);
          }
        }while(c != EOF && c != '\n');
        buffer[pos] = 0;
        // line is now in buffer
       if(c != EOF)
        handle_line(buffer,line_count++);
      } while(c != EOF); 
      fclose(f);           
    }
    free(buffer);
 sort_dictionary();

 while(1){
    string query;
    std::getline (std::cin,query);
    handle_query(query,line_count);
    fflush(stdin);
   }
    return 0;
}
