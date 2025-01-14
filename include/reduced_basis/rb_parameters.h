// rbOOmit: An implementation of the Certified Reduced Basis method.
// Copyright (C) 2009, 2010 David J. Knezevic

// This file is part of rbOOmit.

// rbOOmit is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or (at your option) any later version.

// rbOOmit is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Lesser General Public License for more details.

// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

#ifndef LIBMESH_RB_PARAMETERS_H
#define LIBMESH_RB_PARAMETERS_H

// libMesh includes
#include "libmesh/libmesh_common.h"

// C++ includes
#include <string>
#include <map>
#include <set>

namespace libMesh
{

/**
 * This class is part of the rbOOmit framework.
 *
 * This class defines a set of parameters index by strings.
 *
 * \author David J. Knezevic
 * \date 2012
 */
class RBParameters
{
public:

  /**
   * The special functions can be defaulted for this class, as it
   * does not manage any memory itself.
   */
  RBParameters () = default;
  RBParameters (RBParameters &&) = default;
  RBParameters (const RBParameters &) = default;
  RBParameters & operator= (const RBParameters &) = default;
  RBParameters & operator= (RBParameters &&) = default;
  ~RBParameters() = default;

  /**
   * Constructor. Set parameters based on the std::map \p parameter_map.
   *
   * This constructor will still be supported once we switch over to
   * the vector-based storage for RBParameters objects. It will just set
   * the 0th entry of the vector corresponding to each parameter name.
   */
  RBParameters(const std::map<std::string, Real> & parameter_map);

  // Define a constant iterator for this class
  typedef std::map<std::string, Real>::const_iterator const_iterator;

  /**
   * Clear this object.
   */
  void clear();

  /**
   * Get a const reference to the map that stores all of the values.
   *
   * This interface is \deprecated and will be removed soon. To iterate over
   * the parameters map, you should instead use the begin/end APIs provided
   * by this class.
   */
  const std::map<std::string, Real> & get_parameters_map() const;

  /**
   * Get a const reference to the map that stores all of the "extra" values.
   *
   * This interface is \deprecated and will be removed soon. To iterate over
   * the parameters map, you should instead use the begin/end APIs provided
   * by this class.
   */
  const std::map<std::string, Real> & get_extra_parameters_map() const;

  /**
   * \returns true if there is a parameter named "param_name" present
   * in this class, false otherwise.
   */
  bool has_value(const std::string & param_name) const;

  /**
   * \returns true if there is an extra parameter named "param_name" present
   * in this class, false otherwise.
   */
  bool has_extra_value(const std::string & param_name) const;

  /**
   * Get the value of the specified parameter, throwing an error if it
   * does not exist.
   */
  Real get_value(const std::string & param_name) const;

  /**
   * Get the value of the specified parameter, returning the provided
   * default value if it does not exist.
   */
  Real get_value(const std::string & param_name, const Real & default_val) const;

  /**
   * Set the value of the specified parameter. If param_name
   * doesn't already exist, it is added to the RBParameters object.
   */
  void set_value(const std::string & param_name, Real value);

  /**
   * Get the value of the specified extra parameter, throwing an error
   * if it does not exist.
   */
  Real get_extra_value(const std::string & param_name) const;

  /**
   * Get the value of the specified extra parameter, returning the
   * provided default value if it does not exist.
   */
  Real get_extra_value(const std::string & param_name, const Real & default_val) const;

  /**
   * Set the value of the specified extra parameter. If param_name
   * doesn't already exist, it is added to the extra parameters.
   */
  void set_extra_value(const std::string & param_name, Real value);

  /**
   * Get the number of parameters that have been added.
   */
  unsigned int n_parameters() const;

  /**
   * Fill \p param_names with the names of the parameters.
   *
   * \deprecated to avoid making it too easy to create copies that in
   * most circumstances aren't needed.  If this functionality really
   * is required, call get_parameters_map() and loop over the keys
   * directly.
   */
  void get_parameter_names(std::set<std::string> & param_names) const;

  /**
   * Fill \p param_names with the names of the extra parameters.
   *
   * \deprecated to avoid making it too easy to create copies that in
   * most circumstances aren't needed.  If this functionality really
   * is required, call get_parameters_map() and loop over the keys
   * directly.
   */
  void get_extra_parameter_names(std::set<std::string> & param_names) const;

  /**
   * Erase \p param_name  from _parameters. If \p param_name is not present
   * in _parameters, then do nothing.
   */
  void erase_parameter(const std::string & param_name);

  /**
   * Erase \p param_name  from _extra_parameters. If \p param_name is not present
   * in _extra_parameters, then do nothing.
   */
  void erase_extra_parameter(const std::string & param_name);

  /**
   * Get const_iterator access to the parameters stored in this RBParameters object.
   */
  const_iterator begin() const;
  const_iterator end() const;

  /**
   * Get const_iterator access to the extra parameters stored in this RBParameters object.
   */
  const_iterator extra_begin() const;
  const_iterator extra_end() const;

  /**
   * Two RBParameters are equal if they have the same _parameters map.
   */
  bool operator== (const RBParameters & rhs) const;

  /**
   * \returns !(*this == rhs).
   */
  bool operator!= (const RBParameters & node) const;

  /**
   * Get a string that specifies the contents of this RBParameters object.
   * \p precision specifies the number of digits of precision we use
   * in scientific notation in the string.
   */
  std::string get_string(unsigned int precision=6) const;

  /**
   * Print the parameters.
   */
  void print() const;

private:

  /**
   * The map that stores the actual parameters, indexed by names.
   */
  std::map<std::string, Real> _parameters;

  /**
   * The map that stores extra parameters not used for RB training, indexed by names.
   */
  std::map<std::string, Real> _extra_parameters;

};

} // namespace libMesh


#endif // LIBMESH_RB_PARAMETERS_H
