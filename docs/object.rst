.. _flyweight-object-component:

Flyweight Object
----------------

.. default-domain:: cpp

.. |object| replace:: :class:`object <object\<T, KeyExtractor, Allocator, Tag>>`
.. |cache| replace:: :class:`cache <cache\<T, KeyExtractor, Allocator, Tag>>`

The |object| component of MNMLSTC Flyweight is the most important. It is, after
all the actual *handle* to the const object.

.. namespace:: flyweight

.. class:: object<T, KeyExtractor, Allocator, Tag>

   |object| takes 4 types, however 3 of these have default values. The types
   *KeyExtractor*, *Allocator*, and *Tag* are passed through to the |cache|.
   The *Tag* type is important when wishing that certain objects be stored
   elsewhere. For instance, if a ``std::string`` were used to represent one set
   of data as well as a completely different set altogether, the *Tag* can be
   used to change where they are stored::

      using namespace flyweight;
      using person = object<std::string>;
      using city = object<
        std::string,
        extractor<std::string>,
        std::allocator<std::string>,
        tag<void> // any set of types placed inside of tag<> will do
      >;

   The ``flyweight::tag`` type takes any number of types, and is simply used
   to instantiate separate caches, and nothing more. One could technically
   pass in many different types to generate a different cache.

   .. warning:: |object| is *copy-constructible* and *copy-assignable*.
      It is *not* moveable. An |object| must *always* have a valid handle to
      an object. It can *never* be in a "valid, but null state".

   .. type:: value_type

      Represents the type that |object| acts as a handle for. It is *always*
      ``T const``.

      .. note:: *value_type* may never be a reference type. Attempting this
         will result in a ``static_assert``.

   .. type:: cache_type

      Represents the |cache| that |object| will use to retrieve a handle from.

   .. type:: key_type

      Represents the type that is extracted for lookup within the |cache|.

   .. type::reference

      Represents an lvalue reference to :type:`value_type`.

   .. type:: pointer

      Represents a pointer to :type:`value_type`.

   .. function:: object (Args&&)
                 object (ValueType&&)

      An |object| may be constructed with a value where *ValueType* is the same
      as :type:`value_type`. Additionally, it may be constructed with a
      variadic number of arguments, as long as :type:`value_type` may be
      constructed from it.

   .. function:: object ()

      Default constructing an |object| will result in a handle to a default
      constructed :type:`value_type`.

   .. function:: object& operator = (ValueType&& value)

      Will change the |object| to act as handle for *ValueType*. *ValueType*
      must be the same as :type:`value_type`. It acts as a *universal reference*

   .. function:: void swap (object& that) noexcept

      Swaps the contents of *that* with |object|.

   .. function:: pointer operator -> () const noexcept

      Allows the user to directly access the value that the |object| handles.
      This was added for convenience. |object| is not actually a wrapper for
      the :type:`value_type` that it holds onto.

   .. function:: operator reference () const noexcept

      :returns: A :type:`reference` to the value handled by |object|.

   .. function:: reference get () const noexcept

      :returns: A :type:`reference` to the value handled by |object|.

Equality and Comparisons
########################

|object| is *LessThanComparable* and *EqualityComparable*. It implements
overloads for *all* the comparison operators.

.. function:: bool operator == (object const& lhs, object const&) noexcept
              bool operator != (object const& lhs, object const&) noexcept
              bool operator <= (object const& lhs, object const&) noexcept
              bool operator >= (object const& lhs, object const&) noexcept
              bool operator > (object const& lhs, object const&) noexcept
              bool operator < (object const& lhs, object const&) noexcept

   Compares |object| by their underlying reference.
   ``std::equal_to``, ``std::not_equal_to``, ``std::greater_equal``,
   ``std::less_equal``, ``std::greater``, or ``std::less`` is used for each
   of the operations respectively.

.. function:: bool operator == (object const&, T const&) noexcept
              bool operator != (object const&, T const&) noexcept
              bool operator >= (object const&, T const&) noexcept
              bool operator <= (object const&, T const&) noexcept
              bool operator > (object const&, T const&) noexcept
              bool operator < (object const&, T const&) noexcept

   Compares |object| and a :type:`value_type` with ``std::equal_to``, 
   ``std::not_equal_to``, ``std::greater_equal``, ``std::less_equal``,
   ``std::greater``, or ``std::less`` respectively.

Specializations
###############

There are a few specializations for |object| so that it may interact with
the C++ standard library.


.. function:: std::swap (flyweight::object&, flyweight::object&)

   Allows `std::swap` to be used.

.. class:: std::hash<flyweight::object<Type, KeyExtractor, Allocator, Tag>>

   This specialization is available as long as the type managed by |object| is
   also usable by ``std::hash``.

