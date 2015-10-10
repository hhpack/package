<?hh //partial

namespace package\spec;

use package\Package;
use package\spec\fixtures\Example1;

describe(Package::class, function () {
  beforeEach(function () {
    $this->package = Package::fromOptions(shape(
      'namespace' => 'package\\spec\\fixtures\\',
      'packageDirectory' => __DIR__ . '/fixtures'
    ));
  });
  describe('getNamespace()', function () {
    it('returns namespace', function () {
      expect($this->package->getNamespace())->toBe('package\\spec\\fixtures');
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
