#include <flyweight/cache.hpp>
#include <string>

#include <unittest/unittest.hpp>

struct texture {
  texture (std::string&& name) : name { std::move(name) } { }
  std::string const& id () const { return this->name; }

private:
  std::string name;
};

struct id_extractor {
  std::string const& operator ()(texture const& tex) const { return tex.id(); }
};

int main () {
  using namespace unittest;

  test("cache") = {
    task("is-associative") = [] {
      assert::is_false(flyweight::cache<std::string>::is_associative::value);
    },

    task("empty") = [] {
      assert::is_true(flyweight::cache<std::string>::ref().empty());
    },

    task("find") = [] {
      std::string not_there { "not there" };
      auto value = flyweight::cache<std::string>::ref().find(not_there);
      assert::is_not_null(value.get());
    },

    task("size") = [] {
      assert::equal(flyweight::cache<std::string>::ref().size(), 0);

      std::string size_1 { "size-1" };
      std::string size_2 { "size-2" };

      auto value = flyweight::cache<std::string>::ref().find(size_1);
      assert::equal(flyweight::cache<std::string>::ref().size(), 1);
      auto value2 = flyweight::cache<std::string>::ref().find(size_2);
      assert::equal(flyweight::cache<std::string>::ref().size(), 2);
    }
  };

  using texture_cache = flyweight::cache<texture, id_extractor>;
  test("kv-cache") = {
    task("is-associative") = [] {
      assert::is_true(texture_cache::is_associative::value);
    },

    task("empty") = [] {
      assert::is_true(texture_cache::ref().empty());
    },

    task("find") = [] {
      ::texture grass { "grass.jpg" };
      auto value = texture_cache::ref().find(grass);
      assert::is_not_null(value.get());
    },

    task("size") = [] {
      assert::equal(texture_cache::ref().size(), 0);

      ::texture grass { "grass.jpg" };
      ::texture water { "water.jpg" };

      auto value = texture_cache::ref().find(grass);
      assert::equal(texture_cache::ref().size(), 1);

      auto value2 = texture_cache::ref().find(water);
      assert::equal(texture_cache::ref().size(), 2);
    }
  };

  monitor::run();
}
