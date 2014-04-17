.. _flyweight-extractor-component:

Key Extractor
=============

.. |cache| replace:: :class:`cache <cache\<T, KeyExtractor, Allocator, Tag>>`

.. default-domain:: cpp

The key extractor exists to extract the lookup key for a flyweight. When the
user does not provide a custom key extractor, the default one is used. This
extractor simply takes a ``T const&`` and returns it. The type returned by a
key extractor determines the key type used inside of the |cache|. The default
key extractor is extremely small, and very simple.

.. class:: extractor<T>

   .. function:: T const& operator () (T const& arg) const noexcept

      :returns: *arg*
