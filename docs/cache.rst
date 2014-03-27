.. _flyweight-cache-component:

Flyweight Cache
---------------

.. default-domain:: cpp

.. |object| replace:: :class:`object <object\<T, KeyExtractor, Allocator, Tag>>`
.. |cache| replace:: :class:`cache <cache\<T, KeyExtractor, Allocator, Tag>>`

The |cache| component of MNMLSTC Flyweight is the backing store used by
|object|. While it is *technically* an internal component, it is provided
in the case that a user would prefer to implement a more custom flyweight-like
type.

.. namespace:: flyweight

.. class:: cache<T, KeyExtractor, Allocator, Tag>

   |cache| takes the same 4 types as |object|. This is because they are
   forwarded from |object| to |cache|. A cache is *not* copyable *nor* is it
   moveable.

   .. type:: extractor_type
   .. type:: allocator_type
   .. type:: key_type
   .. type:: tag_type

   .. type:: difference_type
   .. type:: value_type
   .. type:: size_type
   .. type:: const_iterator
   .. type:: iterator
   .. type:: const_reference
   .. type:: reference
   .. type:: const_pointer
   .. type:: pointer

   .. function:: cache& ref () noexcept

   .. function:: const_iterator begin () const noexcept
   .. function:: const_iterator end () const noexcept
   .. function:: size_type size () const noexcept
   .. function:: bool empty () const noexcept
   .. function:: std::shared_ptr<T const> find (ValueType&& value) noexcept
