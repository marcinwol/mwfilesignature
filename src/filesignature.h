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
    #define ADD_SIGNATURE(sig, b, is_image) \
          SIGNATURE_SET_NAME.emplace<vector<unsigned char>, string> \
                    (BRACED_INIT_LIST sig, b, is_image);
#endif



namespace mw {

  using namespace std;

  struct Signature;

  using signature_set       = multiset<Signature>;
  using signature_set_iter  = multiset<Signature>::iterator;
  using signature_set_riter = multiset<Signature>::reverse_iterator;



  struct Signature
  {
     vector<unsigned char> sig;
     string img_type;
     bool is_image;

     Signature();

     Signature(const vector<unsigned char> & sig_,
               const string & img_type_ = "UNKNOWN",
               bool is_image_ = false);

     bool operator <  (const Signature & other) const;
     bool operator == (const Signature & other) const;
     operator bool () const;

  };


  set<int>
  get_known_signatures_lengths();

  string
  get_signature_as_string(const vector<unsigned char> & signature);


  vector<unsigned char>
  get_bin_signature(const string & in_file, int length = 132);

  bool
  is_ascii(const string & in_file, vector<mw::Signature> & sig_holder);


  bool
  detect_type(const string & a_path, vector<mw::Signature> & sig_holder);

  bool
  is_image(const string & a_path, mw::Signature * sig_holder = nullptr);


  /**
   * @brief returns a reference to the multiset of signatures containing known signatures.
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

      ADD_SIGNATURE((0x42, 0x4D),             "BMP",   true);

      ADD_SIGNATURE((0x42, 0x4D),             "CHM",   false);

      ADD_SIGNATURE((0xD0, 0xCF, 0x11, 0xE0,
                     0xA1, 0xB1, 0x1A, 0xE1,
                     0x00, 0x00, 0x00, 0x00,
                     0x00, 0x00, 0x00, 0x00), "DB",    false);

      ADD_SIGNATURE((0x49, 0x54, 0x53, 0x46), "DIB",   false);

      ADD_SIGNATURE((0x4D, 0x5A),             "DLL",   false);


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
                     0x44, 0x49, 0x43, 0x4D), "DCM",    true);

      ADD_SIGNATURE((0x50, 0x4B, 0x03, 0x04,
                     0x14, 0x00, 0x06, 0x00), "DOCX",   false);

      ADD_SIGNATURE((0x4D, 0x5A, 0x90, 0x00,
                     0x03, 0x00, 0x00, 0x00,
                     0x04, 0x00, 0x00, 0x00,
                                 0xFF, 0xFF), "EXE",    false);



      ADD_SIGNATURE((0x47, 0x49, 0x46, 0x38,
                                 0x37, 0x61), "GIF",    true);

      ADD_SIGNATURE((0x47, 0x49, 0x46, 0x38,
                                 0x39, 0x61), "GIF",    true);

      ADD_SIGNATURE((0x3C, 0x21),             "HTML",   false);

      ADD_SIGNATURE((0x00, 0x00, 0x01, 0x00), "ICO",    true);

      ADD_SIGNATURE((0x69, 0x63, 0x6E, 0x73), "ICNS",   true);

      ADD_SIGNATURE((0xFF, 0xD8, 0xFF, 0xE1), "JPEG",   true);
      ADD_SIGNATURE((0xFF, 0xD8, 0xFF, 0xE0), "JPEG",   true);
      ADD_SIGNATURE((0xFF, 0xD8, 0xFF, 0xE8), "JPEG",   true);

      ADD_SIGNATURE(( 0x4D, 0x41, 0x54, 0x4C,
                      0x41, 0x42, 0x20, 0x35,
                      0x2E, 0x30, 0x20, 0x4D,
                      0x41, 0x54, 0x2D, 0x66,
                      0x69, 0x6C, 0x65),      "MAT",    false);


      ADD_SIGNATURE((0xCE, 0xFA, 0xED, 0xFE), "MACH-O", false);

      ADD_SIGNATURE((0x0C, 0xED),             "MP",     false);

      ADD_SIGNATURE((0x4D, 0x4D, 0x00, 0x2A,
                     0x00, 0x00, 0x00, 0x08,
                                       0x00), "NEF",    true);

      ADD_SIGNATURE((0x49, 0x49, 0x2A, 0x00,
                     0x08, 0x00, 0x00, 0x00,
                                       0x1A), "NEF",    true);

      ADD_SIGNATURE((0x25, 0x50, 0x44, 0x46), "PDF",    false);

      ADD_SIGNATURE((0x89, 0x50, 0x4E, 0x47,
                     0x0D, 0x0A, 0x1A, 0x0A), "PNG",    true);

      ADD_SIGNATURE((0x50, 0x4B, 0x03, 0x04,
                     0x14, 0x00, 0x06, 0x00), "PPTX",   false);

      ADD_SIGNATURE((0x38, 0x42, 0x50, 0x53), "PSD",    true);

      ADD_SIGNATURE((0x49, 0x20, 0x49),       "TIFF",   true);
      ADD_SIGNATURE((0x4D, 0x4D, 0x00, 0x2A), "TIFF",   true);
      ADD_SIGNATURE((0x4D, 0x4D, 0x00, 0x2B), "TIFF",   true);
      ADD_SIGNATURE((0x49, 0x49, 0x2A, 0x00), "TIFF",   true);

      ADD_SIGNATURE((0x67, 0x69, 0x6D, 0x70,
                     0x20, 0x78, 0x63, 0x66,
                     0x20, 0x66, 0x69, 0x6C,
                                       0x65), "XCF",    true);

      ADD_SIGNATURE((0x50, 0x4B, 0x03, 0x04,
                     0x14, 0x00, 0x06, 0x00), "XLSX",   false);

      ADD_SIGNATURE((0x3C                  ), "XML",    false);


      ADD_SIGNATURE((0x50, 0x4B, 0x03, 0x04), "ZIP",    false);




      return SIGNATURE_SET_NAME;
  }



  inline set<int>
  get_known_signatures_lengths()
  {
      signature_set sig_set = get_known_signatures();

      static set<int> sig_lengths;

      if (!sig_lengths.empty())
      {
          return sig_lengths;
      }

      for (const Signature & sig: sig_set)
      {
            sig_lengths.insert(sig.sig.size());
      }

      return sig_lengths;
  }




 }


#endif // FILESIGNATURE_H
