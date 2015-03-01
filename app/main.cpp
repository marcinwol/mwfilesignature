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


int main(int ac, char* av[])
{


    //std::string in_folder = "/media/sf_D_DRIVE/dcm_for_tests";
    std::string in_folder = "/media/sf_D_DRIVE/Photos_2014";
    // std::string in_folder = "/media/sf_D_DRIVE";



    std::vector<string> found_files;

    if (dir_tree_scan(in_folder, found_files) == 1)
    {
     cout << "some error occured";
     return 1;
    }

    size_t file_no {1};

    for (const string & a_path : found_files)
    {

      mw::Signature empty_signature;

      cout << file_no << ": " << a_path;

      if (mw::is_image(a_path, &empty_signature))
      {
         cout << " type: " <<  empty_signature.img_type;
      }

      cout << endl;

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


