<?hh //partial

namespace hhpack\package\spec;

use hhpack\package\VendorPackage;
use hhpack\package\VendorNamespace;
use hhpack\package\spec\fixtures\Example1;

describe(VendorPackage::class, function () {
  beforeEach(function () {
    $namespace = VendorNamespace::of( Pair {
      'hhpack\\package\\spec\\fixtures\\',
      __DIR__ . '/fixtures'
    });
    $this->package = new VendorPackage([ $namespace ]);
  });
  describe('classes()', function () {
    it('returns class files for vendor package', function () {
      $classes = $this->package->classes()->toImmVector();
      expect($classes->count())->toBe(2);
    });
  });
});
