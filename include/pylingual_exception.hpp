#include <exception>
class pylingual_exception : public std::exception
{
public:
  virtual const char* what() const noexcept { return "standard pylingual exception"; };
};

class pylingual_unregistered : public pylingual_exception
{
public:
  virtual const char* what() const noexcept { return "Module/Function has not been imported"; };
};
