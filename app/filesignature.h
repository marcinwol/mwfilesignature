#ifndef FILESIGNATURE_H
#define FILESIGNATURE_H

#include <iostream>
#include <fstream>
#include <set>
#include <vector>


#ifndef BRACED_INIT_LIST
    #define BRACED_INIT_LIST(...) {__VA_ARGS__}
#endif

#ifndef ADD_SIGNATURE
    #define ADD_SIGNATURE(sig, b) KNOWN_IMG_SIGNATURES.emplace<vector<unsigned char>, string>(BRACED_INIT_LIST sig, b);
#endif



namespace mw {

  using namespace std;


  vector<unsigned char>
  get_bin_signature(const string & in_file, int length = 132);

  struct Signature
  {
     vector<unsigned char> sig;
     string img_type;

     Signature(const vector<unsigned char> & sig_, const string & img_type_ = "");

     bool operator < (const Signature & other) const;
     bool operator == (const Signature & other) const;

  };






//     inline void
//     init_signatures()
//     {
//      //   ADD_SIGNATURE((1,2,3,4), "JPGE");
//      //   ADD_SIGNATURE((1,2,3,5), "JPFP");
//      //   ADD_SIGNATURE((1,2,3),   "JPFP3");
//       ;
//     }


 }


#endif // FILESIGNATURE_H
