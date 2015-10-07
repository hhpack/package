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
  describe('getSourceFiles()', function () {
    it('returns source files for vendor package', function () {
      $items = Vector {};
      $sources = $this->package->getSourceFiles();
      foreach ($sources as $source) {
        $items->add($source);
      }
      expect($items->count())->toBe(1);
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
  describe('resolve()', function () {
    it('returns new resolve class instance', function () {
      $instance = $this->package->resolve(__DIR__ . '/fixtures/Example1.hh');
      expect($instance)->toBeAnInstanceOf(Example1::class);
    });
  });
  describe('resolveWith()', function () {
    it('returns new resolve class instance with parameters', function () {
      $instance = $this->package->resolveWith(__DIR__ . '/fixtures/Example1.hh', [ 'foo' ]);
      expect($instance)->toBeAnInstanceOf(Example1::class);
      expect($instance->getName())->toBe('foo');
    });
  });
});
