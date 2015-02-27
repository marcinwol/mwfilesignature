#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>

#include <errno.h>
#include <string.h>
#include <fts.h>

#include "filesignature.h"

using namespace std;


int dir_tree_scan(const string & in_path, vector<string> & found_paths);


bool detect_type(const string & a_path, mw::Signature & sig_holder)
{
    mw::signature_set known_sigs    = mw::get_known_signatures();
    set<int> sig_lengths            = mw::get_known_signatures_lengths();
    vector<unsigned char> signature = mw::get_bin_signature(a_path);


    if (signature.empty())
    {
        return false;
    }


    for (set<int>::reverse_iterator rit = sig_lengths.rbegin();rit!=sig_lengths.rend(); ++rit)
    {
        int sig_length = *rit;

        vector<unsigned char> v_partial(signature.begin(),
                                        signature.begin() + sig_length);

       // cout << sig_length <<": " << mw::get_signature_as_string(v_partial);

      //  cout << endl;

        mw::signature_set_iter si = known_sigs.find(v_partial);

        if (si != known_sigs.end())
        {
            sig_holder = (*si);

            return true;
        }
    }

    return false;

}


int main(int ac, char* av[])
{

 std::string in_folder = "/media/sf_D_DRIVE/dcm_for_tests";

 std::vector<string> found_files;

 if (dir_tree_scan(in_folder, found_files) == 1)
 {
     cout << "some error occured";
     return 1;
 }

  size_t file_no {1};

  //ofstream out_csv {"found_files.csv"};


  for (const string & a_path : found_files)
  {

      cout << file_no << ": " << a_path;

      mw::Signature  sig_holder;

      bool type_found = detect_type(a_path,  sig_holder);

      if (!type_found)
      {
        mw::is_ascii(a_path, sig_holder);
      }

      cout << " type: " <<  sig_holder.img_type << endl;

      ++file_no;

    }

    return 0;
}




int dir_tree_scan(const string & in_path, vector<string> & found_paths)
{

    char * cstr = new char[in_path.length() + 1];
    strcpy(cstr, in_path.c_str());

    char * path[2] {cstr, nullptr};

    size_t i {0};


    FTS *tree = fts_open(path, FTS_NOCHDIR, 0);

    if (!tree)
    {
        delete[] cstr;
        perror("fts_open");
        return 1;
    }

    FTSENT *node;

    while ((node = fts_read(tree)))
    {
        if (node->fts_info & FTS_F)
        {
            if (i % 100 == 0)
            {
                cout  << "\r" << "Read " << i << " files "
                      << "in " << in_path
                      << flush;
            }

            ++i;

           found_paths.emplace_back<string>(node->fts_path);
        }
    }

    if (errno)
    {
        delete[] cstr;
        perror("fts_read");
        return 1;
    }

    if (fts_close(tree))
    {
        delete[] cstr;
        perror("fts_close");
        return 1;
    }

    delete[] cstr;
    return 0;
}


