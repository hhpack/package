<?hh //strict

namespace HHPack\Package\Test;

use HHPack\Package\{VendorPackage, VendorNamespace};
use HHPack\Package\Test\Fixtures\Example1;
use type Facebook\HackTest\HackTest;
use function Facebook\FBExpect\expect;

final class VendorPackageTest extends HackTest {
  public function testPackageName(): void {
    $namespace = VendorNamespace::of(
      Pair { 'HHPack\\Package\\Test\\Fixtures\\', __DIR__.'/fixtures' },
    );
    $package = new VendorPackage([$namespace]);

    $classes = $package->classes()->toImmVector();
    expect($classes->count())->toBeSame(2);
  }
}
