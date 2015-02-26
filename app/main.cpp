#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>

#include "filesignature.h"

using namespace std;


int main(int ac, char* av[])
{


  string a_path {"/mnt/e/DCIM/20140907_165341.jpg"};

    int length=2;

//  cin >> length;

  vector<unsigned char> signature = mw::get_bin_signature(a_path, length);

  vector<unsigned char> bytes {0xFF, 0xFF, 0xFD};

  for (const unsigned char & v: signature)
  {
      cout << hex << setfill('0') << setw(2) << uppercase << static_cast<unsigned>(v) <<" ";
  }

  cout << endl;


  mw::signature_set sig = mw::get_known_signatures();


//    mw::Signature unknowns {{1,2,3,4}};

//    set<mw::Signature>::const_iterator item = sig_set.find(unknowns);
//    if (item != sig_set.end())
//    {
//        cout << "found " << (*item).img_type << endl;
//    }



  //cout << (s1 < s2) << endl;
//

  cout << "Hello World!" << endl;

    return 0;
}
