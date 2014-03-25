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

   .. type:: value_type

      Represents the type that |object| acts as a handle for. It is *always*
      ``T const``.
