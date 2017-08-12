<?hh //strict

namespace HHPack\Package\Test;

use HHPack\Package\{ VendorPackage, VendorNamespace };
use HHPack\Package\Test\Fixtures\Example1;
use HackPack\HackUnit\Contract\Assert;

final class VendorPackageTest
{
    <<Test>>
    public function packageName(Assert $assert): void
    {
        $namespace = VendorNamespace::of( Pair {
            'HHPack\\Package\\Test\\Fixtures\\',
            __DIR__ . '/fixtures'
        });
        $package = new VendorPackage([ $namespace ]);

        $classes = $package->classes()->toImmVector();
        $assert->int($classes->count())->eq(2);
    }
}
