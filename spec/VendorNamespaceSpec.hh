<?hh //partial

namespace hhpack\package\spec;

use hhpack\package\VendorNamespace;
use hhpack\package\spec\fixtures\Example1;

describe(VendorNamespace::class, function () {
  beforeEach(function () {
    $this->ns = VendorNamespace::of(Pair {
      'hhpack\\package\\spec\\fixtures\\',
      __DIR__ . '/fixtures'
    });
  });
  describe('name()', function () {
    it('returns namespace', function () {
      expect($this->ns->name())->toBe('hhpack\\package\\spec\\fixtures');
    });
  });
  describe('directory()', function () {
    it('returns package directory', function () {
      expect($this->ns->directory())->toBe(realpath(__DIR__ . '/fixtures'));
    });
  });
  describe('classes()', function () {
    it('returns class files for vendor package', function () {
      $classes = $this->ns->classes()->toImmVector();
      expect($classes->count())->toBe(2);
    });
  });
});
