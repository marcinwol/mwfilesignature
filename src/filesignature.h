#ifndef FILESIGNATURE_H
#define FILESIGNATURE_H

#include <iostream>
#include <fstream>
#include <set>
#include <vector>
#include <sstream>
#include <iomanip>

#include <string.h>
#include <errno.h>


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
  using signature_set_iter = set<Signature>::iterator;
  using signature_set_riter = set<Signature>::reverse_iterator;



  struct Signature
  {
     vector<unsigned char> sig;
     string img_type;

     Signature(const vector<unsigned char> & sig_,
               const string & img_type_ = "");

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

      if (!SIGNATURE_SET_NAME.empty())
      {
          return SIGNATURE_SET_NAME;
      }

      ADD_SIGNATURE((0x42, 0x4D),             "BMP");
      ADD_SIGNATURE((0x42, 0x4D),             "DIB");


      ADD_SIGNATURE((0x00, 0x00, 0x00, 0x00,
                     0x00, 0x00, 0x00, 0x00,
                     0x00, 0x00, 0x00, 0x00,
                     0x00, 0x00, 0x00, 0x00,
                     0x00, 0x00, 0x00, 0x00,
                     0x00, 0x00, 0x00, 0x00,
                     0x00, 0x00, 0x00, 0x00,
                     0x00, 0x00, 0x00, 0x00,
                     0x00, 0x00, 0x00, 0x00,
                     0x00, 0x00, 0x00, 0x00,
                     0x00, 0x00, 0x00, 0x00,
                     0x00, 0x00, 0x00, 0x00,
                     0x00, 0x00, 0x00, 0x00,
                     0x00, 0x00, 0x00, 0x00,
                     0x00, 0x00, 0x00, 0x00,
                     0x00, 0x00, 0x00, 0x00,
                     0x00, 0x00, 0x00, 0x00,
                     0x00, 0x00, 0x00, 0x00,
                     0x00, 0x00, 0x00, 0x00,
                     0x00, 0x00, 0x00, 0x00,
                     0x00, 0x00, 0x00, 0x00,
                     0x00, 0x00, 0x00, 0x00,
                     0x00, 0x00, 0x00, 0x00,
                     0x00, 0x00, 0x00, 0x00,
                     0x00, 0x00, 0x00, 0x00,
                     0x00, 0x00, 0x00, 0x00,
                     0x00, 0x00, 0x00, 0x00,
                     0x00, 0x00, 0x00, 0x00,
                     0x00, 0x00, 0x00, 0x00,
                     0x00, 0x00, 0x00, 0x00,
                     0x00, 0x00, 0x00, 0x00,
                     0x00, 0x00, 0x00, 0x00,
                     0x44, 0x49, 0x43, 0x4D), "DCM");

      ADD_SIGNATURE((0x50, 0x4B, 0x03, 0x04,
                     0x14, 0x00, 0x06, 0x00), "DOCX");

      ADD_SIGNATURE((0x47, 0x49, 0x46, 0x38,
                                 0x37, 0x61), "GIF");

      ADD_SIGNATURE((0x47, 0x49, 0x46, 0x38,
                                 0x39, 0x61), "GIF");

      ADD_SIGNATURE((0x00, 0x00, 0x01, 0x00), "JPEG");

      ADD_SIGNATURE((0xFF, 0xD8, 0xFF, 0xE1), "JPEG");
      ADD_SIGNATURE((0xFF, 0xD8, 0xFF, 0xE0), "JPEG");
      ADD_SIGNATURE((0xFF, 0xD8, 0xFF, 0xE8), "JPEG");

      ADD_SIGNATURE((0x0C, 0xED),             "MP");

      ADD_SIGNATURE((0x4D, 0x4D, 0x00, 0x2A,
                     0x00, 0x00, 0x00, 0x08,
                                       0x00), "NEF");

      ADD_SIGNATURE((0x25, 0x50, 0x44, 0x46), "PDF");

      ADD_SIGNATURE((0x89, 0x50, 0x4E, 0x47,
                     0x0D, 0x0A, 0x1A, 0x0A), "PNG");

      ADD_SIGNATURE((0x50, 0x4B, 0x03, 0x04,
                     0x14, 0x00, 0x06, 0x00), "PPTX");

      ADD_SIGNATURE((0x38, 0x42, 0x50, 0x53), "PSD");

      ADD_SIGNATURE((0x49, 0x20, 0x49),       "TIFF");
      ADD_SIGNATURE((0x4D, 0x4D, 0x00, 0x2A), "TIFF");
      ADD_SIGNATURE((0x4D, 0x4D, 0x00, 0x2B), "TIFF");
      ADD_SIGNATURE((0x49, 0x49, 0x2A, 0x00), "TIFF");

      ADD_SIGNATURE((0x67, 0x69, 0x6D, 0x70,
                     0x20, 0x78, 0x63, 0x66,
                     0x20, 0x66, 0x69, 0x6C,
                                       0x65), "XCF");

      ADD_SIGNATURE((0x50, 0x4B, 0x03, 0x04,
                     0x14, 0x00, 0x06, 0x00), "XLSX");




      return SIGNATURE_SET_NAME;
  }

  set<int>
  get_known_signatures_lengths();

  string
  get_signature_as_string(const vector<unsigned char> & signature);




  vector<unsigned char>
  get_bin_signature(const string & in_file, int length = 132);


 }


#endif // FILESIGNATURE_H
