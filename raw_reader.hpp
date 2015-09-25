#ifndef RAW_READER_HPP
#define RAW_READER_HPP
#include <string>
#include <vector>
/**
 *A structure holding the contents of a <i>single</i> line of a raw file(itt between the square brackets)
 */
struct RawTag{
  RawTag(){}
  /**
   *The name of the tag.
   */
  std::string tagname;
  /**
   *The values of the tag, I.E. not the name of the tag.
   */
  std::vector<std::string> tagvalues;
};
class RawReader{
public:
  static std::vector<RawTag> ReadFile(const std::string& file);
};
#endif
