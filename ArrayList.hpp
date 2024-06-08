/// @author - Brandon Wallace
/// @file - ArrayList.hpp
/// @brief - The ArrayList is a container that encapsulates dynamic arrays.
/// ArrayList storage is handled automatically, being expanded as needed.

#ifndef ArrayList_hpp
#define ArrayList_hpp

/// C++ Standard Library Header Files
#include <algorithm>
#include <iostream>
#include <initializer_list>
#include <iterator>
#include <exception>
#include <vector>

namespace AL {

template <class T> class ArrayList {
    public:
        struct Iterator {
        public:
            // Iterator Type Aliases
            using iterator_category = std::bidirectional_iterator_tag;
            using difference_type   = std::ptrdiff_t;
            using value_type        = T;
            using reference         = value_type&;
            using pointer           = value_type*;
            
            /// ------------------------------------------------------------------
            /// @function Iterator   </! Iterator Default Constructor !/>
            /// @param    ptr         initializes pointer to nullptr
            /// @note     Initializes instance variables.
            /// ------------------------------------------------------------------
            Iterator(pointer ptr = nullptr) : m_ptr(ptr) {}
            
            /// ------------------------------------------------------------------
            /// @function Iterator   </! Copy Constructor !/>
            /// @param    other    A copy of the other iterator
            /// @note     Makes a shallow copy.
            /// ------------------------------------------------------------------
            
            Iterator(const Iterator& other) : m_ptr(other.m_ptr) {}
            
            /// ------------------------------------------------------------------
            /// @function operator*  </! Dereference Operator !/>
            ///
            /// @return   Returns a reference to the object pointed to by m_ptr.
            /// ------------------------------------------------------------------
            
            reference operator*() const { return *m_ptr; }
            
            /// ------------------------------------------------------------------
            /// @function operator*  </! Member Access Operator !/>
            ///
            /// @return   Returns a pointer to the object.
            /// -----------------------------------------------------------------
            pointer operator->() { return m_ptr; }
            
            /// ------------------------------------------------------------------
            /// @function operator++  </! Increment Operator !/>
            ///
            /// @return Returns incremented reference to the 'Iterator' object.
            /// ------------------------------------------------------------------
            
            Iterator& operator++() { ++m_ptr; return *this; }
            
            /// ------------------------------------------------------------------
            /// @function operator--  </! Decrement Operator !/>
            ///
            /// @return Returns decremented reference to the 'Iterator' object.
            /// ------------------------------------------------------------------

            Iterator& operator--() { --m_ptr; return *this; }
            
            /// ------------------------------------------------------------------
            /// @function operator<  </! Less Than Rational Operator !/>
            ///
            /// @return True if m_ptr is less than other m_ptr, else false
            /// ------------------------------------------------------------------
            
            bool operator<(const Iterator& other) { return m_ptr < other.m_ptr; }
            
            /// ------------------------------------------------------------------
            /// @function operator>  </! Greater Than Rational Operator !/>
            ///
            /// @return True if m_ptr is greater than other m_ptr, else false
            /// ------------------------------------------------------------------
            
            bool operator>(const Iterator& other) { return m_ptr > other.m_ptr; }

            /// ------------------------------------------------------------------
            /// @function operator==    </! Equality Comparison Operator !/>
            /// @param    lhs        -Left-hand side dynamic array
            /// @param    rhs        -Right-hand side dynamic array
            /// @return   True if lhs 'does' compare equal to rhs, else false.
            /// ------------------------------------------------------------------
        
            friend bool operator==(const Iterator& lhs, const Iterator& rhs) { return lhs.m_ptr == rhs.m_ptr; }
            
            /// ------------------------------------------------------------------
            /// @function operator!=    </! Inequality Comparison Operator !/>
            /// @param    lhs        -Left-hand side dynamic array
            /// @param    rhs        -Right-hand side dynamic array
            /// @return   True if lhs is 'not' equal to rhs, else false.
            /// ------------------------------------------------------------------
            
            friend bool operator!=(const Iterator& lhs, const Iterator& rhs) { return lhs.m_ptr != rhs.m_ptr; }
            
            /// ------------------------------------------------------------------
            
        private:
            pointer m_ptr{}; ///< Iterator pointer
        };  // Iterator class
    
    // type aliases
    using value_type      = T;
    using size_type       = std::size_t;
    using reference       = value_type&;
    using const_reference = const value_type&;
    using pointer         = value_type*;
    using const_pointer   = const value_type*;
    using iterator        = Iterator;
    using const_iterator  = const iterator;
    
    size_type vector_size = 0;
    
    /// ----------------------------------------------------------------------
    /// @function ArrayList </! Default Constructor !/>
    /// @param count    initializes the count to 0
    /// @note Default constructor. Constructs an ArrayList with count copies of
    /// the default value of value_type, e.g., the default value for an
    /// int is 0.
    /// ----------------------------------------------------------------------
    
    ArrayList(size_type count = 0)
    : m_capacity(count), m_size(count), m_data(new value_type[count]{}) {}
    
    /// ----------------------------------------------------------------------
    /// @function ArrayList
    /// @param    source   Holds initializer list of elements
    /// @note     Constructs a container with a copy of the source elements.
    /// ----------------------------------------------------------------------
    ArrayList(const std::initializer_list<value_type>& source);
    
    /// ----------------------------------------------------------------------
    /// @function ArrayList  </! Copy Constructor !/>
    /// @param    other    holds a reference to other ArrayList
    /// @note     Makes a deep copy of another ArrayList.
    /// ----------------------------------------------------------------------
    
    ArrayList(const ArrayList& other);
    
    /// ----------------------------------------------------------------------
    /// @function ArrayList  </! Move Constructor !/>
    /// @param    other     holds the state of another object being moved
    /// @note Creates container with source contents using move semantics.
    /// ----------------------------------------------------------------------
    
    ArrayList(ArrayList&& other)
    : m_capacity(std::exchange(other.m_capacity, 0)),
      m_size(std::exchange(other.m_size, 0)),
      m_data(std::exchange(other.m_data, nullptr)) {}
    
    /// ----------------------------------------------------------------------
    /// @function ~ArrayList  </! Deconstructor !/>
    ///
    /// @note Releases any resources the object aquired over its lifetime.
    /// ----------------------------------------------------------------------
    virtual ~ArrayList() { delete[] m_data; }
    
    /// ----------------------------------------------------------------------
    /// @function at
    /// @param    pos     Zero-based index of the element to access
    /// @return   Returns a reference to an element at the specified position.
    /// ----------------------------------------------------------------------
    
    reference at(size_type pos);
    const_reference at(size_type pos) const;
    
    /// ----------------------------------------------------------------------
    /// @function front
    ///
    /// @return Returns a reference to the first element in the container.
    /// ----------------------------------------------------------------------
    
    reference front();
    const_reference front() const;
    
    /// ----------------------------------------------------------------------
    /// @function back
    ///
    /// @return Returns a reference to the last element in the container.
    /// ----------------------------------------------------------------------
    
    reference back() { return *(begin() + size() - 1); }
    const_reference back() const { return *(begin() + size() - 1); }
    
    /// ----------------------------------------------------------------------
    /// @function begin
    ///
    /// @return Returns an iterator to the beginning of the container.
    /// ----------------------------------------------------------------------
    
    iterator begin() { return iterator(m_data); };
    const_iterator begin() const { return iterator (m_data); };
    
    /// ----------------------------------------------------------------------
    /// @function end
    ///
    /// @return Returns an iterator to the end of the container.
    /// ----------------------------------------------------------------------

    iterator end() { return iterator(m_data + m_size); };
    const_iterator end() const { return iterator(m_data + m_size); };
    
    /// ----------------------------------------------------------------------
    /// @function empty
    ///
    /// @return Returns 'True' if the size of the container is 0, empty.
    /// ----------------------------------------------------------------------
    
    bool empty() const { return size() == 0; }
    
    /// ----------------------------------------------------------------------
    /// @function size
    ///
    /// @return Returns the number of elements in the container.
    /// ----------------------------------------------------------------------
    
    size_type size() const { return m_size; }
    
    /// ----------------------------------------------------------------------
    /// @function capacity
    ///
    /// @return Returns the capacity of the container, which is the maximum
    /// number of elements the container can hold without needing reallocation.
    /// ----------------------------------------------------------------------
    
    size_type capacity() const { return m_capacity; }
    
    /// ----------------------------------------------------------------------
    /// @function clear
    ///
    /// @note Resets the size of the container to 0, clearing the container.
    /// Doesn't deallocate memory or destroy the elements, just marks the
    /// container as empty by setting its size to zero.
    /// ----------------------------------------------------------------------
    
    void clear() { m_size = 0; }
    
    /// ----------------------------------------------------------------------
    /// @function push_back
    ///
    /// @param    value    holds the 'value' to append
    /// @note Appends the given element value to the end of the container.
    /// If the new size() is greater than capacity(), reallocation occurs.
    /// ----------------------------------------------------------------------
    
    void push_back(const value_type& value);
    
    /// ----------------------------------------------------------------------
    /// @function insert
    /// @param    pos        holds the position to be inserted to
    /// @param    value    holds the new element to be inserted
    /// @return   Returns an iterator pointing to the newly inserted element.
    /// @note     Inserts the new element 'value', at the iterator 'pos'.
    /// ----------------------------------------------------------------------
    
    iterator insert(iterator pos, const value_type& value);
    
    /// ----------------------------------------------------------------------
    /// @function erase
    /// @param    pos  holds the position to be erased
    /// @return   Returns an iterator pointing to the element immediately
    ///           following the erased element.
    /// @note Removes the element at the position indicated by the iterator.
    /// ----------------------------------------------------------------------
    
    iterator erase(iterator pos);
    
    /// ----------------------------------------------------------------------
    /// @function resize
    /// @param    count    holds the new size of the desired container
    /// @note Resizes the container to the specified 'count'. If the current
    /// size is greater than 'count', the container is reduced to its first
    /// 'count' elements. If the current size is less than count, additional
    /// default-constructed elements are appended.
    /// ----------------------------------------------------------------------
    
    void resize(size_type count);
    
    /// ----------------------------------------------------------------------
    /// @function swap
    /// @param    other   holds a reference to other contianer
    /// @note Exchanges the contents of the container with those of another,
    /// without copying any elements.
    /// ----------------------------------------------------------------------
    
    void swap(ArrayList& other);
    
    /// ----------------------------------------------------------------------
    /// @function operator=  </Move Assignment Operator/>
    /// @param    other     holds contents of source container
    /// @return   Transfers assets from source object to target object using move semantics
    /// @return *this
    /// ----------------------------------------------------------------------
    
    ArrayList& operator=(ArrayList&& other);
    
    /// ----------------------------------------------------------------------
    /// @function operator=   </Copy Assignment Operator/>
    /// @param     rhs          holds contents of other container
    /// @return  Replaces the contents of the container
    ///          with a copy of the contents of rhs
    /// @return *this
    /// ----------------------------------------------------------------------
    
    ArrayList& operator=(const ArrayList& rhs);
    
    /// ----------------------------------------------------------------------
    /// @function operator+=
    /// @param other    holds other contents to be appended
    /// @return Appends the contents of other to the contianer.
    /// ----------------------------------------------------------------------
    
    ArrayList& operator+=(const ArrayList& other);
    
    /// ----------------------------------------------------------------------
    /// @function operator[]
    /// @param    index  holds the position of the element you want to access
    /// @return   Returns a reference as an array element
    /// ----------------------------------------------------------------------
    reference operator[](size_type index);
    const_reference operator[](size_type index) const;
    
protected:
    size_type m_capacity;  ///< The number of elements that can be stored.
    size_type m_size;      ///< The number of elements in use.
    pointer   m_data;      ///< Dynamically-allocated array custodian.
};  // ArrayList class

//! *********************** Operator Overloads *********************** !//

/// ----------------------------------------------------------------------
/// @function operator==    </! Equality Comparison Operator !/>
/// @param    lhs        -Left-hand side dynamic array
/// @param    rhs        -Right-hand side dynamic array
/// @return   Returns true if lhs 'does' compare equal to rhs, else false.
/// ----------------------------------------------------------------------

template <class T>
bool operator==(const ArrayList<T>& lhs, const ArrayList<T>& rhs);

/// ----------------------------------------------------------------------
/// @function operator!=    </! Inequality Comparison Operator !/>
/// @param    lhs        -Left-hand side dynamic array
/// @param    rhs        -Right-hand side dynamic array
/// @return   Returns true if lhs is not equal to rhs, else false.
/// ----------------------------------------------------------------------

template <class T>
bool operator!=(const ArrayList<T>& lhs, const ArrayList<T>& rhs);

/// ----------------------------------------------------------------------
/// @function operator+   </! Concatenation Operator !/>
/// @param    lhs    -Left-hand side dynamic array
/// @param    rhs    -Right-hand side dynamic array
/// @return   Returns the concatenated elements of lhs and rhs.
/// ----------------------------------------------------------------------

template <class T>
ArrayList<T> operator+(const ArrayList<T>& lhs, const ArrayList<T>& rhs);

/// ----------------------------------------------------------------------
/// @function operator<<  </! Stream Insertion Operator !/>
/// @param    output      Output stream where data is sent
/// @param    list        Object of the class
/// @return   Allows objects to be formatted and sent to output streams.
/// ----------------------------------------------------------------------

template <class T>
std::ostream& operator<<(std::ostream& output, const ArrayList<T>& list);

// =======================================================================
//                      D E F I N I T I O N S
// =======================================================================

/// ----------------------------------------------------------------------
/// @function operator[]
/// @param    index  holds the position of the element you want to access
/// @return   Returns a reference as an array element
/// ----------------------------------------------------------------------

template <class T>
typename ArrayList<T>::reference ArrayList<T>::operator[](size_type index)
{
    return *(m_data + index);
}

template <class T>
typename ArrayList<T>::const_reference ArrayList<T>::operator[](size_type index) const
{
    return *(m_data + index);
}

/// ----------------------------------------------------------------------
/// @function ArrayList  </! Copy Constructor !/>
/// @param    other    holds a reference to other ArrayList
/// @note     Makes a deep copy of another ArrayList.
/// ----------------------------------------------------------------------

template <class T>
ArrayList<T>::ArrayList(const ArrayList& other)
: ArrayList(other.size())
{
    std::copy(other.begin(), other.end(), begin());
}

/// ----------------------------------------------------------------------
/// @function ArrayList
/// @param    source   Holds initializer list of elements
/// @note     Constructs a container with a copy of the source elements.
/// ----------------------------------------------------------------------

template <class T>
ArrayList<T>::ArrayList(const std::initializer_list<T>& source)
: ArrayList(source.size())
{
    std::(source.begin(), source.end(), begin());
}

/// ----------------------------------------------------------------------
/// @function front
///
/// @return Returns a reference to the first element in the container.
/// ----------------------------------------------------------------------

template <class T>
typename ArrayList<T>::reference ArrayList<T>::front() {
    if (size() == 0)
    {
        throw std::out_of_range{ "Accessed position is out of range!" };
    }
    return *begin();
    
}
template <class T>
typename ArrayList<T>::const_reference ArrayList<T>::front() const
{
    if (size() == 0)
    {
        throw std::out_of_range{ "Accessed position is out of range!" };
    }
    return *begin();
}

/// ----------------------------------------------------------------------
/// @function at
/// @param    pos     Zero-based index of the element to access
/// @return   Returns a reference to an element at the specified position.
/// ----------------------------------------------------------------------

template <class T>
typename ArrayList<T>::reference ArrayList<T>::at(size_type pos)
{
    if (pos > size() || pos == size())
    {
        throw std::out_of_range{ "Accessed position is out of range!" };
    }
    
    return *(m_data + pos);
}

template <class T>
typename ArrayList<T>::const_reference ArrayList<T>::at(size_type pos) const
{
    if (pos > size() || pos == size())
    {
        throw std::out_of_range{ "Accessed position is out of range!" };
    }
    
    return *(m_data + pos);
}

/// ----------------------------------------------------------------------
/// @function push_back
///
/// @param    value    holds the 'value' to append
/// @note Appends the given element value to the end of the container.
/// If the new size() is greater than capacity(), reallocation occurs.
/// ----------------------------------------------------------------------
    
template <class T>
void ArrayList<T>::push_back(const value_type& value)
{
    // checks if arraylist size has reached capacity
    if (size() == capacity())
    {
        // temporary array
        pointer temp{};
        
        // compute new capacity
        m_capacity  = capacity() == 0 ? 1 : m_capacity * 2;
        temp        = new value_type[m_capacity]{};     // allocate temp array
        
        // copies over elements to tmp array
        std::copy(begin(), end(), temp);
        
        // reallocate memory
        delete [] m_data;
        
        // sets m_data to new arraylist
        m_data = temp;
    }
    // appends value to array list
    *(m_data + m_size++) = value;
}

/// ----------------------------------------------------------------------
/// @function insert
/// @param    pos        holds the position to be inserted to
/// @param    value    holds the new element to be inserted
/// @return   Returns an iterator pointing to the newly inserted element.
/// @note     Inserts the new element 'value', at the iterator 'pos'.
/// ----------------------------------------------------------------------

template <class T>
typename ArrayList<T>::iterator
ArrayList<T>::insert(iterator pos, const value_type& value)
{
    iterator z = end();
    
    if (pos < iterator(m_data))
    {
        throw std::out_of_range{ "Accessed position is out of range!" };
    }
    
    if (pos > iterator(m_data + m_size))
    {
        throw std::out_of_range{ "Accessed position is out of range!" };
    }
    
    // reallocate if necessary
    if (size() == capacity()) {
        const auto offset   = std::distance(begin(), pos); // index of pos
        auto new_capacity   = capacity() == 0 ? 1 : capacity() * 2;
        auto temp           = new value_type[new_capacity]{};   // temp array
        
        std::copy(begin(), end(), temp);
        
        delete [] m_data;
        m_data = temp;
        m_capacity = new_capacity;
        pos = iterator(m_data + offset); // reacquire pos
    }
    
    std::copy_backward(pos, z, ++z);
    
    // insert new value and update size
    *pos = value;
    ++m_size;
    
    return pos;
}

/// ----------------------------------------------------------------------
/// @function erase
/// @param    pos  holds the position to be erased
/// @return   Returns an iterator pointing to the element immediately
///           following the erased element.
/// @note Removes the element at the position indicated by the iterator.
/// ----------------------------------------------------------------------

template <class T>
typename ArrayList<T>::iterator ArrayList<T>::erase(iterator pos)
{
    if (pos < iterator(m_data) || pos == iterator(m_data))
    {
        throw std::out_of_range{ "Accessed position is out of range!" };
    }
    
    if (pos > iterator(m_data + m_size))
    {
        throw std::out_of_range{ "Accessed position is out of range!" };
    }
    
    // shuffle elements right of pos to the left
    std::copy(pos + 1, end(), pos);
    
    --m_size;
    
    return pos;
}

/// ----------------------------------------------------------------------
/// @function resize
/// @param    count    holds the new size of the desired container
/// @note Resizes the container to the specified 'count'. If the current
/// size is greater than 'count', the container is reduced to its first
/// 'count' elements. If the current size is less than count, additional
/// default-constructed elements are appended.
/// ----------------------------------------------------------------------

template <class T>
void ArrayList<T>::resize(size_type count)
{
    // checks if new size is != current size
    if (size() != count)
    {
        // allocate and zero a new array
        const pointer temp = new value_type[count] {};
        
        // determine the upper limit of elements to copy
        //const pointer limit = count < size() ? begin() + count : end();
        const pointer limit = count < size() ? m_data + count : m_data + m_size;
        
        std::copy(m_data, limit, temp);
        
        delete [] m_data;
        m_data = temp;
        m_capacity = m_size = count;
    }
}

/// ----------------------------------------------------------------------
/// @function swap
/// @param    other   holds a reference to other contianer
/// @note Exchanges the contents of the container with those of another,
/// without copying any elements.
/// ----------------------------------------------------------------------

template <class T>
void ArrayList<T>::swap(ArrayList& other)
{
    // swap contents
    std::swap(m_capacity, other.m_capacity);
    std::swap(m_size,     other.m_size);
    std::swap(m_data,     other.m_data);

}

/// ----------------------------------------------------------------------
/// @function operator=   </Copy Assignment Operator/>
/// @param    rhs          holds contents of other container
/// @return  Replaces the contents of the container
///          with a copy of the contents of rhs
/// @return *this
/// ----------------------------------------------------------------------

template <class T>
ArrayList<T>& ArrayList<T>::operator=(const ArrayList& rhs)
{
    if (this != &rhs) {                         // checks for self-assignment
        if(capacity() != rhs.capacity()) {
            delete[] m_data;                    // deallocates memory
            
            m_data = nullptr;                   // set m_data to nullptr
            
            m_capacity = m_size = 0;            // ensures that there is memory
            
            m_data = new value_type[rhs.capacity()]{};   // allocate new memory
            
            m_capacity = rhs.capacity();  // set m_capacity to the rhs capacity
        }
        // replace container with rhs elements
        std::copy(rhs.begin(), rhs.end(), begin());
        
        // set m_size to the rhs size
        m_size = rhs.size();
    }
    // return the reference
    return *this;
}

/// ----------------------------------------------------------------------
/// @function operator=  </Move Assignment Operator/>
/// @param    other      holds contents of source container
/// @return   Transfers assets from source object to target object using
///           move semantics.
/// ----------------------------------------------------------------------

template <class T>
ArrayList<T>& ArrayList<T>::operator=(ArrayList&& other)
{
    if (this != &other) { //< checks for self-assignment
      
        m_capacity = std::exchange(other.m_capacity, 0);
        m_size = std::exchange(other.m_size, 0);
        m_data = std::exchange(other.m_data, nullptr);
      
    }
  
    return *this;
}

/// ----------------------------------------------------------------------
/// @function operator+=
/// @param other    holds other contents to be appended
/// @return Appends the contents of other to the contianer.
/// ----------------------------------------------------------------------

template <class T>
ArrayList<T>& ArrayList<T>::operator+=(const ArrayList& other)
{
    // new minimum capacity
    size_type reqd_size = size() + other.size();
    
    // checks to see if the container's capacity
    // has enough space for the new elements
    if (capacity() < reqd_size) {
        pointer temp = new value_type[reqd_size];
        std::copy(begin(), end(), temp);
        
        delete [] m_data;
        m_data = temp;
        m_capacity = reqd_size;
    }
    // creates a temporary dynamic array append other array to the end
    // of lhs dynamic array
    std::copy(other.begin(), other.end(), begin() + size());
    
    // set m_used to the number of elements within the array
    m_size += other.m_size;

    // return the value
    return *this;
}

/// ----------------------------------------------------------------------
/// @function operator==  </! Equality Comparison Operator !/>
/// @param    lhs         -Left-hand side dynamic array
/// @param    rhs         -Right-hand side dynamic array
/// @return   Returns true if lhs 'does' compare equal to rhs, else false.
/// ----------------------------------------------------------------------

template <class T>
bool operator==(const ArrayList<T>& lhs, const ArrayList<T>& rhs)
{
    return std::equal(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}

/// ----------------------------------------------------------------------
/// @function operator!=    </! Inequality Comparison Operator !/>
/// @param    lhs        -Left-hand side dynamic array
/// @param    rhs        -Right-hand side dynamic array
/// @return   Returns true if lhs is not equal to rhs, else false.
/// ----------------------------------------------------------------------

template <class T>
bool operator!=(const ArrayList<T>& lhs, const ArrayList<T>& rhs)
{
    return !(lhs == rhs);
}

/// ----------------------------------------------------------------------
/// @function operator+   </! Concatenation Operator !/>
/// @param    lhs    -Left-hand side dynamic array
/// @param    rhs    -Right-hand side dynamic array
/// @return   Returns the concatenated elements of lhs and rhs.
/// ----------------------------------------------------------------------

template <class T>
ArrayList<T> operator+(const ArrayList<T>& lhs, const ArrayList<T>& rhs)
{
    return ArrayList<T>(lhs) += rhs;
}

/// ----------------------------------------------------------------------
/// @function operator<<  </! Stream Insertion Operator !/>
/// @param    output      Output stream where data is sent
/// @param    list        Object of the class
/// @return   Allows objects to be formatted and sent to output streams.
/// ----------------------------------------------------------------------
template <class T>
std::ostream& operator<<(std::ostream& output, const ArrayList<T>& list)
{
    char separator[2]{};
    
    output << '{';
    
    for (auto item : list) {
        output << separator << item;
        *separator = ',';
    }
    
    return output << '}';
}

// ----------------------------------------------------------------------

} // namespace AL

#endif /* ArrayList_hpp */

/* EOF */

