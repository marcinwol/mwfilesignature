#include "filesignature.h"

namespace mw {



  Signature::Signature(const vector<unsigned char> & sig_, const string & img_type_):
      sig {sig_}, img_type {img_type_} {}

  bool Signature::operator < (const Signature & other) const
  {
        return sig < other.sig;
  }

  bool Signature::operator == (const Signature & other) const
  {
        return sig == other.sig;
  }




  vector<unsigned char>
  get_bin_signature(const string & in_file, int length)
  {

      vector<unsigned char> signature;

      ifstream ifs {in_file, ios_base::binary};

      if (!ifs)
      {
          return signature;
      }

      char bytes[length];

      ifs.read(bytes, length);

      signature.assign(bytes, bytes + length);

      return signature;
  }

}
