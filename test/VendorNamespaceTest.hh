<?hh //strict

namespace HHPack\Package\Test;

use HHPack\Package\VendorNamespace;
use HHPack\Package\Test\Fixtures\Example1;
use HackPack\HackUnit\Contract\Assert;

final class VendorNamespaceTest {
  <<Test>>
  public function packageName(Assert $assert): void {
    $ns = VendorNamespace::of(
      Pair {'HHPack\\Package\\Test\\Fixtures\\', __DIR__.'/fixtures'},
    );
    $assert->string($ns->name())->is('HHPack\\Package\\Test\\Fixtures');
    $assert->string($ns->directory())->is(\realpath(__DIR__.'/fixtures'));
  }

  <<Test>>
  public function directoryName(Assert $assert): void {
    $ns = VendorNamespace::of(
      Pair {'HHPack\\Package\\Test\\Fixtures\\', __DIR__.'/fixtures'},
    );
    $classes = $ns->classes()->toImmVector();
    $assert->int($classes->count())->eq(2);
  }
}
