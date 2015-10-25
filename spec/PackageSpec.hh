<?hh //partial

namespace hhpack\package\spec;

use hhpack\package\Package;
use hhpack\package\spec\fixtures\Example1;

describe(Package::class, function () {
  beforeEach(function () {
    $this->package = Package::fromOptions(shape(
      'namespace' => 'hhpack\\package\\spec\\fixtures\\',
      'packageDirectory' => __DIR__ . '/fixtures'
    ));
  });
  describe('getNamespace()', function () {
    it('returns namespace', function () {
      expect($this->package->getNamespace())->toBe('hhpack\\package\\spec\\fixtures');
    });
  });
  describe('getPackageDirectory()', function () {
    it('returns package directory', function () {
      expect($this->package->getPackageDirectory())->toBe(realpath(__DIR__ . '/fixtures'));
    });
  });
  describe('classes()', function () {
    it('returns class files for vendor package', function () {
      $classes = $this->package->classes()->toImmVector();
      expect($classes->count())->toBe(2);
    });
  });
});
