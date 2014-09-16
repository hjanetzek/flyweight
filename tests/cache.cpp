#define CATCH_CONFIG_MAIN
#include <flyweight/cache.hpp>
#include <string>

#include <catch.hpp>

struct texture {
  texture (std::string&& name) : name { std::move(name) } { }
  std::string const& id () const { return this->name; }

private:
  std::string name;
};

struct id_extractor {
  std::string const& operator ()(texture const& tex) const { return tex.id(); }
};

using texture_cache = flyweight::cache<texture, id_extractor>;

TEST_CASE("cache-is-associative") {
  CHECK_FALSE(flyweight::cache<std::string>::is_associative::value);
}

TEST_CASE("cache-empty") {
  CHECK(flyweight::cache<std::string>::ref().empty());
}

TEST_CASE("cache-find") {
  std::string not_there { "not there" };
  auto value = flyweight::cache<std::string>::ref().find(not_there);
  CHECK(value.get());
}

TEST_CASE("cache-size") {
  CHECK(flyweight::cache<std::string>::ref().size() == 0);

  std::string size_1 { "size-1" };
  std::string size_2 { "size-2" };

  auto value = flyweight::cache<std::string>::ref().find(size_1);
  CHECK(flyweight::cache<std::string>::ref().size() == 1);
  auto value2 = flyweight::cache<std::string>::ref().find(size_2);
  CHECK(flyweight::cache<std::string>::ref().size() == 2);
}

/* kv-cache */
TEST_CASE("kv-cache-is-associative") {
  CHECK(texture_cache::is_associative::value);
}

TEST_CASE("kv-cache-empty") {
  CHECK(texture_cache::ref().empty());
}

TEST_CASE("kv-cache-find") {
  ::texture grass { "grass.jpg" };
  auto value = texture_cache::ref().find(grass);
  CHECK(value.get());
}

TEST_CASE("kv-cache-size") {
  CHECK(texture_cache::ref().size() == 0);

  ::texture grass { "grass.jpg" };
  ::texture water { "water.jpg" };

  auto value = texture_cache::ref().find(grass);
  CHECK(texture_cache::ref().size() == 1);

  auto value2 = texture_cache::ref().find(water);
  CHECK(texture_cache::ref().size() == 2);
}
