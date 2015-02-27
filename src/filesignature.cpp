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
          cerr << "Error : get_bin_signature: "
               << strerror(errno) << endl;
          return signature;
      }

      char bytes[length];

      ifs.read(bytes, length);

      signature.assign(bytes, bytes + length);

      return signature;
  }


  string
  get_signature_as_string(const vector<unsigned char> & signature)
  {
      ostringstream oss;

      oss << setfill('0')  << uppercase;

      for (const unsigned char & ps: signature)
      {
          oss << hex << setw(2) << static_cast<unsigned>(ps)<< " ";
      }

      return oss.str();

  }


  set<int>
  get_known_signatures_lengths()
  {
      signature_set sig_set = get_known_signatures();

      set<int> sig_lengths;

      for (const Signature & sig: sig_set)
      {
            sig_lengths.insert(sig.sig.size());
      }

      return sig_lengths;

  }

}
