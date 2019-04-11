namespace HHPack\Package\Test;

use HHPack\Package\VendorNamespace;
use HHPack\Package\Test\Fixtures\Example1;
use type Facebook\HackTest\HackTest;
use function Facebook\FBExpect\expect;

final class VendorNamespaceTest extends HackTest {
  public function testPackageName(): void {
    $ns = VendorNamespace::of(
      Pair { 'HHPack\\Package\\Test\\Fixtures\\', __DIR__.'/fixtures' },
    );
    expect($ns->name())->toBeSame('HHPack\\Package\\Test\\Fixtures');
    expect($ns->directory())->toBeSame(\realpath(__DIR__.'/fixtures'));
  }

  public function testDirectoryName(): void {
    $ns = VendorNamespace::of(
      Pair { 'HHPack\\Package\\Test\\Fixtures\\', __DIR__.'/fixtures' },
    );
    $classes = $ns->classes()->toImmVector();
    expect($classes->count())->toBeSame(3);
  }
}
