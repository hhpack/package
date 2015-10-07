<?hh //partial

namespace package\spec;

use package\PackageSpecification;
use package\spec\fixtures\Example1;

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
  describe('getClassFiles()', function () {
    it('returns class files for vendor package', function () {
      $items = Vector {};
      $classes = $this->package->getClassFiles();
      foreach ($classes as $class) {
        $items->add($class);
      }
      expect($items->count())->toBe(1);
    });
  });
});
