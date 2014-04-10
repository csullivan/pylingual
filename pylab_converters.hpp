using namespace boost::python;
using namespace std;


template<typename T>
struct Vector_to_python_list
{
   
  static PyObject* convert(std::vector<T> const& v)
  {
    using namespace std;
    using namespace boost::python;
    using boost::python::list;
    list l;
    typename vector<T>::const_iterator p;
    for(p=v.begin();p!=v.end();++p){
      l.append(object(*p));
    }
    return incref(l.ptr());
  }
};
 
template<typename T>
struct Vector_from_python_list
{

    Vector_from_python_list()
    {
      using namespace boost::python;
      using namespace boost::python::converter;
      registry::push_back(&Vector_from_python_list<T>::convertible,
			  &Vector_from_python_list<T>::construct,
			  type_id<std::vector<T> >());
    }
 
    // Determine if obj_ptr can be converted in a std::vector<T>
    static void* convertible(PyObject* obj_ptr)
    {
      if (!PyList_Check(obj_ptr)){
	return 0;
      }
      return obj_ptr;
    }
 
    // Convert obj_ptr into a std::vector<T>
    static void construct(
    PyObject* obj_ptr,
    boost::python::converter::rvalue_from_python_stage1_data* data)
    {
      using namespace boost::python;
      // Extract the character data from the python string
      //      const char* value = PyString_AsString(obj_ptr);
      list l(handle<>(borrowed(obj_ptr)));

      // // Verify that obj_ptr is a string (should be ensured by convertible())
      // assert(value);
 
      // Grab pointer to memory into which to construct the new std::vector<T>
      void* storage = (
        (boost::python::converter::rvalue_from_python_storage<std::vector<T> >*)
        data)->storage.bytes;
 
      // in-place construct the new std::vector<T> using the character data
      // extraced from the python object
      std::vector<T>& v = *(new (storage) std::vector<T>());
 
      // populate the vector from list contains !!!
      int le = len(l);
      v.resize(le);
      for(int i = 0;i!=le;++i){
	v[i] = extract<T>(l[i]);
      }

      // Stash the memory chunk pointer for later use by boost.python
      data->convertible = storage;
    }
};
 
void initializeConverters()
{
}

void
print(std::vector<double>v)
{
  using namespace std;
  copy(v.begin(),v.end(),
       ostream_iterator<double>(cout," "));
  cout << endl;
}

BOOST_PYTHON_MODULE(std)
{
  using namespace boost::python;
  using namespace boost::python;

  // register the to-python converter
  to_python_converter<
    std::vector<double>,
    Vector_to_python_list<double> >();
 
  // register the from-python converter
    Vector_from_python_list<double>();

  def("display",print);
}


