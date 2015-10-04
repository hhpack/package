<?hh //partial

namespace package\spec;

use package\PackageSpecification;

describe(PackageSpecification::class, function () {
  beforeEach(function () {
    $this->package = new PackageSpecification(shape(
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
});
