.. _flyweight-cache-component:

Flyweight Cache
---------------

.. default-domain:: cpp

.. |object| replace:: :class:`object <object\<T, KeyExtractor, Allocator, Tag>>`
.. |cache| replace:: :class:`cache <cache\<T, KeyExtractor, Allocator, Tag>>`

The |cache| component of MNMLSTC Flyweight is the backing store used by
|object|. While it is *technically* an internal component, it is provided
in the case that a user would prefer to implement a more custom flyweight-like
type. Please note that the *internals* for |cache| are not discussed.

.. namespace:: flyweight

.. class:: cache<T, KeyExtractor, Allocator, Tag>

   |cache| takes the same 4 types as |object|. This is because they are
   forwarded from |object| to |cache|. A cache is *not* copyable *nor* is it
   moveable.

   A |cache| uses an hash map as its backing store. This is to make searching
   for existing values easier. Although it returns a ``shared_ptr`` to a given
   value, it only stores ``weak_ptr``. Now in the case of a type where the
   :type:`extractor_type` returns the type itself, the ``shared_ptr`` created
   will in fact simply reference the key in the hash map. The deleter function
   of the ``shared_ptr`` will simply erase the object from the hash map itself.
   This saves an unnecessary allocation (such as for strings, where they are
   the key and the object itself).

   .. type:: extractor_type

      The *KeyExtractor* template parameter. This is used to determine the
      :type:`key_type` used within the internal hash map. If the
      :type:`key_type` is the same type as *T*, special optimizations are taken
      to avoid unnecessary memory allocations.

   .. type:: allocator_type

      The correctly rebound allocator based off of *Allocator*.

   .. type:: key_type

      The type used to search for the correct underlying ``weak_ptr``.

   .. type:: tag_type

      Used to provide different |cache| instantiations.

   .. type:: difference_type

      ``std::ptrdiff_t``

   .. type:: value_type

      ``std::pair<key_type, std::weak_ptr<T const>``

   .. type:: size_type

      ``std::size_t``

   .. type:: const_iterator
             iterator

      The underlying hash map's iterator type

   .. type:: const_reference
             reference

      An lvalue reference of :type:`value_type`

   .. type:: const_pointer
             pointer

      A pointer version of :type:`value_type`.

   .. function:: cache& ref () noexcept

      Access to a mutable reference of |cache|. The reference is to a static
      local instance. This means a |cache| is not created until it is first
      accessed. This function is a static member function.

   .. function:: const_iterator begin () const noexcept

      :returns: :type:`const_iterator` to the beginning of the internal hash
                map

   .. function:: const_iterator end () const noexcept

      :returns: :type`const_iterator` past the end of the internal hash map.

   .. function:: size_type size () const noexcept

      :returns: Number of elements stored within the |cache|.

   .. function:: bool empty () const noexcept

      :returns: Whether :func:`size` returns 0

   .. function:: std::shared_ptr<T const> find (ValueType&& value) noexcept

      The meat and potatoes of |cache|. Give a *ValueType*, it will extract a
      :type:`key_type` from *value*. This is then used to search the internal
      hash map. If the search is successful, the stored ``weak_ptr`` is used to
      lock an instance. If no value is found, *value* is inserted into the
      underlying hash map, and the resulting ``shared_ptr`` is then returned.
