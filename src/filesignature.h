#ifndef FILESIGNATURE_H
#define FILESIGNATURE_H

#include <iostream>
#include <fstream>
#include <set>
#include <vector>


#ifndef SIGNATURE_SET_NAME
    #define SIGNATURE_SET_NAME known_signatures
#endif

#ifndef BRACED_INIT_LIST
    #define BRACED_INIT_LIST(...) {__VA_ARGS__}
#endif

#ifndef ADD_SIGNATURE
    #define ADD_SIGNATURE(sig, b) \
          SIGNATURE_SET_NAME.emplace<vector<unsigned char>, string> \
                    (BRACED_INIT_LIST sig, b);
#endif



namespace mw {

  using namespace std;

  struct Signature;

  using signature_set = set<Signature>;



  struct Signature
  {
     vector<unsigned char> sig;
     string img_type;

     Signature(const vector<unsigned char> & sig_, const string & img_type_ = "");

     bool operator < (const Signature & other) const;
     bool operator == (const Signature & other) const;

  };



  /**
   * @brief returns a reference to the set of signatures containing known signatures.
   *        New signatures are compared against this set to determine the file type.
   * @return
   */
  inline signature_set &
  get_known_signatures()
  {
      static signature_set SIGNATURE_SET_NAME;

      ADD_SIGNATURE((1,2,3,4), "JPGE");
      ADD_SIGNATURE((1,2,3,5), "JPFP");
      ADD_SIGNATURE((1,2,3),   "JPFP3");

      return known_signatures;
  }



  vector<unsigned char>
  get_bin_signature(const string & in_file, int length = 132);



 }


#endif // FILESIGNATURE_H
