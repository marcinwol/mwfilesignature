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


  vector<string> paths {
      "/mnt/e/DCIM/20140907_165341.jpg",
      "/mnt/e/ImageDatabases/Ida_Sep_2014/11_reproducibility_of_params/example_of_manual_selection/019_dhs1328345_0_im_2_i0000_0000b_DPI_177_R.xcf",
      "/mnt/e/ImageDatabases/Ida_Sep_2014/04_front_tiffs_cropped/019_dhs1328345_0_im_2_i0000_0000b_DPI_177_R.tiff",
      "/mnt/e/ImageDatabases/Ida_Sep_2014/02_dicoms_extracted/dcm/002_dhs1263510_0_im_2_i0000_0000b.dcm"
  };


 std::string in_folder = "/tmp";



 std::vector<string> found_files;

 if (dir_tree_scan(in_folder, found_files) == 1)
 {
     cout << "some error occured";
     return 1;
 }



  mw::signature_set known_sigs = mw::get_known_signatures();

  set<int> sig_lengths = mw::get_known_signatures_lengths();


  size_t file_no {1};


  for (const string & a_path : found_files)
  {

      if (a_path.find("NEF") == string::npos)
      {
      //    continue;
      }
      cout << file_no << ": " << a_path << endl;

      vector<unsigned char> signature = mw::get_bin_signature(a_path);
      //cout << mw::get_signature_as_string(signature) << endl;

      if (signature.empty())
      {
          continue;
      }


      //for (auto sig_length : sig_lengths)
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
              cout << "We found a match to: "
                   << (*si).img_type
                   << endl;
              break;
          }
      }

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
/*        if (node->fts_level > 0 && node->fts_name[0] == '.')
        {
            //fts_set(tree, node, FTS_SKIP);

        }



        else*/

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


