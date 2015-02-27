#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>

#include "filesignature.h"

using namespace std;


int main(int ac, char* av[])
{



  vector<string> paths {
      "/mnt/e/DCIM/20140907_165341.jpg",
      "/mnt/e/ImageDatabases/Ida_Sep_2014/11_reproducibility_of_params/example_of_manual_selection/019_dhs1328345_0_im_2_i0000_0000b_DPI_177_R.xcf",
      "/mnt/e/ImageDatabases/Ida_Sep_2014/04_front_tiffs_cropped/019_dhs1328345_0_im_2_i0000_0000b_DPI_177_R.tiff",
      "/mnt/e/ImageDatabases/Ida_Sep_2014/02_dicoms_extracted/dcm/002_dhs1263510_0_im_2_i0000_0000b.dcm"
  };



  mw::signature_set known_sigs = mw::get_known_signatures();

  set<int> sig_lengths = mw::get_known_signatures_lengths();


  for (const string & a_path : paths)
  {
      cout << a_path << endl;
      vector<unsigned char> signature = mw::get_bin_signature(a_path);
      cout << mw::get_signature_as_string(signature) << endl;

      for (auto sig_length : sig_lengths)
      {

          vector<unsigned char> v_partial(signature.begin(),
                                          signature.begin() + sig_length);

          cout << sig_length <<": " << mw::get_signature_as_string(v_partial);

          cout << endl;

          mw::signature_set_iter si = known_sigs.find(v_partial);

          if (si != known_sigs.end())
          {
              cout << "We found a match to: "
                   << (*si).img_type
                   << endl;
              break;
          }

      }
    }

    return 0;
}
