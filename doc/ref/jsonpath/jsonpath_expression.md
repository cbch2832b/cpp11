### jsoncons::jsonpath::jsonpath_expression

```c++
#include <jsoncons_ext/jsonpath/jsonpath.hpp>

template <class Json,class JsonReference>
class jsonpath_expression
```

#### Member functions

    Json evaluate(reference instance, result_flags flags = result_flags::value); 

#### Parameters

<table>
  <tr>
    <td>instance</td>
    <td>Json value</td> 
  </tr>
  <tr>
    <td>result_flags</td>
    <td>Result options, a bitmask of type <a href="result_flags.md">result_flags</></td> 
  </tr>
</table>

#### Static functions

    template <class Source>
    static jsonpath_expression compile(const Source& expr);    (1)

    static jsonpath_expression compile(const char_type* expr); (2)

    template <class Source>
    static jsonpath_expression compile(const Source& expr,
                                       std::error_code& ec);   (3)

    static jsonpath_expression compile(const char_type* expr,
                                       std::error_code& ec);   (4)

Compiles the JSONPath expression for later evaluation. Returns a `jsonpath_expression` object 
that represents the JSONPath expression.
In (1) and (3), the JSONPath expression `expr` is provided as a sequential container 
or view of characters, such as a `std::basic_string` or `std::basic_string_view`.
In (2) and (4), the JSONPath expression `expr` is provided as a null terminated string.

#### Parameters

<table>
  <tr>
    <td>expr</td>
    <td>JSONPath expression</td> 
  </tr>
  <tr>
    <td>ec</td>
    <td>out-parameter for reporting errors in the non-throwing overload</td> 
  </tr>
</table>

#### Exceptions

(1) Throws a [jsonpath_error](jsonpath_error.md) if JSONPath compilation fails.

(2) Sets the out-parameter `ec` to the [jsonpath_error_category](jsonpath_errc.md) if JSONPath compilation fails. 
