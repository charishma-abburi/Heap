#include <bits/stdc++.h>

using namespace std;

class page
{
    public:
    vector<int> rids;
    vector<int> recsizes;
    int freespaceptr;
    int space_avail;
};

class file
{
    int max_pgsize;
    vector<page*> pages; 

    public:
    file(int);
    void insert_rec(int,int);
    bool search_id(int);
    void status();

};

file::file(int maxpgsize)
{
    this->max_pgsize = maxpgsize;
}

void file::insert_rec(int rec_size,int pkey)
{
    // initially if file is empty
  if(pages.size()==0)
  {
      page* newpage = new page();
      newpage->recsizes.push_back(rec_size);
      newpage->rids.push_back(pkey);
      newpage->freespaceptr = 16+rec_size+4;
      newpage->space_avail = max_pgsize - newpage->freespaceptr;
      pages.push_back(newpage);
      return;
  }
 
 // if file is not empty traverse through the pages from start and check
 // if free space is available
  for(int i=0; i<pages.size(); i++)
  {
        if(pages[i]->space_avail >= (rec_size+4))
        {
            pages[i]->recsizes.push_back(rec_size);
            pages[i]->rids.push_back(pkey);
            pages[i]->freespaceptr = pages[i]->freespaceptr + rec_size+4;
            pages[i]->space_avail = max_pgsize - pages[i]->freespaceptr;
            return;
        }
  }
  // space available is not sufficient for the new record 
  // create a new page
  page* newpage = new page();
      newpage->recsizes.push_back(rec_size);
      newpage->rids.push_back(pkey);
      newpage->freespaceptr = 16+rec_size+4;
      newpage->space_avail = max_pgsize - newpage->freespaceptr;
      pages.push_back(newpage);
}

void file::status()
{
    cout<<pages.size()<<" ";
    for(int i=0; i<pages.size(); i++)
    {
        cout<<pages[i]->recsizes.size()<<" ";
    }
    cout<<endl;
}

bool file::search_id(int rid)
{
    for(int i=0 ; i<pages.size(); i++)
    {
        auto it = find(pages[i]->rids.begin(),pages[i]->rids.end(),rid);
        if(it != pages[i]->rids.end())
        {
            cout<<i<<" "<<(it - pages[i]->rids.begin())<<endl;
            return true;
        }
    }
    cout<<-1<<" "<<-1<<endl;
    return false;
}



int main()
{
    int maxpg_size;
    cin>>maxpg_size;
    file f(maxpg_size);
    int n=9;
    while(n!=4)
    {
        cin>>n;
        if(n==1)
        {
            int rsize,pkey;
            cin>>rsize>>pkey;
            f.insert_rec(rsize,pkey);
        }
        else if(n==2)
        {
            f.status();
        }
        else if(n==3)
        {
            int rid;
            cin>>rid;
            f.search_id(rid);
        }
    }
    return 0;
}